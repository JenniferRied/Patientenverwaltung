#include "verwaltung.h"
#include "ui_verwaltung.h"

Verwaltung::Verwaltung(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Verwaltung)
{
    ui->setupUi(this);
}

Verwaltung::~Verwaltung()
{
    delete ui;
}
