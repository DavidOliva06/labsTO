#include "Comunicacion.h"
#include <QDebug>

Comunicacion::Comunicacion(QObject *parent) : QObject(parent)
{
}

void Comunicacion::escuchar(const QString &str)
{
    qDebug().noquote() << strnombre << "está escuchando....:" << str;
}

void Comunicacion::conversar(const QString &conversa)
{
    qDebug().noquote() << strnombre << "dice:" << conversa;

    // emitir la señal
    emit enviarmensaje(conversa);
}
