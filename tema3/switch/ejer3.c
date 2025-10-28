/*
 * Ejercicio 3: Escribe un programa en C que implemente una calculadora sencilla. 
 * El usuario escribe una operación (ej: 2+3) y el programa realiza la operación 
 * indicada. Usa switch (NOTA: los operadores +, - *, / son caracteres y se leen 
 * con %c)
 */

#include <stdio.h>

int main() {
    float num1, num2;
    char operador;
    printf("Introduce una operación (ej: 2+3): ");
    scanf("%f%c%f", &num1, &operador, &num2);

    switch (operador) {
        case '+':
            printf("Resultado: %.2f\n", num1 + num2);
            break;
        case '-':
            printf("Resultado: %.2f\n", num1 - num2);
            break;
        case '*':
            printf("Resultado: %.2f\n", num1 * num2);
            break;
        case '/':
            //Extensión: controla la división entre cero
            printf("Resultado: %.2f\n", num1 / num2);
            break;
        default:
            printf("Error: Operador inválido\n");
            break;
    }

    return 0;
}
