/*
 * 3.4. Entrada de horas hasta una cierta condición
 * 
 * Escribe un programa en C que vaya pidiendo horas válidas
 * (formato 24 horas HH:MM, si no es válida volverá a pedirla). Continuar
 * siempre que las horas se introduzcan en orden creciente. El programa
 * terminará cuando la hora introducida sea menor que la anterior.
 */

#include <stdio.h>

int main() {
    int horas, minutos; // hora introducida
    int anterior, actual = -1; //hora anterior y actual en minutos;
    int creciente = 1;
    int contador = 0;
    
    printf("Introduce horas en orden creciente.\n");
    
    while (creciente) {
        // Pedir hora hasta que sea válida
        do{
            printf("(HH:MM)> ");
            scanf("%d:%d", &horas, &minutos);
        }while(horas < 0 || horas > 23 || minutos < 0 || minutos > 59); 
        // iteración n-1:           anterior actual
        //                            15:35  16:00
        // iteración n:      15:35    16:00  (nuevo valor) <-- (es como si empujamos)
        // la antigua hora actual se convierte en la anterior y la nueva en actual
        anterior = actual;
        actual = horas * 60 + minutos;
        if( anterior < actual )
            // incrementamos el número de horas introducidas
            contador++;
        else 
            // para salir del bucle cuando no sean crecientes
            creciente = 0;
    }
    printf("\nSe han introducido %d horas en orden creciente.\n", contador);
    return 0;
}
