#ifndef SPEICHER_H
#define SPEICHER_H

#include <QList>
#include <QMap>
#include "patient.h"

class Beobachter {
public:
    virtual ~Beobachter()= default;
    virtual void patient_updated() = 0;
};

class Speicher
{
public:
    static Speicher& getInstance();

    void beobachter_anhaengen(Beobachter* beobachter);
    void beobachter_abmachen(Beobachter* beobachter);

    //get und set der Patienten Liste
    Patient* get_patient(int id);
    QList<Patient*> get_alle_patienten();
    void update_patient(Patient* patient);
    void loesche_patient(int id);

    QJsonObject json_erstellen(QList<Patient*> patienten);
    
private:
    Speicher();
    virtual ~Speicher();

    void daten_laden();
    void daten_speichern();

    void patientenaenderung_melden();

    QMap<int, Patient*> patienten;
    QList<Beobachter*> beobachter_patient_update;
};

#endif // SPEICHER_H
