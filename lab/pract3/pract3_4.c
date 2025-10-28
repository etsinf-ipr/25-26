/*
 * Problema 3.4: Detección de valores fuera de rango
 * 
 * Enunciado: Escribe un programa que lea una secuencia de tempera-
 * turas (todas válidas) y muestre un aviso si alguna está por debajo de
 * 0 °C o por encima de 50 °C. El proceso de lectura terminará cuando el
 * usuario introduzca una temperatura igual a 999, que servirá como valor
 * centinela para indicar el final.
 * Al finalizar, el programa mostrará el número total de valores fuera
 * de rango detectados.
 */

#include <stdio.h>

// Macro para validar temperatura en el rango [-100, +80]
#define temp_valida(temp) ((temp) >= -100 && (temp) <= 80)

int main() {
    float temperatura = 0.0;
    int fuera_rango = 0;
    
    printf("Introduce temperaturas válidas (999 para terminar):\n");
    
    while (temperatura != 999) {
        do{
            printf("Temperatura: ");
            scanf("%f", &temperatura);
        }while (!temp_valida(temperatura));

        if (temperatura < 0) {
            printf("AVISO: Temperatura por debajo de 0°C\n");
            fuera_rango++;
        } else if (temperatura > 50 && temperatura != 999) {
            printf("AVISO: Temperaturapor encima de 50°C\n");
            fuera_rango++;
        }
    }
    
    printf("\n%d valores fuera de rango.\n", fuera_rango);
    
    return 0;
}
