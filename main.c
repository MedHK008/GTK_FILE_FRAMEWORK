#include "headers.h"
int main(int argc, char *argv[]) {
    debut_programme(argc,argv);
    FILE *F = fopen("reader.txt", "r");
    FILE *G = fopen("boite_dialogue.txt", "r"); // Ouvre le fichier en mode lecture
    Boite_message*BD; // Ouvre le fichier en mode lecture
    if (F == NULL || G==NULL)
        g_print("Impossible d'ouvrir le fichier!!\n");
    Fenetre *Win=(Fenetre*)malloc(sizeof(Fenetre));
    if(Win)
    {
        fseek(G,0,SEEK_END);
        if(G>0)
        {
            fseek(G,0,SEEK_SET);
            BD=initialiser_boite_message();
            BD=lire_boite_message(G,BD);
            definir_attribut_boite_message(BD);
            BD=ajouter_to_boite_message_fichier(G,BD);
            fclose(G);
        }
        lire_fichier(F,Win,NULL,"/root",BD);
    }
    while(Win){
            Fenetre *sup=Win;
            Win=Win->svt;
        free(sup);
    }



    return 0;
}

   // GtkWidget *notebook = exemple();


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
//     menubar *maMenuBar = add_menubar(GTK_PACK_DIRECTION_LTR,fixed4);
//    gtk_fixed_put(fixed4, maMenuBar->menubar,34,34);
//
//       menu *menu_file = add_menu(maMenuBar, "File");
//  // Exemple d'ajout d'éléments de menu à "File"
//    menu *menu_open = add_menu_item(menu_file, DEFAULT_MENU, "_New", TRUE, FALSE, NULL);
//       add_menu_item(menu_open, DEFAULT_MENU, "empty file", FALSE, FALSE, NULL);
//       add_menu_item(menu_open, SEPARATOR_MENU, "sep", FALSE, FALSE, NULL);
//       add_menu_item(menu_open, DEFAULT_MENU, "project...", FALSE, FALSE, NULL);
//       add_menu_item(menu_file, DEFAULT_MENU, "_Save", FALSE, FALSE, NULL);
//
//    // Exemple d'ajout d'un menu "Edit"
//    menu *menu_edit = add_menu(maMenuBar, "Edit");
//        // Exemple d'ajout d'éléments de menu à "Edit"
//        add_menu_item(menu_edit,DEFAULT_MENU, "C_ut", FALSE, FALSE, NULL);
//        add_menu_item(menu_edit,DEFAULT_MENU, "_Copy", FALSE, TRUE, NULL);
//        add_menu_item(menu_edit,DEFAULT_MENU, "_Paste", FALSE, FALSE, NULL);
//
//     menu *menu_view = add_menu(maMenuBar, "View");
//       menu *menu_tool = add_menu_item(menu_view,DEFAULT_MENU, "_Toolbars", TRUE, FALSE, NULL);
//           add_menu_item(menu_tool,DEFAULT_MENU, "Fit toolbar", FALSE, FALSE, NULL);
//           add_menu_item(menu_tool,DEFAULT_MENU, "OPtimise toolbar", FALSE, FALSE, NULL);
//           add_menu_item(menu_tool,SEPARATOR_MENU, NULL, FALSE, FALSE, NULL);
//           add_menu_item(menu_tool,CHECKBOX_MENU, "Compiler", FALSE, FALSE, NULL);
//           add_menu_item(menu_tool, CHECKBOX_MENU, "Debuger", FALSE, FALSE, NULL);
//           add_menu_item(menu_view,CHECKBOX_MENU, "Status_bar", FALSE, FALSE, NULL);
//       add_menu_item(menu_view,CHECKBOX_MENU, "_Logs", FALSE, FALSE, NULL);
//       add_menu_item(menu_view,CHECKBOX_MENU, "_Manager", FALSE, FALSE, NULL);
//       add_menu_item(menu_view,CHECKBOX_MENU, "Status_bar", FALSE, FALSE, NULL);
//
//    // Exemple d'ajout d'un menu "Language"
//    menu *menu_language = add_menu(maMenuBar, "Language");
//    // Exemple d'ajout d'éléments radio à "Language"
//       add_menu_item(menu_language, RADIO_MENU, "C/C++", FALSE, TRUE, NULL);
//       add_menu_item(menu_language, RADIO_MENU, "Python", FALSE, FALSE, NULL);
//       add_menu_item(menu_language, RADIO_MENU, "Java", FALSE, FALSE, NULL);
//       add_menu_item(menu_language, RADIO_MENU, "C#", FALSE, FALSE, NULL);
//       add_menu_item(menu_language, RADIO_MENU, "JavaScript", FALSE, FALSE, NULL);
//       add_menu_item(menu_language, RADIO_MENU, "PHP", FALSE, FALSE, NULL);
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
   // add_to_window(notebook,ma_fenetre->window);






