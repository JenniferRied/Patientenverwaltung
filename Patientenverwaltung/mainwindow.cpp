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

       //if(ui->pushButton->clicked())
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

