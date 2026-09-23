#include <iostream>
#include <string>
#include <vector>
using namespace std;

// ================= Clase base =================
class Coronavirus {
protected:
    string nombre;
    string linaje;          // nomenclatura Pango
    string paisDeteccion;
    int anioDeteccion;
    vector<string> mutaciones;   // mutaciones clave en la proteina Spike

    void agregarMutacion(const string& m) {
        for (const string& x : mutaciones)
            if (x == m) return;          // evita duplicados al combinar cepas
        mutaciones.push_back(m);
    }

public:
    Coronavirus(const string& nombre, const string& linaje,
                const string& pais, int anio)
        : nombre(nombre), linaje(linaje), paisDeteccion(pais), anioDeteccion(anio) {}

    virtual ~Coronavirus() {}

    string getNombre() const { return nombre; }

    // Transmisibilidad relativa a la cepa original de Wuhan
    virtual double transmisibilidad() const { return 1.0; }
    virtual string descripcion() const { return "Cepa original de SARS-CoV-2."; }

    void mostrar() const {
        cout << "Variante: " << nombre << " (" << linaje << ")" << endl;
        cout << "  Detectada en: " << paisDeteccion << ", " << anioDeteccion << endl;
        cout << "  Transmisibilidad relativa: x" << transmisibilidad() << endl;
        cout << "  Mutaciones Spike: ";
        if (mutaciones.empty()) cout << "(referencia)";
        for (size_t i = 0; i < mutaciones.size(); i++)
            cout << mutaciones[i] << (i + 1 < mutaciones.size() ? ", " : "");
        cout << endl << "  " << descripcion() << endl << endl;
    }
};

// ================= Herencia simple =================
class Alfa : public Coronavirus {
public:
    Alfa() : Coronavirus("Alfa", "B.1.1.7", "Reino Unido", 2020) {
        agregarMutacion("del69-70"); agregarMutacion("N501Y");
        agregarMutacion("P681H");    agregarMutacion("D614G");
    }
    double transmisibilidad() const override { return 1.5; }
    string descripcion() const override { return "Mayor transmisibilidad que la cepa original."; }
};

class Beta : public Coronavirus {
public:
    Beta() : Coronavirus("Beta", "B.1.351", "Sudafrica", 2020) {
        agregarMutacion("K417N"); agregarMutacion("E484K");
        agregarMutacion("N501Y"); agregarMutacion("D614G");
    }
    double transmisibilidad() const override { return 1.3; }
    string descripcion() const override { return "Escape parcial a anticuerpos (E484K)."; }
};

class Gamma : public Coronavirus {
public:
    Gamma() : Coronavirus("Gamma", "P.1", "Brasil", 2020) {
        agregarMutacion("K417T"); agregarMutacion("E484K");
        agregarMutacion("N501Y"); agregarMutacion("D614G"); agregarMutacion("H655Y");
    }
    double transmisibilidad() const override { return 1.7; }
    string descripcion() const override { return "Asociada a reinfecciones en Manaos."; }
};

// ================= Clases que participan en el diamante =================
class Delta : virtual public Coronavirus {
protected:
    string severidad;
public:
    Delta() : Coronavirus("Delta", "B.1.617.2", "India", 2020), severidad("Alta") {
        agregarMutacion("L452R"); agregarMutacion("T478K");
        agregarMutacion("P681R"); agregarMutacion("D614G");
    }
    string getSeveridad() const { return severidad; }
    double transmisibilidad() const override { return 2.4; }
    string descripcion() const override { return "Alta carga viral y mayor riesgo de hospitalizacion."; }
};

class Omicron : virtual public Coronavirus {
protected:
    string escapeInmune;
public:
    Omicron() : Coronavirus("Omicron", "B.1.1.529", "Sudafrica/Botsuana", 2021), escapeInmune("Alto") {
        agregarMutacion("K417N"); agregarMutacion("N440K"); agregarMutacion("T478K");
        agregarMutacion("E484A"); agregarMutacion("N501Y"); agregarMutacion("P681H");
        agregarMutacion("D614G");
    }
    string getEscapeInmune() const { return escapeInmune; }
    double transmisibilidad() const override { return 3.5; }
    string descripcion() const override { return "Gran escape inmune; cuadros generalmente mas leves."; }
};

// ================= Herencia multiple =================
// Recombinante XD: esqueleto genetico de Delta + Spike de Omicron BA.1
class Deltacron : public Delta, public Omicron {
public:
    // Con herencia virtual, la clase mas derivada construye la base comun.
    Deltacron() : Coronavirus("Deltacron", "XD", "Francia", 2022), Delta(), Omicron() {}

    // Delta y Omicron sobrescriben estos metodos: hay que resolver la ambiguedad.
    double transmisibilidad() const override {
        return (Delta::transmisibilidad() + Omicron::transmisibilidad()) / 2.0;
    }
    string descripcion() const override {
        return "Recombinante: hereda severidad de Delta y escape inmune de Omicron.";
    }
};

// ================= Programa principal =================
int main() {
    vector<Coronavirus*> cepas;
    cepas.push_back(new Coronavirus("Original", "B", "China", 2019));
    cepas.push_back(new Alfa());
    cepas.push_back(new Beta());
    cepas.push_back(new Gamma());
    cepas.push_back(new Delta());
    cepas.push_back(new Omicron());
    cepas.push_back(new Deltacron());

    cout << "=== Cepas del SARS-CoV-2 ===" << endl << endl;
    for (Coronavirus* c : cepas) c->mostrar();

    cout << "=== Herencia multiple en Deltacron ===" << endl;
    Deltacron dc;
    cout << "  Severidad (heredada de Delta):     " << dc.getSeveridad() << endl;
    cout << "  Escape inmune (heredado de Omicron): " << dc.getEscapeInmune() << endl;

    Delta* comoDelta = &dc;
    Omicron* comoOmicron = &dc;
    Coronavirus* baseDesdeDelta = comoDelta;
    Coronavirus* baseDesdeOmicron = comoOmicron;
    cout << "  Una sola copia de Coronavirus (herencia virtual): "
         << (baseDesdeDelta == baseDesdeOmicron ? "SI" : "NO") << endl;

    for (Coronavirus* c : cepas) delete c;
    return 0;
}