#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct datos
{
    char nombre_cancion[30];
    char interprete[30];
    char album[30];
    int year;
    struct datos *sig;
}LISTA;


