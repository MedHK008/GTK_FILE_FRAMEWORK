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
        NM->nom = NULL;
    }

    NM->IsSubmenu = Submenu;
    NM->type_composant = type;
    NM->liste = NULL;
    NM->suivant=NULL;

    return NM;
}

void ajouter_menu(menubar *M, menu *menu_child)
{
    if (!M->liste)
        M->liste = menu_child;
    else {
        menu *courant;
        for (courant = M->liste; courant->suivant; courant = courant->suivant);
        courant->suivant = menu_child;
        menu_child->suivant = NULL;
    }

    menu_child->menu_item = gtk_menu_item_new_with_label(menu_child->nom);
    menu_child->MENU = gtk_menu_new();
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(menu_child->menu_item), menu_child->MENU);

    gtk_menu_shell_append(GTK_MENU_SHELL(M->menubar), menu_child->menu_item);
}

void ajouter_menu_item(menu *parent_menu, menu *menu_elem, const gchar *icon)
{
    if (!parent_menu->liste)
        parent_menu->liste = menu_elem;
    else {
        menu *courant;
        for (courant = parent_menu->liste; courant->suivant; courant = courant->suivant) {}
        courant->suivant = menu_elem;
        menu_elem->suivant = NULL;
    }
    if (!menu_elem->IsSubmenu) {
        switch (menu_elem->type_composant) {
            case 1:
                menu_elem->menu_item = gtk_check_menu_item_new_with_label(menu_elem->nom);
//                menu_elem->menu_item = init_cocher(menu_elem->MENU,"koko",menu_elem->MENU,0,0);
                break;
            case 2:
                menu_elem->menu_item = gtk_separator_menu_item_new();
                break;
            case 3:
                menu_elem->menu_item = gtk_menu_item_new_with_label(menu_elem->nom);
                GtkWidget *copy_image = gtk_image_new_from_icon_name(icon, GTK_ICON_SIZE_MENU);
                gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(menu_elem->menu_item), copy_image);
                break;
            case 4:
                menu_elem->menu_item = gtk_radio_menu_item_new_with_label(parent_menu->liste, menu_elem->nom);
                break;
            default:
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


void add_menu(GtkWidget* Fixed1)
{
    menubar *maMenuBar = creer_menubar(0, Fixed1);
   gtk_fixed_put(GTK_FIXED(Fixed1), maMenuBar->menubar, 0, 0);
    menu *menu_file = init_menu_item(0, "File", TRUE);
    ajouter_menu(maMenuBar, menu_file);
    menu *menu_open = init_menu_item(0, "Open", FALSE);
    ajouter_menu_item(menu_file, menu_open,NULL);
    menu *menu_save = init_menu_item(1, "Save", FALSE);
    ajouter_menu_item(menu_file, menu_save, NULL);
    menu *menu_edit = init_menu_item(0, "Edit", TRUE);
    ajouter_menu(maMenuBar, menu_edit);
    menu *menu_cut = init_menu_item(1, "Cut", FALSE);
    ajouter_menu_item(menu_edit, menu_cut, NULL);
    menu *menu_copy = init_menu_item(1, "Copy", FALSE);
    ajouter_menu_item(menu_edit, menu_copy, NULL);
    menu *menu_paste = init_menu_item(1, "Paste", FALSE);
    ajouter_menu_item(menu_edit, menu_paste, NULL);
     menu *menu_S = init_menu_item(0, "Search", TRUE);
    ajouter_menu(maMenuBar, menu_S);
     menu *menu_B = init_menu_item(0, "Build", TRUE);
    ajouter_menu(maMenuBar, menu_B);
    menu *menu_D = init_menu_item(0, "Debug", TRUE);
    ajouter_menu(maMenuBar, menu_D);
     menu *menu_Set= init_menu_item(0, "Settings", TRUE);
    ajouter_menu(maMenuBar, menu_Set);
    menu *menu_Help = init_menu_item(0, "Help", TRUE);
    ajouter_menu(maMenuBar, menu_Help);
}

#endif // MENU_H_INCLUDED
