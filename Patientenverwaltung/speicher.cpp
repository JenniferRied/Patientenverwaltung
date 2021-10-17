#include "speicher.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

Speicher& Speicher::getInstance()
{
    static Speicher instance;
    return instance;
}

void Speicher::beobachter_anhaengen(Beobachter *beobachter)
{
    if (!beobachter_patient_update.contains(beobachter))
    {
        beobachter_patient_update.append(beobachter);
    }
}

void Speicher::beobachter_abmachen(Beobachter *beobachter)
{
    if (beobachter_patient_update.contains(beobachter))
    {
        beobachter_patient_update.removeOne(beobachter);
    }
}

Patient* Speicher::get_patient(int id)
{
    return new Patient(*patienten[id]);
}

QList<Patient *> Speicher::get_alle_patienten()
{
    return patienten.values();
}

void Speicher::update_patient(Patient *patient)
{
    if (patienten.contains(patient->get_patient_id()) && patient != patienten[patient->get_patient_id()])
    {
        delete patienten[patient->get_patient_id()];
    }

    patienten[patient->get_patient_id()] = patient;
    daten_speichern();

    patientenaenderung_melden();
}


void Speicher::loesche_patient(int id)
{
    if (patienten.contains(id))
    {
        delete patienten[id];
        patienten.remove(id);
    }
    daten_speichern();
    patientenaenderung_melden();
}

Speicher::Speicher()
{
    daten_laden();
}

Speicher::~Speicher()
{
    foreach (Patient* pat, patienten)
    {
        delete pat;
    }
    patienten.clear();
}

void Speicher::daten_laden()
{
    QFile patienten_datei("Patienten.json");

    if (!patienten_datei.open(QIODevice::ReadOnly))
    {
        return;
    }

    QJsonObject json = QJsonDocument::fromJson(patienten_datei.readAll()).object();

    if (json.contains("patienten"))
    {
        QJsonArray jsonPatients = json["patienten"].toArray();

        for (int patienten_index = 0; patienten_index < jsonPatients.size(); patienten_index++)
        {
            Patient* patient = Patient::read(jsonPatients[patienten_index].toObject());
            if (!patienten.contains(patient->get_patient_id()))
            {
                patienten[patient->get_patient_id()] = patient;
            }
        }
    }
}

void Speicher::daten_speichern()
{
    QFile patienten_datei("Patienten.json");

    if (!patienten_datei.open(QIODevice::WriteOnly))
    {
        return;
    }

    QJsonArray json_patienten;
    for (Patient* patient : patienten.values())
    {
        QJsonObject json_patient;
        patient->write(json_patient);
        json_patienten.append(json_patient);
    }

    QJsonObject json;
    json["patienten"] = json_patienten;
    patienten_datei.write(QJsonDocument(json).toJson(QJsonDocument::Indented));
}

void Speicher::patientenaenderung_melden()
{
    for (Beobachter* beobachter : beobachter_patient_update)
    {
        beobachter->patient_updated();
    }
}
