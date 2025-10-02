/*
  Ejercicio 3: Escribe un programa en C que simula el lanzamiento de una moneda.
  
  El programa generará un número aleatorio y mostrará si salió cara o cruz.
 */

#include <stdio.h>
#include <stdlib.h> // Para rand() y srand()
#include <time.h>.  // Para time()

int main() {
    // Inicializar la semilla para números aleatorios
    // para que en cada ejecución se generen diferentes resultados
    srand(time(NULL));

    // rand() genera un número entre 0 y RAND_MAX   
    // que es el mayor entero que puede generar el ordenador
    int resultado = rand() % 2;
    if (resultado == 0) {
        printf("cara\n");
    } else {
        printf("cruzn");
    }
    
    return 0;
}