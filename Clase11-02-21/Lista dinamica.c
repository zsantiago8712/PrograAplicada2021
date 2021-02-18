#include <stdio.h>
#include <stdlib.h>



int main(void)
{
    typedef struct datos
    {
        char nombre[25];
        int edad;
        struct datos *sig;
        
    }DATOS;

    /*Tipo de Listas

        FIFO --> Cola, primero que entras primero que sale
        LIFO --> Primero que entra ultimo que sale
            Sencillas
            Dobles
        Circulares ----> Cunado estas en la ultimo pasas a la primera 
            Sencillas
            Dobles

    */

    DATOS *inicio, *aux, *nodo;

    /*Pasos para crear lista dinámica

        !) Crear el esapcio
        2) Llenar la información
        3) Encadenar
    */

    inicio = NULL;

    
    //Paso 1) Pedir el espacio 

    nodo = malloc(sizeof(DATOS)); // ------> Pedir a c que cree espacio para la lista

    if(nodo == NULL)
    {
        printf("Nodo no hay memoria\n");
        exit(0);
    }

    //Paso 2) Llenar informacion

    printf("Dame el nombre: ");
    scanf("%s", &nodo ->nombre);
    printf("Dame la edad: ");
    scanf("%d", &nodo ->edad);

    //Paso 3) Encadenar
    if(inicio == NULL)
    {
        inicio = nodo;
    }else
    {
        aux ->sig = nodo;
    }
    aux = nodo;     //aux es un apuntador que apunta al ultimo nodo creado
    nodo ->sig = NULL; //sig es un pauntador dentro de la estructura que apunta a la mismo tipo de estructura osea apunta al siguinete elemento



    //Recorrido de la lista
    nodo = inicio;
    while(nodo != NULL)
    {
        printf("%s\n", nodo->nombre);
        printf("%s\n", nodo->edad);
        nodo = nodo ->sig;
    }

    //free();





}