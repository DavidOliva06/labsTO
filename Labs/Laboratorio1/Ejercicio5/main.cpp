// ============================================================
//  EJERCICIO 5
//  Citas medicas implementadas con CLASES (encapsulamiento,
//  constructores, get/set y metodos de comportamiento).
// ============================================================
#include "CitaMedica.h"
#include "Utilidades.h"

#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

// ------------------------------------------------------------
// Datos de prueba usando el constructor parametrizado
// ------------------------------------------------------------
vector<CitaMedica> cargarDemo() {
    vector<CitaMedica> agenda;

    agenda.push_back(CitaMedica(1, "AS-100234", "Maria Quispe Rojas", "45871236", 68,
                                "15/09/2026", "08:30", "Cardiologia", "Consulta",
                                "Dr. Luis Vargas", 12, 120.00));

    agenda.push_back(CitaMedica(2, "AS-100987", "Jorge Ramos Diaz", "70012345", 34,
                                "15/09/2026", "09:15", "Traumatologia", "Emergencia",
                                "Dra. Ana Soto", 3, 250.00));

    agenda.push_back(CitaMedica(3, "AS-100555", "Lucia Torres Mena", "61239874", 27,
                                "16/09/2026", "11:00", "Pediatria", "Control",
                                "Dr. Pedro Nieto", 7, 80.00));

    agenda[2].atenderCita();   // esta cita ya fue atendida (usa el set validado)
    return agenda;
}

// ------------------------------------------------------------
// Busca la posicion de una cita por su ID; -1 si no existe
// ------------------------------------------------------------
int buscarPorId(const vector<CitaMedica> &agenda, int id) {
    for (size_t i = 0; i < agenda.size(); i++) {
        if (agenda[i].getIdCita() == id) return (int)i;
    }
    return -1;
}

int main() {
    vector<CitaMedica> agenda = cargarDemo();
    int opcion;

    do {
        cout << endl;
        cout << "=================================================" << endl;
        cout << "  EJERCICIO 5 - CITAS MEDICAS (con CLASES)       " << endl;
        cout << "=================================================" << endl;
        cout << " 1. Registrar nueva cita" << endl;
        cout << " 2. Listar todas las citas" << endl;
        cout << " 3. Ver ficha detallada de una cita" << endl;
        cout << " 4. Atender una cita" << endl;
        cout << " 5. Cancelar una cita" << endl;
        cout << " 6. Reprogramar una cita" << endl;
        cout << " 7. Listar solo las urgencias" << endl;
        cout << " 8. Reporte de recaudacion" << endl;
        cout << " 0. Salir" << endl;
        opcion = leerEntero("Opcion: ");

        if (opcion == 1) {
            CitaMedica nueva;                       // constructor por defecto
            nueva.registrarCita((int)agenda.size() + 1);
            agenda.push_back(nueva);

        } else if (opcion == 2) {
            cout << endl << "LISTADO GENERAL DE CITAS" << endl;
            CitaMedica::imprimirEncabezado();       // metodo estatico
            for (size_t i = 0; i < agenda.size(); i++) agenda[i].mostrarFila();

        } else if (opcion == 3) {
            int pos = buscarPorId(agenda, leerEntero("ID de la cita: "));
            if (pos >= 0) agenda[pos].mostrarCita();
            else cout << ">> ID no existe." << endl;

        } else if (opcion == 4) {
            int pos = buscarPorId(agenda, leerEntero("ID de la cita a atender: "));
            if (pos >= 0) agenda[pos].atenderCita();
            else cout << ">> ID no existe." << endl;

        } else if (opcion == 5) {
            int pos = buscarPorId(agenda, leerEntero("ID de la cita a cancelar: "));
            if (pos >= 0) agenda[pos].cancelarCita(leerLinea("Motivo: "));
            else cout << ">> ID no existe." << endl;

        } else if (opcion == 6) {
            int pos = buscarPorId(agenda, leerEntero("ID de la cita a reprogramar: "));
            if (pos >= 0) {
                string f = leerLinea("Nueva fecha (dd/mm/aaaa): ");
                string h = leerLinea("Nueva hora  (hh:mm)     : ");
                agenda[pos].reprogramar(f, h);
            } else cout << ">> ID no existe." << endl;

        } else if (opcion == 7) {
            cout << endl << "CITAS DE EMERGENCIA" << endl;
            CitaMedica::imprimirEncabezado();
            int encontradas = 0;
            for (size_t i = 0; i < agenda.size(); i++) {
                if (agenda[i].esUrgente()) {
                    agenda[i].mostrarFila();
                    encontradas++;
                }
            }
            if (encontradas == 0) cout << "  (no hay citas de emergencia)" << endl;

        } else if (opcion == 8) {
            double recaudado = 0.0;
            int atendidas = 0;
            for (size_t i = 0; i < agenda.size(); i++) {
                if (agenda[i].getEstado() == "ATENDIDA") {
                    recaudado += agenda[i].calcularCostoFinal();
                    atendidas++;
                }
            }
            cout << endl << "REPORTE DE RECAUDACION" << endl;
            cout << "  Citas en agenda   : " << agenda.size() << endl;
            cout << "  Citas atendidas   : " << atendidas << endl;
            cout << fixed << setprecision(2);
            cout << "  Total recaudado   : S/. " << recaudado << endl;

        } else if (opcion != 0) {
            cout << ">> Opcion no valida." << endl;
        }

    } while (opcion != 0);

    cout << endl << "Programa finalizado. Hasta pronto." << endl;
    return 0;
}
