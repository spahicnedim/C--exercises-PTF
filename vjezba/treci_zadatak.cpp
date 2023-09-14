#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>
using namespace std;

struct Plod {
    string naziv, boja;
    double tezina, cijena;

    void unesiPlod(){
        cin.ignore();
        cout << "Unesite naziv ploda: ";
        getline(cin, naziv);
        cout << "Unesite boju ploda: ";
        getline(cin, boja);
        cout << "Unesite tezinu ploda: ";
        cin >> tezina;
        cout << "Unesite cijenu ploda: ";
        cin >> cijena;

    }
};
vector<Plod> plod;

void ispisPlodova(){
    if (plod.size() > 0)        
    {
        for (int i = 0; i < plod.size(); i++)
        {
            cout << "Naziv: " << plod[i].naziv << '\n';
            cout << "Boja: " << plod[i].boja << '\n';
            cout << "Tezina: " << plod[i].tezina << '\n';
            cout << "Cijena: " << plod[i].cijena << '\n';
        }
        
    }
    
}

void ispisNajskupljeg(){
    float najvecaCijena = 0;
    string najskuplji;
    for (int i = 0; i < plod.size(); i++)
    {
        if (plod[i].cijena > najvecaCijena)
        {
            najvecaCijena = plod[i].cijena;
            najskuplji = plod[i].naziv;
        }   
    }
    cout << "Najskuplji plod je: " << najskuplji;
}


float ispisProsjecneTezine(){
    float temp = 0;
    float prosjek;
    for (int i = 0; i < plod.size(); i++)
    {
        temp += plod[i].tezina;
    }
    return prosjek = temp / plod.size();
}

void snimiPlod(){
    fstream unos("plod.csv", ios::out);
    unos << "Naziv;Boja;tezina;cijena" << endl;
    for (int i = 0; i < plod.size(); i++)
    {
        unos << plod[i].naziv << ";";
        unos << plod[i].boja << ";";
        unos << to_string(plod[i].tezina) << ";";
        unos << to_string(plod[i].cijena) << ";";
    }
    unos.close();
    
}

void ucitajPlod(){
    fstream citaj("plod.csv", ios::in);
    string linija, rijec;
    vector<string> red;
    Plod tempPlod;
    plod.clear();
    getline(citaj, linija);
    while(getline(citaj, linija)){
        red.clear();
        stringstream s(linija);
        while(getline(s,rijec,';')){
            red.push_back(rijec);
        }
        tempPlod.naziv = red[0];
        tempPlod.boja = red[1];
        tempPlod.tezina = stoi(red[2]);
        tempPlod.cijena = stoi(red[3]);
        plod.push_back(tempPlod);
    }
    citaj.close();
}

int meni(){
    int izbor;
    cout << "1. Unos plodova\n";
    cout << "2. Ispis plodova\n";
    cout << "3. Ispis najskupljeg ploda\n";
    cout << "4. Ispis prosjecne tezine\n";
    cout << "5. Pretraga\n";
    cout << "6. Kraj\n";
    cout << "Odabir: ";
    cin >> izbor;
    return izbor;
}

void pretraga(){
    int izbor;
    do{
        system("cls");
        do{
            cout << "\t::Pretraga meni::" << '\n';
            cout << "1. Po boji " << endl;
            cout << "2. Po cijeni " << endl;
            cout << "3. izlaz " << endl;
            cout << "Unesite izbor: ";
            cin >> izbor;
        }while(izbor<1 || izbor>3);
        if (izbor == 1) {
           cin.ignore();
           string b;
           cout << "Unesite boju: ";
           getline(cin, b);
           for (int i = 0; i < plod.size(); i++)
           {
            if (plod[i].boja == b)
            {
                cout << "Plodovi: " << plod[i].naziv << '\n';
            }
            
           } 
        } else if(izbor == 2){
            float x;
            cout << "Unesite cijenu: ";
            cin >> x;
            for (int i = 0; i < plod.size(); i++)
            {
                if (plod[i].cijena <= x)
                {
                    cout << "Svi plodovi manji od unesene cijene: " << plod[i].naziv << '\n';
                }
                
            }
            
        } else if(izbor == 3){
            cout << "Hvala i dovidjenja\n";
        }
        
        system("pause");
    }while(izbor != 3);
}


int main() {
    ucitajPlod();
    int izbor;
    do{
        system("cls");
        izbor = meni();
        if (izbor == 1){
            cout << "Unesi plodove: \n";
            cout << "--------------------------------------------------\n";
            Plod temp;
            temp.unesiPlod();
            plod.push_back(temp);
        }else if(izbor == 2){
            cout << "Dostupni plodovi: \n";
            cout << "--------------------------------------------------\n";
            ispisPlodova();
        }else if(izbor == 3){
            cout << "Ispis najskupljeg ploda: \n";
            cout << "--------------------------------------------------\n";
            ispisNajskupljeg();
        }else if(izbor == 4){
            cout << "Ispis prosjecne tezine svih plodova: " <<  ispisProsjecneTezine();
            cout << "--------------------------------------------------\n";
            
        }else if(izbor == 5){
            pretraga();

        } else if(izbor == 6){
            cout << "Hvala i dovidjenja\n";
        }
        system("pause");
    }while(izbor != 6);
    snimiPlod();
    return 0;
}
