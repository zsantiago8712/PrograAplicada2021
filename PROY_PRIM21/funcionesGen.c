#include "local.h"


//* INICIO --> FUNCIONES EXTERNAS
extern void menuPrincipal(void);
extern void jugador1VsJugador2(char *nombreJ1, char *nombreJ2);
extern void jugador1VsCpu(char *nombreJ1);
//* FIN --> FUNCIONES EXTERNAS


//* INICIO --> FUNCIONES INTERNAS
void salir(GtkWidget *widget, gpointer userData);
void cancel(GtkButton *boton, gpointer userData);
void saveHistory(GtkButton *boton, gpointer userData);
gboolean delete_event_handler(GtkWidget *widget, gpointer userData);
void createFile(GtkButton *boton, gpointer userData);
void fileChooser(GtkButton *boton, gpointer userData);
void cambiarNombre(char *nombre);
void atras(GtkButton *boton, gpointer userData);
void deshacerFunction(GtkButton *boton, gpointer userData);
void adelante(GtkButton *boton, gpointer userData);
void rehacerFunction(GtkButton *boton, gpointer userData);
gboolean show_question(WIDGETS *elementos);
void backToMenu(GtkButton *boton, gpointer userData);
void barcosPosition(GtkWidget *botones[7][7], GtkWidget *botonesJ2[7][7], WIDGETS *elementos);
void ventanaAcercaDe(GtkButton *boton, gpointer userData);
void recuperarPartida(gpointer userData);
void ordenar(WIDGETS *elementos, char *dato, int renglon);
void arreglarHistorial(char *palabra);
void escogerNombresJugadores(WIDGETS *elementos);
void saveNames(GtkButton *boton, gpointer userData);
void dialogWarning(WIDGETS *elementos, int numMensajeError);
void cancelWindowName(GtkButton *boton, gpointer userData);
gint timer(gpointer data);
void restart(WIDGETS *elementos);
void crearJuegoNuevo(GtkButton *boton, gpointer userData);
void dialogWinner(WIDGETS *elementos, int jugador);
void on_close (GtkDialog *dialog, gint response_id, gpointer userData);
void saveScoreBoard(char *nombre, int tiempo);
void create_list(MARCADORES **inicio, MARCADORES **aux, char *nombre, int tiempo);
void ordenarMarcadores(MARCADORES *incio);
void reescribir_archivo(MARCADORES *inicio);
void liberarMemorial(MARCADORES *inicio);
void ayuda(GtkButton *boton, gpointer userData);
//* FIN --> FUNCIONES INTERNA



//! INICION ---> Funciones Genearles
gboolean delete_event_handler(GtkWidget *widget, gpointer userData)
{
    g_print("En delete_event_handler.\n");
    return FALSE;
}
    //* Funcion que hace que finalice el programa
void salir(GtkWidget *widget, gpointer userData)
{
    WIDGETS *elementos = (WIDGETS *)userData;
    if(!elementos->nextWindow) 
    {
        g_print("SALIDA");
        if(elementos->numVentan == 2)
        {
            g_list_free(elementos->list);
        }
        g_print("Click en salir\n");
        g_print("sip\n");
        gtk_main_quit();
    }
    g_print("sip\n");
}

    //* Funcion que crea una ventana para recibir el nombre del archivo en donde se va a gurdar la partida
void createFile(GtkButton *boton, gpointer userData)
{
    WIDGETS *elementos = (WIDGETS *)userData;
    GtkWidget *windowChoose, *aceptar, *cancelar, *etiqueta, *cajaV, *cajaH, *cajaH2;

    gtk_timeout_remove(elementos->idTimer);
    elementos->entryFileName = gtk_entry_new();
    windowChoose = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    aceptar = gtk_button_new_from_stock(GTK_STOCK_APPLY);
    cancelar = gtk_button_new_from_stock(GTK_STOCK_CANCEL);
    cajaV = gtk_vbox_new(FALSE, 5);
    cajaH = gtk_hbox_new(FALSE, 5);
    cajaH2 = gtk_hbox_new(FALSE, 5);
    etiqueta = gtk_label_new("Ingresa el nombre del archivo que quieres crear (Porfavor no ingrese la extension)!\n");

    elementos->windowFile = windowChoose;
    elementos->saveNewFile = TRUE;
    //Atributos
    gtk_window_set_title(GTK_WINDOW(windowChoose), "Crear Archivo");
    gtk_window_set_default_size(GTK_WINDOW(windowChoose), 100, 100);
    gtk_statusbar_push(GTK_STATUSBAR(elementos->statusBar), 0, "Guardando Partida");

    
    g_signal_connect(G_OBJECT(aceptar), "clicked", G_CALLBACK(saveHistory), elementos);
    g_signal_connect(G_OBJECT(cancelar), "clicked", G_CALLBACK(cancel), elementos);


    gtk_box_pack_start(GTK_BOX(cajaV), etiqueta, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(cajaH), elementos->entryFileName, TRUE, TRUE, 5);
    gtk_box_pack_start(GTK_BOX(cajaV), cajaH, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(cajaH2), aceptar, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(cajaH2), cancelar, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(cajaV), cajaH2, FALSE, FALSE, 0);
    gtk_container_add(GTK_CONTAINER(windowChoose), cajaV);

    gtk_widget_show_all(windowChoose);
}

//* Recibe la señal del boton cancelar en la ventana donde se recibe ewl nombre del archivo donde se va ha guardar la apartida
void cancel(GtkButton *boton, gpointer userData)
{
    WIDGETS *elementos = (WIDGETS *)userData;
    gtk_widget_destroy(elementos->windowFile);
    g_print("\nc\n");
    restart(elementos);
}

