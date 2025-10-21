/*
 * 3.5. Obtener hora válida más tardía
 * 
 * Escribe un programa en C que pida diez horas (formato 24 horas) 
 * con formato HH:MM. Cuando termine, mostrará por pantalla la hora más 
 * tardía de la secuencia. Si alguna no es válida, se volverá a pedir.
 */

#include <stdio.h>

int main() {
    int horas, minutos;
    int max = -1;
    
    printf("Introduce 10 horas en formato HH:MM.\n\n");
    
    // Pedir 10 horas
    for (int i = 0; i < 10; i++) {        
        // Repetir hasta obtener una hora válida
        do{
            printf("(HH:MM)> ");
            scanf("%d:%d", &horas, &minutos);
        }while(horas < 0 || horas > 23 || minutos < 0 || minutos > 59); 
        
        // Convertir a minutos totales para facilitar la comparación
        int minutos_totales = horas * 60 + minutos;     
        // Actualizar la hora máxima si la actual es mayor
        if (minutos_totales > max) 
            max = minutos_totales;
    }
    
    // Mostrar la hora más tardía
    printf("\nLa hora más tardía es: %02d:%02d\n", max / 60, max % 60);

    return 0;
}
