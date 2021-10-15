#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "verwaltung.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->pushButton->clicked();

    connect(ui->pushButton, SIGNAL (clicked()),this, SLOT (buttonclick()));

    Speicher::getInstance().beobachter_anhaengen(this);
}
void MainWindow::buttonclick()
{
    Verwaltung *verw = new Verwaltung();
    verw->show();
}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::patient_updated()
{
    //tabelle neu laden, da in liste der Patienten eine Änderung passiert ist
    //sinnvollsten nur funktionsaufruf der Tabellenerstellung
}
