#ifndef EX_BUTTONS_H_INCLUDED
#define EX_BUTTONS_H_INCLUDED

GtkWidget* exemple(GtkWidget* win)
{
    FILE* F=fopen("reader.txt","r");
    GtkWidget *notebook = gtk_notebook_new();
    /****************************************************** les bouttons***********************************/
        fixed* fixed0=init_gtk_fixed("fixed0");
        GtkWidget* box=gtk_vbox_new(FALSE,10);
        GtkWidget* box1=gtk_vbox_new(FALSE,10);
        GtkWidget *fixed=gtk_fixed_new();
    /******************************************************boutton normal***********************************/
    /// les parametres : le fixed , le label du button , path de l'image utiliser (NULL s'il y a pas d'image),height,width,bgcolor, x , y
        //texte* txt_button=initialiser_texte(20,30,"exemple des boutons",3,"Verdana",12,"italic",NULL,"#000000","#FFFFFF",NULL);
        //add_label(fixed0->fixed,txt_button,TRUE,FALSE,50,0);
        lire_fichier(F,fixed0,box,win);
        gtk_box_pack_start(GTK_BOX(box), fixed0->fixed, FALSE, FALSE,10);
//        ButtonSimple *button = add_button("boutton1","first","gtklogo.png",100,100,"#FF0000",50,50);
//        add_widget_to_fixed(fixed0,B->button,50,50);

    /******************************************************boutton normal***********************************/
    /****************************************************** les cochers***********************************/
    /// les parametres : le fixed , le label , le x , le y ,le bgcolor, si le checkbox est cocher dès le début ou non
        //texte* txt_cocher=initialiser_texte(20,30,"exemple des bouttons a cocher",3,"Verdana",12,"italic",NULL,"#000000","#FFFFFF",NULL);
        //add_label(fixed0->fixed,txt_cocher,TRUE,FALSE,50,280);
        // Initialize the checkbox list
        CheckboxList *checkboxList = init_checkbox_list();

        GtkWidget *checkbox1 = add_cocher(checkboxList,fixed0->fixed, "testing cocher1", 200, 300,NULL, TRUE,"coche1");
        GtkWidget *checkbox2 = add_cocher(checkboxList,fixed0->fixed, "testing cocher2", 200, 330, "#FFFFFF", TRUE,"coche2");
        GtkWidget *checkbox3 = add_cocher(checkboxList,fixed0->fixed, "testing cocher3", 200, 360, "#FFFFFF", TRUE,"coche3");
        GtkWidget *checkbox4 = add_cocher(checkboxList,fixed0->fixed, "testing cocher4", 200, 390, "#FFFFFF", TRUE,"coche4");

        // Add the checkboxes to the fixed container
        add_widget_to_fixed(fixed0,checkbox1, 200, 300);
        add_widget_to_fixed(fixed0,checkbox2, 200, 330);
        add_widget_to_fixed(fixed0,checkbox3, 200, 360);
        add_widget_to_fixed(fixed0,checkbox4, 200, 390);


    /****************************************************** les cochers***********************************/
    /****************************************************** les radios***********************************/
    /// les parametres : le fixed  , le x , le y , les labels,le bgcolor de chaque button, le radio qui soit cocher dès le début (all FALSE signifie que aucun ne sera cocher)
        //texte* txt_radio=initialiser_texte(20,30,"exemple des bouttons radio",3,"Verdana",12,"italic",NULL,"#000000","#FFFFFF",NULL);
        //add_label(fixed0->fixed,txt_radio,TRUE,FALSE,50,430);
    //    char *labels2[NB_RADIO] = {"Option 1", "Option 2", "Option 3"};
    //    char *colors2[NB_RADIO] = {"#FFFFFF", "#FFFFFF", "#FFFFFF"};
    //    gboolean checked2[NB_RADIO] = {FALSE, FALSE, FALSE};
        GtkWidget *radioBox = add_radio(3, 20, 20, (char *[]){"Option 1", "Option 2", "Option 3"},(char *[]){NULL}, (gboolean[]){TRUE, FALSE, FALSE},(gchar *[]){"radio1", "radio2", "radio3"});
        add_widget_to_fixed(fixed0,radioBox,200,450);
    /****************************************************** les radios***********************************/
    /****************************************************** les spins***********************************/
    ///khdem biha wskot mafiya li ykteb lcommentaire db
        //texte* txt_spin=initialiser_texte(20,30,"exemple boutton spin",3,"Verdana",12,"italic",NULL,"#000000","#FFFFFF",NULL);
        //add_label(fixed0->fixed,txt_spin,TRUE,FALSE,50,570);
        SpinButton* spin=add_spin(50, 650, 0.0, 100.0, 1.0, 1.0, 30, 150, 1, 2, 1, 1, "#00ff00", 1.0,"spin1");
        add_widget_to_fixed(fixed0,spin->SpinButton,200,600);
    /****************************************************** les spins***********************************/
        //add_onglet(notebook,box1,"onglet 0","#FFFFFF");
    /***********************************************les bouttons fin*****************************************/
    return ((GtkWidget*)notebook);
}
#endif // EX_BUTTONS_H_INCLUDED
