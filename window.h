#ifndef WINDOW_H_INCLUDED
#define WINDOW_H_INCLUDED




typedef struct f{
  GtkWidget *window; // Pointeur vers le widget de la fenêtre (obligatoire)
  GtkWidget *scrollwin; // Ajout d'un pointeur vers GtkScrolledWindow
  gboolean scroll_bool;
  gchar *titre; // Titre de la fenêtre (facultatif, par défaut : "")
  gchar *icon; // Chemin vers l'icône de la fenêtre (facultatif, par défaut : "")
  gchar *name; // Nom de la fenêtre (facultatif, par défaut : "")
  gchar *bgcolor; // Couleur de fond de la fenêtre (facultatif, par défaut : "#FFFFFF")
  gchar* bgimg ;
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
  struct f *svt;
} Fenetre;


//Fonction pour initialiser la structure fenetre
Fenetre* init_window()
{
    Fenetre* win = (Fenetre*)malloc(sizeof(Fenetre));
    if (!win) {
        printf("\nErreur d'allocation !!\n");
        exit(0);
    }
    win->name=(gchar*)g_malloc(sizeof(gchar)*30);
    win->name[0] ='\0';

    win->titre=(gchar*)g_malloc(sizeof(gchar)*30);
    win->titre[0]='\0';

    win->bgcolor=(gchar*)g_malloc(sizeof(gchar)*30);
    win->bgcolor[0]='\0';

    win->name=(gchar*)g_malloc(sizeof(gchar)*30);
    win->name[0]='\0';

    win->icon=(gchar*)g_malloc(sizeof(gchar)*100);
    win->icon[0]='\0';

    win->bgimg=(gchar*)g_malloc(sizeof(gchar)*100);
    win->bgimg[0]='\0';

    win->scroll_bool=FALSE;
    win->largeur=0;
    win->hauteur=0;
    win->posx=0;
    win->posy=0;
    win->border_width=0;
    win->modifiable=TRUE;
    win->svt=NULL;
    return win;
}
//Fonction pour transformer une chaine a un element de type GtkWindowPosition
GtkWindowPosition string_to_window_position( gchar *str)
{
    if (strcmp(str, "none") == 0)
        return GTK_WIN_POS_NONE;
    else if (strcmp(str, "center") == 0)
        return GTK_WIN_POS_CENTER;
     else if (strcmp(str, "mouse") == 0)
        return GTK_WIN_POS_MOUSE;
     else if (strcmp(str, "center-always") == 0)
        return GTK_WIN_POS_CENTER_ALWAYS;
     else if (strcmp(str, "center-on-parent") == 0)
        return GTK_WIN_POS_CENTER_ALWAYS;
     else
       return GTK_WIN_POS_NONE;

}

 Fenetre* windowFunction(Fenetre* w,FILE* F)
 {
    int i;
    gchar* elem;
    elem=(gchar*)g_malloc(sizeof(gchar)*30);
    gchar c;
    do
    {
        fscanf(F,"%s",elem);
       if (strcmp(elem, "name") == 0)
        {
            if ((c = epurer_blan(F)) == '=')
                if ((c = epurer_blan(F)) == '\"')
                {
                     i= 0;
                    while ((c = fgetc(F)) != '\"')
                        w->name[i++] = c;
                    w->name[i] = '\0';
                }

        } else if (strcmp(elem, "title") == 0)
        {
            if ((c = epurer_blan(F)) == '=')
                if ((c = epurer_blan(F)) == '\"')
                {
                     i = 0;
                    while ((c = fgetc(F)) != '\"')
                        w->titre[i++] = c;
                    w->titre[i] = '\0';
                }

         }else if (strcmp(elem, "icon") == 0)
         {
            if ((c = epurer_blan(F)) == '=')
                if ((c = epurer_blan(F)) == '\"')
                {
                     i = 0;
                    while ((c = fgetc(F)) != '\"')
                        w->icon[i++] = c;
                    w->icon[i] = '\0';
                }

        } else if (strcmp(elem, "width") == 0)
        {
            if ((c = epurer_blan(F)) == '=')
                fscanf(F, "%d", &w->largeur);

        } else if (strcmp(elem, "height") == 0)
        {
            if ((c = epurer_blan(F)) == '=')
                fscanf(F, "%d", &w->hauteur);

        } else if (strcmp(elem, "bgColor") == 0)
        {
            if ((c = epurer_blan(F)) == '=')
                if ((c = epurer_blan(F)) == '\"')
                {
                     i = 0;
                    while ((c = fgetc(F)) != '\"')
                        w->bgcolor[i++] = c;
                    w->bgcolor[i] = '\0';

                }
        }else if (strcmp(elem, "posx") == 0)
        {
                if ((c = epurer_blan(F)) == '=')
                  fscanf(F, "%d", &w->posx);
        }
        else if (strcmp(elem, "posy") == 0)
        {
                if ((c = epurer_blan(F)) == '=')
                  fscanf(F, "%d", &w->posy);
        }
         else if (strcmp(elem, "border_width") == 0)
        {
                if ((c = epurer_blan(F)) == '=')
                  fscanf(F, "%d", &w->border_width);
        }
         else if (strcmp(elem, "resizable") == 0)
        {
                if ((c = epurer_blan(F)) == '=')
                  {
                    if((c = epurer_blan(F)) == 'F')
                      w->modifiable=FALSE;
                    else w->modifiable=TRUE;

                  }

        }
         else if (strcmp(elem, "scrolled") == 0)
        {
                if ((c = epurer_blan(F)) == '=')
                  {
                    if((c = epurer_blan(F)) == 'F')
                      w->scroll_bool=FALSE;
                    else w->scroll_bool=TRUE;

                  }

        }
         else if (strcmp(elem, "bgImage") == 0)
        {
        if ((c = epurer_blan(F)) == '=')
            if ((c = epurer_blan(F)) == '\"')
            {
                 i = 0;
                while ((c = fgetc(F)) != '\"')
                    w->bgimg[i++] = c;
                w->bgimg[i] = '\0';
            }
        }


        else if (strcmp(elem, "position_init") == 0)
        {
            gchar temp[30];
            if ((c = epurer_blan(F)) == '=')
             {
                if ((c = epurer_blan(F)) == '\"')
                {
                     i = 0;
                    while ((c = fgetc(F)) != '\"')
                        temp[i++] = c;
                    temp[i] = '\0';
                }
                w->position_init=string_to_window_position(temp);

            }
        }


    }while(strcmp(elem,">"));
    return(Fenetre*) w;
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
    if(W->bgcolor[0]!='\0')
    {
        GdkRGBA color;
        // Utilisez gdk_rgba_parse pour définir la couleur de fond de la fenêtre
        if (gdk_rgba_parse(&color,W->bgcolor)) {
            gtk_widget_override_background_color(W->window, GTK_STATE_NORMAL, &color);
        } else {
            g_warning("\nImpossible de definir la couleur de fond.");
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
    if(W->scroll_bool)
    {
        W->scrollwin = gtk_scrolled_window_new(NULL, NULL);
        gtk_container_add(GTK_CONTAINER(W->window), W->scrollwin);
         gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(W->scrollwin),
                                    GTK_POLICY_ALWAYS, GTK_POLICY_ALWAYS);
    }
    if(W->name[0]!='\0')
      gtk_widget_set_name(W->window,W->name);

    if(W->bgimg[0]!='\0')
    {
       load_css();
    }
}

Fenetre* add_window(FILE* F)
{
    // Initialize the button structure
    Fenetre* win=NULL;
    win = init_window();
    win = windowFunction(win,F);//lire les parametres de la fenetre a partir du fichier
    create_window(win);

    return(Fenetre*)win;
}

#endif // WINDOW_H_INCLUDED
