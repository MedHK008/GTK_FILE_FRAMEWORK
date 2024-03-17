#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED


// Structure pour les éléments d'un menu ou sous-menu


typedef struct Menu {
    GtkWidget *MENU;         // Contient le sous-menu associé à l'élément du menu
    GtkWidget *menu_item;    // Contient le widget GTK de l'élément du menu
    guint type_composant;
    gboolean IsradioGroup;   // Type de l'élément du menu (1: checkbox, 2: séparateur, 3: image, 4: radio)
    gboolean IsSubmenu;      // Indique si l'élément du menu est un sous-menu
    gchar *nom;              // Nom de l'élément du menu
    struct Menu *suivant;    // Pointeur vers l'élément de menu suivant dans la liste
    struct Menu *liste;      // Liste des éléments de sous-menu s'il s'agit d'un menu
} menu;

menu* RadioGroup(menu* M)
{
  menu *courant;
  for (courant = M; courant; courant = courant->suivant)
     if(courant->IsradioGroup)
        return courant;

 return NULL;
}
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
menu* init_menu_item(guint type, gchar *nom, gboolean Submenu, gboolean isRadioGroup)
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
    NM->IsradioGroup= isRadioGroup;
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
                menu_elem->menu_item = gtk_check_menu_item_new_with_mnemonic(menu_elem->nom);
                break;
            case 2:
                // Créer un séparateur
                menu_elem->menu_item = gtk_separator_menu_item_new();
                break;
            case 3:
                  if (icon) {
                    // Chargement de l'icône prédéfinie à partir du thème d'icônes par défaut
                    GtkIconTheme *icon_theme = gtk_icon_theme_get_default();
                    GdkPixbuf *icon_pixbuf = gtk_icon_theme_load_icon(icon_theme, icon, GTK_ICON_SIZE_MENU, GTK_ICON_LOOKUP_USE_BUILTIN, NULL);

                    // Créer le widget de l'élément de menu avec l'icône chargée
                    menu_elem->menu_item = gtk_image_menu_item_new_with_mnemonic(menu_elem->nom);
                    GtkWidget *icon_image = gtk_image_new_from_pixbuf(icon_pixbuf);
                    gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(menu_elem->menu_item), icon_image);

                    // Libérer la mémoire allouée pour le pixbuf de l'icône
                    g_object_unref(icon_pixbuf);
                } else {
                    // Créer un élément de menu sans icône
                    menu_elem->menu_item = gtk_menu_item_new_with_mnemonic(menu_elem->nom);
                }
                break;
            case 4:
                // Créer un bouton radio
                menu* Rgroup = RadioGroup(parent_menu->liste);
                if (!parent_menu->liste)
                    menu_elem->menu_item = gtk_radio_menu_item_new_with_mnemonic(NULL, menu_elem->nom);
                else if(Rgroup)
                    menu_elem->menu_item = gtk_radio_menu_item_new_with_mnemonic_from_widget(GTK_RADIO_MENU_ITEM(Rgroup->menu_item), menu_elem->nom);
                break;
            default:
                // Item par défaut (élément de menu standard)
                menu_elem->menu_item = gtk_menu_item_new_with_mnemonic(menu_elem->nom);
                break;
        }
    } else {
        // Créer un sous-menu
        menu_elem->menu_item = gtk_menu_item_new_with_mnemonic(menu_elem->nom);
        menu_elem->MENU = gtk_menu_new();
        gtk_menu_item_set_submenu(GTK_MENU_ITEM(menu_elem->menu_item), menu_elem->MENU);
    }

    // Ajouter l'élément (ou le sous-menu) au menu parent
    gtk_menu_shell_append(GTK_MENU_SHELL(parent_menu->MENU), menu_elem->menu_item);
}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    // Création de la fenêtre principale
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Menu Example");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);

     GtkWidget *Fixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(window), Fixed);

    // Création de la barre de menus
    menubar *maMenuBar = creer_menubar(0, Fixed);

    // Ajout de la barre menu au conteneur GtkFixed
   gtk_fixed_put(GTK_FIXED(Fixed), maMenuBar->menubar, 0, 0);

    // Exemple d'ajout d'un menu "File"
    menu *menu_file = init_menu_item(0, "File", TRUE,FALSE);
    ajouter_menu(maMenuBar, menu_file);

    // Exemple d'ajout d'éléments de menu à "File"
    menu *menu_open = init_menu_item(0, "_Open", TRUE,FALSE);
    ajouter_menu_item(menu_file, menu_open,NULL);

        menu *menu_here = init_menu_item(1, "project", FALSE,FALSE);
        ajouter_menu_item(menu_open, menu_here,NULL);
          menu *menu_sep = init_menu_item(2,"sep" , FALSE,FALSE);
          ajouter_menu_item(menu_open, menu_sep,NULL);
           menu *menu_there = init_menu_item(0,"file" ,TRUE,FALSE);
          ajouter_menu_item(menu_open, menu_there,NULL);

    menu *menu_save = init_menu_item(1, "_Save", FALSE,FALSE);
    ajouter_menu_item(menu_file, menu_save, NULL);

    // Exemple d'ajout d'un menu "Edit"
    menu *menu_edit = init_menu_item(0, "Edit", TRUE,FALSE);
    ajouter_menu(maMenuBar, menu_edit);

    // Exemple d'ajout d'éléments de menu à "Edit"
    menu *menu_cut = init_menu_item(1, "C_ut",FALSE ,FALSE);
    ajouter_menu_item(menu_edit, menu_cut, NULL);

    menu *menu_copy = init_menu_item(3, "_Copy",FALSE ,FALSE);
    ajouter_menu_item(menu_edit, menu_copy, "edit-copy");

    menu *menu_paste = init_menu_item(3, "_Paste",FALSE,FALSE);
    ajouter_menu_item(menu_edit, menu_paste, "edit-paste");

     menu *menu_S = init_menu_item(0, "Language", TRUE,FALSE);
    ajouter_menu(maMenuBar, menu_S);
     menu *menu_B = init_menu_item(0, "Build", TRUE,FALSE);
    ajouter_menu(maMenuBar, menu_B);
    menu *menu_D = init_menu_item(0, "Debug", TRUE,FALSE);
    ajouter_menu(maMenuBar, menu_D);
     menu *menu_Set= init_menu_item(0, "Settings", TRUE,FALSE);
    ajouter_menu(maMenuBar, menu_Set);
    menu *menu_Help = init_menu_item(0, "Help", TRUE,FALSE);
    ajouter_menu(maMenuBar, menu_Help);


    gtk_container_add(GTK_CONTAINER(window), Fixed);




    // Connexion du signal destroy pour quitter l'application
    g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Affichage de la fenêtre et exécution de la boucle principale GTK
    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}




#endif // MENU_H_INCLUDED
