/*
 * Problema 3.6: Variación media (Extensión opcional)
 * 
 * Enunciado: Amplía el programa anterior para que, además de contar
 * las lecturas, calcule la variación media entre lecturas consecutivas (di-
 * ferencia promedio).
 * 
 * Conceptos relacionados: bucle while con condición dependiente de
 * valores anteriores, uso de variable para recordar la lectura previa,
 * cálculo de promedio de diferencias.
 */

#include <stdio.h>

// Macro para validar temperatura en el rango [-100, +80]
#define temp_valida(temp) ((temp) >= -100 && (temp) <= 80)

int main() {
    // uso dos temperaturas fuera de rango para asegurar que entra en while
    float tactual, tanterior = -999;
    int contador = 0;
    float diferencias = 0.0, variacion;
    
    printf("Introduce temperaturas válidas:\n");
    // leemos la primera fuera (para tener un intervalo)
    do {
        printf("> ");
        scanf("%f", &tactual);
    } while (!temp_valida(tactual));
    printf("%.2f°C\n", tactual);
    
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
        
        // Calcular la diferencia con la temperatura anterior (solo si no es la primera lectura)
        diferencias += (tactual - tanterior);
    }
    printf("\n%d temperaturas válidas en orden creciente.\n", contador);
    
    variacion = diferencias / contador;
    printf("Variación media: %.2f°C\n", variacion);
    return 0;
}
