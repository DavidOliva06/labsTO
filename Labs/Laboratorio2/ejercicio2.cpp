#include <iostream>
using namespace std;

typedef unsigned short int USHORT;

int main() {
    USHORT myAge;
    USHORT * pAge = 0;
    myAge = 5;
    cout << "myAge: " << myAge << "\n";
    cout << "pAge: " << pAge << "\n";

    pAge = &myAge;
    cout << "*pAge: " << *pAge << "\n";
    cout << "pAge: " << pAge << "\n\n";

    cout << "Asignar nuevo valor al puntero\n";
    *pAge = 7;
    cout << "*pAge: " << *pAge << "\n";
    cout << "myAge: " << myAge << "\n";
    cout << "pAge: " << pAge << "\n\n";

    cout << "Asignar nuevo valor al puntero\n";
    myAge = 9;
    cout << "myAge: " << myAge << "\n";
    cout << "*pAge: " << *pAge << "\n";
    cout << "pAge: " << pAge << "\n";

    return 0;
}