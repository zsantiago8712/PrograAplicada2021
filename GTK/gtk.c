#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>



//! Documentación de GTK --> https://developer.gnome.org/gtk3/stable/


gint main(gint argc, gchar *argv[])
{

    //Declaracion de variables
    GtkWidget *window, *cajaVertical, *etiqueta, *separador, *boton;

    // 1.- Inicializar ambiente
    gtk_init(&argc, &argv);


    //2.- Crear widgets
    window = gtk_window_new( GTK_WINDOW_TOPLEVEL);         //Crear Ventana -> pude recibir tambien ventana tipo GTK_WINDOW_POPUP
    cajaVertical = gtk_vbox_new(TRUE, 5);                //Crear caja vertical -> BOoleano y pixeles de separacion
    etiqueta = gtk_label_new("Hola, Mundo");
    separador = gtk_hseparator_new();
    //boton = gtk_button_new_with_label("OK");
    boton = gtk_button_new_from_stock(GTK_STOCK_APPLY);
    //! Para crear diferentes tipos de botones
    //! gkt_button_new()
    //! gtk_button_new_with_mnemonic("_OK") -> el '_' hace que aparezca subrayada



    //2-1.- Fijar atributos
    gtk_window_set_title(GTK_WINDOW(window), "GTK is fun!");
    

    //3.- Registrar las llamadas de las funciones



    //4.- Definir la jerarquia del programa
    gtk_box_pack_start_defaults(GTK_BOX(cajaVertical), etiqueta);
    gtk_box_pack_start_defaults(GTK_BOX(cajaVertical), separador);
    gtk_box_pack_start_defaults(GTK_BOX(cajaVertical), boton);
    gtk_container_add(GTK_CONTAINER(window), cajaVertical);


    //5.- Mostrar los widgets
    gtk_widget_show_all(window);



    //6.- Procesar señales
    gtk_main();



    //7.- Salir de la aplicaciones
    
    return 0;
}