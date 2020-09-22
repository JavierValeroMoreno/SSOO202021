#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    /* code */
    double a, b, result;
    char op;
    int c;

    printf("Introduzca el primer valor (A): ");
    scanf("%lf", &a);
    printf("Introduzca el segundo valor (B): ");
    scanf("%lf", &b);
    while((c = getchar())!= '\n');
    printf("Seleccione una operacion (+, -, *, /): ");
    scanf("%c", &op);

    switch (op)
    {
    case '+':
        /* code */
        result = a + b;
        break;
    case '-':
        /* code */
        result = a - b;
        break;
    case '*':
        /* code */
        result = a * b;
        break;
    case '/':
        /* code */
        result = a / b;
        break;
    default:
        printf("No se ha introducido una entrada valida\n");
        return -1;
    }

    printf("El resultado de la operacion %f %c %f = %f\n", a, op, b, result);
    return 0;
}
