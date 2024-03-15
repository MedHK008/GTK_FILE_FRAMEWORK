#ifndef WINDOW_H_INCLUDED
#define WINDOW_H_INCLUDED



typedef struct {
    GtkWidget *window; // Pointeur vers le widget de la fenêtre
    gchar *titre; // Titre de la fenêtre
    gchar *icon; // Chemin vers l’icône de la fenêtre
    gchar*name;
    gchar* bgcolor;
    guint hauteur;
    guint largeur;
    gint posx;
    gint posy;
    gint position_init;// Position initiale de la fenêtre
    guint border_width;
    gboolean modifiable; // Indique si la taille de la fenêtre peut être modifiée
    // Ajoutez d'autres champs si nécessaire
} Fenetre;

Fenetre* initialiser_win(gchar* titre, gchar* icon_path,gchar *name,gchar*bgcolor, guint h, guint w, gint pos, gint x, gint y,guint border, gboolean resizable)
{
    Fenetre* win = malloc(sizeof(Fenetre));
    if (!win) {
        printf("\nErreur d'allocation de mémoire.");
        exit(-1);
    }

    win->window = NULL; // Initialisez à NULL avant de créer la fenêtre

    // Copiez le titre
    if (titre) {
        win->titre=malloc(50*sizeof(gchar));

        win->titre = g_strdup(titre);

    } else {
        win->titre = NULL;
    }

    // Copiez le chemin de l'icône
    if (icon_path) {
        win->icon=malloc(200*sizeof(gchar));
        win->icon = g_strdup(icon_path);
    } else {
        win->icon = NULL;
    }
    //Copier le nom de la fenetre

    if (name) {
        win->name=malloc(25*sizeof(gchar));
        win->name = g_strdup(name);
    } else {
        win->name = NULL;
    }
    if (bgcolor) {
        win->bgcolor=malloc(20*sizeof(gchar));
        win->bgcolor = g_strdup(bgcolor);
    } else {
        win->bgcolor = NULL;
    }
    win->hauteur = h;
    win->largeur = w;
    win->position_init = pos;
    win->posx = x;
    win->posy = y;
    win->border_width=border;
    win->modifiable = resizable;

    return win;
}

void create_window(Fenetre *W) {
    // Créez la fenêtre
    W->window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    // Ajoutez le titre s'il existe
    if (W->titre) {

        gtk_window_set_title(GTK_WINDOW(W->window), W->titre);
    }

    // Ajoutez l'icône s'il existe
    if (W->icon) {
        gtk_window_set_icon_from_file(GTK_WINDOW(W->window), W->icon, NULL);
    }
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
    if (W->hauteur > 0 && W->largeur > 0) {
        gtk_window_set_default_size(GTK_WINDOW(W->window), W->largeur, W->hauteur);
    }

    // Configurez la position initiale de la fenêtre
    switch (W->position_init) {
        case 1:
            gtk_window_set_position(GTK_WINDOW(W->window), GTK_WIN_POS_NONE);
            break;
        case 2:
            gtk_window_set_position(GTK_WINDOW(W->window), GTK_WIN_POS_CENTER);
            break;
        case 3:
            gtk_window_set_position(GTK_WINDOW(W->window), GTK_WIN_POS_MOUSE);
            break;
        case 4:
            gtk_window_set_position(GTK_WINDOW(W->window), GTK_WIN_POS_CENTER_ALWAYS);
            break;
        case 5:
            gtk_window_set_position(GTK_WINDOW(W->window), GTK_WIN_POS_CENTER_ON_PARENT);
            break;
        default:
            gtk_window_move(GTK_WINDOW(W->window), W->posx, W->posy);
            break;
    }
    //Definir l'epaisseur de la bordure
     gtk_container_set_border_width(GTK_CONTAINER(W->window),W->border_width);

    // Si redimensionnable, autorisez le redimensionnement
    if (W->modifiable) {
        gtk_window_set_resizable(GTK_WINDOW(W->window), TRUE);
    } else {
        gtk_window_set_resizable(GTK_WINDOW(W->window), FALSE);
    }
}

Fenetre* add_window()
{
    Fenetre *ma_fenetre = initialiser_win("Instagram", NULL, "F1", "#f72585", 3840, 2160, 2, 0, 0, 25, TRUE);
    create_window(ma_fenetre);
    return((Fenetre*)ma_fenetre);
}

#endif // WINDOW_H_INCLUDED
