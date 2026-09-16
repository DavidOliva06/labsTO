// ============================================================
//  EJERCICIO 4
//  Citas medicas implementadas con ESTRUCTURA (struct) y
//  mas de 02 metodos dentro de la propia estructura.
// ============================================================
#include <iostream>
#include <iomanip>
#include <string>
#include <limits>

using namespace std;

const int MAX_CITAS = 50;

// ------------------------------------------------------------
// Utilitario: leer una linea completa (permite nombres con espacios)
// ------------------------------------------------------------
string leerLinea(const string &mensaje) {
    string texto;
    cout << mensaje;
    getline(cin, texto);
    while (texto.empty()) {                 // no aceptar vacio
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

// ============================================================
//  ESTRUCTURA CitaMedica
// ============================================================
struct CitaMedica {
    // ---------------- Atributos (publicos) ----------------
    int    idCita;
    string numeroAsegurado;
    string nombrePaciente;
    string dniPaciente;
    int    edadPaciente;
    string fecha;            // dd/mm/aaaa
    string hora;             // hh:mm
    string especialidad;
    string tipoAtencion;     // Consulta / Control / Emergencia
    string medicoAsignado;
    int    consultorio;
    string estado;           // PENDIENTE / ATENDIDA / CANCELADA
    double costoConsulta;

    // ---------------- METODO 1: registrar por consola ----------------
    void registrarCita(int nuevoId) {
        idCita = nuevoId;
        cout << endl << "--- REGISTRO DE CITA N. " << idCita << " ---" << endl;
        numeroAsegurado = leerLinea("Numero de asegurado : ");
        nombrePaciente  = leerLinea("Nombre del paciente : ");
        dniPaciente     = leerLinea("DNI del paciente    : ");
        edadPaciente    = leerEntero("Edad del paciente   : ");
        fecha           = leerLinea("Fecha (dd/mm/aaaa)  : ");
        hora            = leerLinea("Hora  (hh:mm)       : ");
        especialidad    = leerLinea("Especialidad        : ");

        int op = 0;
        while (op < 1 || op > 3) {
            op = leerEntero("Tipo (1=Consulta 2=Control 3=Emergencia): ");
        }
        if      (op == 1) tipoAtencion = "Consulta";
        else if (op == 2) tipoAtencion = "Control";
        else              tipoAtencion = "Emergencia";

        medicoAsignado = leerLinea("Medico asignado     : ");
        consultorio    = leerEntero("Consultorio         : ");
        costoConsulta  = leerDecimal("Costo base (S/.)    : ");
        estado         = "PENDIENTE";

        cout << ">> Cita registrada correctamente." << endl;
    }

    // ---------------- METODO 2: mostrar la ficha completa ----------------
    void mostrarCita() const {
        cout << "-------------------------------------------------" << endl;
        cout << " CITA N. " << idCita << "   [" << estado << "]" << endl;
        cout << "-------------------------------------------------" << endl;
        cout << " Asegurado   : " << numeroAsegurado << endl;
        cout << " Paciente    : " << nombrePaciente << " (DNI " << dniPaciente
             << ", " << edadPaciente << " anios)" << endl;
        cout << " Fecha/Hora  : " << fecha << "  " << hora << endl;
        cout << " Especialidad: " << especialidad << endl;
        cout << " Atencion    : " << tipoAtencion;
        if (esUrgente()) cout << "  <-- URGENTE";
        cout << endl;
        cout << " Medico      : " << medicoAsignado
             << "   Consultorio: " << consultorio << endl;
        cout << fixed << setprecision(2);
        cout << " Costo base  : S/. " << costoConsulta << endl;
        cout << " Costo final : S/. " << calcularCostoFinal() << endl;
        cout << "-------------------------------------------------" << endl;
    }

    // ---------------- METODO 3: mostrar como fila de tabla ----------------
    void mostrarFila() const {
        cout << fixed << setprecision(2);
        cout << setw(5)  << idCita
             << setw(14) << numeroAsegurado
             << setw(24) << nombrePaciente
             << setw(14) << fecha
             << setw(8)  << hora
             << setw(16) << especialidad
             << setw(13) << tipoAtencion
             << setw(12) << estado
             << setw(11) << calcularCostoFinal() << endl;
    }

    // ---------------- METODO 4: calcular el costo con cobertura ----------------
    double calcularCostoFinal() const {
        double factor;
        if      (tipoAtencion == "Emergencia") factor = 1.00;   // el seguro cubre 0%
        else if (tipoAtencion == "Consulta")   factor = 0.70;   // el seguro cubre 30%
        else                                   factor = 0.50;   // Control: cubre 50%

        double total = costoConsulta * factor;
        if (edadPaciente >= 65) total = total * 0.90;           // adulto mayor -10%
        return total;
    }

    // ---------------- METODO 5: saber si es urgente ----------------
    bool esUrgente() const {
        return tipoAtencion == "Emergencia";
    }

    // ---------------- METODO 6: reprogramar ----------------
    void reprogramar(const string &nuevaFecha, const string &nuevaHora) {
        if (estado != "PENDIENTE") {
            cout << ">> No se puede reprogramar: la cita esta " << estado << "." << endl;
            return;
        }
        fecha = nuevaFecha;
        hora  = nuevaHora;
        cout << ">> Cita " << idCita << " reprogramada para el "
             << fecha << " a las " << hora << "." << endl;
    }

    // ---------------- METODO 7: cancelar ----------------
    void cancelarCita(const string &motivo) {
        if (estado != "PENDIENTE") {
            cout << ">> No se puede cancelar: la cita esta " << estado << "." << endl;
            return;
        }
        estado = "CANCELADA";
        cout << ">> Cita " << idCita << " cancelada. Motivo: " << motivo << endl;
    }

    // ---------------- METODO 8: marcar como atendida ----------------
    void atenderCita() {
        if (estado != "PENDIENTE") {
            cout << ">> La cita ya esta " << estado << "." << endl;
            return;
        }
        estado = "ATENDIDA";
        cout << ">> Cita " << idCita << " marcada como ATENDIDA." << endl;
    }
};

// ------------------------------------------------------------
// Encabezado del listado (alineado con setw)
// ------------------------------------------------------------
void imprimirEncabezado() {
    cout << setw(5)  << "ID"    << setw(14) << "ASEGURADO" << setw(24) << "PACIENTE"
         << setw(14) << "FECHA" << setw(8)  << "HORA"      << setw(16) << "ESPECIALIDAD"
         << setw(13) << "TIPO"  << setw(12) << "ESTADO"    << setw(11) << "COSTO" << endl;
    cout << string(117, '-') << endl;
}

// ------------------------------------------------------------
// Datos de prueba para no empezar con la agenda vacia
// ------------------------------------------------------------
int cargarDemo(CitaMedica citas[]) {
    citas[0] = {1, "AS-100234", "Maria Quispe Rojas", "45871236", 68,
                "15/09/2026", "08:30", "Cardiologia", "Consulta",
                "Dr. Luis Vargas", 12, "PENDIENTE", 120.00};

    citas[1] = {2, "AS-100987", "Jorge Ramos Diaz", "70012345", 34,
                "15/09/2026", "09:15", "Traumatologia", "Emergencia",
                "Dra. Ana Soto", 3, "PENDIENTE", 250.00};

    citas[2] = {3, "AS-100555", "Lucia Torres Mena", "61239874", 27,
                "16/09/2026", "11:00", "Pediatria", "Control",
                "Dr. Pedro Nieto", 7, "ATENDIDA", 80.00};
    return 3;
}

int main() {
    CitaMedica citas[MAX_CITAS];
    int total = cargarDemo(citas);
    int opcion;

    do {
        cout << endl;
        cout << "=================================================" << endl;
        cout << "  EJERCICIO 4 - CITAS MEDICAS (con STRUCT)       " << endl;
        cout << "=================================================" << endl;
        cout << " 1. Registrar nueva cita" << endl;
        cout << " 2. Listar todas las citas" << endl;
        cout << " 3. Ver ficha detallada de una cita" << endl;
        cout << " 4. Atender una cita" << endl;
        cout << " 5. Cancelar una cita" << endl;
        cout << " 6. Reprogramar una cita" << endl;
        cout << " 7. Listar solo las urgencias" << endl;
        cout << " 0. Salir" << endl;
        opcion = leerEntero("Opcion: ");

        if (opcion == 1) {
            if (total >= MAX_CITAS) {
                cout << ">> Agenda llena." << endl;
            } else {
                citas[total].registrarCita(total + 1);
                total++;
            }

        } else if (opcion == 2) {
            cout << endl << "LISTADO GENERAL DE CITAS" << endl;
            imprimirEncabezado();
            for (int i = 0; i < total; i++) citas[i].mostrarFila();

        } else if (opcion == 3) {
            int id = leerEntero("ID de la cita: ");
            if (id >= 1 && id <= total) citas[id - 1].mostrarCita();
            else cout << ">> ID no existe." << endl;

        } else if (opcion == 4) {
            int id = leerEntero("ID de la cita a atender: ");
            if (id >= 1 && id <= total) citas[id - 1].atenderCita();
            else cout << ">> ID no existe." << endl;

        } else if (opcion == 5) {
            int id = leerEntero("ID de la cita a cancelar: ");
            if (id >= 1 && id <= total) {
                string motivo = leerLinea("Motivo: ");
                citas[id - 1].cancelarCita(motivo);
            } else cout << ">> ID no existe." << endl;

        } else if (opcion == 6) {
            int id = leerEntero("ID de la cita a reprogramar: ");
            if (id >= 1 && id <= total) {
                string f = leerLinea("Nueva fecha (dd/mm/aaaa): ");
                string h = leerLinea("Nueva hora  (hh:mm)     : ");
                citas[id - 1].reprogramar(f, h);
            } else cout << ">> ID no existe." << endl;

        } else if (opcion == 7) {
            cout << endl << "CITAS DE EMERGENCIA" << endl;
            imprimirEncabezado();
            int encontradas = 0;
            for (int i = 0; i < total; i++) {
                if (citas[i].esUrgente()) {
                    citas[i].mostrarFila();
                    encontradas++;
                }
            }
            if (encontradas == 0) cout << "  (no hay citas de emergencia)" << endl;

        } else if (opcion != 0) {
            cout << ">> Opcion no valida." << endl;
        }

    } while (opcion != 0);

    cout << endl << "Programa finalizado. Hasta pronto." << endl;
    return 0;
}
