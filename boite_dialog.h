#ifndef BOITE_DIALOG_H_INCLUDED
#define BOITE_DIALOG_H_INCLUDED


// Structure repr�sentant une bo�te de dialogue
typedef struct {
    GtkWidget *dialogue;        // Le widget de la bo�te de dialogue GTK
    GtkWidget *zone_contenu;    // Le widget de la zone de contenu de la bo�te de dialogue
    GtkWindow *parent;
    gchar *name;          // La fen�tre parente de la bo�te de dialogue
    gchar *titre;               // Le titre de la bo�te de dialogue
    gchar *icone;               // Le chemin vers l'ic�ne de la bo�te de dialogue
    gint modal;                 // Indique si la bo�te de dialogue est modale (TRUE) ou non modale (FALSE)
    gint hauteur;               // La hauteur de la bo�te de dialogue
    gint largeur;               // La largeur de la bo�te de dialogue
    gint position;              // La position de la bo�te de dialogue sur l'�cran (par exemple, GTK_WIN_POS_CENTER)
    gint etat;                  // L'�tat de la bo�te de dialogue (0: normal, 1: actif, 2: pr�-s�lectionn�, 3: s�lectionn�, 4: insensible)
    gchar *couleur_fond;        // La couleur de fond de la bo�te de dialogue
} BoiteDialogue;
BoiteDialogue* init_boite_dialogue()
{
     BoiteDialogue *BD = (BoiteDialogue *)g_malloc(sizeof(BoiteDialogue));
     BD->couleur_fond=NULL;
     BD->dialogue=NULL;
     BD->name=NULL;
     BD->etat=0;
     BD->hauteur=0;
     BD->icone=NULL;
     BD->largeur=0;
     BD->modal=0;
     BD->parent=NULL;
     BD->position=0;
     BD->titre=NULL;
     BD->zone_contenu=NULL;
     return BD;
}
BoiteDialogue* boiteDialogueFunction(BoiteDialogue*BD,FILE* F)
{
    gchar* elem;
    elem=(gchar*)g_malloc(sizeof(gchar)*50);
    gchar c;
    do
    {

        c=epurer_blan(F);
        ungetc(c,F);
        fscanf(F,"%s",elem);
        printf("%s\n",elem);

       if (strcmp(elem, "name") == 0)
        {
            if ((c = epurer_blan(F)) == '=') {
                if ((c = epurer_blan(F)) == '\"') {
                    int i = 0;
                    BD->name=(gchar*)g_malloc(sizeof(gchar)*30);
                    while ((c = fgetc(F)) != '\"') BD->name[i++] = c;
                    BD->name[i] = '\0';
                }

            }
        }
        else if (strcmp(elem, "title") == 0)
            {
            if ((c = epurer_blan(F)) == '=') {
                if ((c = epurer_blan(F)) == '\"') {
                    int i = 0;
                    BD->titre=(gchar*)g_malloc(sizeof(gchar)*50);
                    while ((c = fgetc(F)) != '\"')
                        BD->titre[i++] = c;
                    BD->titre[i] = '\0';
                }
            }
        }
       else if (strcmp(elem, "bgColor") == 0)
        {
            if ((c = epurer_blan(F)) == '=') {
                if ((c = epurer_blan(F)) == '\"') {
                    int i = 0;
                    BD->couleur_fond=(gchar*)g_malloc(sizeof(gchar)*30);
                    while ((c = fgetc(F)) != '\"')
                        BD->couleur_fond[i++] = c;
                    BD->couleur_fond[i] = '\0';
                }
            }

        }
       else if (strcmp(elem, "width") == 0) {
            if ((c = epurer_blan(F)) == '=') {
                fscanf(F, "%d", &BD->largeur);
            }

        } else if (strcmp(elem, "height") == 0) {
            if ((c = epurer_blan(F)) == '=') {
                fscanf(F, "%d", &BD->hauteur);
            }

        }

         else if (strcmp(elem, "color_state") == 0) {
            if ((c = epurer_blan(F)) == '=') {
                fscanf(F, "%d", &BD->etat);
            }

         }


         else if (strcmp(elem, "icone") == 0)
        {
            if ((c = epurer_blan(F)) == '=') {
                if ((c = epurer_blan(F)) == '\"') {
                    int i = 0;
                    BD->icone=(gchar*)g_malloc(sizeof(gchar)*30);
                    while ((c = fgetc(F)) != '\"')
                        BD->icone[i++] = c;
                    BD->icone[i] = '\0';
                }
            }

        }
          else if (strcmp(elem, "modal") == 0) {
            if ((c = epurer_blan(F)) == '=') {
                fscanf(F, "%d", &BD->modal);
            }

         }




    }while(strcmp(elem,">"));
    return (BoiteDialogue*)(BD);
}
// Fonction pour d�finir les attributs visuels de la bo�te de dialogue
void definir_attributs_boite_dialogue(BoiteDialogue *BD) {
    GdkRGBA couleur; // D�claration d'une structure de couleur GTK
    BD->dialogue = gtk_dialog_new(); // Cr�er une nouvelle bo�te de dialogue GTK
    if(BD->titre) gtk_window_set_title(GTK_WINDOW(BD->dialogue), BD->titre); // D�finir le titre de la bo�te de dialogue
    if(BD->icone)gtk_window_set_icon_from_file(GTK_WINDOW(BD->dialogue), BD->icone, NULL); // D�finir l'ic�ne de la bo�te de dialogue � partir d'un fichier
    GtkWidget*content = gtk_dialog_get_content_area(GTK_DIALOG(BD->dialogue));
    BD->zone_contenu=gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(content),BD->zone_contenu);
    // Obtenir la zone de contenu de la bo�te de dialogue
    if(BD->largeur>0 && BD->hauteur>0) gtk_widget_set_size_request(BD->dialogue, BD->largeur, BD->hauteur); // D�finir la taille de la bo�te de dialogue
    gtk_window_set_transient_for(GTK_WINDOW(BD->dialogue), GTK_WINDOW(BD->parent)); // D�finir la fen�tre parente de la bo�te de dialogue

    if (BD->modal == 1) // V�rifier si la bo�te de dialogue est modale

        {gtk_window_set_modal(GTK_WINDOW(BD->dialogue), TRUE);
        gtk_window_set_transient_for(GTK_WINDOW(BD->dialogue),GTK_WINDOW(BD->parent));// D�finir la bo�te de dialogue comme modale
        }
    gdk_rgba_parse(&couleur, BD->couleur_fond); // Convertir la couleur de fond en format GTK

    // Appliquer la couleur de fond en fonction de l'�tat de la bo�te de dialogue
    switch (BD->etat) {
    case 0: // �tat normal
        gtk_widget_override_background_color(BD->dialogue, GTK_STATE_FLAG_NORMAL, &couleur);
        break;
    case 1: // �tat actif
        gtk_widget_override_background_color(BD->dialogue, GTK_STATE_FLAG_ACTIVE, &couleur);
        break;
    case 2: // �tat de surbrillance
        gtk_widget_override_background_color(BD->dialogue, GTK_STATE_FLAG_PRELIGHT, &couleur);
        break;
    case 3: // �tat s�lectionn�
        gtk_widget_override_background_color(BD->dialogue, GTK_STATE_FLAG_SELECTED, &couleur);
        break;
    case 4: // �tat insensible
        gtk_widget_override_background_color(BD->dialogue, GTK_STATE_FLAG_INSENSITIVE, &couleur);
        break;
    }
}
BoiteDialogue* Add_boite_dialogue(FILE *F)
{
    BoiteDialogue*bd=init_boite_dialogue();
    bd=boiteDialogueFunction(bd,F);
    definir_attributs_boite_dialogue(bd);
    return (BoiteDialogue*)(bd);

}
// Fonction pour ajouter un bouton � une bo�te de dialogue
void ajouter_a_boite_dialogue(BoiteDialogue*dialogue,GtkWidget*element , gint x , gint y) {
    if (dialogue && element) // V�rifier si le libell� du bouton et la bo�te de dialogue sont d�finis
        gtk_fixed_put(GTK_FIXED(dialogue->zone_contenu),element,x,y);
 }

// Fonction pour ajouter une action � une bo�te de dialogue
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
    if (widget && dialogue) // V�rifier si le widget et la bo�te de dialogue sont d�finis
        gtk_dialog_add_action_widget(dialogue->dialogue, widget, reponse); // Ajouter une action associ�e au widget � la bo�te de dialogue
}
void on_button_clicked(GtkWidget *widget, gpointer data) {
    gtk_widget_show_all(GTK_WIDGET(data));
}


#endif // BOITE_DIALOG_H_INCLUDED
