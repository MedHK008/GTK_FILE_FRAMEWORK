#ifndef COCHER_H_INCLUDED
#define COCHER_H_INCLUDED



typedef struct coche
{
    GtkWidget *parent;  /// le widget parent
    char label[NBC];    /// Le nom du bouton à cocher;
    GtkWidget *boutcoche;
    GtkWidget *fixed;    // Fixed widget to hold cocher buttons
    gint x;
    gint y;
} cocher;

cocher *init_cocher(GtkWidget *parent, const char *label, gint x, gint y)
{
    cocher *C = (cocher *)malloc(sizeof(cocher));
    if (C == NULL) {
        // Handle allocation failure here
        return NULL;
    }
    C->parent = parent;
    strncpy(C->label, label, NBC - 1); // Safer version of strcpy
    C->label[NBC - 1] = '\0'; // Ensure null-terminated string
    C->boutcoche = gtk_check_button_new_with_label(C->label);
    C->x=x;
    C->y=y;
    return C;
}

#endif // COCHER_H_INCLUDED
