#include "speicher.h"
#include <QFile>
#include <QFileInfo>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QMessageBox>
#include <QErrorMessage>

/*Diese Funktion übergibt die eine Instance der Speicherung dem Aufrufer zurück.
Es gibt nur eine Instance, da Singelton-Pattern verwendet.*/

Speicher& Speicher::getInstance()
{
    static Speicher instance;
    return instance;
}

/*Fügt den übergebenen Beobachter der Liste der Beobachter hinzu(Observer).*/

void Speicher::beobachter_anhaengen(Beobachter *beobachter)
{
    if (!beobachter_patient_update.contains(beobachter))
    {
        beobachter_patient_update.append(beobachter);
    }
}

/*Die Funktion entfernt den übergebenen Beobachter aus der Liste der Beobachter(Observer).*/

void Speicher::beobachter_abmachen(Beobachter *beobachter)
{
    if (beobachter_patient_update.contains(beobachter))
    {
        beobachter_patient_update.removeOne(beobachter);
    }
}

/*Diese Funktion gibt den Patienten, der zu der übergebenen Id gehört, dem Aufrufer zurück.*/

Patient* Speicher::get_patient(int id)
{
    return new Patient(*patienten[id]);
}

/*Übergebt alle in der internen Speicherung vorhandenen Patienten an den Aufrufer zurück.*/

QList<Patient *> Speicher::get_alle_patienten()
{
    return patienten.values();
}

/*Der übergebene Patient wird in die interne Speicherung(QMap) aufgenommen, dabei ist der Key die ID und der Value ist der Patient.*/

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

/*Der Patient mit der übergebenen id wird aus dem internen Speicher(QMap) gelöscht.*/

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

/*Der Konstruktor der Klasse. Sorgt für das Laden der Daten bei Programmstart.*/

Speicher::Speicher()
{
    daten_laden();
}

/*Der Destruktor der Klasse. Der interne Speicher wird gelöscht. Wird bei Beendigung des Programm aufgerufen.*/

Speicher::~Speicher()
{
    foreach (Patient* pat, patienten)
    {
        delete pat;
    }
    patienten.clear();
}

/*Diese Funktion lädt aus der json-Datei die Patienten in die interne Speicherung(QMap).*/

void Speicher::daten_laden()
{
    QString dateiname = "Patienten.json";
    QFileInfo datei(dateiname);

    if (datei.exists())
    {
        QFile patienten_datei(dateiname);

        if (!patienten_datei.open(QIODevice::ReadOnly))
        {
            QMessageBox fehlermeldung;
            fehlermeldung.critical(0, "Fehler", "Ein Fehler beim Öffnen der Datei ist aufgetreten.");
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
}

/*Aus der übergebenen QListe werden zuerst einzele JsonObjekte aus den Patienten gemacht und in einen JsonArray gespeichert.
Dann wird das ganze Array in einem einzelnen JsonObjekt gespeichert und dem Aufrufer zurückgegeben.*/

QJsonObject Speicher::json_erstellen(QList<Patient*> patienten)
{
    QJsonArray json_patienten;
    for (Patient* patient : patienten)
    {
        QJsonObject json_patient;
        patient->write(json_patient);
        json_patienten.append(json_patient);
    }

    QJsonObject json;
    json["patienten"] = json_patienten;

    return json;
}

/*Das JsonObjekt, dass in "json_erstellen" erstellt wurde, wird hier in einer json-Datei gespeichert.
Diese Funktion wird immer aufrufen wenn ein Patient neuerstellt, beabeitet oder gelöscht wurde.*/

void Speicher::daten_speichern()
{
    QString dateiname = "Patienten.json";
    QFile patienten_datei(dateiname);

    if (!patienten_datei.open(QIODevice::WriteOnly))
    {
        QMessageBox fehlermeldung;
        fehlermeldung.critical(0, "Fehler", "Ein Fehler beim Öffnen der Datei ist aufgetreten.");
        return;
    }

    QJsonObject json = json_erstellen(patienten.values());

    patienten_datei.write(QJsonDocument(json).toJson(QJsonDocument::Indented));
}

/*Diese Funktion teilt den Beobachter mit, dass es in der internen Speicherung eine Änderung gab.*/

void Speicher::patientenaenderung_melden()
{
    for (Beobachter* beobachter : beobachter_patient_update)
    {
        beobachter->patient_updated();
    }
}
