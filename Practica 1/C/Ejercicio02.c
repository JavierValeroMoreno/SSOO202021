#include <stdio.h>
#include <stdlib.h>


int main(int argc, char const *argv[])
{
    ssize_t bytes_leidos;

    int t = 20;
    
    int value;
    char* str_01 = NULL;
    char* str_02; = NULL;

    for (size_t i = 0; i < 3; i++)
    {
        /* code */
        printf("Introduce un entero: ");
        scanf("%d", &value);
        printf("El valor introducido es: %d", value);
    
    }

    bytes_leidos = getline(&str_01, &t, stdin);
    
    if(bytes_leidos == -1)
        printf("ERROR.\n");

    bytes_leidos = getline(&str_02, &t, stdin);

    if (bytes_leidos == -1)
        printf("ERROR.\n");
    
    printf("%s",(value%2 == 0)? str_01:str_02);
    
    return 0;
}
