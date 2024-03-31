#ifndef COCHER_H_INCLUDED
#define COCHER_H_INCLUDED


typedef struct {
    GtkWidget *parent;
    gchar *label;
    gchar *name;
    GtkWidget *boutcoche;
    gint x_pos;
    gint y_pos;
    gchar *gui;
    gboolean checked;
    gint signal;
} cocher;

cocher *init_empty_cocher() {
    cocher *C = (cocher*)malloc(sizeof(cocher));
    if (C == NULL) return NULL;
    C->parent = NULL;
    C->label = NULL;
    C->name = NULL;
    C->x_pos = 0;
    C->y_pos = 0;
    C->gui = NULL;
    C->checked = FALSE;
    C->signal=0;
    return C;
}

void create_cocher(cocher *C) {
    C->boutcoche = gtk_check_button_new_with_label(C->label);
    if (C->name)
        gtk_widget_set_name(C->boutcoche, C->name);
    if (C->gui)
    {
        GdkColor color;
        gdk_color_parse(C->gui, &color);
        gtk_widget_modify_bg(C->boutcoche, GTK_STATE_NORMAL, &color);
    }
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(C->boutcoche), C->checked);
}

cocher *cocherFunction(cocher *C, FILE *F) {

    gchar elem[50];
    gchar c;
    int check;
    do {
        fscanf(F, "%s", elem);
        printf("%s\n",elem);
        if (strcmp(elem, "label") == 0)
        {
            C->label=(gchar*)g_malloc(sizeof(gchar)*50);
            if ((c = epurer_blan(F)) == '=') {

                if ((c = fgetc(F)) == '\"') {
                    int i = 0;
                    while ((c=fgetc(F)) != '\"')
                        C->label[i++] = c;
                    C->label[i] = '\0';
                }
            }
        }
        else if (strcmp(elem, "name") == 0)
        {
            C->name=(gchar*)g_malloc(sizeof(gchar)*50);
            if ((c = epurer_blan(F)) == '=') {
                if ((c = fgetc(F)) == '\"') {
                    int i = 0;
                    while ((c = fgetc(F)) != '\"')
                        C->name[i++] = c;
                    C->name[i] = '\0';
                }
            }
        }
        else if (strcmp(elem, "gui") == 0)
        {
            C->gui=(gchar*)g_malloc(sizeof(gchar)*50);
            if ((c = epurer_blan(F)) == '=') {
                if ((c = fgetc(F)) == '\"') {
                    int i = 0;
                    while ((c = fgetc(F)) != '\"')
                        C->gui[i++] = c;
                    C->gui[i] = '\0';
                }
            }
        }else if (strcmp(elem, "posx") == 0) {
            if ((c = epurer_blan(F)) == '=') {
                fscanf(F, "%d", &C->x_pos);
            }
        }else if (strcmp(elem, "posy") == 0) {
            if ((c = epurer_blan(F)) == '=') {
                fscanf(F, "%d", &C->y_pos);
            }
        }else if (strcmp(elem, "checked") == 0) {
            if ((c = epurer_blan(F)) == '=') {
                    fscanf(F,"%d",&check);
                    if(check == 1)
                        C->checked = TRUE;
                    else
                        C->checked = FALSE;
                }
        } else if (strcmp(elem, "signal") == 0) {
            if ((c = epurer_blan(F)) == '=') {
                fscanf(F, "%d", &C->signal);
            }
        }
    } while (strcmp(elem, ">"));

    return C;
}

cocher *add_cocher(FILE *F) {
    cocher *checkbox = init_empty_cocher();
    checkbox = cocherFunction(checkbox, F);
    create_cocher(checkbox);
    return checkbox;
}

#endif // COCHER_H_INCLUDED
