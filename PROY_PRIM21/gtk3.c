#include "local.h"


//* INICIO --> FUNCIONES GENERALES
extern void salir(GtkWidget *widget, gpointer userData);
extern void cancel(GtkButton *boton, gpointer userData);
extern void saveHistory(GtkButton *boton, gpointer userData);
extern gboolean delete_event_handler(GtkWidget *widget, gpointer userData);
extern void createFile(GtkButton *boton, gpointer userData);
extern void fileChooser(GtkButton *boton, gpointer userData);
extern void cambiarNombre(char *nombre);
extern void atras(GtkButton *boton, gpointer userData);
extern void deshacerFunction(GtkButton *boton, gpointer userData);
extern void adelante(GtkButton *boton, gpointer userData);
extern void rehacerFunction(GtkButton *boton, gpointer userData);
extern gboolean show_question(WIDGETS *elementos);
extern void backToMenu(GtkButton *boton, gpointer userData);
extern void barcosPosition(GtkWidget *botones[7][7], GtkWidget *botonesJ2[7][7], WIDGETS *elementos);
extern void ventanaAcercaDe(GtkButton *boton, gpointer userData);
extern void escogerNombresJugadores(WIDGETS *elementos);
extern gint timer(gpointer data);
extern void restart(WIDGETS *elementos);
//* FIN --> FUNCIONES GENERALES


//* INICIO --> FUNCIONES EXTERNAS
extern void menuPrincipal(void);
//* FIN --> FUNCIONES EXTERNAS


//* INICIO --> FUNCIONES INTERNAS
void jugador1VsJugador2(char *nombreJ1, char *nombreJ2);
void clickTablero(GtkButton *boton, gpointer userData);
void crearJuegoNuevo(GtkButton *boton, gpointer userData);
//* FIN --> FUNCIONES INTERNAS