//* Guarda la partida en un archivo .btn
void saveHistory(GtkButton *boton, gpointer userData)
{

    WIDGETS *elementos = (WIDGETS *)userData;
    FILE *fp;
    char *jugadasJ1;
    char *jugadasJ2;
    if(elementos->saveNewFile){
        elementos->fileName =  strdup(gtk_entry_get_text(GTK_ENTRY(elementos->entryFileName)));
        strcat(elementos->fileName, ".btn");
        g_print("%s", elementos->fileName);
        fp = fopen(strdup(elementos->fileName), "r");
        
        if(fp != NULL)
        {
            elementos->question = 0;
            if(!show_question(elementos))
            {
                elementos->nextWindow = FALSE;
                return;
            }
        }
        fclose(fp);
    }
    g_print("CORRECTO GUARDAR H: ---> %s\n", elementos->fileName);
    
    fp=fopen(strdup(elementos->fileName), "w");
    fprintf(fp, "%d\n", elementos->tirosJ1);
    fprintf(fp, "%d\n", elementos->tirosTotalJ1);
    fprintf(fp, "%d\n", elementos->tirosJ2);
    fprintf(fp, "%d\n", elementos->tirosTotalJ2);
    fprintf(fp, "%d\n", elementos->tirosTotal);
    fprintf(fp, "%s\n", elementos->nameJ1);
    fprintf(fp, "%s\n", elementos->nameJ2);
    
    if(elementos->turnoJ1)
    {
        fprintf(fp, "%s", "J1\n");
    }else{
        fprintf(fp, "%s", "J2\n");
    }
    

    for(int i = 0; i < 10; i++)
    {
        fprintf(fp, "%s", elementos->seleccionJ1[i]);
        fprintf(fp, "\n");
    }
    for(int i = 0; i < 10; i++)
    {
        fprintf(fp, "%s", elementos->seleccionJ2[i]);
        fprintf(fp, "\n");
    }

    for(int i = 0; i < elementos->tirosTotal; i++)
    {
        jugadasJ1 = g_list_nth_data(elementos->list, i);
        fprintf(fp, "%s\n", jugadasJ1);
        g_print("%s\n", jugadasJ1);
        g_print("H: ----> %s ---> ", jugadasJ1);
        if(i != elementos->tirosTotal - 1)
        {
            g_print("\n");
        }
    }

    for(int i = 0; i < 7; i++)
    {
        for(int j = 0; j < 7; j++)
        {
            jugadasJ1 = strdup(gtk_widget_get_name(elementos->botonesTb1[i][j]));
            jugadasJ2 = strdup(gtk_widget_get_name(elementos->botonesTb2[i][j]));
            if(jugadasJ1[0] == 'X')
            {
                fprintf(fp, "%s", jugadasJ1);
                fprintf(fp, "\n");
            }
            if(jugadasJ2[0] == 'Z')
            {
                fprintf(fp, "%s", jugadasJ2);
                fprintf(fp, "\n");
            }
        }
    }

    fprintf(fp, "%d", elementos->segundos);
    fprintf(fp, "%s", "*T");

    fclose(fp);

    if(elementos->saveAndQuit && elementos->saveNewFile)
    {   
        g_print("nel");
        elementos->nextWindow = TRUE;
        gtk_widget_destroy(elementos->windowFile);
        gtk_widget_destroy(elementos->ventana);
        g_list_free(elementos->list);
        menuPrincipal(); 

    }else if(elementos->saveNewFile)
    {
        g_print("NUEVO");
        elementos->nextWindow = TRUE;
        gtk_widget_destroy(elementos->windowFile);
        restart(elementos);
    }
    elementos->nextWindow = FALSE;
    
}

//* ventana para escoger el archivo de forma grafica
void fileChooser(GtkButton *boton, gpointer userData)
{
    WIDGETS *elementos = (WIDGETS *)userData;
    g_print("A-->%s", strdup(gtk_widget_get_name(GTK_WIDGET(boton))));

    gtk_timeout_remove(elementos->idTimer);
    elementos->saveNewFile = FALSE;
    GtkWidget *dialog, *window, *errorDialog, *windowError;
    gint resp, respW;
    gboolean isValid = FALSE;
    gboolean recoveryMode = FALSE;
    windowError = gtk_window_new(GTK_WINDOW_TOPLEVEL); 
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    
    dialog = gtk_file_chooser_dialog_new("Elige un archivo", GTK_WINDOW(window),
            GTK_FILE_CHOOSER_ACTION_OPEN, GTK_STOCK_OK, GTK_RESPONSE_OK, GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL, NULL);

    gtk_widget_show_all(dialog);

    if(strcmp(gtk_widget_get_name(GTK_WIDGET(boton)), "Guardar") == 0)
    {
        gtk_statusbar_push(GTK_STATUSBAR(elementos->statusBar), 0, "Guardando Partida");
    }else
    {
        gtk_statusbar_push(GTK_STATUSBAR(elementos->statusBar), 0, "Recuperando Partida");
    }
    

   
    //gtk_file_chooser_add_filter (GTK_FILE_CHOOSER(dialog), "*.btn");
    gtk_file_chooser_set_create_folders(GTK_FILE_CHOOSER(dialog), FALSE);
    while(!isValid)
    {
        resp = gtk_dialog_run(GTK_DIALOG(dialog));
        if(resp == GTK_RESPONSE_OK)
        {
            g_print("R: %d\n", resp);
            elementos->fileName = strdup(gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog)));
            g_print("%s\n", elementos-> fileName);
            if(elementos-> fileName[strlen(elementos-> fileName) - 1] == 'n' && elementos-> fileName[strlen(elementos-> fileName) - 2] == 't' && elementos-> fileName[strlen(elementos-> fileName) - 3] == 'b')
            {
                g_print("correcto");
                gtk_widget_destroy(GTK_WIDGET(dialog));
                if(strcmp(gtk_widget_get_name(GTK_WIDGET(boton)), "Guardar") == 0)
                {
                    saveHistory(boton, elementos);
                }else
                {
                    recuperarPartida(elementos);
                    recoveryMode = TRUE;
                }
                isValid = TRUE;
            }else if(strlen(elementos-> fileName) > 0){
                g_print("incorrecto");
                errorDialog = gtk_message_dialog_new(GTK_WINDOW(windowError), GTK_DIALOG_MODAL, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK, "ERROR: Solo puedes escoger archivos con .btn\n");
                gtk_widget_show_all(errorDialog);
                respW = gtk_dialog_run(GTK_DIALOG(errorDialog));
                if(respW == GTK_RESPONSE_OK)
                    gtk_widget_destroy(errorDialog);
                }        
        }
        else
        {
            g_print("R: %d\n", resp);
            g_print("Canceled\n");
            isValid = TRUE;
        }
    }
    
    gtk_widget_destroy(GTK_WIDGET(dialog));
    if(!recoveryMode)
    { 
        if(elementos->segundos > 0)
        {
            restart(elementos);
        }
    }
    gtk_statusbar_push(GTK_STATUSBAR(elementos->statusBar), 0, "Esperando al siguiente tiro");
   
}
//* Formate el string para quitar todo lo que este apartir de '*'
void cambiarNombre(char *nombre)
{
    char nuevoNombre[strlen(nombre)];
    for(int i = 0; i < strlen(nombre); i++)
    {
        if(nombre[i] != '*')
        {
            nombre[i] = nombre[i];       
        }else
        {
            nombre[i] = '\0';
            break;
        }
    }
}

