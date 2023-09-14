#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>
using namespace std;

struct Ucenik {
    string ime, prezime;
    int razred;
    int ocjene[5];


    void unesiUcenika(){
   
        cin.ignore();
       cout << "Unesite ime ucenika: ";
       getline(cin, ime);
       cout << "Unesite prezime ucenika: ";
       getline(cin, prezime);
       cout << "Unesite koji razred pohadja ucenik: ";
       cin >> razred;
    
    cout << "Unijeti ocjene za svih pet testova za svakog ucenika: \n";
    
        for (int j = 0; j < 5; j++)
        {
            cout << j+1 << ". test: \n";
            cout << "Ocjena: ";
            cin >> ocjene[j];
        }
        cout << "\n---------------------------------------\n";
        
    
    
        
}
};
vector<Ucenik> ucenici;



void ispisOcjena(){
    cin.ignore();
    string ime, prezime;
    cout << "Unesite ime ucenika kojeg zelite pretraziti: ";
    getline(cin, ime);
    cout << "Unesite prezime ucenika kojeg zelite pretraziti: ";
    getline(cin, prezime);
    for (int i = 0; i < ucenici.size(); i++)
    {
        if(ucenici[i].ime == ime && ucenici[i].prezime == prezime){
            for (int j = 0; j < 5; j++)
            {
                cout << j+1 << ". test, ocjena: " << ucenici[i].ocjene[j] << '\n';
            }
            
        }
        
    }
    cout << "\n============================================\n";
    
}

float ispisProsjeka(){
    cin.ignore();
    string ime, prezime;
    cout << "Unesite ime ucenika kojeg zelite pretraziti: ";
    getline(cin, ime);
    cout << "Unesite prezime ucenika kojeg zelite pretraziti: ";
    getline(cin, prezime);
    float prosjek = 0;
    
     for (int i = 0; i < ucenici.size(); i++)
    {
        if(ucenici[i].ime == ime && ucenici[i].prezime == prezime){
            int suma=0;
            for (int j = 0; j < 5; j++)
            {
                
                suma += ucenici[i].ocjene[j];
            }
            prosjek = static_cast<float>(suma) / 5;
            break;
            
        }
        
    }
    
    return prosjek;
}

void ispisNajboljeg(){
    string ime, prezime;
    float najboljiProsjek = 0;
    for (int i = 0; i < ucenici.size(); i++)
    {
        int suma = 0;
        for (int j = 0; j < 5; j++)
        {
            suma += ucenici[i].ocjene[j];
        }
        float prosjek = static_cast<float>(suma) / 5;

        if(prosjek > najboljiProsjek){
            najboljiProsjek = prosjek;
            ime = ucenici[i].ime;
            prezime = ucenici[i].prezime;
        }
        
    }
    if (najboljiProsjek > 0)    
    {
        cout << "Najbolji ucenik je " << ime << " " << prezime << " sa prosjekom: " << najboljiProsjek << '\n';
    } else {
        cout << "Nema unesenih ocneja\n";
    }
    
    
}

void snimiUcenike(){
    fstream unos("ucenik.csv", ios::out);
    unos << "Ime-Prezime-Razred-Ocjene\n";
    for (int i = 0; i < ucenici.size(); i++)
    {
        unos << ucenici[i].ime << " - ";
        unos << ucenici[i].prezime << " - ";
        unos << to_string(ucenici[i].razred) << " - ";
        for (int i = 0; i < ucenici.size(); i++)
        {
            for (int j = 0; j < 5; j++)
            {
                unos << ucenici[i].ocjene[j] << '\n';
            }
            
        }
        
    }
    unos.close();
    
}

void ucitajUcenike(){
    fstream citaj("ucenik.csv", ios::in);
    string linija, rijec;
    vector<string> red;
    Ucenik tempUcenik;
    ucenici.clear();
    getline(citaj, linija);
    while(getline(citaj, linija)){
        red.clear();
        stringstream s(linija);
        while(getline(s,rijec,';')){
            red.push_back(rijec);
        }
        tempUcenik.ime = red[0];
        tempUcenik.prezime = red[1];
        tempUcenik.razred = stoi(red[2]);
        
        ucenici.push_back(tempUcenik);
    }
    citaj.close();
}



int meni(){
    int izbor;
    cout << "1. Unos ucenika\n";
    cout << "2. Ispis ocjena\n";
    cout << "3. Ispis prosjeka\n";
    cout << "4. Ispis najboljeg ucenika\n";
    cout << "5. Kraj\n";
    cout << "Odabir: ";
    cin >> izbor;
    return izbor;
}


int main() {
   ucitajUcenike();
    int izbor;
    do{
        system("cls");
        izbor = meni();
        if (izbor == 1){
            cout << "Unesi ucenike: \n";
            cout << "--------------------------------------------------\n";
           Ucenik temp;
            temp.unesiUcenika();
            ucenici.push_back(temp);
        }else if(izbor == 2){
            cout << "--------------------------------------------------\n";
            ispisOcjena();
        }else if(izbor == 3){
            float prosjek = ispisProsjeka();
    if (prosjek != 0) {
        std::cout << "Prosjek ocjena: " << prosjek << std::endl;
    } else {
        std::cout << "Ucenik nije pronadjen." << std::endl;
    }
        }else if(izbor == 4){
            
            cout << "--------------------------------------------------\n";
            ispisNajboljeg();
        }else if(izbor == 5){
           cout << "Hvala i dovidjenja\n";

        } 
        system("pause");
    }while(izbor != 5);
   snimiUcenike();
    return 0;
}