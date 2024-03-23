#ifndef HEADERS_H_INCLUDED
#define HEADERS_H_INCLUDED


///les bibliothèque
#include <gtk/gtk.h>
#include <gdk/gdk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

///les constante
#define NBC 100
#define NB_RADIO 3

///les bibliothèque des widget

#include "boutton_normal.h"
#include "cocher.h"
#include "radio.h"
#include "spin_button.h"



//#include "prog_bar.h"
#include "label.h"
//#include "frame.h"
//#include "scrollbar.h"
//#include "tool_bar.h"


//#include "boite_dialog.h"
//#include "entry.h"
//
//
//#include "menu.h"
#include "window.h"
#include "onglet.h"
#include "fixed.h"
#include "ex_buttons.h"

void debut_programme(int argc,char*argv[]){
    gtk_init(&argc,&argv);
}

void fin_programme(Fenetre* ma_fenetre)
{
    g_signal_connect(G_OBJECT(ma_fenetre->window), "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_main();
}

#endif // HEADERS_H_INCLUDED
