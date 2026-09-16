// Lista doblemente enlazada implementada con punteros
#include <iostream>
using namespace std;

struct Nodo {
    int dato;
    Nodo* ant;
    Nodo* sig;
    Nodo(int d) : dato(d), ant(nullptr), sig(nullptr) {}
};

class ListaDoble {
private:
    Nodo* cabeza;
    Nodo* cola;
    int tam;

public:
    ListaDoble() : cabeza(nullptr), cola(nullptr), tam(0) {}

    ~ListaDoble() {
        Nodo* actual = cabeza;
        while (actual != nullptr) {
            Nodo* temp = actual;
            actual = actual->sig;
            delete temp;
        }
    }

    bool vacia() const { return cabeza == nullptr; }
    int tamano() const { return tam; }

    void insertarInicio(int valor) {
        Nodo* nuevo = new Nodo(valor);
        if (vacia()) {
            cabeza = cola = nuevo;
        } else {
            nuevo->sig = cabeza;
            cabeza->ant = nuevo;
            cabeza = nuevo;
        }
        tam++;
    }

    void insertarFinal(int valor) {
        Nodo* nuevo = new Nodo(valor);
        if (vacia()) {
            cabeza = cola = nuevo;
        } else {
            cola->sig = nuevo;
            nuevo->ant = cola;
            cola = nuevo;
        }
        tam++;
    }

    // Inserta en la posicion pos (0 = inicio)
    bool insertarEn(int pos, int valor) {
        if (pos < 0 || pos > tam) return false;
        if (pos == 0) { insertarInicio(valor); return true; }
        if (pos == tam) { insertarFinal(valor); return true; }

        Nodo* actual = cabeza;
        for (int i = 0; i < pos; i++) actual = actual->sig;

        Nodo* nuevo = new Nodo(valor);
        nuevo->sig = actual;
        nuevo->ant = actual->ant;
        actual->ant->sig = nuevo;
        actual->ant = nuevo;
        tam++;
        return true;
    }

    Nodo* buscar(int valor) const {
        Nodo* actual = cabeza;
        while (actual != nullptr) {
            if (actual->dato == valor) return actual;
            actual = actual->sig;
        }
        return nullptr;
    }

    // Elimina la primera aparicion del valor
    bool eliminar(int valor) {
        Nodo* nodo = buscar(valor);
        if (nodo == nullptr) return false;

        if (nodo->ant != nullptr) nodo->ant->sig = nodo->sig;
        else cabeza = nodo->sig;

        if (nodo->sig != nullptr) nodo->sig->ant = nodo->ant;
        else cola = nodo->ant;

        delete nodo;
        tam--;
        return true;
    }

    void mostrarAdelante() const {
        cout << "NULL <-> ";
        for (Nodo* p = cabeza; p != nullptr; p = p->sig)
            cout << p->dato << " <-> ";
        cout << "NULL\n";
    }

    void mostrarAtras() const {
        cout << "NULL <-> ";
        for (Nodo* p = cola; p != nullptr; p = p->ant)
            cout << p->dato << " <-> ";
        cout << "NULL\n";
    }
};

int main() {
    ListaDoble lista;
    int opcion, valor, pos;

    do {
        cout << "\n=== LISTA DOBLEMENTE ENLAZADA ===\n"
             << "1. Insertar al inicio\n"
             << "2. Insertar al final\n"
             << "3. Insertar en posicion\n"
             << "4. Eliminar valor\n"
             << "5. Buscar valor\n"
             << "6. Mostrar (inicio -> fin)\n"
             << "7. Mostrar (fin -> inicio)\n"
             << "0. Salir\n"
             << "Opcion: ";
        if (!(cin >> opcion)) break;

        switch (opcion) {
            case 1:
                cout << "Valor: "; cin >> valor;
                lista.insertarInicio(valor);
                break;
            case 2:
                cout << "Valor: "; cin >> valor;
                lista.insertarFinal(valor);
                break;
            case 3:
                cout << "Posicion (0-" << lista.tamano() << "): "; cin >> pos;
                cout << "Valor: "; cin >> valor;
                if (!lista.insertarEn(pos, valor)) cout << "Posicion invalida\n";
                break;
            case 4:
                cout << "Valor a eliminar: "; cin >> valor;
                cout << (lista.eliminar(valor) ? "Eliminado\n" : "No encontrado\n");
                break;
            case 5:
                cout << "Valor a buscar: "; cin >> valor;
                cout << (lista.buscar(valor) ? "Encontrado\n" : "No encontrado\n");
                break;
            case 6: lista.mostrarAdelante(); break;
            case 7: lista.mostrarAtras(); break;
            case 0: cout << "Fin del programa\n"; break;
            default: cout << "Opcion invalida\n";
        }
    } while (opcion != 0);

    return 0;
}