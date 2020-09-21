#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    /* code */
    double a, b, result;
    char op;

    printf("Introduzca el primer valor (A): ");
    scanf("%lf", &a);
    printf("Introduzca el segundo valor (B): ");
    scanf("%lf", &b);

    printf("Seleccione una operacion (+, -, *, /): ");
    scanf("%c", &op);

    switch (op)
    {
    case op == '+':
        /* code */
        result = a + b;
        break;
    case op == '-':
        /* code */
        result = a - b;
        break;
    case op == '*':
        /* code */
        result = a * b;
        break;
    case op == '/':
        /* code */
        result = a / b;
        break;
    default:
        printf("No se ha introducido una entrada valida");
        return -1;
    }

    printf("El resultado de la operacion %f %c %f = %f", a, op, b, result);
    return 0;
}
