#include "local.h"

extern void create_list(LISTA **inicio, LISTA **aux, char *palabra);
extern int buscar_ocurrencia(LISTA *inicio, char *palabra);
extern void recorrer_list(LISTA *inicio, ARBOL **insercion);
extern void imprimir(ARBOL *raiz);
extern void guardaReporte(ARBOL *raiz);
extern void buscarPalabra(ARBOL *raiz, char *palabra);




int main(int argc, char *argv[])
{

    ARBOL *raiz;
    LISTA *inicio, *aux;
    FILE *fp;
    char palabra[128];
    int cont = 0;
    char user_palabra[100];


    inicio = NULL;
    raiz = NULL;

    
    if(argc != 2)
    {
        printf("ERROR: de argumentos\n");
        exit(1);
    }


    fp = fopen(argv[1], "r");
    if (fp == NULL)
    {
        printf("ERROR: No existe el archivo %s\n", argv[1]);
        exit(1);
    }


    while(fscanf(fp, "%s", palabra) == 1)
    {
        if(buscar_ocurrencia(inicio, palabra) == 0)
        {
            create_list(&inicio, &aux, palabra);
        }

    }

    recorrer_list(inicio, &raiz);
    guardaReporte(raiz);
    printf("RELEVANCIA          PALABRA\n\n");
    imprimir(raiz);

    printf("\n\nIngrese la palabra a buscar:\n");
    scanf("%s",user_palabra);
    buscarPalabra(raiz, user_palabra);
    printf("\n");




}