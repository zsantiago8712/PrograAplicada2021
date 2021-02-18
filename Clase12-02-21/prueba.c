#include <stdlib.h>
#include <stdio.h>






typedef struct datos
{
    char letra;
    struct datos *sig;
}LISTA;

 void crearLista(char c, LISTA *aux, LISTA *inicio);
 void recorrerLista(LISTA *aux, LISTA *inicio);
 void liberarMemoria(LISTA *aux, LISTA *inicio);





int main(int argc, char *argv[])
{

    FILE *fp;
    char c;

    LISTA *inicio, *aux;

    inicio = NULL;

    if(argc != 2)
    {
        printf("ERROR");
        exit(0);
    }


    fp = fopen(argv[1], "r");
    if(fp == NULL)
    {
        printf("ERROR");
        exit(0);
    }

    while((c= getc(fp)) !=  EOF)
    {
        crearLista(c, aux, inicio);
    }
    recorrerLista(aux, inicio);
    liberarMemoria(aux, inicio);

}



LISTA * crearLista(char c, LISTA *aux, LISTA *inicio)
{
    LISTA *nodo;
    nodo = malloc(sizeof(char));
    if(nodo == NULL)
    {
        printf("No hay memoria\n");
        exit(1);
    }


    nodo->letra = c;
    if(inicio == NULL)
    {
        inicio = nodo;
    }else
    {
        aux ->sig = nodo;
    }
    aux = nodo;
    nodo ->sig = NULL;
    
    return 
}


void recorrerLista(LISTA *aux, LISTA *inicio)
{
    LISTA *nodo;
    nodo = inicio;
    while (nodo != NULL)
    {
        printf("sss");
        printf("%c\n", nodo ->letra);
        nodo = nodo ->sig;
    }
    printf("aaa\n");
  
}


void liberarMemoria(LISTA *aux, LISTA *inicio)
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