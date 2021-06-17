#include "tables.h"
#include <stdio.h>
#include <stdlib.h>

/*************** PROTOTIPOS DE FUNCION ***************/ 
void initialise(void *datos);
void getevent(void *datos);

int encender(void *datos);
int error_encendido(void *datos);
int correcto(void *datos);
int tres_veces(void *datos);
int bienvenida(void *datos);
int error_clave(void *datos);
int bloquear_radio(void *datos);
int modificar_archivo(void *datos);
int creacion_archivo(void *datos);
int lectura_archivo(void *datos);
int error_seleccion(void *datos);
int seis_mod(void *datos);
int error_modificacion(void *datos);
int error_creacion(void *datos);
int existe_archivo(void *datos);
int error_lectura(void *datos);
int seis_veces(void *datos); 
int error_agregar(void *datos);
int despedida(void *datos);
int mostrar_estacion1(void *datos);
int mostrar_estacion2(void *datos);
int mostrar_estacion3(void *datos);
int mostrar_estacion4(void *datos);
int mostrar_estacion5(void *datos);
int mostrar_estacion6(void *datos);
int mostrar_cd(void *datos);
int error_menu(void *datos);
int error_seis_veces(void *datos);
int num_estaciones(void *datos); 
int mostrar_opciones(void *datos);
int error_modificar_archivo(void *datos);
int error_num_estaciones(void *datos);
int error_existe_archivo(void *datos);
int instrucciones_creacion_archivo(void *datos);



/*************** MAIN ***************/ 
int main(int argc, char **argv)
{
    // Variables de la máquina de estados
    EVENT event;

    int actx, auxx, outcome;

    initialise(&event);
    
    while (1) {    /* loop infinito para la MFE */
        getevent(&event);

        for ((actx = state_table[event.state].start);(action_table[actx].event != event.etype) && (actx < state_table[event.state].end);actx++)
            ;
        outcome = (*(action_table[actx].action))(&event);
            if(action_table[actx].moreacts == -1)
                event.state = action_table[actx].nextstate;
            else {
                auxx = action_table[actx].moreacts + outcome;
                while (auxx != -1){
                    outcome = (*(aux_table[auxx].action))(&event);
                    if (aux_table[auxx].moreacts == -1 ){
                        event.state = aux_table[auxx].nextstate;
                        auxx = -1;
                    }
                    else
                        auxx = aux_table[auxx].moreacts + outcome;
                
                }
        }
        
    } /* while(1) */
}

void initialise(void *datos)
{
    EVENT *event = (EVENT *) datos;

    event->state = 0;
    event -> intentos = 0;
    event -> numero_estaciones = 0;
    bienvenida(datos);//Mensaje de inicio
}

//Toma los eventoss
void getevent(void *datos)
{
    EVENT *event = (EVENT *) datos;
    char *ptmp;
    char buf[BUFFER];

    //strcpy(buf, event->buf); Aquí estaba esta linea en el original 
    //ptmp = &buf[2];
    
#ifdef DEBUG 
    printf("wait event \n");
#endif
    gets(event->buf);
    //scanf("%s", event -> buf);
    strcpy(buf, event->buf); //Aquí es donde deberían ir
    ptmp = &buf[2];
    
    //scanf("%[^\n]s",event->buf);
         switch (event->buf[0]){
                case 'O':
                    event->etype = ENCENDIDO;
                    system("clear");
                    break;
                case 'C': //Entradas que requieren información adicional 
                    event->etype = CLAVE;
                    strcpy(event->args,ptmp);
                    system("clear");
                    break;
                case 'T':
                    strcpy(event->nombre_archivo,ptmp);
                    event->etype = NOMBRE_MOD_ARCHIVO;
                    system("clear");
                    break;
                case 'R':
                    event->etype = NOMBRE_CREACION_ARCHIVO;
                    system("clear");
                    break;
                case 'L':
                    event->etype = NOMBRE_LECTURA_ARCHIVO;
                    system("clear");
                    break;
                case 'M':
                    strcpy(event->agregar_estacion,ptmp);
                    event->etype = MODIFICACION;
                    system("clear");
                    break;
                case 'F':
                    strcpy(event->nombre_archivo,ptmp);
                    event->etype = NOMBRE_NUEVO_ARCHIVO;
                    system("clear");
                    break;
                case 'N':
                    strcpy(event->nombre_archivo,ptmp);
                    event->etype = NOMBRE_ARCHIVO;
                    system("clear");
                    break;
                case 'A':
                    strcpy(event->agregar_estacion,ptmp);
                    event->etype = NOMBRE_ESTACION;
                    system("clear");
                    break;
                case 'G':
                    event->etype = APAGAR;
                    system("clear");
                    break;
                case 'S':
                    event->etype = ESTACION1;
                    system("clear");
                    break;
                case 'H':
                    event->etype = ESTACION2;
                    system("clear");
                    break;
                case 'I':
                    event->etype = ESTACION3;
                    system("clear");
                    break;
                case 'J':
                    event->etype = ESTACION4;
                    system("clear");
                    break;
                case 'K':
                    event->etype = ESTACION5;
                    system("clear");
                    break;
                case 'P':
                    event->etype = ESTACION6;
                    system("clear");
                    break;
                case 'D':
                    strcpy(event->cd,ptmp); 
                    event->etype = CD;
                    system("clear");
                    break;
                default:
                    event->etype = -1; //Entradas cualquier otra cosa
                    system("clear");
                    break;
                

		#ifdef DEBUG
    			printf("---> %s \n",event->args);
		#endif

                     
             }//switch
}// getevent
 

