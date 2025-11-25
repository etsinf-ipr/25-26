/*
    programa que define una estrucura triangulo formada por tres
    puntos (estructuras también)

    El programa calcula el área y el perímetro del triángulo.

*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

typedef struct _punto punto;
typedef struct _triangulo triangulo;

struct _punto {
    int x;
    int y;
};

struct _triangulo {
    punto v1; //vertice 1
    punto v2; //vertice 2
    punto v3; //vertice 3
};


void imprime_punto(punto p) {
    printf("(%d, %d)", p.x, p.y);
}   

void imprime_triangulo(triangulo t) {
    imprime_punto(t.v1);
    printf(" - ");
    imprime_punto(t.v2);
    printf(" - ");
    imprime_punto(t.v3);
    printf("\n");
}

double distancia(punto p1, punto p2) {
    int dx = p2.x - p1.x;
    int dy = p2.y - p1.y;
    return sqrt(dx * dx + dy * dy);
}

double area(triangulo t) {
    // altura desde v3 al segmento v1v2
    punto medio;
    medio.x = (t.v1.x + t.v2.x) / 2.0;
    medio.y = (t.v1.y + t.v2.y) / 2.0;
    double base = distancia(t.v1, t.v2);
    double altura = t.v3.y - medio.y;
    return (base * altura) / 2;
}


double perimetro(triangulo t) {
    return distancia(t.v1, t.v2) + distancia(t.v2, t.v3) + distancia(t.v3, t.v1);
}


triangulo crear_triangulo_aleatorio() {
    triangulo t;
    t.v1.x = rand() % 10;
    t.v1.y = rand() % 10;
    t.v2.x = rand() % 10;
    t.v2.y = rand() % 10;
    t.v3.x = rand() % 10;
    t.v3.y = rand() % 10;
    return t;
}

triangulo crear_triangulo(int x1, int y1, int x2, int y2, int x3, int y3) {
    triangulo t;
    t.v1.x = x1;
    t.v1.y = y1;
    t.v2.x = x2;
    t.v2.y = y2;
    t.v3.x = x3;
    t.v3.y = y3;
    return t;
}

triangulo crear_triangulo_vertices(punto v1, punto v2, punto v3) {
    triangulo t;
    t.v1 = v1;
    t.v2 = v2;
    t.v3 = v3;
    return t;
}


int main() {
    triangulo t;

    srand(time(NULL));
    t = crear_triangulo_aleatorio();
    imprime_triangulo(t);
    printf("Área del triángulo: %.2f\n", area(t));
    printf("Perímetro del triángulo: %.2f\n\n", perimetro(t));

    t = crear_triangulo(0, 0, 1, 0, 0, 1);
    imprime_triangulo(t);
    printf("Área del triángulo: %.2f\n", area(t));
    printf("Perímetro del triángulo: %.2f\n\n", perimetro(t));

    punto v1 = {0, 0};
    punto v2 = {3, 0};
    punto v3 = {0, 4};
    t = crear_triangulo_vertices(v1, v2, v3);
    //también puede hacerse así, pasando los valores directamente sin crear variables
    // el casting (punto) es necesario para indicarle al compilador de qué estructura se trata
    // (puede haber varias con dos valores)
    //t = crear_triangulo_vertices((punto){0, 0}, (punto){3, 0}, (punto){0, 4});
    imprime_triangulo(t);
    printf("Área del triángulo: %.2f\n", area(t));
    printf("Perímetro del triángulo: %.2f\n", perimetro(t));
    return 0;
}