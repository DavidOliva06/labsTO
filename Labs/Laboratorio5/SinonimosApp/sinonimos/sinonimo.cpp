#include "sinonimo.h"
#include "ui_sinonimo.h"
#include <utility>

Sinonimo::Sinonimo(const QString &palabra1, const QString &palabra2, QWidget *parent)
    : QWidget(parent), ui(new Ui::Sinonimo)
{
    ui->setupUi(this);
    ui->checkbox->setChecked(false);                       // b) checkbox sin check
    setPalabras(palabra1, palabra2);                       // b) texto con los sinónimos

    // Signals & slots de los objetos del formulario
    connect(ui->checkbox, &QCheckBox::toggled, this, &Sinonimo::checkboxCambiado);
    connect(ui->editButton, &QPushButton::clicked, this, [this] {
        emit edicionSolicitada(this);                      // c) Editar
    });
    connect(ui->removeButton, &QPushButton::clicked, this, [this] {
        emit quitado(this);                                // d) Quitar
    });
}

Sinonimo::~Sinonimo()
{
    delete ui;
}

QString Sinonimo::texto() const
{
    return m_palabra1 + " - " + m_palabra2;
}

QString Sinonimo::claveDe(const QString &a, const QString &b)
{
    QString x = a.trimmed().toLower();
    QString y = b.trimmed().toLower();
    if (y < x) std::swap(x, y);
    return x + "|" + y;
}

QString Sinonimo::clave() const
{
    return claveDe(m_palabra1, m_palabra2);
}

bool Sinonimo::estaRevisado() const
{
    return ui->checkbox->isChecked();
}

void Sinonimo::setPalabras(const QString &palabra1, const QString &palabra2)
{
    m_palabra1 = palabra1.trimmed();
    m_palabra2 = palabra2.trimmed();
    ui->sinonimosLabel->setText(texto());
}

void Sinonimo::setDuplicado(bool duplicado)
{
    m_duplicado = duplicado;
    refrescarEstilo();
}

void Sinonimo::checkboxCambiado(bool)
{
    refrescarEstilo();
    emit estadoCambiado(this);
}

void Sinonimo::refrescarEstilo()
{
    // Marcado = revisado → texto tachado (como en la versión original)
    QFont f = ui->sinonimosLabel->font();
    f.setStrikeOut(ui->checkbox->isChecked());
    ui->sinonimosLabel->setFont(f);

    // Repetido → texto en rojo para que el usuario lo revise
    if (m_duplicado) {
        ui->sinonimosLabel->setStyleSheet("color: #c62828; font-weight: bold;");
        ui->sinonimosLabel->setToolTip(tr("Repetido: otra fila tiene los mismos sinónimos. Use Editar."));
    } else {
        ui->sinonimosLabel->setStyleSheet(QString());
        ui->sinonimosLabel->setToolTip(QString());
    }
}
