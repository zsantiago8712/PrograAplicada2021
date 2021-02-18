#include "local.h"

//Funcion para crear una lista dinamica PILA/LIFO
void crear_lista(char c, LISTA **inicio)
{
    LISTA *nodo;

    nodo = malloc(sizeof(LISTA));
    if(nodo == NULL)
    {
        printf("ERROR: No hay espacio en la memoria\n");
        exit(0);
    }

    
    nodo -> letra = c;
    if(*inicio == NULL)
    {
        nodo -> sig = NULL;
    }else
    {
        nodo -> sig = *inicio;
    }
    *inicio = nodo;

}

//Funcion para recorrer la lista dinamica (PILA/LIFO) y escibri en el archivo
void recorrer_lista(LISTA *inicio, char *file_name)
{
    LISTA *nodo;
    FILE *fp;

    fp = fopen(file_name, "w");
    nodo = inicio;

    while(nodo != NULL)
    {
        putc(nodo -> letra, fp);
        nodo = nodo -> sig;      
    }
    fclose(fp);

    
}

//Funcion para liberar la memoria de la lista dinamica
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