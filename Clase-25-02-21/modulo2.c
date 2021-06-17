#include "tipos.h"



void crear_lista(char letra, LISTA **inicio, LISTA **aux)
{
    LISTA *nodo;
    
    nodo = malloc(sizeof(LISTA));
    if(nodo == NULL)
    {
        printf("ERROR\n");
    }

    nodo -> letra = letra;
    if(*inicio == NULL)
    {
        *inicio = nodo;
        *aux = nodo;
        nodo -> sig = *inicio;
        nodo -> ant = *aux;
    }else
    {
        (*aux) -> sig = nodo;
        nodo ->ant = *aux;
        nodo -> sig = *inicio;
        (*inicio) -> ant = nodo;
        *aux = nodo;
    }
}

void recorrer_lista(LISTA *inicio, LISTA *aux ,int opcion)
{
    LISTA *nodo;
    system("clear");
    nodo = inicio;
    if(inicio != NULL)
    {
        if(nodo != NULL)
        {
            do
            {
                
                if(opcion == 1)
                {
                    printf("%c", nodo-> letra);
                    nodo = nodo -> sig;
                }else
                {
                    nodo = nodo -> ant;
                    printf("%c", nodo-> letra);
                }
            } while (nodo != inicio);
            printf("\n");
            
        }
    }
}


void liberar_espacio(LISTA *inicio, LISTA *aux)
{
    LISTA *nodo;
    if(inicio != NULL)
    {
        nodo = inicio;
        aux = inicio;
        do
        {
            aux = nodo -> sig;
            free(nodo);
            nodo = aux;
        } while (nodo != inicio);        
    }
}