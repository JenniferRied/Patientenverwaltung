#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "verwaltung.h"

#include <QCheckBox>
#include <QHBoxLayout>
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
        // Dialog, dass man sicher ist, dass es gelöscht werden soll
        Speicher::getInstance().loesche_patient(patienten_id);
    }
}

void MainWindow::suchen_buttonclick()
{

}

void MainWindow::export_buttonclick()
{
    QList<Patient*> patienten;
    int zeilen = ui->tableWidget->rowCount();

    for (int i = 0; i < zeilen; i++)
    {
        QWidget *item = ui->tableWidget->cellWidget(i,0);
        QCheckBox* checkB = qobject_cast <QCheckBox *> (item->layout()->itemAt(0)->widget());

        if(checkB->isChecked())
        {
            int id = ui->tableWidget->verticalHeaderItem(i)->text().toInt();
            Patient* patient= Speicher::getInstance().get_patient(id);
            patienten.append(patient);
        }
    }

    QFile patienten_datei("Export.json");

    if (!patienten_datei.open(QIODevice::WriteOnly))
    {
        //Json-Datei nicht erfolgreich geöffnet
        return;
    }

    QJsonObject json = Speicher::getInstance().json_erstellen(patienten);
    patienten_datei.write(QJsonDocument(json).toJson(QJsonDocument::Indented));
    // erfolgreich in datei gespeichert
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
                                   + patient->get_geburtstag().toString("dd.MM.yyyy") + "\n"
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
    ui->tableWidget->setColumnCount(5); //Anzahl Spalten
    ui->tableWidget->horizontalHeader()->setDefaultSectionSize(111);  //Breite der Spalten

    ui->tableWidget->setHorizontalHeaderItem(0,new QTableWidgetItem(""));
    ui->tableWidget->setHorizontalHeaderItem(1,new QTableWidgetItem("Titel"));
    ui->tableWidget->setHorizontalHeaderItem(2,new QTableWidgetItem("Vorname"));
    ui->tableWidget->setHorizontalHeaderItem(3,new QTableWidgetItem("Nachname"));
    ui->tableWidget->setHorizontalHeaderItem(4,new QTableWidgetItem("Geburtsdatum"));

    ui->tableWidget->setColumnWidth(0,1);

    for (int patienten_nr = 0; patienten_nr < patienten.size(); patienten_nr++)
    {

        Patient* patient = patienten[patienten_nr];

        QWidget *checkBoxWidget = new QWidget();
        QCheckBox *checkBox = new QCheckBox();
        QHBoxLayout *layoutCheckBox = new QHBoxLayout(checkBoxWidget);
        layoutCheckBox->addWidget(checkBox);
        layoutCheckBox->setAlignment(Qt::AlignCenter);

        checkBox->setChecked(false);

        QTableWidgetItem *patientId = new QTableWidgetItem(QString::number(patient->get_patient_id()));
        ui->tableWidget->setVerticalHeaderItem(patienten_nr, patientId);
        ui->tableWidget->setCellWidget(patienten_nr,0, checkBoxWidget);

        QTableWidgetItem *new_titel = new QTableWidgetItem(patient->get_titel());
        ui->tableWidget->setItem(patienten_nr,1,new_titel);
        QTableWidgetItem *new_vorname = new QTableWidgetItem(patient->get_vorname());
        ui->tableWidget->setItem(patienten_nr,2,new_vorname);
        QTableWidgetItem *new_nachname = new QTableWidgetItem(patient->get_nachname());
        ui->tableWidget->setItem(patienten_nr,3,new_nachname);
        QTableWidgetItem *new_geb = new QTableWidgetItem(patient->get_geburtstag().toString("dd.MM.yyyy"));
        ui->tableWidget->setItem(patienten_nr,4,new_geb);
    }
}

int MainWindow::ausgewaehlte_id()
{
    int zeilen = ui->tableWidget->rowCount();
    int patienten_id = 0;
    bool eins_ausgewaehlt = false;

    for (int i = 0; i < zeilen; i++)
    {
        QWidget *item = ui->tableWidget->cellWidget(i,0);
        QCheckBox* checkB = qobject_cast <QCheckBox *> (item->layout()->itemAt(0)->widget());

        if(checkB->isChecked())
        {
            if(eins_ausgewaehlt == false)
            {
                  eins_ausgewaehlt = true;
                  patienten_id = ui->tableWidget->verticalHeaderItem(i)->text().toInt();
            }else{
                //Fehlermeldung mehr als ein Patient ausgewählt
                return -1;
            }
        }
    }

    if (patienten_id == 0)
    {
        //Fehlermeldung, dass kein Patient ausgewählt wurde
        patienten_id = -1;
    }

    return patienten_id;
}
