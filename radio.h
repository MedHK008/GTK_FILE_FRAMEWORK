#ifndef RADIO_H_INCLUDED
#define RADIO_H_INCLUDED

typedef struct elem_radio {
    GtkWidget *pRadio; // le widget radio
    gchar* name;
    gchar label[NBC]; // label du bouton
    gchar *hexcolor; // couleur de fond en hexadécimal
    gboolean checked; // indique si le bouton est coché au début ou non
    struct elem_radio *suivant; // le bouton radio qui vient après le courant
} elem_radio;

typedef struct radio {
    GtkWidget *fixed; // Conteneur de type Fixed
    GtkWidget *parent; // le widget parent
    GtkWidget *pRadio; // L'objet bouton radio
    elem_radio *liste; // Les éléments de la Liste radio
} radio;

elem_radio* ajouter_radio_fin(elem_radio *L, gchar label[NBC], gchar *bgcolor, gboolean checked,gchar* name) {
    elem_radio *elem = (elem_radio*)malloc(sizeof(elem_radio));
    if (elem == NULL) {
        perror("Erreur lors de l'allocation de mémoire");
        exit(EXIT_FAILURE);
    }
    elem->name = name;
    elem->suivant = NULL;
    strcpy(elem->label, label);
    elem->hexcolor = strdup(bgcolor); // Allocation et copie de la couleur
    elem->checked = checked; // Initialisation du statut du bouton radio
    if (!L) return elem;
    elem_radio *t = L;
    while (L->suivant) L = L->suivant;
    L->suivant = elem;
    return t;
}

radio* grouper_radio(elem_radio *L, GtkWidget *parent) {
    radio *radioButtons = (radio*)malloc(sizeof(radio));
    if (radioButtons == NULL) {
        perror("Erreur lors de l'allocation de mémoire");
        exit(EXIT_FAILURE);
    }
    radioButtons->fixed = gtk_fixed_new(); // Création du conteneur Fixed
    radioButtons->liste = L;
    radioButtons->parent = parent;
    return radioButtons;
}

void create_radio(radio *R, gint x, gint y) {
    GtkWidget *first_radio = NULL; // Pour conserver une référence au premier bouton radio
    while (R->liste) {
        R->liste->pRadio = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(first_radio), R->liste->label);
        if (R->liste->name)gtk_widget_set_name(R->liste->pRadio,R->liste->name);
        if (R->liste->hexcolor) {
            GdkRGBA color;
            gdk_rgba_parse(&color, R->liste->hexcolor);
            gtk_widget_override_background_color(R->liste->pRadio, GTK_STATE_FLAG_NORMAL, &color);
        }
        if (R->liste->checked) {
            gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(R->liste->pRadio), TRUE); // Cocher le bouton si nécessaire
        }
        if (!first_radio) // Si c'est le premier bouton radio, sauvegardez sa référence
            first_radio = R->liste->pRadio;
        gtk_fixed_put(GTK_FIXED(R->fixed), R->liste->pRadio, x, y); // Positionnement des boutons dans le Fixed
        y+=25;
        R->liste = R->liste->suivant;
    }
}


GtkWidget* add_radio(int numButtons, gint x, gint y, char *labels[], char *colors[], gboolean checked[],gchar* name[]) {
    elem_radio *liste_radio = NULL;
    for (int i = 0; i < numButtons; i++) {
        liste_radio = ajouter_radio_fin(liste_radio, labels[i], colors[i], checked[i],name[i]);
    }
    radio *grouped_radio = grouper_radio(liste_radio, NULL);
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    GtkWidget *first_radio = NULL;
    while (grouped_radio->liste) {
        grouped_radio->liste->pRadio = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(first_radio), grouped_radio->liste->label);
        if (grouped_radio->liste->hexcolor) {
            GdkRGBA color;
            gdk_rgba_parse(&color, grouped_radio->liste->hexcolor);
            gtk_widget_override_background_color(grouped_radio->liste->pRadio, GTK_STATE_FLAG_NORMAL, &color);
        }
        if (grouped_radio->liste->checked) {
            gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(grouped_radio->liste->pRadio), TRUE);
        }
        if (!first_radio)
            first_radio = grouped_radio->liste->pRadio;
        gtk_box_pack_start(GTK_BOX(box), grouped_radio->liste->pRadio, FALSE, FALSE, 0);
        grouped_radio->liste = grouped_radio->liste->suivant;
    }

    return box;
}




#endif // RADIO_H_INCLUDED
