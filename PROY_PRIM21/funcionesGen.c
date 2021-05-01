#include "local.h"

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

extern void menuPrincipal(void);
extern void jugador1VsJugador2(char *nombreJ1, char *nombreJ2);


//! INICION ---> Funciones Genearles
gboolean delete_event_handler(GtkWidget *widget, gpointer userData)
{
    g_print("En delete_event_handler.\n");
    return FALSE;
}

void salir(GtkWidget *widget, gpointer userData)
{
    WIDGETS *elementos = (WIDGETS *)userData;

     
    if(!elementos->nextWindow) 
    {
        g_print("Click en salir\n");
        g_list_free(elementos->list);
        gtk_main_quit();
    }
    g_print("sip\n");
}

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


void cancel(GtkButton *boton, gpointer userData)
{
    WIDGETS *elementos = (WIDGETS *)userData;
    gtk_widget_destroy(elementos->windowFile);
    restart(elementos);
}


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
        
        if(fp == NULL)
        {
            g_print("si paso\n");
        }else
        {
            fclose(fp);
            g_print("2si paso\n");
            if(!show_question(elementos))
            {
                gtk_widget_destroy(elementos->windowFile);
                restart(elementos);
                return;
            }
            g_print("si paso\n");
        }
        
        g_print("si paso\n");

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
    fprintf(fp, "%s", "*T\n");

    fclose(fp);

    if(elementos->saveNewFile)
    {
       gtk_widget_destroy(elementos->windowFile);
    }
    restart(elementos);
    
}


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
        g_print("aaaa\n");
        resp = gtk_dialog_run(GTK_DIALOG(dialog));
        if(resp == GTK_RESPONSE_OK)
        {
            g_print("R: %d\n", resp);
            elementos-> fileName = strdup(gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog)));
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
        restart(elementos);
    }
    gtk_statusbar_push(GTK_STATUSBAR(elementos->statusBar), 0, "Esperando al siguiente tiro");
   
}

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
    g_print("NN: %s--->%c", nombre, nombre[strlen(nombre) - 1]);

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
    
    if(elementos->numAtras == 0)
    {
      gtk_widget_set_sensitive(GTK_WIDGET(boton), FALSE);  
    }
}

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
    g_print("%s|\n%s|", name, gtk_widget_get_name(elementos->botonesTb1[6][6]));
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
        if(elementos->turnoJ1)
        {
            g_print("\nssss\n");
            gtk_widget_set_sensitive(GTK_WIDGET(elementos->tb1), TRUE);
        }else if(elementos->turnoJ2)
        {
            g_print("\nhhhhh\n");
            gtk_widget_set_sensitive(GTK_WIDGET(elementos->tb2), TRUE);
        }
        restart(elementos);
    }
}



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
    if(elementos->turnoJ1)
    {
        gtk_widget_set_sensitive(GTK_WIDGET(elementos->tb1), TRUE);
        
    }else if(elementos->turnoJ2)
    {
        gtk_widget_set_sensitive(GTK_WIDGET(elementos->tb2), TRUE);
    }
    restart(elementos);
    g_print("\nnumA ---> %d\n", elementos->numAtras);
}



void backToMenu(GtkButton *boton, gpointer userData)
{
    WIDGETS *elementos = (WIDGETS *)userData; 
    elementos->nextWindow = TRUE;
    gtk_widget_destroy(elementos->ventana);
    menuPrincipal();
}


void ventanaAcercaDe(GtkButton *boton, gpointer userData)
{
    WIDGETS *elementos = (WIDGETS *)userData;
    GtkWidget *window2;
    const char *author[] = {"Sebastian Sedano", "Mauricio Olguín", "Santiago Zamora", '\0'};
    gtk_timeout_remove(elementos->idTimer);
    window2 = gtk_about_dialog_new();
    
    gtk_window_set_default_size(GTK_WINDOW(window2), 300, 300);
    gtk_about_dialog_set_name(GTK_ABOUT_DIALOG(window2), "Batalla Naval");
    gtk_about_dialog_set_comments(GTK_ABOUT_DIALOG(window2), "Version 3.1");
    gtk_about_dialog_set_authors(GTK_ABOUT_DIALOG(window2), author);
    gtk_about_dialog_set_artists(GTK_ABOUT_DIALOG(window2), author);
    gtk_about_dialog_set_documenters(GTK_ABOUT_DIALOG(window2), author);
    gtk_about_dialog_set_copyright(GTK_ABOUT_DIALOG(window2), "Copyright");
    

    g_signal_connect_swapped(G_OBJECT(window2), "response", G_CALLBACK(gtk_widget_destroy), window2);

    gtk_widget_show_all(window2);
    gtk_window_set_modal(GTK_WINDOW(window2), TRUE);
    restart(elementos);
}


