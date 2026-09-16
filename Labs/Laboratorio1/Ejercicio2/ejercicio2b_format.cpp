#include <iostream>
#include <string>
#include <version>

#if defined(__cpp_lib_format)
  #include <format>
  #define TIENE_FORMAT 1
#else
  #include <sstream>
  #include <iomanip>
  #define TIENE_FORMAT 0
#endif

using namespace std;

struct Jugador {
    string nombre;
    string equipo;
    int    partidos;
    int    goles;
    int    asistencias;
};

// ------------------------------------------------------------
// Arma una fila del reporte usando std::format.
// ------------------------------------------------------------
string fila(int n, const string &nombre, const string &equipo,
            int pj, int gol, int ast, double prom) {
#if TIENE_FORMAT
    return format("{:<4}{:<20}{:<16}{:>6}{:>6}{:>6}{:>12.2f}",
                  n, nombre, equipo, pj, gol, ast, prom);
#else
    ostringstream os;
    os << left  << setw(4) << n << setw(20) << nombre << setw(16) << equipo
       << right << setw(6) << pj << setw(6) << gol << setw(6) << ast
       << fixed << setprecision(2) << setw(12) << prom;
    return os.str();
#endif
}

// ------------------------------------------------------------
// Fila final de totales
// ------------------------------------------------------------
string filaTotales(int gol, int ast) {
#if TIENE_FORMAT
    return format("{:<40}{:>6}{:>6}{:>6}", "TOTALES", "", gol, ast);
#else
    ostringstream os;
    os << left << setw(40) << "TOTALES" << right << setw(6) << ""
       << setw(6) << gol << setw(6) << ast;
    return os.str();
#endif
}

string encabezado() {
#if TIENE_FORMAT
    return format("{:<4}{:<20}{:<16}{:>6}{:>6}{:>6}{:>12}",
                  "N", "JUGADOR", "EQUIPO", "PJ", "GOL", "AST", "GOL/PART");
#else
    ostringstream os;
    os << left  << setw(4) << "N" << setw(20) << "JUGADOR" << setw(16) << "EQUIPO"
       << right << setw(6) << "PJ" << setw(6) << "GOL" << setw(6) << "AST"
       << setw(12) << "GOL/PART";
    return os.str();
#endif
}

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
    cout << "   ESTADISTICA DEPORTIVA - TABLA DE GOLEADORES (std::format)       " << endl;
    cout << "===================================================================" << endl;

    cout << encabezado() << endl;
    cout << string(67, '-') << endl;

    int sumaGoles = 0, sumaAsist = 0;
    for (int i = 0; i < TOTAL; i++) {
        double promedio = (double)tabla[i].goles / tabla[i].partidos;
        cout << fila(i + 1, tabla[i].nombre, tabla[i].equipo,
                     tabla[i].partidos, tabla[i].goles,
                     tabla[i].asistencias, promedio) << endl;

        sumaGoles += tabla[i].goles;
        sumaAsist += tabla[i].asistencias;
    }

    cout << string(67, '-') << endl;
    cout << filaTotales(sumaGoles, sumaAsist) << endl;
    cout << "===================================================================" << endl;

    return 0;
}