//* Funcion para regresar un tiro atras
void atras(GtkButton *boton, gpointer userData)
{
    WIDGETS *elementos = (WIDGETS *)userData;
    elementos->numAtras-=1;
    char *nombre = strdup(g_list_nth_data(elementos->list, elementos->numAtras));
    char *nombreCompare;
    gtk_timeout_remove(elementos->idTimer);
    gtk_widget_set_sensitive(GTK_WIDGET(elementos->bAdelante), TRUE);
    gtk_widget_set_sensitive(GTK_WIDGET(elementos->rehacer), TRUE);
    gtk_widget_set_sensitive(GTK_WIDGET(elementos->tb1), FALSE);
    gtk_widget_set_sensitive(GTK_WIDGET(elementos->tb2), FALSE);

    if(nombre[strlen(nombre) - 1] == '2')
    {
        cambiarNombre(nombre);
        for(int i = 0; i < 7; i++)
        {
            for(int j = 0; j < 7; j++)
            {
                nombreCompare = strdup(gtk_widget_get_name(elementos->botonesTb2[i][j]));
                if(strcmp(nombre, nombreCompare) == 0)
                {
                    gtk_widget_modify_bg(elementos->botonesTb2[i][j], GTK_STATE_INSENSITIVE, NULL);
                    break;
                }
            }
        }
    }else if(nombre[strlen(nombre) - 1] == '1')
    {
        cambiarNombre(nombre);
        for(int i = 0; i < 7; i++)
        {
            for(int j = 0; j < 7; j++)
            {
                nombreCompare = strdup(gtk_widget_get_name(elementos->botonesTb1[i][j]));
                if(strcmp(nombre, nombreCompare) == 0)
                {
                    gtk_widget_modify_bg(elementos->botonesTb1[i][j], GTK_STATE_INSENSITIVE, NULL);
                    break;
                }
            }
        } 
    }
    
    if(elementos->numAtras == 0)
    {
      gtk_widget_set_sensitive(GTK_WIDGET(boton), FALSE);
      gtk_widget_set_sensitive(GTK_WIDGET(elementos->deshacer), FALSE); 
    }
}

//* Regresa todos los tiros hasta el inicio
void deshacerFunction(GtkButton *boton, gpointer userData)
{
    
    WIDGETS *elementos = (WIDGETS *)userData;
    char *nombre;
    char *nombreCompare;
    
    gtk_timeout_remove(elementos->idTimer);
    gtk_widget_set_sensitive(GTK_WIDGET(elementos->bAdelante), TRUE);
    gtk_widget_set_sensitive(GTK_WIDGET(elementos->tb1), FALSE);
    gtk_widget_set_sensitive(GTK_WIDGET(elementos->tb2), FALSE);
    gtk_widget_set_sensitive(GTK_WIDGET(boton), FALSE);
    gtk_widget_set_sensitive(GTK_WIDGET(elementos->bAtras), FALSE);
   
    for(elementos->numAtras -= 1; elementos->numAtras >= 0; elementos->numAtras--)
    {
        nombre = strdup(g_list_nth_data(elementos->list, elementos->numAtras));
        g_print("entre %s", nombre);
        if(nombre[strlen(nombre) - 1] == '2')
        {
            cambiarNombre(nombre);
            for(int i = 0; i < 7; i++)
            {
                for(int j = 0; j < 7; j++)
                {
                    nombreCompare = strdup(gtk_widget_get_name(elementos->botonesTb2[i][j]));
                    g_print("NS: %s ---- %s\n", nombre, nombreCompare);
                    if(strcmp(nombre, nombreCompare) == 0)
                    {
                        g_print("SI ENCONTRO 2\n");
                        gtk_widget_modify_bg(elementos->botonesTb2[i][j], GTK_STATE_INSENSITIVE, NULL);
                        break;
                    }
                }
            }
        }else if(nombre[strlen(nombre) - 1] == '1')
        {
            cambiarNombre(nombre);
            for(int i = 0; i < 7; i++)
            {
                for(int j = 0; j < 7; j++)
                {
                    nombreCompare = strdup(gtk_widget_get_name(elementos->botonesTb1[i][j]));
                    g_print("NS: %s ---- %s\n", nombre, nombreCompare);
                    if(strcmp(nombre, nombreCompare) == 0)
                    {
                        g_print("SI ENCONTRO 1\n");
                        gtk_widget_modify_bg(elementos->botonesTb1[i][j], GTK_STATE_INSENSITIVE, NULL);
                        break;
                    }
                }
            } 
        }
    }
    gtk_widget_set_sensitive(GTK_WIDGET(elementos->rehacer), TRUE);
    g_print("\nnumA ---> %d\n", elementos->numAtras);
    elementos->numAtras = 0;
}

//* Si se regreso un tiro hacia atras este lo regresara hacia adelante
void adelante(GtkButton *boton, gpointer userData)
{
    WIDGETS *elementos = (WIDGETS *)userData;
    GdkColor color;
    g_print("D.-%d\n", elementos->tirosTotal);
    char *name = strdup(g_list_nth_data(elementos->list, elementos->numAtras));
    char *nameComp;
    gdk_color_parse("blue", &color);
    gboolean is1Player = FALSE;

    g_print("NOMBRE --> %s --> %c\n", name, name[strlen(name) - 1]);

    if(name[strlen(name) - 1] == '1')
    {
        g_print("\nPLAYER\n");
        is1Player = TRUE;
    }

    if(name[strlen(name) - 2] == 'R')
    {
        gdk_color_parse("red", &color);
    }

    cambiarNombre(name);
    for(int i = 0; i < 7; i++)
    {
        for(int j = 0; j < 7; j++)
        {
            if(is1Player)
            {
                nameComp = strdup(gtk_widget_get_name(elementos->botonesTb1[i][j]));
                
                if(strcmp(name, nameComp) == 0)
                {
                    gtk_widget_modify_bg(elementos->botonesTb1[i][j], GTK_STATE_INSENSITIVE, &color);
                    gtk_widget_set_sensitive(GTK_WIDGET(elementos->botonesTb1[i][j]), FALSE);
                    break; 
                }
            }else 
            {
                nameComp = strdup(gtk_widget_get_name(elementos->botonesTb2[i][j]));
                if(strcmp(name, nameComp) == 0)
                {
                    gtk_widget_modify_bg(elementos->botonesTb2[i][j], GTK_STATE_INSENSITIVE, &color);
                    gtk_widget_set_sensitive(GTK_WIDGET(elementos->botonesTb2[i][j]), FALSE);
                    break;
                }
            }
        }
    }  
    elementos->numAtras += 1;
    g_print("%d -- %d\n", elementos->numAtras, elementos->tirosTotal);
    if(elementos->numAtras == elementos->tirosTotal)
    {
        gtk_widget_set_sensitive(GTK_WIDGET(boton), FALSE);
        gtk_widget_set_sensitive(GTK_WIDGET(elementos->rehacer), FALSE);
        gtk_widget_set_sensitive(GTK_WIDGET(elementos->deshacer), TRUE); 
        gtk_widget_set_sensitive(GTK_WIDGET(elementos->bAtras), TRUE);
        if(elementos->gameMode == 1)
        {
            if(elementos->turnoJ1)
            {
                gtk_widget_set_sensitive(GTK_WIDGET(elementos->tb1), TRUE);
            }else if(elementos->turnoJ2)
            {
                gtk_widget_set_sensitive(GTK_WIDGET(elementos->tb2), TRUE);
            }
        }else
        {
           gtk_widget_set_sensitive(GTK_WIDGET(elementos->tb1), TRUE); 
        }
        restart(elementos);
    }
}


