#include<gtk/gtk.h>

void botonClic(GtkButton *button, gpointer user_data);
gboolean delete_event_handler(GtkWidget *widget, GdkEvent *event, gpointer user_data);
void salir(GtkWidget *widget, gpointer user_data);

gint main(gint argc, gchar *argv[])
{
    //Declaración de variables.
    GtkWidget *ventana, *cajaVertical, *cajaHorizontal1, *cajaHorizontal2, *cajaHorizontal3, *etiqueta1, *etiqueta2, *separador,*boton1, *boton2, *entrada1, *entrada2;

    //1. Inicializar el ambiente.
    gtk_init(&argc, &argv);

    //2.1 Crear widgets.
    ventana = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    cajaVertical = gtk_vbox_new(TRUE, 5);
    cajaHorizontal1 = gtk_hbox_new(TRUE, 5);
    cajaHorizontal2 = gtk_hbox_new(TRUE, 5);
    cajaHorizontal3 = gtk_hbox_new(TRUE, 5);
    etiqueta1 = gtk_label_new("Usuario:");
    etiqueta2 = gtk_label_new("Contraseña:");
    entrada1 = gtk_entry_new();
    entrada2 = gtk_entry_new();
    gtk_entry_set_visibility(GTK_ENTRY(entrada2), FALSE);
    separador = gtk_hseparator_new();
    boton1 = gtk_button_new_with_mnemonic("_Ok"); //Se subraya la O
    boton2 = gtk_button_new_with_mnemonic("_Cancelar");


    //2.2 Fijar atributos.
    gtk_window_set_title(GTK_WINDOW(ventana), "GTK is fun!"); //GTK_WINDOW(ventana) es un cast.

    //3. Registrar las llamadas a las funciones.
    g_signal_connect(G_OBJECT(boton1), "clicked", G_CALLBACK(botonClic), NULL);
    g_signal_connect(G_OBJECT(boton2), "clicked", G_CALLBACK(botonClic), NULL);
    g_signal_connect(G_OBJECT(ventana), "delete_event", G_CALLBACK(delete_event_handler), NULL);
    g_signal_connect(G_OBJECT(ventana), "destroy", G_CALLBACK(salir), NULL);

    //4. Definir jerarquía del programa.
        //Etiqueta, separador y boton en caja vertical. De arriba hacia abajo.
    gtk_box_pack_start_defaults(GTK_BOX(cajaHorizontal1), etiqueta1);
    gtk_box_pack_start_defaults(GTK_BOX(cajaHorizontal1), entrada1);
    gtk_box_pack_start_defaults(GTK_BOX(cajaVertical), cajaHorizontal1);
    gtk_box_pack_start_defaults(GTK_BOX(cajaHorizontal2), etiqueta2);
    gtk_box_pack_start_defaults(GTK_BOX(cajaHorizontal2), entrada2);
    gtk_box_pack_start_defaults(GTK_BOX(cajaVertical), cajaHorizontal2);
    gtk_box_pack_start_defaults(GTK_BOX(cajaVertical), separador);
    gtk_box_pack_start_defaults(GTK_BOX(cajaHorizontal3), boton1);
    gtk_box_pack_start_defaults(GTK_BOX(cajaHorizontal3), boton2);
    gtk_box_pack_start_defaults(GTK_BOX(cajaVertical), cajaHorizontal3);

    gtk_container_add(GTK_CONTAINER(ventana), cajaVertical);


    //De abajo hacia arriba.
    /*  
        gtk_box_pack_end_defaults(GTK_BOX(cajaVertical), etiqueta);
        gtk_box_pack_end_defaults(GTK_BOX(cajaVertical), separador);
        gtk_box_pack_end_defaults(GTK_BOX(cajaVertical), boton);
    */

    //5. Mostrar los widgets.
    gtk_widget_show_all(ventana);

    //6. Procesar señales y eventos.
    gtk_main();

    //7. Salir de la aplicación.
    return 0;
}

void botonClic(GtkButton *button, gpointer user_data)
{
    g_print("Click en el boton.\n");
    gtk_main_quit(); //Unicamente para salir del programa.
}

//Es necesario para poder usar el boton de la ventana de cerrar 
gboolean delete_event_handler(GtkWidget *widget, GdkEvent *event, gpointer user_data)
{
    g_print("En delete_event_handler.\n"); 
    return FALSE;   //Para usar el boton de la ventana siempre tiene que estar en false
}

void salir(GtkWidget *widget, gpointer user_data)
{
    g_print("Click YES.\n"); 
    gtk_main_quit();
}
