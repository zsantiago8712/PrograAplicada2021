#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct datos
{
    char letra;
    struct datos *sig;
}LISTA;