//* Regresa todos los tiros hasta donde se quedo la partida
void rehacerFunction(GtkButton *boton, gpointer userData)
{
    WIDGETS *elementos = (WIDGETS *)userData;
    GdkColor color;
    char *name;
    char *nameComp;
    gdk_color_parse("blue", &color);
    gboolean is1Player = FALSE;


    for(elementos->numAtras; elementos->numAtras < elementos->tirosTotal; elementos->numAtras++)
    {
        name = strdup(g_list_nth_data(elementos->list, elementos->numAtras));
        g_print("eee\n");
        if(name[strlen(name) - 1] == '1')
        {
            is1Player = TRUE;
        }
        if(name[strlen(name) - 2] == 'R')
        {
            gdk_color_parse("red", &color); 
        }
        cambiarNombre(name);

        for(int i = 0; i < 7; i++)
        {
            
            for(int j = 0; j < 7; j++)
            {
                if(is1Player)
                {
                    nameComp = strdup(gtk_widget_get_name(elementos->botonesTb1[i][j]));
                    if(strcmp(name, nameComp) == 0)
                    {
                        gtk_widget_modify_bg(elementos->botonesTb1[i][j], GTK_STATE_INSENSITIVE, &color); 
                    }
                }else 
                {
                    nameComp = strdup(gtk_widget_get_name(elementos->botonesTb2[i][j]));
                    if(strcmp(name, nameComp) == 0)
                    {
                        gtk_widget_modify_bg(elementos->botonesTb2[i][j], GTK_STATE_INSENSITIVE, &color);
                    }
                }
            }
        }
        is1Player = FALSE;
        gdk_color_parse("blue", &color); 
    }
    gtk_widget_set_sensitive(GTK_WIDGET(boton), FALSE);
    gtk_widget_set_sensitive(GTK_WIDGET(elementos->bAdelante), FALSE);
    gtk_widget_set_sensitive(GTK_WIDGET(elementos->bAtras), TRUE);
    gtk_widget_set_sensitive(GTK_WIDGET(elementos->deshacer), TRUE);
    if(elementos->gameMode == 1)
    {
        if(elementos->turnoJ1)
        {
            gtk_widget_set_sensitive(GTK_WIDGET(elementos->tb1), TRUE);
            
        }else if(elementos->turnoJ2)
        {
            gtk_widget_set_sensitive(GTK_WIDGET(elementos->tb2), TRUE);
        }
    }else
    {
       gtk_widget_set_sensitive(GTK_WIDGET(elementos->tb1), TRUE);  
    }
    
    restart(elementos);
    g_print("\nnumA ---> %d\n", elementos->numAtras);
}


//* Regresera al menu, preguntando si quiere salir y si quiere guardar la partida
void backToMenu(GtkButton *boton, gpointer userData)
{
    WIDGETS *elementos = (WIDGETS *)userData; 
    gtk_timeout_remove(elementos->idTimer);
    gboolean save;
    elementos->nextWindow = TRUE;
    elementos->question = 1;
    elementos->saveAndQuit = TRUE;
    if(show_question(elementos))
    {
        elementos->question = 2;
        
        if(elementos->segundos == 0)
        {
            gtk_widget_destroy(elementos->ventana);
            g_list_free(elementos->list);
            menuPrincipal();
            return;
        }else
        {
            if(!show_question(elementos))
            {
                gtk_widget_destroy(elementos->ventana);
                menuPrincipal();
                return;
            }else
            {
                createFile(boton, elementos);
                return;
            }
        }
    }
    if(elementos->segundos > 0)
    {
        restart(elementos);
    }
    elementos->nextWindow = FALSE;
}


void on_close(GtkDialog *dialog, gint response_id, gpointer userData)
{
  /* This will cause the dialog to be destroyed */
  WIDGETS *elementos = (WIDGETS *)userData;
  if(elementos->remove)
  {
    restart(elementos);
  }
  elementos->remove = FALSE;
  gtk_widget_destroy(GTK_WIDGET(dialog));
}


//* Ventana para ver la inforamcion del programa
void ventanaAcercaDe(GtkButton *boton, gpointer userData)
{
    WIDGETS *elementos = (WIDGETS *)userData;
    GtkWidget *window2;
    const char *author[] = {"Sebastian Sedano", "Mauricio Olguin", "Santiago Zamora", '\0'};
    if(elementos->segundos > 0)
    {
        elementos->remove = TRUE;
        gtk_timeout_remove(elementos->idTimer);
    }
    window2 = gtk_about_dialog_new();
    
    gtk_window_set_default_size(GTK_WINDOW(window2), 300, 300);
    gtk_about_dialog_set_name(GTK_ABOUT_DIALOG(window2), "Batalla Naval");
    gtk_about_dialog_set_comments(GTK_ABOUT_DIALOG(window2), "Version 3.1");
    gtk_about_dialog_set_authors(GTK_ABOUT_DIALOG(window2), author);
    gtk_about_dialog_set_artists(GTK_ABOUT_DIALOG(window2), author);
    gtk_about_dialog_set_documenters(GTK_ABOUT_DIALOG(window2), author);
    gtk_about_dialog_set_copyright(GTK_ABOUT_DIALOG(window2), "Copyright");
    
    
    g_signal_connect (GTK_DIALOG(window2), "response", G_CALLBACK (on_close), elementos);

    gtk_widget_show_all(window2);
    gtk_window_set_modal(GTK_WINDOW(window2), TRUE);
}

