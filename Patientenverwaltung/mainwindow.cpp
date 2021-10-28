#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "verwaltung.h"

#include <QTableWidget>
#include <QTableWidgetItem>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    //in dieser Funktion wird die ui des MainWindow erzeugt
    ui->setupUi(this);

    //Buttons im MainWindow
    connect(ui->hinzufuegen_button, SIGNAL (clicked()),this, SLOT (hinzufuegen_buttonclick()));
    connect(ui->aendern_button, SIGNAL (clicked()),this, SLOT (aendern_buttonclick()));
    connect(ui->loeschen_button, SIGNAL (clicked()),this, SLOT (loeschen_buttonclick()));
    connect(ui->suchen_button, SIGNAL (clicked()),this, SLOT (suchen_buttonclick()));
    connect(ui->export_button, SIGNAL (clicked()),this, SLOT (export_buttonclick()));
    connect(ui->anzeigen_button, SIGNAL (clicked()),this, SLOT (anzeigen_buttonclick()));
    connect(ui->schliessen_button,SIGNAL (clicked()),this, SLOT(anzeige_schliessen_buttonclick()));
    connect(ui->suche_beenden_button, SIGNAL (clicked()),this, SLOT(suche_beenden_buttonclick()));
    connect(ui->suche_starten_button, SIGNAL (clicked()),this, SLOT(suche_starten_buttonclick()));

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
    //https://www.clipartmax.com/download/m2i8K9b1N4i8A0A0_user-image-clip-art/
    QIcon* anzeigen_icon = new QIcon(":/Bilder/clipart153137.png");

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
    ui->anzeigen_button->setIcon(*anzeigen_icon);
    ui->anzeigen_button->setIconSize(iconSize);

    //Tool Tips

    ui->hinzufuegen_button->setToolTip("Patienten hinzufügen");
    ui->aendern_button->setToolTip("Patientendaten ändern");
    ui->loeschen_button->setToolTip("Patienten löschen");
    ui->anzeigen_button->setToolTip("Patienten anzeigen");
    ui->suchen_button->setToolTip("Suche");
    ui->export_button->setToolTip("Auswahl exportieren");

    ui->widget->setVisible(false);
    ui->suchen_widget->setVisible(false);
    Speicher::getInstance().beobachter_anhaengen(this);

    tabelle_erzeugen();
}

/*die hinzufügen_buttonclick Funktion ruft nach einem click auf den hinzufügen_button
das Fenster "Neuer Patient" auf, indem man einen neuen Patienten hinzufügen kann*/

void MainWindow::hinzufuegen_buttonclick()
{
    Verwaltung *verw = new Verwaltung(0);
    verw->show();
}

/*die aendern_buttonclick Funktion ruft nach einem click auf den aendern_button
das Fenster "Patient editieren" auf, indem man einen bereits bekannten Patienten editieren kann
das Fenster "Patient editieren" ist die gleiche Maske wie beim hinzufügen eines Patienten.
Allerdings ist dieses Fenster bereits ausgefüllt*/

void MainWindow::aendern_buttonclick()
{
    int patienten_id = ausgewaehlte_id();

    if (patienten_id > 0)
    {
        Verwaltung *verw = new Verwaltung(patienten_id);
        verw->show();
    }

}

/*die FUnktion loeschen_buttonclick, wird aufgerufen durch einen click auf den loeschen_button.
Zunächst erscheint eine Kontrollabfrage, ob der Nutzer den markierten Patienten wirklich löschen möchte.
Erst wenn diese Frage mit dem Button "Yes" beantwortet wird, wird der Patient gelöscht.
Wird die Frage mit "No" beantwortet, wird der Vorgang abgebrochen*/

void MainWindow::loeschen_buttonclick()
{
    int patienten_id = ausgewaehlte_id();

    if (patienten_id > 0)
    {
        //Kontrollabfrage

        QMessageBox del_msgBox;
        del_msgBox.setWindowTitle("Kontrollnachfrage");
        del_msgBox.setText("Wollen Sie den Patienten wirklich löschen?");
        del_msgBox.setStandardButtons(QMessageBox::Yes);
        del_msgBox.addButton(QMessageBox::No);
        del_msgBox.setDefaultButton(QMessageBox::No);

        // erst bei click des "Yes"-Buttons wird gelöscht
        if(del_msgBox.exec() == QMessageBox::Yes)
        {
            Speicher::getInstance().loesche_patient(patienten_id);
        }
    }
}

/*die Funktion suchen_buttonclick macht, nach click des suchen_buttons, das Widget für die Suche sichtbar*/

void MainWindow::suchen_buttonclick()
{
    ui->suchen_widget->setVisible(true);

}

