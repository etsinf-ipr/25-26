/*
  Ejercicio 1: Escribe un programa en C que resuelva una ecuación de segundo grado
 
  Una ecuación de segundo grado tiene la forma: ax² + bx + c = 0
  Se resuelve usando la fórmula: x = (-b ± √(b²-4ac)) / 2a
 */

#include <stdio.h>
#include <math.h>

int main() {
    // Declaración de variables
    float a, b, c;
    float discriminante;
    float x1, x2;
    
    // Entrada de datos
    printf("Ecuación de segundo grado: ax2 + bx + c = 0\n");
    printf("a: ");
    scanf("%f", &a);
    printf("b: ");
    scanf("%f", &b);
    printf("c: ");
    scanf("%f", &c);
    
    // Verificar que 'a' no sea cero
    if (a == 0) {
        printf("x = %.2f\n", -c/b);
    }
    else {
        discriminante = b * b - 4 * a * c;
        if (discriminante >=0) {
            x1 = (-b + sqrt(discriminante)) / (2 * a);
            x2 = (-b - sqrt(discriminante)) / (2 * a);
            printf("x1 = %.2f\n", x1);
            printf("x2 = %.2f\n", x2);
        }
        else {
            printf("La ecuación no tiene soluciones reales.\n");
            // piensa cómo obtener las soluciones complejas
        }
    }
    return 0;

}