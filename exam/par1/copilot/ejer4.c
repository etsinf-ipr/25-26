/*
 * Ejercicio 4 (2 puntos): Número oblongo
 * 
 * Un número oblongo es igual al producto de dos números consecutivos.
 * Ejemplo: 6 es un número oblongo porque 2*3=6
 * 
 * Escribe un programa en C que determine si un entero que se genera al azar 
 * entre 0 y 99 es oblongo o no. Si lo es, escribe el producto de los dos números 
 * consecutivos. Si no lo es, escribe un mensaje indicándolo.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    // Inicializar generador de números aleatorios
    srand(time(NULL));
    
    // Generar número aleatorio entre 0 y 99
    int numero = rand() % 100;
    
    printf("Número generado: %d\n", numero);
    
    // Verificar si es oblongo
    // Un número oblongo es n * (n+1)
    // Probar todos los valores posibles de n desde 0 hasta que n*(n+1) > numero
    int es_oblongo = 0;
    int n = 0;
    
    while (n * (n + 1) <= numero) {
        if (n * (n + 1) == numero) {
            es_oblongo = 1;
            break;
        }
        n++;
    }
    
    // Mostrar el resultado
    if (es_oblongo) {
        printf("%d ES un número oblongo: %d * %d = %d\n", 
               numero, n, n+1, numero);
    } else {
        printf("%d NO es un número oblongo.\n", numero);
    }
    
    return 0;
}
