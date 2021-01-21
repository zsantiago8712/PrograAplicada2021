// Programa de ejemplo para el suo de git
// Santiago Zamora
// Programacion
// Primavera 2021


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern int suma(int a, int b);
extern int resta(int a, int b);




int main(int argc, char *argv[])
{
    
    if(argc != 4)
    {
        printf("1ERROR DE ARGUMENTOS");
        exit(1);
    }

    if(strcmp(argv[2], "+") == 0)
    {

        printf("RE = %d\n", suma(atoi(argv[1]), atoi(argv[3]))); // Tambien  se puede con sscanf(argv[1], "%d", &->variable);
        exit(0);

    }else if(strcmp(argv[2], "-") == 0)
    {
        printf("re = %d\n", resta(atoi(argv[1]), atoi(argv[3])));
        exit(0);
    }


    printf("ERROR DE ARGUMENTOS\n");
    exit(1);

}