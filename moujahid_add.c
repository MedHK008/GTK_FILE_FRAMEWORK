#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>


// D�finition de la structure style
typedef struct
{
    gint w; // Largeur
    gint h; // Hauteur
} style;

// D�finition de la structure barre_def
typedef struct
{
    GtkWidget *widget;   // Widget de la barre de d�filement
    GtkWidget *parent;   // Widget parent de la barre de d�filement
    GtkWidget *fils;     // Widget fils (conteneur) associ� � la barre de d�filement
    guint hpolic;        // Politique de d�filement horizontal (GTK_POLICY_AUTOMATIC, GTK_POLICY_ALWAYS, GTK_POLICY_NEVER)
    guint vpolic;        // Politique de d�filement vertical (GTK_POLICY_AUTOMATIC, GTK_POLICY_ALWAYS, GTK_POLICY_NEVER)
    style s;             // Style de la barre de d�filement (largeur et hauteur)

} barre_def;

// Fonction pour initialiser une barre de d�filement avec des param�tres sp�cifi�s
barre_def *initialiser_barre_def(gint w, gint h, guint hpl, guint vpl)
{
    // Allocation dynamique de m�moire pour une nouvelle structure barre_def
    barre_def *scrBar = (barre_def *)g_malloc(sizeof(barre_def));

    // Cr�ation d'une nouvelle barre de d�filement GtkScrolledWindow
    scrBar->widget = gtk_scrolled_window_new(NULL, NULL);

    // Initialisation des champs de style
    scrBar->s.h = h;
    scrBar->s.w = w;

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
    gtk_widget_set_size_request(scrbar->widget, scrbar->s.w, scrbar->s.h);

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


/****************************************************************************************************************/
// D�finition de la structure item_bar
typedef struct
{
    GtkWidget *widget; // Widget associ� � l'�l�ment de la barre d'outils
    style *s;         // Style de l'�l�ment (position, largeur, hauteur)
    const gchar *icon;    // Ic�ne associ�e � l'�l�ment
    gchar *text;      // Texte associ� � l'�l�ment
    GtkWidget *parent;
    gint pos;//// Position dans la barre d'outils

} item_bar;



// D�finition de la structure toolbar
typedef struct
{
    GtkWidget *widget;   // Widget de la barre d'outils
    GtkWidget *parent;   // Widget parent de la barre d'outils
    gchar orientation;   // Orientation de la barre d'outils ('h' pour horizontal, 'v' pour vertical)
    style *s;

} toolbar;

// Fonction pour initialiser une barre d'outils avec une orientation sp�cifi�e
toolbar *initialiser_toolbar(GtkWidget *pere,gchar orientation,gint w,gint h,GtkToolbarStyle stl,GtkIconSize siz)
{
    toolbar *tbar = (toolbar *)g_malloc(sizeof(toolbar));
    tbar->widget=(GtkWidget *)g_malloc(sizeof(GtkWidget));
    tbar->parent=(GtkWidget *)g_malloc(sizeof(GtkWidget));
    //tbar->items->item=(item_bar *)g_malloc(sizeof(item_bar));
    tbar->orientation = orientation;
    tbar->widget = gtk_toolbar_new();
    tbar->parent = pere;
    tbar->s->w = w;
    tbar->s->h = h;
    if(stl)
        gtk_toolbar_set_style(GTK_TOOLBAR(tbar->widget),stl);
    if(siz)
        gtk_toolbar_set_icon_size(GTK_TOOLBAR(tbar->widget),siz);
    return tbar;
}

// Fonction pour d�finir l'orientation d'une barre d'outils
toolbar *creer_toolbar(toolbar *tbar)
{
    // V�rifie si l'orientation de la barre d'outils est horizontale
    if (tbar->orientation == 'h' || tbar->orientation == 'H')
        // Si oui, d�finir l'orientation de la barre d'outils comme horizontale
        gtk_orientable_set_orientation(GTK_TOOLBAR(tbar), GTK_ORIENTATION_HORIZONTAL);
    else
        // Sinon, d�finir l'orientation de la barre d'outils comme verticale
     gtk_orientable_set_orientation(GTK_TOOLBAR(tbar),GTK_ORIENTATION_VERTICAL);
}

//Fonction pour initialiser un �l�ment de la barre d'outils � partir d'une ic�ne stock�e
item_bar *initialiser_item_stock(GtkWidget *pere,const gchar *icon, gchar *lab, gint w, gint h, gint pos)
{
    item_bar *item = (item_bar *)g_malloc(sizeof(item_bar));
    item->widget = gtk_tool_item_new();
    item->text = lab;
    item->icon = icon;

    // Allocation de m�moire pour la structure style et initialisation de ses champs
    item->s = (style *)g_malloc(sizeof(style));
    item->pos = pos;
    item->s->w = w;
    item->s->h = h;

    return item;
}

// Fonction pour cr�er un GtkToolItem � partir d'un item_bar et l'ajouter � la barre d'outils
void creer_toolitem(item_bar *toolitem, toolbar *bar,gboolean choix,void (*fonction)(GtkWidget*,gpointer),gchar *type,gpointer data)
{
    /* Cr�ation � partir de stock */
    GtkWidget *box = gtk_vbox_new(FALSE, 5);
    GtkWidget *button = gtk_tool_button_new_from_stock(toolitem->icon);
    //gtk_toolbar_insert(GTK_TOOLBAR(ptoolbar), button, -1);
    gtk_box_pack_start(GTK_BOX(box), button, FALSE, FALSE, 0);
    // Ajoutez une �tiquette au conteneur
    GtkWidget *label = gtk_label_new(toolitem->text);
    gtk_box_pack_start(GTK_BOX(box), label, FALSE, FALSE, 0);
    gtk_container_add(GTK_CONTAINER(toolitem->widget), box);
    gtk_toolbar_insert(GTK_TOOLBAR(bar->widget), toolitem->widget, toolitem->pos);
    // D�finir la taille du widget si la largeur et la hauteur sont sp�cifi�es
    if (toolitem->s->w && toolitem->s->h)
        gtk_widget_set_size_request(toolitem->widget, toolitem->s->w, toolitem->s->h);
    if(choix)
       g_signal_connect(G_OBJECT(button),type, G_CALLBACK(fonction), data);

}


// Fonction pour cr�er et ajouter un s�parateur � une barre d'outils (toolbar) GTK
// Param�tres :
// - sep : Un pointeur vers le widget de s�parateur (sera initialis� dans la fonction)
// - pere : Le widget parent, g�n�ralement une barre d'outils GTK (GtkWidget *)
// - pos : La position � laquelle ins�rer le s�parateur dans la barre d'outils (gint)
// Retourne le widget de s�parateur cr��
GtkWidget *creer_separ(GtkWidget *sep, GtkWidget *pere, gint pos)
{
    // Cr�er un nouveau s�parateur
    sep = gtk_separator_tool_item_new();

    // Ins�rer le s�parateur dans la barre d'outils � la position sp�cifi�e
    gtk_toolbar_insert(GTK_TOOLBAR(pere), sep, pos);

    // Renvoyer le widget de s�parateur cr��
    return sep;
}

toolbar *add_toolbar(GtkWidget *box,gchar orientation,gint x,gint y,gint w,gint h,GtkToolbarStyle sty,GtkIconSize size_icone,gint padding)
{
    toolbar *tool_bar=initialiser_toolbar(box,orientation,w,h,sty,size_icone);
    creer_toolbar(tool_bar);
    gtk_box_pack_start(GTK_BOX(box), tool_bar->widget, FALSE, FALSE, padding);
    return tool_bar;

}

void add_item_bar(toolbar *bar_pere,const gchar *icon,gchar *label,gint w,gint h,gint pos)
{
    item_bar *element=initialiser_item_stock(bar_pere->widget,icon,label,w,h,pos);
    creer_toolitem(element,bar_pere,0,NULL,NULL,NULL);
}


/**********************************************************************************************************/

typedef struct
{
     gchar text[200];
     guint alignement;/* L'alignement du texte
    1: GTK_JUSTIFY_LEFT pour aligner le texte � gauche (par d�faut);
    2: GTK_JUSTIFY_RIGHT pour aligner le texte � droite ;
    3: GTK_JUSTIFY_CENTER pour centrer le texte ;
    4:GTK_JUSTIFY_FILL pour justifier�le�texte*/
    style s;
    gchar police[30];//Pour definir la police utils�e*/
    gint taille_text;/* Pour definir la taille du texte*/
    gchar style[15];//Pour definir le style du texte*/
    gchar epaisseur[15]; /*Pour definir l'epaisseur du texte : small , large , Xlaarge... */
    gchar couleur_text[15];//Pour definir la couleur du texte*/
    gchar couleur_fond[15];//Pour definir la couleur du fond*/
    gchar underline[15];/* Pour le soulignement du texte*/
    gboolean line_through; //Pour barrer le texte/

}texte;

// Fonction pour initialiser une structure texte
texte *initialiser_texte(gint w, gint h, gchar lb[200], guint alg, gchar police[30], gint size, gchar styl[15], gchar epaisseur[15], gchar couleur[15], gchar background[15], gchar underline[15])
{
    // Allouer dynamiquement de la m�moire pour une nouvelle structure texte
    texte *tex = (texte *)g_malloc(sizeof(texte));

    // Copier le texte pass� en param�tre dans la structure texte
    strcpy(tex->text, lb);

    // Si alg est non nul, utiliser sa valeur, sinon, utiliser 1 (GTK_JUSTIFY_LEFT) par d�faut
    tex->alignement = (alg != 0) ? alg : 1;

    // Si une police est sp�cifi�e, l'utiliser, sinon, utiliser "Sans" par d�faut
    if (police)
        strcpy(tex->police, police);
    else
        strcpy(tex->police, "Sans");

    // Si une taille de texte est sp�cifi�e, l'utiliser, sinon, utiliser 10 par d�faut
    if (size)
        tex->taille_text = size;
    else
        tex->taille_text = 10;

    // Si un style est sp�cifi�, l'utiliser, sinon, utiliser "normal" par d�faut
    if (styl)
        strcpy(tex->style, styl);
    else
        strcpy(tex->style, "normal");

    // Si une couleur de texte est sp�cifi�e, l'utiliser, sinon, utiliser "#000000" (noir) par d�faut
    if (couleur)
        strcpy(tex->couleur_text, couleur);
    else
        strcpy(tex->couleur_text, "#000000");

    // Si un soulignement est sp�cifi�, l'utiliser, sinon, utiliser "none" par d�faut
    if (underline)
        strcpy(tex->underline, underline);
    else
        strcpy(tex->underline, "none");

    // Initialiser la structure style � partir des valeurs de largeur (w) et hauteur (h)
    tex->s.w = w;
    tex->s.h = h;

    // Renvoyer un pointeur vers la structure texte nouvellement cr��e
    return tex;
}

// Fonction pour appliquer un style � un �l�ment GTK en fonction d'un type donn�
GtkWidget *style_texte(GtkWidget *element, texte *text, gint type)
{
    gchar *sUtf8; // Cha�ne de caract�res pour le formatage du texte en UTF-8

    // Utiliser un commutateur (switch) pour g�rer diff�rents types d'�l�ments GTK
    switch (type)
    {
        case 1: // Cas o� l'�l�ment est un label (GTK_LABEL)
            element = gtk_label_new(NULL);

            // Formater le texte avec les propri�t�s sp�cifi�es dans la structure texte
            sUtf8 = g_strdup_printf("<span  font_desc=\"%d\" style=\"%s\" foreground=\"%s\" font_family=\"%s\" underline=\"%s\">%s</span> ",
                                    text->taille_text, text->style, text->couleur_text, text->police, text->underline, text->text);

            // Appliquer le texte format� au label
            gtk_label_set_markup(GTK_LABEL(element), sUtf8);

            // Lib�rer la m�moire allou�e pour la cha�ne sUtf8
            g_free(sUtf8);
            break;

        // Ajouter d'autres cas pour d'autres types d'�l�ments GTK si n�cessaire

    }

    // Renvoyer l'�l�ment GTK avec le style appliqu�
    return element;
}



/**********************************************************************************************************/

// Structure pour repr�senter une �tiquette avec un texte stylis�
typedef struct Label_et
{
    GtkWidget *widget;    /// Pointeur vers le widget du label
    GtkWidget *pere;      /// Pointeur vers le parent du label
    texte *text;          /// Texte du label
    gboolean selectable;  /// Indique si le texte peut �tre s�lectionn�
    gboolean wrap;        /// Indique si le texte peut �tre coup� en lignes
} Etiquette;

// Fonction pour initialiser une �tiquette (label) avec un texte stylis�
Etiquette *initialiser_label(GtkWidget *parent, texte *stext, gboolean select, gboolean coupe)
{
    // Allouer dynamiquement de la m�moire pour une nouvelle �tiquette
    Etiquette *label = (Etiquette *)g_malloc(sizeof(Etiquette));

    // Initialiser les champs de la structure Etiquette
    label->widget = gtk_label_new(NULL); // Cr�er un nouveau widget label
    label->pere = parent; // Stocker le widget parent
    label->text = stext; // Stocker le texte � afficher
    label->widget = style_texte(label->widget, label->text, 1); // Appliquer le style au label
    label->selectable = select; // Indiquer si le texte peut �tre s�lectionn�
    gtk_label_set_selectable(GTK_LABEL(label->widget), label->selectable);
    label->wrap=coupe;
    gtk_label_set_line_wrap(GTK_LABEL(label->widget), label->wrap);

    // Renvoyer un pointeur vers la structure Etiquette nouvellement cr��e
    return label;
}

void add_label(GtkWidget *pere,texte *text,gboolean selectable,gboolean wrap,gint x,gint y)
{
    Etiquette *label=initialiser_label(pere,text,selectable,wrap);
    gtk_fixed_put(GTK_FIXED(pere),label->widget,x,y);
    if(label->text->s.h && label->text->s.w)
            gtk_widget_set_size_request(label->widget,label->text->s.w,label->text->s.h);

}


/**********************************************************************************************************/


// Structure pour repr�senter une image avec diff�rentes options
typedef struct
{
    GtkWidget *widget;            // Widget repr�sentant l'image
    GtkWidget *parent;            // Widget parent de l'image
    gint type;                    // Type d'image (1:fichier, 2:animation, 3:stock)
    const gchar *icon_anim_stock; // Chemin du fichier, nom de l'animation, ou nom d'ic�ne selon le type
    GdkPixbufAnimation *anim;     // Animation de l'image (utilis� si le type est 2)
    GtkIconSize size;             // Taille de l'ic�ne (utilis� si le type est 3)
    style s;                      // Structure pour d�finir la largeur et la hauteur de l'image
} image;

// Fonction pour initialiser une image avec des param�tres sp�cifiques
image *initialiser_image(GtkWidget *pere, gint t, const gchar *fichier, GtkIconSize sz, gint w, gint h)
{
    // Allouer dynamiquement de la m�moire pour une nouvelle structure image
    image *img = (image *)g_malloc(sizeof(image));

    // Initialiser les champs de la structure image
    img->parent = pere;                // Stocker le widget parent
    img->type = t;                     // Stocker le type d'image
    img->icon_anim_stock = fichier;    // Stocker le chemin du fichier, nom de l'animation, ou nom d'ic�ne
    img->size = sz;                    // Stocker la taille de l'ic�ne
    img->s.w = w;                      // Stocker la largeur sp�cifi�e
    img->s.h = h;                      // Stocker la hauteur sp�cifi�e

    // Renvoyer un pointeur vers la structure image nouvellement cr��e
    return img;
}

// Fonction pour changer la taille de l'image en fonction des sp�cifications
void change_size(image *img)
{
    GdkPixbuf *image = gdk_pixbuf_new_from_file(img->icon_anim_stock, NULL);

    // Sp�cifier la nouvelle largeur et hauteur souhait�es
    int nouvelle_largeur = img->s.w;
    int nouvelle_hauteur = img->s.h;

    // Redimensionner l'image
    GdkPixbuf *image_redimensionnee = gdk_pixbuf_scale_simple(image, nouvelle_largeur, nouvelle_hauteur, GDK_INTERP_BILINEAR);

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
        if (img->s.w || img->s.h)
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

/**********************************************************************************************************/


// Structure pour repr�senter un cadre (frame) avec des �l�ments associ�s
typedef struct
{
    GtkWidget *widget;          // Le widget GTK repr�sentant le cadre
    GtkWidget *parent;          // Le parent du cadre
    gint xligne;                // Position horizontale de l'�tiquette dans le cadre
    gint yligne;                // Position verticale de l'�tiquette dans le cadre
    texte *text;                // Structure de texte associ�e au cadre
    GtkWidget *conteneur;       // Le conteneur associ� au cadre (peut �tre un label ou autre)
    GtkShadowType type;         // Type d'ombre du cadre
} frame;

// Fonction pour initialiser une structure de cadre avec des param�tres sp�cifi�s
frame *initialiser_frame(GtkWidget *pere, gint x, gint y, texte *t, GtkWidget *fils, GtkShadowType type)
{
    // Allouer dynamiquement la m�moire pour la structure de cadre
    frame *fr = (frame *)g_malloc(sizeof(frame));

    // Initialiser les champs de la structure avec les valeurs sp�cifi�es
    fr->widget = gtk_frame_new(NULL);
    fr->text = t;
    fr->parent = pere;
    fr->type = type;
    fr->xligne = x;
    fr->yligne = y;
    fr->conteneur = fils;

    // Retourner la structure de cadre initialis�e
    return fr;
}

// Fonction pour cr�er un cadre en utilisant les param�tres sp�cifi�s dans la structure
void creer_frame(frame *fr)
{
    // Cr�er une cha�ne de caract�res format�e pour l'�tiquette avec des propri�t�s de texte sp�cifi�es
    gchar *lab = g_strdup_printf("<span  font_desc=\"%d\" style=\"%s\" foreground=\"%s\" font_family=\"%s\" underline=\"%s\">%s</span> ", fr->text->taille_text, fr->text->style, fr->text->couleur_text, fr->text->police, fr->text->underline, fr->text->text);

    // Cr�er un widget de label GTK et d�finir son contenu avec la cha�ne format�e
    GtkWidget *label = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(label), lab);

    // D�finir le label comme �tiquette du cadre
    gtk_frame_set_label_widget(GTK_FRAME(fr->widget), label);

    // Assigner le label au conteneur du cadre
    fr->conteneur = label;

    // Si des positions sp�cifi�es, les appliquer � l'�tiquette du cadre
    if (fr->xligne || fr->yligne)
        gtk_frame_set_label_align(GTK_FRAME(fr->widget), fr->xligne, fr->yligne);

    // Si un type d'ombre sp�cifi�, l'appliquer au cadre
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

/**********************************************************************************************************/

// D�finition de la structure barre_prog
typedef struct
{
    GtkWidget *widget;   // Pointeur vers l'objet de la barre de progression (GtkProgressBar)
    GtkWidget *parent;   // Pointeur vers un widget parent
    gdouble fraction;    // La fraction actuelle de la barre de progression (peut varier de 0 � 1)
    gdouble unite;      // L'unit� de progression de la barre de progression
    style s;

} barre_prog;

// Fonction pour initialiser une barre_prog avec des valeurs sp�cifi�es
barre_prog *initialiser_barre_prog(GtkWidget *pere,gdouble dfr, gdouble unt,gint w,gint h)
{
    // Allocation dynamique de m�moire pour une nouvelle structure barre_prog
    barre_prog *ProgressBar = (barre_prog *)g_malloc(sizeof(barre_prog));

    // Cr�ation d'une nouvelle barre de progression GtkProgressBar et assignation au champ widget
    ProgressBar->widget = gtk_progress_bar_new();
    ProgressBar->parent=pere;
    ProgressBar->s.w=w;
    ProgressBar->s.h=h;
    if(ProgressBar->s.w || ProgressBar->s.h)
          gtk_widget_set_size_request(ProgressBar->widget, ProgressBar->s.w, ProgressBar->s.h);
    // Initialisation des champs fraction et unite avec les valeurs sp�cifi�es
    ProgressBar->unite = unt;
    ProgressBar->fraction = dfr;

    // Retour de la structure initialis�e
    return ProgressBar;
}

// Fonction pour animer la progression d'une barre
void progression_animation(barre_prog *pWidget, gpointer data)
{
    gdouble dFraction;      // Fraction de progression
    gint i = (pWidget->fraction * 2000);  // Conversion de la fraction en entier
    gint iTotal = 2000;     // Valeur totale pour la boucle d'animation

    /* Initialisation de l'animation */
    gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(pWidget->widget), pWidget->fraction);

    /* Acquisition du grab sur la barre de progression pour optimiser et bloquer les actions de l'utilisateur */
    gtk_grab_add(pWidget->widget);
    printf("D�but de l'animation de progression\n");

    // Boucle d'animation
    for (i; i < iTotal; ++i)
    {
        dFraction = (gdouble)i / (gdouble)iTotal;

        /* Modification de la valeur de la barre de progression */
        gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(pWidget->widget), dFraction);

        /* Permet � GTK+ de traiter les �v�nements en cours */
        gtk_main_iteration();
    }

    /* Lib�ration du grab sur la barre de progression � la fin de l'animation */
    gtk_grab_remove(pWidget->widget);
}

