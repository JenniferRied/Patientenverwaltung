#include "verwaltung.h"
#include "ui_verwaltung.h"
#include "patient.h"
#include "speicher.h"
#include <list>
#include <QMessageBox>
#include <QRegExp>
#include <QRegExpValidator>

/*In dieser Funktion wird die Verwaltungs ui erstellt(Konstruktor).*/

Verwaltung::Verwaltung(int patienten_id, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Verwaltung)
{
    ui->setupUi(this);

    //Vorgabe, dass die Telefonnummer nur aus Zahlen besteht und eine führende 0 besitzt und maximal 21 Ziffern lang ist
    QRegExp rx_tel("[0]{1}\\d{1,20}");
    rx_tel.setCaseSensitivity(Qt::CaseInsensitive);
    QValidator *tel_validator = new QRegExpValidator(rx_tel, this);
    ui->tel_nr_lineEdit->setValidator(tel_validator);
    ui->tel_nr_lineEdit->setMaxLength(21);

    //Vorgabe Postleitzahl besteht aus maximal 5 Zahlen
    QRegExp rx_plz("[0-9]{5}");
    QValidator *plz_validator = new QRegExpValidator(rx_plz, this);
    ui->plz_lineEdit->setValidator(plz_validator);
    ui->plz_lineEdit->setMaxLength(5);

    QList<QString> geschlecht;
    geschlecht.append(" ");
    geschlecht.append("w");
    geschlecht.append("m");
    geschlecht.append("d");
    ui->geschlecht_comboBox->addItems(geschlecht);

    //setzt die Überschrift des Fensters
    if (patienten_id > 0) {
        setWindowTitle("Patient editieren");
        patienten_editieren(patienten_id);
    } else {
        setWindowTitle("Neuer Patient");
    }


    connect(ui->geb_dateEdit, SIGNAL (dateChanged(QDate)), this, SLOT (datechange(QDate)));
    connect(ui->titel_lineEdit, SIGNAL (textChanged(QString)), this , SLOT (change()));
    connect(ui->nachname_lineEdit, SIGNAL (textChanged(QString)), this , SLOT (change()));
    connect(ui->vorname_lineEdit, SIGNAL (textChanged(QString)), this , SLOT (change()));
    connect(ui->ort_lineEdit, SIGNAL (textChanged(QString)), this , SLOT (change()));
    connect(ui->strasse_lineEdit, SIGNAL (textChanged(QString)), this , SLOT (change()));
    connect(ui->hnr_lineEdit, SIGNAL (textChanged(QString)), this , SLOT (change()));
    connect(ui->plz_lineEdit, SIGNAL (textChanged(QString)), this , SLOT (change()));
    connect(ui->tel_nr_lineEdit, SIGNAL (textChanged(QString)), this , SLOT (change()));
    connect(ui->geschlecht_comboBox, SIGNAL (currentTextChanged(QString)), this, SLOT (textchange(QString)));
    connect(ui->speichern_button,SIGNAL (clicked()),this, SLOT (ueberpruefen()));
    connect(ui->abbrechen_button, SIGNAL (clicked()), this, SLOT(abgebrochen()));
}

//Diese Funktion bricht den Vorgang des hinzufügen oder ändern eines Patiente ab und schließt das Fenster wieder.

void Verwaltung::abgebrochen()
{
    QDialog::close();
}

/*In dieser Funktion werden die Eingaben überprüft und gegebenenfalls Fehlermeldungen ausgegeben.
Erst wenn alle Eingaben gültig sind und alle Pflichtfelder vorhanden ist wird der Patient gespeichert*/

