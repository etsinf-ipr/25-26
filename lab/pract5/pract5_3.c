/*
Enunciado: escribe un programa en C que defina la estructura struct
vehiculo con los siguientes campos:
- Una cadena de siete caracteres que indiquen la matrícula (cuatro
números y tres letras)
- Un entero que indique la plaza en el párking
- Un real que indique la tarifa aplicada t
Implementar la función main que define una variable del tipo struct
vehiculo y lea sus datos (matricula, plaza asignada y tarifa aplicada). La
matrícula debe leerse como una cadena de 7 caracteres 9999ABC, la
plaza como un entero y la tarifa con un número real (float). Si todos
los datos son válidos, se imprimirán los datos del vehículo, y si no un
mensaje de error.
Los datos son válidos si:
- La matrícula está compuesta por 4 números y 3 letras mayúsculas;
se recomienda usar una función que reciba la matrícula y devuelva
si es válida.
- El parking tiene 3 plantas y 50 plazas por planta. Las plantas se
numeran de 101 a 150, de 201 a 250 y de 301 a 350. Se recomienda
usar también una función.
- La tarifa es mayor que cero
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>

struct vehiculo {
    char matricula[8]; // 7 chars + terminador
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

int main() {
    struct vehiculo v;

    printf("Matrícula (9999ABC): ");
    scanf("%7s", v.matricula);

    printf("Plaza: ");
    scanf("%d", &v.plaza);

    printf("Tarifa (> 0): ");
    scanf("%f", &v.tarifa);

    if (vehiculo_valido(v)) {
        printf("\nVehículo válido:\n");
        printf("  Matrícula: %s\n", v.matricula);
        printf("  Plaza: %d\n", v.plaza);
        printf("  Tarifa: %.2f\n", v.tarifa);
    } else {
        printf("\nError: datos no válidos.\n");
    }

    return 0;
}
