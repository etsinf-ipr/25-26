/*
Enunciado:
Las categorías de los libros del ejercicio 1 según su letra son: ‘C’ clásico, ‘D’ divulgación, ‘E’ ensayo, ‘N’ novela). Crea una función que imprima por pantalla la información de un libro, mostrando el nombre completo de la categoría. Escribe una función main para comprobar su funcionamiento con varios tipos de libro.
*/

#include <stdio.h>

struct libro {
    int isbn;
    float precio;
    char categoria; /* C,D,E,N */
};

void imprimir_libro(struct libro l) {
    printf("ISBN: %d | Precio: %.2f | Categoria: ", l.isbn, l.precio);
    switch (l.categoria) {  
		case 'C': printf("clásico"); break;
		case 'D': printf("divulgación"); break;
		case 'E': printf("ensayo"); break;
		case 'N': printf("novela"); break;
		default: printf("desconocida") ;
	}
    printf("\n");
}

int main(void) {
	struct libro beloved = {97884264, 10.0, 'C'};
	struct libro paradise = {97806794, 15.5, 'D'};
	struct libro love = {97803754, 20.0, 'E'};
	struct libro shosha = {97803742, 8.99, 'N'};
    struct libro submundo = {97803072, 12.50, 'X'};
	imprimir_libro(beloved);
	imprimir_libro(paradise);
	imprimir_libro(love);
	imprimir_libro(shosha);
    imprimir_libro(submundo);
	return 0;
}

