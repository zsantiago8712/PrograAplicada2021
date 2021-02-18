#include <stdlib.h>
#include <stdio.h>

#include "local.h"


extern void crearLista(char c, LISTA **aux, LISTA **inicio);
extern void recorrerLista(LISTA *inicio);
extern void liberarMemoria(LISTA *inicio);


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
        crearLista(c, &aux, &inicio);
    }
    recorrerLista(inicio);
    liberarMemoria(inicio);

}