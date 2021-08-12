#include "tipos.h"


extern void crear_lista(char letra, LISTA **inicio, LISTA **aux);
extern void recorrer_lista(LISTA *inicio, LISTA *aux ,int opcion);
extern void liberar_espacio(LISTA *inicio, LISTA *aux);

int main(int argc, char *argv[])
{
    LISTA *inicio, *aux;
    FILE *fp;
    char letra;
    int opcion;

    inicio = NULL;
    
    if(argc != 2)
    {
        printf("ERROR");
        exit(1);
    }

    fp = fopen(argv[1], "r");

    if(fp == NULL)
    {
        printf("ERROR\n");
        exit(1);
    }

    while(fscanf(fp, "%c", &letra) == 1)
    {
        crear_lista(letra, &inicio, &aux);
    }
    printf("Como quieres recorrer la lista (1 - normal, 2 -inverso)\n");
    scanf("%d", &opcion);
    recorrer_lista(inicio, aux, opcion);
    liberar_espacio(inicio, aux);
    
}


