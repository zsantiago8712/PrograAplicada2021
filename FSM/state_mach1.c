/****************************************************************
 *								*
 * Archivo:	state_mach1.c					*
 * Descripcion: Codigo Fuente para implementar el programa	*
 *		de maquina de estados.			 	*
 *								*
 ****************************************************************/

/*************** ARCHIVOS DE INCLUSION ***************/ 
#include "tables.h"


/*************** PROTOTIPOS DE FUNCION ***************/ 
void initialise(void *datos);
void getevent(void *datos);

int pideNIP(void *datos);
int error(void *datos);
int correcto(void *datos);
int errorNIP(void *datos);
int despedida(void *datos);
int daDinero(void *datos);
int despliegaSaldo(void *datos);
int errorMenu(void *datos);
int opciones(void *datos);
int bienvenida(void *datos);
/*************** FUNCION PRINCIPAL ***************/ 
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
    bienvenida(datos);//Mensaje de inicio
}


void getevent(void *datos)
{
    EVENT *event = (EVENT *) datos;
    char *ptmp;
    char buf[BUFFER];

    //strcpy(buf, event->buf); Aquí estaba esta linea en el original 
    //ptmp = &buf[2];
    
#ifdef DEBUG 1
    printf("wait event \n");
#endif
    gets(event->buf);
    //scanf("%s", event -> buf);
    strcpy(buf, event->buf); //Aquí es donde deberían ir
    ptmp = &buf[2];
    
    //scanf("%[^\n]s",event->buf);
         switch (event->buf[0])
             {
                case 'T':
                    event->etype = TARJETA;
                    break;
                case 'N': //Entradas que requieren información adicional 
                    event->etype = NIP;
                    strcpy(event->args,ptmp);
                    break;
                case 'S':
                    event->etype = SALIR;
                    break;
                case 'R':
                    event->etype = RETIRAR;
                    strcpy(event->args,ptmp);
                    break;
                case 'C':
                    event->etype = CONSULTAR;
                    break;
                default:
                    event->etype = -1; //Entradas cualquier otra cosa
                    break;
		#ifdef DEBUG
    			printf("---> %s \n",event->args);
		#endif

                     
             }//switch
}// getevent
 

/* FUNCIONES DE IMPLEMENTACION */

int bienvenida(void *datos){

    EVENT *event = (EVENT *) datos;
    event -> intentos = 0;
    printf("Bienvenido al cajero. Ingrese su tarjeta: [T]\n");
}//bienvenida

int pideNIP(void *datos)
{
	printf("Ingresa tu NIP: [N:****]:\n");
}//pideNIP

int error(void *datos)
{
	printf("Error. Entrada no válida, vuelva a intentar\n");
}//error

int correcto(void *datos)
{
    EVENT *event = (EVENT *) datos;         //Primero tenemos que hacer cast para poder usar variable
	if(strcmp("1234",event->args) == 0){    //Si es correcto
        return 0;                           //Renglón en el que está la siguiente función en la tabla auxiliar
    }
    else{
        return 1; //Renglón en el que está la función error en la tabla auxiliar
    }
}//correcto

int errorNIP(void *datos)
{
	printf("El NIP es incorrecto. Favor de intentar nuevamente\n");

    pideNIP(datos); //Se manda a llamar aquí directamente la siguiente función después de función
}//errorNIP

int despedida(void *datos)
{
	printf("Gracias por usar el cajero, que tenga buen día\n");
    printf("No olvide retirar su tarjeta\n");
}//despedida

int daDinero(void *datos)
{
	printf("Retire la cantidad solicitada\n");
    opciones(datos);
}//daDinero

int despliegaSaldo(void *datos)
{
	printf("Su saldo es de: 500\n");
    opciones(datos);
}//despliegaSaldo

int errorMenu(void *datos)
{
	printf("Opción no válida. Vuelva a intentar\n");
    opciones(datos);
}//errorMenu

int opciones(void *datos)
{
	printf("Seleccione la opción deseada:\n");
    printf("Retiro de efectivo: [R:monto]\n");
    printf("Consulta de saldo: C\n");
    printf("Salir S\n");
    printf("¿Cuál es su opción: ");
}//opciones

int tresVeces(void *datos)
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




int retenTarj(void *datos)
{
    
    printf("Su tarjeta fue retenida\n");
}