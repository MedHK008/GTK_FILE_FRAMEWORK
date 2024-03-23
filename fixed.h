#ifndef FIXED_H_INCLUDED
#define FIXED_H_INCLUDED

typedef struct {
    gchar* name;
    GtkWidget* fixed;
} Fixed;


Fixed* init_gtk_fixed(gchar* name) {
    Fixed* info =(Fixed*)malloc(sizeof(Fixed));
    if (!info) {
        g_print("Error: Failed to allocate memory for Fixed\n");
        return NULL;
    }
    info->name=name;
    info->fixed = gtk_fixed_new();
    if (info->name) gtk_widget_set_name(info->fixed,info->name);
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
