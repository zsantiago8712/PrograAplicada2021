#include <unistd.h>

#include "local.h"

//Funciones para cada tipo de opcion
void copiar_normal(char *argv[], int argc, int imprmir);
void copiar_alreves(char *argv[], int argc, int imprmir);
void num_caracteres(char *argv[], int argc, int imprmir);
void num_espacios(char *argv[], int argc, int imprmir);
void imprimir_ayuda();

//Funciones que necesitan las funciones de las opciones
extern int validar_opcion(char *opcion, int argc, int *comandos);
extern void crear_lista(char c, LISTA **inicio);
extern void recorrer_lista(LISTA *inicio, char *argv[], int argc, int imprimir);
extern void liberar_memoria(LISTA *inicio);


/*
    SANTIAGO
    Función que sirve como un estilo de menu, llamara a las funciones de las opciones
*/

void opcion(int argc, char *argv[])
{
    void (*opciones[])(char *argv[], int argc, int imprmir) = {imprimir_ayuda, copiar_normal, copiar_alreves, num_caracteres, num_espacios};
    int index_de_opciones[6];
    int imprimir_pantalla = 0;
    int num_comandos = 0;
    FILE *fp, *fp2;
    


    if(argc == 2)
    {
        system("clear");
        imprimir_pantalla = 1;
        num_comandos = validar_opcion(argv[1], argc, index_de_opciones);
        for(int i = 0; i < num_comandos - 1; i++)
        {
            if(index_de_opciones[i] != 5)
            {
                (*opciones[index_de_opciones[i]])(argv, argc, imprimir_pantalla);
            }
        }

    }else if(argc == 3 || argc == 4)
    {
        system("clear");
        imprimir_pantalla = 1;
        if(argc == 4)
        {
            fp = fopen(argv[3], "w");

        }else if(argc == 3)
        {
            fp = fopen("salida.arch", "w");
        }

        fclose(fp);

        num_comandos = validar_opcion(argv[1], argc, index_de_opciones);
        for(int i = 0; i < num_comandos; i++)
        {
            
            if(index_de_opciones[i] != 5)
            {
                (*opciones[index_de_opciones[i]])(argv, argc, imprimir_pantalla);
            }
        }
        

    }else if(argc == 5)
    {
        system("clear");
        fp = fopen(argv[3], "w");
        fp2 = fopen(argv[4], "w");
        fclose(fp);
        fclose(fp2);

        num_comandos = validar_opcion(argv[1], argc, index_de_opciones);
        for(int i = 0; i < num_comandos; i++)
        {
            if(index_de_opciones[i] == 5)
            {
                imprimir_pantalla = 1;
                break;
            }
        }
        for(int i = 0; i < num_comandos; i++)
        {
            if(index_de_opciones[i] != 5)
            {
                (*opciones[index_de_opciones[i]])(argv, argc, imprimir_pantalla);
            }
        }


    }
    printf("\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~FIN~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
}

/*
SANTIAGO
Funcion que copia los datos de un archivo a otro archivo de forma normal
*/

void copiar_normal(char *argv[], int argc, int imprmir)
{
    FILE *fp, *fp2, *fp3;
    char letra;
    char *archivo_salida = "salida.arch";
    char *archivo_log = NULL;

    if(argc == 4 || argc == 5)
    {
        archivo_salida = argv[3];
        archivo_log = argv[4];
    }


    fp = fopen(argv[2], "r");
    if(fp == NULL)
    {
        printf("\nERROR: no existe el archivo %s.\n", argv[2]);
        exit(1);
    }


    fp2 = fopen(strdup(archivo_salida), "a");
    fputs("\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~COPIADO NORMAL~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n", fp2);
    if(imprmir == 1)
    {
        printf("\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~COPIADO NORMAL~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
        while(fscanf(fp, "%c", &letra) != EOF)
        {
            fputc(letra, fp2);
            printf("%c", letra);
        }
    }else
    {
        while(fscanf(fp, "%c", &letra) != EOF)
        {
            fputc(letra, fp2);
        }
    }

    fclose(fp);
    fclose(fp2);
    
    if(archivo_log != NULL)
    {
        fp3 = fopen(strdup(archivo_log), "a");
        fprintf(fp3, "Se copio de forma normal los datos del archivo %s al archivo %s\n", argv[2], archivo_salida);
        fclose(fp3);
    }

    printf("\n\nSe copio con exito de forma normal!!");
    
}

/*
    MAURICIO
    Función para copiar los dato de un archivo a otro de forma inversa
*/

void copiar_alreves(char *argv[], int argc, int imprimir)
{
    LISTA *inicio;
    FILE *fp;
    char letra; 
    char *archivo_salida = "salida.arch";
    char *archivo_log = NULL;

    inicio = NULL;
    if(argc == 4 || argc == 5)
    {
        archivo_salida = argv[3];
        archivo_log = argv[4];
    }


    fp = fopen(argv[2], "r");
    if(fp == NULL)
    {
        printf("\nERROR: no existe el archivo %s.\n", argv[2]);
        exit(1);
    }

    while(fscanf(fp, "%c", &letra) != EOF)
    {
        crear_lista(letra, &inicio);
    }

    fclose(fp);
    recorrer_lista(inicio, argv, argc, imprimir);
    liberar_memoria(inicio);
    
}

/*
    MAURICIO
    Funcíon que cuenta el numer de caracteres en el archivo de entrada
*/

void num_caracteres(char *argv[], int argc, int imprimir)
{
    FILE *fp, *fp2, *fp3;
    char letra;
    int num_chars = 0;
    char *archivo_salida = "salida.arch";
    char *archivo_log = NULL;

    if(argc == 4 || argc == 5)
    {
        archivo_salida = argv[3];
        archivo_log = argv[4];
    }

    
    fp2 = fopen(strdup(archivo_salida), "a");
    fp = fopen(argv[2], "r");
    if(fp == NULL)
    {
        printf("\nERROR: no existe el archivo %s.\n", argv[2]);
        exit(1);
    }

    while(fscanf(fp, "%c", &letra) != EOF)
    {
        num_chars++;
    }
    fclose(fp);
    fputs("\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~CONTEO DE CARACTERES~~~~~~~~~~~~~~~~~~~~~~~\n\n", fp2);
    fprintf(fp2, "%d", num_chars);
    fclose(fp2);

    if(imprimir == 1)
    {
        printf("\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~CONTEO DE CARACTERES~~~~~~~~~~~~~~~~~~~~~~~\n\n");
        printf("Hay %d de caracteres en el archivo %s.\n", num_chars, argv[2]);
    }

    if(archivo_log != NULL)
    {
        fp3 = fopen(strdup(archivo_log), "a");
        fprintf(fp3, "Se contaron %d caracteres del archivo %s\n", num_chars, argv[2]);
        fclose(fp3);
    }
    
}

/*
    SANTIAGO
    Funcion que cuenta el numero de espacios que hay en el archivo de entrada
*/

void num_espacios(char *argv[], int argc, int imprimir)
{
    FILE *fp, *fp2, *fp3;
    char letra;
    int num_esp = 0;
    char *archivo_salida = "salida.arch";
    char *archivo_log = NULL;

    if(argc == 4 || argc == 5)
    {
        archivo_salida = argv[3];
        archivo_log = argv[4];
    }


    fp = fopen(argv[2], "r");
    fp2 = fopen(strdup(archivo_salida), "a");
    if(fp == NULL)
    {
        printf("\nERROR: no existe el archivo %s.\n", argv[2]);
        exit(1);
    }

    while(fscanf(fp, "%c", &letra) == 1)
    {
        if(letra == 32)
        {
            num_esp++;
        }
    }
    fclose(fp);
    fputs("\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~CONTEO DE ESPACIOS~~~~~~~~~~~~~~~~~~~~~~~~~\n\n", fp2);
    fprintf(fp2, "%d", num_esp);
    fclose(fp2);
    if(imprimir == 1)
    {
        printf("\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~CONTEO DE ESPACIOS~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
        printf("Hay %d de espacios en el archivo %s\n", num_esp, argv[2]);
    }
    if(archivo_log != NULL)
    {
        fp3 = fopen(strdup(archivo_log), "a");
        fprintf(fp3, "Se contaron %d espacios del archivo %s\n", num_esp, argv[2]);
        fclose(fp3);
    }
}


/*
    SANTIAGO
    Funcion que imoreme el menu de ayuda en la terminal
*/
void imprimir_ayuda(char *argv[], int argc, int imprimir)
{
    
    FILE *fp;

    if(imprimir == 0)
    {
        return;
    }

    if(argc == 5)
    {
        fp = fopen(argv[4], "a");
        fprintf(fp, "Se imprimio el menu de ayuda\n");
        fclose(fp);
    }

    printf("\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~MENU DE AYUDA~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
    printf("Los parametros deberan pasarse de esta manera.\n");
    printf("-opcion nombre_de_archivo_a_leer [archivo_a_escribir] [archvio_log]\n");
    printf("Los parametros que esten en [] son opcionales y no se deberan escirbir con estos.\n\n");

    printf("-OPCIONES:\n");
    printf("-n: Para copiar el archivo en modo normal.\n");
    printf("-r: Para copiar el archivo en reverso.\n");
    printf("-c: Para conocer el numero de caracteres que hay en el archivo.\n");
    printf("-e: Para conocer el numero de espacios en el archivo.\n");
    printf("-v: Para imprimr la informacion del archivo en pantalla.\n");
    printf("-h: Para desplegar en pantalla una ayuda para las opciones.\n");


}