void MettreAJourBarreProgression(barre_prog *pWidget, gpointer data)
{
   // R�cup�ration de la valeur actuelle de la barre de progression
   gdouble valeurCourante = gtk_progress_bar_get_fraction(GTK_PROGRESS_BAR(pWidget->widget));

   // Ajout de l'unit� � la valeur actuelle
   valeurCourante += pWidget->unite;

   // Si la nouvelle valeur d�passe 1.0, revenir � 0.0
   if (valeurCourante > 1.0)
      valeurCourante = 0.0;

   // Mise � jour de la valeur de la barre de progression dans la structure
   pWidget->fraction = valeurCourante;

   // Modification de la valeur de la barre de progression
   gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(pWidget->widget), valeurCourante);
}

void add_progress_bar(GtkWidget *pere,gdouble dfr,gdouble unite,gint x,gint y,gboolean type,gint w,gint h)
{
    barre_prog *bar=initialiser_barre_prog(pere,dfr,unite,w,h);
    GtkWidget *pVBox=gtk_vbox_new(FALSE,10);
    gtk_box_pack_start(GTK_BOX(pMainVBox),bar->widget, TRUE, FALSE, 0);
    switch(type)
    {
        case 0:
        case 1:
               pButton = gtk_button_new_with_label("ajouter unite");
               gtk_box_pack_start(GTK_BOX(pMainVBox), pButton, TRUE, FALSE, 0);
               g_signal_connect_swapped(G_OBJECT(pButton), "clicked", G_CALLBACK(OnButton),bar);
               if(type==1) break;
        case 2:pButton1 = gtk_button_new_with_label(GTK_STOCK_REFRESH);
                gtk_box_pack_start(GTK_BOX(pMainVBox), pButton1, TRUE, FALSE, 0);
               g_signal_connect_swapped(G_OBJECT(pButton1), "clicked", G_CALLBACK(OnButton1),bar);
               break;
    }
    gtk_fixed_put(pere,pVBox,x,y);

}

