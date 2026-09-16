// ============================================================
//  EJERCICIO 5 - Declaracion de la CLASE CitaMedica
// ============================================================
#ifndef CITAMEDICA_H
#define CITAMEDICA_H

#include <string>

class CitaMedica {
private:
    // ---------------- Atributos privados ----------------
    int         idCita;
    std::string numeroAsegurado;
    std::string nombrePaciente;
    std::string dniPaciente;
    int         edadPaciente;
    std::string fecha;            // dd/mm/aaaa
    std::string hora;             // hh:mm
    std::string especialidad;
    std::string tipoAtencion;     // Consulta / Control / Emergencia
    std::string medicoAsignado;
    int         consultorio;
    std::string estado;           // PENDIENTE / ATENDIDA / CANCELADA
    double      costoConsulta;

    // metodo auxiliar privado: solo lo usa la propia clase
    double obtenerFactorCobertura() const;

public:
    // ---------------- Constructores y destructor ----------------
    CitaMedica();                                   // por defecto
    CitaMedica(int id, const std::string &asegurado, const std::string &paciente,
               const std::string &dni, int edad, const std::string &f,
               const std::string &h, const std::string &esp,
               const std::string &tipo, const std::string &medico,
               int consult, double costo);          // parametrizado
    ~CitaMedica();                                  // destructor

    // ---------------- Metodos get (accesores) ----------------
    int         getIdCita() const;
    std::string getNumeroAsegurado() const;
    std::string getNombrePaciente() const;
    std::string getEstado() const;
    std::string getTipoAtencion() const;
    double      getCostoConsulta() const;

    // ---------------- Metodos set (mutadores) ----------------
    void setIdCita(int id);
    void setNombrePaciente(const std::string &nombre);
    void setEstado(const std::string &nuevoEstado);
    void setCostoConsulta(double costo);

    // ---------------- Metodos de comportamiento ----------------
    void   registrarCita(int nuevoId);                   // pide datos por consola
    void   mostrarCita() const;                          // ficha completa
    void   mostrarFila() const;                          // fila de la tabla
    double calcularCostoFinal() const;                   // costo con cobertura
    bool   esUrgente() const;                            // true si es Emergencia
    void   reprogramar(const std::string &f, const std::string &h);
    void   cancelarCita(const std::string &motivo);
    void   atenderCita();

    // ---------------- Metodo estatico ----------------
    static void imprimirEncabezado();                    // cabecera del listado
};

#endif // CITAMEDICA_H
