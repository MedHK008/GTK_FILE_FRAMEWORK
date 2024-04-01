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


#include "combobox.h"
#include "prog_bar.h"
#include "label.h"
#include "frame.h"
//#include "scrollbar.h"
#include "tool_bar.h"
//#include "image.h"
#include "boite_dialog.h"
#include "entry.h"
//
//
#include "menu.h"
#include "window.h"
#include "onglet.h"
#include "reader.h"
#include "fixed.h"

#include "ex_buttons.h"
void load_css() {
    GtkCssProvider *provider = gtk_css_provider_new();
    GdkDisplay *display = gdk_display_get_default();
    GdkScreen *screen = gdk_display_get_default_screen(display);
    GError *error = NULL;

    if (!gtk_css_provider_load_from_path(provider, "style_win.css", &error)) {
        g_warning("Failed to load CSS file: %s", error->message);
        g_error_free(error);
        return;
    }
    gtk_style_context_add_provider_for_screen(screen, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    g_object_unref(provider);
}

void debut_programme(int argc,char*argv[]){
    gtk_init(&argc,&argv);
}

void fin_programme(Fenetre* ma_fenetre)
{
    g_signal_connect(G_OBJECT(ma_fenetre->window), "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_main();
}




#endif // HEADERS_H_INCLUDED
