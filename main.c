
///les biblioth�que
#include <gtk/gtk.h>
#include <gdk/gdk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

///les constante
#define NBC 100
#define NB_RADIO 3

///les biblioth�que des widget
#include "window.h"
#include "boutton_normal.h"
#include "cocher.h"
#include "radio.h"
#include "spin_button.h"
#include "onglet.h"

#include "prog_bar.h"
#include "image.h"
#include "label.h"
#include "frame.h"
#include "scrollbar.h"
#include "tool_bar.h"
GtkWidget *create_fixed()
{
    GtkFixed *fixed = GTK_FIXED(gtk_fixed_new());
    return ((GtkWidget*)fixed);
}



int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);
    GtkWidget *notebook = gtk_notebook_new();
    Fenetre* ma_fenetre = add_window();
    GtkWidget* fixed = create_fixed();///les bouttons (is finished)
    GtkWidget* fixed1 = create_fixed();///fiha le menu bohdo db
    GtkWidget* fixed2 = create_fixed();///khawya
    GtkWidget* fixed3 = create_fixed();///khawya
    GtkWidget* fixed4 = create_fixed();///khawya


/****************************************************** les bouttons***********************************/

/// les parametres : le fixed , le label du button , mnemonique ou non (par defaut on prend premier lettre du label, x , y , path de l'image utiliser (NULL s'il y a pas d'image)
    add_button(fixed,"first",NULL,100,100,"#FF0000",0,100);
    add_button(fixed,"second",NULL,100,100,NULL,100,100);
    add_button(fixed,NULL,"gtklogo.png",100,100,"#FF0000",200,100);
    add_button(fixed,NULL,"gtklogo.png",100,100,NULL,350,100);
    add_button(fixed,"fifth","gtklogo.png",100,100,"#FF00FF",470,100);

/// les parametres : le fixed , le label , le x , le y ,le bgcolor, si le checkbox est cocher d�s le d�but ou non
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


/// les parametres : le fixed  , le x , le y , les labels,le bgcolor de chaque button, le radio qui soit cocher d�s le d�but (all FALSE signifie que aucun ne sera cocher)
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
//    add_onglet(notebook,fixed,"onglet 1");
/***********************************************les bouttons fin*****************************************/


    add_progress_bar(fixed1,2.3,1.0,1000,500,1,250,250);
    add_image(fixed1,1,"gtklogo.png",GTK_ICON_SIZE_BUTTON,100,100,250,250);
    add_onglet(notebook,fixed1,"onglet 2");///pour ajouter le fixed dans l'onglet (tqdr dir bo wla tableau wla contenair, ay widget)

    texte* txt=initialiser_texte(20,30,"izenfoizfn",NULL,NULL,25,NULL,NULL,"red","#00FF00",NULL);
    add_label(fixed2,txt,TRUE,FALSE,350,350);
    add_onglet(notebook,fixed2,"onglet 3");///pour ajouter le fixed dans l'onglet (tqdr dir bo wla tableau wla contenair, ay widget)
    frame* frm=add_frame(fixed3,0.5,1.0,txt,NULL,GTK_SHADOW_IN,540,0);
    gtk_container_add(GTK_CONTAINER(frm->widget),fixed);
    add_onglet(notebook,fixed3,"onglet 4");///pour ajouter le fixed dans l'onglet (tqdr dir bo wla tableau wla contenair, ay widget)




    ///matqissch hadchi li mor had lcomment
    add_to_window(notebook,ma_fenetre->window);
    gtk_widget_show_all(ma_fenetre->window);
    g_signal_connect(G_OBJECT(ma_fenetre->window), "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_main();

    return 0;
}



