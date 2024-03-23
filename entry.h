#ifndef ENTRY_H_INCLUDED
#define ENTRY_H_INCLUDED


// Structure repr�sentant une zone de saisie
typedef struct {
    GtkWidget *entree;          // Le widget de la zone de saisie GTK
    gchar *placeholder;         // Le texte de substitution affich� lorsqu'il n'y a pas de texte
    gchar *nom;                 // Le nom du widget
    gint longueur_max;          // Le nombre maximal de caract�res pouvant �tre saisis
    gfloat alignement_x;        // L'alignement horizontal du texte (0 pour � gauche, 1 pour � droite)
    gint visible;               // Indique si le texte saisi est visible (TRUE) ou cach� (FALSE)
    gint caractere_visible;     // Indique si un caract�re sp�cifique est utilis� pour masquer le texte saisi
    guchar caractere;           // Le caract�re utilis� pour masquer le texte saisi (si caractere_visible est TRUE)
    gint hauteur;               // La hauteur de la zone de saisie
    gint largeur;               // La largeur de la zone de saisie
    gint etat;                  // L'�tat de la zone de saisie (0: normal, 1: actif, 2: pr�-s�lectionn�, 3: s�lectionn�, 4: insensible)
    gchar *couleur_fond;        // La couleur de fond de la zone de saisie
} Saisie;


// Fonction pour cr�er et initialiser une structure Saisie
Saisie *creer_initialiser_saisie(gchar *placeholder, gint longueur_max, gfloat alignement_x, gint visible, gint caractere_visible, guchar carac_vis, gint w, gint h, gint etat, gchar *couleur_fond) {
    // Allouer de la m�moire pour la structure Saisie
    Saisie *saisie = (Saisie *)g_malloc(sizeof(Saisie));
    if (!saisie) { // V�rifier si l'allocation de m�moire a r�ussi
        printf("\Erreur\n"); // Afficher un message d'erreur
        exit(0); // Quitter le programme avec un code d'erreur
    }
    if (placeholder) { // V�rifier si le param�tre placeholder est d�fini
        saisie->placeholder = g_strdup(placeholder); // Dupliquer la cha�ne placeholder
        if (!saisie->placeholder) { // V�rifier si la duplication a r�ussi
            printf("\nErreur\n"); // Afficher un message d'erreur
            exit(0); // Quitter le programme avec un code d'erreur
        }
    }
    if (couleur_fond) { // V�rifier si le param�tre couleur_fond est d�fini
        saisie->couleur_fond = g_strdup(couleur_fond); // Dupliquer la couleur de fond
        if (!saisie->couleur_fond) { // V�rifier si la duplication a r�ussi
            printf("\nERREUR\n"); // Afficher un message d'erreur
            exit(0); // Quitter le programme avec un code d'erreur
        }
    }

    // Initialiser les autres attributs de la structure Saisie
    saisie->hauteur = h; // Hauteur de la zone de saisie
    saisie->largeur = w; // Largeur de la zone de saisie
    saisie->alignement_x = alignement_x; // Alignement horizontal de la zone de saisie
    saisie->visible = visible; // Visibilit� de la zone de saisie
    saisie->caractere_visible = caractere_visible; // Visibilit� des caract�res saisis
    saisie->caractere = carac_vis; // Caract�re utilis� pour masquer les saisies
    saisie->longueur_max = longueur_max; // Longueur maximale de la saisie
    return saisie; // Retourner la structure Saisie initialis�e
}

// Fonction pour d�finir les attributs visuels de la zone de saisie
void definir_attributs_saisie(Saisie *e) {
    GdkRGBA couleur; // D�claration d'une structure de couleur GTK
    e->entree = gtk_entry_new(); // Cr�er une nouvelle zone de saisie GTK
    gdk_rgba_parse(&couleur, e->couleur_fond); // Convertir la couleur de fond en format GTK

    // D�finir le texte de substitution de la zone de saisie
    gtk_entry_set_placeholder_text(GTK_ENTRY(e->entree), e->placeholder);
    // D�finir la longueur maximale de la saisie
    gtk_entry_set_max_length(GTK_ENTRY(e->entree), e->longueur_max);
    // D�finir l'alignement horizontal de la zone de saisie
    gtk_entry_set_alignment(GTK_ENTRY(e->entree), e->alignement_x);

    // Masquer ou afficher le texte saisi en fonction de la visibilit�
    if (!e->visible) {
        gtk_entry_set_visibility(GTK_ENTRY(e->entree), FALSE);
    }

    // D�finir le caract�re utilis� pour masquer les saisies si n�cessaire
    if (e->caractere_visible == 1) {
        gtk_entry_set_invisible_char(GTK_ENTRY(e->entree), e->caractere);
    }

    // D�finir la taille de la zone de saisie si des valeurs positives sont sp�cifi�es
    if (e->largeur > 0 && e->hauteur > 0) {
        gtk_widget_set_size_request(e->entree, e->largeur, e->hauteur);
    }

    // Appliquer la couleur de fond en fonction de l'�tat de la zone de saisie
    switch (e->etat) {
    case 0: // �tat normal
        gtk_widget_override_background_color(e->entree, GTK_STATE_FLAG_NORMAL, &couleur);
        break;
    case 1: // �tat actif
        gtk_widget_override_background_color(e->entree, GTK_STATE_FLAG_ACTIVE, &couleur);
        break;
    case 2: // �tat de surbrillance
        gtk_widget_override_background_color(e->entree, GTK_STATE_FLAG_PRELIGHT, &couleur);
        break;
    case 3: // �tat s�lectionn�
        gtk_widget_override_background_color(e->entree, GTK_STATE_FLAG_SELECTED, &couleur);
        break;
    case 4: // �tat insensible
        gtk_widget_override_background_color(e->entree, GTK_STATE_FLAG_INSENSITIVE, &couleur);
        break;
    }
}

Enty *Add_Entry(GtkWidget*fixed,gchar *placeholder, gint longueur_max, gfloat alignement_x, gint visible, gint caractere_visible, guchar carac_vis, gint w, gint h, gint etat, gchar *couleur_fond,gint x ,gint y)
{
    Saisie *E=creer_initialiser_saisie(placeholder,longueur_max,alignement_x,visible,caractere_visible,carac_vis,w,h,etat,couleur_fond);
    definir_attributs_saisie(E);
    gtk_fixed_put(fixed,E->entree,x,y);
}


#endif // ENTRY_H_INCLUDED
