
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
#include "menu.h"
#include "window.h"
#include "boutton_normal.h"
#include "cocher.h"
#include "radio.h"
#include "spin_button.h"
#include "onglet.h"
#include "tool_bar.h"


int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);
    GtkWidget *notebook = gtk_notebook_new();
    Fenetre* ma_fenetre = add_window();
    GtkWidget* fixed = create_fixed();///les bouttons (is finished)
    GtkWidget* fixed1 = create_fixed();///fiha le menu bohdo db
    GtkWidget* fixed2 = create_fixed();///khawya
    GtkWidget* fixed3 = create_fixed();///khawya


/****************************************************** les bouttons***********************************/

/// les parametres : le fixed , le label du button , mnemonique ou non (par defaut on prend premier lettre du label, x , y , path de l'image utiliser (NULL s'il y a pas d'image)
    add_button(fixed, 0, 50, "Click Me", FALSE, 100, 50, "image.png");
    add_button(fixed, 100, 50, "", FALSE, 100, 50, NULL);
    add_button(fixed, 200, 50, "don't click me", FALSE, 100, 50, NULL);
    add_button(fixed, 300, 50, "", FALSE, 100, 50, "image.png");

/// les parametres : le fixed , le label , le x , le y ,le bgcolor, si le checkbox est cocher dès le début ou non
    add_cocher(fixed,"testing cocher1",0,300,"#000000",TRUE);
    add_cocher(fixed,"testing cocher2",0,330,"#FFFFFF",FALSE);
    add_cocher(fixed,"testing cocher3",0,360,"#00FF00",TRUE);
    add_cocher(fixed,"testing cocher4",0,390,"#FF0000",FALSE);

    add_cocher(fixed,"testing cocher1",200,300,"#FFFFFF",TRUE);
    add_cocher(fixed,"testing cocher2",200,330,"#FFFFFF",TRUE);
    add_cocher(fixed,"testing cocher3",200,360,"#FFFFFF",TRUE);
    add_cocher(fixed,"testing cocher4",200,390,"#FFFFFF",TRUE);

    add_cocher(fixed,"testing cocher1",400,300,"#000000",FALSE);
    add_cocher(fixed,"testing cocher2",400,330,"#000000",FALSE);
    add_cocher(fixed,"testing cocher3",400,360,"#000000",FALSE);
    add_cocher(fixed,"testing cocher4",400,390,"#000000",FALSE);


/// les parametres : le fixed  , le x , le y , les labels,le bgcolor de chaque button, le radio qui soit cocher dès le début (all FALSE signifie que aucun ne sera cocher)
    char *labels1[NB_RADIO] = {"Option 1", "Option 2", "Option 3"};
    char *colors1[NB_RADIO] = {"#FF0000", "#00FF00", "#0000FF"};
    gboolean checked1[NB_RADIO] = {FALSE, TRUE, FALSE};
    add_radio(fixed, NB_RADIO,0,600, labels1, colors1,checked1);


    char *labels2[NB_RADIO] = {"Option 1", "Option 2", "Option 3"};
    char *colors2[NB_RADIO] = {"#FFFFFF", "#FFFFFF", "#FFFFFF"};
    gboolean checked2[NB_RADIO] = {FALSE, FALSE, FALSE};
    add_radio(fixed, NB_RADIO,200,600, labels2, colors2,checked2);

    char *labels3[NB_RADIO] = {"Option 1", "Option 2", "Option 3"};
    char *colors3[NB_RADIO] = {"#000000", "#000000", "#000000"};
    gboolean checked3[NB_RADIO] = {FALSE, FALSE, TRUE};
    add_radio(fixed, NB_RADIO,400,600, labels3, colors3,checked3);

///khdem biha wskot mafiya li ykteb lcommentaire db
    add_spin(fixed, 0, 800, 0.0, 100.0, 1.0, 1.0, 30, 150, 1, 2, 1, 1, "#00ff00", 1.0);
    add_spin(fixed, 200, 800, 0.0, 100.0, 50.0, 5.0, 30, 30, 1, 2, 1, 1, "#ff0000", 1.0);
    add_spin(fixed, 400, 800, 0.0, 100.0, 100.0, 100.0, 50, 150, 1, 2, 1, 1, "#ffffff", 1.0);

    add_onglet(notebook,fixed,"onglet 1");
/***********************************************les bouttons fin*****************************************/


///le menu
    add_menu(fixed1);
    add_onglet(notebook,fixed1,"onglet 2");///pour ajouter le fixed dans l'onglet (tqdr dir bo wla tableau wla contenair, ay widget)



    ///matqissch hadchi li mor had lcomment
    add_to_window(notebook,ma_fenetre->window);
    gtk_widget_show_all(ma_fenetre->window);
    g_signal_connect(G_OBJECT(ma_fenetre->window), "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_main();

    return 0;
}



