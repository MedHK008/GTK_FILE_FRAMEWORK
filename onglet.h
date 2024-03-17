#ifndef ONGLET_H_INCLUDED
#define ONGLET_H_INCLUDED


typedef struct _Onglet {
  GtkWidget *onglet; // Le widget onglet lui-même
  char *titre; // Le titre de l'onglet
  GtkWidget *contenu; // Le contenu de l'onglet
  gboolean actif; // Indique si l'onglet est actif
} Onglet;

Onglet *onglet_nouveau(const char *titre, GtkWidget *contenu) {
  Onglet *onglet = malloc(sizeof(Onglet));
  onglet->titre = strdup(titre); // Allocate memory for titre and copy the title string

  // Créer le widget onglet
  onglet->onglet = gtk_notebook_new();

  // Définir le contenu de l'onglet
  gtk_container_add(GTK_CONTAINER(onglet->onglet), contenu);

  // Définir l'onglet comme inactif par défaut
  onglet->actif = FALSE;

  return onglet;
}

// Fonction pour obtenir le widget onglet
GtkWidget *onglet_get_widget(Onglet *onglet) {
  return onglet->onglet;
}

// Fonction pour obtenir le titre de l'onglet
const char *onglet_get_titre(Onglet *onglet) {
  return onglet->titre;
}

// Fonction pour définir le titre de l'onglet
void onglet_set_titre(Onglet *onglet, const char *titre) {
  free(onglet->titre); // Free previous titre
  onglet->titre = strdup(titre); // Allocate memory for new titre and copy the title string
  gtk_notebook_set_tab_label_text(GTK_NOTEBOOK(onglet->onglet), onglet->onglet, titre);
}

void onglet_set_contenu(Onglet *onglet, GtkWidget *contenu) {
  if (onglet->contenu != NULL) // Free previous contenu if exists
    gtk_container_remove(GTK_CONTAINER(onglet->onglet), onglet->contenu);

  onglet->contenu = contenu;
  gtk_container_add(GTK_CONTAINER(onglet->onglet), contenu);
}

void onglet_activer(Onglet *onglet) {
  onglet->actif = TRUE;
  gtk_notebook_set_current_page(GTK_NOTEBOOK(onglet->onglet), 0); // Set current page to the first page (index 0)
}


#include <gtk/gtk.h>

void add_onglet(GtkWidget* notebook, GtkWidget* fixed, gchar* label, const char* bgcolor) {
    // Create a label widget with the specified text
    GtkWidget* tab_label = gtk_label_new(label);

    // Set the background color of the tab label
    GdkRGBA color;
    gdk_rgba_parse(&color, bgcolor); // Parse the background color string
    gtk_widget_override_background_color(tab_label, GTK_STATE_FLAG_NORMAL, &color);

    // Append the fixed widget with the custom tab label to the notebook
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), fixed, tab_label);
}



void add_to_window(GtkWidget* notebook,GtkWidget* window)
{
    gtk_container_add(GTK_CONTAINER(window), notebook);
}
#endif // ONGLET_H_INCLUDED