/*die Funktion suche_starten_buttonclick löst, durch einen click auf den suche_starten_button,
die Suche aus. Hierfür werden die einzelnen Felder des TableWidgets mit den Patienteneinträgen durchlaufen.
Die Funktion überprüft zuerst nach welchen Suchkriterien gesucht werden soll. Es gibt die Suchkriterien Nachname, Vorname und Geburtsdatum.
Der Nutzer muss mindestens eins der Suchkriterien angeben. Er kann diese allerdings beliebig kombinieren, sodass auch nach einem genauen Patienten
mithilfe des Vor- und Nachnamen und des Geburtsdatum gesucht werden kann. In der for-Schleife werden die Tabelleneinträge geprüft und die Einträge,
die zur Suche passen werden temporär gespeichert und im Anschluss, wenn die komplette Liste durchsucht wurde, werden die Treffer anstatt der ursprünglichen
Liste angezeigt.*/

void MainWindow::suche_starten_buttonclick()
{
    QString vorname = ui->vorname_lineEdit->text();
    QString nachname = ui->nachname_lineEdit->text();
    QString geburtstag = ui->geburtstag_suche_lineEdit->text();
    bool keine_eingabe = false;
    for(int i = 0; i < ui->tableWidget->rowCount(); i++){
            bool treffer = false;
            for(int j = 0; j < ui->tableWidget->columnCount(); j++){
                QTableWidgetItem *eintrag = ui->tableWidget->item(i, j);
                QTableWidgetItem *eintrag2 = ui->tableWidget->item(i,j+1);
                QTableWidgetItem *eintrag3 = ui->tableWidget->item(i,j+2);

                //Eingabe cases

                //Fehlermeldung wenn kein Feld ausgefüllt wurde


                if(ui->geburtstag_suche_lineEdit->text().isEmpty() && ui->vorname_lineEdit->text().isEmpty() && ui->nachname_lineEdit->text().isEmpty())
                {
                    keine_eingabe = true;
                }


                if(!ui->vorname_lineEdit->text().isEmpty() && !ui->nachname_lineEdit->text().isEmpty())
                {
                    //alle 3 Felder ausgefüllt

                    if(!ui->geburtstag_suche_lineEdit->text().isEmpty())
                    {
                        if( eintrag->text() == vorname and eintrag2->text() == nachname and eintrag3->text() == geburtstag)
                        {
                            treffer = true;
                            break;
                        }
                    }

                    //Vor und Nachname ausgefüllt

                    if(ui->geburtstag_suche_lineEdit->text().isEmpty())
                    {
                        if( eintrag->text()== vorname and eintrag2->text() == nachname )
                        {
                            treffer = true;
                            break;
                        }
                    }
                }



                if(!ui->vorname_lineEdit->text().isEmpty() || !ui->nachname_lineEdit->text().isEmpty())
                {
                    //nur 1 der Namensfelder ausgefüllt

                    if(ui->geburtstag_suche_lineEdit->text().isEmpty())
                    {
                        if( eintrag->text().contains(vorname + nachname))
                        {
                            treffer = true;
                            break;
                        }
                    }

                    //Geburtsdatumsfeld ebenfalls ausgefüllt
                    if(!ui->geburtstag_suche_lineEdit->text().isEmpty())
                    {
                        //Vorname und Geburtsdatumsfeld ausgefüllt
                        if(!ui->vorname_lineEdit->text().isEmpty())
                        {
                            if(eintrag->text() == vorname && eintrag3->text() == geburtstag)
                            {
                                treffer = true;
                                break;
                            }
                        }
                        //Nachname und Geburtsdatumsfeld ausgefüllt
                        else
                        {
                            if(eintrag->text() == nachname && eintrag2->text() == geburtstag)
                            {
                                treffer = true;
                                break;
                            }
                        }
                    }

                }

                //Nur Geburtsdatumsfeld ausgefüllt

                if(ui->vorname_lineEdit->text().isEmpty() && ui->nachname_lineEdit->text().isEmpty())
                {
                    if(eintrag->text().contains(geburtstag))
                    {
                        treffer = true;
                        break;
                    }
                }



            }
            ui->tableWidget->setRowHidden( i, !treffer);
            kein_treffer.append(*ui->tableWidget->item( i, !treffer));
        }

    //Fehlermeldung, falls der Nutzer versucht die Suche zu starten ohne ein Suchkriterium eingegeben zu haben

    if(keine_eingabe == true)
    {
        QMessageBox fehlermeldung;
        fehlermeldung.critical(0, "Fehler", "Sie müssen mindestens 1 Feld für die Suche ausfüllen.");
    }

}

/*durch einen click auf den suche_beenden_button wird die Funktion suche_beenden_buttonclick aufgerufen.
In dieser Funktion werden die eingaben der Suchkriterien aus den dementsprechenden Felder gelöscht und
das Suchen Widget wieder versteckt. Danach wird wieder die gesamte Liste der Patienten angezeigt*/

