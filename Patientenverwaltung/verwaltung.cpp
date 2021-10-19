#include "verwaltung.h"
#include "ui_verwaltung.h"
#include "patient.h"
#include "speicher.h"
#include <list>

Verwaltung::Verwaltung(QWidget *parent) :
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
    patient = new Patient(ui->titel_textEdit->toPlainText(),ui->nachname_textEdit->toPlainText(), ui->vorname_textEdit->toPlainText(), ui->strasse_textEdit->toPlainText(),
                          ui->ort_textEdit->toPlainText(), ui->hnr_textEdit->toPlainText().toInt(),ui->plz_textEdit->toPlainText().toInt(),1,ui->geb_dateEdit->date(),ui->tel_nr_textEdit->toPlainText(),"weiblich");
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
