#include "local.h"


void ordenar_por_num_hojas(LISTA *incio)
{
    LISTA *nodo, *nodo2;

    char *temp;
    int num_temp;

    nodo = incio;
    nodo2 = nodo -> sig;

    do
    {

        while (nodo2 != NULL)
        {
            if(nodo -> numero_hojas > nodo2->numero_hojas)
            {
                temp = nodo -> nombre_archivo;
                num_temp = nodo -> numero_hojas;

                nodo -> nombre_archivo = nodo2 -> nombre_archivo;
                nodo -> numero_hojas = nodo2 -> numero_hojas;

                nodo2 -> numero_hojas = num_temp;
                nodo2 -> nombre_archivo = temp; 
            }
            nodo2 = nodo2 -> sig;
        }

        nodo = nodo -> sig;
        if(nodo != NULL)
        {
            nodo2 = nodo -> sig;
        }
        
    }while(nodo != NULL);
    
}


void imprimir(LISTA *inicio)
{
    LISTA *nodo;
    if(inicio != NULL)
    {
        nodo = inicio;
        inicio = nodo -> sig;
        free(nodo);
    }
}


void imprimir_lista(LISTA *inicio)
{
    system("clear");
    LISTA *nodo; 
    nodo = inicio; //Tambien se puede nolo = aux
    printf("Nombre del Archivo      Hojas\n");
    printf("________________________________\n");
    while(nodo != NULL)
    {
        printf("%s                     %d\n", nodo->nombre_archivo, nodo -> numero_hojas);
        nodo = nodo ->sig; //nodo = nodo ->ant;
    }
    fflush(stdin);
    while(getchar()!='\n');
    getchar();
}