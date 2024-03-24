#ifndef READER_H_INCLUDED
#define READER_H_INCLUDED
#include "menu.h"

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
    MenuItem,
    Root

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
    } else if (!strcmp(str, "menu_item"))
        return MenuItem;
      else if (!strcmp(str, "root"))
        return Root;

     else {
        // Retourner une valeur par défaut ou une valeur d'erreur
        return -1;
    }
}
void add_to_parent(GtkWidget* child,GtkWidget* parent_w, gchar* parent,guint posx, guint posy)
{
  if(!strcmp(parent,"/fixed"))
    gtk_fixed_put(GTK_FIXED(parent_w),child,posx,posy);
 else if(!strcmp(parent,"/box"))
    gtk_box_pack_start(GTK_BOX(parent_w),child,FALSE,FALSE,0);
 else if(!strcmp(parent,"/window"))
    gtk_container_add(GTK_CONTAINER(parent_w),child);

}
void lire_fichier(FILE*F,Fenetre* W,GtkWidget* parent_w , gchar* parent_token)
{
    gchar c ;
    gchar current_token[MAX];
    Token tok;
    c=epurer_blan(F);
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
                       fin_programme(W);
                  }
                c=epurer_blan(F);
                return ;
            }
             tok=string_to_token(current_token);
             switch(tok)
             {
               case Root: c=epurer_blan(F);
                          c=epurer_blan(F);

                   break;

                case fenetre:
                    printf("\nswitch F");
                    W=add_window(F);
                    lire_fichier(F,W,W->window,"/window");
                    printf("\nsortie F");
                    c=epurer_blan(F);
                    break;
                case Fixed:
                    fixed* fix=init_gtk_fixed();
                    add_to_parent(fix->fixed,parent_w,parent_token,0,0);
                    c=epurer_blan(F);
                    lire_fichier(F,W,fix->fixed,"/fixed");
                     printf("\nsortie FIXED");
                    c=epurer_blan(F);

                    break;
//                case Label:
//                    labelFunction(F);
//                    break;
//                case Entry:
//                    entryFunction(F);
//                    break;
//                case Button:
//                    ButtonSimple* B=add_button(F);
//                    add_widget_to_fixed(fixed0,B->button,50,50);
//                    c=epurer_blan(F);
//                    break;
//                case Radio:
//                    buttonRadioFunction(F);
//                    break;
//                case Checkbox:
//                    checkboxFunction(F);
//                    break;
//                case BoiteDialogue:
//                    boiteDialogueFunction(F);
//                    break;
//                case Frame:
//                    frameFunction(F);
//                    break;
//                case Image:
//                    imageFunction(F);
//                    break;
//                case ProgBar:
//                    progBarFunction(F);
//                    break;
//                case ScrollBar:
//                    scrollBarFunction(F);
//                    break;
//                case spB:
//                    spinButtonFunction(F);
//                    break;
//                case ToolBar:
//                    toolBarFunction(F);
//                    break;
//                case ItemBar:
//                    itemBarFunction(F);
//                    break;
//                case Tab:
//                    ongletFunction(F);
//                    break;
                  case MenuBar:
                        menubar *mbar =add_menubar(mbar,F);
                         ajouter_elems(mbar,F);
                        add_to_parent(mbar->menubar,parent_w,parent_token,mbar->posx,mbar->posy);
                        printf("\nSortirADD");
                        c=epurer_blan(F);

                        break;
//                case MenuItem:
//                    menuItemFunction(F);
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

//void lire_fichier(FILE *F,Fenetre *Win ,gchar* parent_token)
//{
//    gchar c;
//    gchar current_token[MAX];
//    Token tok;
//    c = epurer_blan(F);
//    while (c != EOF) {
//        if (c == '<')
//        {
//
//            fscanf(F, "%s", current_token);
//             if (!strcmp(current_token , parent_token))
//            {
//               // if(tok==Root)
//
//                return ;
//            }
//            printf("\n2222");
//            tok = string_to_token(current_token);
//
//
//            switch (tok) {
//            case Root:
//                   c=epurer_blan(F);
//                   printf("\n%c",c);
//                   c=epurer_blan(F);
//                   printf("\n%c",c);
//                   break;
//                case fenetre:
//                    {
//                        Win = add_window(F);
//                        lire_fichier(F,Win,"/window"); // Appel récursif pour lire les descendants de la fenêtre
//
//                        break;
//                    }
//                case Fixed:
//                    {
//                        // Ajoutez ici le code pour gérer le conteneur Fixed
//                        // Appel récursif pour lire les descendants du conteneur Fixed
//                        break;
//                    }
//
//                case MenuBar:
//                    {
//                        menubar *mbar = add_menubar(mbar, F);
//                        ajouter_elems(mbar, F);
//                        // Ajoutez le menu bar à son conteneur parent (s'il y en a un)
//                        c = epurer_blan(F);
//                        break;
//                    }
//                // Ajoutez des cas pour d'autres conteneurs si nécessaire
//                default:
//                    printf("\nDEFAULT");
//                    break;
//            }
//        } else {
//            return;
//        }
//    }
//}
//


#endif // READER_H_INCLUDED
