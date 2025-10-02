/*
  Ejercicio 4: Modifica el programa anterior para que siga lanzando la moneda 
  hasta que salgan tres caras seguidas. 
  
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    // Inicializar la semilla para números aleatorios
    srand(time(NULL));
    
    // Variables para contar
    int resultado, caras_seguidas = 0;
    
    while (caras_seguidas < 3) {
        resultado = rand() % 2;
        printf("%d", resultado); //para comprobar que se para
        if (resultado == 0)
            caras_seguidas++;
        else 
            caras_seguidas = 0; // Reiniciar contador
    }
    printf("\n");
    
    return 0;
}