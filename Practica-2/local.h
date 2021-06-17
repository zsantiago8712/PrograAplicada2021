
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
/****************************************************************
 *								                                *
 * Archivo:	local.h						                        *
 * Descripcion: Archivo de encabezado para maquina de estados	*
 *		Aqui se definen todos los tipos de datos y 	            *
 *		constantes que se utilizan en el programa	            *
 *								                                *
 ****************************************************************/

/******************* CONSTANTES *******************
 * En esta seccion se declaran todas las 	      *
 * las constantes que se necesiten en el programa *
 **************************************************/ 
#define BUFFER        128
#define L_EVENT_ARGS  21


/****************** ESTRUCTURAS *****************
 * En esta seccion se declaran todas las	    *
 * estructuras que se necesiten en el programa	*
 ************************************************/ 

// Este tipo de datos se utiliza para leer la informacion
// que teclea el usuario 
struct event_s
{
    int etype;
    char args[L_EVENT_ARGS];
    int state;
    char buf[BUFFER];
    int intentos;
    char estaciones[6][BUFFER];
    char nombre_archivo[L_EVENT_ARGS];
    char agregar_estacion[BUFFER];
    char cd[BUFFER];
    int numero_estaciones;
};
typedef struct event_s EVENT;

// Este tipo de datos se utiliza para implementar 
// la tabla auxiliar
struct aux_table_s 
{
    int (*action)(void *datos);
    int moreacts;
    int nextstate;
};
typedef struct aux_table_s AUX_TAB;

// Este tipo de datos se utiliza para implementar
// la tabla de accion
struct action_tab_s 
{
    int event;
    int (*action)(void *datos);
    int moreacts;
    int nextstate;
};
typedef struct action_tab_s ACTION_TAB;

// Este tipo de datos se utiliza para implementar
// la tabla de estados
struct state_tab_s 
{
    int state;
    int start;
    int end;
};
typedef struct state_tab_s STATE_TAB;


/********************* EVENTOS *******************
 * En esta seccion se declaran como constantes	 *
 * los eventos (entradas) que recibe el programa *
 *************************************************/ 
#define ENCENDIDO                       0   // O
#define CLAVE                           2   // C
#define NOMBRE_MOD_ARCHIVO              4   // T
#define NOMBRE_CREACION_ARCHIVO         5   // R
#define NOMBRE_LECTURA_ARCHIVO          6   // L
#define MODIFICACION                    8   // M
#define NOMBRE_NUEVO_ARCHIVO            10  // F
#define NOMBRE_ARCHIVO                  12  // N
#define NOMBRE_ESTACION                 14  // A 
#define APAGAR                          16  // G
#define ESTACION1                       17  // S
#define ESTACION2                       18  // H
#define ESTACION3                       19  // I
#define ESTACION4                       20  // J
#define ESTACION5                       21  // K
#define ESTACION6                       22  // P
#define CD                              23  // D





/********************* ESTADOS ******************
 * En esta seccion se declaran como constantes	*
 * los estados de que consta el programa 	    *
 ************************************************/ 
#define E_INICIO                    0 
#define E_CLAVE                     1
#define E_DESICION_ARCHIVO          2
#define E_MODIFICAR_ARCHIVO         3
#define E_CREAR_ARCHIVO             4
#define E_LEER_ARCHIVO              5
#define E_AGREGAR_ESTACION          6
#define E_MENU                      7









