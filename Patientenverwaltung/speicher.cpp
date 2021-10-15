#include "speicher.h"

Speicher& Speicher::getInstance()
{
    static Speicher instance;
    return instance;
}

void Speicher::beobachter_anhaengen(Beobachter *beobachter)
{
    if (!beobachter_patient_update.contains(beobachter)) {
        beobachter_patient_update.append(beobachter);
    }
}

void Speicher::beobachter_abmachen(Beobachter *beobachter)
{
    if (beobachter_patient_update.contains(beobachter)) {
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
    if (patienten.contains(patient->get_patient_id()) && patient != patienten[patient->get_patient_id()]) {
        delete patienten[patient->get_patient_id()];
    }

    patienten[patient->get_patient_id()] = patient;
    daten_speichern();

    patientenaenderung_melden();
}


void Speicher::loesche_patient(int id)
{
    if (patienten.contains(id)) {
        delete patienten[id];
        patienten.remove(id);
    }
    daten_speichern();
    patientenaenderung_melden();
}

Speicher::Speicher()
{
    daten_speichern();
}

Speicher::~Speicher()
{
    foreach (Patient* pat, patienten) {
        delete pat;
    }
    patienten.clear();
}

void Speicher::daten_laden()
{

}

void Speicher::daten_speichern()
{

}

void Speicher::patientenaenderung_melden()
{
    for (Beobachter* beobachter : beobachter_patient_update) {
        beobachter->patient_updated();
    }
}
