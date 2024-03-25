#ifndef COCHER_H_INCLUDED
#define COCHER_H_INCLUDED

typedef struct coche {
    GtkWidget *parent;  // le widget parent
    gchar *label;       // Le nom du bouton à cocher;
    gchar *name;
    GtkWidget *boutcoche;
    gint x;
    gint y;
    gchar *gui;         // Couleur de fond du bouton au format HEX (par exemple, "#000000")
    struct coche *next; // Pointer to the next checkbox in the list
} cocher;

typedef struct {
    cocher *head; // Pointer to the head of the list
} CheckboxList;

CheckboxList *init_checkbox_list() {
    CheckboxList *list = (CheckboxList *)malloc(sizeof(CheckboxList));
    if (list == NULL) return NULL;
    list->head = NULL; // Initialize the list with NULL
    return list;
}

cocher *init_cocher(GtkWidget *parent, gchar *label, gint x, gint y, gchar *gui, gboolean checked,gchar* name) {
    cocher *C = (cocher *)malloc(sizeof(cocher));
    if (C == NULL) return NULL;
    C->name=name;
    C->parent = parent;
    C->label = g_strdup(label);  // Allocate memory for C->label and copy the string
    C->boutcoche = gtk_check_button_new_with_label(C->label);
    C->x = x;
    C->y = y;
    C->next = NULL; // Initialize next pointer to NULL

    // Set button background color
    if (gui)
    {
        C->gui = g_strdup(gui);  // Allocate memory for C->gui and copy the string
        GdkColor color;
        gdk_color_parse(C->gui, &color);
        gtk_widget_modify_bg(C->boutcoche, GTK_STATE_NORMAL, &color);
    }
    // Définir le nom du bouton (ID) pour le styliser en CSS
    if (C->name)
        gtk_widget_set_name(C->boutcoche,C->name);
    // Set initial state of the check button
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(C->boutcoche), checked);

    return C;
}

GtkWidget *add_cocher(CheckboxList *list, GtkWidget *parent, gchar *label, gint x, gint y, gchar *gui, gboolean checked,gchar* name) {
    cocher *checkbox = init_cocher(parent, label, x, y, gui, checked,name);
    if (checkbox == NULL) return NULL; // Check if initialization failed

    // Add checkbox to the list
    checkbox->next = list->head;
    list->head = checkbox;

    return checkbox->boutcoche;
}

#endif // COCHER_H_INCLUDED
