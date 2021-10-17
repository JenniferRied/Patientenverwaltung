#include "patient.h"
#include <QList>
#include "speicher.h"
#include <QMessageBox>
#include <QString>

Patient::Patient(QString titel, QString nachname, QString vorname,
                 QString strasse, QString ort, int hnr, int plz,
                 int patient_id, QDate geb, QString tel, QString geschlecht)
    :titel(titel),nachname(nachname),vorname(vorname),
    strasse(strasse),ort(ort),hnr(hnr),plz(plz),
    patient_id(patient_id), geb(geb), tel(tel), geschlecht(geschlecht)
{

}

Patient* Patient::read(const QJsonObject &json)
{
    Patient* patient = new Patient();

    if (json.contains("titel") && json["titel"].isString())
    {
        patient->set_titel(json["titel"].toString());
    }

    if (json.contains("nachname") && json["nachname"].isString())
    {
        patient->set_nachname(json["nachname"].toString());
    }

    if (json.contains("vorname") && json["vorname"].isString())
    {
        patient->set_vorname(json["vorname"].toString());
    }

    if (json.contains("strasse") && json["strasse"].isString())
    {
        patient->set_strasse(json["strasse"].toString());
    }

    if (json.contains("ort") && json["ort"].isString())
    {
        patient->set_ort(json["ort"].toString());
    }

    if (json.contains("tel") && json["tel"].isString())
    {
        patient->set_tel(json["tel"].toString());
    }

    if (json.contains("hnr") && json["hnr"].isDouble())
    {
        patient->set_hnr(json["hnr"].toInt());
    }

    if (json.contains("plz") && json["plz"].isDouble())
    {
        patient->set_plz(json["plz"].toInt());
    }

    if (json.contains("id") && json["id"].isDouble())
    {
        patient->set_patient_id(json["id"].toInt());
    }

    if (json.contains("geb") && json["geb"].isString())
    {
        QDate datum = QDate::fromString(json["geb"].toString(), "dd.MM.yyyy");
        patient->set_geburtstag(datum);
    }

    if (json.contains("geschlecht") && json["geschlecht"].isString()) {
        patient->set_geschlecht(json["geschlecht"].toString());
    }

    return patient;
}

void Patient::write(QJsonObject &json) const
{
    json["titel"] = titel;
    json["nachname"] = nachname;
    json["vorname"] = vorname;
    json["strasse"] = strasse;
    json["ort"] = ort;
    json["tel"] = tel;
    json["hnr"] = hnr;
    json["plz"] = plz;
    json["id"] = patient_id;
    json["geb"] = geb.toString("dd.MM.yyyy");
    json["geschlecht"] = geschlecht;
}
