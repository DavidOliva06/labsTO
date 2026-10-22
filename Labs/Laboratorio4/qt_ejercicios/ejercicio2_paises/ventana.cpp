#include "ventana.h"

#include <QListWidget>
#include <QLabel>
#include <QVBoxLayout>

Ventana::Ventana(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("Países");
    resize(320, 400);

    // Datos: país -> {idioma, capital}
    paises = {
        {"Perú",           {"Español", "Lima"}},
        {"Argentina",      {"Español", "Buenos Aires"}},
        {"Brasil",         {"Portugués", "Brasilia"}},
        {"Chile",          {"Español", "Santiago"}},
        {"Colombia",       {"Español", "Bogotá"}},
        {"México",         {"Español", "Ciudad de México"}},
        {"Estados Unidos", {"Inglés", "Washington D. C."}},
        {"España",         {"Español", "Madrid"}},
        {"Francia",        {"Francés", "París"}},
        {"Alemania",       {"Alemán", "Berlín"}},
        {"Italia",         {"Italiano", "Roma"}},
        {"Japón",          {"Japonés", "Tokio"}}
    };

    // Widgets
    lista = new QListWidget(this);
    lista->addItems(paises.keys());

    etiqueta = new QLabel("Seleccione un país", this);
    etiqueta->setWordWrap(true);
    etiqueta->setStyleSheet("font-size: 14px; padding: 6px;");

    // Layout
    auto *layout = new QVBoxLayout(this);
    layout->addWidget(lista);
    layout->addWidget(etiqueta);

    // Señal -> Slot
    connect(lista, &QListWidget::itemClicked, this, &Ventana::mostrarInfo);
}

void Ventana::mostrarInfo(QListWidgetItem *item)
{
    const QString pais = item->text();
    const InfoPais info = paises.value(pais);

    etiqueta->setText(QString("<b>%1</b><br>Idioma: %2<br>Capital: %3")
                          .arg(pais, info.idioma, info.capital));
}
