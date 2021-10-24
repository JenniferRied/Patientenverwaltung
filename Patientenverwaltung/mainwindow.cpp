#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "verwaltung.h"
#include "suchen.h"

#include <QTableWidget>
#include <QTableWidgetItem>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->hinzufuegen_button, SIGNAL (clicked()),this, SLOT (hinzufuegen_buttonclick()));
    connect(ui->aendern_button, SIGNAL (clicked()),this, SLOT (aendern_buttonclick()));
    connect(ui->loeschen_button, SIGNAL (clicked()),this, SLOT (loeschen_buttonclick()));
    connect(ui->suchen_button, SIGNAL (clicked()),this, SLOT (suchen_buttonclick()));
    connect(ui->export_button, SIGNAL (clicked()),this, SLOT (export_buttonclick()));
    connect(ui->anzeigen_button, SIGNAL (clicked()),this, SLOT (anzeigen_buttonclick()));
    connect(ui->schliessen_button,SIGNAL (clicked()),this, SLOT(anzeige_schliessen_buttonclick()));

    //Icons

    //https://www.clipartmax.com/download/m2i8m2Z5K9Z5N4d3_plus-icons-no-attribution-add-icon-green/
    QIcon* hinzufuegen = new QIcon(":/Bilder/clipart1719902.png");
    //https://www.clipartmax.com/download/m2i8b1N4m2N4m2b1_trash-can-clip-art/
    QIcon* loeschen = new QIcon(":/Bilder/clipart1976610.png");
    //https://www.clipartmax.com/download/m2i8i8G6i8G6K9i8_pencil-and-paper-clipart-school-pencil-clip-art/
    QIcon* aendern = new QIcon(":/Bilder/clipart209647.png");
    //https://www.clipartmax.com/download/m2K9A0b1m2d3G6K9_clipart-magnifying-glass-black-clipart/
    QIcon* suche = new QIcon(":/Bilder/clipart28741.png");
    //https://www.clipartmax.com/download/m2i8H7m2G6d3A0N4_email-free-clip-art-envelope-clipart-transparent-background/
    QIcon* export_icon = new QIcon(":/Bilder/clipart611030.png");

    QSize iconSize;
    iconSize.setWidth(60);
    iconSize.setHeight(60);

    ui->hinzufuegen_button->setIcon(*hinzufuegen);
    ui->loeschen_button->setIcon(*loeschen);
    ui->loeschen_button->setIconSize(iconSize);
    ui->aendern_button->setIcon(*aendern);
    ui->aendern_button->setIconSize(iconSize);
    ui->suchen_button->setIcon(*suche);
    ui->suchen_button->setIconSize(iconSize);
    ui->export_button->setIcon(*export_icon);
    ui->export_button->setIconSize(iconSize);

    ui->widget->setVisible(false);
    Speicher::getInstance().beobachter_anhaengen(this);

    tabelle_erzeugen();
}

void MainWindow::hinzufuegen_buttonclick()
{
    Verwaltung *verw = new Verwaltung(0);
    verw->show();
}

void MainWindow::aendern_buttonclick()
{
    int patienten_id = ausgewaehlte_id();

    if (patienten_id > 0)
    {
        Verwaltung *verw = new Verwaltung(patienten_id);
        verw->show();
    }

}

void MainWindow::loeschen_buttonclick()
{
    int patienten_id = ausgewaehlte_id();

    if (patienten_id > 0)
    {
        QMessageBox del_msgBox;
        del_msgBox.setWindowTitle("Kontrollnachfrage");
        del_msgBox.setText("Wollen Sie den Patienten wirklich löschen?");
        del_msgBox.setStandardButtons(QMessageBox::Yes);
        del_msgBox.addButton(QMessageBox::No);
        del_msgBox.setDefaultButton(QMessageBox::No);

        if(del_msgBox.exec() == QMessageBox::Yes)
        {
            Speicher::getInstance().loesche_patient(patienten_id);
        }
    }
}

void MainWindow::suchen_buttonclick()
{
    Suchen *suche = new Suchen();
    suche->show();

    QString ergebnis = suche->get_suchen_text();                            //For-Schleife soll die Tabelleneinträge durchlaufen und im Anschluss alle Einträge, welche nicht
    for(int i= 0; i < ui->tableWidget->rowCount(); i++){                    //dem Suchbegriff entsprechen, versteckt werden
        bool treffer = false;                                               //Dazu muss ich die MainWindow-UI in suchen.cpp aufrufen, was mir aktuell nicht gelingt.
        for(int j = 0; j < ui->tableWidget->columnCount(); j++){
            QTableWidgetItem *eintrag = ui->tableWidget->item(i, j);
            if( eintrag->text().contains(ergebnis))
            {
                treffer = true;
                break;
            }
        }
        ui->tableWidget->setRowHidden( i, !treffer);
    }



}

