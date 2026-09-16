#include <iostream>
using namespace std;

int main() {
    unsigned short int myAge = 5, yourAge = 10;
    unsigned short int * pAge = &myAge;

    cout << "myAge:\t" << myAge << "\tyourAge:\t" << yourAge << "\n";
    cout << "&myAge:\t" << &myAge << "\t&yourAge:\t" << &yourAge << "\n";

    cout << "pAge:\t" << pAge << "\n";
    cout << "*pAge:\t" << *pAge << "\n";
    cout << "\n";

    pAge = &yourAge;   // reasignar el puntero

    cout << "myAge:\t" << myAge << "\tyourAge:\t" << yourAge << "\n";
    cout << "&myAge:\t" << &myAge << "\t&yourAge:\t" << &yourAge << "\n";

    cout << "pAge:\t" << pAge << "\n";
    cout << "*pAge:\t" << *pAge << "\n";

    cout << "&pAge:\t" << &pAge << "\n";

    return 0;
}