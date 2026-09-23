#include <iostream>
#include <sstream>
#include <string>
#include <cctype>
#include <stdexcept>
using namespace std;

// ================= Nodo abstracto =================
class Nodo {
public:
    virtual ~Nodo() {}
    virtual double evaluar() const = 0;
    virtual string etiqueta() const = 0;
    virtual void preorden() const = 0;
    virtual void inorden() const = 0;
    virtual void postorden() const = 0;
    virtual Nodo* getIzq() const { return nullptr; }
    virtual Nodo* getDer() const { return nullptr; }
};

// ================= Hoja: numero =================
class NodoNumero : public Nodo {
private:
    double valor;
public:
    NodoNumero(double v) : valor(v) {}
    double evaluar() const override { return valor; }
    string etiqueta() const override {
        ostringstream os; os << valor; return os.str();
    }
    void preorden() const override  { cout << etiqueta() << " "; }
    void inorden() const override   { cout << etiqueta() << " "; }
    void postorden() const override { cout << etiqueta() << " "; }
};

// ================= Nodo interno: operador =================
class NodoOperador : public Nodo {
protected:
    Nodo* izq;
    Nodo* der;
public:
    NodoOperador(Nodo* izq, Nodo* der) : izq(izq), der(der) {}
    ~NodoOperador() override { delete izq; delete der; }   // libera el subarbol
    NodoOperador(const NodoOperador&) = delete;
    NodoOperador& operator=(const NodoOperador&) = delete;

    virtual char simbolo() const = 0;
    virtual double operar(double a, double b) const = 0;

    double evaluar() const override { return operar(izq->evaluar(), der->evaluar()); }
    string etiqueta() const override { return string(1, simbolo()); }
    Nodo* getIzq() const override { return izq; }
    Nodo* getDer() const override { return der; }

    void preorden() const override {
        cout << simbolo() << " "; izq->preorden(); der->preorden();
    }
    void inorden() const override {
        cout << "( "; izq->inorden(); cout << simbolo() << " "; der->inorden(); cout << ") ";
    }
    void postorden() const override {
        izq->postorden(); der->postorden(); cout << simbolo() << " ";
    }
};

class NodoSuma : public NodoOperador {
public:
    NodoSuma(Nodo* izq, Nodo* der) : NodoOperador(izq, der) {}
    char simbolo() const override { return '+'; }
    double operar(double a, double b) const override { return a + b; }
};

class NodoMultiplicacion : public NodoOperador {
public:
    NodoMultiplicacion(Nodo* izq, Nodo* der) : NodoOperador(izq, der) {}
    char simbolo() const override { return '*'; }
    double operar(double a, double b) const override { return a * b; }
};

// ================= Arbol de expresion =================
class ArbolExpresion {
private:
    Nodo* raiz;
    string expr;
    size_t pos;

    void saltarEspacios() {
        while (pos < expr.size() && isspace((unsigned char)expr[pos])) pos++;
    }

    Nodo* parsearExpresion() {
        Nodo* izq = parsearTermino();
        saltarEspacios();
        while (pos < expr.size() && expr[pos] == '+') {
            pos++;
            Nodo* der;
            try { der = parsearTermino(); } catch (...) { delete izq; throw; }
            izq = new NodoSuma(izq, der);
            saltarEspacios();
        }
        return izq;
    }

    Nodo* parsearTermino() {
        Nodo* izq = parsearFactor();
        saltarEspacios();
        while (pos < expr.size() && expr[pos] == '*') {
            pos++;
            Nodo* der;
            try { der = parsearFactor(); } catch (...) { delete izq; throw; }
            izq = new NodoMultiplicacion(izq, der);
            saltarEspacios();
        }
        return izq;
    }

