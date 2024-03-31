#ifndef READER_H_INCLUDED
#define READER_H_INCLUDED

#define MAX 100


//typedef struct pl{
//    gchar *contenue;
//    struct pl*svt;
//}Pile;
//Pile *initialiser_Pile(Pile*P)
//{
//    P=NULL;
//    return(Pile*)(P);
//}
//Pile*empiler(Pile *P,gchar*name)
//{
//    Pile*NE=(Pile*)malloc(sizeof(Pile));
//    if(NE){
//        NE->contenue=name;
//        if(!P) return(Pile*)(NE);
//        else {
//            NE->svt=P;
//            return(Pile*)(P);
//        }
//    }
//    exit(-1);
//}
//Pile* depiler(Pile*P)
//{
//    if(!P) return(Pile*)(NULL);
//    Pile*Supp=P;
//    P=P->svt;
//    free(Supp);
//    return (Pile*)(P);
//}



void add_to_parent(GtkWidget* child,GtkWidget* parent_w, gchar* parent,guint posx, guint posy)
{
  if(!strcmp(parent,"/fixed"))
    gtk_fixed_put(GTK_FIXED(parent_w),child,posx,posy);
 else if(!strcmp(parent,"/box"))
    gtk_box_pack_start(GTK_BOX(parent_w),child,TRUE,TRUE,0);
 else if(!strcmp(parent,"/window"))
    gtk_container_add(GTK_CONTAINER(parent_w),child);
else if (!strcmp(parent,"/boite_dialogue"))
    ajouter_a_boite_dialogue(parent_w,child,posx,posy);

}
void lire_fichier(FILE*F,Fenetre* W,GtkWidget* parent_w , gchar* parent_token)
{
    gchar c ;
    gchar current_token[MAX];
    Token tok;
    int into=0;
    c=epurer_blan(F);
    ButtonSimple *Button_dial;
    GtkWidget* radiopar = gtk_radio_button_new(NULL);
    printf("\n%s->%c",parent_token,c);
    while(c!=EOF)
    {
        printf("\n%s ::: %c",parent_token,c);
        if(c=='<')
        {
              fscanf(F, "%s", current_token);
              printf("\n%s",current_token);

            if (!strcmp(current_token , parent_token))

            {
                if(!(strcmp(current_token,"/root")))
                  {
                       printf("\nRRRRRRRRR");
                       gtk_widget_show_all(W->window);
                       if(W->svt)
                           gtk_widget_show_all(W->svt->window);
                       fin_programme(W);
                  }
                c=epurer_blan(F);
                return ;
            }
            else if (!strcmp(current_token,"/boite_dialogue>"))
            {
                into=0;
                printf("%s",current_token);
            }

             tok=string_to_token(current_token);
             switch(tok)
             {
               case Root: c=epurer_blan(F);
                          c=epurer_blan(F);

                   break;

                case fenetre:
                    printf("\nswitch F");
                    if(W->window)
                    {
                        W->svt=add_window(F);
                        W->svt->svt=NULL;
                        if(!W->scroll_bool)
                         lire_fichier(F,W->svt,W->svt->window,"/window");

                        else
                        lire_fichier(F,W->svt,W->svt->scrollwin,"/window");
                        printf("\nsortie F");
                        c=epurer_blan(F);
                    }
                    else{
                        W=add_window(F);
                    if(!W->scroll_bool)
                         lire_fichier(F,W,W->window,"/window");
                    else
                        lire_fichier(F,W,W->scrollwin,"/window");
                    printf("\nsortie F");
                    c=epurer_blan(F);
                    }

                    break;
               case Fixed:

                    fixed* fix=add_fixed(F,fix);
                    add_to_parent(fix->fixed,parent_w,parent_token,fix->posx,fix->posy);
                    lire_fichier(F,W,fix->fixed,"/fixed");
                    free(fix);
                    c=epurer_blan(F);

                    break;
                case Label:
                   Etiquette *lab= add_label(F);
                   add_to_parent(lab->widget,parent_w,parent_token,lab->x,lab->y);
                   free(lab);
                   c=epurer_blan(F);
                   break;
                case Entry:
                   Saisie* E=Add_Entry(F);
                   add_to_parent(E->entree,parent_w,parent_token,E->x_pos,E->y_pos);
                   free(E);
                    c=epurer_blan(F);
                    break;
                case Button:
                     ButtonSimple* B=add_button(F);
                    add_to_parent(B->button,parent_w,parent_token,50,50);
                    free(B);
                    c=epurer_blan(F);
                    break;
                case Radio:
                   elem_radio* R = add_radio(F, fix, radiopar);
                    if (R) {
                            add_to_parent(R->pRadio,parent_w,parent_token,R->x_pos,R->y_pos);
                            free(R);
                    }
                    c=epurer_blan(F);
                    break;
                case Checkbox:
                        cocher* C = add_cocher(F);
                        add_to_parent(C->boutcoche,parent_w,parent_token,C->x_pos,C->y_pos);
                        free(C);
                        c=epurer_blan(F);
                        break;
//                case button_dialogue :
//                    Button_dial=add_button(F);
//                    add_to_parent(Button_dial->button,parent_w,parent_token,100,100);
//                    free()
//                    c=epurer_blan(F);
//                    break;
//                case boiteDialogue:
//
//                    BD=Add_boite_dialogue(F);
//                    c=epurer_blan(F);
//                    ungetc(c,F);
//                    lire_boite_dialogue(F,BD);
//                                        printf("\nsortie de boite dialogue\n");
//
//                    g_signal_connect(Button_dial->button, "clicked", G_CALLBACK(on_button_clicked),BD->dialogue);
//                    c=epurer_blan(F);
//                    break;
                case Frame:
                    frame *fr=add_frame(parent_w,F);
                    lire_son_elem(fr,F,W);
                    free(fr);
                    c=epurer_blan(F);
                    break;
              case Image:
                   image *img=add_image(F);
                   add_to_parent(img->widget,parent_w,parent_token,img->x,img->y);
                   free(img);
                   c=epurer_blan(F);
                   break;
                  case ProgBar:
                      barre_prog *prog_bar=add_progress_bar(F);
                      add_to_parent(prog_bar->parent,parent_w,parent_token,prog_bar->x,prog_bar->y);
                      free(prog_bar);
                      c=epurer_blan(F);
                      break;
                case ScrollBar:
                    parent_w=add_scrollbar(F,parent_w);
                    printf("\n hhhhhh");
                    //add_to_parent(fi,parent_w,parent_token,0,0);
                    lire_fichier(F,W,parent_w,"/fixed");
                    //free();
                    c=epurer_blan(F);
                    break;
                 case spB:
                        SpinButton* spB=add_spin_button_from_file(F);
                        add_to_parent(spB->SpinButton,parent_w,parent_token,spB->posx,spB->posy);
                        free(spB);
                        c=epurer_blan(F);
                        break;
                case ToolBar:
                   toolbar *tbar=add_toolbar(F);
                    lire_son_item(tbar ,F);
                    gtk_box_pack_start(GTK_BOX(parent_w),tbar->widget,TRUE,FALSE,0);
                    free(tbar);
                    c=epurer_blan(F);
                    break;
               case Box:
                    box * bx=NULL;
                    bx=add_box(F);
                    add_to_parent(bx->box,parent_w,parent_token,bx->posx,bx->posy);

                    lire_fichier(F,W,bx->box,"/box");
                    free(bx);
                    c=epurer_blan(F);
                    break;
//                case Tab:
//                    ongletFunction(F);
//                    break;
                  case MenuBar:
                      printf("\n ici menubar    ");
                        menubar *mbar =add_menubar(mbar,F);
                        printf("\n ici menubar  apres add_menubar  ");
                         ajouter_elems(mbar,F);
                         printf("\n ici menubar  apres ajouter  ");
                        add_to_parent(mbar->menubar,parent_w,parent_token,mbar->posx,mbar->posy);
                        free(mbar);

                        c=epurer_blan(F);

                        break;
//                case MenuItem:
//                    menuItemFunction(F);
//
//                    break;
                default:
                    // Gérer le cas où le token n'est pas reconnu
                    break;
            }


        }
        else
           {
             printf("\nssssWWW"); return ;
           }




    }


}
//BoiteDialogue* lire_Boite_dialogue(FILE*F,ButtonSimple*B)
//{
//    BoiteDialogue*BD=Add_boite_dialogue(F);
//    if(!BD) exit(-1);
//    gchar c ;
//    gchar current_token[MAX];
//    Token tok;
//    gchar*elem=(gchar*)g_malloc(sizeof(gchar)*50);
//    c=epurer_blan(F);
//
//    Saisie*E;
//    while(c!=EOF)
//    {
//        if(c=='<')
//        {
//            c=fgetc(F);
//            if(c!='/')
//            {
//            ungetc(c,F);
//             fscanf(F,"%s",current_token);
//             printf("%s",current_token);
//
//
//             tok=string_to_token(current_token);
//             switch(tok) {
//                case Entry:
//
//                    E=Add_Entry(F);
//                    c=epurer_blan(F);
//                        ajouter_a_boite_dialogue(BD,E->entree,E->x_pos,E->y_pos);
//
//                    break;
//                case Button:
//                     B=add_button(F);
////                    add_widget_to_fixed(fixed0,B->button,50,50);
//                    c=epurer_blan(F);
//
//                        ajouter_a_boite_dialogue(BD,B->button,100,100);
//
//                    break;
////                case Radio:
////                    buttonRadioFunction(F);
////                    break;
////                case Checkbox:
////                    checkboxFunction(F);
////                    break;
//
////                case Frame:
////                    frameFunction(F);
////                    break;
////                case Image:
////                    imageFunction(F);
////                    break;
////                case ProgBar:
////                    progBarFunction(F);
////                    break;
////                case ScrollBar:
////                    scrollBarFunction(F);
////                    break;
////                case spB:
////                    spinButtonFunction(F);
////                    break;
////                case ToolBar:
////                    toolBarFunction(F);
////                    break;
////                case ItemBar:
////                    itemBarFunction(F);
////                    break;
////                case MenuBar:
////                    menuBarFunction(F);
////                    break;
////                case Tab:
////                    ongletFunction(F);
////                    break;
////                case MenuItem:
////                    menuItemFunction(F);
////                    break;
//                default:
//                    // Gérer le cas où le token n'est pas reconnu
//                    break;
//            }
//
//
//        }
//        else
//        {
//
//            fscanf(F,"%s",elem);
//            if(!strcmp(elem,"boite_dialogue>"))
//            {
//
//
//
//
//            }
//            c=epurer_blan(F);
//
//        }
//
//    }
//    }
//    g_signal_connect(B->button, "clicked", G_CALLBACK(on_button_clicked), BD->dialogue);
//
//    return BD;
//}

