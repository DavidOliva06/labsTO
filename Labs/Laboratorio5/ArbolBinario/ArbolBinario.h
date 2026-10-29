#ifndef ARBOLBINARIO_H
#define ARBOLBINARIO_H

#include <QTextStream>
#include <QString>
#include <queue>
#include <type_traits>
#include <stdexcept>

template <class T>
class ArbolBinario {
    static_assert(std::is_arithmetic<T>::value,
                  "ArbolBinario<T> solo admite tipos numericos o caracteres");

    struct Nodo {
        T dato;
        Nodo *izq = nullptr;
        Nodo *der = nullptr;
        explicit Nodo(const T &d) : dato(d) {}
    };

    Nodo *raiz = nullptr;
    int   n    = 0;

    static Nodo *copiar(const Nodo *p) {
        if (!p) return nullptr;
        Nodo *q = new Nodo(p->dato);
        q->izq = copiar(p->izq);
        q->der = copiar(p->der);
        return q;
    }

    static void destruir(Nodo *p) {
        if (!p) return;
        destruir(p->izq);
        destruir(p->der);
        delete p;
    }

    bool insertar(Nodo *&p, const T &d) {
        if (!p)          { p = new Nodo(d); ++n; return true; }
        if (d < p->dato) return insertar(p->izq, d);
        if (p->dato < d) return insertar(p->der, d);
        return false;
    }

    bool eliminar(Nodo *&p, const T &d) {
        if (!p) return false;
        if (d < p->dato) return eliminar(p->izq, d);
        if (p->dato < d) return eliminar(p->der, d);

        if (p->izq && p->der) {
            Nodo *s = p->der;
            while (s->izq) s = s->izq;
            p->dato = s->dato;
            return eliminar(p->der, s->dato);
        }
        Nodo *borrar = p;
        p = p->izq ? p->izq : p->der;
        delete borrar;
        --n;
        return true;
    }

    static int altura(const Nodo *p) {
        if (!p) return 0;
        int a = altura(p->izq), b = altura(p->der);
        return 1 + (a > b ? a : b);
    }

    static int hojas(const Nodo *p) {
        if (!p) return 0;
        if (!p->izq && !p->der) return 1;
        return hojas(p->izq) + hojas(p->der);
    }

    template <class F> static void inorden(const Nodo *p, F &f) {
        if (!p) return;
        inorden(p->izq, f); f(p->dato); inorden(p->der, f);
    }
    template <class F> static void preorden(const Nodo *p, F &f) {
        if (!p) return;
        f(p->dato); preorden(p->izq, f); preorden(p->der, f);
    }
    template <class F> static void postorden(const Nodo *p, F &f) {
        if (!p) return;
        postorden(p->izq, f); postorden(p->der, f); f(p->dato);
    }

    static void dibujar(QTextStream &out, const Nodo *p,
                        const QString &prefijo, bool esIzq, bool esRaiz) {
        if (!p) return;
        dibujar(out, p->der, prefijo + (esRaiz ? "" : (esIzq ? "|   " : "    ")), false, false);
        out << prefijo << (esRaiz ? "" : (esIzq ? "\\-- " : "/-- ")) << p->dato << Qt::endl;
        dibujar(out, p->izq, prefijo + (esRaiz ? "" : (esIzq ? "    " : "|   ")), true, false);
    }

public:
    ArbolBinario() = default;
    ~ArbolBinario() { destruir(raiz); }

    // Regla de tres: copia profunda
    ArbolBinario(const ArbolBinario &o) : raiz(copiar(o.raiz)), n(o.n) {}
    ArbolBinario &operator=(const ArbolBinario &o) {
        if (this != &o) { destruir(raiz); raiz = copiar(o.raiz); n = o.n; }
        return *this;
    }

    bool insertar(const T &d) { return insertar(raiz, d); }
    bool eliminar(const T &d) { return eliminar(raiz, d); }

    bool buscar(const T &d) const {
        const Nodo *p = raiz;
        while (p) {
            if (d < p->dato)      p = p->izq;
            else if (p->dato < d) p = p->der;
            else                  return true;
        }
        return false;
    }

    const T &minimo() const {
        if (!raiz) throw std::runtime_error("arbol vacio");
        const Nodo *p = raiz;
        while (p->izq) p = p->izq;
        return p->dato;
    }

    const T &maximo() const {
        if (!raiz) throw std::runtime_error("arbol vacio");
        const Nodo *p = raiz;
        while (p->der) p = p->der;
        return p->dato;
    }

    int  tamano() const { return n; }
    int  altura() const { return altura(raiz); }
    int  hojas()  const { return hojas(raiz); }
    bool vacio()  const { return raiz == nullptr; }
    void limpiar()      { destruir(raiz); raiz = nullptr; n = 0; }

    // Recorridos con función/lambda
    template <class F> void recorrerInorden(F f)   const { inorden(raiz, f); }
    template <class F> void recorrerPreorden(F f)  const { preorden(raiz, f); }
    template <class F> void recorrerPostorden(F f) const { postorden(raiz, f); }

    template <class F> void recorrerPorNiveles(F f) const {
        if (!raiz) return;
        std::queue<const Nodo *> q;
        q.push(raiz);
        while (!q.empty()) {
            const Nodo *p = q.front(); q.pop();
            f(p->dato);
            if (p->izq) q.push(p->izq);
            if (p->der) q.push(p->der);
        }
    }

    // Impresión
    enum Orden { Inorden, Preorden, Postorden, Niveles };

    void imprimir(QTextStream &out, Orden o = Inorden) const {
        bool primero = true;
        auto f = [&](const T &d) { out << (primero ? "" : " ") << d; primero = false; };
        out << "[";
        switch (o) {
        case Inorden:   recorrerInorden(f);    break;
        case Preorden:  recorrerPreorden(f);   break;
        case Postorden: recorrerPostorden(f);  break;
        case Niveles:   recorrerPorNiveles(f); break;
        }
        out << "]" << Qt::endl;
    }

    // Dibuja el árbol girado 90° (la raíz a la izquierda, derecha arriba)
    void dibujar(QTextStream &out) const {
        if (!raiz) { out << "(vacio)" << Qt::endl; return; }
        dibujar(out, raiz, "", false, true);
    }
};

#endif // ARBOLBINARIO_H
