#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED


// Structure pour les éléments d'un menu ou sous-menu
typedef struct Menu {
    GtkWidget *MENU;         // Contient le sous-menu associé à l'élément du menu
    GtkWidget *menu_item;    // Contient le widget GTK de l'élément du menu
    guint type_composant;    // Type de l'élément du menu (1: checkbox, 2: séparateur, 3: image, 4: radio)
    gboolean IsSubmenu;      // Indique si l'élément du menu est un sous-menu
    gchar *nom;              // Nom de l'élément du menu
    struct Menu *suivant;    // Pointeur vers l'élément de menu suivant dans la liste
    struct Menu *liste;      // Liste des éléments de sous-menu s'il s'agit d'un menu
} menu;

// Structure pour la barre de menus
typedef struct {
    GtkWidget *menubar;// Contient la barre de menus GTK
    GtkWidget *parent; // Contient le widget parent (généralement la fenêtre principale)
    gint orientation;  // Orientation de la barre de menus (1: V, par défaut: H)
    menu *liste;      // Liste des éléments de menu dans la barre de menus
} menubar;

// Fonction pour créer une barre de menus
menubar *creer_menubar(gint orientation,GtkWidget *parent)
{
    // Allocation de la mémoire pour la structure menubar
    menubar *mbar = malloc(sizeof(menubar));
    if (!mbar) {
        // Gestion de l'erreur d'allocation mémoire
        printf("\nEchec d'allocation mémoire pour la barre de menu");
        exit(-1);
    }

    // Initialisation des attributs de la structure
    mbar->parent = parent;
    mbar->liste = NULL;//initialiser la liste des menu par NULL

    // Création de la barre de menus GTK
    mbar->menubar = gtk_menu_bar_new();

    // Définition de l'orientation de la barre de menus
    switch (orientation) {
    case 1:
        // Orientation verticale
        gtk_menu_bar_set_pack_direction(GTK_MENU_BAR(mbar->menubar), GTK_PACK_DIRECTION_TTB);
        break;
    default:
        // Orientation horizontale (par défaut)
        gtk_menu_bar_set_pack_direction(GTK_MENU_BAR(mbar->menubar), GTK_PACK_DIRECTION_LTR);
        break;
    }


    // Retour de la structure menubar
    return mbar;
}

//Fonction pour initialiser un élément de menu
menu* init_menu_item(guint type, gchar *nom, gboolean Submenu)
{
    // Allocation de la mémoire pour la structure menu
    menu *NM = malloc(sizeof(menu));
    if (!NM) {
        // Gestion de l'erreur d'allocation mémoire
        g_critical("Echec d'allocation mémoire pour l'élément de menu");
        exit(-1);
    }

    // Allocation de la mémoire pour le nom de l'élément
    if (nom) {
        // Copie du nom passé en paramètre
        NM->nom = g_strdup(nom);
    } else {
        // Nom par défaut (NULL)
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

// Fonction pour ajouter un menu à la barre de menus
void ajouter_menu(menubar *M, menu *menu_child)
{
    if (!M->liste)
        M->liste = menu_child;
    else {
        // Insertion à la fin de la liste
        menu *courant;
        for (courant = M->liste; courant->suivant; courant = courant->suivant);
        courant->suivant = menu_child;
        menu_child->suivant = NULL;
    }

    // Créer le widget de l'élément de menu
    menu_child->menu_item = gtk_menu_item_new_with_label(menu_child->nom);
    menu_child->MENU = gtk_menu_new();
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(menu_child->menu_item), menu_child->MENU);

    // Ajouter l'élément de menu à la barre de menus
    gtk_menu_shell_append(GTK_MENU_SHELL(M->menubar), menu_child->menu_item);
}

// Fonction pour ajouter un élément de menu à un menu parent
void ajouter_menu_item(menu *parent_menu, menu *menu_elem, const gchar *icon)
{
    // Vérifie si le menu parent a déjà un élément
    if (!parent_menu->liste)
        // Le menu parent est vide, ajouter l'élément comme premier élément
        parent_menu->liste = menu_elem;
    else {
        // Le menu parent n'est pas vide, ajouter l'élément à la fin de la liste
        menu *courant;
        for (courant = parent_menu->liste; courant->suivant; courant = courant->suivant) {}
        // La boucle trouve le dernier élément de la liste
        courant->suivant = menu_elem;
        menu_elem->suivant = NULL; // Marque la fin de la liste
    }

    // Si l'élément n'est pas un sous-menu, créer le widget approprié en fonction du type
    if (!menu_elem->IsSubmenu) {
        switch (menu_elem->type_composant) {
            case 1:
                // Créer une case à cocher
                menu_elem->menu_item = gtk_check_menu_item_new_with_label(menu_elem->nom);
//                    menu_elem->menu_item = init_cocher(menu_elem->MENU,"koko",menu_elem->MENU,0,0);
                break;
            case 2:
                // Créer un séparateur
                menu_elem->menu_item = gtk_separator_menu_item_new();
                break;
            case 3:
                // Créer un élément avec une image
                menu_elem->menu_item = gtk_menu_item_new_with_label(menu_elem->nom);
                GtkWidget *copy_image = gtk_image_new_from_icon_name(icon, GTK_ICON_SIZE_MENU);
//                gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(menu_elem->menu_item), copy_image);
                break;
            case 4:
                // Créer un bouton radio
                menu_elem->menu_item = gtk_radio_menu_item_new_with_label(parent_menu->liste, menu_elem->nom);
                break;
            default:
                // Item par défaut (élément de menu standard)
                menu_elem->menu_item = gtk_menu_item_new_with_label(menu_elem->nom);
                break;
        }
    } else {
        // Créer un sous-menu
        menu_elem->menu_item = gtk_menu_item_new_with_label(menu_elem->nom);
        menu_elem->MENU = gtk_menu_new();
        gtk_menu_item_set_submenu(GTK_MENU_ITEM(menu_elem->menu_item), menu_elem->MENU);
    }

    // Ajouter l'élément (ou le sous-menu) au menu parent
    gtk_menu_shell_append(GTK_MENU_SHELL(parent_menu->MENU), menu_elem->menu_item);
}

#endif // MENU_H_INCLUDED