//* Pone los barcos de los 2 jugadores de forma aletoria
void barcosPosition(GtkWidget *botones[7][7], GtkWidget *botonesJ2[7][7], WIDGETS *elementos)
{
    const char *nombreSelecciones[20] = {"X0", "X1", "X2", "X3", "X4", "X5", "X6", "X7", "X8", "X9", 
                                    "Z0", "Z1", "Z2", "Z3", "Z4", "Z5", "Z6", "Z7", "Z8", "Z9"};
    char *nombre;
    srand(time(0));
    int x, y;
    for(int i = 0; i < 20; i++)
    {
        x = rand() %7;
        y = rand() %7;
        if(i <= 9)
        {
            nombre = strdup(gtk_widget_get_name(botones[x][y]));
            if(nombre[0] != 'X')
            {
                elementos->seleccionJ1[i] = strdup(nombre);
                g_print("%s---->%d: J1.- X%d, Y%d\n", nombreSelecciones[i], i, x, y);
            }else if(nombre[0] == 'X')
            {
                do{
                    x = rand() %7; 
                    y = rand() %7;
                    g_print("R2.- 2: %c\n", nombre[0]);
                    nombre = strdup(gtk_widget_get_name(botones[x][y]));
                    elementos->seleccionJ1[i] = strdup(nombre);
                    g_print("R2: %c\n", nombre[0]);
                }while(nombre[0] == 'X');
                g_print("R3: %c\n", nombre[0]);
                g_print("%s---->%d: J1.- X%d, Y%d\n", nombreSelecciones[i], i, x, y); 
            }
            gtk_widget_set_name(botones[x][y], nombreSelecciones[i]);

            
            
        }else if(i >= 10)
        {
            nombre = strdup(gtk_widget_get_name(botonesJ2[x][y]));
            if(nombre[0] != 'Z')
            {
                elementos->seleccionJ2[i-10] = strdup(nombre);
                g_print("%s----->%d: J2.- X%d, Y%d\n", nombreSelecciones[i], i, x, y);
            }else if(nombre[0] == 'Z')
            {
                
                do{
                    g_print("R1.- 1: %c ---> %s\n", nombre[0], nombre);
                    x = rand() %7;
                    y = rand() %7; 
                    nombre = strdup(gtk_widget_get_name(botonesJ2[x][y]));
                    elementos->seleccionJ2[i-10] = strdup(nombre);
                    g_print("R2: %c ---> %s ---> %d, %d\n", nombre[0], nombre, x, y);
                }while(nombre[0] == 'Z');
                g_print("R3: %c\n", nombre[0]);
                g_print("%s----->%d: J2.- X%d, Y%d\n", nombreSelecciones[i], i, x, y);
            }
            gtk_widget_set_name(botonesJ2[x][y], nombreSelecciones[i]);
        }
    }

    for(int i = 0; i < 10; i++)
    {
        g_print("1.- %s ---> ", elementos->seleccionJ1[i]);
        g_print("2.- %s\n", elementos->seleccionJ2[i]);
    }

}

//* Ventana para mostrar un dialogo, este dependera de que se haya presionado antes
gboolean show_question(WIDGETS *elementos) {
    
    GtkWidget *dialog, *window;
    gint resp;
    char *message[] = {"¿Seguro quieres rescribir el archivo?, se perederan todos los datos actuales!!",
                        "¿Seguro quieres salir?", "¿Quieres guardar la partida actual?", "Si quieres jugar otra partida presione el boton OK, de lo contrario presiona cancel"};

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    dialog = gtk_message_dialog_new(GTK_WINDOW(window), GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_QUESTION,GTK_BUTTONS_OK_CANCEL, message[elementos->question], NULL);
    gtk_window_set_title(GTK_WINDOW(dialog), "Question");
    resp = gtk_dialog_run(GTK_DIALOG(dialog));
    if(resp == GTK_RESPONSE_OK)
    {
        g_print("yes\n");
        gtk_widget_destroy(dialog);
        return TRUE;
    }else
    {
        g_print("no\n");
        gtk_widget_destroy(dialog);
        return FALSE;
    }
  
}

//* Recuperar la inforamcion del archivo que se eligio, para recuperar una partida
void recuperarPartida(gpointer userData)
{
    
    WIDGETS *elementos = (WIDGETS *)userData; 
    FILE *fp;
    char textTime[40] = "Tiempo: ";
    char saveTemp[10];

    int renglon = 0;
    char *name[100][100] =  {  
                            {"0, 0", "0, 1", "0, 2", "0, 3", "0, 4", "0, 5", "0, 6"}, 
                            {"1, 0", "1, 1", "1, 2", "1, 3", "1, 4", "1, 5", "1, 6"},
                            {"2, 0", "2, 1", "2, 2", "2, 3", "2, 4", "2, 5", "2, 6"},
                            {"3, 0", "3, 1", "3, 2", "3, 3", "3, 4", "3, 5", "3, 6"},
                            {"4, 0", "4, 1", "4, 2", "4, 3", "4, 4", "4, 5", "4, 6"},
                            {"5, 0", "5, 1", "5, 2", "5, 3", "5, 4", "5, 5", "5, 6"},
                            {"6, 0", "6, 1", "6, 2", "6, 3", "6, 4", "6, 5", "6, 6"}
                        };

    
    elementos->list = NULL;                    
    
    gtk_widget_set_sensitive(GTK_WIDGET(elementos->tb1), FALSE);
    gtk_widget_set_sensitive(GTK_WIDGET(elementos->tb2), FALSE);
    for(int i = 0; i < 7; i++)
    {
        for(int j = 0; j < 7; j++)
        {
            gtk_widget_set_name(elementos->botonesTb1[i][j], strdup(name[i][j]));
            gtk_widget_set_name(elementos->botonesTb2[i][j], strdup(name[i][j]));
            gtk_widget_modify_bg(elementos->botonesTb2[i][j], GTK_STATE_INSENSITIVE, NULL);
            gtk_widget_modify_bg(elementos->botonesTb1[i][j], GTK_STATE_INSENSITIVE, NULL);
        }
    }
    

    fp = fopen(elementos->fileName, "r");
    while(fgets(saveTemp, 10, fp) != NULL)
    {
        arreglarHistorial(saveTemp);
        if(renglon < 28 || saveTemp[0] == 'X' || saveTemp[0] == 'Z')
        {
            ordenar(elementos, saveTemp, renglon);
        }else
        {
            if(saveTemp[strlen(saveTemp) - 1] == 'T')
            {
                cambiarNombre(saveTemp);
                elementos->segundos = atoi(saveTemp);
                strcat(textTime, saveTemp);
                strcat(textTime, "s");
                gtk_label_set_text(GTK_LABEL(elementos->eTiempo), textTime);
            }else
            {
                g_print("H --> %s\n", saveTemp);
                elementos->list = g_list_append(elementos->list, strdup(saveTemp));
            }
        }
        renglon++;
    } 
    fclose(fp);

    gtk_widget_set_sensitive(GTK_WIDGET(elementos->rehacer), TRUE);
    gtk_widget_set_sensitive(GTK_WIDGET(elementos->bAdelante), TRUE);
    gtk_widget_set_sensitive(GTK_WIDGET(elementos->guardar), FALSE);
    gtk_widget_set_sensitive(GTK_WIDGET(elementos->guardarNuevoArchivo), FALSE);
    gtk_widget_set_sensitive(GTK_WIDGET(elementos->deshacer), FALSE);
    gtk_widget_set_sensitive(GTK_WIDGET(elementos->bAtras), FALSE);
}

