#include <stdio.h>
#include <stdlib.h>

#include "local.h"

extern void add_impresion_work(LISTA **inicio, LISTA **aux);
extern void ordenar_por_num_hojas(LISTA *inicio);
extern void imprimir(LISTA *inicio);
extern void imprimir_lista(LISTA *inicio);

int main(void)
{
    LISTA *inicio, *aux;
    int opcion = 0;

    inicio = NULL;

    while (1)
    {
        system("clear");
        printf("\nEscoja un opcion\n");
        printf("--------------------------------------------\n");
        printf("1. Agregar un trabajo de impresion\n");
        printf("2. Ordenar trabajo por numero de paginas\n");
        printf("3. Imprimir trabajo\n");
        printf("4. Ver cola\n");
        printf("5. Salir\n");
        printf("Opcion elegida: ");
        scanf("%d", &opcion);

        if(opcion == 1)
        {
            add_impresion_work(&inicio, &aux);
        }else if(opcion == 2)
        {
            ordenar_por_num_hojas(inicio);
        }else if(opcion == 3)
        {
            imprimir(inicio);
        }else if(opcion == 4)
        {
            imprimir_lista(inicio);
        }else if(opcion == 5)
        {
            printf("Gracias por venir\n");
            exit(0);
        }

    }
    
}