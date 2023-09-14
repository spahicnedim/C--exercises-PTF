#include <iostream>
#include <iomanip>
#include <cstring>

using namespace std;
char * crt = "\n========================================\n";
/*
Napraviti enumeracije
godinaStudija, nacinStudiranja, Odgovori
*/
enum godinaStudija {prva=1, druga, treca, cetvrta};
enum nacinStudiranja {redovan, vanredni};
enum Odgovori {NETACNO, TACNO};

struct Student
{
    int brIndeksa;
    char imePrezime[50];
    bool radioTest;
    nacinStudiranja nacin;
    godinaStudija godina;
    Odgovori odgovori[100];
};
struct Pitanje{
    char tekstPitanja[100];
    Odgovori odgovorNaPitanje;
};
const int maxPitanja = 100;
const int maxStudenata = 100;
Pitanje pitanjaDB[maxPitanja];
Student studentiDB[maxStudenata];
int brojPitanja = 0, brojStudenata = 0;

void Dodaj(char* tekstPitanja, Odgovori tacanOdgovor){
    Pitanje temp;
    strcpy(temp.tekstPitanja, tekstPitanja);
    temp.odgovorNaPitanje = tacanOdgovor;
    pitanjaDB[brojPitanja++] = temp;
}
void dodajDefaultPitanja(){
    Dodaj("Enumeracije i unije su sinonimi?",NETACNO);
    Dodaj("Moguce je kreirati anonimnu uniju?",TACNO);
    Dodaj("Svi clanovi unije koriste istu memorijsku lokaciju?",TACNO);
    Dodaj("Svi clanovi strukture koriste istu memorijsku lokaciju?",NETACNO);
    Dodaj("Unija moze biti deklarisana unutar strukture?",TACNO);
}
void prikaziPitanje(int rbPitanja) {
    cout << "\n\t" << pitanjaDB[rbPitanja].tekstPitanja << endl;
}
Odgovori dajTacanOdgovor(int rbPitanja) {
    return pitanjaDB[rbPitanja].odgovorNaPitanje;
}
int dajBrojTacnih(Student & s) {
    int brTacnih = 0;
    for(int i=0;i<brojPitanja;i++){
        if(s.odgovori[i] == dajTacanOdgovor(i)) brTacnih++;
    }
    return brTacnih;
}
void pokreniTest(Student & student) {
    for(int i=0;i<brojPitanja;i++){
        cout << i+1 << ". pitanje: ";
        prikaziPitanje(i);
        int x;
        do{
            cout << "\t0 - Netacno\t1 - Tacno\nOdgovor: ";
            cin >> x;
        }while(x<0 || x>1);
        student.odgovori[i] = static_cast<Odgovori>(x); //(Odgovori)x
    }
    student.radioTest = true;
}
void unosPodataka()
{
    int x;
    cout << brojStudenata+1 << ". student:\n";
    cin.ignore();
    cout << "\tUnesite ime i prezime: ";
    cin.getline(studentiDB[brojStudenata].imePrezime, 50);
    cout << "\tUnesite broj indeksa: ";
    cin >> studentiDB[brojStudenata].brIndeksa;
    do{
        cout << "\tNacin studiranja (0-Redovan, 1-Vanredan): ";
        cin >> x;
    }while(x<0 || x>1);
    studentiDB[brojStudenata].nacin = static_cast<nacinStudiranja>(x);
    do{
        cout << "\tUnesite godinu studija (1, 2, 3 ili 4): ";
        cin >> x;
    }while(x<0 || x>4);
    studentiDB[brojStudenata].godina = static_cast<godinaStudija>(x);
    cin.ignore();
    studentiDB[brojStudenata++].radioTest = false;
}
int PrikaziMeni() {
    int izbor;
    do
    {
        cout << crt << "\t::MENI::" << crt;
        cout << "1. Pokreni test" << endl;
        cout << "2. Prikazi rezultate" << endl;
        cout << "3. Unos pitanja" << endl;
        cout << "4. Unos studenta" << endl;
        cout << "5. Pretraga" << endl;
        cout << "6. Kraj rada" << crt;
        cout << "Unesite izbor: ";
        cin >> izbor;
    } while (izbor<1 || izbor>6);
    return izbor;
}
int prikaziStudente()
{
    int rb = 0;
    cout << setw(5) << " Rb. " << setw(30) << left << "Ime i prezime"
         << setw(10) << "Broj indeksa\n";
    cout << "-------------------------------------------------------------------\n";
    for(int i=0;i<brojStudenata;i++){
        cout << setw(3) << right << i+1 << setw(2) << ". " << setw(30)
             << left << studentiDB[i].imePrezime <<setw(12) << right << studentiDB[i].brIndeksa
             << endl;
    }
    cout << "-------------------------------------------------------------------\n";
    do{
        cout << "Unesite redni broj studenta: ";
        cin >> rb;
    }while(rb<1 ||rb>brojStudenata);
    return rb-1;
}
void unosPitanja(){
    cin.ignore();
    int x;
    cout << "Unesite tekst pitanja: ";
    cin.getline(pitanjaDB[brojPitanja].tekstPitanja,100);
    do{
        cout << "Unesite tacan odgovor na ovo pitanje (0-Netacno, 1-Tacno):";
        cin >> x;
    }while(x<0 || x>1);
    pitanjaDB[brojPitanja++].odgovorNaPitanje = static_cast<Odgovori>(x);
}
string vratiGodinu(godinaStudija x){
    switch(x){
        case prva:
            return "prvoj";
        case druga:
            return "drugoj";
        case treca:
            return "trecoj";
        case cetvrta:
            return "cetvrtoj";
    }
}
string vratiNacin(nacinStudiranja x){
    switch(x){
        case redovan:
            return "redovnih";
        case vanredni:
            return "vanrednih";
    }
}
void pretraga(){
    int izbor;
    do{
        system("cls");
        do{
            cout << crt << "\t::Pretraga meni::" << crt;
            cout << "1. Po godini studija " << endl;
            cout << "2. Po nacinu studiranja " << endl;
            cout << "3. Po rezultatima testa " << endl;
            cout << "4. Izlaz iz pretrage!" << endl;
            cout << "Unesite izbor: ";
            cin >> izbor;
        }while(izbor<1 || izbor>4);
        int x;
        if(izbor == 1){
            do{
                cout << "Unesite godinu studija (1,2,3 ili 4): ";
                cin >> x;
            }while(x<1 || x>4);
            int br = 1;
            cout << setw(5) << " Rb. " << setw(30) << left << "Ime i prezime"
                 << setw(10) << "Broj indeksa\n";
            cout << "-------------------------------------------------------------------\n";
            for(int i=0;i<brojStudenata;i++){
                if(studentiDB[i].godina == static_cast<godinaStudija>(x)){
                    cout << setw(3) << right << br++ << setw(2) << ". " << setw(30)
                         << left << studentiDB[i].imePrezime <<setw(12) << right << studentiDB[i].brIndeksa
                         << endl;
                }
            }
            if(br==1){
                cout << "Nema studenata na " << vratiGodinu(static_cast<godinaStudija>(x))
                     << " godini!\n";
            }
            cout << "-------------------------------------------------------------------\n";
        }else if(izbor == 2){
            do{
                cout << "Unesite nacin studiranja (0-Redovan,1-Vanredan): ";
                cin >> x;
            }while(x<0 || x>1);
            int br = 1;
            cout << setw(5) << " Rb. " << setw(30) << left << "Ime i prezime"
                 << setw(10) << "Broj indeksa\n";
            cout << "-------------------------------------------------------------------\n";
            for(int i=0;i<brojStudenata;i++){
                if(studentiDB[i].nacin == static_cast<nacinStudiranja>(x)){
                    cout << setw(3) << right << br++ << setw(2) << ". " << setw(30)
                         << left << studentiDB[i].imePrezime <<setw(12) << right << studentiDB[i].brIndeksa
                         << endl;
                }
            }
            if(br==1){
                cout << "Nema " << vratiNacin(static_cast<nacinStudiranja>(x))
                     << " studenata!\n";
            }
            cout << "-------------------------------------------------------------------\n";
        }else if(izbor == 3){
            float minP, maxP;
            do{
                cout << "Unesite minimalni procenat: ";
                cin >> minP;
            }while(minP<0 || minP>100);
            if(minP == 100){
                maxP == 100;
            }else{
                do {
                    cout << "Unesite maksimalni procenat (>" << minP << "): ";
                    cin >> maxP;
                }while (maxP < minP || maxP > 100);
            }
            int br = 1;
            cout << setw(5) << " Rb. " << setw(30) << left << "Ime i prezime"
                 << setw(10) << "Broj indeksa\n";
            cout << "-------------------------------------------------------------------\n";
            for(int i=0;i<brojStudenata;i++){
                int t = dajBrojTacnih(studentiDB[i]);
                float p = (100.*t)/brojPitanja;
                if(p>=minP && p<=maxP){
                    cout << setw(3) << right << br++ << setw(2) << ". " << setw(30)
                         << left << studentiDB[i].imePrezime <<setw(12) << right << studentiDB[i].brIndeksa
                         << endl;
                }
            }
            if(br==1){
                cout << "Nema studenata sa procentom iz intervala ["
                     << minP << "," << maxP << "]!\n";
            }
            cout << "-------------------------------------------------------------------\n";

        }
        system("pause");
    }while(izbor != 4);
}
int main()
{
    int izbor;
    dodajDefaultPitanja();
    do{
        system("cls");
        izbor = PrikaziMeni();
        if(izbor == 6){
            cout << "Hvala i dovidjenja!\n";
        }else if(izbor == 1 && brojStudenata != 0){
            Student &st = studentiDB[prikaziStudente()];
            if(st.radioTest){
                cout << crt << "Test je uradjen za ovog studenta!" << crt;
            }else{
                cout << "Student " << st.imePrezime << " radi test.\n";
                pokreniTest(st);
                cout << "Test je zavrsen. Hvala na odgovorima!\n";
            }
            system("pause");
        }else if(izbor == 2 && brojStudenata != 0){
            Student &st = studentiDB[prikaziStudente()];
            if(st.radioTest){
                int t = dajBrojTacnih(st);
                float p = (100.*t)/brojPitanja;
                cout << "Uspjeh je " << setprecision(2) << p << " % - ("
                     << t << "/" << brojPitanja+1 << ")\n";
            }else{
                cout << crt << st.imePrezime << " jos nije radio test!" << crt;
            }
            system("pause");
        }else if(izbor == 3 && brojPitanja<100){
            unosPitanja();
        }else if(izbor == 4 && brojStudenata<100){
            unosPodataka();
        }else if(izbor == 5){
            pretraga();
        }
    }while(izbor != 6);
    system("pause");
    return 0;
}
