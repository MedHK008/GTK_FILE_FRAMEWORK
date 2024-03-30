#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED



// Définition des constantes pour les types d'éléments de menu
guint DEFAULT_MENU=0;
guint CHECKBOX_MENU=1;
guint SEPARATOR_MENU=2;
guint IMAGE_MENU=3;
guint RADIO_MENU=4;


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
    gchar* name;
    guint posx,posy;
    GtkPackDirection orientation;  // Orientation de la barre de menus
      /*GTK_PACK_DIRECTION_TTB   haut vers le bas (Vertical)
      GTK_PACK_DIRECTION_BTT    bas vers le haut  (Vertical)
      GTK_PACK_DIRECTION_LTR    gauche vers droite (horizontal)
      GTK_PACK_DIRECTION_RTL    droite vers le gauche(horizontal)
      */
   menu *liste;      // Liste des éléments de menu dans la barre de menus
} menubar;

GtkPackDirection string_to_pack_direction(gchar *str)
{
    if (strcmp(str, "LTR") == 0)
        return GTK_PACK_DIRECTION_LTR;
    else if (strcmp(str, "RTL") == 0)
        return GTK_PACK_DIRECTION_RTL;
    else if (strcmp(str, "TTB") == 0)
        return GTK_PACK_DIRECTION_TTB;
    else if (strcmp(str, "BTT") == 0)
        return GTK_PACK_DIRECTION_BTT;
    else {
        return GTK_PACK_DIRECTION_LTR; // ou une autre valeur par défaut
    }
}

menubar* init_menubar()
{
    menubar* mb = (menubar*)malloc(sizeof(menubar));
    if (!mb)
    {
        printf("\nErreur d'allocation !!\n");
        exit(0);
    }
    mb->menubar=(GtkWidget*)g_malloc(sizeof(GtkWidget));
    mb->parent=(GtkWidget*)g_malloc(sizeof(GtkWidget));
    mb->name=(gchar*)g_malloc(sizeof(gchar)*30);
    mb->name[0] ='\0';
    mb->posx=0;
    mb->posy=0;
    mb->orientation=GTK_PACK_DIRECTION_LTR;
    mb->parent=NULL;
    mb->liste=NULL;
    return mb;
}

menubar* menubarFunction(menubar* mb,FILE* F)
{
    int i;
    gchar* elem;
    elem=(gchar*)g_malloc(sizeof(gchar)*50);
    gchar c;
    do
    {
        fscanf(F,"%s",elem);
        if (strcmp(elem, "name") == 0) {
            if ((c = epurer_blan(F)) == '=') {
                if ((c = epurer_blan(F)) == '\"') {
                    i = 0;
                    while ((c = fgetc(F)) != '\"')
                        mb->name[i++] = c;
                    mb->name[i] = '\0';
                }
            }
        } else if (strcmp(elem, "orientation") == 0) {
            if ((c = epurer_blan(F)) == '=') {
                    gchar temp[4];
                if ((c = epurer_blan(F)) == '\"')
                {
                     i = 0;
                    while ((c = fgetc(F)) != '\"')
                        temp[i++] = c;
                    temp[i] = '\0';
                    mb->orientation=string_to_pack_direction(temp);
                }
            }

        } else if (strcmp(elem, "posx") == 0)
        {
            if ((c = epurer_blan(F)) == '=')
                fscanf(F, "%d", &mb->posx);

        }
        else if (strcmp(elem, "posy") == 0)
        {
            if ((c = epurer_blan(F)) == '=')
                fscanf(F, "%d", &mb->posy);

        }
    }while(strcmp(elem,">"));
    return mb;
}
// Fonction pour créer une barre de menus
menubar *add_menubar(menubar* mb,FILE *F)
{
    mb=init_menubar();
    mb=menubarFunction(mb,F);
    // Création de la barre de menus GTK
    mb->menubar = gtk_menu_bar_new();
    // Définition de l'orientation de la barre de menus
    gtk_menu_bar_set_pack_direction(GTK_MENU_BAR(mb->menubar), mb->orientation);
    // Retour de la structure menubar
    return mb;
}

//Fonction pour initialiser un élément de menu
menu* init_menu_item()
{
    // Allocation de la mémoire pour la structure menu
    menu *NM = malloc(sizeof(menu));
    if (!NM) {
        // Gestion de l'erreur d'allocation mémoire
        g_critical("Echec d'allocation mémoire pour l'élément de menu");
        exit(-1);
    }
    NM->menu_item=(GtkWidget*)g_malloc(sizeof(GtkWidget));
    NM->MENU=(GtkWidget*)g_malloc(sizeof(GtkWidget));
    // Allocation de la mémoire pour le nom de l'élément
    NM->nom=(gchar*)g_malloc(sizeof(gchar)*30);
    NM->nom[0] ='\0';
    // Initialisation des attributs de la structure
    NM->IsSubmenu = FALSE;
    NM->IsradioGroup= FALSE;
    NM->type_composant = DEFAULT_MENU;
    NM->liste = NULL;
    NM->suivant=NULL;

    // Retour de la structure menu
    return NM;
}