//* INICIO ---> VENTANA TABLERO
void jugador1VsJugador2(char *nombreJ1, char *nombreJ2)
{
    //declarar variables
    GtkWidget *ventana, *cajaVertical, *tabla, *cajaHorizontal1, *cajaHorizontal2, *cajaH3, *botones[7][7], *botonesj2[7][7],*separador, *cajaV, *juegoNuevo, *cajaH6, *eTiempo;
    GtkWidget *menuBar, *fileItem, *fileMenu, *quitItem, *ayudaItem, *acercaDe, *ayudaMenu, *menubarAyuda, *tablero2, *etiquetaJ1, *etiquetaJ2, *cajaH5, *toolBar;
    GtkWidget *botonAtras, *botonAdelante, *cajaH4, *guardar, *deshacer, *rehacer, *guardarEnNuevoArchivo, *recuperar ,*herramientas, *herramientasMenu, *statusBar;
    GtkToolItem *toolNg, *toolSalir, *toolSv;
    GList *listD = NULL;
    GdkColor colorJ1, colorJ2;
    char mensaje[100] = "(Tiros- Barcos Hundidos)|| ";
    WIDGETS *elementos;
    char *name[100][100] =  {  
                                {"0, 0", "0, 1", "0, 2", "0, 3", "0, 4", "0, 5", "0, 6"}, 
                                {"1, 0", "1, 1", "1, 2", "1, 3", "1, 4", "1, 5", "1, 6"},
                                {"2, 0", "2, 1", "2, 2", "2, 3", "2, 4", "2, 5", "2, 6"},
                                {"3, 0", "3, 1", "3, 2", "3, 3", "3, 4", "3, 5", "3, 6"},
                                {"4, 0", "4, 1", "4, 2", "4, 3", "4, 4", "4, 5", "4, 6"},
                                {"5, 0", "5, 1", "5, 2", "5, 3", "5, 4", "5, 5", "5, 6"},
                                {"6, 0", "6, 1", "6, 2", "6, 3", "6, 4", "6, 5", "6, 6"}
                            };
    char *cordTemp;

    //1. Inicializar el ambiente.
    elementos = malloc(sizeof(WIDGETS));
    gdk_color_parse("green", &colorJ1); 
    gdk_color_parse("orange", &colorJ2); 

    //2.1 Crear widgets.
    ventana = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    cajaVertical = gtk_vbox_new(FALSE, 5);
    cajaHorizontal1 = gtk_hbox_new(FALSE, 5);
    cajaHorizontal2 =  gtk_hbox_new(FALSE, 5);
    cajaH3 = gtk_hbox_new(FALSE, 5);
    cajaH4 = gtk_hbox_new(FALSE, 5); 
    cajaV = gtk_hbox_new(FALSE, 5);
    tabla = gtk_table_new(6, 7, TRUE);
    tablero2 = gtk_table_new(6, 7, TRUE);
    etiquetaJ1 = gtk_label_new(nombreJ1);
    etiquetaJ2 = gtk_label_new(nombreJ2);
    botonAtras = gtk_button_new_with_mnemonic("_Atras");
    botonAdelante = gtk_button_new_with_mnemonic("_Adelante");
    separador = gtk_hseparator_new();
    statusBar = gtk_statusbar_new();
    cajaH5 = gtk_hbox_new(FALSE, 5);
    cajaH6 = gtk_hbox_new(FALSE, 5);
    eTiempo = gtk_label_new("Tiempo: 0s");
    
    
    
    

     //Menu
    menuBar = gtk_menu_bar_new();
    herramientas = gtk_menu_item_new_with_label("Herramientas");
    fileItem = gtk_menu_item_new_with_label("Juego");
    fileMenu = gtk_menu_new();
    herramientasMenu = gtk_menu_new();
    guardar = gtk_image_menu_item_new_from_stock(GTK_STOCK_SAVE, NULL);
    deshacer = gtk_image_menu_item_new_from_stock(GTK_STOCK_GO_BACK, NULL);
    rehacer = gtk_image_menu_item_new_from_stock(GTK_STOCK_GO_FORWARD, NULL);
    guardarEnNuevoArchivo = gtk_image_menu_item_new_from_stock(GTK_STOCK_SAVE_AS, NULL);
    quitItem = gtk_image_menu_item_new_from_stock(GTK_STOCK_QUIT, NULL);
    ayudaItem = gtk_menu_item_new_with_label("Ayuda");
    ayudaMenu = gtk_menu_new(); 
    acercaDe = gtk_menu_item_new_with_label("Acerca de");
    recuperar = gtk_menu_item_new_with_label("Recuperar");
    juegoNuevo = gtk_image_menu_item_new_from_stock(GTK_STOCK_NEW, NULL);

    //ToolBar
    toolBar = gtk_toolbar_new();
    toolNg = gtk_tool_button_new_from_stock(GTK_STOCK_NEW);
    toolSv = gtk_tool_button_new_from_stock(GTK_STOCK_SAVE_AS); 
    toolSalir = gtk_tool_button_new_from_stock(GTK_STOCK_QUIT);
    gtk_toolbar_insert(GTK_TOOLBAR(toolBar), toolNg, 0);
    gtk_toolbar_insert(GTK_TOOLBAR(toolBar), toolSv, 1);
    gtk_toolbar_insert(GTK_TOOLBAR(toolBar), toolSalir, 2);




    //Guardanod en estructura
    elementos->tb1 = tabla;
    elementos->tb2 = tablero2;
    elementos->tirosJ1 = 0;
    elementos->tirosJ2 = 0;
    elementos->tirosTotal = 0;
    elementos-> ventana = ventana;
    elementos->bAtras = botonAtras;
    elementos->bAdelante = botonAdelante;
    elementos->numAtras = 0;
    elementos->list = listD;
    elementos->deshacer = deshacer;
    elementos->rehacer = rehacer;
    elementos->guardar = guardar;
    elementos->guardarNuevoArchivo = guardarEnNuevoArchivo;
    elementos->ventana = ventana;
    elementos->nextWindow = FALSE;
    elementos->nameJ1 = strdup(nombreJ1);
    elementos->nameJ2 = strdup(nombreJ2);
    elementos->turnoJ1 = TRUE;
    elementos->turnoJ2 = FALSE;
    elementos->tirosTotalJ1 = 0;
    elementos->tirosTotalJ2 = 0;
    elementos->eJugador1 = etiquetaJ1;
    elementos->eJugador2 = etiquetaJ2;
    elementos->statusBar = statusBar;
    elementos->eTiempo = eTiempo;
    elementos->segundos = 0;
    elementos->remove = FALSE;  


    for(int i = 0; i < 7; i++)
    {
        for(int j = 0; j < 7; j++)
        {
            
            botones[i][j] = gtk_button_new();
            botonesj2[i][j] = gtk_button_new();
            gtk_widget_set_name(botones[i][j], name[i][j]);
            gtk_widget_set_name(botonesj2[i][j], name[i][j]);
            elementos->botonesTb1[i][j] = botones[i][j];
            elementos->botonesTb2[i][j] = botonesj2[i][j];
        }
    }

    strcat(mensaje, strdup(elementos->nameJ1));
    strcat(mensaje, " 0-0    ||");
    strcat(mensaje, strdup(elementos->nameJ2));
    strcat(mensaje, " 0-0");

    
   
    //2.2 Fijar atributos.
    gtk_window_set_title(GTK_WINDOW(ventana), "Batalla Naval");
    gtk_window_set_default_size(GTK_WINDOW(ventana), 430, 350);
    gtk_widget_modify_fg(etiquetaJ1, GTK_STATE_NORMAL, &colorJ1);
    gtk_widget_modify_fg(etiquetaJ2, GTK_STATE_NORMAL, &colorJ2);
    gtk_widget_set_sensitive(GTK_WIDGET(tablero2), FALSE);
    gtk_widget_set_sensitive(GTK_WIDGET(botonAtras), FALSE);
    gtk_widget_set_sensitive(GTK_WIDGET(botonAdelante), FALSE);
    gtk_widget_set_sensitive(GTK_WIDGET(deshacer), FALSE);
    gtk_widget_set_sensitive(GTK_WIDGET(rehacer), FALSE);
    gtk_widget_set_sensitive(GTK_WIDGET(guardar), FALSE);
    gtk_widget_set_sensitive(GTK_WIDGET(elementos->guardarNuevoArchivo), FALSE);
    gtk_widget_set_name(GTK_WIDGET(guardar), "Guardar");
    gtk_menu_item_right_justify(GTK_MENU_ITEM(ayudaItem));
    gtk_statusbar_push(GTK_STATUSBAR(statusBar), 0, mensaje);


    barcosPosition(botones, botonesj2, elementos);

   
    
    //3. Registrar las llamadas a las funciones.
    g_signal_connect(G_OBJECT(ventana), "delete_event", G_CALLBACK(delete_event_handler), elementos);
    g_signal_connect(G_OBJECT(ventana), "destroy", G_CALLBACK(salir), elementos);
    g_signal_connect(G_OBJECT(quitItem), "activate", G_CALLBACK(backToMenu), elementos);
    g_signal_connect(G_OBJECT(deshacer), "activate", G_CALLBACK(deshacerFunction), elementos);
    g_signal_connect(G_OBJECT(rehacer), "activate", G_CALLBACK(rehacerFunction), elementos);
    g_signal_connect(G_OBJECT(guardar), "activate", G_CALLBACK(fileChooser), elementos);
    g_signal_connect(G_OBJECT(recuperar), "activate", G_CALLBACK(fileChooser), elementos);
    g_signal_connect(G_OBJECT(guardarEnNuevoArchivo), "activate", G_CALLBACK(createFile), elementos);
    g_signal_connect(G_OBJECT(acercaDe), "activate", G_CALLBACK(ventanaAcercaDe), elementos);
    g_signal_connect(G_OBJECT(botonAtras), "clicked", G_CALLBACK(atras), elementos);
    g_signal_connect(G_OBJECT(botonAdelante), "clicked", G_CALLBACK(adelante), elementos);
    g_signal_connect(G_OBJECT(juegoNuevo), "activate", G_CALLBACK(crearJuegoNuevo), elementos);
    g_signal_connect(G_OBJECT(toolNg), "clicked", G_CALLBACK(crearJuegoNuevo), elementos);
    g_signal_connect(G_OBJECT(toolSv), "clicked", G_CALLBACK(createFile), elementos);
    g_signal_connect(G_OBJECT(toolSalir), "clicked", G_CALLBACK(backToMenu), elementos);
    for(int i = 0; i < 7; i++)
    {
        for(int j = 0; j < 7; j++)
        {
            g_signal_connect(G_OBJECT(botonesj2[i][j]), "clicked", G_CALLBACK(clickTablero), elementos);
            g_signal_connect(G_OBJECT(botones[i][j]), "clicked", G_CALLBACK(clickTablero), elementos);
        }
    }
    
    



    //4. Definir jerarquía del programa.

    //Menu jerarquía
    gtk_menu_shell_append(GTK_MENU_SHELL(fileMenu), juegoNuevo);
    gtk_menu_shell_append(GTK_MENU_SHELL(fileMenu), guardar);
    gtk_menu_shell_append(GTK_MENU_SHELL(fileMenu), guardarEnNuevoArchivo);
    gtk_menu_shell_append(GTK_MENU_SHELL(fileMenu), recuperar); 
    gtk_menu_shell_append(GTK_MENU_SHELL(fileMenu), quitItem);
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(fileItem), fileMenu);
    gtk_menu_bar_append(GTK_MENU_BAR(menuBar), fileItem);
    gtk_menu_shell_append(GTK_MENU_SHELL(herramientasMenu), deshacer); 
    gtk_menu_shell_append(GTK_MENU_SHELL(herramientasMenu), rehacer);
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(herramientas), herramientasMenu);
    gtk_menu_bar_append(GTK_MENU_BAR(menuBar), herramientas);
    gtk_menu_shell_append(GTK_MENU_SHELL(ayudaMenu), acercaDe);
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(ayudaItem), ayudaMenu);
    gtk_menu_bar_append(GTK_MENU_BAR(menuBar), ayudaItem);

    //Botones
    for(int i = 0; i < 7; i++)
    {
        for(int j = 0; j < 7; j++)
        {
            gtk_table_attach_defaults(GTK_TABLE(tablero2), botonesj2[i][j], j, j + 1, i, i + 1);
            gtk_table_attach_defaults(GTK_TABLE(tabla), botones[i][j], j, j + 1, i, i + 1);
        }
    }

    gtk_box_pack_start(GTK_BOX(cajaVertical), menuBar, FALSE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(cajaVertical), toolBar, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(cajaH6), eTiempo, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(cajaVertical), cajaH6, TRUE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(cajaH3), etiquetaJ1, TRUE, TRUE, 5);
    gtk_box_pack_start(GTK_BOX(cajaH3), etiquetaJ2, TRUE, TRUE, 5);
    gtk_box_pack_start(GTK_BOX(cajaVertical), cajaH3, TRUE, TRUE, 5);
    gtk_box_pack_start(GTK_BOX(cajaHorizontal1), tabla, TRUE, TRUE, 5);
    gtk_box_pack_start(GTK_BOX(cajaV), cajaHorizontal1, TRUE, TRUE, 5);
    gtk_box_pack_start(GTK_BOX(cajaHorizontal2), tablero2, TRUE, TRUE, 5);
    gtk_box_pack_start(GTK_BOX(cajaV), cajaHorizontal2, TRUE, TRUE, 5);
    gtk_box_pack_start(GTK_BOX(cajaVertical), cajaV, TRUE, TRUE, 5);
    gtk_box_pack_start(GTK_BOX(cajaVertical), separador, FALSE, FALSE, 0); 
    gtk_box_pack_start(GTK_BOX(cajaH4), botonAtras, TRUE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(cajaH4), botonAdelante, TRUE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(cajaVertical), cajaH4, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(cajaH5), statusBar, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(cajaVertical), cajaH5, FALSE, FALSE, 0);
    gtk_container_add(GTK_CONTAINER(ventana), cajaVertical);

    //5. Mostrar los widgets.
    gtk_widget_show_all(ventana);
}
//* FIN --> VENTANA TABLERO



