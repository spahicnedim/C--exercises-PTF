#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>
using namespace std;

enum Stanje{NEAKTIVAN, AKTIVAN};

struct Autobus{
    string ID, vozac, prevoznik;
    int brojMjesta;
    vector<string> mjesta;
    Stanje stanje;

    void unosAutobusa(){
        string provjera;
        bool postoji;
        do{
            postoji = false;
            cout << "Unesite ID autobusa: ";
            cin >> ID;
            ifstream citaj("autobus.csv",ios::in);
            string linija, rijec, temp;
            vector<string> red;
            getline(citaj,linija);
            while(getline(citaj,linija)){
                red.clear();
                stringstream s(linija);
                while(getline(s,rijec,';')){
                    red.push_back(rijec);
                }
                if(red[0] == ID) postoji = true;
            }
            citaj.close();
            if(postoji) cout << "Autobus sa tim ID-om vec postoji!\n";
        }while(postoji);
        cin.ignore();
        cout << "Unesite ime i prezime vozaca: ";
        getline(cin,vozac);
        cout << "Unesite naziv prevoznika: ";
        getline(cin, prevoznik);
        cout << "Unesite broj mjesta u autobusu: ";
        cin >> brojMjesta;
        int x;
        do{
            cout << "Unesite stanje autobusa: \n\t0. Neaktivan\t1. Aktivan";
            cout << "\nOdabir: ";
            cin >> x;
        }while(x<0 || x>1);
        stanje = static_cast<Stanje>(x);
        for(int i=0;i<brojMjesta;i++){
            mjesta.push_back("Prazno");
        }
    }
};
vector<Autobus> autobusi;


void snimiAutobuse(){
    fstream unos("autobus.csv",ios::out);
    unos << "ID;Vozac;Prevoznik;Broj mjesta;Stanje\n";
    for(int i=0;i<autobusi.size();i++){
        unos << autobusi[i].ID << ";";
        unos << autobusi[i].vozac << ";";
        unos << autobusi[i].prevoznik << ";";
        unos << to_string(autobusi[i].brojMjesta) << ";";
        unos << to_string(static_cast<int>(autobusi[i].stanje)) << endl;
        ofstream unosMjesta(autobusi[i].ID+".txt",ios::out);
        for(int j=0;j<autobusi[i].mjesta.size();j++){
            if(j<autobusi[i].mjesta.size()-1){
                unosMjesta << autobusi[i].mjesta[j] << endl;
            }else{
                unosMjesta << autobusi[i].mjesta[j];
            }
        }
        unosMjesta.close();
    }
    unos.close();
}
void ucitajAutobuse(){
    fstream citaj("autobus.csv",ios::in);
    string linija, rijec, temp;
    vector<string> red;
    Autobus tempAutobus;
    autobusi.clear();
    getline(citaj,linija);
    while(getline(citaj, linija)){
        red.clear();
        stringstream s(linija);
        while(getline(s,rijec,';')){
            red.push_back(rijec);
        }
        tempAutobus.ID = red[0];
        tempAutobus.vozac = red[1];
        tempAutobus.prevoznik = red[2];
        tempAutobus.brojMjesta = stoi(red[3]);
        tempAutobus.stanje = static_cast<Stanje>(stoi(red[4]));
        fstream citajMjesta(tempAutobus.ID+".txt",ios::in);
        string tempMjesta;
        while(getline(citajMjesta,tempMjesta)) tempAutobus.mjesta.push_back(tempMjesta);
        citajMjesta.close();
        autobusi.push_back(tempAutobus);
    }
    citaj.close();
}
string getStanje(Stanje s){
    switch(s){
        case NEAKTIVAN:
            return "Neaktivan";
        case AKTIVAN:
            return "Aktivan";
    }
}

