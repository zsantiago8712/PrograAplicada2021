#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>


gboolean delete_event_handler(GtkWidget *widget, gpointer userData);
void salir(GtkWidget *widget, gpointer userData);
void botonClick(GtkButton *boton, gpointer userData);



gint main(gint argc, gchar *argv[])
{
    //Declaración de variables.
    GtkWidget *ventana, *cajaVertical, *etiqueta, 
              *boton, *boton1, *cajaH, *menu, *fileItem, 
              *fileMenu, *quitItem, *menuBar, *separador;
    

    // 1.- Inicializar ambiente
    gtk_init(&argc, &argv);


    //2.- Crear widgets
    ventana = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    cajaVertical = gtk_vbox_new(TRUE, 5);
    etiqueta = gtk_label_new("Hola mundo!");
    boton = gtk_button_new_with_mnemonic("Ok");
    boton1 = gtk_button_new_with_mnemonic("HOLA");
    cajaH = gtk_hbox_new(TRUE, 5);
    separador = gtk_hseparator_new();
    menuBar = gtk_menu_bar_new();
    fileItem = gtk_menu_item_new_with_label("Archivo");
    fileMenu = gtk_menu_new();
    quitItem = gtk_menu_item_new_with_label("Salir");



    //2-1.- Fijar atributos
    gtk_window_set_title(GTK_WINDOW(ventana), "GTK is fun!");


    //3.- Registrar las llamadas de las funciones
    g_signal_connect(G_OBJECT(ventana), "delete_event", G_CALLBACK(delete_event_handler), NULL);
    g_signal_connect(G_OBJECT(ventana), "destroy", G_CALLBACK(salir), NULL);
    g_signal_connect(G_OBJECT(boton), "clicked", G_CALLBACK(botonClick), NULL);
    g_signal_connect(G_OBJECT(boton), "clicked", G_CALLBACK(botonClick), NULL);
    
    
    //4.- Definir la jerarquia del programa

    //Menu
    gtk_menu_shell_append(GTK_MENU_SHELL(fileMenu), quitItem);
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(fileItem), fileMenu);
    gtk_menu_bar_append(GTK_MENU_BAR(menuBar), fileItem);

    


    gtk_box_pack_start(GTK_BOX(cajaVertical), cajaH, TRUE, TRUE, 5);
    gtk_box_pack_start(GTK_BOX(cajaH), menuBar, TRUE, TRUE, 5);
    gtk_box_pack_start(GTK_BOX(cajaVertical), separador, TRUE, TRUE, 5);
    gtk_box_pack_start(GTK_BOX(cajaVertical), etiqueta, TRUE, TRUE, 5);
    gtk_box_pack_start(GTK_BOX(cajaVertical), boton, TRUE, TRUE, 5);
    gtk_container_add(GTK_CONTAINER(ventana), cajaVertical);


    //5.- Mostrar los widgets
    gtk_widget_show_all(ventana);


    //6.- Procesar señales
    gtk_main();


    //7.- Salir de la aplicaciones



    return 0;

}


//Funciones
void botonClick(GtkButton *boton, gpointer userData)
{
    g_print("Se presiono el botono Ok\n");
}



gboolean delete_event_handler(GtkWidget *widget, gpointer userData)
{
    g_print("En delete_event_handler.\n");
    return FALSE;
    
}

void salir(GtkWidget *widget, gpointer userData)
{
    g_print("Click en salir\n");
    gtk_main_quit();
}