//! FUNCIONES --> VENTANA TABLERO
void clickTablero(GtkButton *boton, gpointer userData)
{
    WIDGETS *elementos = (WIDGETS *)userData;
    char *nombre = strdup(gtk_widget_get_name(GTK_WIDGET(boton)));
    char *tiro;
    int index;
    char mensaje[100] = "El jugador ";
    GdkColor color;
    /*for(int i = 0; i < elementos->tirosTotal; i++)
    {
        g_print("H: ----> %s ---> ", g_list_nth_data(elementos->list, i));
        g_print("\n");
    }*/

    if(elementos->segundos == 0)
    {
        g_print("start\n");
        elementos->idTimer = gtk_timeout_add(1000, timer, elementos);
    }

    gtk_widget_set_sensitive(GTK_WIDGET(elementos->guardar), TRUE);
    gtk_widget_set_sensitive(GTK_WIDGET(elementos->guardarNuevoArchivo), TRUE);
    gtk_widget_set_sensitive(GTK_WIDGET(elementos->deshacer), TRUE);
    g_print("C.- %c\n", nombre[0]);
    g_print("E: %d ----> I: %d\n", elementos->tirosTotal, index);

    if(elementos->turnoJ1)
    {
        strcat(mensaje, strdup(elementos->nameJ1));
        strcat(mensaje, " disparo en ");
        if(nombre[0] == 'X')
        {
            index = nombre[1] - '0';
            g_print("I: %d\n", index);
            elementos->tirosJ1 ++;
            gdk_color_parse("red", &color);
            tiro =  strdup(elementos->seleccionJ1[index]);
            gtk_widget_set_name(GTK_WIDGET(boton), elementos->seleccionJ1[index]);
            strcat(mensaje, tiro);
            strcat(mensaje, " y acerto en un barco");
            strcat(tiro, "*R");
            
        }else
        {
            tiro = strdup(nombre);
            gdk_color_parse("blue", &color);
            elementos->turnoJ1 = FALSE;
            elementos->turnoJ2 = TRUE;
            gtk_widget_set_sensitive(GTK_WIDGET(elementos->tb1), FALSE);
            gtk_widget_set_sensitive(GTK_WIDGET(elementos->tb2), TRUE);
            strcat(mensaje, tiro);
            strcat(mensaje, " y no acerto en nada!");
            strcat(tiro, "*B");
        }
        strcat(tiro, "1");
        elementos->tirosTotalJ1++;
    }else if(elementos->turnoJ2)
    {
        strcat(mensaje, strdup(elementos->nameJ2));
        strcat(mensaje, " presiono el boton ");
        if(nombre[0] == 'Z')
        {
            index = nombre[1] - '0';
            elementos->tirosJ2 += 1;
            gdk_color_parse("red", &color);
            tiro = strdup(elementos->seleccionJ2[index]);
            gtk_widget_set_name(GTK_WIDGET(boton), elementos->seleccionJ2[index]);
            g_print("click en %s\n", tiro);
            strcat(mensaje, tiro);
            strcat(mensaje, " y acerto en un barco");
            gtk_widget_set_name(GTK_WIDGET(boton), elementos->seleccionJ2[index]);
            strcat(tiro, "*R");
        }else
        {
            tiro = strdup(nombre);
            
            gdk_color_parse("blue", &color);
            elementos->turnoJ1 = TRUE;
            elementos->turnoJ2 = FALSE;
            gtk_widget_set_sensitive(GTK_WIDGET(elementos->tb1), TRUE);
            gtk_widget_set_sensitive(GTK_WIDGET(elementos->tb2), FALSE);
            strcat(mensaje, tiro);
            strcat(mensaje, " y no acerto en nada, mala suerte!!");
            strcat(tiro, "*B");
        }
        strcat(tiro, "2");
        elementos->tirosTotalJ2++;
    }
    gtk_statusbar_push(GTK_STATUSBAR(elementos->statusBar), 0, mensaje);
    g_print("click en %s --> %s\n", tiro,  gtk_widget_get_name(GTK_WIDGET(boton)));
    elementos->tirosTotal += 1;
    elementos->numAtras += 1;
    gtk_widget_modify_bg(GTK_WIDGET(boton), GTK_STATE_INSENSITIVE, &color);
    gtk_widget_set_sensitive(GTK_WIDGET(boton), FALSE);
    elementos->list = g_list_append(elementos->list, tiro);
    gtk_widget_set_sensitive(GTK_WIDGET(elementos->bAtras), TRUE);

    if(elementos->tirosJ1 == 10 || elementos->tirosJ2 == 10 || elementos->tirosTotal == 98)
    {
        gtk_widget_hide_all(elementos->ventana);
        g_print("SIIIII\n");
    }
}

void crearJuegoNuevo(GtkButton *boton, gpointer userData)
{
    WIDGETS *elementos = (WIDGETS *)userData;
    elementos->nextWindow = TRUE;
    gtk_timeout_remove(elementos->idTimer);
    gtk_widget_destroy(elementos->ventana);
    jugador1VsJugador2(elementos->nameJ1, elementos->nameJ2);
}

//! FUNCIONES --> VENTANA TABLERO