#ifndef PATIENT_H
#define PATIENT_H
#include <QString>

class Patient
{
public:
    //objekt Patient
        Patient(QString titel,
                QString nachname,
                QString vorname,
                QString strasse,
                QString ort,
                QString tel,
                int hnr,
                int plz,
                int patient_id,
                char geschlecht);

        //get-funktionen
        QString get_titel(){return titel;}
        QString get_nachname(){return nachname;}
        QString get_vorname(){return vorname;}
        QString get_strasse() {return strasse;}
        QString get_ort(){return ort;}
        QString get_tel(){return tel;}
        int get_hnr() {return hnr;}
        int get_plz(){return plz;}
        int get_patient_id(){return patient_id;}
        char get_geschlecht(){return geschlecht;}

        //set-funktionen
        void set_titel(QString title){titel = title;}
        void set_nachname(QString nn){nachname = nn;}
        void set_vorname(QString vn){vorname = vn;}
        void set_strasse(QString street) {strasse = street;}
        void set_ort(QString place){ort = place;}
        void set_tel(QString telefonnummer){tel = telefonnummer;}
        void set_hnr(int hausnummer){hnr = hausnummer;}
        void set_plz(int postleitzahl){plz = postleitzahl;}
        void set_patient_id(int pat_id){patient_id = pat_id;}
        void set_geschlecht(char geschl){geschlecht = geschl;}

    private:
        //variablen
        QString titel;
        QString nachname;
        QString vorname;
        QString strasse;
        QString ort;
        QString tel;
        int hnr;
        int plz;
        int patient_id;
        char geschlecht;
    };


#endif // PATIENT_H
