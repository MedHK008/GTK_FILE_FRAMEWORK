#ifndef FIXED_H_INCLUDED
#define FIXED_H_INCLUDED

typedef struct {
    gchar* name;
    guint posx,posy;
    GtkWidget* fixed;
} fixed;


fixed* init_gtk_fixed()
{
    fixed* info =(fixed*)malloc(sizeof(fixed));
    if (!info) {
        g_print("Error: Failed to allocate memory for fixed\n");
        return NULL;
    }
    info->name=(gchar*)malloc(sizeof(gchar));
    info->name[0]='\0';
    info->posx=0;
    info->posy=0;
    info->fixed = gtk_fixed_new();
    return info;
}


void add_widget_to_fixed(fixed* fixedInfo, GtkWidget* widget, gint x, gint y) {
    gtk_fixed_put(GTK_FIXED(fixedInfo->fixed), widget, x, y);
}

void remove_widget_from_fixed(fixed* fixedInfo, GtkWidget* widget) {
    gtk_container_remove(GTK_CONTAINER(fixedInfo->fixed), widget);
}

void free_gtk_fixed_info(fixed* fixedInfo) {
    if (fixedInfo) {
        g_object_unref(fixedInfo->fixed);
        g_free(fixedInfo);
    }
}

#endif // FIXED_H_INCLUDED