    Nodo* parsearFactor() {
        saltarEspacios();
        if (pos >= expr.size())
            throw runtime_error("Expresion incompleta");

        if (expr[pos] == '(') {
            pos++;
            Nodo* n = parsearExpresion();
            saltarEspacios();
            if (pos >= expr.size() || expr[pos] != ')') {
                delete n;
                throw runtime_error("Falta ')'");
            }
            pos++;
            return n;
        }

        if (isdigit((unsigned char)expr[pos]) || expr[pos] == '.') {
            size_t inicio = pos;
            while (pos < expr.size() && (isdigit((unsigned char)expr[pos]) || expr[pos] == '.'))
                pos++;
            string num = expr.substr(inicio, pos - inicio);
            size_t leidos = 0;
            double v;
            try { v = stod(num, &leidos); } catch (...) { leidos = 0; }
            if (leidos != num.size())
                throw runtime_error("Numero invalido: " + num);
            return new NodoNumero(v);
        }

        throw runtime_error(string("Caracter inesperado: '") + expr[pos] + "'");
    }

    void dibujar(const Nodo* n, int nivel) const {
        if (n == nullptr) return;
        dibujar(n->getDer(), nivel + 1);
        cout << string(nivel * 6, ' ') << n->etiqueta() << endl;
        dibujar(n->getIzq(), nivel + 1);
    }

public:
    ArbolExpresion() : raiz(nullptr), pos(0) {}
    explicit ArbolExpresion(Nodo* r) : raiz(r), pos(0) {}
    ~ArbolExpresion() { delete raiz; }
    ArbolExpresion(const ArbolExpresion&) = delete;
    ArbolExpresion& operator=(const ArbolExpresion&) = delete;

    void construir(const string& e) {
        expr = e;
        pos = 0;
        Nodo* nuevo = parsearExpresion();
        saltarEspacios();
        if (pos != expr.size()) {
            delete nuevo;
            throw runtime_error(string("Caracter inesperado: '") + expr[pos] + "'");
        }
        delete raiz;
        raiz = nuevo;
    }

    double evaluar() const {
        if (raiz == nullptr) throw runtime_error("Arbol vacio");
        return raiz->evaluar();
    }

    void mostrar() const {
        if (raiz == nullptr) { cout << "  (arbol vacio)" << endl; return; }
        cout << "  Arbol (rotado 90 grados, raiz a la izquierda):" << endl;
        dibujar(raiz, 1);
        cout << "  Preorden  (prefija):  "; raiz->preorden();  cout << endl;
        cout << "  Inorden   (infija):   "; raiz->inorden();   cout << endl;
        cout << "  Postorden (postfija): "; raiz->postorden(); cout << endl;
        cout << "  Resultado = " << evaluar() << endl << endl;
    }
};

// ================= Programa principal =================
int main() {
    // 1) Arbol armado a mano con punteros: (3 + 4) * 5
    cout << "=== Arbol construido manualmente: (3 + 4) * 5 ===" << endl;
    ArbolExpresion manual(
        new NodoMultiplicacion(
            new NodoSuma(new NodoNumero(3), new NodoNumero(4)),
            new NodoNumero(5)));
    manual.mostrar();

    // 2) Arboles construidos a partir de una cadena
    const string ejemplos[] = { "2 + 3 * 4", "(2 + 3) * 4", "1.5 * (2 + 2) + 10" };
    for (const string& e : ejemplos) {
        cout << "=== Expresion: " << e << " ===" << endl;
        ArbolExpresion a;
        a.construir(e);
        a.mostrar();
    }

    // 3) Modo interactivo
    ArbolExpresion arbol;
    string linea;
    cout << "Ingrese una expresion con + y * (o 'salir'): ";
    while (getline(cin, linea) && linea != "salir") {
        try {
            arbol.construir(linea);
            arbol.mostrar();
        } catch (const exception& ex) {
            cout << "  Error: " << ex.what() << endl << endl;
        }
        cout << "Ingrese una expresion con + y * (o 'salir'): ";
    }
    return 0;
}
