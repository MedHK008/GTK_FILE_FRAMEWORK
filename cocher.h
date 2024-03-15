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

void add_cocher(GtkWidget* fixed)
{
    cocher *checkbox1 = init_cocher(fixed, "Check 1", 150, 50);
    cocher *checkbox2 = init_cocher(fixed, "Check 2", 150, 100);
    cocher *checkbox3 = init_cocher(fixed, "Check 3", 150, 150);
    gtk_fixed_put(fixed,checkbox1->boutcoche,checkbox1->x,checkbox1->y);
    gtk_fixed_put(fixed,checkbox2->boutcoche,checkbox2->x,checkbox2->y);
    gtk_fixed_put(fixed,checkbox3->boutcoche,checkbox3->x,checkbox3->y);
}


#endif // COCHER_H_INCLUDED
