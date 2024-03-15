
///les bibliothèque
#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


///les constante
#define NBC 100


///les bibliothèque des widget
#include "menu.h"
#include "window.h"
#include "boutton_normal.h"
#include "cocher.h"
#include "radio.h"
#include "spin_button.h"
#include "onglet.h"
#include "tool_bar.h"


GtkWidget *create_fixed()
{
    GtkFixed *fixed = GTK_FIXED(gtk_fixed_new());
    return ((GtkWidget*)fixed);
}

Fenetre* add_window()
{
    Fenetre *ma_fenetre = initialiser_win("Instagram", NULL, "F1", "#f72585", 500, 500, 2, 0, 0, 25, TRUE);
    create_window(ma_fenetre);
    return((Fenetre*)ma_fenetre);
}

void add_fixed_in_onglet()
{

}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);
    Fenetre* ma_fenetre = add_window();
    GtkWidget* fixed = create_fixed();
    GtkWidget* fixed1 = create_fixed();

    add_button(fixed,50,50,"Click Me", FALSE,10,50,"image.png");


    add_cocher(fixed);
    add_radio(fixed);
    add_spin(fixed);
    add_menu(fixed1);
    add_onglet(ma_fenetre->window,fixed,fixed1,"one","two");


    gtk_widget_show_all(ma_fenetre->window);
    gtk_main();

    return 0;
}



