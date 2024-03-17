#ifndef SCROLLBAR_H_INCLUDED
#define SCROLLBAR_H_INCLUDED

// D�finition de la structure barre_def
typedef struct
{
    GtkWidget *widget;   // Widget de la barre de d�filement
    GtkWidget *parent;   // Widget parent de la barre de d�filement
    GtkWidget *fils;     // Widget fils (conteneur) associ� � la barre de d�filement
    guint hpolic;        // Politique de d�filement horizontal (GTK_POLICY_AUTOMATIC, GTK_POLICY_ALWAYS, GTK_POLICY_NEVER)
    guint vpolic;        // Politique de d�filement vertical (GTK_POLICY_AUTOMATIC, GTK_POLICY_ALWAYS, GTK_POLICY_NEVER)
    gint w; // Largeur
    gint h; // Hauteur

} barre_def;

// Fonction pour initialiser une barre de d�filement avec des param�tres sp�cifi�s
barre_def *initialiser_barre_def(gint w, gint h, guint hpl, guint vpl)
{
    // Allocation dynamique de m�moire pour une nouvelle structure barre_def
    barre_def *scrBar = (barre_def *)g_malloc(sizeof(barre_def));

    // Cr�ation d'une nouvelle barre de d�filement GtkScrolledWindow
    scrBar->widget = gtk_scrolled_window_new(NULL, NULL);

    // Initialisation des champs de style
    scrBar->h = h;
    scrBar->w = w;

    // Initialisation des champs de politique de d�filement
    scrBar->hpolic = hpl;
    scrBar->vpolic = vpl;

    // Retour de la structure initialis�e
    return scrBar;
}

// Fonction pour cr�er une barre de d�filement avec un conteneur associ�
void creer_scrollbar(barre_def *scrbar, GtkWidget *pere, GtkWidget *conteneur)
{
    // Ajout de la barre de d�filement en tant que fils du widget parent
    gtk_container_add(GTK_CONTAINER(pere), scrbar->widget);

    // D�finition de la taille demand�e pour la barre de d�filement
    gtk_widget_set_size_request(scrbar->widget, scrbar->w, scrbar->h);

    // Ajout du conteneur � la barre de d�filement avec une vue
    gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(scrbar->widget), conteneur);

    // D�finition des politiques de d�filement (horizontal et vertical)
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrbar->widget), scrbar->vpolic, scrbar->hpolic);
}

void add_scrollbar(GtkWidget *grand_pere,GtkWidget *fixed,gint w,gint h,guint hpolic,guint vpolic)
{
    barre_def *scrolled=initialiser_barre_def(w,h,hpolic,vpolic);
    creer_scrollbar(scrolled,grand_pere,fixed);
}



#endif // SCROLLBAR_H_INCLUDED
