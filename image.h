#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
// Structure pour représenter une image avec différentes options
typedef struct
{
    GtkWidget *widget;            // Widget représentant l'image
    GtkWidget *parent;            // Widget parent de l'image
    gint type;                    // Type d'image (1:fichier, 2:animation, 3:stock)
    const gchar *icon_anim_stock; // Chemin du fichier, nom de l'animation, ou nom d'icône selon le type
    GdkPixbufAnimation *anim;     // Animation de l'image (utilisé si le type est 2)
    GtkIconSize size;             // Taille de l'icône (utilisé si le type est 3)
    gint h;
    gint w;
} image;

// Fonction pour initialiser une image avec des paramètres spécifiques
image *initialiser_image(GtkWidget *pere, gint t, const gchar *fichier, GtkIconSize sz, gint w, gint h)
{
    // Allouer dynamiquement de la mémoire pour une nouvelle structure image
    image *img = (image *)g_malloc(sizeof(image));

    // Initialiser les champs de la structure image
    img->parent = pere;                // Stocker le widget parent
    img->type = t;                     // Stocker le type d'image
    img->icon_anim_stock = fichier;    // Stocker le chemin du fichier, nom de l'animation, ou nom d'icône
    img->size = sz;                    // Stocker la taille de l'icône
    img->w = w;                      // Stocker la largeur spécifiée
    img->h = h;                      // Stocker la hauteur spécifiée

    // Renvoyer un pointeur vers la structure image nouvellement créée
    return img;
}

// Fonction pour changer la taille de l'image en fonction des spécifications
void change_size(image *img)
{
    GdkPixbuf *image = gdk_pixbuf_new_from_file(img->icon_anim_stock, NULL);

    // Spécifier la nouvelle largeur et hauteur souhaitées
    int nouvelle_largeur = img->w;
    int nouvelle_hauteur = img->h;

    // Redimensionner l'image
    GdkPixbuf *image_redimensionnee = gdk_pixbuf_scale_simple(image, nouvelle_largeur, nouvelle_hauteur, GDK_INTERP_BILINEAR);

    // Créer un widget GtkImage à partir du GdkPixbuf redimensionné
    img->widget = gtk_image_new_from_pixbuf(image_redimensionnee);

    // Libérer la mémoire allouée pour les images
    g_object_unref(image);
    g_object_unref(image_redimensionnee);
}

// Fonction pour créer l'image en fonction du type spécifié
void creer_img(image *img)
{
    // Instruction switch pour gérer différents types d'images
    switch (img->type)
    {
    // Cas 1 : Image statique
    case 1:
        // Vérifier si la largeur ou la hauteur est spécifiée pour le redimensionnement
        if (img->w || img->h)
            change_size(img); // Appeler une fonction pour changer la taille si elle est spécifiée
        else
        {
            // Créer un widget d'image GTK et définir sa source à partir d'un fichier
            img->widget = gtk_image_new();
            gtk_image_set_from_file(img->widget, img->icon_anim_stock);
        }
        break;

    // Cas 2 : Image animée
    case 2:
        // Créer une animation GDK Pixbuf à partir d'un fichier
        img->anim = gdk_pixbuf_animation_new_from_file(img->icon_anim_stock, NULL);
        // Créer un widget d'image GTK à partir de l'animation
        img->widget = gtk_image_new_from_animation(img->anim);
        break;

    // Cas 3 : Image stock
    case 3:
        // Créer un widget d'image GTK et définir sa source à partir d'une icône stock avec une taille spécifiée
        img->widget = gtk_image_new();
        gtk_image_set_from_stock(img->widget, img->icon_anim_stock, img->size);
        break;
    }
}

void add_image(GtkWidget *pere,gint type,const gchar fichier,GtkIconSize size_icon,gint w,gint h,gint x,gint y)
{
    image *img=initialiser_image(pere,type,fichier,size_icon,w,h);
    creer_img(img);
    gtk_fixed_put(GTK_FIXED(pere),img->widget,x,y);
}

