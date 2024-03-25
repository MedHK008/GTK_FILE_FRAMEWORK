#ifndef RADIO_H_INCLUDED
#define RADIO_H_INCLUDED
#include "fixed.h"
typedef struct elem_radio {
    GtkWidget *pRadio; // le widget radio
    gchar* name;
    gchar* label; // label du bouton
    gchar* hexcolor; // couleur de fond en hexadécimal
    gboolean checked; // indique si le bouton est coché au début ou non
    gint x_pos;
    gint y_pos;
    struct elem_radio* suivant; // le bouton radio qui vient après le courant
} elem_radio;

typedef struct radio {
    elem_radio *liste; // Les éléments de la Liste radio
} radio;



elem_radio* init_elem_radio()
{
    elem_radio* R=(elem_radio*)g_malloc(sizeof(elem_radio));
    R->name=(gchar*)g_malloc(sizeof(gchar)*NBC);
    R->label=(gchar*)g_malloc(sizeof(gchar)*NBC);
    R->hexcolor=(gchar*)g_malloc(sizeof(gchar)*NBC);
    R->checked=FALSE;
    R->x_pos=0;
    R->y_pos=0;
    R->suivant=NULL;
    return((elem_radio*)R);
}

elem_radio* elemRadioFunction(elem_radio* R,FILE* F)
{
    gchar* elem;
    elem=(gchar*)g_malloc(sizeof(gchar)*NBC);
    gchar c;
    int check;
    if((c = epurer_blan(F)) == '<')
    {
        fscanf(F,"%s",elem);
        if (strcmp("/radio>",elem)==0) return ((elem_radio*)NULL);
        do
        {
            fscanf(F,"%s",elem);
            printf("%s  ",elem);
            if (strcmp(elem, "name") == 0) {
                if ((c = epurer_blan(F)) == '=') {
                    if ((c = epurer_blan(F)) == '\"') {
                        int i = 0;
                        while ((c = fgetc(F)) != '\"')
                            R->name[i++] = c;
                        R->name[i] = '\0';
                    }
                }
            } else if (strcmp(elem, "label") == 0) {
                if ((c = epurer_blan(F)) == '=') {
                    if ((c = epurer_blan(F)) == '\"') {
                        int i = 0;
                        while ((c = fgetc(F)) != '\"')
                            R->label[i++] = c;
                        R->label[i] = '\0';
                    }
                }
            } else if (strcmp(elem, "hexcolor") == 0) {
                if ((c = epurer_blan(F)) == '=') {
                    if ((c = epurer_blan(F)) == '\"') {
                        int i = 0;
                        while ((c = fgetc(F)) != '\"')
                            R->hexcolor[i++] = c;
                        R->hexcolor[i] = '\0';
                    }
                }
            } else if (strcmp(elem, "posx") == 0) {
                if ((c = epurer_blan(F)) == '=') {
                    fscanf(F, "%d", &R->x_pos);
                }
            }else if (strcmp(elem, "posy") == 0) {
                if ((c = epurer_blan(F)) == '=') {
                    fscanf(F, "%d", &R->y_pos);
                }
            }else if (strcmp(elem, "checked") == 0)
            {
                if ((c = epurer_blan(F)) == '=') {
                    fscanf(F,"%d",&check);
                    if(check == 1)
                        R->checked = TRUE;
                    else
                        R->checked = FALSE;
                }
            }
        }while(strcmp(elem,">"));
    }
    return R;
}

elem_radio* ajouter_radio_fin(FILE* F) {
    elem_radio *elem =init_elem_radio();
    elem=elemRadioFunction(elem,F);
    return ((elem_radio*)elem);
}

radio* grouper_radio(FILE* F) {
    radio *radioButtons = (radio*)malloc(sizeof(radio));
    if (radioButtons == NULL)
    {
        perror("Erreur lors de l'allocation de mémoire");
        exit(-1);
    }
    elem_radio *elem =ajouter_radio_fin(F);
    elem_radio* L=elem;
    do
    {
        L->suivant=ajouter_radio_fin(F);
        L=L->suivant;
    }while(L);
    radioButtons->liste=elem;
    return radioButtons;
}

<<<<<<< Updated upstream
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
//
//elem_radio* radioFunction(elem_radio* L, FILE* F) {
//    if (L == NULL || F == NULL) return NULL;
//
//    gchar elem[50];
//    gchar c;
//    int check;
//
//    do {
//        if (fscanf(F, "%49s", elem) != 1) break;
//
//        if (strcmp(elem, "label") == 0) {
//            gchar label[NBC];
//            if (fscanf(F, "=\"%49[^\"]\"", label) != 1) break;
//            L->label = strdup(label);
//        } else if (strcmp(elem, "name") == 0) {
//            gchar name[NBC];
//            if (fscanf(F, "=\"%49[^\"]\"", name) != 1) break;
//            L->name = strdup(name);
//        } else if (strcmp(elem, "hexcolor") == 0) {
//            gchar hexcolor[8];  // Assuming hex color is in the format "#RRGGBB"
//            if (fscanf(F, "=\"%7[^\"]\"", hexcolor) != 1) break;
//            L->hexcolor = strdup(hexcolor);
//        } else if (strcmp(elem, "checked") == 0) {
//            if (fscanf(F, "=\"%d\"", &check) == 1)
//                L->checked = (check == 1) ? TRUE : FALSE;
//        }
//    } while (strcmp(elem, ">"));
//
//    return L;
//}


GtkWidget* add_radio(int numButtons, gint x, gint y, char *labels[], char *colors[], gboolean checked[],gchar* name[]) {
    elem_radio *liste_radio = NULL;
    for (int i = 0; i < numButtons; i++) {
        liste_radio = ajouter_radio_fin(liste_radio, labels[i], colors[i], checked[i],name[i]);
    }
    radio *grouped_radio = grouper_radio(liste_radio, NULL);
=======
// Function to create radio buttons from the radio list
GtkWidget* create_radio_buttons(radio* radio_list) {
>>>>>>> Stashed changes
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    elem_radio* current = radio_list->liste;
    while (current)
    {
        current->pRadio = gtk_radio_button_new_with_label(NULL, current->label);
        if (current->hexcolor)
        {
            GdkRGBA color;
            gdk_rgba_parse(&color, current->hexcolor);
            gtk_widget_override_background_color(current->pRadio, GTK_STATE_FLAG_NORMAL, &color);
        }
        if (current->checked)
        {
            gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(current->pRadio), TRUE);
        }
        gtk_box_pack_start(GTK_BOX(box), current->pRadio, FALSE, FALSE, 0);
        current = current->suivant;
    }
    return box;
}

GtkWidget* add_radio(FILE* F) {
    radio* radio_list = grouper_radio(F);
    if (radio_list == NULL || radio_list->liste == NULL)
    {
        // Error handling: Failed to read radio data or empty radio list
        fprintf(stderr, "Error: Failed to read radio button data.\n");
        return NULL;
    }
    GtkWidget *pVBox=create_radio_buttons(radio_list);
    // Debug output
    printf("Radio buttons created successfully.\n");
    return ((GtkWidget*)pVBox); // Return the fixed container as GtkWidget
}


#endif // RADIO_H_INCLUDED
