# Ejercicio 2 — Comparación de manipuladores

## Estadística propuesta
Tabla de goleadores de la Liga 1 (fútbol peruano): número, jugador, equipo,
partidos jugados (PJ), goles, asistencias y promedio de goles por partido.

## Versión A — `setw`
Archivo: `ejercicio2a_setw.cpp`

`std::setw(n)` fija el ancho **del siguiente dato** que se envía a `cout`.
Es un manipulador *no persistente*: hay que repetirlo antes de cada columna.

```cpp
cout << setw(4) << i+1 << setw(20) << nombre << setw(6) << goles << endl;
```

## Versión B — `std::format` (C++20)
Archivo: `ejercicio2b_format.cpp`

Reemplaza a `setw`: el ancho y la alineación se escriben dentro de la
cadena de formato, no en el flujo de salida.

| Especificador | Significado                     |
|---------------|---------------------------------|
| `{:<20}`      | ancho 20, alineado a la izquierda |
| `{:>6}`       | ancho 6, alineado a la derecha    |
| `{:^10}`      | ancho 10, centrado                |
| `{:>12.2f}`   | ancho 12, 2 decimales             |

```cpp
cout << format("{:<4}{:<20}{:>6}{:>12.2f}", i+1, nombre, goles, promedio) << endl;
```

Otros manipuladores revisados en laboratorio:
- `setfill('.')` → rellena el espacio sobrante de `setw` con un carácter.
- `left` / `right` / `internal` → alineación (sí son persistentes).
- `fixed` + `setprecision(2)` → decimales fijos.
- `setbase(16)` / `hex` / `oct` → base numérica.

## ¿Cuál me ha servido mejor?

**`std::format`.** Razones:

1. **Una sola línea por fila.** Con `setw` cada columna necesita su propio
   manipulador; el `cout` se vuelve largo y difícil de leer.
2. **La plantilla del reporte se ve completa** (`"{:<4}{:<20}{:>6}"`), así que
   ajustar la tabla es cambiar un número dentro del string, no perseguir
   `setw` repartidos por el código.
3. **No deja estado pegado al flujo.** `fixed`, `setprecision` o `left` quedan
   activos en `cout` y afectan a impresiones posteriores; `format` sólo
   afecta a la cadena que genera.
4. **Es tipo-seguro**: si el tipo no coincide con el formato, falla en
   compilación (a diferencia de `printf`).

**Cuándo sigue conviniendo `setw`:** cuando el compilador no soporta C++20
(`<format>` requiere GCC 13+ / MSVC 2022), o cuando el ancho se calcula en
tiempo de ejecución y sólo se necesita alinear un par de datos sueltos.
