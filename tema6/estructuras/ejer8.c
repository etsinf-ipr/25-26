/*
Enunciado:
Dadas tres coordenadas:
- esquina inferior izquierda
- esquina superior derecha
- un punto
escribe una función que devuelva 1 si el punto está dentro del rectángulo (latitud y longitud) definido por las esquinas indicadas. Ten en cuenta que los valores de latitud y longitud pueden ser negativos, dependiendo del hemisferio en el que se encuentren.
*/

#include <stdio.h>

struct coord {
	double latitud;
	double longitud;
};

int dentro_rect(struct coord inf_izq, struct coord sup_der, struct coord p) {
    // la latitud del punto está fuera  de los límites
	if (p.latitud < inf_izq.latitud || p.latitud > sup_der.latitud){
        return 0;
    }
    // la longitud del punto está fuera de los límites
	if (p.longitud < inf_izq.longitud || p.longitud > sup_der.longitud){
        return 0;
    }
    return 1;
}


int main(void) {
	struct coord inf_izq = { 10.0, -20.0 };
	struct coord sup_der = { 15.0, -10.0 };
	struct coord p1 = { 12.0, -15.0 }; /* dentro */
	struct coord p2 = { 16.0, -15.0 }; /* fuera lat */
	struct coord p3 = { 12.0, -25.0 }; /* fuera lon */
	printf("p1 dentro: %d\n", dentro_rect(inf_izq, sup_der, p1));
	printf("p2 dentro: %d\n", dentro_rect(inf_izq, sup_der, p2));
	printf("p3 dentro: %d\n", dentro_rect(inf_izq, sup_der, p3));
	return 0;
}

