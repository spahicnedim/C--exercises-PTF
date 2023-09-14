#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>
using namespace std;

struct Film{
    string naslov, reziser;
    double ocjena;
};

void pretragaFilmova(vector<Film> &film, double minOcjena){
    cout << "Naslov-reziser-ocjena\n";
    bool found = false;
    for (int i = 0; i < film.size(); i++)
    {
        if (film[i].ocjena >= minOcjena)
        {
            cout << film[i].naslov << "-" << film[i].reziser << "-" << film[i].ocjena << '\n';
            found = true;
        }
        
        
    }
    if (!found)
    {
        cout << "Nema filmova sa zadatom pretragom\n";
    }
    
    
}

int main() {
    int brojFilmova;
    cout << "Unijeti broj filmova: ";
    cin >> brojFilmova;
    vector<Film> film;
    Film temp;
    for (int i = 0; i < brojFilmova; i++)
    {
        cin.ignore();
        cout << "Unijeti naziv filma: ";
        getline(cin, temp.naslov);
        cout << "Unijeti rezisera: ";
        getline(cin, temp.reziser);
        cout << "Unijeti ocjenu za film: ";
        cin >> temp.ocjena;
        
        film.push_back(temp);
    }
    double minOcjena;
    cout << "Unesite minimalnu ocjenu za pretragu filmova: ";
    cin >> minOcjena;
    pretragaFilmova(film, minOcjena);
    
    
    return 0;
}
