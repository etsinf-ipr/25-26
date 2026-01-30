// anillo.c
// Este archivo une la lógica de los módulos de rec: activo, actualizar, crear, hueco, init, media, sensor
// y añade la función nuevo_estado para generar un estado de prueba.


#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define INF 999999
#define UMBRAL 100


// Estructura que representa un sensor con su ángulo, estado y distancia
struct sensor {
    float ang;    // Ángulo del sensor en radianes
    int activo;   // 1 si está activo, 0 si no
    int dist;     // Distancia medida por el sensor
};

// Crea un sensor con un ángulo dado, inactivo y distancia infinita
struct sensor crear(float angulo) {
    // también válido: struct sensor s = {angulo, 0, INF};
    struct sensor s;
    s.ang = angulo;
    // activo=0 y dist=INF | activo=1 y dist=0
    s.activo = 0;
    s.dist = INF;
    return s;
}

// Actualiza el estado de un sensor según la distancia medida
void actualizar(struct sensor *s, int d) {
    s->dist = d;
    if(d < UMBRAL)
        s->activo = 1;
    else
        s->activo = 0;
    // también: s->activo = d < UMBRAL ? 1 : 0;
}

// Inicializa el anillo de sensores con ángulos equiespaciados
void init(struct sensor sensor[]) {
    for (int i = 0; i < 16; i++)
        // cada sensor está a 360/16=22,5º (en radianes)
        // 0 - 22,5 - 45 - 67,5 - 90...
        sensor[i] = crear(i * (2 * M_PI / 16.0));
}

// Calcula la media de las distancias de los sensores activos
float media(struct sensor s[]) {
    float total = 0;
    int num = 0;           // elementos no INF
    for(int i = 0; i < 16; i++) {
        if( s[i].dist < INF) {
            total += s[i].dist;
            num++; 
        }
    }
    if (num == 0)
        return 0; // evita división por cero
    else
        return total / num; 
}

// Busca los huecos (secuencias de sensores inactivos) en el anillo
void hueco(struct sensor anillo[], int huecos[], int *nhuecos) {
    int j = 0;    // número de huecos
    int tam = 0;  // tamaño del hueco actual
    for (int i = 0; i < 16; i++) {
        // activo -> incrementa el hueco actual
        if (anillo[i].activo == 0) {
            tam++;
        } 
        // no activo
        else if (tam > 0) {
            // guarda hueco actual
            huecos[j] = tam;
            j++;
            // prepara el hueco nuevo
            tam = 0;
        }
    }
    // hay que indicar cuántos huecos ha encontrado
    *nhuecos =  j;
}

// Genera un estado de prueba para el anillo, 
// (no es parte del examen)
void nuevo_estado(struct sensor anillo[]) {
    // estado que genera {1,0,0,1,0,0,0,1,1,0,1,0,0,1,1,1}
    int activo[] = {1,0,0,1,0,0,0,1,1,0,1,0,0,1,1,1};
    for (int i = 0; i < 16; i++) {
        actualizar(&anillo[i], activo[i] ? UMBRAL-50 : UMBRAL+50);
    }
    // fuerza algunos INF
    actualizar(&anillo[1], INF);    
    actualizar(&anillo[2], INF);  
}


int main() {
    // crea el anillo de sensores
    struct sensor an[16];
    init(an);
    // Generar estado de prueba (No es parte del examen)
    nuevo_estado(an);
    // calcula la media
    float m = media(an);
    // busca huecos
    int h[16];  // vector de huecos
    int numh;   // número de huecos
    hueco(an, h, &numh);
    // busca el máximo en el vector de huecos
    int max = 0;   // tamaño del mayor hueco
    for (int i = 0; i < numh; i++)
        if(h[i] > max)
            max = h[i];
    // imprime los resultados
    printf("dist media: %.2f (esperado: 92.86)\n", m);
    printf("hueco: %d (esperado: 3)\n", max);
    return 0;
}
