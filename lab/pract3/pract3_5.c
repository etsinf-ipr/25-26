/*
 * Problema 3.5: Secuencia creciente
 * 
 * Enunciado: Escribe un programa que lea una secuencia de temperatu-
 * ras válidas. El programa se detendrá cuando la temperatura actual sea
 * menor que la anterior. Debe mostrar todas las temperaturas leídas y el
 * número total de valores introducidos antes de detenerse.
 * 
 */

#include <stdio.h>

// Macro para validar temperatura en el rango [-100, +80]
#define temp_valida(temp) ((temp) >= -100 && (temp) <= 80)

int main() {
    // uso dos temperaturas fuera de rango para asegurar que entra en while
    float tactual = -101, tanterior = -999;
    int contador = 0;
    
    printf("Introduce temperaturas válidas:\n");
    
    //lee temperaturas mientras la siguiente no sea menor 
    while (tanterior <= tactual) {
        //guardo la temperatura anteior
        tanterior = tactual;
        // leo la nueva temperatura
        do {
            printf("> ");
            scanf("%f", &tactual);
        } while (!temp_valida(tactual));
        printf("%.2f°C\n", tactual);
        contador++;
    }
    
    printf("\n%d temperaturas válidas en orden creciente.\n", contador);
    return 0;
}