//* Acomodara la informacion leida del archivo elegido apra recuperar la partida
void ordenar(WIDGETS *elementos, char *dato, int renglon)
{
    int index;
    gboolean notFound = FALSE;
    char *realName;
    char *nameComp;
    if(renglon <= 28)
    {
        switch (renglon)
        {
        case 0:
            elementos->tirosJ1 = atoi(dato);
            break;
        case 1:
            elementos->tirosTotalJ1 = atoi(dato);
            break;
        case 2:
            elementos->tirosJ2 = atoi(dato);
            break;
        case 3:
            elementos->tirosTotalJ2 = atoi(dato);
            break;
        case 4:
            elementos->tirosTotal = atoi(dato);
            elementos->numAtras = 0;
            break;
        case 5:
            elementos->nameJ1 = strdup(dato);
            gtk_label_set_text(GTK_LABEL(elementos->eJugador1), strdup(dato));
            break;
        case 6:
            elementos->nameJ2 = strdup(dato);
            gtk_label_set_text(GTK_LABEL(elementos->eJugador2), strdup(dato)); 
            break;
        case 7:
            if(elementos->gameMode == 0)
            {
                elementos->turnoJ1 = TRUE;
                elementos->turnoJ2 = FALSE;
            }else
            {
                if(strcmp("J1", dato) == 0)
                {
                    elementos->turnoJ1 = TRUE;
                    elementos->turnoJ2 = FALSE;
                }else if(strcmp("J2", dato) == 0)
                {
                    elementos->turnoJ1 = FALSE;
                    elementos->turnoJ2 = TRUE;
                }
            }
            break;

        default:
            break;
        }

        if(renglon >= 8 && renglon <= 17)
        {
            elementos->seleccionJ1[renglon - 8] = strdup(dato);
        }else if(renglon >= 18 && renglon <= 27)
        {
            elementos->seleccionJ2[renglon - 18] = strdup(dato);
        }

    }else
    {
        
        if(dato[0] == 'X')
        {
            index = dato[1] - '0';
            realName = strdup(elementos->seleccionJ1[index]);
            arreglarHistorial(realName);
            for(int i = 0; i < 7; i++)
            {
                for(int j = 0; j < 7; j++)
                {
                    
                    for(int k = 0; k < elementos->tirosTotal; k++)
                    {
                        nameComp = strdup(g_list_nth_data(elementos->list, k));
                        if(nameComp[strlen(nameComp) - 1] == '1')
                        {
                            cambiarNombre(nameComp);
                            if(strcmp(realName, nameComp) == 0)
                            {
                                notFound = TRUE;
                                break;
                            }
                        }
                    }
                    if(!notFound)
                    {
                        nameComp = strdup(gtk_widget_get_name(elementos->botonesTb1[i][j]));
                        if(strcmp(realName, nameComp) == 0)
                        {
                            gtk_widget_set_name(elementos->botonesTb1[i][j], strdup(dato));
                            break;
                        }
                    }
                    notFound = FALSE;
                }
            }
        }else if(dato[0] == 'Z')
        {
            index = dato[1] - '0';
            realName = strdup(elementos->seleccionJ2[index]);
            arreglarHistorial(realName);
            arreglarHistorial(dato);
            for(int i = 0; i < 7; i++)
            {
                for(int j = 0; j < 7; j++)
                {
                    
                    for(int k = 0; k < elementos->tirosTotal; k++)
                    {
                        nameComp = strdup(g_list_nth_data(elementos->list, k));
                        if(nameComp[strlen(nameComp) - 1] == '2')
                        {
                            cambiarNombre(nameComp);
                            if(strcmp(realName, nameComp) == 0)
                            {
                                notFound = TRUE;
                                break;
                            }
                        }
                    }
                    if(!notFound)
                    {
                        nameComp = strdup(gtk_widget_get_name(elementos->botonesTb2[i][j]));
                        if(strcmp(realName, nameComp) == 0)
                        {
                            gtk_widget_set_name(elementos->botonesTb2[i][j], strdup(dato));
                            break;
                        }
                    }
                    notFound = FALSE;
                }
            }
        }

    }
}


//* Formatera los strings quitando el salto de linea
void arreglarHistorial(char *palabra)
{
    for(int i = 0; i < strlen(palabra); i++)
    {
        if(palabra[i] != 10)
        {
            palabra[i] = palabra[i];
        }else
        {
            palabra[i] = '\0';
            break;
        }
    }
}


//* Ventana para escoger el nombre de los jugadores
void escogerNombresJugadores(WIDGETS *elementos)
{
    GtkWidget *windowNames, *aceptar, *cancelar, *etiqueta, *cajaV, *cajaH, *cajaH2, *cajaH3, *etiquetaJ1, *etiquetaJ2;
    
    elementos->entryJugar1Name = gtk_entry_new();
    elementos->entryJugar2Name = gtk_entry_new();
    windowNames = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    aceptar = gtk_button_new_from_stock(GTK_STOCK_APPLY);
    cancelar = gtk_button_new_from_stock(GTK_STOCK_CANCEL);
    cajaV = gtk_vbox_new(FALSE, 5);
    cajaH = gtk_hbox_new(FALSE, 5);
    cajaH2 = gtk_hbox_new(FALSE, 5);
    cajaH3 = gtk_hbox_new(FALSE, 5);
    etiqueta = gtk_label_new("Para empezar la partida ingresen sus nombres minimo se debe de poner 1 letra!\n");
    etiquetaJ1 = gtk_label_new("Jugador1");
    etiquetaJ2 = gtk_label_new("Jugador2");
    elementos->windowFile = windowNames;

    //Atributos
    gtk_window_set_title(GTK_WINDOW(windowNames), "Nombres Jugadores");
    gtk_window_set_default_size(GTK_WINDOW(windowNames), 100, 100);
    gtk_entry_set_max_length(GTK_ENTRY(elementos->entryJugar1Name), 8);
    gtk_entry_set_max_length(GTK_ENTRY(elementos->entryJugar2Name), 8);


    g_signal_connect(G_OBJECT(aceptar), "clicked", G_CALLBACK(saveNames), elementos);
    g_signal_connect(G_OBJECT(cancelar), "clicked", G_CALLBACK(cancelWindowName), elementos);


    gtk_box_pack_start(GTK_BOX(cajaV), etiqueta, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(cajaH), etiquetaJ1, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(cajaH), elementos->entryJugar1Name, TRUE, TRUE, 5);
    gtk_box_pack_start(GTK_BOX(cajaV), cajaH, FALSE, FALSE, 0);
    if(elementos->gameMode == 1)
    {
        gtk_box_pack_start(GTK_BOX(cajaH2), etiquetaJ2, FALSE, FALSE, 0);
        gtk_box_pack_start(GTK_BOX(cajaH2), elementos->entryJugar2Name, TRUE, TRUE, 5);
        gtk_box_pack_start(GTK_BOX(cajaV), cajaH2, FALSE, FALSE, 0); 
    }
    gtk_box_pack_start(GTK_BOX(cajaH3), aceptar, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(cajaH3), cancelar, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(cajaV), cajaH3, FALSE, FALSE, 0);
    gtk_container_add(GTK_CONTAINER(windowNames), cajaV);
    gtk_widget_show_all(windowNames); 
}

