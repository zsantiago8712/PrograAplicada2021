#include <stdio.h>
#include <stdlib.h>

typedef struct lista
{
    int num;
    struct lista *der;
    struct lista *izq;

}ARBOL;