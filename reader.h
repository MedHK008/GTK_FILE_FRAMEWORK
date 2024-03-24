#ifndef READER_H_INCLUDED
#define READER_H_INCLUDED


#define MAX 100
typedef enum{
    fenetre,
    Fixed,
    Label,
    Entry,
    Button,
    Radio,
    Checkbox,
    BoiteDialogue,
    Frame,
    Image,
    ProgBar,
    ScrollBar,
    spB,
    ToolBar,
    ItemBar,
    MenuBar,
    Tab,
    MenuItem
}Token;


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





Token string_to_token(const char *str) {
    if (!strcmp(str, "window")){
        return fenetre;
    }else if (!strcmp(str, "fixed")){
        return Fixed;
    } else if (!strcmp(str, "label")) {
        return Label;
    } else if (!strcmp(str, "entry")) {
        return Entry;
    } else if (!strcmp(str, "button")) {
        return Button;
    } else if (!strcmp(str, "button_radio")) {
        return Radio;
    } else if (!strcmp(str, "checkbox")) {
        return Checkbox;
    } else if (!strcmp(str, "boite_dialogue")) {
        return BoiteDialogue;
    } else if (!strcmp(str, "frame")) {
        return Frame;
    } else if (!strcmp(str, "image")) {
        return Image;
    } else if (!strcmp(str, "prog_bar")) {
        return ProgBar;
    } else if (!strcmp(str, "scroll_bar")) {
        return ScrollBar;
    } else if (!strcmp(str, "spin_button")) {
        return spB;
    } else if (!strcmp(str, "tool_bar")) {
        return ToolBar;
    } else if (!strcmp(str, "item_bar")) {
        return ItemBar;
    } else if (!strcmp(str, "menu_bar")) {
        return MenuBar;
    } else if (!strcmp(str, "Tab")) {
        return Tab;
    } else if (!strcmp(str, "menu_item")) {
        return MenuItem;
    } else {
        // Retourner une valeur par d�faut ou une valeur d'erreur
        return -1;
    }
}


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
                 // case Frame:
                    //frame *fr=add_frame(F);
                   // lire_son_elem(fr,F);
                   // c=epurer_blan(F);
                  //  break;
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
                    // G�rer le cas o� le token n'est pas reconnu
                    break;
            }
            printf("\n fin de if");

        }
        else
                return;
    }
}


#endif // READER_H_INCLUDED