//* Funcipn para validar que los nombres que se introducieron son validos
void saveNames(GtkButton *boton, gpointer userData)
{
    WIDGETS *elementos = (WIDGETS *)userData;
    elementos->nameJ1 = strdup(gtk_entry_get_text(GTK_ENTRY(elementos->entryJugar1Name)));
    int numMensajeError;
    int lettersCount = 0;
    gboolean isValid = TRUE;
    if(elementos->gameMode == 1)
    {
        elementos->nameJ2 = strdup(gtk_entry_get_text(GTK_ENTRY(elementos->entryJugar2Name)));
        if(strlen(elementos->nameJ1) == 0 && strlen(elementos->nameJ2) > 0)
        {
            isValid = FALSE;
            numMensajeError = 0;
        }else if(strlen(elementos->nameJ2) == 0 && strlen(elementos->nameJ1) > 0)
        {
            isValid = FALSE;
            numMensajeError = 1;
        }else if(strlen(elementos->nameJ2) == 0 && strlen(elementos->nameJ1) == 0)
        {
            isValid = FALSE;
            numMensajeError = 2;
        }else
        {
            if(strcmp(elementos->nameJ1, elementos->nameJ2) == 0)
            {
                isValid = FALSE;
                numMensajeError = 3; 
                
            }else
            {
                for(int i = 0; i < strlen(elementos->nameJ1); i++)
                {
                    if(elementos->nameJ1[i] >= 65 && elementos->nameJ1[i] < 91|| elementos->nameJ1[i] >= 97 && elementos->nameJ1[i] < 123)
                    {
                        lettersCount++;
                        break;
                    }
                }
                for(int i = 0; i < strlen(elementos->nameJ2); i++)
                {
                    if(elementos->nameJ2[i] >= 65 && elementos->nameJ2[i] < 91|| elementos->nameJ2[i] >= 97 && elementos->nameJ2[i] < 123)
                    {
                        lettersCount++;
                        break;
                    }
                }

                if(lettersCount >= 2)
                {
                    isValid = TRUE;
                }else
                {
                    isValid = FALSE;
                    numMensajeError = 4;
                }
            }
        }
    }else if(elementos->gameMode == 0)
    {
        if(strlen(elementos->nameJ1) == 0)
        {
            isValid = FALSE;
            numMensajeError = 0;
        }else if(strcmp(elementos->nameJ1, "CPU") == 0)
        {
            isValid = FALSE;
            numMensajeError = 4; 
        }else
        {
            for(int i = 0; i < strlen(elementos->nameJ1); i++)
            {
                if(elementos->nameJ1[i] >= 65 && elementos->nameJ1[i] < 91|| elementos->nameJ1[i] >= 97 && elementos->nameJ1[i] < 123)
                {
                    lettersCount++;
                }
            } 
            if(lettersCount >= 1)
            {
                isValid = TRUE;
            }else
            {
                isValid = FALSE;
                numMensajeError = 4;
            }
        }
    }
    if(!isValid)
    {
        dialogWarning(elementos, numMensajeError);
    }else
    {
        elementos->nextWindow = TRUE;
        gtk_widget_destroy(elementos->ventana);
        gtk_widget_destroy(elementos->windowFile);
        if(elementos->gameMode == 0)
        {
            jugador1VsCpu(elementos->nameJ1);
        }else if(elementos->gameMode == 1)
        {
            jugador1VsJugador2(elementos->nameJ1, elementos->nameJ2);
        }
    }
} 

//* recibe la informacion de la ventana de elegir nombres
void cancelWindowName(GtkButton *boton, gpointer userData)
{
    WIDGETS *elementos = (WIDGETS *)userData;
    gtk_widget_destroy(elementos->windowFile);
}

//* ventan para mostrar dialogo de error con los nombres
void dialogWarning(WIDGETS *elementos, int numMensajeError)
{
    GtkWidget *windowError, *errorDialog;
    const char *listaMensajesErrores[6] = {"El nombre del Jugador1 NO es VALIDO!\n", "El nombre del Jugador2 NO es VALIDO!\n", 
                            "El nombre de ambos NO son VALIDOS!\n", "Los jugadores NO pueden tener nombre IDENTICOS!!\n", "No se ingreso como MINIMO Una LETRA en los nombres\n", "No pueden tener el mismo nombre la computadora y el jugador\n"};
    gint resp;
    windowError = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    errorDialog = gtk_message_dialog_new(GTK_WINDOW(windowError), GTK_DIALOG_MODAL, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK, listaMensajesErrores[numMensajeError], NULL);
    
    gtk_widget_show_all(errorDialog);
    resp = gtk_dialog_run(GTK_DIALOG(errorDialog));
    if(resp == GTK_RESPONSE_OK)
    {
        gtk_widget_destroy(errorDialog);
    } 
}

//* funcion para llevar la cuneta del timer
gint timer(gpointer data)
{
    WIDGETS *elementos = (WIDGETS *) data;
    elementos->segundos++;
    char timeText[100] = "Tiempo: ";
    char text_res[sizeof(gint) *5 + 1];
    sprintf(text_res, "%d", elementos->segundos);
    strcat(timeText, text_res);
    strcat(timeText, "s");
    gtk_label_set_text(GTK_LABEL(elementos->eTiempo), timeText);
    return 1;
}

//* fucnion para resetear el timer
void restart(WIDGETS *elementos)
{
    g_print("\nentro\n");
    elementos->idTimer = gtk_timeout_add(1000, timer, elementos);
}

//* Crear un juego nuevo 
void crearJuegoNuevo(GtkButton *boton, gpointer userData)
{
    WIDGETS *elementos = (WIDGETS *)userData;
    elementos->nextWindow = TRUE;
    gtk_timeout_remove(elementos->idTimer);
    gtk_widget_destroy(elementos->ventana);
    if(elementos->gameMode == 0)
    {
        jugador1VsCpu(elementos->nameJ1);
    }else
    {
        jugador1VsJugador2(elementos->nameJ1, elementos->nameJ2);
    }
}

