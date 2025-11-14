/*
 * Ejercicio 7: Función con decisiones internas
 * 
 * Escribe una función calificacion(nota) que devuelva una letra:
 * - 'A' si la nota ≥ 9
 * - 'B' si la nota ≥ 7
 * - 'C' si la nota ≥ 5
 * - 'D' en caso contrario.
 * 
 * El main() debe pedir una nota y mostrar el resultado.
 */

#include <stdio.h>

char calificacion(float nota) {
    if (nota >= 9) {
        return 'A';
    } else if (nota >= 7) {
        return 'B';
    } else if (nota >= 5) {
        return 'C';
    } else {
        return 'D';
    }
}

int main() {
    float nota;
    
    printf("Introduce una nota: ");
    scanf("%f", &nota);
    
    printf("Calificación: %c\n", calificacion(nota));
    
    return 0;
}
