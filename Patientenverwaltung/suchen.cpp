#include "suchen.h"
#include "patient.h"
#include "speicher.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLabel>
#include <QMessageBox>
#include <QGridLayout>


Suchen::Suchen(QWidget *parent)
    : QDialog(parent)

{
    QLabel *findLabel = new QLabel(tr("Hier nach Patienten suchen:"));
    suchleiste = new QLineEdit;

    button = new QPushButton(tr("&Suchen"));
    suchen_text = "";

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(findLabel, 0, 0);
    layout->addWidget(suchleiste, 0, 1);
    layout->addWidget(button, 0, 2);

    setLayout(layout);
    setWindowTitle(tr("Suchen eines Patienten"));
    connect(button, SIGNAL(clicked()), this, SLOT(button_gedrueckt()));
    connect(button, SIGNAL(clicked()), this, SLOT(accept()));

}

void Suchen::button_gedrueckt()
{
    QString text = suchleiste->text();

    if (text.isEmpty()) {                                               //If-Abfrage prüft, ob ein Name eingegeben wurde, falls nicht kommt eine Meldung
        QMessageBox::information(this, tr("Leeres Feld"),               //Verstecken der nicht gesuchten Einträge steht bei suchen_buttonClick in mainwindow.cpp
                                 tr("Bitte einen Namen eingeben"));
        return;
    } else {
        suchen_text = text;
        suchleiste->clear();
        hide();
    }
}

QString Suchen::get_suchen_text()
{
    return suchen_text;
}
