#ifndef CJ220423_ADAPTIVNA_HES_TABELA_H
#define CJ220423_ADAPTIVNA_HES_TABELA_H

#include "Hes_tabela.h"

struct Node{
    int mojkljuc;
    string mojarec;
};

class Adaptivna_hes_tabela : public Hes_tabela{
public:
    Adaptivna_hes_tabela(int velicinatabele, Adresna_funkcija *adresnafunkcija, double lim) : Hes_tabela(velicinatabele,adresnafunkcija,lim) {}

    bool dodaj(int k, const string& s) override{
        if(popunjenost()>=0.77 || prosecanbruspesno()>limit || prosecanbrneuspesno()>limit){
            prosiri();
        }
        Hes_tabela::dodaj(k,s);
    }

    void prosiri(){
        int i=0,j=0,novibrk;
        Node* niz=new Node[brkljuceva];
        while(i<velicinatabele){
            if(tabela[i].kljuc!=-1){
                niz[j].mojkljuc=tabela[i].kljuc;
                niz[j].mojarec=tabela[i].vrednost;
                j++;
            }
            i++;
        }
        novibrk=brkljuceva;
        resetujstatistiku();
        ocisti();
        velicinatabele=(velicinatabele+1)*1.5;
        tabela.resize(velicinatabele);
        j=0;
        while(j<novibrk){
            Hes_tabela::dodaj(niz[j].mojkljuc,niz[j].mojarec);
            j++;
        }
    }
};

#endif