menu* menuItemFunction(menu*me, FILE*F)
{
    gchar* elem;
    int i;
    elem=(gchar*)g_malloc(sizeof(gchar)*30);
    gchar c;
    c=epurer_blan(F);
    if(c=='<')
    {
        fscanf(F,"%s",elem);
        if(strcmp(elem, "menu_item/>") == 0)
           return (menu*)NULL;

        do
        {

         if (strcmp(elem, "name") == 0)
         {
            if ((c = epurer_blan(F)) == '=')
                if ((c = epurer_blan(F)) == '\"')
                {
                    i = 0;
                    while ((c = fgetc(F)) != '\"')
                        me->nom[i++] = c;
                    me->nom[i] = '\0';
                }
         }else if (strcmp(elem, "IsradioGroup") == 0)
        {
                if ((c = epurer_blan(F)) == '=')
                  {
                    if((c = epurer_blan(F)) == 'T')
                        me->IsradioGroup=TRUE;
                    else me->IsradioGroup=FALSE;
                  }
        }else if (strcmp(elem, "IsSubmenu") == 0)
        {
                if ((c = epurer_blan(F)) == '=')
                {
                    if((c = epurer_blan(F)) == 'T')
                      me->IsSubmenu=TRUE;
                    else me->IsSubmenu=FALSE;

                }
        }else if (strcmp(elem, "type") == 0)
            if ((c = epurer_blan(F)) == '=')
                fscanf(F, "%d", &me->type_composant);

        fscanf(F,"%s",elem);
      }while(strcmp(elem,">"));
    }
    return me;
}


//Foction pour trouver l'element du groupe radio
menu* RadioGroup(menu* M)
{
  menu *courant;
  for (courant = M; courant; courant = courant->suivant)
     if(courant->IsradioGroup)
        return courant;

 return NULL;
}
// Fonction pour ajouter un élément de menu à un menu parent
menu* creer_menu_item(menu *parent_menu, menu *menu_elem)
{
    // Vérifie si le menu parent a déjà un élément
    if (!parent_menu->liste)
        // Le menu parent est vide, ajouter l'élément comme premier élément
        parent_menu->liste = menu_elem;
    else {
        // Le menu parent n'est pas vide, ajouter l'élément à la fin de la liste
        menu *courant;
        for (courant = parent_menu->liste; courant->suivant; courant = courant->suivant);
        // La boucle trouve le dernier élément de la liste
        courant->suivant = menu_elem;
        menu_elem->suivant = NULL; // Marque la fin de la liste
    }

    // Si l'élément n'est pas un sous-menu, créer le widget approprié en fonction du type
    if (!menu_elem->IsSubmenu) {
        switch (menu_elem->type_composant) {
            case 1:
                // Créer une case à cocher
                printf("\n nom du menu eleme : %s",menu_elem->nom);
                menu_elem->menu_item = gtk_check_menu_item_new_with_mnemonic(menu_elem->nom);
                break;
            case 2:
                // Créer un séparateur
                menu_elem->menu_item = gtk_separator_menu_item_new();
                break;
            case 3:
                // Créer un bouton radio
                menu* Rgroup = RadioGroup(parent_menu->liste);//trouver l'element de groupe radio
                if ((!parent_menu->liste) ||(!Rgroup))//Si on a pas encore creer le premier button radio qui sera le greoupe
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

  return menu_elem;
}

// Fonction pour ajouter un sous element d'un menu
menu *add_menu_item(menu *parent,menu* newItem, FILE *F) {
    // Initialisation de l'élément de menu
    newItem = init_menu_item();
    newItem=menuItemFunction(newItem,F);
    if(newItem)
      newItem=creer_menu_item(parent, newItem);
    else return NULL;

    return newItem;
}

void ajouter_subelem(menu *parent,FILE* F)
{
   menu* ne=NULL;
    while((ne=add_menu_item(parent,ne,F))!=NULL)
    {
         if(ne->IsSubmenu==TRUE)
            ajouter_subelem(ne,F);
    }

}

menu* menuFunction(menu*mi, FILE*F)
{
    gchar* elem;
    int i;
    elem=(gchar*)g_malloc(sizeof(gchar)*30);
    gchar c;
    c=epurer_blan(F);
    if(c=='<')
    {
        fscanf(F,"%s",elem);
        if(strcmp(elem, "menu_bar/>") == 0)
            return (menu*)NULL;
        do
        {

         if (strcmp(elem, "name") == 0)
         {
            if ((c = epurer_blan(F)) == '=')
                if ((c = epurer_blan(F)) == '\"')
                {
                    i = 0;
                    while ((c = fgetc(F)) != '\"')
                        mi->nom[i++] = c;
                    mi->nom[i] = '\0';
                }
        }

        fscanf(F,"%s",elem);
      }while(strcmp(elem,">"));
    }
    return mi;
}

// Fonction pour ajouter un menu à la barre de menus
menu* add_menu(menubar* M, menu *child ,FILE *F)
{
    child=init_menu_item();
    child=menuFunction(child,F);
    if(child)
    {
      if (!M->liste)
        M->liste = child;
     else {
        // Insertion à la fin de la liste
        menu *courant;
        for (courant = M->liste; courant->suivant; courant = courant->suivant);
        courant->suivant = child;
        child->suivant = NULL;
      }

    // Créer le widget de l'élément de menu
    child->menu_item = gtk_menu_item_new_with_label(child->nom);
    child->MENU = gtk_menu_new();
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(child->menu_item), child->MENU);

    // Ajouter l'élément de menu à la barre de menus
    gtk_menu_shell_append(GTK_MENU_SHELL(M->menubar), child->menu_item);

    return child;
   }
    return NULL;
}

void ajouter_elems(menubar *parent ,FILE *F)
{
    menu* ne=NULL;
    while((ne=add_menu(parent,ne,F))!=NULL)
       ajouter_subelem(ne,F);

}



#endif // MENU_H_INCLUDED
