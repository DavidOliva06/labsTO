// ============================================================
//  EJERCICIO 5 - Implementacion de la CLASE CitaMedica
// ============================================================
#include "CitaMedica.h"
#include "Utilidades.h"

#include <iostream>
#include <iomanip>

using namespace std;

// ------------------------------------------------------------
// Constructor por defecto: deja la cita en un estado valido
// ------------------------------------------------------------
CitaMedica::CitaMedica() {
    idCita          = 0;
    numeroAsegurado = "SIN-ASIGNAR";
    nombrePaciente  = "";
    dniPaciente     = "";
    edadPaciente    = 0;
    fecha           = "00/00/0000";
    hora            = "00:00";
    especialidad    = "Medicina General";
    tipoAtencion    = "Consulta";
    medicoAsignado  = "Por asignar";
    consultorio     = 0;
    estado          = "PENDIENTE";
    costoConsulta   = 0.0;
}

// ------------------------------------------------------------
// Constructor parametrizado
// ------------------------------------------------------------
CitaMedica::CitaMedica(int id, const string &asegurado, const string &paciente,
                       const string &dni, int edad, const string &f,
                       const string &h, const string &esp,
                       const string &tipo, const string &medico,
                       int consult, double costo) {
    idCita          = id;
    numeroAsegurado = asegurado;
    nombrePaciente  = paciente;
    dniPaciente     = dni;
    edadPaciente    = edad;
    fecha           = f;
    hora            = h;
    especialidad    = esp;
    tipoAtencion    = tipo;
    medicoAsignado  = medico;
    consultorio     = consult;
    estado          = "PENDIENTE";
    costoConsulta   = costo;
}

// ------------------------------------------------------------
// Destructor
// ------------------------------------------------------------
CitaMedica::~CitaMedica() {
    // No hay memoria dinamica que liberar en esta version.
}

// ================= METODOS GET =================
int    CitaMedica::getIdCita() const           { return idCita; }
string CitaMedica::getNumeroAsegurado() const  { return numeroAsegurado; }
string CitaMedica::getNombrePaciente() const   { return nombrePaciente; }
string CitaMedica::getEstado() const           { return estado; }
string CitaMedica::getTipoAtencion() const     { return tipoAtencion; }
double CitaMedica::getCostoConsulta() const    { return costoConsulta; }

// ================= METODOS SET =================
void CitaMedica::setIdCita(int id) {
    if (id > 0) idCita = id;
}

void CitaMedica::setNombrePaciente(const string &nombre) {
    if (!nombre.empty()) nombrePaciente = nombre;
}

void CitaMedica::setEstado(const string &nuevoEstado) {
    // el set valida: solo se aceptan los 3 estados del negocio
    if (nuevoEstado == "PENDIENTE" || nuevoEstado == "ATENDIDA" ||
        nuevoEstado == "CANCELADA") {
        estado = nuevoEstado;
    } else {
        cout << ">> Estado invalido, se mantiene " << estado << "." << endl;
    }
}

void CitaMedica::setCostoConsulta(double costo) {
    if (costo >= 0) costoConsulta = costo;
}

// ------------------------------------------------------------
// Metodo privado: porcentaje que paga el paciente segun el tipo
// ------------------------------------------------------------
double CitaMedica::obtenerFactorCobertura() const {
    if (tipoAtencion == "Emergencia") return 1.00;   // el seguro cubre 0%
    if (tipoAtencion == "Consulta")   return 0.70;   // el seguro cubre 30%
    return 0.50;                                     // Control: cubre 50%
}

// ------------------------------------------------------------
// Registrar la cita solicitando los datos por consola
// ------------------------------------------------------------
void CitaMedica::registrarCita(int nuevoId) {
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

// ------------------------------------------------------------
// Ficha detallada
// ------------------------------------------------------------
void CitaMedica::mostrarCita() const {
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

// ------------------------------------------------------------
// Fila de la tabla (alineada con setw)
// ------------------------------------------------------------
void CitaMedica::mostrarFila() const {
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

// ------------------------------------------------------------
// Encabezado (metodo estatico: no necesita un objeto)
// ------------------------------------------------------------
void CitaMedica::imprimirEncabezado() {
    cout << setw(5)  << "ID"    << setw(14) << "ASEGURADO" << setw(24) << "PACIENTE"
         << setw(14) << "FECHA" << setw(8)  << "HORA"      << setw(16) << "ESPECIALIDAD"
         << setw(13) << "TIPO"  << setw(12) << "ESTADO"    << setw(11) << "COSTO" << endl;
    cout << string(117, '-') << endl;
}

// ------------------------------------------------------------
// Costo final aplicando cobertura y descuento de adulto mayor
// ------------------------------------------------------------
double CitaMedica::calcularCostoFinal() const {
    double total = costoConsulta * obtenerFactorCobertura();
    if (edadPaciente >= 65) total = total * 0.90;    // adulto mayor -10%
    return total;
}

bool CitaMedica::esUrgente() const {
    return tipoAtencion == "Emergencia";
}

// ------------------------------------------------------------
// Reprogramar / cancelar / atender
// ------------------------------------------------------------
void CitaMedica::reprogramar(const string &f, const string &h) {
    if (estado != "PENDIENTE") {
        cout << ">> No se puede reprogramar: la cita esta " << estado << "." << endl;
        return;
    }
    fecha = f;
    hora  = h;
    cout << ">> Cita " << idCita << " reprogramada para el "
         << fecha << " a las " << hora << "." << endl;
}

void CitaMedica::cancelarCita(const string &motivo) {
    if (estado != "PENDIENTE") {
        cout << ">> No se puede cancelar: la cita esta " << estado << "." << endl;
        return;
    }
    setEstado("CANCELADA");
    cout << ">> Cita " << idCita << " cancelada. Motivo: " << motivo << endl;
}

void CitaMedica::atenderCita() {
    if (estado != "PENDIENTE") {
        cout << ">> La cita ya esta " << estado << "." << endl;
        return;
    }
    setEstado("ATENDIDA");
    cout << ">> Cita " << idCita << " marcada como ATENDIDA." << endl;
}
