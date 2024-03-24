#ifndef TOOL_BAR_H_INCLUDED
#define TOOL_BAR_H_INCLUDED

// D�finition de la structure item_bar
typedef struct
{
    GtkWidget *widget; // Widget associ� � l'�l�ment de la barre d'outils
    gint h;
    gint w;
    const gchar *icon;    // Ic�ne associ�e � l'�l�ment
    gchar *text;      // Texte associ� � l'�l�ment
    GtkWidget *parent;
    gint pos;//// Position dans la barre d'outils
    gchar *name;

} item_bar;



// D�finition de la structure toolbar
typedef struct
{
    GtkWidget *widget;   // Widget de la barre d'outils
    GtkWidget *parent;   // Widget parent de la barre d'outils
    gchar orientation;   // Orientation de la barre d'outils ('h' pour horizontal, 'v' pour vertical)
    gint h;
    gint w;
    gchar *name;
    gint x;
    int y;
    gint style_tbar;
    gint style_icon;
    gint padding;

} toolbar;

// Fonction pour initialiser une barre d'outils avec une orientation sp�cifi�e
toolbar *initialiser_toolbar()
{
    toolbar *tbar = (toolbar *)g_malloc(sizeof(toolbar));
    tbar->widget=(GtkWidget *)g_malloc(sizeof(GtkWidget));
    tbar->parent=(GtkWidget *)g_malloc(sizeof(GtkWidget));
    //tbar->items->item=(item_bar *)g_malloc(sizeof(item_bar));
    tbar->orientation = 'h';
    tbar->widget = gtk_toolbar_new();
   // tbar->parent = pere;
    tbar->w = 0;
    tbar->h = 0;
    tbar->x = 0;
    tbar->y = 0;
    tbar->name=(gchar*)g_malloc(sizeof(gchar)*30);
    tbar->name[0]='\0';
    tbar->style_icon=1;
    tbar->style_tbar=1;
    tbar->padding=0;

    return tbar;
}

// Fonction pour d�finir l'orientation d'une barre d'outils
toolbar *creer_toolbar(toolbar *tbar)
{
    gtk_toolbar_set_style(GTK_TOOLBAR(tbar->widget),style_toolbar(tbar->style_tbar));
    gtk_toolbar_set_icon_size(GTK_TOOLBAR(tbar->widget),style_iconsize(tbar->style_icon));
    // V�rifie si l'orientation de la barre d'outils est horizontale
    if (tbar->orientation == 'h' || tbar->orientation == 'H')
        // Si oui, d�finir l'orientation de la barre d'outils comme horizontale
        gtk_orientable_set_orientation(GTK_TOOLBAR(tbar), GTK_ORIENTATION_HORIZONTAL);
    else
        // Sinon, d�finir l'orientation de la barre d'outils comme verticale
     gtk_orientable_set_orientation(GTK_TOOLBAR(tbar),GTK_ORIENTATION_VERTICAL);
}

//Fonction pour initialiser un �l�ment de la barre d'outils � partir d'une ic�ne stock�e
item_bar *initialiser_item_stock()
{
    item_bar *item = (item_bar *)g_malloc(sizeof(item_bar));
    item->widget = gtk_tool_item_new();
    item->icon=(gchar*)g_malloc(sizeof(gchar)*30);
    item->text=(gchar*)g_malloc(sizeof(gchar)*30);
    item->name=(gchar*)g_malloc(sizeof(gchar)*30);
    item->text[0] = '\0';
    //item->icon = '\0';
    item->name[0] = '\0';

    // Allocation de m�moire pour la structure style et initialisation de ses champs
    item->pos = -1;
    item->w = 40;
    item->h = 40;

    return item;
}
const gchar *element_icon(gint type)
{
   switch(type)
   {
       case 1: return GTK_STOCK_SAVE;
       case 2: return GTK_STOCK_QUIT;
       case 3: return GTK_STOCK_CLOSE;
       case 4: return GTK_STOCK_SAVE;
   }
}
// Fonction pour cr�er un GtkToolItem � partir d'un item_bar et l'ajouter � la barre d'outils
void creer_toolitem(item_bar *toolitem, toolbar *bar,gboolean choix,void (*fonction)(GtkWidget*,gpointer),gchar *type,gpointer data)
{
    /* Cr�ation � partir de stock */
    GtkWidget *box = gtk_vbox_new(FALSE, 5);
    printf("\n %s",toolitem->icon);
    GtkWidget *button = gtk_tool_button_new_from_stock(toolitem->icon);
    //gtk_toolbar_insert(GTK_TOOLBAR(ptoolbar), button, -1);
    gtk_box_pack_start(GTK_BOX(box), button, FALSE, FALSE, 0);
    // Ajoutez une �tiquette au conteneur
    GtkWidget *label = gtk_label_new(toolitem->text);
    gtk_box_pack_start(GTK_BOX(box), label, FALSE, FALSE, 0);
    gtk_container_add(GTK_CONTAINER(toolitem->widget), box);
    gtk_toolbar_insert(GTK_TOOLBAR(bar->widget), toolitem->widget, toolitem->pos);
    // D�finir la taille du widget si la largeur et la hauteur sont sp�cifi�es
    if (toolitem->w && toolitem->h)
        gtk_widget_set_size_request(toolitem->widget, toolitem->w, toolitem->h);
    if(choix)
       g_signal_connect(G_OBJECT(button),type, G_CALLBACK(fonction), data);

}


