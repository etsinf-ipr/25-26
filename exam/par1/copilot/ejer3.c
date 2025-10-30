/*
 * Ejercicio 3 (2 puntos): Suma de dígitos
 * 
 * Escribe un programa en C que suma los dígitos de un número entero positivo 
 * que se le pasa por línea de comandos. Utiliza el tipo de bucle más adecuado. 
 * No es necesario validar las entradas.
 * 
 * Ejemplo:
 * $ suma 236
 * suma: 11
 */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Uso: %s <numero>\n", argv[0]);
        return 1;
    }
    
    int numero = atoi(argv[1]);
    int suma = 0;
    int digito;
    
    // Usar un bucle while para extraer cada dígito
    while (numero > 0) {
        digito = numero % 10;  // Obtener el último dígito
        suma += digito;         // Sumar el dígito
        numero /= 10;           // Eliminar el último dígito
    }
    
    // Mostrar el resultado
    printf("suma: %d\n", suma);
    
    return 0;
}
