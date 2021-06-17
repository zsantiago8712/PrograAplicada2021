#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

 

typedef struct datos{
    gchar nombre[20];
    gint numero;
}DATOS;

 

gint main(gint argc, gchar **argv)
{
    GSList *lista = NULL;
    DATOS *persona;
    gchar salida;
    gint i;
    gpointer info;
    
    do{
        persona = malloc(sizeof(DATOS)); // 1.- Crear espacio
        g_print("Nombre: ");                // 2.- Llenar informaci—n
        scanf("%[^\n]s", persona->nombre);
        g_print("Numero: ");
        scanf("%d",&persona->numero);
        getchar();
        
        lista = g_slist_append(lista,persona); // 3.- Encadenar
    
        g_print("Desea seguir metiendo datos: ([s]/n) ");
        salida = getchar();
        
        getchar();
        
    }while (salida != 'n');
    
    printf("La longitud es: %d\n",g_slist_length(lista));
    
    g_print("Los datos son: \n");
    
    for(i = 0; i < g_slist_length(lista); i++){
        info = g_slist_nth_data(lista,i);
        persona = (DATOS *)info;

 

        g_print("Nombre: %s\n",persona->nombre);
        g_print("Numero: %d\n",persona->numero);
    }// for    
    
    g_slist_free(lista);
    
    return 0;
}// main