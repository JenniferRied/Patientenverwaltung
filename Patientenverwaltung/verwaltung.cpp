#include "verwaltung.h"
#include "ui_verwaltung.h"
#include "patient.h"

Verwaltung::Verwaltung(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Verwaltung)
{
    ui->setupUi(this);
    title = ui->titel_textEdit->toPlainText().toStdString();
    lastname = ui->titel_textEdit->toPlainText().toStdString();
    firstname = ui->titel_textEdit->toPlainText().toStdString();
    place = ui->titel_textEdit->toPlainText().toStdString();
    //Patient::set_titel(title);

}


Verwaltung::~Verwaltung()
{
    delete ui;
}
