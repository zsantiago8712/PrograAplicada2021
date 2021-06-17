#include <stdio.h>
#include <stdlib.h>




typedef struct datos
{
    char letra;
    struct datos *sig;
    struct datos *ant;
}LISTA;