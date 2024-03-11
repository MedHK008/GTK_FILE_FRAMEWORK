#ifndef BOUTTON_NORMAL_H_INCLUDED
#define BOUTTON_NORMAL_H_INCLUDED

typedef struct b {
    GtkWidget *parent;  // le widget parent
    GtkWidget *btn;     // le boutton
    GtkWidget *icon;    // icon si le boutton a une, null si non
    gchar *label;       // le label
    gboolean mnemonique; // si le label est mnémonique ou non
    gint width;         // width of the button
    gint height;        // height of the button
} boutton;

boutton* init_button(GtkWidget* p, char label[NBC], int mnemo, int bgcolor, gint width, gint height, char *image_path) {
    boutton *B;
    B = (boutton*)malloc(sizeof(boutton)); // Allocation de memoire
    if(!B) exit(-1); // erreur d'allocation
    if(mnemo) B->mnemonique = TRUE;
    B->label = (char*)malloc(sizeof(char) * (strlen(label) + 1));
    strcpy(B->label, label);
    B->icon = NULL;
    B->width = width;
    B->height = height;
    if (image_path != NULL) {
        B->icon = gtk_image_new_from_file(image_path);
    }
    return B;
}

void create_button(boutton* B, GtkFixed *fixed, gint x, gint y) {
    if (B->icon) {
        // Create a vertical box to hold the image and label
        GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

        // Add the image to the box
        gtk_box_pack_start(GTK_BOX(vbox), B->icon, FALSE, FALSE, 0);

        // Create a label for the button
        GtkWidget *label = NULL;
        if (B->mnemonique)
            label = gtk_label_new_with_mnemonic(B->label);
        else
            label = gtk_label_new(B->label);

        // Set label alignment to center
        gtk_label_set_xalign(GTK_LABEL(label), 0.5);

        // Add the label to the box
        gtk_box_pack_start(GTK_BOX(vbox), label, FALSE, FALSE, 0);

        // Create the button and set its size
        B->btn = gtk_button_new();
        gtk_widget_set_size_request(B->btn, B->width, B->height);

        // Add the box (containing the image and label) to the button
        gtk_container_add(GTK_CONTAINER(B->btn), vbox);
    } else {
        if (!(B->mnemonique))
            B->btn = gtk_button_new_with_label(B->label);
        else
            B->btn = gtk_button_new_with_mnemonic(B->label);
    }
    gtk_fixed_put(fixed, B->btn, x, y);
}

#endif // BOUTTON_NORMAL_H_INCLUDED
