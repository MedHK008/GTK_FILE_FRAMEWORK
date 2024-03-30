#ifndef RADIO_H_INCLUDED
#define RADIO_H_INCLUDED

typedef struct elem_radio {
    GtkWidget *pRadio; // le widget radio
    GtkWidget *parent; // father
    gchar* name;
    gchar* label; // label du bouton
    gchar *hexcolor; // couleur de fond en hexadécimal
    gint x_pos;
    gint y_pos;
    gboolean checked; // indique si le bouton est coché au début ou non
} elem_radio;




elem_radio* init_elem_radio()
{
    elem_radio* R=(elem_radio*)g_malloc(sizeof(elem_radio));
    R->parent=(GtkWidget*)g_malloc(sizeof(GtkWidget));
    R->name=(gchar*)g_malloc(sizeof(gchar)*NBC);
    R->label=(gchar*)g_malloc(sizeof(gchar)*NBC);
    R->hexcolor=(gchar*)g_malloc(sizeof(gchar)*NBC);
    R->checked=FALSE;
    R->x_pos=0;
    R->y_pos=0;
    return((elem_radio*)R);
}
elem_radio* elemRadioFunction(elem_radio* R, FILE* F) {
    gchar elem[NBC];  // Use a fixed-size buffer for reading elements
    gchar c;
    int check;
    printf("\nradio : \n");
    do {
        fscanf(F, "%s", elem);
        printf("Read element: %s\n", elem);

        if (strcmp(elem, "name") == 0) {
            if ((c = epurer_blan(F)) == '=') {
                if ((c = epurer_blan(F)) == '\"') {
                    int i = 0;
                    while ((c = fgetc(F)) != '\"' && c != EOF && i < NBC - 1)
                        R->name[i++] = c;
                    R->name[i] = '\0';
                }
            }
        } else if (strcmp(elem, "label") == 0) {
            if ((c = epurer_blan(F)) == '=') {
                if ((c = epurer_blan(F)) == '\"') {
                    int i = 0;
                    while ((c = fgetc(F)) != '\"' && c != EOF && i < NBC - 1)
                        R->label[i++] = c;
                    R->label[i] = '\0';
                }
            }
        } else if (strcmp(elem, "hexcolor") == 0) {
            if ((c = epurer_blan(F)) == '=') {
                if ((c = epurer_blan(F)) == '\"') {
                    int i = 0;
                    while ((c = fgetc(F)) != '\"' && c != EOF && i < NBC - 1)
                        R->hexcolor[i++] = c;
                    R->hexcolor[i] = '\0';
                }
            }
        } else if (strcmp(elem, "posx") == 0) {
            if ((c = epurer_blan(F)) == '=') {
                fscanf(F, "%d", &R->x_pos);
                c=fgetc(F);
            }
        } else if (strcmp(elem, "posy") == 0) {
            if ((c = epurer_blan(F)) == '=') {
                fscanf(F, "%d", &R->y_pos);
            }
        } else if (strcmp(elem, "checked") == 0) {
            if ((c = epurer_blan(F)) == '=') {
                fscanf(F, "%d", &check);
                R->checked = (check == 1) ? TRUE : FALSE;
            }
        }
    } while (strcmp(elem, ">"));

    return R;
}




elem_radio* add_radio(FILE* F, GtkWidget* parent, GtkWidget* radioparent) {
    elem_radio* R = init_elem_radio();
    R = elemRadioFunction(R, F);
    R->parent = parent;

    if (radioparent) {
        R->pRadio = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(radioparent), R->label);
    } else {
        R->pRadio = gtk_radio_button_new_with_label(NULL, R->label);
        radioparent = R->pRadio;  // Update radioparent if it was NULL
    }

    if (R->hexcolor) {
        GdkRGBA color;
        gdk_rgba_parse(&color, R->hexcolor);
        gtk_widget_override_background_color(R->pRadio, GTK_STATE_FLAG_NORMAL, &color);
    }

    if (R->checked) {
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(R->pRadio), TRUE);
    }

    return R;
}




#endif // RADIO_H_INCLUDED
