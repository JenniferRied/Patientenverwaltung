#include "verwaltung.h"
#include "ui_verwaltung.h"
#include "patient.h"
#include "speicher.h"
#include <list>

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

    if (patienten_id > 0)
    {
        patienten_editieren(patienten_id);
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
    connect(ui->buttonBox,SIGNAL (accepted()),this, SLOT (save()));
}
void Verwaltung::save()
{
    Patient* patient = new Patient(ui->titel_textEdit->toPlainText(),ui->nachname_textEdit->toPlainText(), ui->vorname_textEdit->toPlainText(), ui->strasse_textEdit->toPlainText(),
                          ui->ort_textEdit->toPlainText(), ui->hnr_textEdit->toPlainText().toInt(),ui->plz_textEdit->toPlainText().toInt(),0,ui->geb_dateEdit->date(),ui->tel_nr_textEdit->toPlainText(),"weiblich");
    Speicher& data = Speicher::getInstance();

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

    data.update_patient(patient);
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
    zum_editieren = true;
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
    title = ui->titel_textEdit->toPlainText();
    lastname = ui->nachname_textEdit->toPlainText();
    firstname = ui->vorname_textEdit->toPlainText();
    place = ui->ort_textEdit->toPlainText();
    street = ui->strasse_textEdit->toPlainText();
    housenumber = ui->hnr_textEdit->toPlainText().toInt();
    region_code = ui->plz_textEdit->toPlainText().toInt();
    phone = ui->tel_nr_textEdit->toPlainText();
    sex = ui->geschlecht_comboBox->currentText();
    geb = ui->geb_dateEdit->date();
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
    QString birthday = geb.toString("dd.MM.yyyy");
    int birth_year = geb.year();
    int current_year = QDate::currentDate().year();
    int alter = current_year - birth_year;
    QString age = QString::number(alter);
    ui->eingaben->setText(title +" "+ firstname +" "+ lastname +"\n"+ birthday +"("+ age +") \n"+ geschl +"\n"+ street +" "+ hnr +"\n"+ regc +" "+ place +"\n"+ phone);
}



Verwaltung::~Verwaltung()
{
    delete ui;
}
