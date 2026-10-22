#include <QCoreApplication>
#include <QDebug>
#include "Comunicacion.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // Clase base (padre) y sus hijas
    QObject *person = new QObject;
    Comunicacion *pepe = new Comunicacion(person);
    Comunicacion *jose = new Comunicacion(person);

    // set....
    pepe->setNombre("Pepe");
    jose->setNombre("Jose");

    // Conexión de señales y slots (sintaxis con macros SIGNAL / SLOT)
    QObject::connect(pepe, SIGNAL(enviarmensaje(QString)), jose, SLOT(escuchar(QString)));
    QObject::connect(jose, SIGNAL(enviarmensaje(QString)), pepe, SLOT(escuchar(QString)));

    pepe->conversar("buenos dias");
    jose->conversar("como vas?");

    delete person;   // destruye también a pepe y jose (son sus hijos)

    return 0;
}
