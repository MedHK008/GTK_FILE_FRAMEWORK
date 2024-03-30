#ifndef SPIN_BUTTON_H_INCLUDED
#define SPIN_BUTTON_H_INCLUDED


typedef struct {
    GtkWidget* SpinButton;
    gchar* name;
    gint min;
    gint max;
    gint step;
    gint value;
    gint height;
    gint width;
    gint wrap;
    gint digits;
    gint numeric;
    gint arrondissement;
    gchar* bgcolor;
    gint posx;
    gint posy;
} SpinButton;

// Function to read attributes from a text file and assign them to a SpinButton structure
SpinButton* spinButtonFunction(SpinButton* sb, FILE* file) {
    gchar elem[50];
    gchar c;
    do {
        fscanf(file, "%s", elem);
        if (strcmp(elem, "name") == 0) {
            if ((c = epurer_blan(file)) == '=') {
                if ((c = epurer_blan(file)) == '\"') {
                    int i = 0;
                    while ((c = fgetc(file)) != '\"')
                        sb->name[i++] = c;
                    sb->name[i] = '\0';
                }
            }
            printf("%s",sb->name);
        } else if (strcmp(elem, "min") == 0) {
            if ((c = epurer_blan(file)) == '=') {
                fscanf(file, "%d", &sb->min);
            }
        } else if (strcmp(elem, "max") == 0) {
            if ((c = epurer_blan(file)) == '=') {
                fscanf(file, "%d", &sb->max);
            }
        } else if (strcmp(elem, "step") == 0) {
            if ((c = epurer_blan(file)) == '=') {
                fscanf(file, "%d", &sb->step);
            }
        } else if (strcmp(elem, "value") == 0) {
            if ((c = epurer_blan(file)) == '=') {
                fscanf(file, "%d", &sb->value);
            }
        } else if (strcmp(elem, "height") == 0) {
            if ((c = epurer_blan(file)) == '=') {
                fscanf(file, "%d", &sb->height);
            }
        } else if (strcmp(elem, "width") == 0) {
            if ((c = epurer_blan(file)) == '=') {
                fscanf(file, "%d", &sb->width);
            }
        } else if (strcmp(elem, "wrap") == 0) {
            if ((c = epurer_blan(file)) == '=') {
                fscanf(file, "%d", &sb->wrap);
            }
        } else if (strcmp(elem, "digits") == 0) {
            if ((c = epurer_blan(file)) == '=') {
                fscanf(file, "%d", &sb->digits);
            }
        } else if (strcmp(elem, "numeric") == 0) {
            if ((c = epurer_blan(file)) == '=') {
                fscanf(file, "%d", &sb->numeric);
            }
        } else if (strcmp(elem, "arrondissement") == 0) {
            if ((c = epurer_blan(file)) == '=') {
                fscanf(file, "%d", &sb->arrondissement);
            }
        } else if (strcmp(elem, "bgcolor") == 0) {
            if ((c = epurer_blan(file)) == '=') {
                if ((c = fgetc(file)) == '\"') {
                    int i = 0;
                    while ((c = fgetc(file)) != '\"')
                        sb->bgcolor[i++] = c;
                    sb->bgcolor[i] = '\0';
                }
            }
        }else if (strcmp(elem, "posx") == 0) {
            if ((c = epurer_blan(file)) == '=') {
                fscanf(file, "%d", &sb->posx);
            }
        }else if (strcmp(elem, "posy") == 0) {
            if ((c = epurer_blan(file)) == '=') {
                fscanf(file, "%d", &sb->posy);
            }
        }
    } while (strcmp(elem, ">"));
    return sb;
}

// Function to initialize a SpinButton structure
SpinButton* init_spin_button() {
    SpinButton* sb = (SpinButton*)malloc(sizeof(SpinButton));
    if (!sb) {
        printf("\nErreur d'allocation !!\n");
        exit(0);
    }
    sb->SpinButton =(GtkWidget*)g_malloc(sizeof(GtkWidget));
    sb->name = NULL;
    sb->name =(gchar*)g_malloc(sizeof(char)*50);
    sb->bgcolor = NULL;
    sb->bgcolor =(gchar*)g_malloc(sizeof(char)*50);

    return sb;
}

// Function to create the SpinButton widget based on the SpinButton structure
void create_spin_button_widget(SpinButton* sb) {


    if ((sb->max) >= (sb->min)) {
        sb->SpinButton = gtk_spin_button_new_with_range(sb->min, sb->max, sb->step);
        gtk_spin_button_set_value(GTK_SPIN_BUTTON(sb->SpinButton), sb->value);
        gtk_widget_set_size_request(GTK_WIDGET(sb->SpinButton), sb->width, sb->height);
        gtk_spin_button_set_wrap(GTK_SPIN_BUTTON(sb->SpinButton), sb->wrap);
        gtk_spin_button_set_digits(GTK_SPIN_BUTTON(sb->SpinButton), sb->digits);
        gtk_spin_button_set_numeric(GTK_SPIN_BUTTON(sb->SpinButton), sb->numeric);
        gtk_spin_button_set_snap_to_ticks(GTK_SPIN_BUTTON(sb->SpinButton), sb->arrondissement);
        if (sb->bgcolor)
            add_bgcolor_spin_button(GTK_WIDGET(sb->SpinButton), sb->bgcolor, 1.0);
        gtk_widget_set_name(sb->SpinButton,sb->name);
    } else {
        printf("\nIntervalle du SpinButton n'est pas correct\n");
        exit(0);
    }
}

// Function to add a background color to the SpinButton widget
void add_bgcolor_spin_button(GtkWidget* widget, const gchar* color, gdouble opacity) {
    GdkRGBA rgba;
    if (gdk_rgba_parse(&rgba, color)) {
        rgba.alpha = opacity;
        gtk_widget_override_background_color(widget, GTK_STATE_NORMAL, &rgba);
    } else {
        g_print("Erreur : Impossible de parser la couleur %s\n", color);
    }
}

// Function to add a SpinButton widget with specified parameters
SpinButton* add_spin_button_from_file(FILE* file) {
    SpinButton* sb = init_spin_button();
    sb = spinButtonFunction(sb, file);
    create_spin_button_widget(sb);
    return ((SpinButton*)sb);
}


#endif // SPIN_BUTTON_H_INCLUDED
