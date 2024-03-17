
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
#include "window.h"
#include "boutton_normal.h"
#include "cocher.h"
#include "radio.h"
#include "spin_button.h"
#include "onglet.h"

#include "prog_bar.h"
#include "label.h"
#include "frame.h"
#include "scrollbar.h"
#include "tool_bar.h"


#include "boite_dialog.h"
#include "entry.h"


GtkWidget *create_fixed()
{

    GtkFixed *fixed = GTK_FIXED(gtk_fixed_new());
    return ((GtkWidget*)fixed);
}

void debut(int argc,char*argv[]){
    gtk_init(&argc,&argv);
}


int main(int argc, char *argv[]) {
    debut(argc,argv);
    GtkWidget *notebook = gtk_notebook_new();
    Fenetre* ma_fenetre = add_window();
    GtkWidget* fixed = create_fixed();///les bouttons (is finished)
    GtkWidget* fixed1 = create_fixed();///fiha le menu bohdo db
    GtkWidget* fixed2 = create_fixed();///khawya
    GtkWidget* fixed3 = create_fixed();///khawya
    GtkWidget* fixed4 = create_fixed();///khawya
    texte* txt=initialiser_texte(20,30,"exemple frame",NULL,NULL,25,NULL,NULL,"red","#00FF00",NULL);
    texte* txt_button=initialiser_texte(20,30,"exemple des boutons",NULL,NULL,25,NULL,NULL,"red","#00FF00",NULL);
    texte* txt_cocher=initialiser_texte(20,30,"exemple des bouttons a cocher",NULL,NULL,25,NULL,NULL,"green","#00FF00",NULL);
    texte* txt_radio=initialiser_texte(20,30,"exemple des bouttons radio",NULL,NULL,25,NULL,NULL,"red","#00FF00",NULL);
    texte* txt_spin=initialiser_texte(20,30,"exemple boutton spin",NULL,NULL,25,NULL,NULL,"red","#00FF00",NULL);



/****************************************************** les bouttons***********************************/
    add_label(fixed,txt_button,TRUE,FALSE,50,50);
/// les parametres : le fixed , le label du button , path de l'image utiliser (NULL s'il y a pas d'image),height,width,bgcolor, x , y
    add_button(fixed,"first","gtklogo.png",100,100,"#FF0000",50,100,50,50);
//    add_button(fixed,"second",NULL,100,100,NULL,170,100);
    add_button(fixed,NULL,"gtklogo.png",100,100,"#FF0000",290,100,150,150);
//    add_button(fixed,NULL,"gtklogo.png",100,100,NULL,430,100);
//    add_button(fixed,"fifth","gtklogo.png",100,100,"#FF00FF",570,100);

    add_label(fixed,txt_cocher,TRUE,FALSE,50,250);
/// les parametres : le fixed , le label , le x , le y ,le bgcolor, si le checkbox est cocher dès le début ou non
    add_cocher(fixed,"testing cocher1",50,300,"#000000",TRUE);
    add_cocher(fixed,"testing cocher2",50,330,"#FFFFFF",FALSE);
    add_cocher(fixed,"testing cocher3",50,360,"#00FF00",TRUE);
    add_cocher(fixed,"testing cocher4",50,390,"#FF0000",FALSE);

    add_cocher(fixed,"testing cocher1",200,300,"#FFFFFF",TRUE);
    add_cocher(fixed,"testing cocher2",200,330,"#FFFFFF",TRUE);
    add_cocher(fixed,"testing cocher3",200,360,"#FFFFFF",TRUE);
    add_cocher(fixed,"testing cocher4",200,390,"#FFFFFF",TRUE);

    add_cocher(fixed,"testing cocher1",400,300,"#000000",FALSE);
    add_cocher(fixed,"testing cocher2",400,330,"#000000",FALSE);
    add_cocher(fixed,"testing cocher3",400,360,"#000000",FALSE);
    add_cocher(fixed,"testing cocher4",400,390,"#000000",FALSE);


    add_label(fixed,txt_radio,TRUE,FALSE,50,450);
/// les parametres : le fixed  , le x , le y , les labels,le bgcolor de chaque button, le radio qui soit cocher dès le début (all FALSE signifie que aucun ne sera cocher)
    char *labels1[NB_RADIO] = {"Option 1", "Option 2", "Option 3"};
    char *colors1[NB_RADIO] = {"#FF0000", "#00FF00", "#0000FF"};
    gboolean checked1[NB_RADIO] = {FALSE, TRUE, FALSE};
    add_radio(fixed, NB_RADIO,50,500, labels1, colors1,checked1);


    char *labels2[NB_RADIO] = {"Option 1", "Option 2", "Option 3"};
    char *colors2[NB_RADIO] = {"#FFFFFF", "#FFFFFF", "#FFFFFF"};
    gboolean checked2[NB_RADIO] = {FALSE, FALSE, FALSE};
    add_radio(fixed, NB_RADIO,250,500, labels2, colors2,checked2);

    char *labels3[NB_RADIO] = {"Option 1", "Option 2", "Option 3"};
    char *colors3[NB_RADIO] = {"#000000", "#000000", "#000000"};
    gboolean checked3[NB_RADIO] = {FALSE, FALSE, TRUE};
    add_radio(fixed, NB_RADIO,450,500, labels3, colors3,checked3);

    add_label(fixed,txt_spin,TRUE,FALSE,50,600);
///khdem biha wskot mafiya li ykteb lcommentaire db
    add_spin(fixed, 50, 650, 0.0, 100.0, 1.0, 1.0, 30, 150, 1, 2, 1, 1, "#00ff00", 1.0);
    add_spin(fixed, 250, 650, 0.0, 100.0, 50.0, 5.0, 30, 30, 1, 2, 1, 1, "#ff0000", 1.0);
    add_spin(fixed, 450, 650, 0.0, 100.0, 100.0, 100.0, 50, 150, 1, 2, 1, 1, "#ffffff", 1.0);
    add_onglet(notebook,fixed,"onglet 1","#FF00FF");
/***********************************************les bouttons fin*****************************************/


    add_progress_bar(fixed1,2.3,1.0,1000,500,1,250,250);
    add_image(fixed1,1,"gtklogo.png",GTK_ICON_SIZE_BUTTON,50,50,250,250);
    add_onglet(notebook,fixed1,"onglet 2","#00FFFF");///pour ajouter le fixed dans l'onglet (tqdr dir bo wla tableau wla contenair, ay widget)

    add_label(fixed2,txt,TRUE,FALSE,350,350);
    add_onglet(notebook,fixed2,"onglet 3","#FFFF00");///pour ajouter le fixed dans l'onglet (tqdr dir bo wla tableau wla contenair, ay widget)

/*************************************frame example******************************************************************/
//    add_button(fixed3,"first",NULL,100,100,"#FF0000",0,100);
//    add_button(fixed3,"second",NULL,100,100,NULL,100,100);
//    add_button(fixed3,NULL,"gtklogo.png",100,100,"#FF0000",200,100);
//    add_button(fixed3,NULL,"gtklogo.png",100,100,NULL,350,100);
//    add_button(fixed3,"fifth","gtklogo.png",100,100,"#FF00FF",470,100);
    add_cocher(fixed3,"testing cocher1",0,300,"#000000",TRUE);
    add_cocher(fixed3,"testing cocher2",0,330,"#FFFFFF",FALSE);
    add_cocher(fixed3,"testing cocher3",0,360,"#00FF00",TRUE);
    add_cocher(fixed3,"testing cocher4",0,390,"#FF0000",FALSE);
    add_cocher(fixed3,"testing cocher1",200,300,"#FFFFFF",TRUE);
    add_cocher(fixed3,"testing cocher2",200,330,"#FFFFFF",TRUE);
    add_cocher(fixed3,"testing cocher3",200,360,"#FFFFFF",TRUE);
    add_cocher(fixed3,"testing cocher4",200,390,"#FFFFFF",TRUE);
    add_cocher(fixed3,"testing cocher1",400,300,"#000000",FALSE);
    add_cocher(fixed3,"testing cocher2",400,330,"#000000",FALSE);
    add_cocher(fixed3,"testing cocher3",400,360,"#000000",FALSE);
    add_cocher(fixed3,"testing cocher4",400,390,"#000000",FALSE);
    char *labels4[NB_RADIO] = {"Option 1", "Option 2", "Option 3"};
    char *colors4[NB_RADIO] = {"#FF0000", "#00FF00", "#0000FF"};
    gboolean checked4[NB_RADIO] = {FALSE, TRUE, FALSE};
    add_radio(fixed3, NB_RADIO,0,600, labels4, colors4,checked4);
    char *labels5[NB_RADIO] = {"Option 1", "Option 2", "Option 3"};
    char *colors5[NB_RADIO] = {"#FFFFFF", "#FFFFFF", "#FFFFFF"};
    gboolean checked5[NB_RADIO] = {FALSE, FALSE, FALSE};
    add_radio(fixed3, NB_RADIO,200,600, labels5, colors5,checked5);
    char *labels6[NB_RADIO] = {"Option 1", "Option 2", "Option 3"};
    char *colors6[NB_RADIO] = {"#000000", "#000000", "#000000"};
    gboolean checked6[NB_RADIO] = {FALSE, FALSE, TRUE};
    add_radio(fixed3, NB_RADIO,400,600, labels6, colors6,checked6);
    add_spin(fixed3, 0, 800, 0.0, 100.0, 1.0, 1.0, 30, 150, 1, 2, 1, 1, "#00ff00", 1.0);
    add_spin(fixed3, 200, 800, 0.0, 100.0, 50.0, 5.0, 30, 30, 1, 2, 1, 1, "#ff0000", 1.0);
    add_spin(fixed3, 400, 800, 0.0, 100.0, 100.0, 100.0, 50, 150, 1, 2, 1, 1, "#ffffff", 1.0);

    frame* frm=add_frame(fixed,0.5,1.0,txt,NULL,GTK_SHADOW_IN,800,0);
    gtk_container_add(GTK_CONTAINER(frm->widget),fixed3);


    Add_Entry(fixed4,"azerty",50,0,1,"A","a",200,50,1,"#FFFFFF",500,500);
    add_onglet(notebook,fixed4,"onglet4","#0000FF");

/*************************************frame example fin******************************************************************/




    ///matqissch hadchi li mor had lcomment
    add_to_window(notebook,ma_fenetre->window);
    gtk_widget_show_all(ma_fenetre->window);
    g_signal_connect(G_OBJECT(ma_fenetre->window), "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_main();

    return 0;
}



