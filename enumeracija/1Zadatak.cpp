#include <iostream>
#include <iomanip>

using namespace std;
char * crt = "\n========================================\n";
/*
Napraviti enumeracije
godinaStudija, nacinStudiranja, Odgovori
*/
enum godinaStudija {prva=1, druga, treca, cetvrta};
enum nacinStudiranja {redovan, vanredni};
enum Odgovori {NETACNO, TACNO};

const int brPitanja = 5;
struct Student {
    int brIndeksa;
    char imePrezime[50];
    bool radioTest;
    nacinStudiranja nacin;
    godinaStudija godina;
    Odgovori odgovori[brPitanja];
};
void prikaziPitanje(int rbPitanja) {
    switch(rbPitanja){
        case 1:
            cout << "\n\tEnumeracije i unije su sinonimi?\n";
            break;
        case 2:
            cout << "\n\tMoguce je kreirati anonimnu uniju?\n";
            break;
        case 3:
            cout << "\n\tSvi clanovi unije koriste istu memorijsku lokaciju?\n";
            break;
        case 4:
            cout << "\n\tSvi clanovi strukture koriste istu memorijsku lokaciju?\n";
            break;
        case 5:
            cout << "\n\tUnija moze biti deklarisana unutar strukture?\n";
            break;
        default:
            cout << "\n\tPogresan redni broj pitanja!\n";
    }
}
Odgovori dajTacanOdgovor(int rbPitanja) {
    switch(rbPitanja) {
        case 1:
            return NETACNO;
        case 2:
            return TACNO;
        case 3:
            return TACNO;
        case 4:
            return NETACNO;
        case 5:
            return TACNO;
    }
}
int dajBrojTacnih(Student & s) {
    int brTacnih = 0;
    for(int i=0;i<brPitanja;i++){
        if(s.odgovori[i] == dajTacanOdgovor(i+1)) brTacnih++;
    }
    return brTacnih;
}
void pokreniTest(Student & student) {
    for(int i=0;i<brPitanja;i++){
        cout << i+1 << ". pitanje: ";
        prikaziPitanje(i+1);
        int x;
        do{
            cout << "\t0 - Netacno\t1 - Tacno\nOdgovor: ";
            cin >> x;
        }while(x<0 || x>1);
        student.odgovori[i] = static_cast<Odgovori>(x); //(Odgovori)x
    }
    student.radioTest = true;
}
void unosPodataka(Student niz[], int max)
{
    int x;
    for(int i=0;i<max;i++){
        cout << i+1 << ". student:\n";
        cout << "\tUnesite ime i prezime: ";
        cin.getline(niz[i].imePrezime, 50);
        cout << "\tUnesite broj indeksa: ";
        cin >> niz[i].brIndeksa;
        do{
            cout << "\tNacin studiranja (0-Redovan, 1-Vanredan): ";
            cin >> x;
        }while(x<0 || x>1);
        niz[i].nacin = static_cast<nacinStudiranja>(x);
        do{
            cout << "\tUnesite godinu studija (1, 2, 3 ili 4): ";
            cin >> x;
        }while(x<0 || x>4);
        niz[i].godina = static_cast<godinaStudija>(x);
        cin.ignore();
        niz[i].radioTest = false;
    }
}
int PrikaziMeni() {
    int izbor;
    do
    {
        cout << crt << "\t::MENI::" << crt;
        cout << "1. Pokreni test" << endl;
        cout << "2. Prikazi rezultate" << endl;
        cout << "3. Kraj rada" << crt;
        cout << "Unesite izbor: ";
        cin >> izbor;
    } while (izbor<1 || izbor>3);
    return izbor;
}
int prikaziStudente(Student niz[], int max)
{
    int rb;
    cout << setw(5) << " Rb. " << setw(30) << left << "Ime i prezime"
         << setw(10) << "Broj indeksa\n";
    cout << "-------------------------------------------------------------------\n";
    for(int i=0;i<max;i++){
        cout << setw(3) << right << i+1 << setw(2) << ". " << setw(30)
             << left << niz[i].imePrezime <<setw(12) << right << niz[i].brIndeksa
             << endl;
    }
    cout << "-------------------------------------------------------------------\n";
    do{
        cout << "Unesite redni broj studenta: ";
        cin >> rb;
    }while(rb<1 ||rb>max);
    return rb-1;
}
int main()
{
    int max, izbor;
    cout << "Unesite broj studenata: ";
    cin >> max;
    cin.ignore();
    Student* niz = new Student[max];
    unosPodataka(niz,max);
    do{
        system("cls");
        izbor = PrikaziMeni();
        if(izbor == 3){
            cout << "Hvala i dovidjenja!\n";
        }else if(izbor == 1){
            Student &st = niz[prikaziStudente(niz,max)];
            if(st.radioTest){
                cout << crt << "Test je uradjen za ovog studenta!" << crt;
            }else{
                cout << "Student " << st.imePrezime << " radi test.\n";
                pokreniTest(st);
                cout << "Test je zavrsen. Hvala na odgovorima!\n";
            }
            system("pause");
        }else if(izbor == 2){
            Student &st = niz[prikaziStudente(niz,max)];
            if(st.radioTest){
                int t = dajBrojTacnih(st);
                float p = (100.*t)/brPitanja;
                cout << "Uspjeh je " << setprecision(2) << p << " % - ("
                     << t << "/" << brPitanja << ")\n";
            }else{
                cout << crt << st.imePrezime << " jos nije radio test!" << crt;
            }
            system("pause");
        }
    }while(izbor != 3);
    delete[] niz;
    niz = NULL;
    system("pause");
    return 0;
}