/* FUNCIONES DE IMPLEMENTACION */

//Muestra como encnder el programa
int encender (void *datos){

    printf("Ingresa tu CLAVE: [C:****]:\n");
    
}

//Muestra que no se encendio de manera correcta
int error_encendido(void *datos){
    printf("Para encender el radio corectamente introdusca -> O\n");
}

//
int correcto(void *datos){
    EVENT *event = (EVENT *)datos;
    if(strcmp("1234", event -> args)== 0){
        return 0;
    }else
    {
        return 1;
    }
}


//Muestra como modificar un archivo
int modificar_archivo(void *datos){
    printf("Ingrese [M: nombre de la estacion que se agregara al archivo]\n");
}

//Muestra como poner el nombre del archivo
int instrucciones_creacion_archivo(void *datos){
    printf("Ingrese [F: nombre del arhcivo] para crear un nuevo archivo\n");
    
}

//Lectura archivo: Indica al usuario como ingresar el nombre del archivo para leerlo
int lectura_archivo(void *datos){
    printf("Ingrese [N:nombre del archivo] para leer las estaciones\n");
}

//error_seleccion: Indica que no se tomo una letra correcta
int error_seleccion(void *datos){
    printf("Seleccione una letra valida\n\n\n");
    menu_archivos(datos);
}

//creacion_archivo: genera un archivo y permite que se vayan ingresando estaciones
int creacion_archivo(void *datos)
{
    EVENT *event = (EVENT *) datos;
    FILE *fp;

    fp = fopen(event -> nombre_archivo, "w");
    fclose(fp);
    printf("Se creo correctamente el archivo\n\n");

    printf("Ingrese [A:El nombre de la estacion que se va a gregar]\n");
}

//error_existe_archivo: indica que no existe el archivo
int error_existe_archivo(void *datos)
{
    printf("No existe el archivo\n");
}

//error_modificacion: Aparece cuando el archivo no logró modificarse
int error_modificacion(void *datos){
    printf("El archivo no se modifico de manera correcta\n");
}

//error_creacion: En caso de que el archivo no se haya creado correctamente
int error_creacion(void *datos){
    printf("Error al crear el archivo\n");
}

//error_lectura: Que el archivo no pudo leerse
int error_lectura(void *datos){
    printf("Error al leer el archivo\n");
}

//error_agregar: cuando no pudo mostrarse la estación
int error_agregar(void *datos){
    printf("Error al agregar la estación\n");
}

//despedida: cuando selecciona la opción salir
int despedida(void *datos){
    printf("Adios =)\n\n");
}

//Todas las funciones mostrar_estacion imprimen la estación recuperada del archivo
int mostrar_estacion1(void *datos){
    EVENT *event = (EVENT *) datos;
    printf("ESTACION 1.- %s\n\n", event -> estaciones[0]);
    mostrar_opciones(datos);
}

int mostrar_estacion2(void *datos){
    EVENT *event = (EVENT *) datos;
    printf("ESTACION 2.- %s\n\n", event -> estaciones[1]);
    mostrar_opciones(datos);
}
int mostrar_estacion3(void *datos){
    EVENT *event = (EVENT *) datos;
    printf("ESTACION 3.- %s\n\n", event -> estaciones[2]);
    mostrar_opciones(datos);
}
int mostrar_estacion4(void *datos){
    EVENT *event = (EVENT *) datos;
    printf("ESTACION 4.- %s\n\n", event -> estaciones[3]);
    mostrar_opciones(datos);
}
int mostrar_estacion5(void *datos){
    EVENT *event = (EVENT *) datos;
    printf("ESTACION 5.- %s\n\n", event -> estaciones[4]);
    mostrar_opciones(datos);
}
int mostrar_estacion6(void *datos){
    EVENT *event = (EVENT *) datos;
    printf("ESTACION 6.- %s\n\n", event -> estaciones[5]);
    mostrar_opciones(datos);
}

int mostrar_cd(void *datos)
{
    EVENT *event = (EVENT *) datos;
    printf("CD.- %s\n\n", event -> cd);
    mostrar_opciones(datos);
}

//tres_veces: Cuenta la cantidad de intentos que se han hecho de ingresar la clave
int tres_veces(void *datos)
{
    EVENT *event = (EVENT *) datos;
    event -> intentos++;
    if(event -> intentos == 3)
    {
        return 3;
    }else
    {
        return 2;
    }
}