//
//int main(int argc, char *argv[]) {
//    debut_programme(argc,argv);
//    Fenetre* ma_fenetre=add_window("ma fenetre","gtklogo.png","window","white",
//                   3840,2160,GTK_WIN_POS_CENTER,
//                   -1,-1,5,TRUE);
//
//    GtkWidget *notebook = exemple(ma_fenetre->window);
//     // FILE* F=fopen("reader.txt","r");
//     /// fixed* fixed0=init_gtk_fixed("fixed0");
//     // GtkWidget* box=gtk_vbox_new(FALSE,10);
//     // lire_fichier(F,fixed0,box,ma_fenetre);
//     // gtk_box_pack_start(GTK_BOX(box), fixed0->fixed, FALSE, FALSE,10);
////    GtkWidget* fixed1 = create_fixed();///fiha le menu bohdo db
////    add_progress_bar(fixed1,2.3,1.0,1000,500,1,250,250);
////    add_image(fixed1,1,"gtklogo.png",GTK_ICON_SIZE_BUTTON,50,50,250,250);
////    add_onglet(notebook,fixed1,"onglet 2","#00FFFF");///pour ajouter le fixed dans l'onglet (tqdr dir bo wla tableau wla contenair, ay widget)
////
////    GtkWidget* fixed2 = create_fixed();///khawya
////    texte* txt=initialiser_texte(20,30,"exemple frame",NULL,NULL,25,NULL,NULL,"red","#00FF00",NULL);
////    add_label(fixed2,txt,TRUE,FALSE,350,350);
////    add_onglet(notebook,fixed2,"onglet 3","#FFFF00");///pour ajouter le fixed dans l'onglet (tqdr dir bo wla tableau wla contenair, ay widget)
/////*************************************frame example******************************************************************/
////
////
////    GtkWidget* fixed3 = create_fixed();///khawya
////
////
//////    add_cocher(fixed3,"testing cocher1",0,300,"#000000",TRUE);
//////    add_cocher(fixed3,"testing cocher2",0,330,"#FFFFFF",FALSE);
//////    add_cocher(fixed3,"testing cocher3",0,360,"#00FF00",TRUE);
//////    add_cocher(fixed3,"testing cocher4",0,390,"#FF0000",FALSE);
//////    add_cocher(fixed3,"testing cocher1",200,300,"#FFFFFF",TRUE);
//////    add_cocher(fixed3,"testing cocher2",200,330,"#FFFFFF",TRUE);
//////    add_cocher(fixed3,"testing cocher3",200,360,"#FFFFFF",TRUE);
//////    add_cocher(fixed3,"testing cocher4",200,390,"#FFFFFF",TRUE);
//////    add_cocher(fixed3,"testing cocher1",400,300,"#000000",FALSE);
//////    add_cocher(fixed3,"testing cocher2",400,330,"#000000",FALSE);
//////    add_cocher(fixed3,"testing cocher3",400,360,"#000000",FALSE);
//////    add_cocher(fixed3,"testing cocher4",400,390,"#000000",FALSE);
////    char *labels4[NB_RADIO] = {"Option 1", "Option 2", "Option 3"};
////    char *colors4[NB_RADIO] = {"#FF0000", "#00FF00", "#0000FF"};
////    gboolean checked4[NB_RADIO] = {FALSE, TRUE, FALSE};
////    add_radio(fixed3, NB_RADIO,0,600, labels4, colors4,checked4);
////    char *labels5[NB_RADIO] = {"Option 1", "Option 2", "Option 3"};
////    char *colors5[NB_RADIO] = {"#FFFFFF", "#FFFFFF", "#FFFFFF"};
////    gboolean checked5[NB_RADIO] = {FALSE, FALSE, FALSE};
////    add_radio(fixed3, NB_RADIO,200,600, labels5, colors5,checked5);
////    char *labels6[NB_RADIO] = {"Option 1", "Option 2", "Option 3"};
////    char *colors6[NB_RADIO] = {"#000000", "#000000", "#000000"};
////    gboolean checked6[NB_RADIO] = {FALSE, FALSE, TRUE};
////    add_radio(fixed3, NB_RADIO,400,600, labels6, colors6,checked6);
////    add_spin(fixed3, 0, 800, 0.0, 100.0, 1.0, 1.0, 30, 150, 1, 2, 1, 1, "#00ff00", 1.0);
////    add_spin(fixed3, 200, 800, 0.0, 100.0, 50.0, 5.0, 30, 30, 1, 2, 1, 1, "#ff0000", 1.0);
////    add_spin(fixed3, 400, 800, 0.0, 100.0, 100.0, 100.0, 50, 150, 1, 2, 1, 1, "#ffffff", 1.0);
////
////    frame* frm=add_frame(fixed,0.5,1.0,txt,NULL,GTK_SHADOW_IN,800,0);
////    gtk_container_add(GTK_CONTAINER(frm->widget),fixed3);
/////*************************************frame example fin******************************************************************/
/////*************************************menu******************************************************************/
////    GtkWidget* fixed4 = create_fixed();///khawya
////    Add_Entry(fixed4,"azerty",50,0,1,"A","a",200,50,1,"#FFFFFF",500,500);
////    add_onglet(notebook,fixed4,"onglet4","#0000FF");
////    // Ajout de la barre de menus à la fenêtre principale
////     menubar *maMenuBar = add_menubar(GTK_PACK_DIRECTION_LTR,fixed4);
////    gtk_fixed_put(fixed4, maMenuBar->menubar,34,34);
////
////       menu *menu_file = add_menu(maMenuBar, "File");
////  // Exemple d'ajout d'éléments de menu à "File"
////    menu *menu_open = add_menu_item(menu_file, DEFAULT_MENU, "_New", TRUE, FALSE, NULL);
////       add_menu_item(menu_open, DEFAULT_MENU, "empty file", FALSE, FALSE, NULL);
////       add_menu_item(menu_open, SEPARATOR_MENU, "sep", FALSE, FALSE, NULL);
////       add_menu_item(menu_open, DEFAULT_MENU, "project...", FALSE, FALSE, NULL);
////       add_menu_item(menu_file, DEFAULT_MENU, "_Save", FALSE, FALSE, NULL);
////
////    // Exemple d'ajout d'un menu "Edit"
////    menu *menu_edit = add_menu(maMenuBar, "Edit");
////        // Exemple d'ajout d'éléments de menu à "Edit"
////        add_menu_item(menu_edit,DEFAULT_MENU, "C_ut", FALSE, FALSE, NULL);
////        add_menu_item(menu_edit,DEFAULT_MENU, "_Copy", FALSE, TRUE, NULL);
////        add_menu_item(menu_edit,DEFAULT_MENU, "_Paste", FALSE, FALSE, NULL);
////
////     menu *menu_view = add_menu(maMenuBar, "View");
////       menu *menu_tool = add_menu_item(menu_view,DEFAULT_MENU, "_Toolbars", TRUE, FALSE, NULL);
////           add_menu_item(menu_tool,DEFAULT_MENU, "Fit toolbar", FALSE, FALSE, NULL);
////           add_menu_item(menu_tool,DEFAULT_MENU, "OPtimise toolbar", FALSE, FALSE, NULL);
////           add_menu_item(menu_tool,SEPARATOR_MENU, NULL, FALSE, FALSE, NULL);
////           add_menu_item(menu_tool,CHECKBOX_MENU, "Compiler", FALSE, FALSE, NULL);
////           add_menu_item(menu_tool, CHECKBOX_MENU, "Debuger", FALSE, FALSE, NULL);
////           add_menu_item(menu_view,CHECKBOX_MENU, "Status_bar", FALSE, FALSE, NULL);
////       add_menu_item(menu_view,CHECKBOX_MENU, "_Logs", FALSE, FALSE, NULL);
////       add_menu_item(menu_view,CHECKBOX_MENU, "_Manager", FALSE, FALSE, NULL);
////       add_menu_item(menu_view,CHECKBOX_MENU, "Status_bar", FALSE, FALSE, NULL);
////
////    // Exemple d'ajout d'un menu "Language"
////    menu *menu_language = add_menu(maMenuBar, "Language");
////    // Exemple d'ajout d'éléments radio à "Language"
////       add_menu_item(menu_language, RADIO_MENU, "C/C++", FALSE, TRUE, NULL);
////       add_menu_item(menu_language, RADIO_MENU, "Python", FALSE, FALSE, NULL);
////       add_menu_item(menu_language, RADIO_MENU, "Java", FALSE, FALSE, NULL);
////       add_menu_item(menu_language, RADIO_MENU, "C#", FALSE, FALSE, NULL);
////       add_menu_item(menu_language, RADIO_MENU, "JavaScript", FALSE, FALSE, NULL);
////       add_menu_item(menu_language, RADIO_MENU, "PHP", FALSE, FALSE, NULL);
/////*************************************menu fin******************************************************************/
////
/////***************************boite de dilogue*****************************/
//////    BoiteDialogue* bd=Add_boite_dialogue(GTK_WINDOW(ma_fenetre->window),"exemple boite de dialogue","",0,300,300,0,"red");
//////    ButtonSimple* bt1=add_button_dialogue(fixed4,"ouvrir boite dialogue","",50,50,"red",200,200,0,0);
//////    ButtonSimple* bt2=add_button_dialogue(bd->zone_contenu,"fermer","",20,20,"red",10,10,0,0);
//////    g_signal_connect(bt1->button, "clicked", G_CALLBACK(on_button_clicked), bd->dialogue);
////
/////*************************************barre d'outil******************************************************************/
////    GtkWidget *box=gtk_vbox_new(FALSE,0);
////    toolbar *ptbar=add_toolbar(box,'v',60,60,60,60,GTK_ICON_SIZE_BUTTON,GTK_TOOLBAR_ICONS,50);
////    add_item_bar(ptbar,GTK_STOCK_SAVE,"enregistrer",100,100,1);
////    add_item_bar(ptbar,GTK_STOCK_CLOSE,"fermer",100,100,-1);
////    add_item_bar(ptbar,GTK_STOCK_QUIT,"quitter",100,100,-1);
////    add_onglet(notebook,box,"onglet 5","#000000");
//
//
//    ///matqissch hadchi li mor had lcomment
//    //add_to_window(notebook,ma_fenetre->window);
//    gtk_widget_show_all(ma_fenetre->window);
//
//    fin_programme(ma_fenetre);
//    return 0;
//}
//
//
//
