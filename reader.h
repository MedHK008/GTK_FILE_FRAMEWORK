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
    } else if (!strcmp(str, "radio")) {
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
        return -1;
    }
}


void lire_fichier(FILE*F,fixed* fixed0)
{
    if(!F) exit(-1);
    gchar c ;
    gchar current_token[MAX];
    Token tok;
    c=epurer_blan(F);
    GtkWidget* radiopar = gtk_radio_button_new(NULL);
    while(c!=EOF)
    {
        if(c=='<')
        {
             fscanf(F,"%s",current_token);
             tok=string_to_token(current_token);
             switch(tok) {
                case Button:
                    texte* txt_cocher=initialiser_texte(20,30,"exemple des bouttons a cocher",3,"Verdana",12,"italic",NULL,"#000000","#FFFFFF",NULL);
                    ButtonSimple* B=add_button(F,txt_cocher);
                    add_widget_to_fixed(fixed0,B->button,B->x_pos,B->y_pos);
                    c=epurer_blan(F);
                    break;
                case Radio:
                    elem_radio* R = add_radio(F, fixed0->fixed, radiopar);
                    if (R) {
                        add_widget_to_fixed(fixed0, R->pRadio,R->x_pos,R->y_pos);
                    }
                    c=epurer_blan(F);
                    break;
                case Checkbox:
                    cocher* C = add_cocher(F);
                    add_widget_to_fixed(fixed0,C->boutcoche,C->x_pos,C->y_pos);
                    c=epurer_blan(F);
                    break;
                case spB:
                    SpinButton* SPB=add_spin_button_from_file(F);
                    add_widget_to_fixed(fixed0,SPB->SpinButton,SPB->x_pos,SPB->y_pos);
                    c=epurer_blan(F);
                    break;
                default:
                    break;
            }
            printf("\n fin de if");
        }
        else
                return;
    }
}


#endif // READER_H_INCLUDED
