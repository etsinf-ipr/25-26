/*
 * 3.2. Pasar una hora en formato 24 horas a formato 12 horas
 * 
 * Escribe un programa en C que pida una hora representada
 * en formato 24 horas, con formato HH:MM; si la hora es válida, imprimirá
 * la hora equivalente en formato 12 horas, es decir, con la marca AM o PM
 * según sea anterior o posterior a las 12:00 (Nota: las 00:00 son las 12:00
 * AM y las 12:00 son las 12:00 PM).
 */

#include <stdio.h>

int main() {
    int horas, minutos, es_am;;
    
    do{
        printf("Introduce una hora (HH:MM): ");
        scanf("%d:%d", &horas, &minutos);
    }while(horas < 0 || horas > 23 || minutos < 0 || minutos > 59); 

    // cambio a formato 12 horas
    if(horas < 12) {
        es_am = 1;
        // las 00:xx es un caso especial: 12:00 AM 
        if(horas == 0) 
            horas = 12;
        printf("%02d:%02d %s\n", horas, minutos, "AM");
    } else {
        es_am = 0;
        // las 12:xx es un caso especial: PM pero no se resta
        if(horas > 12) 
            horas -= 12;
        printf("%02d:%02d %s\n", horas, minutos, "PM");

    }

    //usando operador ternario
    //char *periodo = es_am ? "AM" : "PM";
    //printf("Hora en formato 12 horas: %02d:%02d %s\n", horas, minutos, periodo);

    return 0;
}
