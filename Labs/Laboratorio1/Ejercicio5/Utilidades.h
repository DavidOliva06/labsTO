// ============================================================
//  Funciones de apoyo para la lectura segura por consola
// ============================================================
#ifndef UTILIDADES_H
#define UTILIDADES_H

#include <string>

std::string leerLinea(const std::string &mensaje);
int         leerEntero(const std::string &mensaje);
double      leerDecimal(const std::string &mensaje);

#endif // UTILIDADES_H
