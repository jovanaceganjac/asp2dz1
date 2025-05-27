#include <iostream>
#include <fstream>
#include <string>
#include "Bidirekciono_hesiranje.h"
#include "Adaptivna_hes_tabela.h"

void performanse(const Hes_tabela* hesTabela, const Bidirekciono_hesiranje* BH, const Node* niz, int brkljuceva, int adapt){
    Hes_tabela* tabelaperformanse=nullptr;
    if (adapt==1) tabelaperformanse=new Adaptivna_hes_tabela(hesTabela->vrativelicinutabele(), (Adresna_funkcija*) BH, hesTabela->vratilimit());
    else tabelaperformanse=new Hes_tabela(hesTabela->vrativelicinutabele(), (Adresna_funkcija*) BH, hesTabela->vratilimit());
    int j=0, brrandomkljuceva=10*brkljuceva;
    int minimum=niz[0].mojkljuc;
    int maksimum=niz[0].mojkljuc;
    while(j<brkljuceva){
        if(niz[j].mojkljuc>maksimum){
            maksimum=niz[j].mojkljuc;
        }
        if(niz[j].mojkljuc<minimum){
            minimum=niz[j].mojkljuc;
        }
        tabelaperformanse->dodaj(niz[j].mojkljuc,niz[j].mojarec);
        j++;
    }
    j=0;
    while(j<brrandomkljuceva){
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<int> ogranicenje(minimum, maksimum);
        int randombroj=ogranicenje(gen);
        tabelaperformanse->nadji(randombroj);
        j++;
    }
    cout<<"Prosecan broj pristupa pri uspesnom pretrazivanju je:"<<tabelaperformanse->prosecanbruspesno()<<endl;
    cout<<"Prosecan broj pristupa pri neuspesnom pretrazivanju je:"<<tabelaperformanse->prosecanbrneuspesno()<<endl;
    cout<<"Priblizan prosecan broj pristupa pri neuspesnom pretrazivanju je:"<<tabelaperformanse->prosecanbrneuspesnopriblizno()<<endl;
    delete tabelaperformanse;
}

