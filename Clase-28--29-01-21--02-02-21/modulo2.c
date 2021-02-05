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


    /* Cada ves que fscanf la computadora lee archivo si encunentra un carater regresar 1,
        es po eso que en el while esta comparando con un 1*/
    while(fscanf(fp, "%d", &numero) == 1)                            
    {
        resultado += numero;
    }
    fclose(fp);
    return resultado;
}




void guardarNumerosBinarios(char *nombre, int numeros[])
{
    FILE *fp;
    int numero = 0, resultado = 0, a;

    fp = fopen(nombre, "wb");

    fwrite(numeros, sizeof(int), 10, fp);

    fclose(fp);

}




int sumaNumerosBinario(char *nombre)
{
    FILE *fp;
    int numeros[10];
    int i, resultado = 0;

    fp = fopen(nombre, "rb");
    if(fp == NULL)
    {
        printf("ERROR: EL archivo no existe");
        exit(0);
    }


    fread(numeros, sizeof(int), 10, fp);
    fclose(fp);

    for(i = 0; i < 10; i++)
    {
        resultado += numeros[i];
    }

    return resultado;
}