void barcosPosition(GtkWidget *botones[7][7], GtkWidget *botonesJ2[7][7], WIDGETS *elementos)
{
    const char *nombreSelecciones[20] = {"X0", "X1", "X2", "X3", "X4", "X5", "X6", "X7", "X8", "X9", 
                                    "Z0", "Z1", "Z2", "Z3", "Z4", "Z5", "Z6", "Z7", "Z8", "Z9"};
    char *nombre;
    srand(time(0));
    int x, y;
    for(int i = 0; i < 20; i++)
    {
        x = rand() %6;
        y = rand() %6;
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
                    x = rand() %6;
                    y = rand() %6;
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
                    x = rand() %6;
                    y = rand() %6; 
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


gboolean show_question(WIDGETS *elementos) {
    
  GtkWidget *dialog, *window;
  gint resp;

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  dialog = gtk_message_dialog_new(GTK_WINDOW(window),
            GTK_DIALOG_DESTROY_WITH_PARENT,
            GTK_MESSAGE_QUESTION,
            GTK_BUTTONS_OK_CANCEL,
            "Seguro quieres rescribir el archivo?, se perederan todos los datos actuales!!");
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
        if(renglon < 28 || saveTemp[0] == 'X' || saveTemp[0] == 'Z')
        {
            ordenar(elementos, saveTemp, renglon);
        }else
        {
            if(saveTemp[strlen(saveTemp) - 2] == 'T')
            {
                cambiarNombre(saveTemp);
                elementos->segundos = atoi(saveTemp);
                strcat(textTime, saveTemp);
                strcat(textTime, "s");
                gtk_label_set_text(GTK_LABEL(elementos->eTiempo), textTime);
            }else
            {
                arreglarHistorial(saveTemp);
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


void ordenar(WIDGETS *elementos, char *dato, int renglon)
{
    int index;
    gboolean notFound = FALSE;
    char *realName;
    char *nameComp;
    arreglarHistorial(dato);
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
            if(strcmp("J1", dato) == 0)
            {
                elementos->turnoJ1 = TRUE;
                elementos->turnoJ2 = FALSE;
                g_print("\n1\n");
            }else if(strcmp("J2", dato) == 0)
            {
                elementos->turnoJ1 = FALSE;
                elementos->turnoJ2 = TRUE;
                g_print("\n2\n");
            }
            break;

        default:
            break;
        }

        if(renglon >= 8 && renglon <= 18)
        {
            elementos->seleccionJ1[renglon - 8] = strdup(dato);
        }else if(renglon >= 19 && renglon <= 28)
        {
            elementos->seleccionJ2[renglon - 19] = strdup(dato);
        }

    }else
    {
        
        if(dato[0] == 'X')
        {
            index = dato[1] - '0';
            realName = strdup(elementos->seleccionJ1[index]);
            arreglarHistorial(realName);
            arreglarHistorial(dato);
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
    gtk_box_pack_start(GTK_BOX(cajaH2), etiquetaJ2, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(cajaH2), elementos->entryJugar2Name, TRUE, TRUE, 5);
    gtk_box_pack_start(GTK_BOX(cajaV), cajaH2, FALSE, FALSE, 0); 
    gtk_box_pack_start(GTK_BOX(cajaH3), aceptar, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(cajaH3), cancelar, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(cajaV), cajaH3, FALSE, FALSE, 0);
    gtk_container_add(GTK_CONTAINER(windowNames), cajaV);
    gtk_widget_show_all(windowNames); 
}


void saveNames(GtkButton *boton, gpointer userData)
{
    WIDGETS *elementos = (WIDGETS *)userData;
    elementos->nameJ1 = strdup(gtk_entry_get_text(GTK_ENTRY(elementos->entryJugar1Name)));
    elementos->nameJ2 = strdup(gtk_entry_get_text(GTK_ENTRY(elementos->entryJugar2Name)));
    int numMensajeError;
    int lettersCount = 0;
    gboolean isValid = TRUE;
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
                }
            }
            for(int i = 0; i < strlen(elementos->nameJ2); i++)
            {
                if(elementos->nameJ2[i] >= 65 && elementos->nameJ2[i] < 91|| elementos->nameJ2[i] >= 97 && elementos->nameJ2[i] < 123)
                {
                    lettersCount++;
                    g_print(" -R++ %d\n", elementos->nameJ2[i]);
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


    if(!isValid)
    {
        dialogWarning(elementos, numMensajeError);
    }else
    {
        elementos->nextWindow = TRUE;
        gtk_widget_destroy(elementos->ventana);
        gtk_widget_destroy(elementos->windowFile);
        jugador1VsJugador2(elementos->nameJ1, elementos->nameJ2);
    }
} 

void cancelWindowName(GtkButton *boton, gpointer userData)
{
    WIDGETS *elementos = (WIDGETS *)userData;
    gtk_widget_destroy(elementos->windowFile);
}

void dialogWarning(WIDGETS *elementos, int numMensajeError)
{
    GtkWidget *windowError, *errorDialog;
    const char *listaMensajesErrores[5] = {"El nombre del Jugador1 NO es VALIDO!\n", "El nombre del Jugador2 NO es VALIDO!\n", 
                            "El nombre de ambos NO son VALIDOS!\n", "Los jugadores NO pueden tener nombre IDENTICOS!!\n", "No se ingreso como MINIMO Una LETRA en los nombres\n"};
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

void restart(WIDGETS *elementos)
{
    g_print("\nentro\n");
    elementos->idTimer = gtk_timeout_add(1000, timer, elementos);
}
//! FIN ---> Funciones Genearles
