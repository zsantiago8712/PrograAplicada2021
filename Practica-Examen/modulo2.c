#include <string.h>
#include <unistd.h>

#include "local.h"


void create_list(LISTA **inicio, LISTA **aux, char *line, int num_hojas);
void ordenar_alfabeticamente(LISTA *incio);
void reescribir_archivo(LISTA *inicio, char *name_file);


void add_impresion_work(LISTA **inicio, LISTA **aux)
{
    FILE *fp;
    char name_file[200];
    char temp[200];
    char line[200];
    int num_hojas = 0;

    system("clear");
    printf("Introduce el archivo que quieres que se lea: ");
    scanf("%s", name_file);

    fp = fopen(name_file, "r");
    if(fp == NULL)
    {
        printf("ERROR: no existe el archivo (%s)\n", name_file);
    }


    while (fgets(temp, 200, fp) !=  NULL)
    {
        sscanf(temp, "%s %d", line, &num_hojas);
        create_list(inicio, aux, line, num_hojas);
    }

    ordenar_alfabeticamente(*inicio);
    reescribir_archivo(*inicio, name_file);

}




void create_list(LISTA **inicio, LISTA **aux, char *line, int num_hojas)
{
    LISTA *nodo;
    nodo = malloc(sizeof(LISTA));
    if(nodo == NULL)
    {
        printf("ERROR: No hay memoria disponible\n");
        exit(1);
    }


    nodo -> nombre_archivo = strdup(line);
    nodo -> numero_hojas = num_hojas;
    if(*inicio == NULL)
    {
        *inicio = nodo;
    }else
    {
        (*aux) -> sig = nodo;

    }
    (*aux) = nodo;
    nodo -> sig = NULL;

}


void ordenar_alfabeticamente(LISTA *incio)
{
    LISTA *nodo, *nodo2;

    char *temp;
    int num_temp;

    nodo = incio;
    nodo2 = nodo -> sig;

    do
    {

        while (nodo2 != NULL)
        {
            if(strcasecmp(nodo -> nombre_archivo, nodo2 -> nombre_archivo) > 0)
            {
                temp = nodo -> nombre_archivo;
                num_temp = nodo -> numero_hojas;

                nodo -> nombre_archivo = nodo2 -> nombre_archivo;
                nodo -> numero_hojas = nodo2 -> numero_hojas;

                nodo2 -> numero_hojas = num_temp;
                nodo2 -> nombre_archivo = temp; 
            }
            nodo2 = nodo2 -> sig;
        }

        nodo = nodo -> sig;
        if(nodo != NULL)
        {
            nodo2 = nodo -> sig;
        }
        
    }while(nodo != NULL);
    
}

void reescribir_archivo(LISTA *inicio, char *name_file)
{
    LISTA *nodo;
    FILE *fp;

    fp = fopen(name_file, "w");

    nodo = inicio;
    while (nodo != NULL)
    {
        fputs(nodo -> nombre_archivo, fp);
        fputc('\t', fp);
        fprintf(fp, "%d", nodo -> numero_hojas);
        if(nodo -> sig != NULL)
        {
            fputc('\n', fp);
        }
        nodo = nodo -> sig;
    }
    fclose(fp);
    
}