void Verwaltung::ueberpruefen()
{
    bool fehler = false;

    bool fehlerhafte_eingabe = false;

    //Fehlermeldung bezüglich ungülteger Eingabe
    if(ui->titel_lineEdit->text().contains("1")||ui->titel_lineEdit->text().contains("2")||ui->titel_lineEdit->text().contains("3")||ui->titel_lineEdit->text().contains("4")||ui->titel_lineEdit->text().contains("5")
            ||ui->titel_lineEdit->text().contains("6")||ui->titel_lineEdit->text().contains("7")||ui->titel_lineEdit->text().contains("8")||ui->titel_lineEdit->text().contains("9")||ui->titel_lineEdit->text().contains("0"))
    {
        fehlerhafte_eingabe = true;
    }

    if(ui->nachname_lineEdit->text().contains("1")||ui->nachname_lineEdit->text().contains("2")||ui->nachname_lineEdit->text().contains("3")||ui->nachname_lineEdit->text().contains("4")||ui->nachname_lineEdit->text().contains("5")
            ||ui->nachname_lineEdit->text().contains("6")||ui->nachname_lineEdit->text().contains("7")||ui->nachname_lineEdit->text().contains("8")||ui->nachname_lineEdit->text().contains("9")||ui->nachname_lineEdit->text().contains("0"))
    {
        fehlerhafte_eingabe = true;
    }

    if(ui->vorname_lineEdit->text().contains("1")||ui->vorname_lineEdit->text().contains("2")||ui->vorname_lineEdit->text().contains("3")||ui->vorname_lineEdit->text().contains("4")||ui->vorname_lineEdit->text().contains("5")
            ||ui->vorname_lineEdit->text().contains("6")||ui->vorname_lineEdit->text().contains("7")||ui->vorname_lineEdit->text().contains("8")||ui->vorname_lineEdit->text().contains("9")||ui->vorname_lineEdit->text().contains("0"))
    {
        fehlerhafte_eingabe = true;
    }

    if(ui->strasse_lineEdit->text().contains("1")||ui->strasse_lineEdit->text().contains("2")||ui->strasse_lineEdit->text().contains("3")||ui->strasse_lineEdit->text().contains("4")||ui->strasse_lineEdit->text().contains("5")
            ||ui->strasse_lineEdit->text().contains("6")||ui->strasse_lineEdit->text().contains("7")||ui->strasse_lineEdit->text().contains("8")||ui->strasse_lineEdit->text().contains("9")||ui->strasse_lineEdit->text().contains("0"))
    {
        fehlerhafte_eingabe = true;
    }

    if(ui->ort_lineEdit->text().contains("1")||ui->ort_lineEdit->text().contains("2")||ui->ort_lineEdit->text().contains("3")||ui->ort_lineEdit->text().contains("4")||ui->ort_lineEdit->text().contains("5")
            ||ui->ort_lineEdit->text().contains("6")||ui->ort_lineEdit->text().contains("7")||ui->ort_lineEdit->text().contains("8")||ui->ort_lineEdit->text().contains("9")||ui->ort_lineEdit->text().contains("0"))
    {
        fehlerhafte_eingabe = true;
    }

    //Fehlermeldungen für fehlende Eingaben

    if (ui->nachname_lineEdit->text().isEmpty())
    {
        //Fehlermeldung für keinen Nachnamen eingetragen
        QMessageBox fehlermeldung;
        fehlermeldung.critical(0, "Fehler", "Bitte tragen sie den Nachnamen ein");
        fehler = true;
    }

    if (ui->vorname_lineEdit->text().isEmpty())
    {
        //Fehlermeldung für keinen Vornamen eingetragen
        QMessageBox fehlermeldung;
        fehlermeldung.critical(0, "Fehler", "Bitte tragen sie den Vornamen ein");
        fehler = true;
    }


    if (ui->geschlecht_comboBox->currentText() == " ")
    {
        //Fehlermeldung für kein eingetragenes Geschlecht
        QMessageBox fehlermeldung;
        fehlermeldung.critical(0, "Fehler", "Bitte ein Geschlecht auswählen");
        fehler = true;
    }

    if (ui->tel_nr_lineEdit->text().isEmpty())
    {
        //Fehlermeldung für keine Telefonnummer eingetragen
        QMessageBox fehlermeldung;
        fehlermeldung.critical(0, "Fehler", "Bitte tragen sie die Telefonnummer ein");
        fehler = true;
    }

    if (ui->strasse_lineEdit->text().isEmpty())
    {
        //Fehlermeldung für keine Straße eingetragen
        QMessageBox fehlermeldung;
        fehlermeldung.critical(0, "Fehler", "Bitte tragen sie die Straße ein");
        fehler = true;
    }

    if (ui->hnr_lineEdit->text().isEmpty())
    {
        //Fehlermeldung für keine Hausnummer eingetragen
        QMessageBox fehlermeldung;
        fehlermeldung.critical(0, "Fehler", "Bitte tragen sie die Hausnummer ein");
        fehler = true;
    }

    if (ui->plz_lineEdit->text().isEmpty())
    {
        //Fehlermeldung für keine Postleitzahl eingetragen
        QMessageBox fehlermeldung;
        fehlermeldung.critical(0, "Fehler", "Bitte tragen sie die Postleitzahl ein");
        fehler = true;
    }

    if (ui->ort_lineEdit->text().isEmpty())
    {
        //Fehlermeldung für keinen Ort eingetragen
        QMessageBox fehlermeldung;
        fehlermeldung.critical(0, "Fehler", "Bitte tragen sie den Ort ein");
        fehler = true;
    }

    //Fehlermeldung falls die Postleitzahl kürzer als 5 ist
    if (ui->plz_lineEdit->text().length() != 5)
    {
        QMessageBox fehlermeldung;
        fehlermeldung.critical(0, "Fehler", "Die Postleitzahl hat weniger als 5 Ziffern.");
        fehler = true;
    }



    if(fehlerhafte_eingabe == true)
    {
        QMessageBox fehlermeldung;
        fehlermeldung.critical(0, "Fehler", "Ungültige Eingabe! Bitte überprüfen sie ihre Eingabe.");
        fehler = true;
    }
    if( fehler == false)
    {
        //wird erst bei gültigen und vollständigen Eingaben ausgeführt
        save();
    }
}

