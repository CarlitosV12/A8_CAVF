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
//devolver el int con valo r 
int calcularPromedio(Estudiante e) {
    int promedio = 0;
    for (int i = 0; i < 5; i++) {
        promedio += e.calificaciones[i];
    }
    promedio /= 5;
    //Eror 1
    // return &promedio;    EL error aqui es que estaba retornando una direccion en vez de la variable 
    return promedio; 
    //Aqui regresamos la varialbe 
}
//https://learn.microsoft.com/es-es/cpp/cpp/sizeof-operator?view=msvc-170
//https://stackoverflow.com/questions/4054284/sizeof-for-a-null-terminated-const-char

//Error 2 , aqui garantizamos que temrine correctamente

// Registra el nombre de un estudiante a partir de una cadena de entrada.
void registrarNombre(Estudiante &e, const char* nombreIngresado) {
    
    strncpy(e.nombre, nombreIngresado, sizeof(e.nombre) - 1);
    
    e.nombre[sizeof(e.nombre)-1] = '\0'; // Garantizar terminación nula
}

// Registra las calificaciones de un estudiante.

//Error 3  el <= debe ser para que aplique bien <
void registrarCalificaciones(Estudiante &e, int calif[], int cantidad) {
    for (int i = 0; i < cantidad; i++) {
        e.calificaciones[i] = calif[i];
    }
}

// Crea dinámicamente un grupo de "cantidad" estudiantes.
Estudiante* crearGrupo(int cantidad) {
    Estudiante* grupo = new Estudiante[cantidad];
    return grupo;
}

// Libera la memoria del grupo.
//https://stackoverflow.com/questions/4670782/the-difference-between-delete-and-delete-in-c
//https://learn.microsoft.com/es-es/cpp/extensions/nullptr-cpp-component-extensions?view=msvc-170

//Errores 4 y 5 
void liberarGrupo(Estudiante* grupo) {
    // delete grupo;
    delete[] grupo; // Se usa asi para borrar todo en la memoria 
    grupo = nullptr; // Se anula el puntero para evitar doble lievion 
}

int main() {
    Estudiante* grupo = crearGrupo(3);

    int notas1[5] = {80, 90, 70, 60, 100};
    registrarCalificaciones(grupo[0], notas1, 5);
    registrarNombre(grupo[0], "Ana Garcia Lopez de un nombre bastante largo");
    // int por valor
    int promedio = calcularPromedio(grupo[0]);
    cout << "Promedio de " << grupo[0].nombre << ": " << promedio << endl;
    // *promedio por promedio
    liberarGrupo(grupo);

    cout << "Programa terminado." << endl;
    return 0;
}
