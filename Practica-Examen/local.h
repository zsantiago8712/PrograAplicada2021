#include <stdio.h>
#include <stdlib.h>


typedef struct datos
{
    int numero_hojas;
    char *nombre_archivo;
    struct datos *sig;

}LISTA;
