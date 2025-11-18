/*
Enunciado: escribe un programa en C con la definición de la estructura
struct vehiculo que lea los datos de dos vehículos en el aparcamiento. Si
todos los datos son válidos, comprobar que los vehículos son distintos,
es decir, que sus matrículas no coinciden, e imprimir un mensaje en
pantalla que lo indique. Se recomienda implementar una función iguales
que reciba dos struct vehiculo y devuelva 1 si son el mismo vehículo y
0 en caso contrario. Revisa las funciones disponibles en string.h para la
comparación de cadenas.
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>

struct vehiculo {
    char matricula[8];
    int plaza;
    float tarifa;
};

int matricula_valida(const char *matricula) {
    // longitud correcta
    if (strlen(matricula) != 7)
        return 0;
    // primeros 4 caracteres son dígitos
    for (int i = 0; i < 4; i++) {
        if (!isdigit(matricula[i]))
            return 0;
    }
    // últimos 3 caracteres son letras mayúsculas
    for (int i = 4; i < 7; i++) {
        if (!isupper(matricula[i]) || !isalpha((unsigned char)matricula[i]))
            return 0;
    }
    return 1;
}

int plaza_valida(int p) {
    // método general
    int planta = p / 100;
    int numero = p % 100;
    if (planta < 1 || planta > 3)
        return 0;
    if (numero < 1 || numero > 50)
        return 0;
    return 1;
    // alternativa con comprobación directa
    return (p >= 101 && p <= 150) || (p >= 201 && p <= 250) || (p >= 301 && p <= 350);
}

int tarifa_valida(float t) {
    return t > 0.0f;
}

int vehiculo_valido(struct vehiculo v) {
    return matricula_valida(v.matricula) && plaza_valida(v.plaza) && tarifa_valida(v.tarifa);
}

int iguales(struct vehiculo a, struct vehiculo b) {
    return strcmp(a.matricula, b.matricula) == 0;
}

int main() {
    struct vehiculo v1, v2;

    printf("Datos del vehículo 1\n");
    printf("Matrícula (9999ABC): ");
    scanf("%7s", v1.matricula);
    printf("Plaza: ");
    scanf("%d", &v1.plaza);
    printf("Tarifa: ");
    scanf("%f", &v1.tarifa);

    printf("\nDatos del vehículo 2\n");
    printf("Matrícula (9999ABC): ");
    scanf("%7s", v2.matricula);
    printf("Plaza: ");
    scanf("%d", &v2.plaza);
    printf("Tarifa: ");
    scanf("%f", &v2.tarifa);

    if (!vehiculo_valido(v1) || !vehiculo_valido(v2)) {
        printf("\nError: algún vehículo tiene datos no válidos.\n");
        return 0;
    }

    if (iguales(v1, v2)) {
        printf("\nLos vehículos son el mismo (matrícula idéntica).\n");
    } else {
        printf("\nLos vehículos son distintos (matrículas diferentes).\n");
    }

    return 0;
}
