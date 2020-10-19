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

int main(){

    //Declaracion de variables

    int i = 0;                          //Contador de proposito general
    int semid;                          //ID del conjunto de semaforos
    int shmid;                          //ID de la memoria compartida
    size_t tambuffinal;                 //Tamaño final del buffer

    typedef struct{

        //XXX: ELEMENTOS A ALMACENAR EN LA ESTRUCTURA DE DATOS 
        char apellido_1[25];
        char apellido_2[25];
        char nombre[25];
        char email[25];
        int movil;
        short last;
    }  DatosContacto;
    DatosContacto contacto, *addr;                  /*
                                        contacto: se utiliza para almacenar los datos de un contacto
                                        addr: puntero a la memoria compartida
                                        */
    
    struct sembuf sem_oper;             //Para las operaciones wait y signal con semaforos

    union semun{
        
        int val;
        struct semid_ds *semstat;
        unsigned short *array;
    } arg;

    //Creamos un conjunto de 3 semaforos

    semid = semget(KEY, 3, 0770 | IPC_CREAT);

    if( semid == -1 ){
        printf("\nError en la creaccion de los semaforos\n");
        exit(1);                        //Error 1: error en la creacion de semaforos
    }

    //Inicializamos los semaforos
    printf("Creamos semaforos\n");
    arg.array = (unsigned short*) malloc( sizeof(short)*3 );
    arg.array[MB] = 1;
    arg.array[EL] = TAMBUFFER;
    arg.array[ED] = 0;

    semctl( semid, 3, SETALL, arg);

    //Crear la memoria compartida
    //XXX: Tamaño total del buffer

    tambuffinal = sizeof(DatosContacto)*TAMBUFFER;
    printf("%d\n", tambuffinal);
    printf("Creamos memoria\n");
    shmid = shmget( KEY, tambuffinal, 0770 | IPC_CREAT);

    if( shmid == -1 ){
        printf("\nError en la creacion de la memoria compartida\n");
        exit(2);                        //Error 2: error al crear memoria compartida
    }

    //Enlazar la memoria compartida al proceso.

    addr = shmat(shmid, 0, 0);

    //Repetimos hasta que no queden contactos
    while(1){

        //Wait (Elemento disponible)
        sem_oper.sem_num = ED;          //Seleccionamos semaforo Elemento Disponible
        sem_oper.sem_op = -1;           //Realizamos wait
        sem_oper.sem_flg = SEM_UNDO;    //Para evitar interbloqueos

        printf("Wait semaforos ED\n");
        semop(semid, &sem_oper, 1);

        //Wait (Manipulacion Buffer)
        sem_oper.sem_num = MB;          //Seleccionamos semaforo Manipulacion de buffer
        sem_oper.sem_op = -1;           //Realizamos wait
        sem_oper.sem_flg = SEM_UNDO;

        printf("Wait semaforos MBr\n");
        semop(semid, &sem_oper, 1);

        //TODO: Seccion critica acceder al buffer recurso no compartible.
        
        contacto = addr[i%TAMBUFFER];

        //Signal (Manipulacion del buffer)
        sem_oper.sem_num = MB;
        sem_oper.sem_op = 1;

        semop(semid, &sem_oper, 1);

        //Signal (Elemento Libre);
        sem_oper.sem_num = EL;
        sem_oper.sem_op = 1;

        semop(semid, &sem_oper, 1);

        i++;
        //TODO: Consumir elemento

        printf("\n########## Elemento numero %d ##########\n", i);
        printf("Nombre : %s\nApellidos : %s %s\nEmail : %s\nTelefono : %d\n", contacto.nombre, contacto.apellido_1, contacto.apellido_2, contacto.email, contacto.movil);
    
        if(contacto.last == 1)
            break;
    }

    // Eliminamos conjunto de semaforos
    semctl(semid, 3, IPC_RMID, 0);

    // Separamos la memoria compartida del proceso
    shmdt(addr);

    //Eliminamos la memoria compartida
    shmctl(shmid, IPC_RMID, 0);

    //Liberamos memoria dinamica.
    free(arg.array);

    return 0;
}