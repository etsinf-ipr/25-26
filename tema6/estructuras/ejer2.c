/*
Enunciado:
Completa la estructura del enunciado anterior pidiendo al usuario los datos. Muestra los valores por pantalla.
*/

#include <stdio.h>

struct libro {
	int isbn;
	float precio;
	char categoria; /* C,D,E,N */
};

int main(void) {
	struct libro l;
	printf("ISBN: ");
	scanf("%d", &l.isbn);
	printf("Precio: ");
	scanf("%f", &l.precio);
	printf("Categoria (C/D/E/N): ");
	// queda pendiente procesar el [Enter] de haber leído precio
    // insertar un espacio antesd e %c es una forma sencilla
	scanf(" %c", &l.categoria);

	printf("\n--- Libro ---\n");
	printf("ISBN: %d\nPrecio: %.2f\nCategoria: %c\n", l.isbn, l.precio, l.categoria);
	return 0;
}

