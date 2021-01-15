// Programa que hace eco de sus argumentos

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if(argc == 1)
    {
        printf("Error al correr el porgrama. Faltan argumentos\n");
        exit(0);
    }

    printf("Se recibieron %d argumentos\n", argc - 1);
    for(int i = 1; i < argc; i++)
    {
        printf("%s\n", argv[i]);
    }
    printf("\n");    
}