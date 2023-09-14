#include <iostream>
#include <iomanip>
#include <cstring>
#include <limits>

using namespace std;
char * crt = "\n========================================\n";
/*
Napraviti enumeracije
godinaStudija, nacinStudiranja, Odgovori
*/
enum godinaStudija {prva=1, druga, treca, cetvrta};
enum nacinStudiranja {redovan, vanredni};
enum Odgovori {NETACNO, TACNO};
enum korisnickaUloga {student, administrator};
const int maxPitanja = 100;
const int maxStudenata = 100;
int brojPitanja = 0, brojStudenata = 0;

struct Osoba{
    char imePrezime[50];
    char username[30];
    char password[30];
};
struct Administrator{
    Osoba administrator;
    int id;
    korisnickaUloga uloga;
};
struct Student
{
    int brIndeksa;
    Osoba student;
    bool radioTest;
    nacinStudiranja nacin;
    godinaStudija godina;
    Odgovori odgovori[maxPitanja];
    korisnickaUloga uloga;
};
struct Pitanje{
    char tekstPitanja[100];
    Odgovori odgovorNaPitanje;
};

Pitanje pitanjaDB[maxPitanja];
Student studentiDB[maxStudenata];
Administrator admin;

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
void unosPodatakaStudenta()
{
    system("cls");
    int x;
    cout << crt << "\t::Registracija studenta::" << crt;
    cout << brojStudenata + 1 << ". student:\n";
    cin.ignore();
    cout << "\tUnesite ime i prezime: ";
    cin.getline(studentiDB[brojStudenata].student.imePrezime, 50);
    bool postoji;
    do{
        postoji = false;
        cout << "\tUnesite username: ";
        cin.getline(studentiDB[brojStudenata].student.username,30);
        if(!strcmp(studentiDB[brojStudenata].student.username,admin.administrator.username)){
            cout << "\t[GRESKA] Ovo je username od administratora!\n";
            postoji = true;
        }
        for(int i=0;i<brojStudenata;i++){
            if(!strcmp(studentiDB[brojStudenata].student.username,studentiDB[i].student.username)){
                cout << "\t[GRESKA] Ovo je username od drugog korisnika!\n";
                postoji = true;
            }
        }
    }while(postoji);
    cout << "\tUnesite password za studenta: ";
    cin.getline(studentiDB[brojStudenata].student.password,30);
    do{
        postoji = false;
        cout << "\tUnesite broj indeksa: ";
        cin >> studentiDB[brojStudenata].brIndeksa;
        if(!cin.good()){
            cin.clear();
            cout << "\t[GRESKA] Uneseni indeks mora biti broj!\n";
            cin.ignore(std::numeric_limits<streamsize>::max(),'\n');
            postoji = true;
        }else if(studentiDB[brojStudenata].brIndeksa<1){
            cout << "\t[GRESKA] Uneseni indeks mora biti veci od 0!\n";
            postoji = true;
        }else if(studentiDB[brojStudenata].brIndeksa == 123456){
            cout << "\t[GRESKA] Uneseni indeks ne moze biti 123456!\n";
            postoji = true;
        }else{
            for(int i=0;i<brojStudenata;i++){
                if(studentiDB[brojStudenata].brIndeksa == studentiDB[i].brIndeksa){
                    cout << "\t[GRESKA] Uneseni indeks vec postoji!\n";
                    postoji = true;
                }
            }
        }
    }while(postoji);
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
    studentiDB[brojStudenata].uloga = student;
}

