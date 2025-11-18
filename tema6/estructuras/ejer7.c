/*
Enunciado:
Crea una estructura para almacenar las coordenadas de un punto (latitud y longitud) y una función que devuelva si las coordenadas están en el hemisferio norte (1) o sur (2). La función devolverá 0 si el punto se encuentra exactamente sobre el Ecuador.
*/

#include <stdio.h>

#define ECUADOR 0
#define NORTE 1
#define SUR 2

// alternativa: usar enum
//enum hemisferio { ECUADOR, NORTE, SUR };
struct coord {
    double latitud;  // grados, positivo norte, negativo sur 
    double longitud; // grados, positivo este, negativo oeste 
};

int hemisferio(struct coord p) {
    if (p.latitud > 0) return NORTE;
    if (p.latitud < 0) return SUR;
    return ECUADOR;
}

int main(void) {
    struct coord valencia = { 39.47, -0.38 };  
    struct coord buenos_aires = { -34.60, -58.38 }; 
    struct coord ecuador = { 0.0, 10.0 };     
	printf("Valencia. Hemisferio: %d\n", hemisferio(valencia));
	printf("Buenos Aires. Hemisferio: %d\n", hemisferio(buenos_aires));
	printf("Ecuador. Hemisferio: %d\n", hemisferio(ecuador));
	return 0;
}

