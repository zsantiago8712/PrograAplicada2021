#include <stdio.h>
#include <stdlib.h>

typedef struct tipos
{
    char letra;
    struct tipos *sig;
    struct tipos *ant;
}LISTA;
