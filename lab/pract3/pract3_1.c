/*
 * Problema 3.1: Validación de una medición
 * 
 * Enunciado: Define una macro que evalúe si una temperatura (en °C)
 * es válida, para lo que debe encontrarse en el rango entre –100 y +80.
 * Escribe un programa en C para comprobar que funciona correctamente.
 */

#include <stdio.h>

// Macro para validar temperatura en el rango [-100, +80]
#define temp_valida(temp) ((temp) >= -100 && (temp) <= 80)

int main() {
    float temperatura;
    
    printf("Introduce una temperatura:");
    scanf("%f", &temperatura);
    
    if (temp_valida(temperatura)) 
        printf("La temperatura %.2f°C es VALIDA.\n", temperatura);
    else 
        printf("La temperatura %.2f°C NO es válida.\n", temperatura);

    
    return 0;
}
