#ifndef SINONIMO_H
#define SINONIMO_H

#include <QWidget>
#include <QString>

namespace Ui { class Sinonimo; }

// Una fila del checklist: [checkbox] [texto "Palabra1 - Palabra2"] [Editar] [Quitar]
class Sinonimo : public QWidget
{
    Q_OBJECT

public:
    explicit Sinonimo(const QString &palabra1, const QString &palabra2,
                      QWidget *parent = nullptr);
    ~Sinonimo();

    QString palabra1() const { return m_palabra1; }
    QString palabra2() const { return m_palabra2; }
    QString texto() const;
    QString clave() const;                 // forma normalizada para detectar repetidos
    bool estaRevisado() const;

    void setPalabras(const QString &palabra1, const QString &palabra2);
    void setDuplicado(bool duplicado);

    // Normaliza un par: minúsculas, sin espacios extremos y en orden alfabético,
    // así "Subir - Ascender" y "ascender - subir" se consideran iguales.
    static QString claveDe(const QString &a, const QString &b);

signals:
    void edicionSolicitada(Sinonimo *s);   // botón Editar
    void quitado(Sinonimo *s);             // botón Quitar
    void estadoCambiado(Sinonimo *s);      // checkbox marcado/desmarcado

private slots:
    void checkboxCambiado(bool marcado);

private:
    void refrescarEstilo();

    Ui::Sinonimo *ui;
    QString m_palabra1;
    QString m_palabra2;
    bool m_duplicado = false;
};

#endif // SINONIMO_H
