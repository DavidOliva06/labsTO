// Calculadora con 3 clases: Analizador, Nucleo y Procesador
#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <stdexcept>
using namespace std;

// ================== 1. ANALIZADOR ==================
// Analiza la cadena: separa numeros y operadores y valida la expresion
class Analizador {
private:
    vector<double> numeros;
    vector<char> operadores;
    static const int MAX_NUMEROS = 6;

    bool esOperador(char c) const {
        return c == '+' || c == '-' || c == '*' || c == '/';
    }

public:
    void analizar(const string& expr) {
        numeros.clear();
        operadores.clear();

        string num = "";
        bool esperaNumero = true;

        for (size_t i = 0; i < expr.size(); i++) {
            char c = expr[i];
            if (c == ' ') continue;

            if (isdigit(c) || c == '.') {
                num += c;
                esperaNumero = false;
            } else if (esOperador(c)) {
                // Signo negativo al inicio o despues de un operador
                if (esperaNumero && c == '-' && num.empty()) {
                    num += c;
                    continue;
                }
                if (esperaNumero)
                    throw invalid_argument("Operador fuera de lugar: " + string(1, c));
                numeros.push_back(stod(num));
                operadores.push_back(c);
                num = "";
                esperaNumero = true;
            } else {
                throw invalid_argument("Caracter no valido: " + string(1, c));
            }
        }

        if (esperaNumero)
            throw invalid_argument("La expresion esta incompleta");
        numeros.push_back(stod(num));

        if ((int)numeros.size() > MAX_NUMEROS)
            throw invalid_argument("Maximo 6 numeros por operacion");
    }

    vector<double> getNumeros() const { return numeros; }
    vector<char> getOperadores() const { return operadores; }

    string tipoOperacion() const {
        if (operadores.empty()) return "Ninguna (solo un numero)";
        string tipos = "";
        bool s = false, r = false, m = false, d = false;
        for (char op : operadores) {
            if (op == '+') s = true;
            if (op == '-') r = true;
            if (op == '*') m = true;
            if (op == '/') d = true;
        }
        if (s) tipos += "suma ";
        if (r) tipos += "resta ";
        if (m) tipos += "multiplicacion ";
        if (d) tipos += "division ";
        return tipos;
    }
};

// ================== 2. NUCLEO ==================
// Administra las operaciones matematicas
class Nucleo {
public:
    double sumar(double a, double b) { return a + b; }
    double restar(double a, double b) { return a - b; }
    double multiplicar(double a, double b) { return a * b; }
    double dividir(double a, double b) {
        if (b == 0) throw runtime_error("Division entre cero");
        return a / b;
    }

    double operar(double a, char op, double b) {
        switch (op) {
            case '+': return sumar(a, b);
            case '-': return restar(a, b);
            case '*': return multiplicar(a, b);
            case '/': return dividir(a, b);
            default: throw invalid_argument("Operador desconocido");
        }
    }
};

// ================== 3. PROCESADOR ==================
// Procesa la operacion ingresada respetando la precedencia (* / antes que + -)
class Procesador {
private:
    Analizador analizador;
    Nucleo nucleo;

public:
    double procesar(const string& expr) {
        analizador.analizar(expr);
        vector<double> nums = analizador.getNumeros();
        vector<char> ops = analizador.getOperadores();

        // Primera pasada: multiplicacion y division
        vector<double> n2;
        vector<char> o2;
        n2.push_back(nums[0]);
        for (size_t i = 0; i < ops.size(); i++) {
            if (ops[i] == '*' || ops[i] == '/') {
                n2.back() = nucleo.operar(n2.back(), ops[i], nums[i + 1]);
            } else {
                o2.push_back(ops[i]);
                n2.push_back(nums[i + 1]);
            }
        }

        // Segunda pasada: suma y resta (izquierda a derecha)
        double resultado = n2[0];
        for (size_t i = 0; i < o2.size(); i++)
            resultado = nucleo.operar(resultado, o2[i], n2[i + 1]);

        return resultado;
    }

    string tipo() const { return analizador.tipoOperacion(); }
};

// ================== MAIN ==================
int main() {
    Procesador calc;
    string entrada;

    cout << "=== CALCULADORA (maximo 6 numeros) ===\n";
    cout << "Escriba 'salir' para terminar.\n";

    while (true) {
        cout << "\nOperacion: ";
        getline(cin, entrada);
        if (entrada == "salir") break;

        try {
            double r = calc.procesar(entrada);
            cout << "Tipo: " << calc.tipo() << "\n";
            cout << "Resultado: " << r << "\n";
        } catch (exception& e) {
            cout << "Error: " << e.what() << "\n";
        }
    }
    return 0;
}