//* Ventan de dialogo done mostrar el ganaodr o empate
void dialogWinner(WIDGETS *elementos, int jugador)
{
    GtkWidget *windowError, *errorDialog;
    char mensaje[100] = "Felicidades, gano el jugador ";
    gint resp;
    windowError = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    if(jugador == 0)
    {
        strcat(mensaje, elementos->nameJ1);
        errorDialog = gtk_message_dialog_new(GTK_WINDOW(windowError), GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, mensaje, NULL);
        saveScoreBoard(elementos->nameJ1, elementos->segundos);
    }else if(jugador == 1)
    {
        strcat(mensaje, elementos->nameJ2);
        errorDialog = gtk_message_dialog_new(GTK_WINDOW(windowError), GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, mensaje, NULL);
        saveScoreBoard(elementos->nameJ1, elementos->segundos);
    }else if(jugador == 2)
    {
        strcpy(mensaje, "EMPATARON!!");
        errorDialog = gtk_message_dialog_new(GTK_WINDOW(windowError), GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, mensaje, NULL);
    }
    
    gtk_widget_show_all(errorDialog);
    resp = gtk_dialog_run(GTK_DIALOG(errorDialog));
    
    if(resp == GTK_RESPONSE_OK)
    {
        gtk_widget_destroy(errorDialog);
        elementos->question = 3;
        elementos->segundos = 0;
        if(show_question(elementos))
        {
            crearJuegoNuevo(NULL, elementos); 
        }else
        {
            elementos->nextWindow = TRUE;
            gtk_widget_destroy(elementos->ventana);
            menuPrincipal();
        }
    } 
}

//* Fucnion para extraer los datos del arcivo de scores
void saveScoreBoard(char *nombre, int tiempo)
{
    char datos[20];
    MARCADORES *inicio, *aux;
    FILE *fp;
    char nombreJugador[8];
    int tiempoFinal;
    inicio = NULL;
    
    fp = fopen("scores.txt", "a");
    fprintf(fp, "\n%s %d", nombre, tiempo);
    fclose(fp);


    fp = fopen("scores.txt", "r");
    while(fgets(datos, 20, fp) != NULL)
    {
        sscanf(datos, "%s %d", nombreJugador, &tiempoFinal);
        create_list(&inicio, &aux, nombreJugador, tiempoFinal);
    }
    fclose(fp);
    ordenarMarcadores(inicio);
    reescribir_archivo(inicio);
    liberarMemorial(inicio);
}

//* Crea una lista dinamica
void create_list(MARCADORES **inicio, MARCADORES **aux, char *nombre, int tiempo)
{
    MARCADORES *nodo;
    nodo = malloc(sizeof(MARCADORES));
    if(nodo == NULL)
    {
        printf("ERROR: No hay memoria disponible\n");
        exit(1);
    }


    nodo->nombre =  strdup(nombre);
    nodo->tiempoFinal = tiempo;
    if(*inicio == NULL)
    {
        *inicio = nodo;
    }else
    {
        (*aux) -> sig = nodo;

    }
    (*aux) = nodo;
    nodo -> sig = NULL;

}

//* Ordena la lista dinamica de menor a mayor
void ordenarMarcadores(MARCADORES *incio)
{
    MARCADORES *nodo, *nodo2;

    char *temp;
    int num_temp;

    nodo = incio;
    nodo2 = nodo -> sig;

    do
    {

        while (nodo2 != NULL)
        {
            if(nodo -> tiempoFinal > nodo2 -> tiempoFinal)
            {
                temp = nodo -> nombre;
                num_temp = nodo -> tiempoFinal;

                nodo -> nombre = nodo2 -> nombre;
                nodo -> tiempoFinal = nodo2 -> tiempoFinal;

                nodo2 -> tiempoFinal = num_temp;
                nodo2 -> nombre = temp;
            }
            nodo2 = nodo2 -> sig;
        }

        nodo = nodo -> sig;
        if(nodo != NULL)
        {
            nodo2 = nodo -> sig;
        }
        
    }while(nodo != NULL);
    
}


//* Rescribe el archivo de marcaodres guardadno solo los 5 primero lugares de la lista
void reescribir_archivo(MARCADORES *inicio)
{
    MARCADORES *nodo;
    FILE *fp;
    int count = 0;
    fp = fopen("scores.txt", "w");

    nodo = inicio;
    while (nodo != NULL)
    {
        if(count == 5)
        {
            break;
        }
        fprintf(fp, "%s %d\n", nodo->nombre, nodo->tiempoFinal);
        g_print("%s %d\n", nodo->nombre, nodo->tiempoFinal);
        nodo = nodo -> sig;
        count++;
    }
    fclose(fp);
}

//* Libera la memoria de l alista dinamica
void liberarMemorial(MARCADORES *inicio)
{
    MARCADORES *nodo;
    nodo = inicio;
    while (nodo != NULL)
    {
        inicio = nodo->sig;
        free(nodo);
        nodo = inicio;
    }
    g_print("fin");
}

//* Ventena de ayuda
void ayuda(GtkButton *boton, gpointer userData) {
    
    WIDGETS *elementos = (WIDGETS *)userData;
    if(elementos->start){
        gtk_timeout_remove(elementos->idTimer);
    }
    GtkWidget *dialog, *window;
    gint resp;
    char message[700] = "El cronometro comenzara a correr hasta que se realice el primer movimiento, seleccionando alguno de los botones en tu tablero.\n\n\t\u2022Si el boton seleccionado revela el color azul, quiere decir que no has hundido uno de los barcos de tu oponente, por lo que sera turno de que CPU o el Jugador 2 haga un tiro.\n\n\t\u2022Si el boton seleccionado revela el color rojo, quiere decir que has hundido un barco de tu oponente, por lo que podras tirar una vez mas.\n\nQuien primero hunde 10 barcos de su oponente, habrá ganado la partida.";
    
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    dialog = gtk_message_dialog_new(GTK_WINDOW(window), GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, message, NULL);
    gtk_window_set_title(GTK_WINDOW(dialog), "AYUDA");
    
    resp = gtk_dialog_run(GTK_DIALOG(dialog));
    g_print("%d", resp);
    g_print("\nnel\n");
    if(resp == GTK_RESPONSE_OK)
    {
        g_print("yes\n");
        gtk_widget_destroy(dialog);
        if(elementos->start)
        {
            restart(elementos);
        }
    }
}
//! FIN ---> Funciones Genearles
