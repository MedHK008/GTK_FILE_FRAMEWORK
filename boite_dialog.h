#ifndef BOITE_DIALOG_H_INCLUDED
#define BOITE_DIALOG_H_INCLUDED

// Structure représentant une boîte de dialogue
typedef struct {
    GtkWidget *dialogue;        // Le widget de la boîte de dialogue GTK
    GtkWidget *zone_contenu;    // Le widget de la zone de contenu de la boîte de dialogue
    GtkWindow *parent;          // La fenêtre parente de la boîte de dialogue
    gchar *titre;               // Le titre de la boîte de dialogue
    gchar *icone;               // Le chemin vers l'icône de la boîte de dialogue
    gint modal;                 // Indique si la boîte de dialogue est modale (TRUE) ou non modale (FALSE)
    gint hauteur;               // La hauteur de la boîte de dialogue
    gint largeur;               // La largeur de la boîte de dialogue
    gint position;              // La position de la boîte de dialogue sur l'écran (par exemple, GTK_WIN_POS_CENTER)
    gint etat;                  // L'état de la boîte de dialogue (0: normal, 1: actif, 2: pré-sélectionné, 3: sélectionné, 4: insensible)
    gchar *couleur_fond;        // La couleur de fond de la boîte de dialogue
} BoiteDialogue;

// Fonction pour créer et initialiser une structure BoiteDialogue
BoiteDialogue *creer_initialiser_boite_dialogue(GtkWindow *parent, gchar *titre, gchar *icone, guint modal, gint hauteur, gint largeur, gint etat, gchar *couleur_fond) {
    // Allouer de la mémoire pour la structure BoiteDialogue
    BoiteDialogue *BD = (BoiteDialogue *)g_malloc(sizeof(BoiteDialogue));
    BD->zone_contenu = NULL; // Initialiser le pointeur de la zone de contenu à NULL
    BD->dialogue = NULL; // Initialiser le pointeur du dialogue à NULL
    BD->icone = NULL; // Initialiser le pointeur de l'icône à NULL
    BD->titre = NULL; // Initialiser le pointeur du titre à NULL

    if (!BD) { // Vérifier si l'allocation de mémoire a échoué
        printf("\nERREUR\n"); // Afficher un message d'erreur
        exit(-1); // Quitter le programme avec un code d'erreur
    }

    if (titre) { // Vérifier si le titre est défini
        BD->titre = g_strdup(titre); // Dupliquer la chaîne de caractères du titre
        if (!BD->titre) { // Vérifier si la duplication a échoué
            printf("\nERREUR\n"); // Afficher un message d'erreur
            exit(-1); // Quitter le programme avec un code d'erreur
        }
    }

    if (icone) { // Vérifier si l'icône est définie
        BD->icone = g_strdup(icone); // Dupliquer la chaîne de caractères de l'icône
        if (!BD->icone) { // Vérifier si la duplication a échoué
            printf("\nErreur\n"); // Afficher un message d'erreur
            exit(-1); // Quitter le programme avec un code d'erreur
        }
    }

    if (couleur_fond) { // Vérifier si la couleur de fond est définie
        BD->couleur_fond = g_strdup(couleur_fond); // Dupliquer la chaîne de caractères de la couleur de fond
        if (!BD->couleur_fond) { // Vérifier si la duplication a échoué
            printf("\nERREUR\n"); // Afficher un message d'erreur
            exit(-1); // Quitter le programme avec un code d'erreur
        }
    }

    BD->parent = parent; // Affecter la fenêtre parente
    BD->modal = modal; // Indiquer si la boîte de dialogue est modale
    BD->hauteur = hauteur; // Définir la hauteur de la boîte de dialogue
    BD->largeur = largeur; // Définir la largeur de la boîte de dialogue

    return BD; // Retourner la structure BoiteDialogue initialisée
}

