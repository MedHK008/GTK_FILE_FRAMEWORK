#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED


// Structure pour les �l�ments d'un menu ou sous-menu
typedef struct Menu {
    GtkWidget *MENU;         // Contient le sous-menu associ� � l'�l�ment du menu
    GtkWidget *menu_item;    // Contient le widget GTK de l'�l�ment du menu
    guint type_composant;    // Type de l'�l�ment du menu (1: checkbox, 2: s�parateur, 3: image, 4: radio)
    gboolean IsSubmenu;      // Indique si l'�l�ment du menu est un sous-menu
    gchar *nom;              // Nom de l'�l�ment du menu
    struct Menu *suivant;    // Pointeur vers l'�l�ment de menu suivant dans la liste
    struct Menu *liste;      // Liste des �l�ments de sous-menu s'il s'agit d'un menu
} menu;

// Structure pour la barre de menus
typedef struct {
    GtkWidget *menubar;// Contient la barre de menus GTK
    GtkWidget *parent; // Contient le widget parent (g�n�ralement la fen�tre principale)
    gint orientation;  // Orientation de la barre de menus (1: V, par d�faut: H)
    menu *liste;      // Liste des �l�ments de menu dans la barre de menus
} menubar;

// Fonction pour cr�er une barre de menus
menubar *creer_menubar(gint orientation,GtkWidget *parent)
{
    // Allocation de la m�moire pour la structure menubar
    menubar *mbar = malloc(sizeof(menubar));
    if (!mbar) {
        // Gestion de l'erreur d'allocation m�moire
        printf("\nEchec d'allocation m�moire pour la barre de menu");
        exit(-1);
    }

    // Initialisation des attributs de la structure
    mbar->parent = parent;
    mbar->liste = NULL;//initialiser la liste des menu par NULL

    // Cr�ation de la barre de menus GTK
    mbar->menubar = gtk_menu_bar_new();

    // D�finition de l'orientation de la barre de menus
    switch (orientation) {
    case 1:
        // Orientation verticale
        gtk_menu_bar_set_pack_direction(GTK_MENU_BAR(mbar->menubar), GTK_PACK_DIRECTION_TTB);
        break;
    default:
        // Orientation horizontale (par d�faut)
        gtk_menu_bar_set_pack_direction(GTK_MENU_BAR(mbar->menubar), GTK_PACK_DIRECTION_LTR);
        break;
    }


    // Retour de la structure menubar
    return mbar;
}

//Fonction pour initialiser un �l�ment de menu
menu* init_menu_item(guint type, gchar *nom, gboolean Submenu)
{
    // Allocation de la m�moire pour la structure menu
    menu *NM = malloc(sizeof(menu));
    if (!NM) {
        // Gestion de l'erreur d'allocation m�moire
        g_critical("Echec d'allocation m�moire pour l'�l�ment de menu");
        exit(-1);
    }

    // Allocation de la m�moire pour le nom de l'�l�ment
    if (nom) {
        // Copie du nom pass� en param�tre
        NM->nom = g_strdup(nom);
    } else {
        // Nom par d�faut (NULL)
        NM->nom = NULL;
    }

    // Initialisation des attributs de la structure
    NM->IsSubmenu = Submenu;
    NM->type_composant = type;
    NM->liste = NULL;
    NM->suivant=NULL;

    // Retour de la structure menu
    return NM;
}

// Fonction pour ajouter un menu � la barre de menus
void ajouter_menu(menubar *M, menu *menu_child)
{
    if (!M->liste)
        M->liste = menu_child;
    else {
        // Insertion � la fin de la liste
        menu *courant;
        for (courant = M->liste; courant->suivant; courant = courant->suivant);
        courant->suivant = menu_child;
        menu_child->suivant = NULL;
    }

    // Cr�er le widget de l'�l�ment de menu
    menu_child->menu_item = gtk_menu_item_new_with_label(menu_child->nom);
    menu_child->MENU = gtk_menu_new();
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(menu_child->menu_item), menu_child->MENU);

    // Ajouter l'�l�ment de menu � la barre de menus
    gtk_menu_shell_append(GTK_MENU_SHELL(M->menubar), menu_child->menu_item);
}

// Fonction pour ajouter un �l�ment de menu � un menu parent
void ajouter_menu_item(menu *parent_menu, menu *menu_elem, const gchar *icon)
{
    // V�rifie si le menu parent a d�j� un �l�ment
    if (!parent_menu->liste)
        // Le menu parent est vide, ajouter l'�l�ment comme premier �l�ment
        parent_menu->liste = menu_elem;
    else {
        // Le menu parent n'est pas vide, ajouter l'�l�ment � la fin de la liste
        menu *courant;
        for (courant = parent_menu->liste; courant->suivant; courant = courant->suivant) {}
        // La boucle trouve le dernier �l�ment de la liste
        courant->suivant = menu_elem;
        menu_elem->suivant = NULL; // Marque la fin de la liste
    }

    // Si l'�l�ment n'est pas un sous-menu, cr�er le widget appropri� en fonction du type
    if (!menu_elem->IsSubmenu) {
        switch (menu_elem->type_composant) {
            case 1:
                // Cr�er une case � cocher
                menu_elem->menu_item = gtk_check_menu_item_new_with_label(menu_elem->nom);
//                    menu_elem->menu_item = init_cocher(menu_elem->MENU,"koko",menu_elem->MENU,0,0);
                break;
            case 2:
                // Cr�er un s�parateur
                menu_elem->menu_item = gtk_separator_menu_item_new();
                break;
            case 3:
                // Cr�er un �l�ment avec une image
                menu_elem->menu_item = gtk_menu_item_new_with_label(menu_elem->nom);
                GtkWidget *copy_image = gtk_image_new_from_icon_name(icon, GTK_ICON_SIZE_MENU);
//                gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(menu_elem->menu_item), copy_image);
                break;
            case 4:
                // Cr�er un bouton radio
                menu_elem->menu_item = gtk_radio_menu_item_new_with_label(parent_menu->liste, menu_elem->nom);
                break;
            default:
                // Item par d�faut (�l�ment de menu standard)
                menu_elem->menu_item = gtk_menu_item_new_with_label(menu_elem->nom);
                break;
        }
    } else {
        // Cr�er un sous-menu
        menu_elem->menu_item = gtk_menu_item_new_with_label(menu_elem->nom);
        menu_elem->MENU = gtk_menu_new();
        gtk_menu_item_set_submenu(GTK_MENU_ITEM(menu_elem->menu_item), menu_elem->MENU);
    }

    // Ajouter l'�l�ment (ou le sous-menu) au menu parent
    gtk_menu_shell_append(GTK_MENU_SHELL(parent_menu->MENU), menu_elem->menu_item);
}

#endif // MENU_H_INCLUDED
