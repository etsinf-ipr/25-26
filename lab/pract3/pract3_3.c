/*
 * Problema 3.3: Conversión de unidades de temperatura
 * 
 * Enunciado: Escribe un programa que lea una temperatura en grados
 * Celsius y permita convertirla a otra unidad de medida elegida por el
 * usuario. El programa mostrará un menú con las siguientes opciones:
 * 1. Convertir a Fahrenheit
 * 2. Convertir a Kelvin
 * 3. Convertir a Rankine
 * 4. Salir
 * El usuario elegirá una opción (1–4), y el programa realizará la conversión
 * usando un switch. El proceso se repetirá hasta que el usuario seleccione
 * la opción 4.
 * 
 * Fórmulas de conversión:
 * Fahrenheit = Celsius × 9/5 + 32
 * Kelvin = Celsius + 273.15
 * Rankine = (Celsius + 273.15) × 9/5
 */

#include <stdio.h>

int main() {
    float celsius;
    int opcion;
    
    printf("Introduce la temperatura en grados Celsius: ");
    scanf("%f", &celsius);
    
    do {
        // muestra el menú
        printf("\n--- MENÚ DE CONVERSIÓN ---\n");
        printf("1. Convertir a Fahrenheit\n");
        printf("2. Convertir a Kelvin\n");
        printf("3. Convertir a Rankine\n");
        printf("4. Salir\n");
        printf("Elige una opción (1-4)> ");
        scanf("%d", &opcion);

        // realiza la conversión según la opción elegida
        switch (opcion) {
            case 1:
                printf("%.2f°C = %.2f°F\n", celsius, celsius * 9.0/5.0 + 32);
                break;
            case 2:
                printf("%.2f°C = %.2fK\n", celsius, celsius + 273.15);
                break;
            case 3:
                printf("%.2f°C = %.2f°R\n", celsius, (celsius + 273.15) * 9.0/5.0);
                break;
            case 4:
                break;
            default:
                printf("Opción no válida. Por favor, elige entre 1 y 4.\n");
        }
    } while (opcion != 4);
    
    return 0;
}
