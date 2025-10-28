/*
 * Ejercicio 3: Números primos
 * 
 * Solicita al usuario un número `N`. Indica si el número es primo.
 * Versión sin usar break
 */

#include <stdio.h>

int main() {
    int num, es_primo = 1;
    printf("Introduce un número entero positivo: ");
    scanf("%d", &num);
    // recorremos los números desde 3 hasta la mitad de num
    // 0, 1 y 2 son primos
    // si num=7 (por ejemplo), no hace falta llegar a 6
    // cualquier número > 4 no es divisor de 7 
    // 7 / 4 = 1,x, así que el único divisor posible que queda es 1
    for(int i = 3; i <= num / 2 && es_primo; i++) {     
        if(num % i == 0) 
            // al cambiar es_primo a 0, la condición del for fallará y saldremos del bucle
            es_primo = 0;
    }
    // debemos comprobar por cuál de las dos condiciones hemos salido del bucle
    // es_primo == 0 (hemos encontrado un divisor)
    // i > num / 2   (hemos comprobado todos los posibles divisores
    if(es_primo) {
        printf("El número %d es primo.\n", num);
    } else {
        printf("El número %d NO es primo.\n", num);
    }
    
    return 0;
}
