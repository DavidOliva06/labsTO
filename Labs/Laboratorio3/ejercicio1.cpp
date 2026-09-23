#include <iostream>
#include <string>
#include <vector>
using namespace std;

// ================= Clase base =================
class Persona {
protected:
    string nombre;
    int edad;
    string dni;

public:
    Persona(const string& nombre, int edad, const string& dni)
        : nombre(nombre), edad(edad), dni(dni) {}

    virtual ~Persona() {}

    string getNombre() const { return nombre; }

    // Metodos virtuales puros: cada oficio los implementa a su manera
    virtual string oficio() const = 0;
    virtual void trabajar() const = 0;

    virtual void mostrarDatos() const {
        cout << "[" << oficio() << "] " << nombre
             << " | Edad: " << edad << " | DNI: " << dni << endl;
    }
};

// ================= Clases derivadas =================
class Arquitecto : public Persona {
private:
    string registroCAP;
    int proyectos;

public:
    Arquitecto(const string& nombre, int edad, const string& dni,
               const string& registroCAP, int proyectos)
        : Persona(nombre, edad, dni), registroCAP(registroCAP), proyectos(proyectos) {}

    string oficio() const override { return "Arquitecto"; }

    void trabajar() const override {
        cout << "  " << nombre << " elabora planos y supervisa obras." << endl;
    }

    void elaborarPlano(const string& obra) {
        proyectos++;
        cout << "  " << nombre << " elaboro el plano de: " << obra
             << " (proyectos: " << proyectos << ")" << endl;
    }

    void mostrarDatos() const override {
        Persona::mostrarDatos();
        cout << "  Registro CAP: " << registroCAP << " | Proyectos: " << proyectos << endl;
    }
};

class Doctor : public Persona {
private:
    string especialidad;
    string registroCMP;

public:
    Doctor(const string& nombre, int edad, const string& dni,
           const string& especialidad, const string& registroCMP)
        : Persona(nombre, edad, dni), especialidad(especialidad), registroCMP(registroCMP) {}

    string oficio() const override { return "Doctor"; }

    void trabajar() const override {
        cout << "  " << nombre << " atiende pacientes en " << especialidad << "." << endl;
    }

    void diagnosticar(const string& paciente, const string& diagnostico) const {
        cout << "  Dr(a). " << nombre << " diagnostica a " << paciente
             << ": " << diagnostico << endl;
    }

    void mostrarDatos() const override {
        Persona::mostrarDatos();
        cout << "  Especialidad: " << especialidad << " | CMP: " << registroCMP << endl;
    }
};

class Enfermera : public Persona {
private:
    string area;
    string turno;

public:
    Enfermera(const string& nombre, int edad, const string& dni,
              const string& area, const string& turno)
        : Persona(nombre, edad, dni), area(area), turno(turno) {}

    string oficio() const override { return "Enfermera"; }

    void trabajar() const override {
        cout << "  " << nombre << " cuida pacientes en " << area
             << " (turno " << turno << ")." << endl;
    }

    void administrarMedicamento(const string& paciente, const string& medicamento) const {
        cout << "  " << nombre << " administra " << medicamento << " a " << paciente << endl;
    }

    void mostrarDatos() const override {
        Persona::mostrarDatos();
        cout << "  Area: " << area << " | Turno: " << turno << endl;
    }
};

class Bombero : public Persona {
private:
    string rango;
    int compania;
    int emergencias;

public:
    Bombero(const string& nombre, int edad, const string& dni,
            const string& rango, int compania)
        : Persona(nombre, edad, dni), rango(rango), compania(compania), emergencias(0) {}

    string oficio() const override { return "Bombero"; }

    void trabajar() const override {
        cout << "  " << nombre << " atiende incendios y rescates." << endl;
    }

    void apagarIncendio(const string& lugar) {
        emergencias++;
        cout << "  " << rango << " " << nombre << " controla un incendio en " << lugar
             << " (emergencias atendidas: " << emergencias << ")" << endl;
    }

    void mostrarDatos() const override {
        Persona::mostrarDatos();
        cout << "  Rango: " << rango << " | Compania N. " << compania << endl;
    }
};

// ================= Programa principal =================
int main() {
    vector<Persona*> personas;
    personas.push_back(new Arquitecto("Carlos Rivera", 45, "40123456", "CAP-10234", 12));
    personas.push_back(new Doctor("Ana Torres", 38, "41234567", "Neumologia", "CMP-55821"));
    personas.push_back(new Enfermera("Lucia Quispe", 29, "72345678", "UCI", "noche"));
    personas.push_back(new Bombero("Miguel Flores", 33, "45678901", "Teniente", 19));

    cout << "=== Polimorfismo: datos y trabajo de cada persona ===" << endl;
    for (Persona* p : personas) {
        p->mostrarDatos();
        p->trabajar();
        cout << endl;
    }

    cout << "=== Metodos propios de cada oficio (dynamic_cast) ===" << endl;
    for (Persona* p : personas) {
        if (Arquitecto* a = dynamic_cast<Arquitecto*>(p))
            a->elaborarPlano("Hospital Regional");
        else if (Doctor* d = dynamic_cast<Doctor*>(p))
            d->diagnosticar("Juan Perez", "neumonia");
        else if (Enfermera* e = dynamic_cast<Enfermera*>(p))
            e->administrarMedicamento("Juan Perez", "amoxicilina");
        else if (Bombero* b = dynamic_cast<Bombero*>(p))
            b->apagarIncendio("Av. Ejercito");
    }

    for (Persona* p : personas) delete p;
    return 0;
}
