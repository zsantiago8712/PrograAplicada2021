#include <stdio.h>
#include <stdlib.h>
#include<strings.h>
#include<string.h>
#include <gtk/gtk.h>

typedef struct widgets
{
    GtkWidget *entrada;
    gchar *texto;
    gchar *primerNum;
    gchar *segundoNum;
    gfloat resultado;
    gchar *sint;
}WIDGETS;

gboolean delete_event_handler(GtkWidget *widget, GdkEvent *event, gpointer user_data);
void salir(GtkWidget *widget, gpointer user_data);
void clickBoton(GtkWidget *boton, gpointer used_data);
void ventanaAcercaDe(void);


gint main(gint argc, gchar *argv[])
{
    //declarar variables
    GtkWidget *ventana, *cajaVertical, *tabla, *cajaHorizontal1, *cajaHorizontal2, *boton[17], *separador;
    GtkWidget *menuBar, *fileItem, *fileMenu, *quitItem, *ayudaItem, *acercaDe, *ayudaMenu, *menubarAyuda;
    gchar *etiquetas[17] = {"clear", "/", "*", "-", "7", "8", "9", "+", "4", "5", "6", "1", "2", "3", "Intro", "0", "."};
    WIDGETS *elementos;
    
    //elementos -> resultado = '';

    //1. Inicializar el ambiente.
    gtk_init(&argc, &argv); //Siempre se inicializa antes que nada.
    elementos = malloc(sizeof(WIDGETS));
    

    //2.1 Crear widgets.
    ventana = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    cajaVertical = gtk_vbox_new(FALSE, 5);
    tabla = gtk_table_new(5, 4, TRUE); 
    elementos->entrada = gtk_entry_new();
    for(int i=0; i < 17; i++)
    {
        boton[i] = gtk_button_new_with_label(etiquetas[i]);
    }
    
    separador = gtk_hseparator_new();

    //Menu
    menuBar = gtk_menu_bar_new();
    fileItem = gtk_menu_item_new_with_label("Archivo");
    fileMenu = gtk_menu_new();
    quitItem = gtk_menu_item_new_with_label("Salir");
    ayudaItem = gtk_menu_item_new_with_label("Ayuda");
    ayudaMenu = gtk_menu_new(); 
    acercaDe = gtk_menu_item_new_with_label("Acerca de");

    //2.2 Fijar atributos.
    gtk_window_set_title(GTK_WINDOW(ventana), "GTK calculadora"); //GTK_WINDOW(ventana) es un cast.
    for(int i=0; i < 17; i++)
    {
        gtk_widget_set_name(boton[i], etiquetas[i]);
    }
    gtk_menu_item_right_justify(ayudaItem);
    
    //3. Registrar las llamadas a las funciones.
    g_signal_connect(G_OBJECT(ventana), "delete_event", G_CALLBACK(delete_event_handler), NULL);
    g_signal_connect(G_OBJECT(ventana), "destroy", G_CALLBACK(salir), NULL);
    g_signal_connect(G_OBJECT(quitItem), "activate", G_CALLBACK(salir), NULL);
    g_signal_connect(G_OBJECT(acercaDe), "activate", G_CALLBACK(ventanaAcercaDe), NULL);
    for(int i=0; i < 17; i++)
    {
        g_signal_connect(G_OBJECT(boton[i]), "clicked", G_CALLBACK(clickBoton), elementos);
    }

    //4. Definir jerarquía del programa.

    //Menu
    gtk_menu_shell_append(GTK_MENU_SHELL(fileMenu), quitItem);
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(fileItem), fileMenu);
    gtk_menu_bar_append(GTK_MENU_BAR(menuBar), fileItem);
    gtk_menu_shell_append(GTK_MENU_SHELL(ayudaMenu), acercaDe);
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(ayudaItem), ayudaMenu);
    gtk_menu_bar_append(GTK_MENU_BAR(menuBar), ayudaItem);


    gtk_box_pack_start(GTK_BOX(cajaVertical), menuBar, TRUE, TRUE, 5);
    gtk_box_pack_start(GTK_BOX(cajaVertical), elementos->entrada, TRUE, TRUE, 5);
    gtk_box_pack_start(GTK_BOX(cajaVertical), separador, TRUE, TRUE, 5);
    

    //Botones
    gtk_table_attach_defaults(GTK_TABLE(tabla), boton[0], 0, 1, 0, 1);
    gtk_table_attach_defaults(GTK_TABLE(tabla), boton[1], 1, 2, 0, 1);
    gtk_table_attach_defaults(GTK_TABLE(tabla), boton[2], 2, 3, 0, 1);
    gtk_table_attach_defaults(GTK_TABLE(tabla), boton[3], 3, 4, 0, 1);
    gtk_table_attach_defaults(GTK_TABLE(tabla), boton[4], 0, 1, 1, 2);
    gtk_table_attach_defaults(GTK_TABLE(tabla), boton[5], 1, 2, 1, 2);
    gtk_table_attach_defaults(GTK_TABLE(tabla), boton[6], 2, 3, 1, 2);
    gtk_table_attach_defaults(GTK_TABLE(tabla), boton[7], 3, 4, 1, 3);
    gtk_table_attach_defaults(GTK_TABLE(tabla), boton[8], 0, 1, 2, 3);
    gtk_table_attach_defaults(GTK_TABLE(tabla), boton[9], 1, 2, 2, 3);
    gtk_table_attach_defaults(GTK_TABLE(tabla), boton[10], 2, 3, 2, 3);
    gtk_table_attach_defaults(GTK_TABLE(tabla), boton[11], 0, 1, 3, 4);
    gtk_table_attach_defaults(GTK_TABLE(tabla), boton[12], 1, 2, 3, 4);
    gtk_table_attach_defaults(GTK_TABLE(tabla), boton[13], 2, 3, 3, 4);
    gtk_table_attach_defaults(GTK_TABLE(tabla), boton[14], 3, 4, 3, 5);
    gtk_table_attach_defaults(GTK_TABLE(tabla), boton[15], 0, 2, 4, 5);
    gtk_table_attach_defaults(GTK_TABLE(tabla), boton[16], 2, 3, 4, 5);
    gtk_box_pack_start(GTK_BOX(cajaVertical), tabla, TRUE, TRUE, 5);
    gtk_container_add(GTK_CONTAINER(ventana), cajaVertical);

    //5. Mostrar los widgets.
    gtk_widget_show_all(ventana);

    elementos -> texto = "?";
    elementos -> primerNum = "?";
    elementos -> segundoNum = "?";
    elementos -> sint = "?";
    elementos -> resultado = -1;
    g_print("HHH%s\n", elementos->texto);
    //6. Procesar señales y eventos.
    gtk_main();
   
    //7. Salir de la aplicación.
    return 0;
}

