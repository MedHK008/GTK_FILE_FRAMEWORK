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






void lire_fichier(FILE*F,fixed* fixed0,GtkWidget *pvbox,GtkWidget *pere)
{
    if(!F) exit(-1);
    gchar c ;
    gchar current_token[MAX];
    Token tok;
    c=epurer_blan(F);
    while(c!=EOF)
    {
        printf("%c",c);
        if(c=='<')
        {
             fscanf(F,"%s",current_token);
             tok=string_to_token(current_token);
             switch(tok) {
//                case fenetre:
//                    windowFunction(F);
//                    break;
//                case Fixed:
//                    fixedFunction(F);
//                    break;
                case Label:
                   Etiquette *lab= add_label(F);
                   add_widget_to_fixed(fixed0,lab->widget,lab->x,lab->y);
                   c=epurer_blan(F);
                   break;
//                case Entry:
//                    entryFunction(F);
//                    break;
                case Button:
                    ButtonSimple* B=add_button(F);
                    add_widget_to_fixed(fixed0,B->button,50,50);
                    c=epurer_blan(F);
                    break;
//                case Radio:
//                    buttonRadioFunction(F);
//                    break;
//                case Checkbox:
//                    checkboxFunction(F);
//                    break;
//                case BoiteDialogue:
//                    boiteDialogueFunction(F);
//                    break;
                  case Frame:
                    frame *fr=add_frame(fixed0->fixed,F);
                    lire_son_elem(fr,F);
                    c=epurer_blan(F);
                    break;
                 case Image:
                   image *img=add_image(F);
                   add_widget_to_fixed(fixed0,img->widget,img->x,img->y);
                   c=epurer_blan(F);
                   break;
                  case ProgBar:
                      barre_prog *prog_bar=add_progress_bar(F);
                      add_widget_to_fixed(fixed0,prog_bar->parent,prog_bar->x,prog_bar->y);
                      c=epurer_blan(F);
                      break;
                case ScrollBar:
                    printf("SDJSJAS");
                    barre_def *scbar=add_scrollbar(pere,pvbox,F);
                    c=epurer_blan(F);
                    break;
//                case spB:
//                    spinButtonFunction(F);
//                    break;
                case ToolBar:
                    toolbar *tbar=add_toolbar(pvbox,F);
                    lire_son_item(tbar ,F);
                    c=epurer_blan(F);
                    /*
                    add_item_bar(tbar,GTK_STOCK_SAVE,"enregistrer",100,100,1);
                    add_item_bar(tbar,GTK_STOCK_CLOSE,"fermer",100,100,-1);
                    add_item_bar(tbar,GTK_STOCK_QUIT,"quitter",100,100,-1);
                    */

                    break;
//                case ItemBar:
//                    itemBarFunction(F);
//                    break;
//                case MenuBar:
//                    menuBarFunction(F);
//                    break;
//                case Tab:
//                    ongletFunction(F);
//                    break;
//                case MenuItem:
//                    menuItemFunction(F);
//                    break;
                default:
                    // Gérer le cas où le token n'est pas reconnu
                    break;
            }
            printf("\n fin de if");

        }
        else
                return;
    }
}


#endif // READER_H_INCLUDED
