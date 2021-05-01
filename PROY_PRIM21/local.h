#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <string.h>
#include <time.h>
#include <strings.h>


typedef struct widgets
{
    GtkWidget *botones[2];
    GtkWidget *ventana;
    GtkWidget *tb1;
    GtkWidget *tb2;
    GtkWidget *bAtras;
    GtkWidget *bAdelante;
    GtkWidget *botonesTb1[7][7];
    GtkWidget *botonesTb2[7][7];
    GtkWidget *deshacer;
    GtkWidget *rehacer;
    GtkWidget *guardar; 
    GtkWidget *guardarNuevoArchivo;
    GtkWidget *windowFile;
    GtkWidget *entryFileName;
    GtkWidget *entryJugar1Name;
    GtkWidget *entryJugar2Name;
    GtkWidget *windowChoose;
    GtkWidget *eJugador1;
    GtkWidget *eJugador2;
    GtkWidget *statusBar;
    GtkWidget *eTiempo;
    GList *list;
    gboolean remove;
    gboolean turnoJ1;
    gboolean turnoJ2; 
    gboolean nextWindow;
    gboolean saveNewFile;
    gboolean saveAndQuit;
    gint segundos;
    int idTimer;
    int tirosJ1;
    int tirosJ2;
    int tirosTotalJ1;
    int tirosTotalJ2;
    int tirosTotal; 
    int question;
    char *seleccionJ1[10];
    char *seleccionJ2[10];
    int numAtras;
    char *fileName;
    char *nameJ1;
    char *nameJ2;

    
}WIDGETS;