void ventanaAcercaDe(void)
{
    g_print("entro");
    GtkWidget *window2;
    static const char *author[] = {"Santiago Zamora Solís"};
    window2 = gtk_about_dialog_new() ;
    
    gtk_about_dialog_set_name(GTK_ABOUT_DIALOG(window2), "Calculadora");
    gtk_about_dialog_set_comments(GTK_ABOUT_DIALOG(window2), "Version 1.8");
    gtk_about_dialog_set_authors(GTK_ABOUT_DIALOG(window2), author);
    gtk_about_dialog_set_copyright(GTK_ABOUT_DIALOG(window2), "Copyright");


    g_signal_connect_swapped(G_OBJECT(window2), "response", G_CALLBACK(gtk_widget_destroy), window2);

    gtk_widget_show_all(window2);
    gtk_window_set_modal(GTK_WINDOW(window2), TRUE);
}

gboolean delete_event_handler(GtkWidget *widget, GdkEvent *event, gpointer user_data)
{
    g_print("En delete_event_handler.\n");
    return FALSE;
}

void salir(GtkWidget *widget, gpointer user_data)
{
    gtk_main_quit();
}

void clickBoton(GtkWidget *boton, gpointer user_data)
{
    WIDGETS *elementos = (WIDGETS *)user_data;
    int res = 0;
    gchar *nombre = gtk_widget_get_name(boton);
    char *a = strdup(nombre);
    if(strcmp(nombre, "+") == 0 || strcmp(nombre, "-") == 0 || strcmp(nombre, "/") == 0 || strcmp(nombre, "*") == 0)
    {
        elementos -> sint = strdup(nombre);
    }else if(strcmp(nombre, "Intro") == 0)
    {

        res = 1;
        gfloat primerN = atof(elementos->primerNum);
        gfloat segundoN = atof(elementos->segundoNum);
        g_print("P._ %f\n", primerN);
        g_print("A.- %f\n", segundoN);
        if(strcmp(elementos->sint, "+") == 0)
        {
            elementos->resultado = primerN + segundoN; 
        }else if(strcmp(elementos->sint, "-") == 0)
        {
            elementos->resultado = primerN - segundoN;
        }else if(strcmp(elementos->sint, "/") == 0)
        {
            elementos->resultado = primerN / segundoN;
        }else if(strcmp(elementos->sint, "*") == 0)
        {
            elementos->resultado = primerN * segundoN;
        }
        
    }else if(strcmp(nombre, "clear") == 0)
    {
        res = -1;
        elementos->texto = strdup(nombre);
        gtk_entry_set_text((GTK_ENTRY(elementos->entrada)), "");
        gchar *clear = "?";
        elementos->texto = strdup(clear);
        elementos->primerNum = strdup(clear);
        elementos->segundoNum = strdup(clear);
        elementos->sint = strdup(clear);
    }else
    {
        if(strcmp(elementos->primerNum, "?") == 0)
        {
            elementos->primerNum = strdup(nombre);
        }else if(strcmp(elementos->sint, "?") == 0)
        {
            strcat(elementos->primerNum, nombre);
        }else if(strcmp(elementos->sint, "?") != 0)
        {
            if(strcmp(elementos->segundoNum, "?") == 0)
            {
                elementos->segundoNum = strdup(nombre);
            }else
            {
                strcat(elementos->segundoNum, nombre);
            }
        }
        g_print("%s", elementos->primerNum);
    }
    if(strcmp(elementos->texto, "?") == 0 && res!=-1)
    {
        elementos->texto = strdup(nombre);
    }else
    {
       if(res == 0)
       {
        strcat(elementos->texto, nombre); 
       }else if(res == 1)
       {
         strcat(elementos->texto, "=");   
       }
    }
    g_print("%s\n%s\n", nombre, elementos->texto);
    /*gtk_entry_set_text((GTK_ENTRY(elementos->entrada)), elementos->texto);*/
    if(res == 0)
    {
        g_print("%s\n%s\n", nombre, elementos->texto);
        gtk_entry_set_text((GTK_ENTRY(elementos->entrada)), elementos->texto);
    }else if(res == 1)
    {
        //strcat(elementos->texto, nombre);
        g_print("%s\n%f\n", nombre, elementos->resultado);
        char text_res[sizeof(gint) *4 + 1];
        sprintf(text_res, "%.2f", elementos->resultado);
        strcat(elementos->texto, text_res);
        gtk_entry_set_text((GTK_ENTRY(elementos->entrada)), elementos->texto);
    }
    
    
}