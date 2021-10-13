#ifndef SPEICHER_H
#define SPEICHER_H
#include <list>
#include "patient.h"

class Speicher
{
public:
    ~Speicher()
    {
        instanceFlag = false;
    };
    Speicher();
    static Speicher* getInstance();
    int number_Patient(){return patientenliste.size();}

    //get und set der Patienten Liste
    void set_patientenliste(Patient ein_patient);
    std::list<Patient> get_patientenliste();

private:
    static bool instanceFlag;
    static Speicher *single;
    std::list<Patient> patientenliste;
};

#endif // SPEICHER_H
