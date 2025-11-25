/*
Escribe un programa en C para manejar una estructura que represente un punto/vector bidimensional en el plano real. el programa debe definir:

una estructura punto formada por dos coordenadas reales
una función muestra que imprime el punto con el format (x,y)
una función modulo que devuelve el módulo del vector
una función que devuelve el producto escalar 
una función que devuelve la distancia entre dos puntos
una función que devuelve el ańgulo que forman
*/

#include <stdio.h>
#include <math.h>

// Definición de la estructura punto
struct punto {
    double x;
    double y;
};  

// Función para mostrar un punto en formato (x,y)
void muestra(struct punto p) {
    printf("(%.2f, %.2f)\n", p.x, p.y);
}   

// Función para calcular el módulo de un punto/vector
// fórmula: |A| = √(x² + y²)
double modulo(struct punto p) {
    return sqrt(p.x * p.x + p.y * p.y);
}

// Función para calcular el producto escalar entre dos puntos/vectores
// fórmula: A · B = x1*x2 + y1*y2
double escalar(struct punto p1, struct punto p2) {
    return p1.x * p2.x + p1.y * p2.y;
}

// Función para calcular la distancia entre dos puntos
// fórmula: d = √((x2 - x1)² + (y2 - y1)²)
double distancia(struct punto p1, struct punto p2) {
    double difx = p2.x - p1.x;
    double dify = p2.y - p1.y;
    return sqrt(difx * difx + dify * dify);
}

// Función para calcular el ángulo entre dos puntos/vectores en radianes
// fórmula: cos(θ) = (A · B) / (|A| * |B|)
double angulo(struct punto p1, struct punto p2) {
    double prod_escalar = escalar(p1, p2);
    double mod1 = modulo(p1);
    double mod2 = modulo(p2);
    return acos(prod_escalar / (mod1 * mod2));
}

int main() {
    struct punto p;
    
    // Entrada de datos para el primer punto
    printf("Introduce las coordenadas del primer punto (x y): ");
    scanf("%g%g", &p.x, &p.y);

    muestra(p);
    printf("Módulo: %.2f\n", modulo(p));
    
    struct punto q;
    // Entrada de datos para el segundo punto
    printf("Introduce las coordenadas del segundo punto (x y): ");
    scanf("%g%g", &q.x, &q.y);
    printf("Producto escalar: %.2f\n", escalar(p, q));
    printf("Distancia entre los puntos: %.2f\n", distancia(p, q));
    printf("Ángulo entre los puntos: %.2f rad\n", angulo(p, q));
    
    return 0;
}