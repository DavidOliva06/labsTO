#include "Utilidades.h"

#include <iostream>
#include <limits>

using namespace std;

string leerLinea(const string &mensaje) {
    string texto;
    cout << mensaje;
    getline(cin, texto);
    while (texto.empty()) {
        cout << "  >> No puede quedar vacio. " << mensaje;
        getline(cin, texto);
    }
    return texto;
}

int leerEntero(const string &mensaje) {
    int valor;
    while (true) {
        cout << mensaje;
        if (cin >> valor) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return valor;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "  >> Valor invalido." << endl;
    }
}

double leerDecimal(const string &mensaje) {
    double valor;
    while (true) {
        cout << mensaje;
        if (cin >> valor) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return valor;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "  >> Valor invalido." << endl;
    }
}