/*diese Funktion erstellt einen neuen Patienten mit den Eingaben des Benutzers. Wurde der Patient bearbeitet behält er seine id,
wenn er ein neues Patient ist, wird die höchste Patienten_Id herausgefunden, um eins erhöht und dem Patienten zugewiesen.
Dann wird der Patient im internen Speicher gespeichert mit dem Aufruf update_patient.*/

void Verwaltung::save()
{
    QString geschl;

    if (ui->geschlecht_comboBox->currentText() == "w")
    {
        geschl = "weiblich";
    }
    if (ui->geschlecht_comboBox->currentText() == "m")
    {
        geschl = "männlich";
    }
    if (ui->geschlecht_comboBox->currentText() == "d")
    {
        geschl = "divers";
    }

    Patient* patient = new Patient(ui->titel_lineEdit->text(),ui->nachname_lineEdit->text(), ui->vorname_lineEdit->text(), ui->strasse_lineEdit->text(),
                                   ui->ort_lineEdit->text(), ui->hnr_lineEdit->text().toInt(),ui->plz_lineEdit->text().toInt(),0,ui->geb_dateEdit->date(),
                                   ui->tel_nr_lineEdit->text(),geschl);

    Speicher& data = Speicher::getInstance();

    if (id == 0)
    {
        int hoechste_Id = 0;

        if (data.get_alle_patienten().count() >=1)
        {
            for (Patient* patient : data.get_alle_patienten()) {
                if (patient->get_patient_id() > hoechste_Id) {
                    hoechste_Id = patient->get_patient_id();
                }
            }
        }
        patient->set_patient_id(hoechste_Id + 1);
    }
    else
    {
        patient->set_patient_id(id);
    }

    data.update_patient(patient);
    QDialog::close();
}

/*Der Funktion patienten_editieren wird die patienten_id übergeben. Mit der id kann der genaue patient identifiziert werden.
Passend zu dem Patient werden die vorhandenen Felder ausgefüllt.*/