void MainWindow::export_buttonclick()
{
    QList<Patient*> patienten;
    QList<QTableWidgetSelectionRange> ausgewaehlte_zeilen = ui->tableWidget->selectedRanges();


    for (int i = 0; i < ausgewaehlte_zeilen.size(); i++)
    {
        int zeile = ausgewaehlte_zeilen.at(i).topRow();
        int id = ui->tableWidget->item(zeile,0)->text().toInt();
        Patient* patient= Speicher::getInstance().get_patient(id);
        patienten.append(patient);
    }

    QFile patienten_datei("Export.json");

    if(patienten_datei.exists())
    {
        QMessageBox del_msgBox;
        del_msgBox.setWindowTitle("Kontrollnachfrage");
        del_msgBox.setText("Wollen Sie den alten Export überschreiben");
        del_msgBox.setStandardButtons(QMessageBox::Yes);
        del_msgBox.addButton(QMessageBox::No);
        del_msgBox.setDefaultButton(QMessageBox::No);

        if(del_msgBox.exec() == QMessageBox::Yes)
        {
            if (!patienten_datei.open(QIODevice::WriteOnly))
            {
                //Json-Datei nicht erfolgreich geöffnet
                return;
            }

            QJsonObject json = Speicher::getInstance().json_erstellen(patienten);
            patienten_datei.write(QJsonDocument(json).toJson(QJsonDocument::Indented));
            ui->tableWidget->clearSelection();
            // erfolgreich in datei gespeichert
        }
    }
}

void MainWindow::anzeigen_buttonclick()
{
    int patienten_id = ausgewaehlte_id();

    if (patienten_id > 0)
    {
        ui->widget->setVisible(true);
        Patient* patient= Speicher::getInstance().get_patient(patienten_id);
        ui->anzeige_label->setText(patient->get_titel() + "\n" + patient->get_vorname() + " " + patient->get_nachname() + "\n"
                                   + patient->get_strasse() + " " + QString::number(patient->get_hnr()) + "\n"
                                   + QString::number(patient->get_plz()) + " " + patient->get_ort() + "\n"
                                   + patient->get_geschlecht() + "\n"
                                   + patient->get_geburtstag().toString("yyyy.MM.dd") + "\n"
                                   + patient->get_tel());
    }
}

void MainWindow::anzeige_schliessen_buttonclick()
{
    ui->widget->setVisible(false);
    ui->anzeige_label->setText("");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::patient_updated()
{
    tabelle_erzeugen();
}

void MainWindow::tabelle_erzeugen()
{
    QList<Patient*> patienten = Speicher::getInstance().get_alle_patienten();

    ui->tableWidget->setRowCount(patienten.size());
    ui->tableWidget->setColumnCount(4); //Anzahl Spalten
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->tableWidget->setHorizontalHeaderItem(0,new QTableWidgetItem("Id"));
    ui->tableWidget->setHorizontalHeaderItem(1,new QTableWidgetItem("Titel"));
    ui->tableWidget->setHorizontalHeaderItem(2,new QTableWidgetItem("Vorname"));
    ui->tableWidget->setHorizontalHeaderItem(3,new QTableWidgetItem("Nachname"));
    ui->tableWidget->setHorizontalHeaderItem(4,new QTableWidgetItem("Geburtsdatum"));


    for (int patienten_nr = 0; patienten_nr < patienten.size(); patienten_nr++)
    {

        Patient* patient = patienten[patienten_nr];

        QTableWidgetItem *patientId = new QTableWidgetItem(QString::number(patient->get_patient_id()));
        patientId->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->setItem(patienten_nr,0,patientId);
        QTableWidgetItem *new_titel = new QTableWidgetItem(patient->get_titel());
        ui->tableWidget->setItem(patienten_nr,1,new_titel);
        QTableWidgetItem *new_vorname = new QTableWidgetItem(patient->get_vorname());
        ui->tableWidget->setItem(patienten_nr,2,new_vorname);
        QTableWidgetItem *new_nachname = new QTableWidgetItem(patient->get_nachname());
        ui->tableWidget->setItem(patienten_nr,3,new_nachname);
        QTableWidgetItem *new_geb = new QTableWidgetItem(patient->get_geburtstag().toString("yyyy.MM.dd"));
        ui->tableWidget->setItem(patienten_nr,4,new_geb);
    }

    ui->tableWidget->horizontalHeader()->setMinimumSectionSize(1);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Fixed);
    ui->tableWidget->setColumnWidth(0, 30);
}

int MainWindow::ausgewaehlte_id()
{
    QList<QTableWidgetSelectionRange> ausgewaehlt = ui->tableWidget->selectedRanges();

    int ausgewaehlte_Zeile = -1;

    if (ausgewaehlt.size() == 0)
    {
        //Fehlermeldung, dass kein Patient ausgewählt wurde
    }
    else if (ausgewaehlt.size() == 1)
    {
        QTableWidgetSelectionRange const& nur_eins = ausgewaehlt.at(0);

        ausgewaehlte_Zeile = ui->tableWidget->item(nur_eins.topRow(), 0)->text().toInt();
    }
    else
    {
        //Fehlermeldung mehr als ein Patient ausgewählt
    }

    ui->tableWidget->clearSelection();

    return ausgewaehlte_Zeile;
}
