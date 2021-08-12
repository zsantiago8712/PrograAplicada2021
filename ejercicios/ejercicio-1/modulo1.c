#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "local.h"


extern void insertar(ARBOL **inserccion, char *line);
extern void imprimir(ARBOL *raiz, int *c);
extern void liberar_memoria(ARBOL *raiz);

int main(int argc, char *argv[])
{
    FILE *fp;
    ARBOL *raiz;
    char letra;
    int i = 0;
    int c = 0;
    int *a = &c;

    char palabra[200];

    raiz = NULL;
    if(argc != 2)
    {
        printf("error\n");
        exit(1);
    }

    fp = fopen(argv[1], "r");
    if(fp == NULL)
    {
        printf("error\n");
        exit(1);
    }

    while (fscanf(fp, "%c", &letra) != EOF)
    {
        if(letra == 32 || letra == 9 || letra == 10)
        {
            palabra[i] = '\0';
            insertar(&raiz, palabra);
            strcpy(palabra, "");
            i = 0;
        }else
        {
            palabra[i] = letra;
            i++;
        }
    }

    fclose(fp);
    imprimir(raiz, &c);
    liberar_memoria(raiz);

    //printf("\n\nSANCHEZ --> %d\n", c); 

    
}