void pregledAutobusa(){
    if(autobusi.size() > 0){
        cout << left << setw(6) << "R.br" << setw(9) << "ID"
             << setw(25) << "Vozac" << setw(25) << "Prevoznik"
             << setw(15) << "Broj mjesta" << setw(15) << "Stanje"
             << endl;
        for(int i=0;i<autobusi.size();i++){
            cout << setw(6) << i+1;
            cout << setw(9) << autobusi[i].ID;
            cout << setw(25) << autobusi[i].vozac;
            cout << setw(25) << autobusi[i].prevoznik;
            cout << setw(15) << autobusi[i].brojMjesta;
            cout << setw(15) << getStanje(autobusi[i].stanje) << endl;
        }
    }else{
        cout << "Nema unijetih autobusa!\n";
    }
}

void pregledRezervacija(){
    pregledAutobusa();
    int x;
    string a;
    do{
        cout << "Unesite redni broj autobusa: ";
        cin >> x;
    }while(x-1<0 || x-1>autobusi.size());
    Autobus *temp = &autobusi[x-1];
    cout << "=====Mjesta u autobusu=====\n";
    for(int i=0;i<temp->mjesta.size();i++){
        a = "[" + to_string(i+1) + "] ";
        if((i+1)%2==0){
            cout << right << setw(5) << a << left << setw(25) << temp->mjesta[i] << "\t\t\t";
        }else{
            cout << right << setw(5) << a << left << setw(25) << temp->mjesta[i];
        }
        if((i+1)%4==0) cout << endl;
    }
}

void rezervacijaMjesta(){
    pregledAutobusa();
    int x;
    string a;
    do{
        cout << "Unesite redni broj autobusa: ";
        cin >> x;
    }while(x-1<0 || x-1>autobusi.size());
    Autobus *temp = &autobusi[x-1];
    cout << "=====Mjesta u autobusu=====\n";
    for(int i=0;i<temp->mjesta.size();i++){
        a = "[" + to_string(i+1) + "] ";
        if((i+1)%2==0){
            cout << right << setw(5) << a << left << setw(25) << temp->mjesta[i] << "\t\t\t";
        }else{
            cout << right << setw(5) << a << left << setw(25) << temp->mjesta[i];
        }
        if((i+1)%4==0) cout << endl;
    }
    do{
        cout << "\nUnesite redni broj mjesta: ";
        cin >> x;
        if(temp->mjesta[x-1] != "Prazno"){
            cout << "To mjesto je vec rezervisano!\n";
            x = 0;
        }
    }while(x<1 || x>temp->mjesta.size());
    cin.ignore();
    cout << "\nUnesite vase ime i prezime: ";
    getline(cin,a);
    temp->mjesta[x-1] = a;
}
int meni(){
    int izbor;
    cout << "1. Unos autobusa\n";
    cout << "2. Pregled autobusa\n";
    cout << "3. Unos rezervacije\n";
    cout << "4. Pregled rezervacija\n";
    cout << "5. Kraj\n";
    cout << "Odabir: ";
    cin >> izbor;
    return izbor;
}
int main() {
    ucitajAutobuse();
    int izbor;
    do{
        system("cls");
        izbor = meni();
        if (izbor == 1){
            cout << "Unos autobusa: \n";
            cout << "--------------------------------------------------\n";
            Autobus temp;
            temp.unosAutobusa();
            autobusi.push_back(temp);
        }else if(izbor == 2){
            cout << "Dostupni autobusi su: \n";
            cout << "--------------------------------------------------\n";
            pregledAutobusa();
        }else if(izbor == 3){
            cout << "Unos rezervacije: \n";
            cout << "--------------------------------------------------\n";
            rezervacijaMjesta();
        }else if(izbor == 4){
            cout << "Pregled rezervacija: \n";
            cout << "--------------------------------------------------\n";
            pregledRezervacija();
        }else if(izbor == 5){
            cout << "Hvala i dovidjenja!\n";
        }
        system("pause");
    }while(izbor != 5);
    snimiAutobuse();
    return 0;
}
