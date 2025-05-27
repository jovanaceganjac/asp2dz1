#ifndef CJ220423_BIDIREKCIONO_HESIRANJE_H
#define CJ220423_BIDIREKCIONO_HESIRANJE_H

#include "Adresna_funkcija.h"

class Bidirekciono_hesiranje: public Adresna_funkcija {
    int s;
public:
    Bidirekciono_hesiranje(int s):s(s){}
    int dohvatiadr(int kljuc, int adresa, int brpokusaja) const{
        if(brpokusaja%2==1){
            return adresa+brpokusaja*s;
        }
        else{
            if (brpokusaja==0) return adresa;
            return adresa+(brpokusaja-1)*s;
        }
    }

};

#endif