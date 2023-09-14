#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>
using namespace std;

double findMax(double* niz, int size, int index = 0){
    if(index == size -1){
        return niz[index];
    }

    double maxInRest = findMax(niz, size, index + 1);
    return (niz[index] > maxInRest) ? niz[index] : maxInRest;
}

int main() {
    
    int n;
    cout << "Unesite broj elemenata niza: ";
    cin >> n;

    double** niz = new double*[n];

    for (int i = 0; i < n; i++)
    {
        niz[i] = new double;
        cout << "unesite " << i+1 << ". broj: ";
        cin >> *niz[i];
    }

    double maxNumber = findMax(*niz, n);
    cout << "Najveci broj u nizu je: " << maxNumber << '\n';
    for (int i = 0; i < n; i++)
    {
        delete niz[i];
    }

    delete[] niz;
    niz = NULL;
    
    
    
    return 0;
}
