#include "verwaltung.h"
#include "ui_verwaltung.h"
#include "patient.h"
#include <list>

Verwaltung::Verwaltung(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Verwaltung)
{
    ui->setupUi(this);
    title = ui->titel_textEdit->toPlainText();
    lastname = ui->nachname_textEdit->toPlainText();
    firstname = ui->vorname_textEdit->toPlainText();
    place = ui->ort_textEdit->toPlainText();
    street = ui->strasse_textEdit->toPlainText();
    housenumber = ui->hnr_textEdit->toPlainText().toInt();
    region_code = ui->plz_textEdit->toPlainText().toInt();
    phone = ui->tel_nr_textEdit->toPlainText().toInt();

    //sex = ui->geschlecht_comboBox;
    connect(ui->buttonBox,SIGNAL (accepted()),this, SLOT (save()));
    connect(ui->pushButton, SIGNAL (clicked()), this , SLOT (control()));
}
void Verwaltung::save()
{
    //Patient::set_titel(title);
}

void Verwaltung::control()
{
    title = ui->nachname_textEdit->toPlainText();
    ui->kontrollausgabe->setText(title);
}

Verwaltung::~Verwaltung()
{
    delete ui;
}
