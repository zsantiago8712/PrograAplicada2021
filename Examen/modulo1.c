/**************************************
 *Funciones - Examen 1
 *Programación Aplicada
 *************************************/
 
#include "local.h"

/*Parte 1.
 *Función agregar_cancion: Crea una lista y la llena con la información correspondiente.
 *Recibe: Doble apuntador a inicio, doble apuntador a aux.
 *Devuelve: Void*/
void agregar_cancion(LISTA **inicio, LISTA **aux)
{
    LISTA *nodo;
    nodo = malloc(sizeof(LISTA));
 
    if(nodo == NULL)
    {
        printf("ERROR\n");
        exit(1);
    }
 
    scanf("%s",nodo->nombre_cancion);
    printf("\nIntroduce el nombre del interprete: ");
    scanf("%s",nodo->interprete);
    printf("\nIntroduce el nombre del album: ");
    scanf("%s",nodo->album);
    printf("\nIntroduce el año en el que salio el album: ");
    scanf("%d",&nodo->year);
 
    nodo = *inicio;
    if(*inicio == NULL)
    {
        *inicio = nodo;
    }else
    {
        (*aux)->sig = nodo;
    }
    *aux = nodo;
    nodo->sig = NULL;
 
}

/*Parte 2: Santiago Zamora Solís
*Función reproducir_cancion: Imprime el contenido del nodo y lo libera.
*Recibe: doble apuntador a inicio.
*Devuelve: void*/
void reproducir_cancion(LISTA *inicio)
{
    LISTA *nodo;
    if(inicio != NULL)
    {
        nodo = inicio;
        printf("Nombre de cancion: %s\n", nodo->nombre_cancion);
        printf("Nombre del interprete %s\n", nodo->interprete);
        printf("Nombre del album: %s\n", nodo->album);
        printf("Año en el que salio la cancion %d\n", nodo->year);
        inicio = nodo -> sig;
        free(nodo);
    }
}

/*Parte 3: Sebastián Sedano Castañeda
*Función ver_lista: Imprime el encabezado de la tabla, recorre la lista
e imprime el nombre de la canción y el intérprete
*Recibe: doble apuntador a inicio.
*Devuelve: void.*/
void ver_lista(LISTA *inicio){
    //Variable nodo de tipo lista
    LISTA *nodo;
    printf("Canción\tIntérprete\tAlbum\tYear\n");
    printf("--------------------------------");
    nodo = inicio;
    while(nodo!=NULL){
        printf("%s\t%s\t%s\t%s\t%d\n",nodo->nombre_cancion, nodo->interprete, nodo->album, nodo->year);
        nodo = nodo->sig;
    }
}


void escribir_lista_archivo(LISTA *inicio){
    
    FILE *fp;
    LISTA *nodo;
    char *name_file;

    prinft("Pon el nombre del archivo en donde quieres que se copie: ");
    scanf("%s", name_file);
    fp = fopen(strdup(name_file), "w");

    nodo=inicio;
    while(nodo!=NULL){
        fprintf(fp, "%s", nodo->nombre_cancion);
        fprintf(fp, "%s", nodo->interprete);
        fprintf(fp, "%s", nodo->album);
        fprintf(fp, "%d", nodo->year);
        nodo=nodo->sig;
    }

}


