#include "local.h"


void crear_lista(LISTA **inicio, LISTA **aux)
{
    LISTA *nodo;
    nodo = malloc(sizeof(LISTA));
    if(nodo == NULL)
    {
        printf("ERROR");
        exit(1);
    }

    printf("Dame una letra");
    scanf("%c", &nodo -> letra);

    if(*inicio == NULL)
    {
        *inicio = nodo;
        nodo -> ant = NULL;
    }
    else
    {
        (*aux) -> sig = nodo;
        nodo -> ant = *aux;
    }

    *aux = nodo;
    nodo -> sig = NULL;

}

//El codigo sirve para ir de inicio a fin, los comentarios es para ir de fin a inicio
void recorrer_lista(LISTA *inicio)
{
    LISTA *nodo; 
    nodo = inicio; //Tambien se puede nolo = aux
    while(nodo != NULL)
    {
        printf("%s\n", &nodo->letra);
        nodo = nodo ->sig; //nodo = nodo ->ant;
    }
}


void liberar_memoria(LISTA *inicio)
{
    LISTA *nodo;

    nodo = inicio;
    while(nodo != NULL)
    {
        inicio = nodo -> sig;
        free(nodo);
        nodo = inicio;
    }
    
}