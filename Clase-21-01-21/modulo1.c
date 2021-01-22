// Programa de ejemplo para el suo de git
// Santiago Zamora
// Programacion
// Primavera 2021


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


extern int suma(int a, int b);
extern int resta(int a, int b);
extern int multiplicacion(int a, int b);
extern int validacion(char a[20], char b[20]);
extern int potencia(int base, int power);
extern int division(int a, int b);


int main(int argc, char *argv[])
{
    
    if(argc != 4)
    {
        printf("1ERROR DE ARGUMENTOS");
        exit(1);
    }

    if(validacion(argv[1], argv[3]) == 0)
    {
        if(strcmp(argv[2], "+") == 0)
        {

            printf("%s + %s = %d\n", argv[1], argv[3], suma(atoi(argv[1]), atoi(argv[3]))); // Tambien  se puede con sscanf(argv[1], "%d", &->variable);
            exit(0);

        }else if(strcmp(argv[2], "-") == 0)
        {
            printf("%s - %s = %d\n", argv[1], argv[3], resta(atoi(argv[1]), atoi(argv[3])));
            exit(0);

        }else if(strcmp(argv[2], "x") == 0)
        {
            printf("%s * %s = %d\n", argv[1], argv[3], multiplicacion(atoi(argv[1]), atoi(argv[3])));
            exit(0);
        }else if(strcmp(argv[2], "P") == 0)
        {
            printf("%s a la %s = %d\n", argv[1], argv[3], potencia(atoi(argv[1]), atoi(argv[3])));
            exit(0);
        }else if(strcmp(argv[2], "/") == 0)
        {
            printf("%s / %s = %d\n", argv[1], argv[3], division(atoi(argv[1]), atoi(argv[3])));
            exit(0);
        }
        printf("ERROR DE ARGUMENTOS\n");
        exit(1);

    }


    printf("ERROR DE ARGUMENTOS, NO ES NUMERO\n");
    exit(1);

}
