#include "speicher.h"

Speicher::Speicher()
{

}

bool Speicher::instanceFlag = false;

Speicher* Speicher::single = NULL;

Speicher* Speicher::getInstance()
{
    if(!instanceFlag)
    {
        single = new Speicher();
        instanceFlag = true;
        return single;
    }
    else
    {
        return single;
    }
}

void Speicher::set_patientenliste(Patient ein_patient)
{
    patientenliste.push_back(ein_patient);
}
