#include "patient.h"
#include <QList>
#include "speicher.h"
#include <QMessageBox>
#include <QString>

Patient::Patient(QString titel,
                 QString nachname,
                 QString vorname,
                 QString strasse,
                 QString ort,
                 QString tel,
                 int hnr,
                 int plz,
                 int patient_id,
                 QString geschlecht)
{
    QList<Patient> patienten;
}

void Patient::save_patient()
{
       Speicher* speicher = Speicher::getInstance();
       speicher->set_patientenliste(*this);

       //zum Debbugen
       QMessageBox msgBox;
       QString string = QString::number(speicher->number_Patient());
       msgBox.setText(string);
       msgBox.exec();
}
