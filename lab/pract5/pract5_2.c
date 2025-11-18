/*
Enunciado: Define una función para validar que la hora de la estructura
struct time es válida y otra que devuelva la hora expresada en minutos
totales desde las 00:00. Revisa el código de las prácticas anteriores.
Amplia la función main de la actividad anterior para probar las funcio-
nes creadas (en un fichero nuevo).
*/

#include <stdio.h>

struct time {
    int hora;
    int minutos;
};

int hora_valida(struct time t) {
    return (t.hora >= 0 && t.hora < 24) && (t.minutos >= 0 && t.minutos < 60);
}

int minutos_totales(struct time t) {
    return t.hora * 60 + t.minutos;
}

int main() {
    struct time t;

    // obtiene una hora válida
    do {
        printf("Introduce la hora (0-23): ");
        scanf("%d", &t.hora);
        printf("Introduce los minutos (0-59): ");
        scanf("%d", &t.minutos);
    }while(hora_valida(t) == 0);
    
    // muestra los minutos totales desde las 00:00  
    printf("Minutos totales: %d\n", minutos_totales(t));
    return 0;
}
