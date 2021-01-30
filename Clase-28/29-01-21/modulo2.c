#include <stdio.h>
#include <stdlib.h>


void guardarNumeros(char *nombre, int numeros[])
{

    FILE *fp;
    fp = fopen(nombre, "w");
    for(int i = 0; i < 10; i++)
    {
        fprintf(fp, "%d\n", numeros[i]);
        
    }
    fclose(fp);
    printf("Se guradaron los datos con exito!\n");
}


extern int sumaNumeros(char *nombre)
{
    FILE *fp;
    int numero = 0, resultado = 0, a;
    /*fopen regresa 1 si encontro el archivo, en el caso de que no regresa NULL*/
    if((fp = fopen(nombre, "r"))== NULL)
    {
        printf("ERROR: No existe el archivo con el nombre '%s'", nombre);
        exit(0);
    }


    /* Cada ves que fscanf la computadora el archivo si encunentra un carater regresar 1,
        es po eso que en while esta comparando*/
    while(fscanf(fp, "%d", &numero) == 1)                            
    {
        resultado += numero;
    }
    fclose(fp);
    return resultado;
}