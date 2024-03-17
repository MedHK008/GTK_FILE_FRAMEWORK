#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED


// Structure pour les éléments d'un menu ou sous-menu

// Définition des constantes pour les types d'éléments de menu
#define DEFAULT_MENU 0
#define CHECKBOX_MENU 1
#define SEPARATOR_MENU 2
#define IMAGE_MENU 3
#define RADIO_MENU 4

//Definir les constantes pour l'orientaton
#define ORIENTATION_H 0
#define ORIENTATION_V 1


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

menu* RadioGroup(menu* M)
{
  menu *courant;
  for (courant = M; courant; courant = courant->suivant)
     if(courant->IsradioGroup)
        return courant;

 return NULL;
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
                    //image
                } else {
                    // Créer un élément de menu sans icône
                    menu_elem->menu_item = gtk_menu_item_new_with_mnemonic(menu_elem->nom);
                }
                break;
            case 4:
                // Créer un bouton radio
                menu* Rgroup = RadioGroup(parent_menu->liste);
                if ((!parent_menu->liste) ||(!Rgroup))
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


// Fonction pour créer et ajouter une barre de menus à un conteneur GtkFixed
menubar *add_menu_bar(GtkWidget *parent_container, gint orientation) {
    // Création de la barre de menus
    menubar *menu_bar = creer_menubar(orientation, parent_container);

    // Ajout de la barre de menus au conteneur GtkFixed
    gtk_fixed_put(GTK_FIXED(parent_container), menu_bar->menubar, 0, 0);

    // Retour de la barre de menus nouvellement créée
    return menu_bar;
}

menu *add_menu(menubar *mbar, gchar *label)
{
    // Initialisation de l'élément de menu
    menu *new_menu_item = init_menu_item(0, label,TRUE, FALSE);
    // Ajout de l'élément de menu au menu parent
    ajouter_menu(mbar, new_menu_item);
    // Retour de le menu nouvellement créé
    return new_menu_item;
}

menu *add_menu_item(menu *parent_menu, guint type, gchar *label, gboolean isSubmenu, gboolean isRadioGroup,  gchar *icon) {
    // Initialisation de l'élément de menu
    menu *new_menu_item = init_menu_item(type, label, isSubmenu, isRadioGroup);
    // Ajout de l'élément de menu au menu parent
    ajouter_menu_item(parent_menu, new_menu_item, icon);
    // Retour de l'élément de menu nouvellement créé
    return new_menu_item;
}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    // Création de la fenêtre principale
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Menu Example");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);

    GtkWidget *Fixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(window), Fixed);

    // Ajout de la barre de menus à la fenêtre principale
    menubar *maMenuBar = add_menu_bar(Fixed, 0);

    // Exemple d'ajout d'un menu "File"
    menu *menu_file = add_menu(maMenuBar, "File");
    // Exemple d'ajout d'éléments de menu à "File"
    menu *menu_open = add_menu_item(menu_file, 0, "_New", TRUE, FALSE, NULL);
       add_menu_item(menu_open, 0, "empty file", FALSE, FALSE, NULL);
       add_menu_item(menu_open, 2, "sep", FALSE, FALSE, NULL);
       add_menu_item(menu_open, 0, "project...", FALSE, FALSE, NULL);
       add_menu_item(menu_file, 0, "_Save", FALSE, FALSE, NULL);

    // Exemple d'ajout d'un menu "Edit"
    menu *menu_edit = add_menu(maMenuBar, "Edit");
        // Exemple d'ajout d'éléments de menu à "Edit"
        add_menu_item(menu_edit,0, "C_ut", FALSE, FALSE, NULL);
        add_menu_item(menu_edit, 0, "_Copy", FALSE, TRUE, NULL);
        add_menu_item(menu_edit, 0, "_Paste", FALSE, FALSE, NULL);

     menu *menu_view = add_menu(maMenuBar, "View");
       menu *menu_tool = add_menu_item(menu_view,0, "_Toolbars", TRUE, FALSE, NULL);
           add_menu_item(menu_tool,0, "Fit toolbar", FALSE, FALSE, NULL);
           add_menu_item(menu_tool, 0, "OPtimise toolbar", FALSE, FALSE, NULL);
           add_menu_item(menu_tool, 2, NULL, FALSE, FALSE, NULL);
           add_menu_item(menu_tool,1, "Compiler", FALSE, FALSE, NULL);
           add_menu_item(menu_tool, 1, "Debuger", FALSE, FALSE, NULL);
           add_menu_item(menu_view, 1, "Status_bar", FALSE, FALSE, NULL);
       add_menu_item(menu_view,1, "_Logs", FALSE, FALSE, NULL);
       add_menu_item(menu_view, 1, "_Manager", FALSE, FALSE, NULL);
       add_menu_item(menu_view, 1, "Status_bar", FALSE, FALSE, NULL);

    // Exemple d'ajout d'un menu "Language"
    menu *menu_language = add_menu(maMenuBar, "Language");
    // Exemple d'ajout d'éléments radio à "Language"
       add_menu_item(menu_language, 4, "C/C++", FALSE, TRUE, NULL);
       add_menu_item(menu_language, 4, "Python", FALSE, FALSE, NULL);
       add_menu_item(menu_language, 4, "Java", FALSE, FALSE, NULL);
       add_menu_item(menu_language, 4, "C#", FALSE, FALSE, NULL);
       add_menu_item(menu_language, 4, "JavaScript", FALSE, FALSE, NULL);
       add_menu_item(menu_language, 4, "PHP", FALSE, FALSE, NULL);

    //Connexion du signal destroy pour quitter l'application
    g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Affichage de la fenêtre et exécution de la boucle principale GTK
    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}




#endif // MENU_H_INCLUDED
