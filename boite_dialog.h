#ifndef BOITE_DIALOG_H_INCLUDED
#define BOITE_DIALOG_H_INCLUDED


// Structure repr�sentant une bo�te de dialogue



typedef struct {
        GtkWidget *boite;
        GtkWidget*parent;
        GtkWidget*fixed;
        gchar *titre;
        gchar *icone;               // Le chemin vers l'icône de la boîte de dialogue
        gint modal ;
        gint destroy_with_parent ;
        gint hauteur ;
        gint largeur ;
        gchar *couleur_fond;
}Boite_dialogue ;


//Token char_to_token(gchar *elem)
//{
//    if(!strcmp(elem,"button")) return button;;
//    if(!strcmp(elem,"Entry")) return Entry
//}
Boite_dialogue *initialiser_boite_dialogue()
{
    Boite_dialogue*BD=(Boite_dialogue*)g_malloc(sizeof(Boite_dialogue));
    if(!BD) exit(-1);
    BD->boite=NULL;
    BD->fixed=NULL;
    BD->parent=NULL;
    BD->titre=NULL;
    BD->icone=NULL;
    BD->couleur_fond=NULL;
    BD->modal=0;
    BD->hauteur=0;
    BD->largeur=0;

    return (Boite_dialogue*)(BD);
}

void definir_attribut(Boite_dialogue*BD)
{
     GdkRGBA couleur;


    BD->boite=gtk_dialog_new();
    if(BD->titre)
        gtk_window_set_title(GTK_WINDOW(BD->boite),BD->titre);
    if(BD->destroy_with_parent)
        gtk_window_set_destroy_with_parent(GTK_WINDOW(BD->boite),TRUE);
    if(BD->modal)
        gtk_window_set_modal(GTK_WINDOW(BD->boite),TRUE);
    if(BD->parent)
        gtk_window_set_transient_for(GTK_WINDOW(BD->boite), GTK_WINDOW(BD->parent));
    if(BD->largeur>0 && BD->hauteur>0)
        gtk_window_set_default_size(GTK_WINDOW(BD->boite), BD->largeur,BD->hauteur);
    if(BD->icone)
        {GdkPixbuf *icon = gdk_pixbuf_new_from_file(BD->icone, NULL);
        GList *icon_list = NULL;
        icon_list = g_list_append(icon_list, icon);
        gtk_window_set_icon_list(GTK_WINDOW(BD->boite), icon_list);



        }
    GtkWidget*content =gtk_dialog_get_content_area(GTK_DIALOG(BD->boite));
    BD->fixed=gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(content),BD->fixed);
    if(BD->couleur_fond)
    {
        gdk_rgba_parse(&couleur, BD->couleur_fond); // Convertir la couleur de fond en format GTK
        gtk_widget_override_background_color(BD->boite, GTK_STATE_FLAG_NORMAL, &couleur);
    }





}




void on_button_clicked(GtkWidget *widget, gpointer data) {
    gtk_widget_show_all(GTK_WIDGET(data));
}


#endif // BOITE_DIALOG_H_INCLUDED
