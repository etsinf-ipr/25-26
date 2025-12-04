/*
    programa para jugar al siete y medio
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

enum PALO { OROS, COPAS, ESPADAS, BASTOS };
// forma alternativa de typedef usando estructuras anónimas.
typedef struct {
    enum PALO palo;
    int valor; // 1-7, 8-10 (figuras)
    double puntos; // puntos que vale la carta (8-10 valen 0.5)
} carta; // OJO: carta no es una variable, es el tipo de datos


void crear (carta baraja[]) {
    for(int i=0; i<40; i++) {
        // usa la misma estrategia del reloj con horas / minutos
        baraja[i].palo = i / 10; // cada 10 cartas cambia de palo 
        baraja[i].valor = (i % 10) + 1; // valores del 1 al 10
        baraja[i].puntos = baraja[i].valor > 7 ? 0.7 : baraja[i].valor;
    }
    /* alternativa con dos bucles anidados 
    for (int palo = OROS; palo <= BASTOS; palo++) {
        for (int valor = 1; valor <= 10; valor++) {
            int i = palo * 10 + (valor - 1);
            baraja[i].palo = palo;
            baraja[i].valor = valor;
            baraja[i].puntos = valor > 7 ? 0.5 : valor;
        }
    }
    */
}

void swap (carta *a, carta *b) {
    carta temp = *a;
    *a = *b;
    *b = temp;
}


void barajar(carta baraja[]) {
    // inicializa la semilla para los números aleatorios
    // solo se hace una vez en toda la partida y aquí queda oculto
    // si se baraja varias veces, hay que sacarlo al main()
    srand(time(NULL)); 
    for(int i=0; i<1000; i++) {
        int pos1 = rand() % 40; // posición aleatoria entre 0 y 39
        int pos2 = rand() % 40; // posición aleatoria entre 0 y 39 (da igual que se repita)
        // intercambiar las cartas en las posiciones pos1 y pos2
        //método habitual para intercambiar dos variables
        carta temp = baraja[pos1];
        baraja[pos1] = baraja[pos2];
        baraja[pos2] = temp;
    }
}

// algoritmo de barajado: fisher-yates (Knuth)
// https://es.wikipedia.org/wiki/Algoritmo_de_Fisher-Yates
void barajar_yates (carta baraja[]) {
    // inicializa la semilla para los números aleatorios
    // solo se hace una vez en toda la partida y aquí queda oculto
    // si se baraja varias veces, hay que sacarlo al main()
    srand(time(NULL)); 
    for(int i=39; i>0; i--) {
        // elige una posición aleatoria entre 0 e i
        int j = rand() % (i + 1); // puede ser i y quedarse donde está
        swap(&baraja[i], &baraja[j]);
    }
}


void imprimir (carta baraja[]) {
    // misma estrategia que para la letra del NIF
    const char nompalo[] ="OCEB"; // nombres cortos de los palos
    const char nomcarta[] = " A234567JQK"; // nombres cortos de las cartas 
    for(int i=0; i<40; i++) {
        int palo = baraja[i].palo;
        int valor = baraja[i].valor;
        // se puede hacer todo en una línea, pero para mayor claridad se separa
        printf("%c%c ", nomcarta[valor], nompalo[palo]);
    }
    printf("\n");
}



int main(){
    carta baraja[40];

    crear(baraja);
    imprimir(baraja);

    carta baraja2[40];
    barajar_yates(baraja2);
    imprimir(baraja2);

    
    return 0;
}