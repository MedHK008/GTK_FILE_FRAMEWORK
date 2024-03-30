#ifndef IMAGE_H_INCLUDED
#define IMAGE_H_INCLUDED

// Structure pour repr�senter une image avec diff�rentes options
typedef struct
{
    GtkWidget *widget;            // Widget repr�sentant l'image// Widget parent de l'image
    gint type;                    // Type d'image (1:fichier, 2:animation, 3:stock)
    const gchar *icon_anim_stock; // Chemin du fichier, nom de l'animation, ou nom d'ic�ne selon le type
    GdkPixbufAnimation *anim;     // Animation de l'image (utilis� si le type est 2)
    gint  sizeicon;                   // Taille de l'ic�ne (utilis� si le type est 3)
    gchar *name;
    gint h;
    gint w;
    gint x;
    gint y;
    GtkWidget *parent;
} image;

gchar epurer_blan(FILE*f)
{
    char c ;
    while((c=fgetc(f))==' ' || c=='\n' || c=='\t');
    return (gchar)(c);
}

// Fonction pour initialiser une image avec des param�tres sp�cifiques
image *initialiser_image()
{
    // Allouer dynamiquement de la m�moire pour une nouvelle structure image
    image *img = (image *)g_malloc(sizeof(image));
    // Initialiser les champs de la structure image
    //img->parent = pere;               // Stocker le widget parent
    img->type = 1;                     // Stocker le type d'image
    img->icon_anim_stock = (const gchar *)g_malloc(sizeof(const gchar )*30);
    img->sizeicon = 1;                    // Stocker la taille de l'ic�ne
    img->name=(gchar *)g_malloc(sizeof( gchar )*30);
    img->name[0]='\0';
    img->w = 0;                      // Stocker la largeur sp�cifi�e
    img->h = 0;                      // Stocker la hauteur sp�cifi�e

    // Renvoyer un pointeur vers la structure image nouvellement cr��e
    return img;
}

// Fonction pour changer la taille de l'image en fonction des sp�cifications
void change_size(image *img)
{
    GdkPixbuf *image = gdk_pixbuf_new_from_file(img->icon_anim_stock, NULL);
    // Sp�cifier la nouvelle largeur et hauteur souhait�es
    int nouvelle_largeur = img->w;
    int nouvelle_hauteur = img->h;

    // Redimensionner l'image
    GdkPixbuf *image_redimensionnee = gdk_pixbuf_scale_simple(image, nouvelle_largeur, nouvelle_hauteur, GDK_INTERP_BILINEAR);
     printf("\nje suis ici");
    // Cr�er un widget GtkImage � partir du GdkPixbuf redimensionn�
    img->widget = gtk_image_new_from_pixbuf(image_redimensionnee);

    // Lib�rer la m�moire allou�e pour les images
    g_object_unref(image);
    g_object_unref(image_redimensionnee);
}

// Fonction pour cr�er l'image en fonction du type sp�cifi�
void creer_img(image *img)
{
    // Instruction switch pour g�rer diff�rents types d'images
    switch (img->type)
    {
    // Cas 1 : Image statique
    case 1:
        // V�rifier si la largeur ou la hauteur est sp�cifi�e pour le redimensionnement
        if (img->w || img->h)
            change_size(img); // Appeler une fonction pour changer la taille si elle est sp�cifi�e
        else
        {
            // Cr�er un widget d'image GTK et d�finir sa source � partir d'un fichier
            img->widget = gtk_image_new();
            gtk_image_set_from_file(img->widget, img->icon_anim_stock);
        }
        break;

    // Cas 2 : Image anim�e
    case 2:
        // Cr�er une animation GDK Pixbuf � partir d'un fichier
        img->anim = gdk_pixbuf_animation_new_from_file(img->icon_anim_stock, NULL);
        // Cr�er un widget d'image GTK � partir de l'animation
        img->widget = gtk_image_new_from_animation(img->anim);
        break;

    // Cas 3 : Image stock
    case 3:
        // Cr�er un widget d'image GTK et d�finir sa source � partir d'une ic�ne stock avec une taille sp�cifi�e
        img->widget = gtk_image_new();
        gtk_image_set_from_stock(img->widget, img->icon_anim_stock, style_iconsize(img->sizeicon));
        break;
    }
}
image *imagefunction(image *img ,FILE *F)
{
    gchar* elem;
    elem=(gchar*)g_malloc(sizeof(gchar)*50);
    gchar c;
    do
    {
        fscanf(F,"%s",elem);
        printf("%s\n",elem);
       if (strcmp(elem, "name") == 0) {
            if ((c = epurer_blan(F)) == '=') {
                if ((c = epurer_blan(F)) == '\"') {
                    int i = 0;
                    while ((c = fgetc(F)) != '\"')
                        img->name[i++] = c;
                    img->name[i] = '\0';
                }
            }
        } else if (strcmp(elem, "fichier") == 0) {
            if ((c = epurer_blan(F)) == '=')
               fscanf(F, "%s", img->icon_anim_stock);
        } else if (strcmp(elem, "style_icon") == 0) {
            if ((c = epurer_blan(F)) == '=') {
               fscanf(F, "%d", &img->sizeicon);
            }
        } else if (strcmp(elem, "width") == 0) {
            if ((c = epurer_blan(F)) == '=') {
                fscanf(F, "%d", &img->w);
            }
        } else if (strcmp(elem, "height") == 0) {
            if ((c = epurer_blan(F)) == '=') {
                fscanf(F, "%d", &img->h);
            }
        } else if (strcmp(elem, "type") == 0) {
            if ((c = epurer_blan(F)) == '=') {
                fscanf(F, "%d", &img->type);
                printf("%d",img->type);
            }
        }else if (strcmp(elem, "xligne") == 0) {
            if ((c = epurer_blan(F)) == '=') {
                fscanf(F, "%d", &img->x);
            }
        }
        else if (strcmp(elem, "yligne") == 0) {
            if ((c = epurer_blan(F)) == '=') {
                fscanf(F, "%d", &img->y);
            }
        }
    }while(strcmp(elem,">"));
    return img;
}

image *add_image(FILE *F)
{
    image *img=initialiser_image();
    img=imagefunction(img,F);
    creer_img(img);
    return img;
}


#endif // IMAGE_H_INCLUDED