// Fonction pour cr�er et ajouter un s�parateur � une barre d'outils (toolbar) GTK
// Param�tres :
// - sep : Un pointeur vers le widget de s�parateur (sera initialis� dans la fonction)
// - pere : Le widget parent, g�n�ralement une barre d'outils GTK (GtkWidget *)
// - pos : La position � laquelle ins�rer le s�parateur dans la barre d'outils (gint)
// Retourne le widget de s�parateur cr��
GtkWidget *creer_separ(GtkWidget *sep, GtkWidget *pere, gint pos)
{
    // Cr�er un nouveau s�parateur
    sep = gtk_separator_tool_item_new();

    // Ins�rer le s�parateur dans la barre d'outils � la position sp�cifi�e
    gtk_toolbar_insert(GTK_TOOLBAR(pere), sep, pos);

    // Renvoyer le widget de s�parateur cr��
    return sep;
}

gint style_toolbar(gint type)
{
  switch(type){
     case 1:return GTK_TOOLBAR_ICONS;
     case 2:return GTK_TOOLBAR_TEXT;
     case 3:return GTK_TOOLBAR_BOTH;
     case 4:return GTK_TOOLBAR_BOTH_HORIZ;
  }

}

gint style_iconsize(gint type) {

    switch(type) {
        case 1:
            return GTK_ICON_SIZE_BUTTON;
        case 2:
            return GTK_ICON_SIZE_MENU;
        case 3:
            return GTK_ICON_SIZE_SMALL_TOOLBAR;
        case 4:
            return GTK_ICON_SIZE_LARGE_TOOLBAR;
        case 6:
            return GTK_ICON_SIZE_DND;
        case 7:
            return GTK_ICON_SIZE_DIALOG;
        default:
            return GTK_ICON_SIZE_INVALID;
    }
}

toolbar *toolBarFunction(toolbar *tool_bar,FILE *F)
{
    gchar* elem;
    elem=(gchar*)g_malloc(sizeof(gchar)*50);
    gchar c;
    do
    {
        fscanf(F,"%s",elem);
       if (strcmp(elem, "name") == 0) {
            if ((c = epurer_blan(F)) == '=') {
                if ((c = epurer_blan(F)) == '\"') {
                    int i = 0;
                    while ((c = fgetc(F)) != '\"')
                        tool_bar->name[i++] = c;
                    tool_bar->name[i] = '\0';
                }
            }
        } else if (strcmp(elem, "style_tbar") == 0) {
            if ((c = epurer_blan(F)) == '=')
               fscanf(F, "%d", &tool_bar->style_tbar);
        } else if (strcmp(elem, "style_icon") == 0) {
            if ((c = epurer_blan(F)) == '=') {
               fscanf(F, "%d", &tool_bar->style_icon);
            }
        } else if (strcmp(elem, "width") == 0) {
            if ((c = epurer_blan(F)) == '=') {
                fscanf(F, "%d", &tool_bar->w);
            }
        } else if (strcmp(elem, "height") == 0) {
            if ((c = epurer_blan(F)) == '=') {
                fscanf(F, "%d", &tool_bar->h);
            }
        } else if (strcmp(elem, "orientation") == 0) {
            if ((c = epurer_blan(F)) == '=') {
                    if ((c = epurer_blan(F)) == '\"') {
                      fscanf(F, "%c", &tool_bar->orientation);
                      fgetc(F);
                    }
            }
        }else if (strcmp(elem, "xligne") == 0) {
            if ((c = epurer_blan(F)) == '=') {
                fscanf(F, "%d", &tool_bar->x);
            }
        }
        else if (strcmp(elem, "yligne") == 0) {
            if ((c = epurer_blan(F)) == '=') {
                fscanf(F, "%d", &tool_bar->y);
            }
        }
        else if (strcmp(elem, "pdding") == 0) {
            if ((c = epurer_blan(F)) == '=') {
                fscanf(F, "%d", &tool_bar->padding);
            }
        }
    }while(strcmp(elem,">"));
    return tool_bar;
}

