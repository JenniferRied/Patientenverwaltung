#include "verwaltung.h"
#include "ui_verwaltung.h"
#include "patient.h"

Verwaltung::Verwaltung(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Verwaltung)
{
    ui->setupUi(this);
    std::string title;
    title = ui->titel_textEdit->toPlainText().toStdString();
    //Patient::set_titel(title);

}


Verwaltung::~Verwaltung()
{
    delete ui;
}
