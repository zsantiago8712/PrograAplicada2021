/*****************************************************
 *Parte 1 - Examen 1
 *Sebastián Sedano, Santiago Zamora, Mauricio Olguín
 *Programación Aplicada
 ****************************************************/
#include "local.h"

extern void agregar_cancion(LISTA **inicio, LISTA **aux);
extern void reproducir_cancion(LISTA *inicio);
extern void ver_lista(LISTA *inicio);
extern void escribir_lista_archivo(LISTA *inicio);
extern void liberar_memoria(LISTA *inicio);

int main(void){
    LISTA *inicio, *aux;
    int opcion; //Variable opcion representa la opción selecionada
    inicio = NULL;
    while(1){
        system("clear");
        printf("Opciones:\n 1.Agregar una canción\n 2. Reproducir canción\n 3. Ver lista de reproducción\n 4.Guardar lista de reproducción\n 5. Salir\n");
        printf("Seleccione una opción: ");
        
        scanf("%d",&opcion);
        if(opcion==1){
            agregar_cancion(&inicio,&aux);
        }else if(opcion==2){
            reproducir_cancion(inicio);

        }else if(opcion==3){
            ver_lista(inicio);

        }else if(opcion==4){
            
            escribir_lista_archivo(inicio);

        }else if(opcion==5){
            liberar_memoria(inicio);
        }else{
            printf("Ingrese una opción válida\n");
        }
                   
    }
    
}