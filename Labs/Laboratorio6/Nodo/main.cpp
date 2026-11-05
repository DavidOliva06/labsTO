#include <QCoreApplication>
#include <QDebug>
#include <thread>
#include <mutex>
#include <random>
#include <chrono>

struct Nodo {
    int valor;
    Nodo* siguiente;
    Nodo(int v) : valor(v), siguiente(nullptr) {}
};

class ListaEnlazada {
private:
    Nodo* cabeza;
    std::mutex candado;

public:
    ListaEnlazada() : cabeza(nullptr) {}

    ~ListaEnlazada() {
        Nodo* actual = cabeza;
        while (actual != nullptr) {
            Nodo* temp = actual;
            actual = actual->siguiente;
            delete temp;
        }
    }

    // Operación del Thread 2: Inserción
    void insertar(int n) {
        std::lock_guard<std::mutex> bloqueo(candado);
        Nodo* nuevo = new Nodo(n);
        nuevo->siguiente = cabeza;
        cabeza = nuevo;
        qInfo().noquote() << QString("Insertando: %1").arg(n);
    }

    // Operación del Thread 1: Eliminación
    void eliminar(int n) {
        std::lock_guard<std::mutex> bloqueo(candado);
        Nodo* actual = cabeza;
        Nodo* anterior = nullptr;

        while (actual != nullptr && actual->valor != n) {
            anterior = actual;
            actual = actual->siguiente;
        }

        if (actual == nullptr) {
            qInfo().noquote() << QString("No se elimino %1").arg(n);
            return;
        }

        if (anterior == nullptr) {
            cabeza = actual->siguiente;
        } else {
            anterior->siguiente = actual->siguiente;
        }

        delete actual;
        qInfo().noquote() << QString("eliminando: %1").arg(n);
    }

    // Operación del Thread 3: Búsqueda
    void buscar(int n) {
        std::lock_guard<std::mutex> bloqueo(candado);
        Nodo* actual = cabeza;

        while (actual != nullptr) {
            if (actual->valor == n) {
                qInfo().noquote() << QString("Buscado: %1").arg(n);
                return;
            }
            actual = actual->siguiente;
        }
        qInfo().noquote() << QString("No encontrado: %1").arg(n);
    }

    // Operación del Thread 4: Modificación
    void modificar(int n, int suma) {
        std::lock_guard<std::mutex> bloqueo(candado);
        Nodo* actual = cabeza;

        while (actual != nullptr) {
            if (actual->valor == n) {
                int m = actual->valor + suma;
                actual->valor = m;
                qInfo().noquote() << QString("Modificando %1 a %2").arg(n).arg(m);
                return;
            }
            actual = actual->siguiente;
        }
        qInfo().noquote() << "No se encontro";
    }
};

// Generador de números aleatorios independiente para cada hilo
int generarAleatorio(int min, int max) {
    thread_local std::mt19937 generador(std::random_device{}());
    std::uniform_int_distribution<int> distribucion(min, max);
    return distribucion(generador);
}

// Thread 1: Eliminar 10 valores aleatorios
void tareaEliminar(ListaEnlazada &lista) {
    for (int i = 0; i < 10; ++i) {
        lista.eliminar(generarAleatorio(1, 15));
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}

// Thread 2: Insertar 10 valores aleatorios
void tareaInsertar(ListaEnlazada &lista) {
    for (int i = 0; i < 10; ++i) {
        lista.insertar(generarAleatorio(1, 15));
        std::this_thread::sleep_for(std::chrono::milliseconds(40));
    }
}

// Thread 3: Buscar 10 valores aleatorios
void tareaBuscar(ListaEnlazada &lista) {
    for (int i = 0; i < 10; ++i) {
        lista.buscar(generarAleatorio(1, 15));
        std::this_thread::sleep_for(std::chrono::milliseconds(60));
    }
}

// Thread 4: Modificar 10 valores aleatorios
void tareaModificar(ListaEnlazada &lista) {
    for (int i = 0; i < 10; ++i) {
        int valorBuscado = generarAleatorio(1, 15);
        int cantidadSumar = generarAleatorio(1, 10);
        lista.modificar(valorBuscado, cantidadSumar);
        std::this_thread::sleep_for(std::chrono::milliseconds(55));
    }
}

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    ListaEnlazada listaCompartida;

    // Lanzamiento concurrente de los 4 hilos
    std::thread hilo2(tareaInsertar, std::ref(listaCompartida));
    std::thread hilo1(tareaEliminar, std::ref(listaCompartida));
    std::thread hilo3(tareaBuscar, std::ref(listaCompartida));
    std::thread hilo4(tareaModificar, std::ref(listaCompartida));

    // Espera a que los 4 hilos terminen sus 10 operaciones
    hilo1.join();
    hilo2.join();
    hilo3.join();
    hilo4.join();

    qInfo() << "--- Fin de las operaciones concurrentes ---";
    return 0;
}