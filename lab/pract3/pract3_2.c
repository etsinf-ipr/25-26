/*
 * Problema 3.2: Promedio de un conjunto de mediciones
 * 
 * Enunciado: Escribe un programa que pida cuántas temperaturas desea
 * introducir el usuario (un número entero positivo, menor o igual que 10).
 * A continuación, lee las temperaturas una a una (validando cada una como
 * en el ejercicio anterior) y calcula el promedio. Muestra el resultado con
 * dos decimales. 
 * 
 * A continuación, muestra un mensaje que indique si la
 * temperatura promedio es alta (superior a los 25 °C) o normal. Usa un
 * operador ternario.
 */

#include <stdio.h>

// Macro para validar temperatura en el rango [-100, +80]
#define temp_valida(temp) ((temp) >= -100 && (temp) <= 80)

int main() {
    int num_temperaturas;
    float temperatura, suma = 0.0, promedio;
    
    printf("¿Cuántas temperaturas desea introducir? (1-10): ");
    scanf("%d", &num_temperaturas);
    
    // introducción de temperaturas y suma
    for (int i = 0; i < num_temperaturas; i++) {
        do {
            printf("Introduce la temperatura %d: ", i);
            scanf("%f", &temperatura);         
        } while (!temp_valida(temperatura));
        
        suma += temperatura;
    }
    // calculo de promedio
    promedio = suma / num_temperaturas;
    printf("\nPromedio de temperaturas: %.2f°C\n", promedio);
    // temperatura normal/alta (op ternario)
    printf("La temperatura promedio es %s.\n", 
           promedio > 25 ? "alta" : "normal");
    
    return 0;
}
