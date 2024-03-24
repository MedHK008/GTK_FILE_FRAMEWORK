#include <gtk/gtk.h>

typedef struct coche {
    GtkWidget *parent;  // le widget parent
    gchar *label;       // Le nom du bouton à cocher;
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

// Function to initialize every attribute to NULL
cocher *init_empty_cocher() {
    cocher *C = (cocher *)malloc(sizeof(cocher));
    if (C == NULL) return NULL;

    C->parent = NULL;
    C->label = NULL;
    C->boutcoche = NULL;
    C->x = 0;
    C->y = 0;
    C->gui = NULL;
    C->next = NULL;

    return C;
}

// Function to create and initialize a cocher widget
cocher *create_cocher(GtkWidget *parent, gchar *label, gint x, gint y, gchar *gui, gboolean checked) {
    cocher *C = init_empty_cocher();
    if (C == NULL) return NULL;

    C->parent = parent;
    C->label = g_strdup(label);  // Allocate memory for C->label and copy the string
    C->boutcoche = gtk_check_button_new_with_label(C->label);
    C->x = x;
    C->y = y;

    // Set button background color
    if (gui)
    {
        C->gui = g_strdup(gui);  // Allocate memory for C->gui and copy the string
        GdkColor color;
        gdk_color_parse(C->gui, &color);
        gtk_widget_modify_bg(C->boutcoche, GTK_STATE_NORMAL, &color);
    }
    // Set initial state of the check button
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(C->boutcoche), checked);

    return C;
}

// Function to add a cocher to the CheckboxList
GtkWidget *add_cocher(CheckboxList *list, GtkWidget *parent, gchar *label, gint x, gint y, gchar *gui, gboolean checked) {
    cocher *checkbox = create_cocher(parent, label, x, y, gui, checked);
    if (checkbox == NULL) return NULL; // Check if creation failed

    // Add checkbox to the list
    checkbox->next = list->head;
    list->head = checkbox;

    return checkbox->boutcoche;
}

