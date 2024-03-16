#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include "label.h"

// Structure pour représenter un cadre (frame) avec des éléments associés
typedef struct
{
    GtkWidget *widget;          // Le widget GTK représentant le cadre
    GtkWidget *parent;          // Le parent du cadre
    gint xligne;                // Position horizontale de l'étiquette dans le cadre
    gint yligne;                // Position verticale de l'étiquette dans le cadre
    texte *text;                // Structure de texte associée au cadre
    GtkWidget *conteneur;       // Le conteneur associé au cadre (peut être un label ou autre)
    GtkShadowType type;         // Type d'ombre du cadre
} frame;

// Fonction pour initialiser une structure de cadre avec des paramètres spécifiés
frame *initialiser_frame(GtkWidget *pere, gint x, gint y, texte *t, GtkWidget *fils, GtkShadowType type)
{
    // Allouer dynamiquement la mémoire pour la structure de cadre
    frame *fr = (frame *)g_malloc(sizeof(frame));

    // Initialiser les champs de la structure avec les valeurs spécifiées
    fr->widget = gtk_frame_new(NULL);
    fr->text = t;
    fr->parent = pere;
    fr->type = type;
    fr->xligne = x;
    fr->yligne = y;
    fr->conteneur = fils;

    // Retourner la structure de cadre initialisée
    return fr;
}

// Fonction pour créer un cadre en utilisant les paramètres spécifiés dans la structure
void creer_frame(frame *fr)
{
    // Créer une chaîne de caractères formatée pour l'étiquette avec des propriétés de texte spécifiées
    gchar *lab = g_strdup_printf("<span  font_desc=\"%d\" style=\"%s\" foreground=\"%s\" font_family=\"%s\" underline=\"%s\">%s</span> ", fr->text->taille_text, fr->text->style, fr->text->couleur_text, fr->text->police, fr->text->underline, fr->text->text);

    // Créer un widget de label GTK et définir son contenu avec la chaîne formatée
    GtkWidget *label = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(label), lab);

    // Définir le label comme étiquette du cadre
    gtk_frame_set_label_widget(GTK_FRAME(fr->widget), label);

    // Assigner le label au conteneur du cadre
    fr->conteneur = label;

    // Si des positions spécifiées, les appliquer à l'étiquette du cadre
    if (fr->xligne || fr->yligne)
        gtk_frame_set_label_align(GTK_FRAME(fr->widget), fr->xligne, fr->yligne);

    // Si un type d'ombre spécifié, l'appliquer au cadre
    if (fr->type)
        gtk_frame_set_shadow_type(GTK_FRAME(fr->widget), fr->type);
}

frame * add_frame(GtkWidget *pere,gfloat xligne,gfloat yligne,texte *tx,GtkWidget *fils,GtkShadowType type,gint x,gint y)
{
    frame *fr=initialiser_frame(pere,xligne,yligne,tx,fils,type);
    creer_frame(fr);
    gtk_fixed_put(GTK_FIXED(pere),fr->widget,x,y);
    return fr;
}

