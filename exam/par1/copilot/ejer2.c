/*
 * Ejercicio 2 (1 punto): Año bisiesto
 * 
 * Un año es bisiesto si es divisible entre 4, excepto si es divisible entre 100, 
 * pero sí lo es si es divisible entre 400. Escribe el código necesario que muestre 
 * por pantalla un mensaje indicando si un año que introduce el usuario es o no 
 * bisiesto. No es necesario el main() ni los includes, pero sí la declaración de 
 * todas las variables necesarias.
 */

#include <stdio.h>

int main() {
    int anio;
    int es_bisiesto;
    
    // Pedir el año al usuario
    printf("Introduce un año: ");
    scanf("%d", &anio);
    
    // Determinar si es bisiesto
    // Un año es bisiesto si:
    // - Es divisible entre 4 Y
    // - NO es divisible entre 100, O si es divisible entre 400
    if (anio % 4 == 0) {
        if (anio % 100 == 0) {
            if (anio % 400 == 0) {
                es_bisiesto = 1; // Divisible entre 400
            } else {
                es_bisiesto = 0; // Divisible entre 100 pero no entre 400
            }
        } else {
            es_bisiesto = 1; // Divisible entre 4 pero no entre 100
        }
    } else {
        es_bisiesto = 0; // No divisible entre 4
    }
    
    // Mostrar el resultado
    if (es_bisiesto) {
        printf("El año %d ES bisiesto.\n", anio);
    } else {
        printf("El año %d NO es bisiesto.\n", anio);
    }
    
    return 0;
}
