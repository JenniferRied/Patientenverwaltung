#include "verwaltung.h"
#include "ui_verwaltung.h"
#include "patient.h"

Verwaltung::Verwaltung(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Verwaltung)
{
    ui->setupUi(this);
    title = ui->titel_textEdit->toPlainText().toStdString();
    lastname = ui->nachname_textEdit->toPlainText().toStdString();
    firstname = ui->vorname_textEdit->toPlainText().toStdString();
    place = ui->ort_textEdit->toPlainText().toStdString();
    street = ui->strasse_textEdit->toPlainText().toStdString();
    housenumber = ui->hnr_textEdit->toPlainText().toInt();
    region_code = ui->plz_textEdit->toPlainText().toInt();
    //sex = ui->geschlecht_comboBox;
    connect(ui->buttonBox,SIGNAL (accepted()),this, SLOT (save()));
}

void Verwaltung::save()
{
    //Patient::set_titel(title);
}


Verwaltung::~Verwaltung()
{
    delete ui;
}
