#ifndef LISTAENLAZADA_H
#define LISTAENLAZADA_H

#include <QTextStream>
#include <QString>
#include <stdexcept>

template <class T>
class ListaEnlazada {
    struct Nodo {
        T dato;
        Nodo *sig;
        Nodo(const T &d, Nodo *s = nullptr) : dato(d), sig(s) {}
    };

    Nodo *cabeza = nullptr;
    Nodo *cola   = nullptr;
    int   n      = 0;

public:
    ListaEnlazada() = default;
    ~ListaEnlazada() { limpiar(); }

    ListaEnlazada(const ListaEnlazada &o) {
        for (Nodo *p = o.cabeza; p; p = p->sig) insertarFinal(p->dato);
    }
    ListaEnlazada &operator=(const ListaEnlazada &o) {
        if (this != &o) {
            limpiar();
            for (Nodo *p = o.cabeza; p; p = p->sig) insertarFinal(p->dato);
        }
        return *this;
    }

    void insertarInicio(const T &d) {
        cabeza = new Nodo(d, cabeza);
        if (!cola) cola = cabeza;
        ++n;
    }

    void insertarFinal(const T &d) {
        Nodo *nuevo = new Nodo(d);
        if (cola) cola->sig = nuevo;
        else      cabeza = nuevo;
        cola = nuevo;
        ++n;
    }

    void insertarOrdenado(const T &d) {
        if (!cabeza || d < cabeza->dato) { insertarInicio(d); return; }
        Nodo *p = cabeza;
        while (p->sig && !(d < p->sig->dato)) p = p->sig;
        p->sig = new Nodo(d, p->sig);
        if (p == cola) cola = p->sig;
        ++n;
    }


    bool eliminar(const T &d) {
        Nodo *ant = nullptr, *p = cabeza;
        while (p && !(p->dato == d)) { ant = p; p = p->sig; }
        if (!p) return false;
        if (ant) ant->sig = p->sig;
        else     cabeza   = p->sig;
        if (p == cola) cola = ant;
        delete p;
        --n;
        return true;
    }

    bool contiene(const T &d) const {
        for (Nodo *p = cabeza; p; p = p->sig)
            if (p->dato == d) return true;
        return false;
    }

    const T &en(int i) const {
        if (i < 0 || i >= n) throw std::out_of_range("indice fuera de rango");
        Nodo *p = cabeza;
        while (i--) p = p->sig;
        return p->dato;
    }

    int  tamano() const { return n; }
    bool vacia()  const { return n == 0; }

    void limpiar() {
        while (cabeza) {
            Nodo *t = cabeza;
            cabeza = cabeza->sig;
            delete t;
        }
        cola = nullptr;
        n = 0;
    }

    template <class F>
    void recorrer(F f) const {
        for (Nodo *p = cabeza; p; p = p->sig) f(p->dato);
    }

    void imprimir(QTextStream &out, const QString &sep = " -> ") const {
        out << "[";
        for (Nodo *p = cabeza; p; p = p->sig) {
            out << p->dato;
            if (p->sig) out << sep;
        }
        out << "]" << Qt::endl;
    }
};

#endif
