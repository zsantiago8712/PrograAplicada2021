#include <stdlib.h>
#include <stdio.h>

#include "local.h"


extern void crear_lista(char c, LISTA **inicio);
extern void recorrer_lista(LISTA *inicio, char *file_name);
extern void liberar_memoria(LISTA *inicio);


int main(int argc, char *argv[])
{
    LISTA *inicio;
    FILE *fp;
    char c;
    

    inicio = NULL;

    if(argc != 3)
    {
        printf("ERROR DE ARGUMENTOS\n");
        exit(1);
    }

    
    fp = fopen(argv[1], "r");
    if(fp == NULL)
    {
        printf("ERROR: no existe el archvio %s\n", argv[1]);
        exit(1);
    }
    
    while(fscanf(fp, "%c", &c) == 1)
    {
        crear_lista(c, &inicio);
    }
    recorrer_lista(inicio, argv[2]);
    liberar_memoria(inicio);

    fclose(fp);
    
}