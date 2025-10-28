/*
 * Ejercicio 8: Promedio de notas válidas
 * 
 * El programa solicita notas entre 0 y 10. Después de cada nota válida, pregunta 
 * si desea introducir otra ('s' o 'n'). Cuando el usuario responde 'n', muestra 
 * el promedio de las notas introducidas.
 */

#include <stdio.h>

int main() {
    float nota, suma = 0;
    int contador = 0;
    char respuesta;

    do {
        // Solicitar nota y validar
        do {
            printf("Introduce una nota (0-10): ");
            scanf("%f", &nota);
        } while(nota < 0 || nota > 10);
        // Añade la nota y aumenta el contador
        suma += nota;
        contador++;

        // Preguntar si desea continuar
        printf("¿Otra? (s/n): ");
        scanf(" %c", &respuesta);
    } while(respuesta == 's' || respuesta == 'S');
    printf("Promedio: %.2f\n", suma / contador);
    return 0;
}
