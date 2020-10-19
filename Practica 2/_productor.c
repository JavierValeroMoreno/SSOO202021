#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <string.h>

#define KEY 100                         //Clave del semaforo
#define MB 0                            //ID semaforo Manipulacion del buffer
#define EL 1                            //ID semaforo Espacio Libre
#define ED 2                            //ID semaforo Elemento Disponible
#define TAMBUFFER 5                     //Tamaño buffer

int main (argc, argv)
    int argc;
    char **argv;{

    //Declaracion de variables

    int i, c;                           //Contador de proposito general
    int numContactos;                   //Numero de contactos a visualizar
    int semid;                          //ID del conjunto de semaforos
    int shmid;                          //ID de la memoria compartida para el buffer
    size_t tambuffinal;                 //Tamaño final del buffer
    char* aux;

    if(argc != 2){
        printf("No se ha introducido ningun parametro de entrada");
        exit(3);                        //Error 3: erro por no introducir parametros.
    }
    numContactos = atoi(argv[1]);
    typedef struct{

        //XXX: ELEMENTOS A ALMACENAR EN LA ESTRUCTURA DE DATOS 
        char apellido_1[25];
        char apellido_2[25];
        char nombre[25];
        char email[25];
        int movil;
        short last;

    } DatosContacto;
    
    DatosContacto contacto, *addr;                  /*
                                        contacto: se utiliza para almacenar los datos de un contacto
                                        addr: puntero a la memoria compartida
                                        */
    
    struct sembuf sem_oper;             //Para las operaciones wait y signal con semaforos

    //XXX: Determinar el numero de contactactos a producir

    tambuffinal = sizeof(DatosContacto)*TAMBUFFER;

    //Acceder al conjunto de semaforos existente

    semid = semget(KEY, 3, 0770);

    if( semid == -1 ){
        printf("\nError en el acceso al conjunto de semaforos\n");
        exit(1);                        //Error 1: error en el acceso al conjunto de semaforos.
    }   

    // OJO: No hay que inicializar los semaforos. Lo ha hecho el proceso de consumidor

    //Acceder a la memoria compartida
    
    shmid = shmget(KEY, tambuffinal, 0770 );
    printf("%d\n", shmid);
    if( shmid == -1 ){
        printf("\nError en la creacion de la Memoria compartida\n");
        exit(2);                        //Error 2: error al crear la Memoria compartida
    }

    //Enlazar la memoria compartida al proceso

    addr = shmat(shmid, 0, 0);

    //Repetimos para cada contacto

    for ( i = 0; i < numContactos; i++)
    {
        //XXX: Producir elemento

        //Introducir Nombre
        
        printf("Nombre\n");
        scanf("%s", contacto.nombre);
        
        //Introducir Apellido 1
        
        printf("Apellido 1\n");
        scanf("%s", contacto.apellido_1);

        //Introducir Apellido 2
        printf("Apellido 2\n");
        scanf("%s", contacto.apellido_2);

        //Introducir Email
        printf("Email\n");
        scanf("%s", contacto.email);

        //Introducir Telefono
        printf("Telefono\n");
        scanf("%d", &contacto.movil);

        while (getchar() != '\n'); 

        contacto.last = (i == numContactos -1)? 1:0;

        //Wait (Espacio libre)

        sem_oper.sem_num = EL;          //Seleccionamos semaforo Espacio Libre
        sem_oper.sem_op = -1;           //Realizamos un Wait
        sem_oper.sem_flg = SEM_UNDO;    //Asi evitamos interbloqueos

        semop(semid, &sem_oper, 1);

        //Wait (Manipulacion del buffer)

        sem_oper.sem_num = MB;          //Seleccionamos semaforo Manipulacion de Buffer
        sem_oper.sem_op = -1;           //Realizamos un Wait
        sem_oper.sem_flg = SEM_UNDO;    //Asi evitamos interbloqueos

        semop(semid, &sem_oper, 1);

        //XXX: Seccion critica. Acceder al buffer que sera el recurso no compartido.

        addr[i%TAMBUFFER] = contacto;

        //Signal (Manipulacion del buffer)

        sem_oper.sem_num = MB;          //Seleccionamos semaforo Manipulacion de Buffer
        sem_oper.sem_op = 1;            //Realizamos un Signal

        semop(semid, &sem_oper, 1);

        //Signal (Elemento Disponible)

        sem_oper.sem_num = ED;          //Seleccionamos semaforo Elemento disponible
        sem_oper.sem_op = 1;            //Realizamos un Signal

        semop(semid, &sem_oper, 1);

    }

    //Separamos la memoria del proceso.
    shmdt(addr);
    for (i = 0; i < 5; i++)
    {
        free(addr[i].nombre);
        free(addr[i].apellido_1);
        free(addr[i].apellido_2);
        free(addr[i].email);
    }
    free(addr);
    free(contacto.nombre);
    free(contacto.apellido_1);
    free(contacto.apellido_2);
    free(contacto.email);


    return 0;
}