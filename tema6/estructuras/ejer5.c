/*
Enunciado:
Un radar de tramo registra para cada coche la distancia del tramo y el tiempo. Define una estructura vehículo que guarde estos dos datos y una función velocidad que tiene como parámetro la estructura y calcula la velocidad media en el tramo.
Escribe un main para probar su funcionamiento.
*/

#include <stdio.h>

struct vehiculo {
    float distancia; /* km */
    float tiempo;    /* horas */
};

float velocidad(struct vehiculo v) {
    // control de errores: impedir división por cero (error)
    // si es negativo, no tiene sentido, pero puede hacer la operación
    if (v.tiempo == 0.0) return 0.0;
    return v.distancia / v.tiempo; }

int main(void) {
    struct vehiculo v = { 20.0, 0.25 }; // 20km en 15 min
	printf("Velocidad media: %.2f km/h\n", velocidad(v));
	return 0;
}

