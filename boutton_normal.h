#ifndef BOUTTON_NORMAL_H_INCLUDED
#define BOUTTON_NORMAL_H_INCLUDED

#include "image.h"

//*********************************************STRUCTURES***********************************************
typedef struct {
    GtkWidget* button; // bouton widget
    gchar* name;       // Nom du bouton
    gchar* label;      // Le texte sur le bouton
    gchar* lien;       // Chemin icone du bouton
    guint width;       // longueur du bouton
    guint height;      // largeur du bouton
    gchar* bgColor;    // Couleur de fond du GtkGrid
    GtkWidget* image;  // Widget de l'image pour le bouton
} ButtonSimple;


// INITIALISER LE BOUTON
ButtonSimple* init_button_simple(gchar* nom, gchar* etiq, gchar* name, GtkWidget* img_widget, gint h, gint w, gchar* bgColor, gint x, gint y) {
    ButtonSimple* b = (ButtonSimple*)malloc(sizeof(ButtonSimple));
    if (!b) {
        printf("\nErreur d'allocation !!\n");
        exit(0);
    }

    b->name = NULL;
    b->label = NULL;
    b->image = NULL;  // Initialize image widget to NULL
    b->bgColor = NULL;
    if (etiq) {
        b->label = (gchar*)malloc(30 * sizeof(gchar)); // Allocation fixe
        strcpy(b->label, etiq);
    }
    if (name) {
        b->name = (gchar*)malloc(30 * sizeof(gchar)); // Allocation fixe
        strcpy(b->name, name);
    }
    if (bgColor) {
        b->bgColor = (gchar*)malloc(30 * sizeof(gchar)); // Allocation fixe
        strcpy(b->bgColor, bgColor);
    }
    b->width = w;
    b->height = h;
    b->image = img_widget;  // Set the image widget
    return b;
}
//***************************************************************

// Fonction pour ajouter une couleur de fond à un widget
void add_bgcolor_btn(GtkWidget* widget, const gchar* color, gdouble opacity) {
    GdkRGBA rgba;

    if (gdk_rgba_parse(&rgba, color)) {
        rgba.alpha = opacity;
        gtk_widget_override_background_color(widget, GTK_STATE_NORMAL, &rgba);
    } else {
        g_print("Erreur : Impossible de parser la couleur %s\n", color);
    }
}
//***********************************************************
// CREER LE BOUTON SIMPLE
void creer_button_Simple(ButtonSimple* B) {
    // Créer un GtkBox vertical pour contenir l'image et le label
    GtkWidget* vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    // Changer la couleur de fond de la vbox
    if (B->bgColor)
        add_bgcolor_btn(vbox, B->bgColor, 1.0); // Utiliser la couleur de fond spécifiée

    // Créer un label pour le texte
    GtkWidget* label = NULL;
    if (B->label) {
        label = gtk_label_new(B->label);
        // Centrer le texte horizontalement et verticalement dans la vbox
        gtk_widget_set_halign(label, GTK_ALIGN_CENTER);
        gtk_widget_set_valign(label, GTK_ALIGN_CENTER);
        // Ajouter le label à la vbox
        gtk_box_pack_start(GTK_BOX(vbox), label, TRUE, TRUE, 0);
    }

    // Ajouter l'image à la vbox
    if (B->image)
        gtk_box_pack_start(GTK_BOX(vbox), B->image, TRUE, TRUE, 0);

    // Créer le bouton avec la vbox comme contenu
    B->button = gtk_button_new();
    gtk_container_add(GTK_CONTAINER(B->button), vbox);

    // Définir le nom du bouton (ID) pour le styliser en CSS
    if (B->name)
        gtk_widget_set_name(B->button, B->name);

    // Définir la taille du bouton
    if ((B->width > 0) && (B->height > 0))
        gtk_widget_set_size_request(B->button, B->width, B->height);
}

ButtonSimple* add_button(gchar* name, gchar* label, gchar* path_to_image, gint height, gint width, gchar* bgColor, gint image_w, gint image_h) {
    ButtonSimple* simpleButton = NULL;

    // Initialize image widget
    image* img = initialiser_image(simpleButton, 1, path_to_image, GTK_ICON_SIZE_BUTTON, image_w, image_h);
    creer_img(img);
    // Initialize the button structure
    simpleButton = init_button_simple("mon_bouton", label, name, img->widget, height, width, bgColor, 0, 0);
    creer_button_Simple(simpleButton);
    return simpleButton;
}

#endif // BOUTTON_NORMAL_H_INCLUDED
