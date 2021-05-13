#include "local.h"

//* INICIO --> FUNCIONES GENERALES
extern void menuPrincipal(void);
//* FIN --> FUNCIONES GENERALES


//* INICIO --> FUNCIONES INTERNAS
void goBack(GtkButton *boton, gpointer userData);
//* FIN --> FUNCIONES INTERNAS


//* Ventan de marcadores
void marcadores(void)
{
    
    GtkWidget *ventana, *marcador[5][3], *cajaH, *cajaV, *etiqueta, *boton, *cajaH2, *tablaM, *cajaH3;
    WIDGETS *elementos;
    FILE *fp;
    char nombre[10];
    char tiempo[10];
    char *posicionToChar;
    char datos[20];
    int posicion = 1;
    
    elementos = malloc(sizeof(WIDGETS));
    elementos->nextWindow = TRUE;
   

    ventana = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    etiqueta = gtk_label_new("MARCADORES");
    boton = gtk_button_new_from_stock(GTK_STOCK_QUIT);
    tablaM = gtk_table_new(6, 3, TRUE);
    cajaV = gtk_vbox_new(FALSE, 5);
    cajaH = gtk_vbox_new(FALSE, 5);
    cajaH2 = gtk_hbox_new(FALSE, 5);
    cajaH3 = gtk_vbox_new(FALSE, 5);

    marcador[0][0] = gtk_label_new("POSICION");
    marcador[0][1] = gtk_label_new("NOMBRE");
    marcador[0][2] = gtk_label_new("TIEMPO"); 

    elementos->ventana = ventana;
    
    fp = fopen("scores.txt", "r");
    while(fgets(datos, 20, fp) != NULL)
    {
        if(posicion == 6)
        {
            break;
        }
        sscanf(datos, "%s %s", nombre, tiempo);
        sprintf(posicionToChar, "%d", posicion);
        g_print("P.- %d\n", posicion);
        g_print("%s --> %s\n", nombre, tiempo);
        if(posicion < 5)
        {
            marcador[posicion][0]= gtk_label_new(posicionToChar);
            marcador[posicion][1] = gtk_label_new(nombre);
            marcador[posicion][2] = gtk_label_new(tiempo); 
        }
       
        posicion++;
    }
    fclose(fp);
    
    strcpy(datos, tiempo);
    strcpy(tiempo, nombre);

    marcador[5][0]= gtk_label_new("5");
    marcador[5][1] = gtk_label_new(tiempo);
    marcador[5][2] = gtk_label_new(datos); 
   

    gtk_window_set_title(GTK_WINDOW(ventana), "MARCADORES");
    gtk_window_set_default_size(GTK_WINDOW(ventana), 430, 350);

    g_signal_connect(G_OBJECT(boton), "clicked", G_CALLBACK(goBack), elementos);

    for(int i = 0; i < 6; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            gtk_table_attach_defaults(GTK_TABLE(tablaM), marcador[i][j], j, j + 1, i, i + 1);
        }
    }
    
    

    gtk_box_pack_start(GTK_BOX(cajaH), etiqueta, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(cajaV), cajaH, FALSE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(cajaH2), tablaM, TRUE, TRUE, 2);
    gtk_box_pack_start(GTK_BOX(cajaV), cajaH2, TRUE, TRUE, 2);
    gtk_box_pack_start(GTK_BOX(cajaH3), boton, FALSE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(cajaV), cajaH3, FALSE, TRUE, 0);
    gtk_container_add(GTK_CONTAINER(ventana), cajaV);

    gtk_widget_show_all(ventana);
}

//* Funcion que regresa al menu principal
void goBack(GtkButton *boton, gpointer userData)
{
    WIDGETS *elementos = (WIDGETS *)userData;
    elementos->numVentan = 1;
    gtk_widget_destroy(elementos->ventana);
    menuPrincipal();
}