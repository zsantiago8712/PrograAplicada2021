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




/*************** FUNCIONES EXTERNAS *********************
 * En esta seccion se declaran los encabezados de 	*
 * todas las funciones que se utilizan en las     	*
 * tablas del programa. Todas las funciones deben 	*
 * ser de tipo entero y no deben recibir parametros	*
 ********************************************************/ 
extern int pideNIP(void *datos);
extern int error(void *datos);
extern int correcto(void *datos);
extern int errorNIP(void *datos);
extern int despedida(void *datos);
extern int daDinero(void *datos);
extern int despliegaSaldo(void *datos);
extern int errorMenu(void *datos);
extern int opciones(void *datos);
extern int bienvenida(void *datos);
extern int tresVeces(void *datos);
extern int retenTarj(void *datos);
/******************** TABLAS ********************
 * En esta seccion se declaran las tablas	*
 * que se van a usar en el programa		*
 ************************************************/ 
 
/*************** TABLA DE ACCION ***************/  
ACTION_TAB action_table[]={
    /*etype          accion       bandera           sigEdo. */    
    {TARJETA,       pideNIP,   	    -1,                 E_NIP},
    {-1,            error,	        -1,	                E_INICIO},
    
    {NIP,           correcto,       0,                  -1},
    {-1,           errorNIP,       -1,                 E_NIP},

    {SALIR,         despedida,      -1,                 E_INICIO},
    {RETIRAR,       daDinero,       -1,                 E_MENU},
    {CONSULTAR,     despliegaSaldo, -1,                 E_MENU},
    {-1,            errorMenu,      -1,                 E_MENU}
};

/*************** TABLA AUXILIAR ***************/  
    AUX_TAB aux_table[]={        
/*  accion       bandera     sigEdo */
    {opciones,      -1,        E_MENU},
    {tresVeces,     0,             -1},
    {errorNIP,      -1,          E_NIP},
    {retenTarj,     -1,         E_INICIO}
};

/*************** TABLA DE ESTADOS ***************/  
STATE_TAB state_table[]={
   /*estado      inicio        fin */
    {E_INICIO,      0,          1},
    {E_NIP,         2,          3},
    {E_MENU,         4,          7}
};


    
        
    
        
    
        
    
        
    
        
    
        
    
        
    
        
    
        
    
        
    
    
        
