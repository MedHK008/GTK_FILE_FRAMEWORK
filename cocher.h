#ifndef COCHER_H_INCLUDED
#define COCHER_H_INCLUDED


typedef struct coche {
    GtkWidget *parent;  // le widget parent
    gchar *label;       // Le nom du bouton à cocher;
    GtkWidget *boutcoche;
    gint x;
    gint y;
    gchar *gui;         // Couleur de fond du bouton au format HEX (par exemple, "#000000")
} cocher;

cocher *init_cocher(GtkWidget *parent, gchar *label, gint x, gint y, gchar *gui, gboolean checked) {
    cocher *C = (cocher *)malloc(sizeof(cocher));
    if (C == NULL) return NULL;

    C->parent = parent;
    C->label = g_strdup(label);  // Allocate memory for C->label and copy the string
    C->boutcoche = gtk_check_button_new_with_label(C->label);
    C->x = x;
    C->y = y;
    C->gui = g_strdup(gui);  // Allocate memory for C->gui and copy the string

    // Set button background color
    GdkColor color;
    gdk_color_parse(C->gui, &color);
    gtk_widget_modify_bg(C->boutcoche, GTK_STATE_NORMAL, &color);

    // Set initial state of the check button
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(C->boutcoche), checked);

    return C;
}

void add_cocher(GtkWidget *fixed, gchar *label, gint x_fixed, gint y_fixed, gchar *gui, gboolean checked) {
    cocher *checkbox1 = init_cocher(fixed, label, x_fixed, y_fixed, gui, checked);
    gtk_fixed_put(GTK_FIXED(fixed), checkbox1->boutcoche, x_fixed, y_fixed);
}
#endif // COCHER_H_INCLUDED