int adminMeni() {
    int izbor;
    do
    {
        cout << crt << "\t::ADMIN::" << crt;
        cout << "1. Unos pitanja" << endl;
        cout << "2. Unos studenta" << endl;
        cout << "3. Prikazi rezultate testova" << endl;
        cout << "4. Pretrga" << endl;
        cout << "5. Resetuj test za studenta" << endl;
        cout << "6. Prikazi sve studente" << endl;
        cout << "7. Prikazi sva pitanja" << endl;
        cout << "8. Kraj rada" << crt;
        cout << "Unesite izbor: ";
        cin >> izbor;
    } while (izbor<1 || izbor>8);
    return izbor;
}
int studentMeni() {
    int izbor;
    do
    {
        cout << crt << "\t::STUDENT::" << crt;
        cout << "1. Pokreni test" << endl;
        cout << "2. Prikazi rezultate testa" << endl;
        cout << "3. Kraj rada" << crt;
        cout << "Unesite izbor: ";
        cin >> izbor;
    } while (izbor<1 || izbor>3);
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
             << left << studentiDB[i].student.imePrezime <<setw(12) << right << studentiDB[i].brIndeksa
             << endl;
    }
    cout << "-------------------------------------------------------------------\n";
    do{
        cout << "Unesite redni broj studenta: ";
        cin >> rb;
    }while(rb<1 ||rb>brojStudenata);
    return rb-1;
}
void prikazStudenata()
{
    if(brojStudenata!=0){
        cout << setw(5) << " Rb. " << setw(30) << left << "Ime i prezime"
             << setw(10) << "Broj indeksa\n";
        cout << "-------------------------------------------------------------------\n";
        for(int i=0;i<brojStudenata;i++){
            cout << setw(3) << right << i+1 << setw(2) << ". " << setw(30)
                 << left << studentiDB[i].student.imePrezime <<setw(12) << right << studentiDB[i].brIndeksa
                 << endl;
        }
        cout << "-------------------------------------------------------------------\n";
    }else{
        cout << "Trenutno nema registrovanih studenata!\n";
        cout << "Za nastavak pritisnite enter:";
        cin.get();
    }
    system("pause");
}
string vratiOdgovor(Odgovori x){
    switch (x) {
        case TACNO:
            return "TACNO";
        case NETACNO:
            return "NETACNO";
    }
}
void prikazPitanja(){
    cout << setw(3) <<"\nPitanja za test:\n";
    for(int i=0;i<brojPitanja;i++){
        cout << setw(3) << i+1 << ". " << pitanjaDB[i].tekstPitanja <<endl;
        cout << setw(3) << " " << "Odgovor: " << vratiOdgovor(pitanjaDB[i].odgovorNaPitanje) << endl;
    }
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
                         << left << studentiDB[i].student.imePrezime <<setw(12) << right << studentiDB[i].brIndeksa
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
                         << left << studentiDB[i].student.imePrezime <<setw(12) << right << studentiDB[i].brIndeksa
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
                         << left << studentiDB[i].student.imePrezime <<setw(12) << right << studentiDB[i].brIndeksa
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
int loginMeni(){
    int izbor;
    do
    {
        cout << crt << "\t::LOGIN::" << crt;
        cout << "1. Login" << endl;
        cout << "2. Registracija usera" << endl;
        cout << "3. Kraj rada" << crt;
        cout << "Unesite izbor: ";
        cin >> izbor;
    } while (izbor<1 || izbor>3);
    return izbor;
}
int login(){
    char username[30], password[30];
    system("cls");
    cout << crt << "\t::LOGIN::" << crt;
    cin.ignore();
    cout << "Username: ";
    cin.getline(username,30);
    cout << "Password: ";
    cin.getline(password,30);
    if(!strcmp(username, admin.administrator.username) && !strcmp(password,admin.administrator.password)){
        return 123456;
    }else{
        for(int i=0;i<brojStudenata;i++){
            if(!strcmp(username, studentiDB[i].student.username) && !strcmp(password,studentiDB[i].student.password)){
                return studentiDB[i].brIndeksa;
            }
        }
    }
    return -1;
}

int main()
{
    strcpy(admin.administrator.imePrezime, "Edin Tabak");
    strcpy(admin.administrator.username, "kobara");
    strcpy(admin.administrator.password, "abcd1234");
    admin.id = 123456;
    admin.uloga = administrator;
    int izbor;
    dodajDefaultPitanja();
    do{
        system("cls");
        izbor = loginMeni();
        system("cls");
        if(izbor == 3) break;
        if(izbor == 1){
            int id = login();
            if(id == -1){
                cout << "[GRESKA] Ne postoji korisnik sa tim podacima!\n";
                cout << "Za nastavak pritisnite enter!";
                cin.get();
            }else if(id == admin.id){
                do{
                    system("cls");
                    izbor = adminMeni();
                    if(izbor == 8) break;
                    if(izbor == 1){
                        unosPitanja();
                        for(int i=0;i<brojStudenata;i++){
                            studentiDB[i].radioTest = false;
                        }
                    }else if(izbor == 2){
                        unosPodatakaStudenta();
                    }else if(izbor == 3){
                        Student &st = studentiDB[prikaziStudente()];
                        if(st.radioTest){
                            int t = dajBrojTacnih(st);
                            float p = (100.*t)/(brojPitanja+1);
                            cout << "Uspjeh je " << setprecision(2) << p << " % - ("
                                 << t << "/" << brojPitanja+1 << ")\n";
                        }else{
                            cout << crt << st.student.imePrezime << " jos nije radio test!" << crt;
                        }
                        system("pause");
                    }else if(izbor == 4){
                        pretraga();
                    }else if(izbor == 5){
                        Student &st = studentiDB[prikaziStudente()];
                        st.radioTest = false;
                    }else if(izbor == 6){
                        prikazStudenata();
                    }else if(izbor == 7){
                        prikazPitanja();
                    }
                    system("pause");
                    system("cls");
                }while(1);
            }else{
                for(int i=0;i<brojStudenata;i++){
                    if(id == studentiDB[i].brIndeksa){
                        do{
                            system("cls");
                            izbor = studentMeni();
                            if(izbor == 3) break;
                            if(izbor == 1){
                               if(studentiDB[i].radioTest){
                                   cout << "Vi ste vec radili test!\n";
                               }else{
                                   pokreniTest(studentiDB[i]);
                               }
                            }else if(izbor == 2){
                                if(!studentiDB[i].radioTest){
                                    cout << "Vi jos niste radili test!\n";
                                }else{
                                    int t = dajBrojTacnih(studentiDB[i]);
                                    float p = (100.*t)/(brojPitanja+1);
                                    cout << "Uspjeh je " << setprecision(2) << p << " % - ("
                                         << t << "/" << brojPitanja+1 << ")\n";
                                }
                                cin.ignore();
                                cout << "Za nastavak pritniste enter!";
                                cin.get();
                                system("cls");
                            }
                        }while(1);
                    }
                }
            }
        }else if(izbor == 2){
            unosPodatakaStudenta();
        }
    }while(1);
    system("pause");
    return 0;
}
