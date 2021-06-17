#include "local.h"


void insertar(ARBOL **inserccion, int num)
{
    ARBOL *avanza, *nuevo;
    avanza = *inserccion;

    nuevo = malloc(sizeof(ARBOL));
    if(nuevo == NULL)
    {
        printf("ERROR");
        exit(1);
    }

    nuevo -> num = num;
    nuevo -> izq = NULL;
    nuevo -> der = NULL;


    if(avanza == NULL)
    {
        *inserccion = nuevo;
        return;
    }

    while(avanza != NULL)
    {
        if(num >= avanza -> num)
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


// long fibo(int num)
// {
//     if(num == 0 || num == -1)
//     {
//         return 1;
//     }else
//     {
//         return fibo(num - 1) + fibo(num - 2);
//     }
// }

void imprimir(ARBOL *raiz)
{
    if(raiz != NULL)
    {
        imprimir(raiz -> izq);
        printf("%d\n", raiz -> num);
        imprimir(raiz -> der);
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