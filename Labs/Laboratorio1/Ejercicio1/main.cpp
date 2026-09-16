#include <iostream>
#include <cstdlib>   // srand, rand, EXIT_SUCCESS
#include <ctime>     // time
#include <string>

using namespace std;

const int MAX = 1000;   // capacidad maxima del arreglo

// ------------------------------------------------------------
// intercambia dos posiciones del arreglo
// ------------------------------------------------------------
void intercambiar(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

// ------------------------------------------------------------
// usamos particionar para el Quicksort de mayor a menor
// ------------------------------------------------------------
int particionar(int arreglo[], int inicio, int fin) {
    int pivote = arreglo[fin];
    int i = inicio - 1;

    for (int j = inicio; j < fin; j++) {
        if (arreglo[j] >= pivote) {     // >=  ->  mayor a menor
            i++;
            intercambiar(arreglo[i], arreglo[j]);
        }
    }
    intercambiar(arreglo[i + 1], arreglo[fin]);
    return i + 1;
}

// ------------------------------------------------------------
// QuickSort recursivo (mayor a menor)
// ------------------------------------------------------------
void quickSort(int arreglo[], int inicio, int fin) {
    if (inicio < fin) {
        int p = particionar(arreglo, inicio, fin);
        quickSort(arreglo, inicio, p - 1);
        quickSort(arreglo, p + 1, fin);
    }
}

// ------------------------------------------------------------
// Muestra el contenido del arreglo separado por espacios
// ------------------------------------------------------------
void mostrarArreglo(const int arreglo[], int n, const string &titulo) {
    cout << titulo << endl;
    for (int i = 0; i < n; i++) {
        cout << arreglo[i];
        if (i < n - 1) cout << "  ";
    }
    cout << endl << endl;
}
// ------------------------------------------------------------
// Programa principal
// ------------------------------------------------------------
int main() {
    int numeros[MAX];
    int n;
    char opcion;

    // ---------- 1) Solicitar N (entero positivo) ----------
    cout << "==============================================" << endl;
    cout << "        EJERCICIO 1 - ORDENAMIENTO            " << endl;
    cout << "==============================================" << endl;

    do {
        cout << "Digite N (numero entero positivo, max " << MAX << "): ";
        cin >> n;

        if (cin.fail()) {                 // el usuario escribio texto
            cin.clear();
            cin.ignore(10000, '\n');
            n = 0;
        }
        if (n <= 0 || n > MAX)
            cout << ">> Error: N debe estar entre 1 y " << MAX << ". Intente de nuevo." << endl;

    } while (n <= 0 || n > MAX);

    // ---------- 2) Solicitar la letra (g / i) ----------
    do {
        cout << endl;
        cout << "Digite una letra:" << endl;
        cout << "   g = generar automaticamente N numeros aleatorios entre 1 y N" << endl;
        cout << "   i = ingresar manualmente los N numeros" << endl;
        cout << "Opcion: ";
        cin >> opcion;

        if (opcion >= 'A' && opcion <= 'Z')      // aceptar mayusculas
            opcion = opcion + 32;

        if (opcion != 'g' && opcion != 'i')
            cout << ">> Error: solo se acepta 'g' o 'i'." << endl;

    } while (opcion != 'g' && opcion != 'i');

    // ---------- 3) Llenado del arreglo ----------
    if (opcion == 'g') {
        srand(time(0));                          // semilla del generador
        cout << endl << "Generando " << n << " numeros aleatorios entre 1 y " << n << "..." << endl;
        for (int i = 0; i < n; i++) {
            numeros[i] = rand() % n + 1;         // rango [1, N]
        }
    } else {
        cout << endl << "Ingrese los " << n << " numeros enteros:" << endl;
        for (int i = 0; i < n; i++) {
            cout << "  Numero [" << (i + 1) << "]: ";
            cin >> numeros[i];

            if (cin.fail()) {                    // validacion basica
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "  >> Valor invalido, se repite el dato." << endl;
                i--;
            }
        }
    }

    // ---------- 4) Mostrar y ordenar ----------
    cout << endl;
    mostrarArreglo(numeros, n, "ARREGLO ORIGINAL:");

    quickSort(numeros, 0, n - 1);

    mostrarArreglo(numeros, n, "ARREGLO ORDENADO DE MAYOR A MENOR (QuickSort):");

    cout << "Proceso terminado correctamente." << endl;
    return 0;
}
