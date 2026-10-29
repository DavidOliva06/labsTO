#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sinonimo.h"

#include <QDialog>
#include <QDialogButtonBox>
#include <QFormLayout>
#include <QHash>
#include <QLineEdit>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->addSinonimoButton, &QPushButton::clicked,
            this, &MainWindow::agregarSinonimo);
    actualizarEstado();
}

MainWindow::~MainWindow()
{
    delete ui;
}

// b) Crea una fila: checkbox sin check + "Subir - Ascender" + Editar + Quitar
void MainWindow::agregarSinonimo()
{
    auto *s = new Sinonimo("Subir", "Ascender");

    connect(s, &Sinonimo::edicionSolicitada, this, &MainWindow::editarSinonimo);
    connect(s, &Sinonimo::quitado,           this, &MainWindow::quitarSinonimo);
    connect(s, &Sinonimo::estadoCambiado,    this, &MainWindow::actualizarEstado);

    m_sinonimos.append(s);
    ui->sinonimosLayout->addWidget(s);
    actualizarEstado();
}

// c) Permite cambiar los dos sinónimos, validando que no se repitan
void MainWindow::editarSinonimo(Sinonimo *s)
{
    QString p1 = s->palabra1();
    QString p2 = s->palabra2();
    if (pedirSinonimos(p1, p2, s)) {
        s->setPalabras(p1, p2);
        actualizarEstado();
    }
}

// d) Elimina toda la fila de objetos
void MainWindow::quitarSinonimo(Sinonimo *s)
{
    m_sinonimos.removeOne(s);
    ui->sinonimosLayout->removeWidget(s);
    s->hide();
    s->deleteLater();       // seguro: la señal proviene de un botón del propio widget
    actualizarEstado();
}

// Diálogo con dos campos; repite hasta obtener datos válidos o cancelar
bool MainWindow::pedirSinonimos(QString &p1, QString &p2, const Sinonimo *actual)
{
    QDialog dlg(this);
    dlg.setWindowTitle(tr("Editar sinónimos"));

    auto *edit1 = new QLineEdit(p1, &dlg);
    auto *edit2 = new QLineEdit(p2, &dlg);
    auto *botones = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, &dlg);
    connect(botones, &QDialogButtonBox::accepted, &dlg, &QDialog::accept);
    connect(botones, &QDialogButtonBox::rejected, &dlg, &QDialog::reject);

    auto *form = new QFormLayout(&dlg);
    form->addRow(tr("Palabra:"), edit1);
    form->addRow(tr("Sinónimo:"), edit2);
    form->addRow(botones);

    while (dlg.exec() == QDialog::Accepted) {
        const QString a = edit1->text().trimmed();
        const QString b = edit2->text().trimmed();

        if (a.isEmpty() || b.isEmpty()) {
            QMessageBox::warning(this, tr("Datos incompletos"),
                                 tr("Debe escribir ambas palabras."));
            continue;
        }
        if (a.compare(b, Qt::CaseInsensitive) == 0) {
            QMessageBox::warning(this, tr("Sinónimo inválido"),
                                 tr("Una palabra no puede ser sinónimo de sí misma."));
            continue;
        }

        const QString clave = Sinonimo::claveDe(a, b);
        bool repetido = false;
        for (const Sinonimo *otro : qAsConst(m_sinonimos))
            if (otro != actual && otro->clave() == clave) { repetido = true; break; }

        if (repetido) {
            QMessageBox::warning(this, tr("Sinónimo repetido"),
                                 tr("Ya existe una fila con \"%1 - %2\".\n"
                                    "Ingrese un par diferente.").arg(a, b));
            continue;
        }

        p1 = a;
        p2 = b;
        return true;
    }
    return false;
}

// Recalcula repetidos y el resumen del checklist
void MainWindow::actualizarEstado()
{
    QHash<QString, int> conteo;
    for (const Sinonimo *s : qAsConst(m_sinonimos))
        ++conteo[s->clave()];

    int revisados = 0, repetidos = 0;
    for (Sinonimo *s : qAsConst(m_sinonimos)) {
        const bool dup = conteo.value(s->clave()) > 1;
        s->setDuplicado(dup);
        if (dup) ++repetidos;
        if (s->estaRevisado()) ++revisados;
    }

    ui->statusLabel->setText(
        tr("Sinónimos: %1   |   Revisados: %2   |   Repetidos: %3")
            .arg(m_sinonimos.size()).arg(revisados).arg(repetidos));
}
