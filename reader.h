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
    boiteDialogue,
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

Saisie *En[MAX];






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
        return boiteDialogue;
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


BoiteDialogue* lire_fichier(FILE*F,fixed* fixed0)
{
    if(!F) exit(-1);
    gchar c ;
    gchar current_token[MAX];
    Token tok;
    gchar*elem=(gchar*)g_malloc(sizeof(gchar)*50);
    int into =0;
    c=epurer_blan(F);
    BoiteDialogue *BD ;
    ButtonSimple* B;
    Saisie*E;
    while(c!=EOF)
    {
        if(c=='<')
        {
            c=fgetc(F);
            if(c!='/')
            {
            ungetc(c,F);
             fscanf(F,"%s",current_token);


             tok=string_to_token(current_token);
             switch(tok) {
//                case fenetre:
//                    windowFunction(F);
//                    break;
//                case Fixed:
//                    fixedFunction(F);
//                    break;
//                case Label:
//                    labelFunction(F);
//                    break;
                case Entry:

                    E=Add_Entry(F);
                    c=epurer_blan(F);
                    if(into==1)
                        ajouter_a_boite_dialogue(BD,E->entree,E->x_pos,E->y_pos);
                    else if(into==0)
                        add_widget_to_fixed(fixed0,E->entree,E->x_pos,E->y_pos);
                    break;
//                case Button:
//                     B=add_button(F);
////                    add_widget_to_fixed(fixed0,B->button,50,50);
//                    c=epurer_blan(F);
//                     if(into==1)
//                        ajouter_a_boite_dialogue(BD,B->button,100,100);
//                    else if(into==0)
//                        add_widget_to_fixed(fixed0,B->button,100,100);
//                    break;
//                case Radio:
//                    buttonRadioFunction(F);
//                    break;
//                case Checkbox:
//                    checkboxFunction(F);
//                    break;
                case boiteDialogue:

                    into=1;
                    BD=Add_boite_dialogue(F);
                    c=epurer_blan(F);
                    break;
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


        }
        else
        {

            fscanf(F,"%s",elem);
            if(!strcmp(elem,"boite_dialogue>"))
            {


                 into=0;

            }
            c=epurer_blan(F);

        }

    }
    }
    return BD;
}


#endif // READER_H_INCLUDED
