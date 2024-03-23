#ifndef FIXED_H_INCLUDED
#define FIXED_H_INCLUDED

typedef struct {
    GtkWidget* fixed;
} Fixed;


Fixed* init_gtk_fixed() {
    Fixed* info =(Fixed*)malloc(sizeof(Fixed));
    if (!info) {
        g_print("Error: Failed to allocate memory for Fixed\n");
        return NULL;
    }
    info->fixed = gtk_fixed_new();

    return info;
}

void add_widget_to_fixed(Fixed* fixedInfo, GtkWidget* widget, gint x, gint y) {
    gtk_fixed_put(GTK_FIXED(fixedInfo->fixed), widget, x, y);
}

void remove_widget_from_fixed(Fixed* fixedInfo, GtkWidget* widget) {
    gtk_container_remove(GTK_CONTAINER(fixedInfo->fixed), widget);
}

void free_gtk_fixed_info(Fixed* fixedInfo) {
    if (fixedInfo) {
        g_object_unref(fixedInfo->fixed);
        g_free(fixedInfo);
    }
}

#endif // FIXED_H_INCLUDED
