#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "verwaltung.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->hinzufuegen_button, SIGNAL (clicked()),this, SLOT (hinzufuegen_buttonclick()));
    connect(ui->aendern_button, SIGNAL (clicked()),this, SLOT (aendern_buttonclick()));
    connect(ui->loeschen_button, SIGNAL (clicked()),this, SLOT (loeschen_buttonclick()));
    connect(ui->suchen_button, SIGNAL (clicked()),this, SLOT (suchen_buttonclick()));

    //Icons

    QIcon hinzufuegen;
    //https://www.clipartmax.com/download/m2i8m2Z5K9Z5N4d3_plus-icons-no-attribution-add-icon-green/
    hinzufuegen.addFile("/home/dbuser/Dokumente/Patientenverwaltung/Patientenverwaltung/clipart1719902.png");
    QIcon loeschen;
    //https://www.clipartmax.com/download/m2i8b1N4m2N4m2b1_trash-can-clip-art/
    loeschen.addFile("/home/dbuser/Dokumente/Patientenverwaltung/Patientenverwaltung/clipart1976610.png");
    QIcon aendern;
    //https://www.clipartmax.com/download/m2i8i8G6i8G6K9i8_pencil-and-paper-clipart-school-pencil-clip-art/
    aendern.addFile("/home/dbuser/Dokumente/Patientenverwaltung/Patientenverwaltung/clipart209647.png");
    QIcon suche;
    //https://www.clipartmax.com/download/m2K9A0b1m2d3G6K9_clipart-magnifying-glass-black-clipart/
    suche.addFile("/home/dbuser/Dokumente/Patientenverwaltung/Patientenverwaltung/clipart28741.png");
    QSize iconSize;
    iconSize.setWidth(60);
    iconSize.setHeight(60);
    ui->hinzufuegen_button->setIcon(hinzufuegen);
    ui->loeschen_button->setIcon(loeschen);
    ui->loeschen_button->setIconSize(iconSize);
    ui->aendern_button->setIcon(aendern);
    ui->aendern_button->setIconSize(iconSize);
    ui->suchen_button->setIcon(suche);
    ui->suchen_button->setIconSize(iconSize);


    Speicher::getInstance().beobachter_anhaengen(this);
}

void MainWindow::hinzufuegen_buttonclick()
{
    Verwaltung *verw = new Verwaltung();
    verw->show();
}

void MainWindow::aendern_buttonclick()
{
    Verwaltung *verw = new Verwaltung();
    verw->show();
}

void MainWindow::loeschen_buttonclick()
{

}

void MainWindow::suchen_buttonclick()
{

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
