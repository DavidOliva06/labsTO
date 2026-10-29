#include <QCoreApplication>
#include <QTextStream>
#include <initializer_list>
#include "ArbolBinario.h"

template <class T>
void demo(QTextStream &out, const QString &titulo,
          std::initializer_list<T> valores, const T &aEliminar, const T &aBuscar)
{
    out << "========== " << titulo << " ==========" << Qt::endl;

    ArbolBinario<T> arbol;
    for (const T &v : valores)
        if (!arbol.insertar(v))
            out << "Duplicado ignorado: " << v << Qt::endl;

    arbol.dibujar(out);
    out << "Inorden:    "; arbol.imprimir(out, ArbolBinario<T>::Inorden);
    out << "Preorden:   "; arbol.imprimir(out, ArbolBinario<T>::Preorden);
    out << "Postorden:  "; arbol.imprimir(out, ArbolBinario<T>::Postorden);
    out << "Por niveles:"; arbol.imprimir(out, ArbolBinario<T>::Niveles);

    out << "Nodos: " << arbol.tamano() << "  Altura: " << arbol.altura()
        << "  Hojas: " << arbol.hojas()
        << "  Min: " << arbol.minimo() << "  Max: " << arbol.maximo() << Qt::endl;
    out << "Buscar " << aBuscar << ": " << (arbol.buscar(aBuscar) ? "encontrado" : "no existe") << Qt::endl;

    ArbolBinario<T> copia = arbol;
    copia.eliminar(aEliminar);
    out << "Copia tras eliminar " << aEliminar << ": "; copia.imprimir(out);
    out << "Original intacto:      ";        arbol.imprimir(out);
    out << Qt::endl;
}

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    QTextStream out(stdout);

    demo<int>   (out, "ENTEROS (int)",    {50, 30, 70, 20, 40, 60, 80, 40}, 30, 60);
    demo<double>(out, "FLOTANTES (double)", {5.5, 2.25, 8.75, 1.0, 3.5, 9.9}, 5.5, 3.5);
    demo<float> (out, "FLOTANTES (float)",  {0.5f, -1.5f, 2.5f, 1.25f}, -1.5f, 7.0f);
    demo<long>  (out, "OTROS (long)",       {1000000L, 500000L, 2000000L}, 1000000L, 500000L);
    demo<char>  (out, "CARACTERES (char)",  {'M', 'F', 'T', 'B', 'H', 'P', 'X', 'a'}, 'F', 'a');

    return 0;
}


