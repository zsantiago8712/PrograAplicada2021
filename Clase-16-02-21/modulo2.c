
#include <local.h>


//Listas tipo PILAS / LISFO


void crear_lista(LISTA **inicio)
{
    //1.- Cear espacio
    LISTA *nodo;
    nodo = malloc(sizeof(LISTA));
    if(nodo == NULL)
    {
        printf("ERROR");
        exit(1);
    }


    //2.- Llenar espacio
    printf("Dame una letra");
    scanf("%c", &nodo ->letra);

    //3.- Encadenar
    if(*inicio == NULL)
    {
        nodo -> sig = NULL;
    }else 
    {
        nodo -> sig = inicio;
    }
    *inicio = nodo;





}