int main() {
    int opcija, adapt=0;
    double limit=0;
    Hes_tabela* tabela=nullptr;
    Bidirekciono_hesiranje* BH=nullptr;
    while(1){
        cout<<"Meni:"<<endl;
        cout<<"0. Prekid programa"<<endl;
        cout<<"1. Formiraj praznu hes tabelu"<<endl;
        cout<<"2. Pronadji rec u hes tabeli"<<endl;
        cout<<"3. Dodaj rec u hes tabelu (sa standardnog ulaza)"<<endl;
        cout<<"4. Dodaj rec u hes tabelu (iz datoteke)"<<endl;
        cout<<"5. Obrisi rec iz hes tabele"<<endl;
        cout<<"6. Odredi prosecan broj pristupa pri uspesnoj pretrazi"<<endl;
        cout<<"7. Odredi prosecan broj pristupa pri neuspesnoj pretrazi"<<endl;
        cout<<"8. Odredi broj kljuceva u hes tabeli"<<endl;
        cout<<"9. Odredi velicinu hes tabele"<<endl;
        cout<<"10. Ispisi sadrzaj hes tabele"<<endl;
        cout<<"11. Odredi stepen popunjenosti hes tabele"<<endl;
        cout<<"12. Ispisi performanse"<<endl;
        cout<<"13. Ocisti hes tabelu"<<endl;
        cout<<"14. Resetuj statistiku"<<endl;
        cin>>opcija;
        switch(opcija){
            case 0: {
                delete BH;
                delete tabela;
                exit(0);
            }
            case 1: {
                int parametar;
                cout << "Unesi parametar s za bidirekciono hesiranje:";
                cin >> parametar;
                BH = new Bidirekciono_hesiranje(parametar);
                int vel;
                if (tabela!=nullptr) {
                    delete tabela;
                }
                cout << "Unesi velicinu hes tabele: ";
                cin >> vel;
                cout << "Unesi da li zelis adaptivnu tabelu? 1-da 0-ne: ";
                cin >> adapt;
                if(adapt){
                    cout << "Unesi indikator za prosecan broj pristupa: ";
                    cin >> limit;
                }
                if (adapt==1) tabela=new Adaptivna_hes_tabela(vel,BH, limit);
                else if (adapt==0) tabela=new Hes_tabela(vel, BH,limit);
                break;
            }
            case 2: {
                int kljuczapretragu;
                cout << "Unesi kljuc za koji zelis da izvrsis pretragu:";
                cin >> kljuczapretragu;
                cout << tabela->nadji(kljuczapretragu) << endl;
                break;
            }
            case 3: {
                int kljuczadodavanje;
                string reczadodavanje;
                cout << "Unesi kljuc koji zelis da dodas u hes tabelu:";
                cin >> kljuczadodavanje;
                cout << "Unesi rec koju zelis da dodas u hes tabelu:";
                cin >> reczadodavanje;
                if (tabela->dodaj(kljuczadodavanje, reczadodavanje)) {
                    cout << "Kljuc je uspesno dodat u hes tabelu." << endl;
                } else {
                    cout << "Nije moguce dodati izabran kljuc." << endl;
                }
                break;
            }
            case 4: {
                string imedatoteke;
                cout << "Unesi ime datoteke:";
                cin >> imedatoteke;
                ifstream file(imedatoteke);
                if (!file) {
                    cout << "Greska pri otvaranju datoteke." << endl;
                    break;
                }
                int kljuc;
                string vrednost;
                while (file >> vrednost >> kljuc) {
                    tabela->dodaj(kljuc, vrednost);
                }
                cout << "Kljucevi su dodati u tabelu." << endl;
                break;
            }

            case 5: {
                int kljuczabrisanje;
                cout << "Unesi kljuc za koji zelis da izvrsis brisanje:";
                cin >> kljuczabrisanje;
                if (tabela->obrisi(kljuczabrisanje) == true) {
                    cout << "Kljuc je uspesno obrisan iz hes tabele." << endl;
                } else {
                    cout << "Nije moguce obrisati izabran kljuc." << endl;
                }
                break;
            }
            case 6: {
                cout << "Prosecan broj pristupa pri uspesnom pretrazivanju je:" << tabela->prosecanbruspesno() << endl;
                break;
            }
            case 7: {
                cout << "Prosecan broj pristupa pri neuspesnom pretrazivanju je:" << tabela->prosecanbrneuspesno()<< endl;
                cout << "Priblizan prosecan broj pristupa pri neuspesnom pretrazivanju je:" << tabela->prosecanbrneuspesnopriblizno()<<endl;
                break;
            }
            case 8: {
                cout << "Broj kljuceva u hes tabeli je:" << tabela->vratibrkljuceva() << endl;
                break;
            }
            case 9: {
                cout << "Velicina hes tabele je:" << tabela->vrativelicinutabele() << endl;
                break;
            }
            case 10: {
                cout << "Tvoja hes tabela izgleda ovako:" << endl;
                cout << *tabela << endl;
                break;
            }
            case 11: {
                cout << "Stepen popunjenosti hes tabele je:" << tabela->popunjenost() << endl;
                break;
            }
            case 12: {
                int brkljucevanovi;
                int i=0;
                cout << "Unesi broj kljuceva koje zelis da dodas:";
                cin >> brkljucevanovi;
                Node* niz=new Node[brkljucevanovi];
                while(i<brkljucevanovi){
                    int k; string rec;
                    cout << "Unesi kljuc: ";
                    cin >> k;
                    cout << "Unesi rec:";
                    cin >> rec;
                    niz[i].mojkljuc=k;
                    niz[i].mojarec=rec;
                    i++;
                }
                performanse(tabela,BH,niz,brkljucevanovi,adapt);
                break;
            }
            case 13: {
                tabela->ocisti();
                cout << "Hes tabela je ociscena." << endl;
                break;
            }
            case 14: {
                tabela->resetujstatistiku();
                cout << "Statistika je resetovana" << endl;
                break;
            }
        }
    }
}