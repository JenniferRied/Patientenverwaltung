#include "verwaltung.h"
#include "ui_verwaltung.h"
#include "patient.h"
#include "speicher.h"
#include <list>
#include <QMessageBox>

Verwaltung::Verwaltung(int patienten_id, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Verwaltung)
{
    ui->setupUi(this);

    QList<QString> geschlecht;
    geschlecht.append(" ");
    geschlecht.append("w");
    geschlecht.append("m");
    geschlecht.append("d");
    ui->geschlecht_comboBox->addItems(geschlecht);

    if (patienten_id > 0) {
        setWindowTitle("Patient editieren");
        patienten_editieren(patienten_id);
    } else {
        setWindowTitle("Neuer Patient");
    }

    connect(ui->geb_dateEdit, SIGNAL (dateChanged(QDate)), this, SLOT (datechange(QDate)));
    connect(ui->titel_textEdit, SIGNAL (textChanged()), this , SLOT (change()));
    connect(ui->nachname_textEdit, SIGNAL (textChanged()), this , SLOT (change()));
    connect(ui->vorname_textEdit, SIGNAL (textChanged()), this , SLOT (change()));
    connect(ui->ort_textEdit, SIGNAL (textChanged()), this , SLOT (change()));
    connect(ui->strasse_textEdit, SIGNAL (textChanged()), this , SLOT (change()));
    connect(ui->hnr_textEdit, SIGNAL (textChanged()), this , SLOT (change()));
    connect(ui->plz_textEdit, SIGNAL (textChanged()), this , SLOT (change()));
    connect(ui->tel_nr_textEdit, SIGNAL (textChanged()), this , SLOT (change()));
    connect(ui->geschlecht_comboBox, SIGNAL (currentTextChanged(QString)), this, SLOT (textchange(QString)));
    connect(ui->speichern_button,SIGNAL (clicked()),this, SLOT (ueberpruefen()));
    connect(ui->abbrechen_button, SIGNAL (clicked()), this, SLOT(abgebrochen()));
}

void Verwaltung::abgebrochen()
{
    QDialog::close();
}

void Verwaltung::ueberpruefen()
{
    bool fehler = false;
    if (ui->nachname_textEdit->toPlainText().isEmpty())
    {
        //Fehlermeldung für keinen Nachnamen eingetragen
        QMessageBox fehlermeldung;
        fehlermeldung.critical(0, "Fehler", "Bitte tragen sie den Nachnamen ein");
        fehler = true;
    }

    if (ui->vorname_textEdit->toPlainText().isEmpty())
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

    if (ui->tel_nr_textEdit->toPlainText().isEmpty())
    {
        //Fehlermeldung für keine Telefonnummer eingetragen
        QMessageBox fehlermeldung;
        fehlermeldung.critical(0, "Fehler", "Bitte tragen sie die Telefonnummer ein");
        fehler = true;
    }

    if (ui->strasse_textEdit->toPlainText().isEmpty())
    {
        //Fehlermeldung für keine Straße eingetragen
        QMessageBox fehlermeldung;
        fehlermeldung.critical(0, "Fehler", "Bitte tragen sie die Straße ein");
        fehler = true;
    }

    if (ui->hnr_textEdit->toPlainText().isEmpty())
    {
        //Fehlermeldung für keine Hausnummer eingetragen
        QMessageBox fehlermeldung;
        fehlermeldung.critical(0, "Fehler", "Bitte tragen sie die Hausnummer ein");
        fehler = true;
    }

    if (ui->plz_textEdit->toPlainText().isEmpty())
    {
        //Fehlermeldung für keine Postleitzahl eingetragen
        QMessageBox fehlermeldung;
        fehlermeldung.critical(0, "Fehler", "Bitte tragen sie die Postleitzahl ein");
        fehler = true;
    }

    if (ui->ort_textEdit->toPlainText().isEmpty())
    {
        //Fehlermeldung für keinen Ort eingetragen
        QMessageBox fehlermeldung;
        fehlermeldung.critical(0, "Fehler", "Bitte tragen sie den Ort ein");
        fehler = true;
    }

    if( fehler == false)
    {
        save();
    }
}

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

    Patient* patient = new Patient(ui->titel_textEdit->toPlainText(),ui->nachname_textEdit->toPlainText(), ui->vorname_textEdit->toPlainText(), ui->strasse_textEdit->toPlainText(),
                                   ui->ort_textEdit->toPlainText(), ui->hnr_textEdit->toPlainText().toInt(),ui->plz_textEdit->toPlainText().toInt(),0,ui->geb_dateEdit->date(),
                                   ui->tel_nr_textEdit->toPlainText(),geschl);

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

void Verwaltung::patienten_editieren(int patienten_id)
{
    Patient* patient = Speicher::getInstance().get_patient(patienten_id);
    ui->titel_textEdit->setText(patient->get_titel());
    ui->nachname_textEdit->setText(patient->get_nachname());
    ui->vorname_textEdit->setText(patient->get_vorname());
    ui->ort_textEdit->setText(patient->get_ort());
    ui->strasse_textEdit->setText(patient->get_strasse());
    ui->hnr_textEdit->setText(QString::number(patient->get_hnr()));
    ui->plz_textEdit->setText(QString::number(patient->get_plz()));
    ui->tel_nr_textEdit->setText(patient->get_tel());
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

void Verwaltung::datechange(QDate)
{
    change();
}

void Verwaltung::textchange(QString)
{
    change();
}

void Verwaltung::change()
{
    QString title = ui->titel_textEdit->toPlainText();
    QString lastname = ui->nachname_textEdit->toPlainText();
    QString firstname = ui->vorname_textEdit->toPlainText();
    QString place = ui->ort_textEdit->toPlainText();
    QString street = ui->strasse_textEdit->toPlainText();
    int housenumber = ui->hnr_textEdit->toPlainText().toInt();
    int region_code = ui->plz_textEdit->toPlainText().toInt();
    QString phone = ui->tel_nr_textEdit->toPlainText();
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



Verwaltung::~Verwaltung()
{
    delete ui;
}
