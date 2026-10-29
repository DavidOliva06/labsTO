#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>

class Sinonimo;
namespace Ui { class MainWindow; }

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void agregarSinonimo();                 // a) botón "Agregar sinónimos"
    void editarSinonimo(Sinonimo *s);       // c) Editar
    void quitarSinonimo(Sinonimo *s);       // d) Quitar
    void actualizarEstado();

private:
    bool pedirSinonimos(QString &p1, QString &p2, const Sinonimo *actual);

    Ui::MainWindow *ui;
    QVector<Sinonimo *> m_sinonimos;
};

#endif // MAINWINDOW_H
