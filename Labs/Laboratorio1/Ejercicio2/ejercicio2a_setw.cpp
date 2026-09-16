
#include <iostream>
#include <iomanip>   // setw, setprecision, fixed
#include <string>

using namespace std;

struct Jugador {
    string nombre;
    string equipo;
    int    partidos;
    int    goles;
    int    asistencias;
};

int main() {
    Jugador tabla[6] = {
        {"Paolo Guerrero",  "Alianza Lima",     28, 21, 5},
        {"Alex Valera",     "Universitario",    30, 18, 7},
        {"Hernan Barcos",   "Alianza Lima",     27, 15, 9},
        {"Christian Cueva", "Cienciano",        25, 11, 12},
        {"Bernardo Cuesta", "Melgar",           29,  9, 3},
        {"Jairo Concha",    "Universitario",    26,  7, 10}
    };
    const int TOTAL = 6;

    cout << "===================================================================" << endl;
    cout << "   ESTADISTICA DEPORTIVA - TABLA DE GOLEADORES (setw)              " << endl;
    cout << "===================================================================" << endl;

    // ---------- Encabezado ----------
    cout << setw(4)  << "N"
         << setw(20) << "JUGADOR"
         << setw(16) << "EQUIPO"
         << setw(6)  << "PJ"
         << setw(6)  << "GOL"
         << setw(6)  << "AST"
         << setw(12) << "GOL/PART" << endl;

    cout << "-------------------------------------------------------------------" << endl;

    // ---------- Detalle ----------
    cout << fixed << setprecision(2);
    for (int i = 0; i < TOTAL; i++) {
        double promedio = (double)tabla[i].goles / tabla[i].partidos;

        cout << setw(4)  << (i + 1)
             << setw(20) << tabla[i].nombre
             << setw(16) << tabla[i].equipo
             << setw(6)  << tabla[i].partidos
             << setw(6)  << tabla[i].goles
             << setw(6)  << tabla[i].asistencias
             << setw(12) << promedio << endl;
    }

    // ---------- Totales ----------
    int sumaGoles = 0, sumaAsist = 0;
    for (int i = 0; i < TOTAL; i++) {
        sumaGoles += tabla[i].goles;
        sumaAsist += tabla[i].asistencias;
    }

    cout << "-------------------------------------------------------------------" << endl;
    cout << setw(40) << "TOTALES:"
         << setw(6)  << ""
         << setw(6)  << sumaGoles
         << setw(6)  << sumaAsist << endl;
    cout << "===================================================================" << endl;

    return 0;
}
