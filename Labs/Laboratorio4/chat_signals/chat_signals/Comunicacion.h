#ifndef COMUNICACION_H
#define COMUNICACION_H

#include <QObject>
#include <QString>

class Comunicacion : public QObject
{
    Q_OBJECT
public:
    explicit Comunicacion(QObject *parent = nullptr);

    void setNombre(const QString &nomb) {
        strnombre = nomb;
    }
    QString getNombre() const {
        return strnombre;
    }

    void conversar(const QString &conversa);   // método que emite la señal

signals:
    void enviarmensaje(QString);               // señal en respuesta a un evento

public slots:
    void escuchar(const QString &str);         // slot: donde se realiza la acción

private:
    QString strnombre;
};

#endif // COMUNICACION_H
