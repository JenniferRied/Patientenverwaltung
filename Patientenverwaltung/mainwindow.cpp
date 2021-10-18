#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "verwaltung.h"

#include<QTableWidget>
#include<QTableWidgetItem>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->hinzufuegen_button, SIGNAL (clicked()),this, SLOT (hinzufuegen_buttonclick()));
    connect(ui->aendern_button, SIGNAL (clicked()),this, SLOT (aendern_buttonclick()));
    connect(ui->loeschen_button, SIGNAL (clicked()),this, SLOT (loeschen_buttonclick()));
    connect(ui->suchen_button, SIGNAL (clicked()),this, SLOT (suchen_buttonclick()));
    connect(ui->export_button, SIGNAL (clicked()),this, SLOT (export_buttonclick()));

    //Icons

    //https://www.clipartmax.com/download/m2i8m2Z5K9Z5N4d3_plus-icons-no-attribution-add-icon-green/
    QIcon* hinzufuegen = new QIcon(":/Bilder/clipart1719902.png");
    //https://www.clipartmax.com/download/m2i8b1N4m2N4m2b1_trash-can-clip-art/
    QIcon* loeschen = new QIcon(":/Bilder/clipart1976610.png");
    //https://www.clipartmax.com/download/m2i8i8G6i8G6K9i8_pencil-and-paper-clipart-school-pencil-clip-art/
    QIcon* aendern = new QIcon(":/Bilder/clipart209647.png");
    //https://www.clipartmax.com/download/m2K9A0b1m2d3G6K9_clipart-magnifying-glass-black-clipart/
    QIcon* suche = new QIcon(":/Bilder/clipart28741.png");
    //https://www.clipartmax.com/download/m2i8H7m2G6d3A0N4_email-free-clip-art-envelope-clipart-transparent-background/
    QIcon* export_icon = new QIcon(":/Bilder/clipart611030.png");

    QSize iconSize;
    iconSize.setWidth(60);
    iconSize.setHeight(60);

    ui->hinzufuegen_button->setIcon(*hinzufuegen);
    ui->loeschen_button->setIcon(*loeschen);
    ui->loeschen_button->setIconSize(iconSize);
    ui->aendern_button->setIcon(*aendern);
    ui->aendern_button->setIconSize(iconSize);
    ui->suchen_button->setIcon(*suche);
    ui->suchen_button->setIconSize(iconSize);
    ui->export_button->setIcon(*export_icon);
    ui->export_button->setIconSize(iconSize);


    Speicher::getInstance().beobachter_anhaengen(this);



    //Patientenliste



    ui->tableWidget->setColumnCount(4); //Anzahl Spalten
    ui->tableWidget->horizontalHeader()->setDefaultSectionSize(111);  //Breite der Spalten

    QTableWidgetItem *header1 = new QTableWidgetItem();
    header1->setText("Titel");
    ui->tableWidget->setHorizontalHeaderItem(0,header1);
    QTableWidgetItem *header2 = new QTableWidgetItem();
    header2->setText("Vorname");
    ui->tableWidget->setHorizontalHeaderItem(1,header2);
    QTableWidgetItem *header3 = new QTableWidgetItem();
    header3->setText("Nachname");
    ui->tableWidget->setHorizontalHeaderItem(2,header3);
    QTableWidgetItem *header4 = new QTableWidgetItem();
    header4->setText("Geburtsdatum");
    ui->tableWidget->setHorizontalHeaderItem(3,header4);


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

void MainWindow::export_buttonclick()
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

void MainWindow::on_pushButton_clicked()
{
    int row_count = 0;

    ui->tableWidget->setRowCount(row_count);

    QList<Patient*> patienten = Speicher::getInstance().get_alle_patienten();


    for (int patienten_nr = 0; patienten_nr < patienten.size(); patienten_nr++){

    row_count++;
    ui->tableWidget->setRowCount(row_count);
    Patient* patient = patienten[patienten_nr];

    QTableWidgetItem *new_titel = new QTableWidgetItem(patient->get_titel());
    ui->tableWidget->setItem(patienten_nr,0,new_titel);
    QTableWidgetItem *new_vorname = new QTableWidgetItem(patient->get_vorname());
    ui->tableWidget->setItem(patienten_nr,1,new_vorname);
    QTableWidgetItem *new_nachname = new QTableWidgetItem(patient->get_nachname());
    ui->tableWidget->setItem(patienten_nr,2,new_nachname);

    //Datumausgabe hinzufügen
    //QTableWidgetItem *new_geb = new QTableWidgetItem(patient->get_geburtstag());
    //ui->tableWidget->setItem(patienten_nr,3,new_geb);
    }
}
