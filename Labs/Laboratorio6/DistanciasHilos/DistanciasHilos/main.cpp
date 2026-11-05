// Calcula distancias Euclidea y Manhattan desde un CSV usando hilos (QThread).
// Muestra los 5 primeros elementos y los compara con los valores del archivo.

#include <QCoreApplication>
#include <QFile>
#include <QTextStream>
#include <QThread>
#include <QVector>
#include <QString>
#include <QStringList>
#include <cmath>
#include <cstdlib>

// Una fila del CSV
struct Fila {
    QString origen;
    QString destino;
    int x1, y1, x2, y2;
    double euclideaCSV;   // valor que trae el archivo (para comparar)
    int manhattanCSV;     // valor que trae el archivo (para comparar)
};

// Formula Euclidea: raiz((x2-x1)^2 + (y2-y1)^2)
double distanciaEuclidea(int x1, int y1, int x2, int y2)
{
    double dx = x2 - x1;
    double dy = y2 - y1;
    return std::sqrt(dx * dx + dy * dy);
}

// Formula Manhattan: |x2-x1| + |y2-y1|
int distanciaManhattan(int x1, int y1, int x2, int y2)
{
    return std::abs(x2 - x1) + std::abs(y2 - y1);
}

// Lee el CSV y devuelve sus filas (salta la cabecera)
QVector<Fila> leerCSV(const QString &ruta)
{
    QVector<Fila> filas;
    QFile archivo(ruta);
    if (!archivo.open(QIODevice::ReadOnly | QIODevice::Text))
        return filas;

    QTextStream entrada(&archivo);
    entrada.readLine(); // cabecera

    while (!entrada.atEnd()) {
        QString linea = entrada.readLine().trimmed();
        if (linea.isEmpty())
            continue;

        QStringList c = linea.split(',');
        if (c.size() < 8)
            continue;

        Fila f;
        f.origen       = c[0];
        f.destino      = c[1];
        f.x1           = c[2].toInt();
        f.y1           = c[3].toInt();
        f.x2           = c[4].toInt();
        f.y2           = c[5].toInt();
        f.euclideaCSV  = c[6].toDouble();
        f.manhattanCSV = c[7].toInt();
        filas.append(f);
    }
    return filas;
}

// Hilo que calcula UN tipo de distancia para todas las filas
class HiloDistancia : public QThread
{
public:
    enum Tipo { Euclidea, Manhattan };

    HiloDistancia(Tipo tipo, const QVector<Fila> &filas, QVector<double> &resultados)
        : m_tipo(tipo), m_filas(filas), m_resultados(resultados) {}

protected:
    void run() override
    {
        for (int i = 0; i < m_filas.size(); ++i) {
            const Fila &f = m_filas[i];
            if (m_tipo == Euclidea)
                m_resultados[i] = distanciaEuclidea(f.x1, f.y1, f.x2, f.y2);
            else
                m_resultados[i] = distanciaManhattan(f.x1, f.y1, f.x2, f.y2);
        }
    }

private:
    Tipo m_tipo;
    const QVector<Fila> &m_filas;
    QVector<double> &m_resultados; // cada hilo escribe en su propio vector
};

// Imprime los n primeros resultados en forma de tabla
void mostrarPrimeros(const QVector<Fila> &filas,
                     const QVector<double> &euclidea,
                     const QVector<double> &manhattan,
                     int n)
{
    QTextStream out(stdout);
    int limite = qMin(n, filas.size());

    out << "\nPrimeros " << limite << " elementos:\n";
    out << QString("%1 %2 %3 %4 %5 %6\n")
               .arg("Origen", -9).arg("Destino", -9).arg("Puntos", -18)
               .arg("Euclidea", 10).arg("Manhattan", 10).arg("Coincide CSV", 14);
    out << QString(75, '-') << "\n";

    for (int i = 0; i < limite; ++i) {
        const Fila &f = filas[i];
        QString puntos = QString("(%1,%2)->(%3,%4)").arg(f.x1).arg(f.y1).arg(f.x2).arg(f.y2);
        bool ok = std::fabs(euclidea[i] - f.euclideaCSV) < 0.001
               && static_cast<int>(manhattan[i]) == f.manhattanCSV;

        out << QString("%1 %2 %3 %4 %5 %6\n")
                   .arg(f.origen, -9).arg(f.destino, -9).arg(puntos, -18)
                   .arg(euclidea[i], 10, 'f', 4)
                   .arg(static_cast<int>(manhattan[i]), 10)
                   .arg(ok ? "Si" : "No", 14);
    }
}

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    QTextStream out(stdout);

    // Ruta del CSV: se puede pasar otra como argumento
    // Por defecto usa el CSV incluido dentro del programa (recursos.qrc)
    QString ruta = (argc > 1) ? argv[1] : ":/distancias_manhattan_euclides.csv";

    QVector<Fila> filas = leerCSV(ruta);
    if (filas.isEmpty()) {
        out << "No se pudo leer el archivo: " << ruta << "\n";
        return 1;
    }
    out << "Filas leidas: " << filas.size() << "\n";

    QVector<double> resEuclidea(filas.size());
    QVector<double> resManhattan(filas.size());

    // Dos hilos trabajando al mismo tiempo
    HiloDistancia hiloE(HiloDistancia::Euclidea, filas, resEuclidea);
    HiloDistancia hiloM(HiloDistancia::Manhattan, filas, resManhattan);

    hiloE.start();
    hiloM.start();

    // Esperar a que ambos terminen
    hiloE.wait();
    hiloM.wait();

    out << "Hilos terminados.\n";
    out.flush(); // vacia el texto antes de imprimir la tabla

    mostrarPrimeros(filas, resEuclidea, resManhattan, 5);
    return 0;
}
