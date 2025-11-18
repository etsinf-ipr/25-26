/*
Enunciado:
Define una estructura persona que guarde su edad, altura y nombre completo.
Implementa una función llamada mostrar_persona que imprima los datos recibidos.
En main, crea una persona por el método que prefieras y llama a la función para mostrar su contenido.
*/

#include <stdio.h>

struct persona {
	int edad;
	float altura; /* metros */
	char nombre[50]; /* nombre completo */
};

void mostrar_persona(struct persona p) {
	printf("Edad: %d\nAltura: %.2f\nNombre: %s\n", p.edad, p.altura, p.nombre);
}

int main(void) {
    struct persona p = { 25, 1.78, "Ana" };
	mostrar_persona(p);
	return 0;
}

