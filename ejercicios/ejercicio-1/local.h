#include <stdlib.h>
#include <stdio.h>
#include <strings.h>


typedef struct lista
{
    char *palabra;
    struct lista *der;
    struct lista *izq;

}ARBOL;