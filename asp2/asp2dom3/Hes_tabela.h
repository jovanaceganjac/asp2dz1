#ifndef CJ220423_HES_TABELA_H
#define CJ220423_HES_TABELA_H

#include <iostream>
#include <string>
#include <vector>
#include <random>
#include "Adresna_funkcija.h"
using namespace std;

class Hes_tabela {
protected:
    struct Elem {
        string vrednost;
        int kljuc;
        bool deleted;

        Elem():vrednost(""), kljuc(-1), deleted(false) {}
    };

    int velicinatabele;
    int brkljuceva;
    vector<Elem> tabela;
    int brpokusajauspesno;
    int brpokusajaneuspesno;
    int brnenadjenih;
    Adresna_funkcija *adresnafunkcija;
    double limit;
public:
    Hes_tabela(int velicinatabele, Adresna_funkcija *adresnafunkcija, double lim) : tabela(velicinatabele), brkljuceva(0), velicinatabele(velicinatabele),
                                                                        adresnafunkcija(adresnafunkcija),brpokusajauspesno(0), brpokusajaneuspesno(0),
                                                                        brnenadjenih(0), limit(lim){}
    string nadji(int zadatkljuc) {
        int adr=zadatkljuc%velicinatabele;
        int pokusaji=0;
        for (int i=0; i<velicinatabele; i++, pokusaji++) {
            int indeks = (adresnafunkcija->dohvatiadr(zadatkljuc, adr, pokusaji))%velicinatabele;
            if (tabela[indeks].kljuc==zadatkljuc) {
                return tabela[indeks].vrednost;
            }
            if (tabela[indeks].deleted==false && tabela[indeks].kljuc==-1) {
                break;
            }
        }
        brpokusajaneuspesno+=pokusaji+1;
        brnenadjenih++;
        return "0";
    }

    virtual bool dodaj(int k, const string& s) {
        int adr = k % velicinatabele;
        for (int pokusaji=0; pokusaji < velicinatabele; pokusaji++) {
            int indeks = (adresnafunkcija->dohvatiadr(k, adr, pokusaji))%velicinatabele;
            if (tabela[indeks].kljuc == k) {
                return false;
            }
            if(tabela[indeks].deleted==true || tabela[indeks].kljuc==-1){

                tabela[indeks].kljuc=k;
                tabela[indeks].vrednost=s;
                tabela[indeks].deleted=false;
                brpokusajauspesno+=pokusaji+1;
                brkljuceva++;
                return true;
            }
        }
        return false;
    }

    bool obrisi(int k){
        int adr = k % velicinatabele;
        int pokusaji = 0;
        for (pokusaji=0; pokusaji<velicinatabele; pokusaji++) {
            int indeks = (adresnafunkcija->dohvatiadr(k, adr, pokusaji))%velicinatabele;
            if (tabela[indeks].kljuc == k) {
                tabela[indeks].kljuc=-1;
                tabela[indeks].vrednost="";
                tabela[indeks].deleted=true;
                brpokusajauspesno-=(pokusaji+1);
                brkljuceva--;
                return true;
            }
        }
        return false;
    }
    int vratibruspesnih() const{
        return brpokusajauspesno;
    }
    int vratibrneuspesnih() const{
        return brpokusajaneuspesno;
    }
    double vratilimit() const {
        return limit;
    }

    double prosecanbruspesno() const{
        if(brkljuceva!=0){
            return (double)vratibruspesnih()/brkljuceva;
        }
        else{
            return 0;
        }
    }
    double prosecanbrneuspesno() const{
        if(brnenadjenih!=0){
            return (double)vratibrneuspesnih()/brnenadjenih;
        }
        else{
            return 0;
        }
    }

    double prosecanbrneuspesnopriblizno() const{
        if(popunjenost()==1) return brkljuceva;
        return 1/(1-popunjenost());
    }

    void resetujstatistiku(){
        brpokusajaneuspesno=0;
        brnenadjenih=0;
    }
    void ocisti(){
        for(int i=0; i<velicinatabele; i++){
            tabela[i].kljuc=-1;
            tabela[i].vrednost="";
            tabela[i].deleted=true;
        }
        brpokusajauspesno=0;
        brkljuceva=0;
        resetujstatistiku();

    }
    int vratibrkljuceva() const{
        return this->brkljuceva;
    }
    int vrativelicinutabele() const{
        return this->velicinatabele;
    }
    double popunjenost() const{
        return (double)vratibrkljuceva()/vrativelicinutabele();
    }
    friend ostream& operator<<(ostream& os, const Hes_tabela& hestabela){
        for(int i=0; i<hestabela.velicinatabele; i++){
            if(hestabela.tabela[i].kljuc==-1){
                os<<"EMPTY"<<endl;
                ;            }
            else{
                os<<"Kljuc:"<<hestabela.tabela[i].kljuc<<", vrednost:"<<hestabela.tabela[i].vrednost<<endl;
            }
        }
        return os;
    }
};

#endif