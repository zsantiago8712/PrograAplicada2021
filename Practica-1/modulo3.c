#include <ctype.h>

#include "local.h"



void is_to_upper(char *opcion);
void encontrar_repetciones(char *opcion, char resultado[]);



/*
    Santiagocha
    Función para validar las opciones que se introdujeron
*/

int  validar_opcion(char *opcion, int argc, int *comandos)
{
    char opciones[] = {'-', 'h', 'n', 'r', 'c', 'e', 'v'};
    int num_opciones = 0;
    int error = 0;
    char resultado[7]  = {'\0', '\0', '\0', '\0', '\0', '\0', '\0'};

    is_to_upper(opcion);

    if(argc == 2)
    {

        if(strlen(opcion) != 2)
        {
            printf("ERROR: solo se puede poner -h cunado se pasan 2 arguemntos\n");
            exit(1);
        }

        for(int i = 0; i < 2; i++)
        {
            if(opciones[i] != opcion[i])
            {
                printf("ERROR\n");
                exit(1);
                
            }else
            {
                num_opciones++;
            }
        }
        
    }else
    {
        encontrar_repetciones(opcion, resultado);
    
        if(resultado[0] != opciones[0])
        {
            printf("ERROR: la primera letra forzosamente tiene que ser - \n");
            exit(1);
        }

        for(int i = 1; i < strlen(resultado); i++)
        {
            for(int j = 1; j < 7; j++)
            {
                if(resultado[i] == opciones[j])
                {
                    if(i > 0)
                    {
                        comandos[i - 1] = j - 1;
                        num_opciones++;
                    }
                    break;
                } 
                if(j == 6)
                {
                    if(opciones[j] != resultado[i])
                    {
                        printf("ERROR: no existe el comando: %c, para mas ayuda inserte -h\n", resultado[i]);
                        exit(1);
                    }
                }
            }
        }
        
        
    }

    return num_opciones;
}

/*
    MAURICIO
    Funcion para crear una lista dinamica tipo LIFO
*/
void crear_lista(char c, LISTA **inicio)
{
    LISTA *nodo;

    nodo = malloc(sizeof(LISTA));
    if(nodo == NULL)
    {
        printf("ERROR: No hay espacio en la memoria\n");
        exit(0);
    }

    
    nodo -> letra = c;
    if(*inicio == NULL)
    {
        nodo -> sig = NULL;
    }else
    {
        nodo -> sig = *inicio;
    }
    *inicio = nodo;

}

/*
MAURICIO
Funcion para recorrer la lista dinamica (PILA/LIFO) y escibri en el archivo
*/
void recorrer_lista(LISTA *inicio, char *argv[], int argc, int imprimir)
{
    LISTA *nodo;
    FILE *fp, *fp2;
    char *archivo_salida = "salida.arch";
    char *archivo_log = NULL;

    if(argc == 4 || argc == 5)
    {
        archivo_salida = argv[3];
        archivo_log = argv[4];
    }

    fp = fopen(strdup(archivo_salida), "a");
    nodo = inicio;
    fputs("\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~COPIADO AL REVES~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n", fp);
    if(imprimir == 1)
    {
        printf("\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~COPIADO AL REVES~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
        while(nodo != NULL)
        {
            fputc(nodo -> letra, fp);
            printf("%c", nodo -> letra);
            nodo = nodo -> sig;      
        }
    }else
    {
        while(nodo != NULL)
        {
            putc(nodo -> letra, fp);
            nodo = nodo -> sig;      
        }
    }
    fclose(fp);

    if(archivo_log != NULL)
    {
        fp2 = fopen(strdup(archivo_log), "a");
        fprintf(fp2, "Se copio de forma al reves los datos del archivo %s al archivo %s\n", argv[2], archivo_salida);
        fclose(fp2);
    }
    printf("\n\nSe copio con exito de forma al reves!!");

    
}

/*
    MAURICIO
    Funcion para liberar la memoria de la lista dinámica
*/
void liberar_memoria(LISTA *inicio)
{
    LISTA *nodo;

    nodo = inicio;
    while(nodo != NULL)
    {
        inicio = nodo -> sig;
        free(nodo);
        nodo = inicio;
    }
    
}


/*
    SANTIAGO
    Función para ver detectar mayusculas y en el case de que encuntre de error
*/
void is_to_upper(char *opcion)
{
    for(int i = 1; i < strlen(opcion); i++)
    {
        if(opcion[i] == toupper(opcion[i]))
        {
            if(opcion[i] == '-')
            {
                printf("El caracter - solo puede estar al inicio, para mas yuda inserte -h\n");
            }else
            {
                printf("ERROR: no existe la opcion  %c, para mas ayuda inserte -h\n", opcion[i]);
            }
            exit(1);
        }
    }
}

/*
    SANTIAGO
    Función para detectar letras repetidas  en la opcion y quitarlas
*/
void encontrar_repetciones(char *opcion, char resultado[])
{
    int repeticion = 0;
    int ant_rep = 0;

    for(int i = 0; i < strlen(opcion); i++)
    {
        if(i > 1)
        {
            if(i == 2)
            {
                if(resultado[i - 1] != opcion[i])
                {
                    
                    resultado[i] = opcion[i];
                }else
                {
                    ant_rep = 1;
                }
            }else
            {
                for(int j = 0; j < i; j++)
                {
                    if(resultado[j] == opcion[i])
                    {
                        repeticion = 1;
                        ant_rep ++;
                        break;
                    }
                }
                if(repeticion == 0)
                {
                    if(ant_rep > 0)
                    {
                        
                        resultado[i - ant_rep] = opcion[i];
                    }else
                    {
                        
                        resultado[i] = opcion[i];
                        ant_rep = 0;
                    }
                    
                }
                repeticion = 0;
            }
            
        }else
        {
            
            resultado[i] = opcion[i];
        }
    }
}