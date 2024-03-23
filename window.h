#ifndef WINDOW_H_INCLUDED
#define WINDOW_H_INCLUDED




typedef struct {
  GtkWidget *window; // Pointeur vers le widget de la fenêtre (obligatoire)
  gchar *titre; // Titre de la fenêtre (facultatif, par défaut : "")
  gchar *icon; // Chemin vers l'icône de la fenêtre (facultatif, par défaut : "")
  gchar *name; // Nom de la fenêtre (facultatif, par défaut : "")
  gchar *bgcolor; // Couleur de fond de la fenêtre (facultatif, par défaut : "#FFFFFF")
  guint hauteur; // Hauteur de la fenêtre en pixels (obligatoire)
  guint largeur; // Largeur de la fenêtre en pixels (obligatoire)
  gint posx; // Position horizontale de la fenêtre par rapport à l'écran (facultatif, par défaut : -1)
  gint posy; // Position verticale de la fenêtre par rapport à l'écran (facultatif, par défaut : -1)
  GtkWindowPosition position_init; // Position initiale de la fenêtre (obligatoire)
       /*GTK_WIN_POS_CENTER
         GTK_WIN_POS_CENTER_ALWAYS
         GTK_WIN_POS_MOUSE
         GTK_WIN_POS_NONE */
  guint border_width; // Largeur de la bordure de la fenêtre en pixels (facultatif, par défaut : 0)
  gboolean modifiable; // Indique si la taille de la fenêtre peut être modifiée (facultatif, par défaut : TRUE)
} Fenetre;

//Fonction pour initialiser la structure fenetre
Fenetre* initialiser_win(gchar* titre, gchar* icon_path,gchar *name,gchar*bgcolor, guint h, guint w, GtkWindowPosition pos,
                          gint x, gint y,guint border, gboolean resizable
                        )
{
    Fenetre* win =(Fenetre*) malloc(sizeof(Fenetre));
    if (!win) {
        printf("\nErreur d'allocation de mémoire.");
        exit(-1);
    }

    win->window = NULL; // Initialisez à NULL avant de créer la fenêtre

    // Copiez le titre
    if (titre)
        win->titre = g_strdup(titre);
    else
        win->titre = NULL;

    // Copiez le chemin de l'icône
    if (icon_path)
        win->icon = g_strdup(icon_path);//cette fonction alloue l'espace memoire necessaire et copy la chaine dans le variable
     else
        win->icon = NULL;
    //Copier le nom de la fenetre
    if (name)
        win->name = g_strdup(name);
     else
        win->name = NULL;
    if (bgcolor)
        win->bgcolor = g_strdup(bgcolor);
     else
       win->bgcolor = NULL;

    win->hauteur = h;
    win->largeur = w;
    win->position_init = pos;
    win->posx = x;
    win->posy = y;
    win->border_width=border;
    win->modifiable = resizable;

    return win;
}

void create_window(Fenetre *W)
{
    // Créez la fenêtre
    W->window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    // Ajoutez le titre s'il existe
    if (W->titre)
        gtk_window_set_title(GTK_WINDOW(W->window), W->titre);
    // Ajoutez l'icône s'il existe
    if (W->icon)
        gtk_window_set_icon_from_file(GTK_WINDOW(W->window), W->icon, NULL);
    //Ajout de couleur de fond
    if(W->bgcolor)
    {
        GdkRGBA color;
        // Utilisez gdk_rgba_parse pour définir la couleur de fond de la fenêtre
        if (gdk_rgba_parse(&color,W->bgcolor)) {
            gtk_widget_override_background_color(W->window, GTK_STATE_NORMAL, &color);
        } else {
            g_warning("\nImpossible de définir la couleur de fond.");
        }
    }
    // Si la hauteur et la largeur sont supérieures à 0, configurez la taille par défaut
    if (W->hauteur > 0 && W->largeur > 0)
        gtk_window_set_default_size(GTK_WINDOW(W->window), W->largeur, W->hauteur);
    
   //Configurer le positionnement
     if(!W->position_init)
        // Utilisez les coordonnées spécifiées
        gtk_window_move(GTK_WINDOW(W->window), W->posx, W->posy);
     else
         gtk_window_set_position(GTK_WINDOW(W->window), W->position_init);
    
    // Définir l'épaisseur de la bordure
    gtk_container_set_border_width(GTK_CONTAINER(W->window), W->border_width);

    // Si redimensionnable, autorisez le redimensionnement
    gtk_window_set_resizable(GTK_WINDOW(W->window), W->modifiable);
}
//Fonction pour ajouter une fenetre
Fenetre* add_window(gchar* title, gchar* icon_path, gchar* name, gchar* bgcolor,
                   guint width, guint height, GtkWindowPosition pos_init,
                   guint posx, guint posy, guint border_size, gboolean resizable)
{
    Fenetre* ma_fenetre = initialiser_win(title, icon_path, name, bgcolor, width, height, pos_init, posx, posy, border_size, resizable);
    create_window(ma_fenetre); 
    return (Fenetre*)ma_fenetre;
}
#endif // WINDOW_H_INCLUDED
