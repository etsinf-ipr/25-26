/*
Enunciado:
Define una estructura libro con los campos isbn (un entero que sirve como identificador), precio y un carácter para la categoria (‘C’ clásico, ‘D’ divulgación, ‘E’ ensayo, ‘N’ novela). Declara una variable de tipo Libro en main e inicialízala usando constantes (sin scanf). Muestra los valores por pantalla.
*/

#include <stdio.h>

struct libro {
	int isbn;
	float precio;
	char categoria; /* C,D,E,N */
};

int main(void) {
	struct libro l = { 2313, 12.5, 'N' };
	printf("ISBN: %d\n", l.isbn);
	printf("Precio: %.2f\n", l.precio);
	printf("Categoria: %c\n", l.categoria);
	return 0;
}

