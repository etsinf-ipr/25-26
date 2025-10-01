/*
 * Ejercicio 7: Leer n notas (0–10) y calcula la media de las que sean correctas
 * 
 * Descripción: Programa que calcula la media de notas válidas en el rango 0-10
 */

#include <stdio.h>

int main() {
    // Declaración de variables
    int n;
    float nota, suma = 0;
    int notasValidas = 0;
    
    // Entrada de datos
    printf("¿Cuántas notas vas a introducir? ");
    scanf("%d", &n);
    
    printf("Introduce %d notas (0-10):\n", n);
    
    // Procesamiento con if-else
    for (int i = 1; i <= n; i++) {
        printf("Nota %d: ", i);
        scanf("%f", &nota);
        
        if (nota >= 0 && nota <= 10) {
            suma += nota;
            notasValidas++;
        } else {
            printf("Nota inválida (debe estar entre 0 y 10). No se incluye en la media.\n");
        }
    }
    
    // Salida de resultados
    if (notasValidas > 0) {
        float media = suma / notasValidas;
        printf("Media de las %d notas válidas: %.2f\n", notasValidas, media);
    } else {
        printf("No se introdujeron notas válidas.\n");
    }
    
    return 0;
}
