# A8 — Corrige el código inseguro

Programación Avanzada para Ciberseguridad (PAC) — Fase 1

## El escenario

`src/registro_estudiantes.cpp` es un programa que **compila sin errores**, pero tiene **5 fallas reales** relacionadas con desbordamiento de buffer y mal manejo de punteros/memoria dinámica — exactamente los temas de Fase 1. El programa puede parecer que funciona, pero su comportamiento es **impredecible**: puede fallar, corromper datos, o cerrarse abruptamente según la entrada.

**Su tarea no es reescribirlo desde cero.** Es encontrar cada falla, entender por qué es un problema, y corregirla — manteniendo exactamente la misma funcionalidad (registrar estudiantes, sus calificaciones, y calcular su promedio).

## Cómo compilar y ejecutar

```bash
g++ -Wall -Wextra src/registro_estudiantes.cpp -o registro
./registro
```

**Presten atención a las advertencias del compilador** (`-Wall -Wextra`) — el compilador ya les está avisando de al menos uno de los 5 problemas antes de que ejecuten una sola línea.

## Herramientas que les van a ayudar a encontrar el resto

El compilador no detecta todo. Estas herramientas sí:

```bash
# AddressSanitizer: detecta errores de memoria en tiempo de ejecución
g++ -fsanitize=address -g src/registro_estudiantes.cpp -o registro_asan
./registro_asan
```

En Linux, si tienen Valgrind instalado, también funciona:

```bash
valgrind --leak-check=full ./registro
```

No es obligatorio usar estas herramientas para resolver el reto, pero les va a ahorrar mucho tiempo — les dicen exactamente en qué línea ocurre el problema.

## Pistas

Hay exactamente **5 fallas**, una por cada una de estas categorías.:

1. **Una función retorna un puntero a algo que ya no existe.** ¿Qué pasa con una variable local cuando la función en la que vive termina?
2. **Una copia de texto no verifica el tamaño del destino.** ¿Qué tan grande es `nombre[20]`? ¿Qué tan largo es el texto que se le está copiando?
3. **Un ciclo escribe un elemento de más en un arreglo.** Cuenten con cuidado desde dónde hasta dónde debería llegar el índice.
4. **Algo reservado con `new[]` no se libera con la pareja correcta.** Repasen la diferencia entre `delete` y `delete[]`.
5. **Ese mismo punto anterior tiene un problema adicional**, relacionado con cuántas veces se libera la misma memoria.

## Cómo saber que ya lo resolvieron

- El programa compila **sin ninguna advertencia** con `-Wall -Wextra`.
- El programa se ejecuta y termina normalmente, imprimiendo `Programa terminado.`, sin *Segmentation fault* ni comportamiento errático.
- Si corren con AddressSanitizer o Valgrind, **no debe reportar ningún error**.
- El nombre del estudiante se sigue mostrando correctamente, y el promedio calculado sigue siendo correcto (80, con los datos de ejemplo del programa).

## Entrega

Suban su `registro_estudiantes.cpp` corregido a su repositorio, y agreguen al final de este README una tabla breve como esta, describiendo cada falla que encontraron **en sus propias palabras** (no copien las pistas):

| # | ¿Dónde estaba la falla? | ¿Por qué era un problema? | ¿Cómo la corrigieron? |
|---|---|---|---|
| 1 |calcularPromedio() |Retornaba la dirección de memoria |Cambié el tipo de valor a int para devolver el valor directamente en lugar de un puntero y modificar tambien en el main|
| 2 | registrarNombre()|Al intentar almacenar un nombre muy largo se desbordaba |Reemplace strcpy por strncpy() para limitar la copia al tamaño máximo del arreglo y agregue tambien el caracter nulo|
| 3 | registrarCalificaciones()|El ciclo usaba la condición i <= si pasábamos 5 como cantidad, intentaba escribir en el índice 5, el cual no es posible porque el arreglo es de 5 elementos |Cambie la condición de salida del ciclo a i < |
| 4 |liberarGrupo() |Se utilizaba un delete sin corchetes para liberar la memoria pero el grupo fue declarado como un arreglo usando new[]. Esto provoca que no se libere todo el bloque de memoria | Cambie la instrucción delete grupo; por delete[] grupo;|
| 5 |liberarGrupo|Tras liberar la memoria, el puntero seguía conservando la misma dirección|Modifique la función para recibir el puntero por referencia y le asigné nullptr inmediatamente después de usar delete|
