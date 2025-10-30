/*
 * Ejercicio 5 (4 puntos): Pares cuadrados
 * 
 * Dos números son pares cuadrados si su suma y su diferencia son un cuadrado 
 * perfecto (4, 9, 25, 36, ...). Por ejemplo, 10 y 26 son pares cuadrados ya que:
 * - 10 + 26 = 36 = 6²
 * - 26 - 10 = 16 = 4²
 * 
 * Escribe un programa en C que imprima los pares cuadrados menores de 100.
 */

#include <stdio.h>
#include <math.h>

int main() {
    printf("Pares cuadrados menores de 100:\n");
    
    // Iterar sobre todos los pares de números menores de 100
    for (int a = 1; a < 100; a++) {
        for (int b = a + 1; b < 100; b++) {
            int suma = a + b;
            int diferencia = b - a;
            
            // Verificar si la suma es un cuadrado perfecto
            int raiz_suma = (int)sqrt(suma);
            int es_suma_cuadrado = (raiz_suma * raiz_suma == suma);
            
            // Verificar si la diferencia es un cuadrado perfecto
            int raiz_diferencia = (int)sqrt(diferencia);
            int es_diferencia_cuadrado = (raiz_diferencia * raiz_diferencia == diferencia);
            
            // Si ambos son cuadrados perfectos, son pares cuadrados
            if (es_suma_cuadrado && es_diferencia_cuadrado) {
                printf("(%d, %d): %d + %d = %d = %d², %d - %d = %d = %d²\n",
                       a, b, a, b, suma, raiz_suma, b, a, diferencia, raiz_diferencia);
            }
        }
    }
    
    return 0;
}
