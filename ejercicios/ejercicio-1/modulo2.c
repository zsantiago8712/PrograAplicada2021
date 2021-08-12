#include <strings.h>
#include <string.h>
#include "local.h"


void insertar(ARBOL **inserccion, char *line)
{
    ARBOL *avanza, *nuevo;
    avanza = *inserccion;

    nuevo = malloc(sizeof(ARBOL));
    if(nuevo == NULL)
    {
        printf("ERROR");
        exit(1);
    }

    nuevo -> palabra = strdup(line);
    //strcpy(nuevo -> palabra, line);
    nuevo -> izq = NULL;
    nuevo -> der = NULL;


    if(avanza == NULL)
    {
        *inserccion = nuevo;
        return;
    }
    
    while(avanza != NULL)
    {
        if(strcasecmp(strdup(line), avanza -> palabra) > 0) // <= para que los ordene de mayor a menor
        {
            if(avanza -> der != NULL)
            {
                avanza = avanza -> der;
            }else
            {
                avanza -> der = nuevo;
                return;
            }
        }else
        {
            if(avanza -> izq != NULL)
            {
                avanza = avanza -> izq;
            }else
            {
                avanza -> izq = nuevo;
                return;
            }
        }

    }

}



void imprimir(ARBOL *raiz, int *c)
{
    if(raiz != NULL)
    {
        
        // if(strcasecmp("SANCHEZ", raiz -> palabra) == 0)
        // {
        //     *c += 1;
        // }
        imprimir(raiz -> izq, c);
        printf("%s\n", raiz -> palabra);
        imprimir(raiz -> der, c);

    }
}

void liberar_memoria(ARBOL *raiz)
{
    if(raiz != NULL)
    {
        liberar_memoria(raiz -> izq);
        liberar_memoria(raiz -> der);
        free(raiz);


    }
}