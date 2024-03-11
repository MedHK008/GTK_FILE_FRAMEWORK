#ifndef RADIO_H_INCLUDED
#define RADIO_H_INCLUDED

typedef struct elem_radio {
    GtkWidget *pRadio; // le widget radio
    char nom[NBC]; // nom du bouton
    struct elem_radio *suivant; // le bouton radio qui vient après le courant
} elem_radio;

typedef struct radio {
    GtkWidget *fixed; // Conteneur de type Fixed
    GtkWidget *parent; // le widget parent
    GtkWidget *pRadio; // L'objet bouton radio
    elem_radio *liste; // Les éléments de la Liste radio
} radio;

elem_radio* ajouter_radio_fin(elem_radio *L, char label[NBC]) {
    elem_radio *elem = (elem_radio*)malloc(sizeof(elem_radio));
    if (elem == NULL) {
        perror("Erreur lors de l'allocation de mémoire");
        exit(EXIT_FAILURE);
    }
    elem->suivant = NULL;
    strcpy(elem->nom, label);
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

void create_radio(radio *R) {
    GtkWidget *first_radio = NULL; // Pour conserver une référence au premier bouton radio
    gint i=20;
    while (R->liste) {
        R->liste->pRadio = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(first_radio), R->liste->nom);
        if (!first_radio) // Si c'est le premier bouton radio, sauvegardez sa référence
            first_radio = R->liste->pRadio;
        gtk_fixed_put(GTK_FIXED(R->fixed), R->liste->pRadio, 350, i); // Positionnement des boutons dans le Fixed
        i+=20;
        R->liste = R->liste->suivant;
    }
}

#endif // RADIO_H_INCLUDED
