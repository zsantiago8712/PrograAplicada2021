/************************************************************************
 *									*
 * Archivo:	tables.h						*
 * Descripcion: Tablas para la maquina de estados y funciones externas	*
 *		Aqui se definen todos las tablas que se utilizan	*
 *		en el programa						*
 *									*
 ************************************************************************/

/*************** ARCHIVOS DE INCLUSION ***************/ 
#include "local.h"
#include <stdio.h>
#include <stdlib.h>


/*************** FUNCIONES EXTERNAS *********************
 * En esta seccion se declaran los encabezados de 	*
 * todas las funciones que se utilizan en las     	*
 * tablas del programa. Todas las funciones deben 	*
 * ser de tipo entero y no deben recibir parametros	*
 ********************************************************/ 
extern int encender(void *datos);
extern int error_encendido(void *datos);
extern int correcto(void *datos);
extern int tres_veces(void *datos);
extern int bienvenida(void *datos);
extern int error_clave(void *datos);
extern int bloquear_radio(void *datos);
extern int modificar_archivo(void *datos);
extern int creacion_archivo(void *datos);
extern int lectura_archivo(void *datos);
extern int error_seleccion(void *datos);
extern int seis_mod(void *datos);
extern int error_modificacion(void *datos);
extern int error_creacion(void *datos);
extern int existe_archivo(void *datos);
extern int error_lectura(void *datos);
extern int seis_veces(void *datos); 
extern int error_agregar(void *datos);
extern int despedida(void *datos);
extern int mostrar_estacion1(void *datos);
extern int mostrar_estacion2(void *datos);
extern int mostrar_estacion3(void *datos);
extern int mostrar_estacion4(void *datos);
extern int mostrar_estacion5(void *datos);
extern int mostrar_estacion6(void *datos);
extern int mostrar_cd(void *datos);
extern int error_menu(void *datos);
extern int error_seis_veces(void *datos);
extern int num_estaciones(void *datos);
extern int mostrar_opciones(void *datos);
extern int error_modificar_archivo(void *datos);
extern int error_num_estaciones(void *datos);
extern int error_existe_archivo(void *datos);
extern int menu_archivos(void *datos);
extern int instrucciones_creacion_archivo(void *datos);

/******************** TABLAS ********************
 * En esta seccion se declaran las tablas	*
 * que se van a usar en el programa		*
 ************************************************/ 
 
/*************** TABLA DE ACCION ***************/  
ACTION_TAB action_table[]={
    /*etype          accion                 bandera           sigEdo. */    
    {ENCENDIDO,       encender,   	            -1,                 E_CLAVE},
    {-1,              error_encendido,	        -1,	                E_INICIO},
    
    {CLAVE,           correcto,                 0,                 -1},
    {-1,              error_clave,               -1,            E_CLAVE},

    {NOMBRE_MOD_ARCHIVO, modificar_archivo,     -1,             E_MODIFICAR_ARCHIVO},
    {NOMBRE_CREACION_ARCHIVO, instrucciones_creacion_archivo, -1,   E_CREAR_ARCHIVO},
    {NOMBRE_LECTURA_ARCHIVO, lectura_archivo,    -1,             E_LEER_ARCHIVO},
    {-1,                    error_seleccion,    -1,             E_DESICION_ARCHIVO},

    {MODIFICACION,      seis_mod,               0,              -1},
    {-1,                error_modificacion,     -1,             E_MODIFICAR_ARCHIVO},
    
    {NOMBRE_NUEVO_ARCHIVO, creacion_archivo,        -1,             E_AGREGAR_ESTACION},
    {-1,                    error_creacion,        -1,            E_CREAR_ARCHIVO},

    {NOMBRE_ARCHIVO,    existe_archivo,             0,               -1},
    {-1,                error_lectura,              -1,              E_DESICION_ARCHIVO},

    {NOMBRE_ESTACION,   seis_veces,                 0,              -1},
    {-1,                error_agregar               -1,             E_AGREGAR_ESTACION},

    {APAGAR,            despedida,                  -1,             E_INICIO},
    {ESTACION1,         mostrar_estacion1,          -1,              E_MENU},
    {ESTACION1,         mostrar_estacion1,          -1,              E_MENU},
    {ESTACION2,         mostrar_estacion2,          -1,              E_MENU},
    {ESTACION3,         mostrar_estacion3,          -1,              E_MENU},
    {ESTACION4,         mostrar_estacion4,          -1,              E_MENU},
    {ESTACION5,         mostrar_estacion5,          -1,              E_MENU},
    {ESTACION6,         mostrar_estacion6,          -1,              E_MENU},
    {CD,                mostrar_cd,                  -1,             E_MENU},
    {-1,                error_menu,                 -1,             E_MENU}

};

/*************** TABLA AUXILIAR ***************/  
    AUX_TAB aux_table[]={        
/*  accion       bandera     sigEdo */
    {menu_archivos,  -1,   E_DESICION_ARCHIVO},
    {tres_veces, 0, -1},
    {error_clave, -1, E_CLAVE},
    {bloquear_radio, -1, E_INICIO},
    {mostrar_opciones, -1, E_MENU},
    {error_modificar_archivo, -1, E_MODIFICAR_ARCHIVO},
    {error_lectura      -1,  E_DESICION_ARCHIVO},
    {error_seis_veces, -1, E_AGREGAR_ESTACION},
    {num_estaciones, 0, -1},
    {error_num_estaciones, -1, E_DESICION_ARCHIVO},
    {error_existe_archivo, -1, E_DESICION_ARCHIVO}
    

};

/*************** TABLA DE ESTADOS ***************/  
STATE_TAB state_table[]={
   /*estado      inicio        fin */
    {E_INICIO,              0,          1},
    {E_CLAVE,               2,          3},
    {E_DESICION_ARCHIVO,    4,          7},
    {E_MODIFICAR_ARCHIVO,   8,          9},
    {E_CREAR_ARCHIVO,       10,         11},
    {E_LEER_ARCHIVO,        12,         13},
    {E_AGREGAR_ESTACION,    14,         15},
    {E_MENU,                16,         24}

};


    
        
    
        
    
        
    
        
    
        
    
        
    
        
    
        
    
        
    
        
    
    
        
