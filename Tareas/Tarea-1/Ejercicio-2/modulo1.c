/*******************************************************
 *
 * Tarea-1  -  Ejercico-2
 * Programación Aplicada
 * Santiago Zamora
 * Primavera 2021
 * 
 *******************************************************/


#include <stdio.h>
#include <stdlib.h>

//Funcion externa para leer y imprimir los paquetes
extern void read_and_print(char *file_to_read);

int main(int argc, char *argv[])
{
    //Verifica que se hayan puesto los sucientes argumentos
    if(argc < 2 || argc > 2)
    {
        printf("Error de argumentos\n");
        exit(0);
    }

    read_and_print(argv[1]); 
    
}