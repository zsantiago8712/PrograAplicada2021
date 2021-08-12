#include "local.h"

//* INICIO --> FUNCIONES GENERALES
extern gboolean delete_event_handler(GtkWidget *widget, gpointer userData);
extern void salir(GtkWidget *widget, gpointer userData);
//* FIN --> FUNCIONES GENERALES

//* INICIO --> FUNCIONES EXTERNAS
extern void menuPrincipal(void); 
//* FIN --> FUNCIONES EXTERNAS

//* INICIO --> FUNCIONES INTERNAS
void pantallaDeCarga(int window_num);
void inc_progress(gpointer data, GtkWidget *window, int window_num);
gint wait(gpointer data);
//* FIN --> FUNCIONES INTERNAS


// INICIO - MAIN DEL PROGRAMA
gint main(gint argc, gchar *argv[])
{
    gtk_init(&argc, &argv);

    pantallaDeCarga(0);

    gtk_main();

    return 0;
}
// FIN MAIN


//! INICIO - PANTALLA DE CARGA INICIAL
    //* Crea la ventana de pantalla de carga
void pantallaDeCarga(int window_num)
{
    GtkWidget *window, *progressBar, *cajaV, *image;
    WIDGETS *elementos;
    
    char *images[] = {"images/3.jpg", "images/6.jpg"};
    elementos = malloc(sizeof(WIDGETS));
    srand(time(NULL));
    


    //2.- Crear widgets
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    cajaV = gtk_vbox_new(FALSE, 5);
    image = gtk_image_new_from_file(images[rand() %2]);
    progressBar = gtk_progress_bar_new();

    elementos->nextWindow = TRUE;

    //2-1.- Fijar atributos
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);
    gtk_window_set_title(GTK_WINDOW(window), "Batalla Naval");
    gtk_progress_bar_set_text(GTK_PROGRESS_BAR(progressBar), "Cargando...");
   
    
    //3.- Registrar las llamadas de las funciones
    g_signal_connect(G_OBJECT(window), "delete_event", G_CALLBACK(delete_event_handler), elementos);
    g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(salir), elementos);
    //g_timeout_add(500, inc_progress, progressBar); // 30
    

    //4.- Definir la jerarquia del programa
    gtk_box_pack_start(GTK_BOX(cajaV), image, TRUE, TRUE, 5);
    gtk_box_pack_start(GTK_BOX(cajaV), progressBar, TRUE, FALSE, 0);
    gtk_container_add(GTK_CONTAINER(window), cajaV);

    //5.- Mostrar los widgets
    gtk_widget_show_all(window);
    inc_progress(progressBar, window, window_num);
}
//! FIN - PANTALLA DE CARGA INICIAL




//* INICIO - FUNCIONES PANTALLA DE CARGA INICIAL


    //Funcion para hacer un update de la pantalla de carga
void inc_progress(gpointer data, GtkWidget *window, int window_num)
{
    gint id;
    static float percent = 0.0;
    while(percent <= 1)
    {
        id = g_timeout_add(1000, wait, NULL);
        gtk_main();
        gtk_timeout_remove(id);
        percent += .25;
        if(percent >= 1.0)
        {
            gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(data), 1);
            gtk_progress_bar_set_text(GTK_PROGRESS_BAR(data), "Completado.... \%100");
        }else
        {
            gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(data), percent);
            char text_perc[sizeof(gint) *4 + 1];
            char text[] = "Cargando..... \%";
            sprintf(text_perc, "%.0f", percent * 100);
            strcat(text, text_perc);
            gtk_progress_bar_set_text(GTK_PROGRESS_BAR(data), text); 
        }
               
    }
    gtk_widget_destroy(window);
    menuPrincipal();
     
}

    //Funcion para simular un sleep
gint wait(gpointer data)
{
    gtk_main_quit();
    return 1;
}
//* FIN - FUNCIONES PANTALLA DE CARGA INICIAL
