#ifndef PATIENT_H
#define PATIENT_H
#include <string>

class Patient
{
public:
    //objekt Patient
        Patient(std::string titel,
                std::string nachname,
                std::string vorname,
                std::string strasse,
                std::string ort,
                int hnr,
                int plz,
                int patient_id,
                double tel,
                char geschlecht);

        //get-funktionen
        std::string get_titel(){return titel;}
        std::string get_nachname(){return nachname;}
        std::string get_vorname(){return vorname;}
        std::string get_strasse() {return strasse;}
        std::string get_ort(){return ort;}
        int get_hnr() {return hnr;}
        int get_plz(){return plz;}
        int get_patient_id(){return patient_id;}
        double get_tel(){return tel;}
        char get_geschlecht(){return geschlecht;}

        //set-funktionen
        void set_titel(std::string title){titel = title;}
        void set_nachname(std::string nn){nachname = nn;}
        void set_vorname(std::string vn){vorname = vn;}
        void set_strasse(std::string street) {strasse = street;}
        void set_ort(std::string place){ort = place;}
        void set_hnr(int hausnummer){hnr = hausnummer;}
        void set_plz(int postleitzahl){plz = postleitzahl;}
        void set_patient_id(int pat_id){patient_id = pat_id;}
        void set_tel(double telefonnummer){tel = telefonnummer;}
        void set_geschlecht(char geschl){geschlecht = geschl;}

    private:
        //variablen
        std::string titel;
        std::string nachname;
        std::string vorname;
        std::string strasse;
        std::string ort;
        int hnr;
        int plz;
        int patient_id;
        double tel;
        char geschlecht;
    };


#endif // PATIENT_H
