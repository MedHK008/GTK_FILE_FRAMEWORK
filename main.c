#include "headers.h"

GtkWidget *create_fixed()
{

    GtkFixed *fixed = GTK_FIXED(gtk_fixed_new());
    return ((GtkWidget*)fixed);
}



int main(int argc, char *argv[]) {
    debut_programme(argc,argv);

    GtkWidget *notebook = gtk_notebook_new();
    Fenetre* ma_fenetre = add_window();

/****************************************************** les bouttons***********************************/

    GtkWidget* fixed = create_fixed();///les bouttons (is finished)
    Fixed* fixed0=init_gtk_fixed();
/******************************************************boutton normal***********************************/
/// les parametres : le fixed , le label du button , path de l'image utiliser (NULL s'il y a pas d'image),height,width,bgcolor, x , y
    texte* txt_button=initialiser_texte(20,30,"exemple des boutons",3,"Verdana",12,"italic",NULL,"#000000","#FFFFFF",NULL);
    add_label(fixed0->fixed,txt_button,TRUE,FALSE,50,0);
    ButtonSimple *button = add_button("first","gtklogo.png",100,100,"#FF0000",50,50);
    add_widget_to_fixed(fixed0,button->button,50,50);
    add_onglet(notebook,fixed0->fixed,"onglet 0","#FFFFFF");
/******************************************************boutton normal***********************************/
/****************************************************** les cochers***********************************/
/// les parametres : le fixed , le label , le x , le y ,le bgcolor, si le checkbox est cocher dès le début ou non
    texte* txt_cocher=initialiser_texte(20,30,"exemple des bouttons a cocher",NULL,NULL,25,NULL,NULL,"green","#00FF00",NULL);
    add_label(fixed0->fixed,txt_cocher,TRUE,FALSE,50,250);
    // Initialize the checkbox list
    CheckboxList *checkboxList = init_checkbox_list();

    GtkWidget *checkbox1 = add_cocher(checkboxList,fixed0->fixed, "testing cocher1", 200, 300,NULL, TRUE);
    GtkWidget *checkbox2 = add_cocher(checkboxList,fixed0->fixed, "testing cocher2", 200, 330, "#FFFFFF", TRUE);
    GtkWidget *checkbox3 = add_cocher(checkboxList,fixed0->fixed, "testing cocher3", 200, 360, "#FFFFFF", TRUE);
    GtkWidget *checkbox4 = add_cocher(checkboxList,fixed0->fixed, "testing cocher4", 200, 390, "#FFFFFF", TRUE);

    // Add the checkboxes to the fixed container
    add_widget_to_fixed(fixed0,checkbox1, 200, 300);
    add_widget_to_fixed(fixed0,checkbox2, 200, 330);
    add_widget_to_fixed(fixed0,checkbox3, 200, 360);
    add_widget_to_fixed(fixed0,checkbox4, 200, 390);


/****************************************************** les cochers***********************************/
/****************************************************** les radios***********************************/
/// les parametres : le fixed  , le x , le y , les labels,le bgcolor de chaque button, le radio qui soit cocher dès le début (all FALSE signifie que aucun ne sera cocher)
    texte* txt_radio=initialiser_texte(20,30,"exemple des bouttons radio",NULL,NULL,25,NULL,NULL,"red","#00FF00",NULL);
    add_label(fixed,txt_radio,TRUE,FALSE,50,450);
//    char *labels2[NB_RADIO] = {"Option 1", "Option 2", "Option 3"};
//    char *colors2[NB_RADIO] = {"#FFFFFF", "#FFFFFF", "#FFFFFF"};
//    gboolean checked2[NB_RADIO] = {FALSE, FALSE, FALSE};
//    add_radio(fixed, NB_RADIO,250,500, labels2, colors2,checked2);

    GtkWidget *radioBox = add_radio(3, 20, 20, (char *[]){"Option 1", "Option 2", "Option 3"},(char *[]){NULL}, (gboolean[]){TRUE, FALSE, FALSE});
    add_widget_to_fixed(fixed0,radioBox,200,450);
/****************************************************** les radios***********************************/
/****************************************************** les spins***********************************/
///khdem biha wskot mafiya li ykteb lcommentaire db
    texte* txt_spin=initialiser_texte(20,30,"exemple boutton spin",NULL,NULL,25,NULL,NULL,"red","#00FF00",NULL);
    add_label(fixed,txt_spin,TRUE,FALSE,50,600);
    add_spin(fixed, 50, 650, 0.0, 100.0, 1.0, 1.0, 30, 150, 1, 2, 1, 1, "#00ff00", 1.0);
    add_spin(fixed, 250, 650, 0.0, 100.0, 50.0, 5.0, 30, 30, 1, 2, 1, 1, "#ff0000", 1.0);
    add_spin(fixed, 450, 650, 0.0, 100.0, 100.0, 100.0, 50, 150, 1, 2, 1, 1, "#ffffff", 1.0);
/****************************************************** les spins***********************************/
    add_onglet(notebook,fixed,"onglet 1","#FF00FF");
/***********************************************les bouttons fin*****************************************/
//    GtkWidget* fixed1 = create_fixed();///fiha le menu bohdo db
//    add_progress_bar(fixed1,2.3,1.0,1000,500,1,250,250);
//    add_image(fixed1,1,"gtklogo.png",GTK_ICON_SIZE_BUTTON,50,50,250,250);
//    add_onglet(notebook,fixed1,"onglet 2","#00FFFF");///pour ajouter le fixed dans l'onglet (tqdr dir bo wla tableau wla contenair, ay widget)
//
//    GtkWidget* fixed2 = create_fixed();///khawya
//    texte* txt=initialiser_texte(20,30,"exemple frame",NULL,NULL,25,NULL,NULL,"red","#00FF00",NULL);
//    add_label(fixed2,txt,TRUE,FALSE,350,350);
//    add_onglet(notebook,fixed2,"onglet 3","#FFFF00");///pour ajouter le fixed dans l'onglet (tqdr dir bo wla tableau wla contenair, ay widget)
///*************************************frame example******************************************************************/
//
//
//    GtkWidget* fixed3 = create_fixed();///khawya
//
//
////    add_cocher(fixed3,"testing cocher1",0,300,"#000000",TRUE);
////    add_cocher(fixed3,"testing cocher2",0,330,"#FFFFFF",FALSE);
////    add_cocher(fixed3,"testing cocher3",0,360,"#00FF00",TRUE);
////    add_cocher(fixed3,"testing cocher4",0,390,"#FF0000",FALSE);
////    add_cocher(fixed3,"testing cocher1",200,300,"#FFFFFF",TRUE);
////    add_cocher(fixed3,"testing cocher2",200,330,"#FFFFFF",TRUE);
////    add_cocher(fixed3,"testing cocher3",200,360,"#FFFFFF",TRUE);
////    add_cocher(fixed3,"testing cocher4",200,390,"#FFFFFF",TRUE);
////    add_cocher(fixed3,"testing cocher1",400,300,"#000000",FALSE);
////    add_cocher(fixed3,"testing cocher2",400,330,"#000000",FALSE);
////    add_cocher(fixed3,"testing cocher3",400,360,"#000000",FALSE);
////    add_cocher(fixed3,"testing cocher4",400,390,"#000000",FALSE);
//    char *labels4[NB_RADIO] = {"Option 1", "Option 2", "Option 3"};
//    char *colors4[NB_RADIO] = {"#FF0000", "#00FF00", "#0000FF"};
//    gboolean checked4[NB_RADIO] = {FALSE, TRUE, FALSE};
//    add_radio(fixed3, NB_RADIO,0,600, labels4, colors4,checked4);
//    char *labels5[NB_RADIO] = {"Option 1", "Option 2", "Option 3"};
//    char *colors5[NB_RADIO] = {"#FFFFFF", "#FFFFFF", "#FFFFFF"};
//    gboolean checked5[NB_RADIO] = {FALSE, FALSE, FALSE};
//    add_radio(fixed3, NB_RADIO,200,600, labels5, colors5,checked5);
//    char *labels6[NB_RADIO] = {"Option 1", "Option 2", "Option 3"};
//    char *colors6[NB_RADIO] = {"#000000", "#000000", "#000000"};
//    gboolean checked6[NB_RADIO] = {FALSE, FALSE, TRUE};
//    add_radio(fixed3, NB_RADIO,400,600, labels6, colors6,checked6);
//    add_spin(fixed3, 0, 800, 0.0, 100.0, 1.0, 1.0, 30, 150, 1, 2, 1, 1, "#00ff00", 1.0);
//    add_spin(fixed3, 200, 800, 0.0, 100.0, 50.0, 5.0, 30, 30, 1, 2, 1, 1, "#ff0000", 1.0);
//    add_spin(fixed3, 400, 800, 0.0, 100.0, 100.0, 100.0, 50, 150, 1, 2, 1, 1, "#ffffff", 1.0);
//
//    frame* frm=add_frame(fixed,0.5,1.0,txt,NULL,GTK_SHADOW_IN,800,0);
//    gtk_container_add(GTK_CONTAINER(frm->widget),fixed3);
///*************************************frame example fin******************************************************************/
///*************************************menu******************************************************************/
//    GtkWidget* fixed4 = create_fixed();///khawya
//    Add_Entry(fixed4,"azerty",50,0,1,"A","a",200,50,1,"#FFFFFF",500,500);
//    add_onglet(notebook,fixed4,"onglet4","#0000FF");
//    // Ajout de la barre de menus à la fenêtre principale
//    menubar *maMenuBar = add_menu_bar(fixed4, 0);
//    // Exemple d'ajout d'un menu "File"
//    menu *menu_file = add_menu(maMenuBar, "File");
//    // Exemple d'ajout d'éléments de menu à "File"
//    menu *menu_open = add_menu_item(menu_file, 0, "_New", TRUE, FALSE, NULL);
//       add_menu_item(menu_open, 0, "empty file", FALSE, FALSE, NULL);
//       add_menu_item(menu_open, 2, "sep", FALSE, FALSE, NULL);
//       add_menu_item(menu_open, 0, "project...", FALSE, FALSE, NULL);
//       add_menu_item(menu_file, 0, "_Save", FALSE, FALSE, NULL);
//
//    // Exemple d'ajout d'un menu "Edit"
//    menu *menu_edit = add_menu(maMenuBar, "Edit");
//        // Exemple d'ajout d'éléments de menu à "Edit"
//        add_menu_item(menu_edit,0, "C_ut", FALSE, FALSE, NULL);
//        add_menu_item(menu_edit, 0, "_Copy", FALSE, TRUE, NULL);
//        add_menu_item(menu_edit, 0, "_Paste", FALSE, FALSE, NULL);
//
//     menu *menu_view = add_menu(maMenuBar, "View");
//       menu *menu_tool = add_menu_item(menu_view,0, "_Toolbars", TRUE, FALSE, NULL);
//           add_menu_item(menu_tool,0, "Fit toolbar", FALSE, FALSE, NULL);
//           add_menu_item(menu_tool, 0, "OPtimise toolbar", FALSE, FALSE, NULL);
//           add_menu_item(menu_tool, 2, NULL, FALSE, FALSE, NULL);
//           add_menu_item(menu_tool,1, "Compiler", FALSE, FALSE, NULL);
//           add_menu_item(menu_tool, 1, "Debuger", FALSE, FALSE, NULL);
//           add_menu_item(menu_view, 1, "Status_bar", FALSE, FALSE, NULL);
//       add_menu_item(menu_view,1, "_Logs", FALSE, FALSE, NULL);
//       add_menu_item(menu_view, 1, "_Manager", FALSE, FALSE, NULL);
//       add_menu_item(menu_view, 1, "Status_bar", FALSE, FALSE, NULL);
//
//    // Exemple d'ajout d'un menu "Language"
//    menu *menu_language = add_menu(maMenuBar, "Language");
//    // Exemple d'ajout d'éléments radio à "Language"
//       add_menu_item(menu_language, 4, "C/C++", FALSE, TRUE, NULL);
//       add_menu_item(menu_language, 4, "Python", FALSE, FALSE, NULL);
//       add_menu_item(menu_language, 4, "Java", FALSE, FALSE, NULL);
//       add_menu_item(menu_language, 4, "C#", FALSE, FALSE, NULL);
//       add_menu_item(menu_language, 4, "JavaScript", FALSE, FALSE, NULL);
//       add_menu_item(menu_language, 4, "PHP", FALSE, FALSE, NULL);
///*************************************menu fin******************************************************************/
//
///***************************boite de dilogue*****************************/
////    BoiteDialogue* bd=Add_boite_dialogue(GTK_WINDOW(ma_fenetre->window),"exemple boite de dialogue","",0,300,300,0,"red");
////    ButtonSimple* bt1=add_button_dialogue(fixed4,"ouvrir boite dialogue","",50,50,"red",200,200,0,0);
////    ButtonSimple* bt2=add_button_dialogue(bd->zone_contenu,"fermer","",20,20,"red",10,10,0,0);
////    g_signal_connect(bt1->button, "clicked", G_CALLBACK(on_button_clicked), bd->dialogue);
//
///*************************************barre d'outil******************************************************************/
//    GtkWidget *box=gtk_vbox_new(FALSE,0);
//    toolbar *ptbar=add_toolbar(box,'v',60,60,60,60,GTK_ICON_SIZE_BUTTON,GTK_TOOLBAR_ICONS,50);
//    add_item_bar(ptbar,GTK_STOCK_SAVE,"enregistrer",100,100,1);
//    add_item_bar(ptbar,GTK_STOCK_CLOSE,"fermer",100,100,-1);
//    add_item_bar(ptbar,GTK_STOCK_QUIT,"quitter",100,100,-1);
//    add_onglet(notebook,box,"onglet 5","#000000");


    ///matqissch hadchi li mor had lcomment
    add_to_window(notebook,ma_fenetre->window);
    gtk_widget_show_all(ma_fenetre->window);

    fin_programme(ma_fenetre);
    return 0;
}



