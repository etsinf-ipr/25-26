/*
  Ejercicio 5: Escribe un programa en C para adivinar un número entre 1 y 100 
  que ha pensado el ordenador. El ordenador te dará pistas indicando si su número 
  es mayor o menor. El programa se detendrá cuando lo adivines o tras 6 intentos. 
  Si no lo aciertas, mostrará el número que había pensado.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    // Inicializar la semilla para números aleatorios
    srand(time(NULL));
    
    // El ordenador "piensa" un número entre 1 y 100
    int numero_secreto = rand() % 100 + 1;
    int mi_numero;
    int intentos = 0;
    int max_intentos = 6;
     
    // Bucle de intentos
    while (intentos < max_intentos) {
        printf("Número: ");
        scanf("%d", &mi_numero);
        if (numero_secreto > mi_numero) {
            printf("El número es MAYOR que %d.\n", mi_numero);
        } 
        else if (numero_secreto < mi_numero) {
            printf("El número es MENOR que %d.\n", mi_numero);
        }
        else {
            printf("¡Felicidades! Has adivinado el número.\n");
            return 0;
        }
        intentos++;
    }
    printf("El número que había pensado era: %d\n", numero_secreto);
    return 0;
}