void Verwaltung::patienten_editieren(int patienten_id)
{
    Patient* patient = Speicher::getInstance().get_patient(patienten_id);
    ui->titel_lineEdit->setText(patient->get_titel());
    ui->nachname_lineEdit->setText(patient->get_nachname());
    ui->vorname_lineEdit->setText(patient->get_vorname());
    ui->ort_lineEdit->setText(patient->get_ort());
    ui->strasse_lineEdit->setText(patient->get_strasse());
    ui->hnr_lineEdit->setText(QString::number(patient->get_hnr()));
    ui->plz_lineEdit->setText(QString::number(patient->get_plz()));
    ui->tel_nr_lineEdit->setText(patient->get_tel());
    ui->geb_dateEdit->setDate(patient->get_geburtstag());

    QString geschlecht = patient->get_geschlecht();
    if (geschlecht == "weiblich")
    {
        ui->geschlecht_comboBox->setCurrentIndex(2);
    }
    else if (geschlecht == "männlich")
    {
        ui->geschlecht_comboBox->setCurrentIndex(3);
    }
    else if (geschlecht == "divers") {
        ui->geschlecht_comboBox->setCurrentIndex(4);
    }
    id = patienten_id;
}

//sobald die Eingabe des Geburtsdatums ändert wird die Funktion change aufgerufen.

void Verwaltung::datechange(QDate)
{
    change();
}

//sobald die Eingabe des Geschlechts ändert wird die Funktion change aufgerufen.

void Verwaltung::textchange(QString)
{
    change();
}

/*Diese Funktion wird aufgerufen sobald sich eine der Eingaben verändert. Die aktuellen Eingaben werden dynamisch zur Eingabe rechts
in dem Fenster angezeigt, dies soll die Überprüfung der eingegebenen Daten erleichtern. Neben dem Geburtsdatum steht in Klammern das Alter des Patienten.*/

void Verwaltung::change()
{
    QString title = ui->titel_lineEdit->text();
    QString lastname = ui->nachname_lineEdit->text();
    QString firstname = ui->vorname_lineEdit->text();
    QString place = ui->ort_lineEdit->text();
    QString street = ui->strasse_lineEdit->text();
    int housenumber = ui->hnr_lineEdit->text().toInt();
    int region_code = ui->plz_lineEdit->text().toInt();
    QString phone = ui->tel_nr_lineEdit->text();
    QString sex = ui->geschlecht_comboBox->currentText();
    QDate geb = ui->geb_dateEdit->date();
    QString hnr = " ";
    QString regc = " ";
    QString geschl = " ";
    if (sex == "w")
    {
        geschl = "weiblich";
    }
    if (sex == "m")
    {
        geschl = "männlich";
    }
    if (sex == "d")
    {
        geschl = "divers";
    }
    if (housenumber != 0)
    {
        hnr = QString::number(housenumber);
    }
    if (region_code != 0)
    {
        regc = QString::number(region_code);
    }
    //Alters-Berechnung
    QString birthday = geb.toString("yyyy.MM.dd");
    int birth_year = geb.year();
    QString geburtsjahr = QString::number(birth_year);
    int birth_month = geb.month();
    QString geburtsmonat = QString::number(birth_month);
    int birth_day = geb.day();
    QString geburtstag = QString::number(birth_day);
    int current_year = QDate::currentDate().year();
    int current_month = QDate::currentDate().month();
    int current_day = QDate::currentDate().day();

    int jahr = current_year - birth_year;
    int monat = current_month - birth_month;
    int tag = current_day - birth_day;
    int alter = jahr;

    if(monat < 0 || (monat == 0 && tag < 0))
    {
        alter = alter - 1;
    }
    QString age = QString::number(alter);
    ui->eingaben->setText(title +" "+ firstname +" "+ lastname +"\n"+ birthday +"("+ age +") \n"+ geschl +"\n"+ street +" "+ hnr +"\n"+ regc +" "+ place +"\n"+ phone);
}


// Der Destruktor der Klasse Verwaltung.

Verwaltung::~Verwaltung()
{
    delete ui;
}