// Fonction pour définir les attributs visuels de la boîte de dialogue
void definir_attributs_boite_dialogue(BoiteDialogue *BD) {
    GdkRGBA couleur; // Déclaration d'une structure de couleur GTK
    BD->dialogue = gtk_dialog_new(); // Créer une nouvelle boîte de dialogue GTK
    gtk_window_set_title(GTK_WINDOW(BD->dialogue), BD->titre); // Définir le titre de la boîte de dialogue
    gtk_window_set_icon_from_file(GTK_WINDOW(BD->dialogue), BD->icone, NULL); // Définir l'icône de la boîte de dialogue à partir d'un fichier
    BD->zone_contenu = gtk_fixed_new(); // Obtenir la zone de contenu de la boîte de dialogue
    gtk_widget_set_size_request(BD->dialogue, BD->largeur, BD->hauteur); // Définir la taille de la boîte de dialogue
    gtk_window_set_transient_for(GTK_WINDOW(BD->dialogue), GTK_WINDOW(BD->parent)); // Définir la fenêtre parente de la boîte de dialogue

    if (BD->modal == 1) // Vérifier si la boîte de dialogue est modale
        gtk_window_set_modal(GTK_WINDOW(BD->dialogue), TRUE); // Définir la boîte de dialogue comme modale

    gdk_rgba_parse(&couleur, BD->couleur_fond); // Convertir la couleur de fond en format GTK

    // Appliquer la couleur de fond en fonction de l'état de la boîte de dialogue
    switch (BD->etat) {
    case 0: // État normal
        gtk_widget_override_background_color(BD->dialogue, GTK_STATE_FLAG_NORMAL, &couleur);
        break;
    case 1: // État actif
        gtk_widget_override_background_color(BD->dialogue, GTK_STATE_FLAG_ACTIVE, &couleur);
        break;
    case 2: // État de surbrillance
        gtk_widget_override_background_color(BD->dialogue, GTK_STATE_FLAG_PRELIGHT, &couleur);
        break;
    case 3: // État sélectionné
        gtk_widget_override_background_color(BD->dialogue, GTK_STATE_FLAG_SELECTED, &couleur);
        break;
    case 4: // État insensible
        gtk_widget_override_background_color(BD->dialogue, GTK_STATE_FLAG_INSENSITIVE, &couleur);
        break;
    }
}
BoiteDialogue* Add_boite_dialogue(GtkWindow *parent, gchar *titre, gchar *icone, guint modal, gint hauteur, gint largeur, gint etat, gchar *couleur_fond)
{
    BoiteDialogue*bd=creer_initialiser_boite_dialogue(parent,titre,icone,modal,hauteur,largeur,etat,couleur_fond);
    definir_attributs_boite_dialogue(bd);
    return (BoiteDialogue*)(bd);

}
// Fonction pour ajouter un bouton à une boîte de dialogue
void ajouter_a_boite_dialogue(BoiteDialogue*dialogue,GtkWidget*element , gint x , gint y) {
    if (dialogue && element) // Vérifier si le libellé du bouton et la boîte de dialogue sont définis
        gtk_fixed_put(dialogue->zone_contenu,element,x,y); // Ajouter un bouton avec le libellé spécifié et la réponse associée à la boîte de dialogue
}

// Fonction pour ajouter une action à une boîte de dialogue
//GTK_RESPONSE_NONE : -1
//GTK_RESPONSE_REJECT : -2
//GTK_RESPONSE_ACCEPT : -3
//GTK_RESPONSE_DELETE_EVENT : -4
//GTK_RESPONSE_OK : -5
//GTK_RESPONSE_CANCEL : -6
//GTK_RESPONSE_CLOSE : -7
//GTK_RESPONSE_YES : -8
//GTK_RESPONSE_NO : -9
//GTK_RESPONSE_APPLY : -10
//GTK_RESPONSE_HELP : -11
void ajouter_action_a_boite_dialogue(BoiteDialogue *dialogue, GtkWidget *widget, gint reponse) {
    if (widget && dialogue) // Vérifier si le widget et la boîte de dialogue sont définis
        gtk_dialog_add_action_widget(dialogue->dialogue, widget, reponse); // Ajouter une action associée au widget à la boîte de dialogue
}




#endif // BOITE_DIALOG_H_INCLUDED
