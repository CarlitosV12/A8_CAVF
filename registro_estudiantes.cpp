/*
 * ============================================================
 *  registro_estudiantes.cpp
 * ============================================================
 *  Sistema simple de registro de calificaciones.
 *
 *  ESTE PROGRAMA COMPILA, PERO TIENE ERRORES REALES DE
 *  SEGURIDAD Y MANEJO DE MEMORIA. Su comportamiento es
 *  IMPREDECIBLE: puede funcionar "bien" varias veces y
 *  luego fallar, corromper datos, o cerrarse abruptamente.
 *
 *  Su tarea NO es reescribirlo desde cero: es encontrar y
 *  corregir cada error, manteniendo la misma funcionalidad
 *  (registrar estudiantes, sus calificaciones, y calcular
 *  su promedio).
 *
 *  Instrucciones de compilación y pistas: ver README.md
 * ============================================================
 */

#include <iostream>
#include <cstring>
using namespace std;

struct Estudiante {
    char nombre[20];
    int calificaciones[5];
};

// Calcula el promedio de calificaciones de un estudiante.
int* calcularPromedio(Estudiante e) {
    int promedio = 0;
    for (int i = 0; i < 5; i++) {
        promedio += e.calificaciones[i];
    }
    promedio /= 5;
    return &promedio;
}

// Registra el nombre de un estudiante a partir de una cadena de entrada.
void registrarNombre(Estudiante &e, const char* nombreIngresado) {
    strcpy(e.nombre, nombreIngresado);
}

// Registra las calificaciones de un estudiante.
void registrarCalificaciones(Estudiante &e, int calif[], int cantidad) {
    for (int i = 0; i <= cantidad; i++) {
        e.calificaciones[i] = calif[i];
    }
}

// Crea dinámicamente un grupo de "cantidad" estudiantes.
Estudiante* crearGrupo(int cantidad) {
    Estudiante* grupo = new Estudiante[cantidad];
    return grupo;
}

// Libera la memoria del grupo.
void liberarGrupo(Estudiante* grupo) {
    delete grupo;
}

int main() {
    Estudiante* grupo = crearGrupo(3);

    int notas1[5] = {80, 90, 70, 60, 100};
    registrarCalificaciones(grupo[0], notas1, 5);
    registrarNombre(grupo[0], "Ana Garcia Lopez de un nombre bastante largo");

    int* promedio = calcularPromedio(grupo[0]);
    cout << "Promedio de " << grupo[0].nombre << ": " << *promedio << endl;

    liberarGrupo(grupo);

    cout << "Programa terminado." << endl;
    return 0;
}
