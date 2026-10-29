#include <QCoreApplication>
#include <QTextStream>
#include <QStringList>
#include "ListaEnlazada.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    QTextStream out(stdout);

    ListaEnlazada<int> edades;
    for (int e : {21, 19, 35, 42, 19, 27})
        edades.insertarFinal(e);

    out << "Edades:            "; edades.imprimir(out);

    int suma = 0, mayor = edades.en(0);
    edades.recorrer([&](int e) { suma += e; if (e > mayor) mayor = e; });
    out << "Cantidad: " << edades.tamano()
        << "  Promedio: " << double(suma) / edades.tamano()
        << "  Mayor: " << mayor << Qt::endl;

    edades.eliminar(19);
    out << "Tras eliminar 19:  "; edades.imprimir(out);

    ListaEnlazada<int> ordenadas;
    edades.recorrer([&](int e) { ordenadas.insertarOrdenado(e); });
    out << "Ordenadas:         "; ordenadas.imprimir(out);
    ListaEnlazada<QString> palabras;
    for (const QString &w : QString("el sistema operativo gestiona procesos").split(' '))
        palabras.insertarFinal(w);
    palabras.insertarInicio("Hoy");

    out << "\nPalabras:          "; palabras.imprimir(out, " ");
    out << "Contiene 'procesos'? " << (palabras.contiene("procesos") ? "si" : "no") << Qt::endl;

    ListaEnlazada<QString> mayus;
    palabras.recorrer([&](const QString &w) { mayus.insertarFinal(w.toUpper()); });
    out << "En mayusculas:     "; mayus.imprimir(out, " ");

    ListaEnlazada<QString> alfabetico;
    palabras.recorrer([&](const QString &w) { alfabetico.insertarOrdenado(w.toLower()); });
    out << "Alfabetico:        "; alfabetico.imprimir(out, ", ");

    ListaEnlazada<QString> copia = palabras;
    copia.eliminar("Hoy");
    out << "Copia sin 'Hoy':   "; copia.imprimir(out, " ");
    out << "Original intacta:  "; palabras.imprimir(out, " ");

    return 0;
}