//bloquear_radio: Muestra mensaje de bloqueo cuando la clave es incorrecta
int bloquear_radio(void *datos)
{
    printf("El radio se bloqueo por 20 segundos por ingresar tres veces la clave incorrecta\n\n");
    sleep(20);
}


//seis_mod: Permite al usuario modificar el archivo ingresado hasta seis veces
int seis_mod(void *datos)
{
    EVENT *event = (EVENT *) datos;
    FILE *fp;
    int index = 0;
    fp = fopen(event -> nombre_archivo, "a");

    fprintf(fp, "%s\n", event -> agregar_estacion);
    fclose(fp);

    fp = fopen(event -> nombre_archivo, "r");
    while (fscanf(fp, "%s", event -> estaciones[index]) == 1)
    {
        event -> numero_estaciones++;
        index++;
    }
    fclose(fp);
    
    if(event -> numero_estaciones== 6)
    {
        return 4;
    }

    return 5;
}

//existe_archivo: Revisa si el archivo proporcionado existe
int existe_archivo(void *datos)
{
    EVENT *event = (EVENT *) datos;
    FILE *fp;
    
    fp = fopen(event -> nombre_archivo, "r");
    if(fp == NULL)
    {
        fclose(fp);
        return 10;
    }
    fclose(fp);
    return 8;
}

// Cuenta cuantos estaciones tiene el archivo
int num_estaciones(void *datos)
{
    EVENT *event = (EVENT *) datos;
    FILE *fp;
    int index = 0;

    fp = fopen(event -> nombre_archivo, "r");

    while (fscanf(fp, "%s", event -> estaciones[index]) == 1)
    {
        event -> numero_estaciones += 1;
        index ++;
    }
    fclose(fp);

    if(event -> numero_estaciones >= 6)
    {
        return 4;
    }
    
    event -> numero_estaciones= 6;
    return 9; 

}

//Funcion para introducinr una estacion al archivo y cuneat cunatoas tiene el archivo
int seis_veces(void *datos)
{
    EVENT *event = (EVENT *) datos;
    FILE *fp;
    int index = 0;
    event -> numero_estaciones = 0;

    fp = fopen(event -> nombre_archivo, "a");
    
    fprintf(fp, "%s\n", event -> agregar_estacion);
    fclose(fp);
    
    fp = fopen(event -> nombre_archivo, "r");
    while (fscanf(fp, "%s", event -> estaciones[index]) == 1)
    {
        event -> numero_estaciones++;
        index ++;
    }
    fclose(fp);
    
    if(event -> numero_estaciones == 6)
    {
        return 4;
    }

    return 7;

}

//Muesta error de numero de estaciones introducidas
int error_seis_veces(void *datos)
{
    EVENT *event = (EVENT *) datos;
    printf("Faltan %d estaciones\n\n", 6 - event -> numero_estaciones);
    printf("Ingrese [A:El nombre de la estacion que se va a gregar]\n");
}

//Muestra error de numero de estaciones
int error_num_estaciones(void *datos)
{
    printf("No hay suficienets estaciones, es necesario que haya 6 estaciones\n");
    menu_archivos(datos);
}

//Muestra bienvenida del radio
int bienvenida(void *datos)
{
    EVENT *event = (EVENT *) datos;
    event -> intentos = 0;
    event -> numero_estaciones = 0;
    printf("Bienvenido al Radio.\nIngrese [O] para encer el radio.\n");
}

//Muestra error al no poner la clave correcta
int error_clave(void *datos)
{
    printf("La clave introducida es incorrecta\n");
    encender(datos);
}

//Muestra error del menu
int error_menu(void *datos)
{
    printf("Opcion no valida!\n");
    mostrar_opciones(datos);
}

//Muestra menu de estaciones y cd
int mostrar_opciones(void *datos){
    EVENT *event = (EVENT *) datos;

    printf("Seleccione una opción\n");
    printf("S - Estación 1  (%s)\n", event -> estaciones[0]);
    printf("H - Estación 2  (%s)\n", event -> estaciones[1]);
    printf("I - Estación 3  (%s)\n", event -> estaciones[2]);
    printf("J - Estación 4  (%s)\n", event -> estaciones[3]);
    printf("K - Estación 5  (%s)\n", event -> estaciones[4]);
    printf("P - Estación 6  (%s)\n", event -> estaciones[5]);
    printf("D:[nombre del disco] - CD\n");
    printf("G - Salir\n");
}

//Muestra error al modificar un archivo
int error_modificar_archivo(void *datos){
    EVENT *event = (EVENT *) datos;
    printf("Faltan %d estaciones\n\n", 6 - event -> numero_estaciones);
    modificar_archivo(datos);
    
}

//Menu de seleccion para archivos
int menu_archivos(void *datos)
{
    printf("Ingresa [T: nombre del archivo que se agregaran estaciones]\n");
    printf("Ingresa [R] para crear un archivo nuevo e ingresar nuevas estaciones\n");
    printf("Ingresa [L] para abrir un archivo y leer las estaciones\n");
}