//
//void lire_fichier(FILE*F,fixed* fixed0,GtkWidget *pvbox,GtkWidget *pere)
//{
//    if(!F) exit(-1);
//    gchar c ;
//    gchar current_token[MAX];
//    Token tok;
//    c=epurer_blan(F);
//    while(c!=EOF)
//    {
//        printf("%c",c);
//        if(c=='<')
//        {
//             fscanf(F,"%s",current_token);
//             tok=string_to_token(current_token);
//             switch(tok) {
////                case fenetre:
////                    windowFunction(F);
////                    break;
////                case Fixed:
////                    fixedFunction(F);
////                    break;
//                case Label:
//                   Etiquette *lab= add_label(F);
//                   add_widget_to_fixed(fixed0,lab->widget,lab->x,lab->y);
//                   c=epurer_blan(F);
//                   break;
////                case Entry:
////                    entryFunction(F);
////                    break;
//                case Button:
//                    ButtonSimple* B=add_button(F);
//                    add_widget_to_fixed(fixed0,B->button,50,50);
//                    c=epurer_blan(F);
//                    break;
////                case Radio:
////                    buttonRadioFunction(F);
////                    break;
////                case Checkbox:
////                    checkboxFunction(F);
////                    break;
////                case BoiteDialogue:
////                    boiteDialogueFunction(F);
////                    break;
//                  case Frame:
//                    frame *fr=add_frame(fixed0->fixed,F);
//                    lire_son_elem(fr,F);
//                    c=epurer_blan(F);
//                    break;
//                 case Image:
//                   image *img=add_image(F);
//                   add_widget_to_fixed(fixed0,img->widget,img->x,img->y);
//                   c=epurer_blan(F);
//                   break;
//                  case ProgBar:
//                      barre_prog *prog_bar=add_progress_bar(F);
//                      add_widget_to_fixed(fixed0,prog_bar->parent,prog_bar->x,prog_bar->y);
//                      c=epurer_blan(F);
//                      break;
//                case ScrollBar:
//                    printf("SDJSJAS");
//                    barre_def *scbar=add_scrollbar(pere,pvbox,F);
//                    c=epurer_blan(F);
//                    break;
////                case spB:
////                    spinButtonFunction(F);
////                    break;
//                case ToolBar:
//                    toolbar *tbar=add_toolbar(pvbox,F);
//                    lire_son_item(tbar ,F);
//                    c=epurer_blan(F);
//                    /*
//                    add_item_bar(tbar,GTK_STOCK_SAVE,"enregistrer",100,100,1);
//                    add_item_bar(tbar,GTK_STOCK_CLOSE,"fermer",100,100,-1);
//                    add_item_bar(tbar,GTK_STOCK_QUIT,"quitter",100,100,-1);
//                    */
//
//                    break;
////                case ItemBar:
////                    itemBarFunction(F);
////                    break;
////                case MenuBar:
////                    menuBarFunction(F);
////                    break;
////                case Tab:
////                    ongletFunction(F);
////                    break;
////                case MenuItem:
////                    menuItemFunction(F);
////                    break;
//                default:
//                    // Gérer le cas où le token n'est pas reconnu
//                    break;
//            }
//            printf("\n fin de if");
//
//        }
//        else
//                return;
//    }
//}


#endif // READER_H_INCLUDED
