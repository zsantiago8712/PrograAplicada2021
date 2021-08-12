#include <stdlib.h>
#include <stdio.h>
#include <strings.h>
#include<string.h>


typedef struct arbol
{
    char *palabra;
    int ocurrencia;
    struct lista *der;
    struct lista *izq;

}ARBOL;


typedef struct lista
{
    char *palabra;
    int ocurrencia;
    struct lista *sig;

}LISTA;