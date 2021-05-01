#include "local.h"



//* INICIO --> FUNCIONES GENERALES
extern gboolean delete_event_handler(GtkWidget *widget, gpointer userData);
extern void salir(GtkWidget *widget, gpointer userData);
extern void escogerNombresJugadores(WIDGETS *elementos);
extern void saveNames(GtkButton *boton, gpointer userData);
extern void cancelWindowName(GtkButton *boton, gpointer userData);
//* FIN --> FUNCIONES GENERALES

//* INICIO --> FUNCIONES EXTERNAS
extern void jugador1VsJugador2(char *nombreJ1, char *nombreJ2);
//* FIN --> FUNCIONES EXTERNAS


//* INICIO --> FUNCIONES INTERNAS
void clickJugar(GtkButton *boton, gpointer userData);
void botonClick(GtkButton *boton, gpointer userData);
//* FIN --> FUNCIONES INTERNAS





// * INICIA ---> Ventana - Menu principal
void menuPrincipal(void)
{
    GtkWidget *window, *progressBar, *cajaV, *etiqueta, *botonJugar, *botonMarcadores, *botonSalir, 
            *botonJugarVsCpu, *botonJugar2, *menu, *item, *separador, *cajaH, *cajaV2, *cajaV3, *image;
    

    WIDGETS *elementos; 
    elementos = malloc(sizeof(WIDGETS));

   
    //2.- Crear widgets
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    cajaV = gtk_hbox_new(FALSE, 5);
    cajaV2 = gtk_vbox_new(FALSE, 5);
    cajaV3 = gtk_vbutton_box_new();
    cajaH = gtk_vbox_new(FALSE, 5); 
    etiqueta = gtk_label_new("Batalla Naval");
    botonJugar = gtk_button_new_with_label("Jugar");
    botonSalir = gtk_button_new_with_label("Salir");
    botonMarcadores = gtk_button_new_with_label("Marcadores");
    botonJugarVsCpu = gtk_button_new_with_label("vs. CPU");
    botonJugar2 = gtk_button_new_with_label("2 Jugadores");
    image = gtk_image_new_from_file("/home/ic20szs/PrograAplicada2021/P-F/4.jpg");

    elementos->botones[0] = botonJugarVsCpu;
    elementos->botones[1] = botonJugar2;
    elementos->ventana = window;
    elementos->nextWindow = FALSE;
    

    // 2-1.- Fijar atributos
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 300);
    gtk_window_set_title(GTK_WINDOW(window), "Batalla Naval");
    

    // 3.- Registrar las llamadas de las funciones
    g_signal_connect(G_OBJECT(window), "delete_event", G_CALLBACK(delete_event_handler), NULL);
    g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(salir), elementos);
    g_signal_connect(G_OBJECT(botonJugar), "clicked", G_CALLBACK(botonClick), elementos);
    g_signal_connect(G_OBJECT(botonSalir), "clicked", G_CALLBACK(salir), NULL);
    // TODO  CREAR EL MODO VS CPU g_signal_connect(G_OBJECT(botonJugarVsCpu), "clicked", G_CALLBACK(clickJugar), elementos);
    g_signal_connect(G_OBJECT(botonJugar2), "clicked", G_CALLBACK(clickJugar), elementos);



    // 4.- Definir la jerarquia del programa
    gtk_box_pack_start(GTK_BOX(cajaV2), image, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(cajaV), cajaV2, TRUE, TRUE, 0);
    //-----------------------------------------------------------
    gtk_box_pack_start(GTK_BOX(cajaH), botonJugar, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(cajaH), botonJugarVsCpu, FALSE, FALSE,0);
    gtk_box_pack_start(GTK_BOX(cajaH), botonJugar2, FALSE, FALSE, 5);
    //-----------------------------------------------------------
    gtk_box_pack_start(GTK_BOX(cajaH), botonMarcadores, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(cajaH), botonSalir, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(cajaV), cajaH, FALSE, FALSE, 5); 
    //-----------------------------------------------------------
    gtk_container_add(GTK_CONTAINER(window), cajaV);

   

    //5.- Mostrar los widgets
    gtk_widget_show_all(window);
    gtk_widget_hide_all(botonJugarVsCpu);
    gtk_widget_hide_all(botonJugar2);
}
// * FIN --> Ventana - Menu principal 






// *INICIO ---> Funciones Venta - Menu Principal

// TODO cambiar a 2JUGADORES ESTA EN VSCPU *Funciona que se activa al presionar el boton 2JUGADORES QUE ES LA MODALIDAD DOS JUGADORES
void clickJugar(GtkButton *boton, gpointer userData)
{
    WIDGETS *elementos = (WIDGETS *)userData;
    g_print("sia");
    escogerNombresJugadores(elementos);
    //jugador1VsJugador2();
    
    
}
//TODO

void botonClick(GtkButton *boton, gpointer userData)
{
    static gboolean is_show= FALSE;
    WIDGETS *elementos = (WIDGETS *)userData;
    if(!is_show)
    {
        for(int i = 0; i < 2; i++)
        {
            gtk_widget_show_all(elementos->botones[i]);
        }
        is_show = TRUE;
    }else
    {
        for(int i = 0; i < 2; i++)
        {
            gtk_widget_hide_all(elementos->botones[i]);
        }
        is_show = FALSE;
    }
}

// *FIN ---> Funciones Venta - Menu Principal