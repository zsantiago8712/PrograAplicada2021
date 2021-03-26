#include <strings.h>
#include <string.h>
#include "local.h" 

void insertar(ARBOL **inserccion, char *line, int ocurrencia);

/*********************************************************************************************************************+*****

* parte 1: Hecha por Santiago Zamora Solis, Mauricio Olguin Lew y Sebastián Sedano Castañeda *

*se creo una lista fifo que guarda la palabra y su ocurrencia para despues vaciarla en el arbos binario *

* se crea el arbol binario a partir de un archivo de texto que contiene la palabra y el número de ocurrencias de la misma *

****************************************************************************************************************************/
void create_list(LISTA **inicio, LISTA **aux, char *palabra)
{
    LISTA *nodo;
    nodo = malloc(sizeof(LISTA));
    if(nodo == NULL)
    {
        printf("ERROR: No hay memoria disponible\n");
        exit(1);
    }


    nodo -> palabra = strdup(palabra);
    nodo -> ocurrencia = 1;
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
/*********************************************************************************************************************+*****

* parte 1: Hecha por Santiago Zamora Solis, Mauricio Olguin Lew y Sebastián Sedano Castañeda *

*se creo una lista fifo que guarda la palabra y su ocurrencia para despues vaciarla en el arbos binario *

* se crea el arbol binario a partir de un archivo de texto que contiene la palabra y el número de ocurrencias de la misma *

****************************************************************************************************************************/

int buscar_ocurrencia(LISTA *inicio, char *palabra)
{
    LISTA *nodo;
    nodo = inicio;

    while(nodo != NULL)
    {
        if(strcasecmp(strdup(palabra), nodo -> palabra) == 0)
        {
            nodo -> ocurrencia += 1;
            return 1;
        }
        nodo = nodo -> sig;      
    }

    return 0;

} 

/*********************************************************************************************************************+*****

* parte 1: Hecha por Santiago Zamora Solis, Mauricio Olguin Lew y Sebastián Sedano Castañeda *

*se creo una lista fifo que guarda la palabra y su ocurrencia para despues vaciarla en el arbos binario *

* se crea el arbol binario a partir de un archivo de texto que contiene la palabra y el número de ocurrencias de la misma *

****************************************************************************************************************************/
void recorrer_list(LISTA *inicio, ARBOL **inserccion)
{
    LISTA *nodo;

    nodo = inicio;
    while (nodo != NULL)
    {
        //printf("%s --> %d\n", nodo -> palabra, nodo -> ocurrencia);
        insertar(inserccion, nodo -> palabra, nodo -> ocurrencia);
        nodo = nodo -> sig;  
    }
    
}


/*********************************************************************************************************************+*****

* parte 1: Hecha por Santiago Zamora Solis, Mauricio Olguin Lew y Sebastián Sedano Castañeda *

*se creo una lista fifo que guarda la palabra y su ocurrencia para despues vaciarla en el arbos binario *

* se crea el arbol binario a partir de un archivo de texto que contiene la palabra y el número de ocurrencias de la misma *

****************************************************************************************************************************/


void insertar(ARBOL **inserccion, char *line, int ocurrencia)
{
    ARBOL *avanza, *nuevo;
    avanza = *inserccion;

    nuevo = malloc(sizeof(ARBOL));
    if(nuevo == NULL)
    {
        printf("ERROR");
        exit(1);
    }

    nuevo -> palabra = strdup(line);
    strcpy(nuevo -> palabra, line);
    nuevo -> ocurrencia = ocurrencia;
    nuevo -> izq = NULL;
    nuevo -> der = NULL;


    if(avanza == NULL)
    {
        *inserccion = nuevo;
        return;
    }
    
    while(avanza != NULL)
    {
        if(ocurrencia >= avanza -> ocurrencia) // <= para que los ordene de mayor a menor
        {
            if(avanza -> der != NULL)
            {
                avanza = avanza -> der;
            }else
            {
                avanza -> der = nuevo;
                return;
            }
        }
        else
        {
            if(avanza -> izq != NULL)
            {
                avanza = avanza -> izq;
            }else
            {
                avanza -> izq = nuevo;
                return;
            }
        }

    }

}




/**************************************************************** parte 3: Hecha por Mauricio Olguin Lew ** función recorrer_arbol: recorre el árbol binario, ** asigna una relevancia dependiendo de la ocurrencia ** e imprime en pantalla una tabla con la relevancia y palabra ****************************************************************/
void imprimir(ARBOL *raiz){

    if(raiz != NULL){

        imprimir(raiz -> izq);


        if(raiz->ocurrencia >= 10){

            printf("5");

        }

        if(raiz->ocurrencia >= 8 && raiz->ocurrencia <10){

            printf("4");

        }

        if(raiz->ocurrencia >= 6 && raiz->ocurrencia <8){

            printf("3");

        }

        if(raiz->ocurrencia >= 4 && raiz->ocurrencia <6){

            printf("2");

        }

        if(raiz->ocurrencia < 4){

            printf("1");

        }

        printf("                    %s\n", raiz -> palabra);

        imprimir(raiz -> der);

    }

}


//Parte 2: Hecha por SebastiÃ¡n Sedano CastaÃ±eda (incluye funciones imprime y guardaReporte)
/*FunciÃ³n imprime: Recorre el Ã¡rbol desde el numero mayor hasta el menor, imprime en el archivo
*la palabra y su ocurrencia, mientras hayan sido los 5 mayores.
*ParÃ¡metros: apuntador a raiz, apuntador a fp y apuntador a contador.
*Devuelve:void.*/
void imprime(ARBOL *raiz, FILE *fp, int *cont){
    if(raiz != NULL){
        printf("%d", *cont);
        if((*cont) < 5){
            imprime(raiz->der,fp,cont);
            fprintf(fp,"%s\t %d\n", raiz->palabra, raiz->ocurrencia);
            (*cont) += 1;
            imprime(raiz->izq,fp,cont);
        }else
        {
            return;
        }
    }
}

/*Funcion guardaReporte: Abre el archivo, manda a llamar a función imprime y cierra el archivo.
 *ParÃ¡metros: apuntador a raiz.
 *Devuelve void.*/
void guardaReporte(ARBOL *raiz, int *cont){
    FILE *fp;
   
    fp = fopen("resultados.txt","w");
    if(fp==NULL){
        printf("No existe el archivo");
    }
    fprintf(fp,"Palabra:\t Ocurrencias:\n");
    imprime(raiz,fp, cont);
    fclose(fp);
}


//Parte 4: Santiago Zamora Solis
/*buscarPalabras: Recorrer el árbol y busca coincidencia entre la palabra ingresada y cada nodo
Recibe: Apuntador a raiz y la palabra ingresada.
Devuelve: void*/
void buscarPalabra(ARBOL *raiz, char *palabra){
    if(raiz != NULL){
        buscarPalabra(raiz->izq,palabra);
        if(strcmp(palabra,raiz->palabra) == 0){
            archivoBusqueda(raiz);
            return;
        }
        buscarPalabra(raiz->der,palabra);
    }
}









/*Santiago Zamora Solis archivoBusqueda: Abre el archivo encontradas.txt y guarda la palabra buscada y sus coincidencias.
*Recibe: Apuntador a raiz.
*Devuelve: void*/
void archivoBusqueda(ARBOL *raiz){
    FILE *fp;
    fp = fopen("encontradas.txt","w");
    if(fp==NULL){
        printf("No existe el archivo");
    }
    fprintf(fp,"Palabra:\t Ocurrencias:\n");
    fprintf(fp,"%s\t %d\n", raiz->palabra, raiz->ocurrencia);
    fclose(fp);
}