toolbar *add_toolbar(GtkWidget *box,FILE *F)
{
    toolbar *tool_bar=initialiser_toolbar();
    toolBarFunction(tool_bar,F);
    creer_toolbar(tool_bar);
    gtk_box_pack_start(GTK_BOX(box), tool_bar->widget, FALSE, FALSE, tool_bar->padding);
    return tool_bar;

}



item_bar *itemBarFunction(item_bar *item,FILE *F)
{
    gchar* elem;
    elem=(gchar*)g_malloc(sizeof(gchar)*50);
    gchar c;
    c=epurer_blan(F);
    printf("%c\n",c);
    if(c=='<')
    {
        fscanf(F,"%s",elem);
        if((strcmp(elem, "/tool_bar") == 0)&&((c=epurer_blan(F))=='>'))
        {
            printf("22222hello\n");

            return (item_bar*)NULL;
        }

        else
        {
            do
            {

       if (strcmp(elem, "name") == 0) {
            if ((c = epurer_blan(F)) == '=') {
                if ((c = epurer_blan(F)) == '\"') {
                    int i = 0;
                    while ((c = fgetc(F)) != '\"')
                        item->name[i++] = c;
                    item->name[i] = '\0';
                }
            }
        } if (strcmp(elem, "icon") == 0) {
            if ((c = epurer_blan(F)) == '=') {
               /*     gchar ICON_elem[30];
                if ((c = epurer_blan(F)) == '\"') {
                    int i = 0;

                    while ((c = fgetc(F)) != '\"')
                        ICON_elem[i++] = c;
                    ICON_elem[i] = '\0';
                }
                item->icon=ICON_elem;*/
                fscanf(F,"%s",item->icon);
            }
        }if (strcmp(elem, "label") == 0) {
            if ((c = epurer_blan(F)) == '=') {
                if ((c = epurer_blan(F)) == '\"') {
                    int i = 0;
                    while ((c = fgetc(F)) != '\"')
                        item->text[i++] = c;
                    item->text[i] = '\0';
                }
            }
        } else if (strcmp(elem, "width") == 0) {
            if ((c = epurer_blan(F)) == '=') {
                fscanf(F, "%d", &item->w);
            }
        } else if (strcmp(elem, "height") == 0) {
            if ((c = epurer_blan(F)) == '=') {
                fscanf(F, "%d", &item->h);
            }
        } else if (strcmp(elem, "position") == 0) {
            if ((c = epurer_blan(F)) == '=') {
                fscanf(F, "%d", &item->pos);
            }
        }
        fscanf(F,"%s",elem);
        }while(strcmp(elem,">"));
        }

    }

    return item;
}
gint add_item_bar(toolbar *bar_pere,FILE *F)
{
    item_bar *element=initialiser_item_stock();
    element=itemBarFunction(element,F);
    if(element)
    {
        creer_toolitem(element,bar_pere,0,NULL,NULL,NULL);
        return 1;
    }
    return 0;

}
void lire_son_item(toolbar *tbar ,FILE *F)
{
    while(add_item_bar(tbar,F));
}




#endif // TOOL_BAR_H_INCLUDED
