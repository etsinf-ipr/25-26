/*
Enunciado:
Completa la estructura del enunciado 1 a través de datos que recibe por línea de comandos. Muestra la información final por pantalla. Ejemplo:
./libro 2313 12.5 N
Ten en cuenta que “N” es una cadena de caracteres. Piensa cómo extraer solo la primera letra (que es la única que hay).
*/

#include <stdio.h>
#include <stdlib.h>

struct libro {
	int isbn;
	float precio;
	char categoria; /* C,D,E,N */
};

int main(int argc, char *argv[]) {
	if (argc != 4) {
		fprintf(stderr, "Uso: %s <isbn> <precio> <categoria>\n", argv[0]);
		return 1;
	}
	struct libro l;
	l.isbn = atoi(argv[1]);
	l.precio = (float)atof(argv[2]);
    // argv[3] es una cadena, así que con [0] accedemos a su primer carácter
	l.categoria = argv[3][0];
	printf("ISBN: %d\nPrecio: %.2f\nCategoria: %c\n", l.isbn, l.precio, l.categoria);
	return 0;
}

