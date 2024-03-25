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


ButtonSimple* buttonSimpleFunction(ButtonSimple* b,FILE* F)
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
                        b->name[i++] = c;
                    b->name[i] = '\0';
                 printf("\n %s \n",b->name);
                }
            }
        } else if (strcmp(elem, "label") == 0) {
            if ((c = epurer_blan(F)) == '=') {
                if ((c = epurer_blan(F)) == '\"') {
                    int i = 0;
                    while ((c = fgetc(F)) != '\"')
                        b->label[i++] = c;
                    b->label[i] = '\0';
                }
            }
        } else if (strcmp(elem, "lien") == 0) {
            if ((c = epurer_blan(F)) == '=') {
                if ((c = epurer_blan(F)) == '\"') {
                    int i = 0;
                    while ((c = fgetc(F)) != '\"')
                        b->lien[i++] = c;
                    b->lien[i] = '\0';
                }
            }
        } else if (strcmp(elem, "width") == 0) {
            if ((c = epurer_blan(F)) == '=') {
                fscanf(F, "%d", &b->width);
            }
        } else if (strcmp(elem, "height") == 0) {
            if ((c = epurer_blan(F)) == '=') {
                fscanf(F, "%d", &b->height);
            }
        } else if (strcmp(elem, "bgColor") == 0) {
            if ((c = epurer_blan(F)) == '=') {
                if ((c = epurer_blan(F)) == '\"') {
                    int i = 0;
                    while ((c = fgetc(F)) != '\"')
                        b->bgColor[i++] = c;
                    b->bgColor[i] = '\0';
                }
            }
        }
    }while(strcmp(elem,">"));
    return b;
}





// INITIALISER LE BOUTON
ButtonSimple* init_button_simple() {
    ButtonSimple* b = (ButtonSimple*)malloc(sizeof(ButtonSimple));
    if (!b) {
        printf("\nErreur d'allocation !!\n");
        exit(0);
    }
    b->name = NULL;
    b->label=(gchar*)g_malloc(sizeof(gchar)*30);
    b->label[0]='\0';

    b->image = NULL;  // Initialize image widget to NULL


    b->bgColor=(gchar*)g_malloc(sizeof(gchar)*30);
    b->bgColor[0]='\0';
    b->name=(gchar*)g_malloc(sizeof(gchar)*30);
    b->name[0]='\0';
    b->height=0;
    b->lien=(gchar*)g_malloc(sizeof(gchar)*30);
    b->lien[0]='\0';
    b->width=0;
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
    if(B->bgColor)
    {

               add_bgcolor_btn(vbox, B->bgColor, 1.0); // Utiliser la couleur de fond spécifiée
    }
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


///gchar* name, gchar* label, gchar* path_to_image, gint height, gint width, gchar* bgColor,


ButtonSimple* add_button(FILE* F) {
    // Initialize the button structure
    ButtonSimple* B =NULL;
    B = init_button_simple();
    B = buttonSimpleFunction(B,F);
    creer_button_Simple(B);
    // Initialize image widget
    image* img = initialiser_image(B, 1, B->lien, GTK_ICON_SIZE_BUTTON, B->width, B->height);
    creer_img(img);
    return B;
}

#endif // BOUTTON_NORMAL_H_INCLUDED
