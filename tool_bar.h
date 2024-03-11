#ifndef TOOL_BAR_H_INCLUDED
#define TOOL_BAR_H_INCLUDED


typedef struct
{
    gint w; // Largeur
    gint h; // Hauteur
} style;


// Définition de la structure item_bar
typedef struct
{
    GtkWidget *widget; // Widget associé à l'élément de la barre d'outils
    style *s;         // Style de l'élément (position, largeur, hauteur)
    const gchar *icon;    // Icône associée à l'élément
    gchar *text;      // Texte associé à l'élément
    GtkWidget *parent;
    gint pos;//// Position dans la barre d'outils

} item_bar;

// Définition de la structure toolbar
typedef struct
{
    GtkWidget *widget;   // Widget de la barre d'outils
    GtkWidget *parent;   // Widget parent de la barre d'outils
    gchar orientation;   // Orientation de la barre d'outils ('h' pour horizontal, 'v' pour vertical)

} toolbar;

// Fonction pour initialiser une barre d'outils avec une orientation spécifiée
toolbar *initialiser_toolbar(GtkWidget *pere,gchar orientation,GtkToolbarStyle stl,GtkIconSize siz)
{
    toolbar *tbar = (toolbar *)g_malloc(sizeof(toolbar));
    tbar->widget=(GtkWidget *)g_malloc(sizeof(GtkWidget));
    tbar->parent=(GtkWidget *)g_malloc(sizeof(GtkWidget));
    //tbar->items->item=(item_bar *)g_malloc(sizeof(item_bar));
    tbar->orientation = orientation;
    tbar->widget = gtk_toolbar_new();
    tbar->parent = pere;
    if(stl)
        gtk_toolbar_set_style(GTK_TOOLBAR(tbar->widget),stl);
    if(siz)
        gtk_toolbar_set_icon_size(GTK_TOOLBAR(tbar->widget),siz);
    return tbar;
}

// Fonction pour définir l'orientation d'une barre d'outils
toolbar *creer_toolbar(toolbar *tbar)
{
    // Vérifie si l'orientation de la barre d'outils est horizontale
    if (tbar->orientation == 'h' || tbar->orientation == 'H')
        // Si oui, définir l'orientation de la barre d'outils comme horizontale
        gtk_orientable_set_orientation(GTK_TOOLBAR(tbar), GTK_ORIENTATION_HORIZONTAL);
    else
        // Sinon, définir l'orientation de la barre d'outils comme verticale
     gtk_orientable_set_orientation(GTK_TOOLBAR(tbar),GTK_ORIENTATION_VERTICAL);
}

//Fonction pour initialiser un élément de la barre d'outils à partir d'une icône stockée
item_bar *initialiser_item_stock(GtkWidget *pere,const gchar *icon, gchar *lab, gint w, gint h, gint pos)
{
    item_bar *item = (item_bar *)g_malloc(sizeof(item_bar));
    item->widget = gtk_tool_item_new();
    item->text = lab;
    item->icon = icon;

    // Allocation de mémoire pour la structure style et initialisation de ses champs
    item->s = (style *)g_malloc(sizeof(style));
    item->pos = pos;
    item->s->w = w;
    item->s->h = h;

    return item;
}

// Fonction pour créer un GtkToolItem à partir d'un item_bar et l'ajouter à la barre d'outils
void creer_toolitem(item_bar *toolitem, toolbar *bar,gboolean choix,void (*fonction)(GtkWidget*,gpointer),gchar *type,gpointer data)
{
    /* Création à partir de stock */
    GtkWidget *box = gtk_vbox_new(FALSE, 5);
    GtkWidget *button = gtk_tool_button_new_from_stock(toolitem->icon);
    //gtk_toolbar_insert(GTK_TOOLBAR(ptoolbar), button, -1);
    gtk_box_pack_start(GTK_BOX(box), button, FALSE, FALSE, 0);
    // Ajoutez une étiquette au conteneur
    GtkWidget *label = gtk_label_new(toolitem->text);
    gtk_box_pack_start(GTK_BOX(box), label, FALSE, FALSE, 0);
    gtk_container_add(GTK_CONTAINER(toolitem->widget), box);
    gtk_toolbar_insert(GTK_TOOLBAR(bar->widget), toolitem->widget, toolitem->pos);
    // Définir la taille du widget si la largeur et la hauteur sont spécifiées
    if (toolitem->s->w && toolitem->s->h)
        gtk_widget_set_size_request(toolitem->widget, toolitem->s->w, toolitem->s->h);
    if(choix)
       g_signal_connect(G_OBJECT(button),type, G_CALLBACK(fonction), data);

}


// Fonction pour créer et ajouter un séparateur à une barre d'outils (toolbar) GTK
// Paramètres :
// - sep : Un pointeur vers le widget de séparateur (sera initialisé dans la fonction)
// - pere : Le widget parent, généralement une barre d'outils GTK (GtkWidget *)
// - pos : La position à laquelle insérer le séparateur dans la barre d'outils (gint)
// Retourne le widget de séparateur créé
GtkWidget *creer_separ(GtkWidget *sep, GtkWidget *pere, gint pos)
{
    // Créer un nouveau séparateur
    sep = gtk_separator_tool_item_new();

    // Insérer le séparateur dans la barre d'outils à la position spécifiée
    gtk_toolbar_insert(GTK_TOOLBAR(pere), sep, pos);

    // Renvoyer le widget de séparateur créé
    return sep;
}
static toolbar *ptoolbar = NULL;

void OnChangeOrientation(GtkWidget *widget, gpointer data)
{
   /* Modification de l'orientation */
   gtk_orientable_set_orientation(GTK_TOOLBAR(ptoolbar->widget),
      GPOINTER_TO_INT(data));

}


void quitter(GtkWidget *widget,gpointer data)
{
    gtk_main_quit();
}
void onclicked(GtkWidget *widget,gchar * fonction,gchar *type,gpointer data)
{
    g_signal_connect(G_OBJECT(widget),type,G_CALLBACK(fonction),data);
}

#endif // TOOL_BAR_H_INCLUDED
