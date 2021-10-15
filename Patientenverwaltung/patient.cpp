#include "patient.h"
#include <QList>
#include "speicher.h"
#include <QMessageBox>
#include <QString>

Patient::Patient(QString titel, QString nachname, QString vorname,
                 QString strasse, QString ort, int hnr, int plz,
                 int patient_id, QString tel, QString geschlecht)
    :titel(titel),nachname(nachname),vorname(vorname),
    strasse(strasse),ort(ort),hnr(hnr),plz(plz),
    patient_id(patient_id), tel(tel), geschlecht(geschlecht)
{

}
