#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>

// Définition de la structure barre_def
typedef struct
{
    GtkWidget *widget;   // Widget de la barre de défilement
    GtkWidget *parent;   // Widget parent de la barre de défilement
    GtkWidget *fils;     // Widget fils (conteneur) associé à la barre de défilement
    guint hpolic;        // Politique de défilement horizontal (GTK_POLICY_AUTOMATIC, GTK_POLICY_ALWAYS, GTK_POLICY_NEVER)
    guint vpolic;        // Politique de défilement vertical (GTK_POLICY_AUTOMATIC, GTK_POLICY_ALWAYS, GTK_POLICY_NEVER)
    gint w; // Largeur
    gint h; // Hauteur

} barre_def;

// Fonction pour initialiser une barre de défilement avec des paramètres spécifiés
barre_def *initialiser_barre_def(gint w, gint h, guint hpl, guint vpl)
{
    // Allocation dynamique de mémoire pour une nouvelle structure barre_def
    barre_def *scrBar = (barre_def *)g_malloc(sizeof(barre_def));

    // Création d'une nouvelle barre de défilement GtkScrolledWindow
    scrBar->widget = gtk_scrolled_window_new(NULL, NULL);

    // Initialisation des champs de style
    scrBar->h = h;
    scrBar->w = w;

    // Initialisation des champs de politique de défilement
    scrBar->hpolic = hpl;
    scrBar->vpolic = vpl;

    // Retour de la structure initialisée
    return scrBar;
}

// Fonction pour créer une barre de défilement avec un conteneur associé
void creer_scrollbar(barre_def *scrbar, GtkWidget *pere, GtkWidget *conteneur)
{
    // Ajout de la barre de défilement en tant que fils du widget parent
    gtk_container_add(GTK_CONTAINER(pere), scrbar->widget);

    // Définition de la taille demandée pour la barre de défilement
    gtk_widget_set_size_request(scrbar->widget, scrbar->w, scrbar->h);

    // Ajout du conteneur à la barre de défilement avec une vue
    gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(scrbar->widget), conteneur);

    // Définition des politiques de défilement (horizontal et vertical)
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrbar->widget), scrbar->vpolic, scrbar->hpolic);
}

void add_scrollbar(GtkWidget *grand_pere,GtkWidget *fixed,gint w,gint h,guint hpolic,guint vpolic)
{
    barre_def *scrolled=initialiser_barre_def(w,h,hpolic,vpolic);
    creer_scrollbar(scrolled,grand_pere,fixed);
}

