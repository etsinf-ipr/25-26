/*
  Ejercicio 4: Modifica el programa anterior para que siga lanzando la moneda 
  hasta que salgan tres caras seguidas. Indica el número de caras y de cruces 
  en total que han salido. Opcional: imprime "o" para las caras y "x" para las 
  cruces, para comprobar el funcionamiento del programa.
  */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    // Inicializar la semilla para números aleatorios
    srand(time(NULL));
    
    // Variables para contar
    int caras_seguidas = 0;
    int total_caras = 0;
    int total_cruces = 0;
    int resultado;
    
     while (caras_seguidas < 3) {
        resultado = rand() % 2;
        if (resultado == 0) { //cara
            printf("o");
            caras_seguidas++;
            total_caras++;
        } else {               //cruz
            printf("x");
            caras_seguidas = 0; // Reiniciar contador
            total_cruces++;
        }
    }
    
    printf("\nTotal de caras: %d\n", total_caras);
    printf("Total de cruces: %d\n", total_cruces);
    
    return 0;
}