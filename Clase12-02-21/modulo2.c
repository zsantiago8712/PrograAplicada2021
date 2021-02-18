#include <stdio.h>
#include <stdlib.h>
#include "local.h"


void crearLista(char c, LISTA **aux, LISTA **inicio) 
{
    //Lista tipo COLA


    //1.- Crear el espacio
    LISTA *nodo;
    nodo = malloc(sizeof(char));
    if(nodo == NULL)
    {
        printf("No hay memoria\n");
        exit(1);
    }


    //2.- Llenar lista
    nodo->letra = c;


    //3.- Encadenar
    if(*inicio == NULL)
    {
        *inicio = nodo;
    }else
    {
        (*aux) ->sig = nodo; //--> Doble apuntador a un elemento de una estructura
    }
    *aux = nodo;
    nodo ->sig = NULL;


}//CrearLista


void recorrerLista(LISTA *inicio)
{
    LISTA *nodo;
    nodo = inicio;
    while (nodo != NULL)
    {
        printf("%c\n", nodo ->letra);
        nodo = nodo ->sig;
    }
  
}


void liberarMemoria(LISTA *inicio)
{
    LISTA *nodo;
    nodo = inicio;

    while (nodo != NULL)
    {
        inicio = nodo ->sig;
        free(nodo);
        nodo = inicio;
    }
    
}