void MainWindow::suche_beenden_buttonclick()
{
    ui->suchen_widget->setVisible(false);
    ui->nachname_lineEdit->setText("");
    ui->vorname_lineEdit->setText("");
    ui->geburtstag_suche_lineEdit->setText("");
    for(int i = 0; i < kein_treffer.size(); i++)
    {
        ui->tableWidget->showRow(i);
    }
    tabelle_erzeugen();
}

/*Diese Funktion erstellt aus den ausgewählten Zeilen aus der ui eine json-Datei.
Wenn bereits die json-Datei existiert wird abgefragt, ob man die Datei überschreiben möchte.*/

void MainWindow::export_buttonclick()
{
    QList<Patient*> patienten;
    QList<QTableWidgetSelectionRange> ausgewaehlte_zeilen = ui->tableWidget->selectedRanges();

    if (ausgewaehlte_zeilen.size() == 0)
    {
        QMessageBox fehlermeldung;
        fehlermeldung.critical(0, "Fehler", "Es wurde kein Patient ausgewählt.");
        return;
    }

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

        if(del_msgBox.exec() == QMessageBox::No)
        {
            return;
        }
    }

    if (!patienten_datei.open(QIODevice::WriteOnly))
    {
        QMessageBox fehlermeldung;
        fehlermeldung.critical(0, "Fehler", "Ein Fehler beim Öffnen der Datei ist aufgetreten.");
        return;
    }

    QJsonObject json = Speicher::getInstance().json_erstellen(patienten);
    patienten_datei.write(QJsonDocument(json).toJson(QJsonDocument::Indented));
    ui->tableWidget->clearSelection();

    QMessageBox erfolgsmeldung;
    erfolgsmeldung.information(0, "Erfolgreich gespeichert", "Die Speicherung ist erfolgreich vonstattengegangen.");
}


/*Wenn der Anzeige-Button geklickt wird, wird das Anzeige-Widget sichtbar gemacht und der in der Tabelle ausgewählte Patient in dem Label des Widgets angezeigt.*/

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

/*Wenn der Button in dem Anzeige-Widget geklickt wird, wird dieses Widget wieder unsichtbar gemacht und das Label geleert.*/

void MainWindow::anzeige_schliessen_buttonclick()
{
    ui->widget->setVisible(false);
    ui->anzeige_label->setText("");
}

/*Der Destruktor der MainWindow Klasse.*/

MainWindow::~MainWindow()
{
    delete ui;
}

/*Wenn ein Patient geupdated wurde, wird diese Funktion aufrufen, die das neu erstellen der Tabelle aufruft.*/

void MainWindow::patient_updated()
{
    tabelle_erzeugen();
}

/*Diese Funktion erzeugt die Tabelle. Es gibt 5 Spalten und genau soviele Zeilen wie es Patienten gibt.
Die Tabelle passt sich dynamisch der Fenstergröße an, wobei die ID-Spalte eine festgelegte Spaltenbreite hat.*/

void MainWindow::tabelle_erzeugen()
{
    QList<Patient*> patienten = Speicher::getInstance().get_alle_patienten();

    ui->tableWidget->setRowCount(patienten.size());
    ui->tableWidget->setColumnCount(5); //Anzahl Spalten
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

/*Diese Funktion überprüft, wie viele Zeilen in der Tablle ausgewählt sind.
Sind mehr als eins oder gar keine ausgewählt, gibt es eine Fehlermeldung,
da sie nur von Funktionen aufgerufen wird, in der nur ein Patient ausgwählt werden darf.*/

int MainWindow::ausgewaehlte_id()
{
    QList<QTableWidgetSelectionRange> ausgewaehlt = ui->tableWidget->selectedRanges();

    int ausgewaehlte_Zeile = -1;

    if (ausgewaehlt.size() == 0)
    {
        //Fehlermeldung, dass kein Patient ausgewählt wurde
        QMessageBox fehlermeldung;
        fehlermeldung.critical(0, "Fehler", "Es wurde kein Patient ausgewählt");
    }
    else if (ausgewaehlt.size() == 1)
    {
        QTableWidgetSelectionRange const& nur_eins = ausgewaehlt.at(0);

        ausgewaehlte_Zeile = ui->tableWidget->item(nur_eins.topRow(), 0)->text().toInt();
    }
    else
    {
        //Fehlermeldung mehr als ein Patient ausgewählt
        QMessageBox fehlermeldung;
        fehlermeldung.critical(0, "Fehler", "Bitte nur einen Patienten auswählen");
    }

    ui->tableWidget->clearSelection();

    return ausgewaehlte_Zeile;
}
