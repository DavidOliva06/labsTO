#include <QCoreApplication>
#include <QRandomGenerator>
#include <QDebug>
#include <vector>
#include <algorithm>
bool esPrimo(int n)
{
    if (n < 2) return false;
    if (n % 2 == 0) return n == 2;
    for (int i = 3; i * i <= n; i += 2)
        if (n % i == 0) return false;
    return true;
}

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    const int N = 50;
    std::vector<int> numeros(N);

    for (int &x : numeros)
        x = QRandomGenerator::global()->bounded(1, 2001);

    qDebug().noquote() << "Vector generado:";
    QString linea;
    for (int x : numeros) linea += QString::number(x) + " ";
    qDebug().noquote() << linea;

    auto cantidad = std::count_if(numeros.begin(), numeros.end(),
                                  [](int n) { return n < 1000 && esPrimo(n); });

    QString encontrados;
    for (int x : numeros)
        if (x < 1000 && esPrimo(x)) encontrados += QString::number(x) + " ";

    qDebug().noquote() << "\nPrimos menores de 1000:" << encontrados;
    qDebug().noquote() << "Cantidad:" << cantidad;

    return 0;
}
