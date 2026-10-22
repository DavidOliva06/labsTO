#ifndef VENTANA_H
#define VENTANA_H

#include <QWidget>
#include <QMap>

class QListWidget;
class QListWidgetItem;
class QLabel;

struct InfoPais {
    QString idioma;
    QString capital;
};

class Ventana : public QWidget
{
    Q_OBJECT

public:
    explicit Ventana(QWidget *parent = nullptr);

private slots:
    void mostrarInfo(QListWidgetItem *item);   // slot que responde al clic

private:
    QListWidget *lista;
    QLabel *etiqueta;
    QMap<QString, InfoPais> paises;
};

#endif // VENTANA_H
