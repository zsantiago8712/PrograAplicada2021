/*******************************************************
 *
 * Tarea-1  -  Ejercico-1
 * Programación Aplicada
 * Santiago Zamora
 * Primavera 2021
 * 
 *******************************************************/


#include <stdio.h>
#include <stdlib.h>


extern void read_and_write(char *file_to_read);

int main(int argc, char *argv[])
{
    //Verifica que se hayan puesto los sucientes argumentos
    if(argc < 2 || argc > 2)
    {
        printf("Error de argumentos\n");
        exit(0);
    }

    read_and_write(argv[1]); 
    
}