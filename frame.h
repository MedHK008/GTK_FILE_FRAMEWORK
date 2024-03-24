#ifndef FRAME_H_INCLUDED
#define FRAME_H_INCLUDED
#include "scrollbar.h"
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
        // Retourner une valeur par défaut ou une valeur d'erreur
        return -1;
    }
}


// Structure pour repr�senter un cadre (frame) avec des �l�ments associ�s
typedef struct
{
    GtkWidget *widget;          // Le widget GTK repr�sentant le cadre
    GtkWidget *parent;          // Le parent du cadre
    gint xligne;                // Position horizontale de l'�tiquette dans le cadre
    gint yligne;                // Position verticale de l'�tiquette dans le cadre
    texte *text;                // Structure de texte associ�e au cadre
    GtkWidget *conteneur;       // Le conteneur associ� au cadre (peut �tre un label ou autre)
    gint type;         // Type d'ombre du cadre
    gint x;
    gint y;
    gchar *name;
} frame;
gint style_border(gint type)
{
    switch(type)
    {
        case 1: return GTK_SHADOW_ETCHED_IN;
        case 2: return GTK_SHADOW_ETCHED_OUT;
        case 3: return GTK_SHADOW_IN;
        case 5: return GTK_SHADOW_NONE;
        case 4: return GTK_SHADOW_OUT;
    }
}
// Fonction pour initialiser une structure de cadre avec des param�tres sp�cifi�s
frame *initialiser_frame()
{
    // Allouer dynamiquement la m�moire pour la structure de cadre
    frame *fr = (frame *)g_malloc(sizeof(frame));

    // Initialiser les champs de la structure avec les valeurs sp�cifi�es
    fr->widget = gtk_frame_new(NULL);
    fr->type = 1;
    fr->xligne = 0.1;
    fr->yligne = 0.1;
    fr->name=(gchar*)g_malloc(sizeof(gchar));
    fr->name[0]='\0';
    // Retourner la structure de cadre initialis�e
    return fr;
}

// Fonction pour cr�er un cadre en utilisant les param�tres sp�cifi�s dans la structure
void creer_frame(frame *fr)
{
    // Cr�er une cha�ne de caract�res format�e pour l'�tiquette avec des propri�t�s de texte sp�cifi�es
    gchar *lab = g_strdup_printf("<span  font_desc=\"%d\" style=\"%s\" foreground=\"%s\" font_family=\"%s\" underline=\"%s\">%s</span> ", fr->text->taille_text, fr->text->style, fr->text->couleur_text, fr->text->police, fr->text->underline, fr->text->tex);

    // Cr�er un widget de label GTK et d�finir son contenu avec la cha�ne format�e
    GtkWidget *label = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(label), lab);

     //D�finir le label comme �tiquette du cadre
    gtk_frame_set_label_widget(GTK_FRAME(fr->widget), label);

    // Assigner le label au conteneur du cadre
    //fr->conteneur = label;

    // Si des positions sp�cifi�es, les appliquer � l'�tiquette du cadre
    if (fr->xligne || fr->yligne)
        gtk_frame_set_label_align(GTK_FRAME(fr->widget), fr->xligne, fr->yligne);

    // Si un type d'ombre sp�cifi�, l'appliquer au cadre
    if (fr->type)
        gtk_frame_set_shadow_type(GTK_FRAME(fr->widget), fr->type);
}
frame *framefunction(frame *fr,FILE *F)
{
    gchar* elem;
    elem=(gchar*)g_malloc(sizeof(gchar)*50);
    gchar c;
    do
    {
        fscanf(F,"%s",elem);
        printf("%s\n",elem);
       if (strcmp(elem, "name") == 0) {
            if ((c = epurer_blan(F)) == '=') {
                if ((c = epurer_blan(F)) == '\"') {
                    int i = 0;
                    while ((c = fgetc(F)) != '\"')
                        fr->name[i++] = c;
                    fr->name[i] = '\0';
                }
            }
        } else if (strcmp(elem, "type") == 0) {
            if ((c = epurer_blan(F)) == '=')
               fscanf(F, "%d", &fr->type);
        } else if (strcmp(elem, "xligne_text") == 0) {
            if ((c = epurer_blan(F)) == '=') {
               fscanf(F, "%d", &fr->xligne);
            }
        }else if (strcmp(elem, "yligne_text") == 0) {
            if ((c = epurer_blan(F)) == '=') {
               fscanf(F, "%d", &fr->yligne);
            }
        }else if (strcmp(elem, "xligne") == 0) {
            if ((c = epurer_blan(F)) == '=') {
                fscanf(F, "%d", &fr->x);
            }
        }
        else if (strcmp(elem, "yligne") == 0) {
            if ((c = epurer_blan(F)) == '=') {
                fscanf(F, "%d", &fr->y);
            }
        }
    }while(strcmp(elem,">"));
    return fr;
}
void lire_son_elem(frame *fr,FILE *F)
{
    GtkWidget *fix=gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(fr->widget),fix);
    if(!F) exit(-1);
    gchar c ;
    gchar current_token[30];
    Token tok;
    c=epurer_blan(F);
    while(c!=EOF)
    {
        printf("%c",c);
        if(c=='<')
        {
             fscanf(F,"%s",current_token);
             printf("djddjdjdjdjdjdjdjdj11111111111\n");
             if(!strcmp(current_token,"/frame"))
             {
                 printf("djddjdjdjdjdjdjdjdj11111111111\n");
                 c=epurer_blan(F);
                 return;
             }
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
                   gtk_fixed_put(GTK_FIXED(fix),lab->widget,lab->x,lab->y);
                   c=epurer_blan(F);
                   break;
//                case Entry:
//                    entryFunction(F);
//                    break;
                case Button:
                    ButtonSimple* B=add_button(F);
                    gtk_fixed_put(GTK_FIXED(fix),B->button,50,50);
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
                  //case Frame:
                   // frame *fr=add_frame(fix,F);
                   // lire_son_elem(fr,F);
                    //c=epurer_blan(F);
                    //break;
                 case Image:
                   image *img=add_image(F);
                   gtk_fixed_put(GTK_FIXED(fix),img->widget,img->x,img->y);
                   c=epurer_blan(F);
                   break;
                  case ProgBar:
                      barre_prog *prog_bar=add_progress_bar(F);
                      gtk_fixed_put(GTK_FIXED(fix),prog_bar->widget,prog_bar->x,prog_bar->y);
                      c=epurer_blan(F);
                      break;
                case ScrollBar:
                    barre_def *scbar=add_scrollbar(fr,fix,F);
                    c=epurer_blan(F);
                    break;
//                case spB:
//                    spinButtonFunction(F);
//                    break;
                //case ToolBar:
                   // toolbar *tbar=add_toolbar(pvbox,F);
                    //lire_son_item(tbar ,F);
                    //c=epurer_blan(F);
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
frame * add_frame(GtkWidget *pere,FILE *F)
{
    frame *fr=initialiser_frame();
    fr=framefunction(fr,F);
    fr->text=initialiser_texte();
    fr->text=textefunction(fr->text,F);
    creer_frame(fr);
    gtk_fixed_put(GTK_FIXED(pere),fr->widget,fr->x,fr->y);
    return fr;
}



#endif // FRAME_H_INCLUDED
