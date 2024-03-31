#ifndef BOITE_MESSAGE_H_INCLUDED
#define BOITE_MESSAGE_H_INCLUDED
// Structure représentant une boîte de message
typedef struct {
    GtkWidget *message_box;
    GtkWidget *parent;
    GtkWidget*fixed ;
    gchar *titre;
    gchar *icon;
    gchar *color;
    gint modal ;
    GtkMessageType type;
    GtkButtonsType button_type ;
    gint h ;
    gint w ;

} Boite_message;

// Fonction pour initialiser une boîte de message
Boite_message *initialiser_boite_message() {
    Boite_message *BM = g_malloc(sizeof(Boite_message));
    if (!BM) exit(-1);

    BM->message_box = NULL;
    BM->parent = NULL;
    BM->titre = NULL;
    BM->type = GTK_MESSAGE_ERROR;
    BM->modal=0;
    BM->button_type=GTK_BUTTONS_NONE;
    BM->h=0;
    BM->w=0;


    return BM;
}
Boite_message *lire_boite_message(FILE*F,Boite_message*BM)
{
    gchar elem[50];
    gchar c ;
    int i=0;
    Token tok ;
    c=epurer_blan(F);
    if(c=='<')
    {
        c=fgetc(F);
            if(c!='\\')
        {
            ungetc(c,F);
            fscanf(F,"%s",elem);
            printf("\nelem--->%s",elem);

            if(!strcmp(elem,"boite_message"))
            {
                while((c=epurer_blan(F))!='>')
            {
                ungetc(c,F);
                fscanf(F,"%s",elem);
                printf("\nelem---->%s\n",elem);
                if(!strcmp(elem,"titre"))
                {
                    BM->titre=(gchar*)g_malloc(sizeof(gchar)*50);
                    c=epurer_blan(F);
                    if(c=='=')
                    {
                        c=epurer_blan(F);
                        if(c=='\"')
                        {
                            i=0;
                            while((c=epurer_blan(F))!='\"')
                            {
                                BM->titre[i++]=c;
                            }

                            BM->titre[i]='\0';



                        }
                    }
                }
                else if(!strcmp(elem,"modal"))
                {
                    c=epurer_blan(F);
                    if(c=='=')
                    {

                        fscanf(F,"%d",&BM->modal);
                    }
                }
                else if(!strcmp(elem,"height"))
                {
                    c=epurer_blan(F);
                    if(c=='=')
                    {
                        fscanf(F,"%d",&BM->h);
                    }
                }
                  else if(!strcmp(elem,"width"))
                {
                    c=epurer_blan(F);
                    if(c=='=')
                    {
                        fscanf(F,"%d",&BM->w);
                    }
                }
                else if(!strcmp(elem,"icone"))
                {
                    BM->icon=(gchar*)g_malloc(sizeof(gchar)*100);
                    c=epurer_blan(F);
                    if(c=='=')
                    {
                        c=epurer_blan(F);
                        if(c=='\"')
                        {
                            i=0;
                            while((c=epurer_blan(F))!='\"')
                            {
                                BM->icon[i++]=c;
                            }

                            BM->icon[i]='\0';
                            printf("\nicon-->%s\n",BM->icon);



                        }
                    }

                }
                  else if(!strcmp(elem,"bgColor"))
                {
                    BM->color=(gchar*)g_malloc(sizeof(gchar)*50);
                    c=epurer_blan(F);
                    if(c=='=')
                    {
                        c=epurer_blan(F);
                        if(c=='\"')
                        {
                            i=0;
                            while((c=epurer_blan(F))!='\"')
                            {
                                BM->color[i++]=c;
                            }

                            BM->color[i]='\0';
                            printf("\ncolor-->%s\n",BM->color);



                        }
                    }

                }



            }
                definir_attribut_boite_message(BM);
                printf("\n---->\n");



        }
        }
    }


    return(Boite_message*)(BM);
}
// Fonction pour définir les attributs de la boîte de message
void definir_attribut_boite_message(Boite_message *BM) {

    BM->message_box = gtk_message_dialog_new(GTK_WINDOW(BM->parent),
                                             GTK_DIALOG_MODAL,
                                             BM->type,
                                             BM->button_type,NULL, NULL);
    if(BM->titre)
        gtk_window_set_title(GTK_WINDOW(BM->message_box), BM->titre);

    GtkWidget*content= gtk_dialog_get_content_area(GTK_DIALOG(BM->message_box));
   BM->fixed=gtk_fixed_new();
   gtk_container_add(GTK_CONTAINER(content),BM->fixed);
    gtk_widget_set_size_request(BM->message_box,BM->w,BM->h);
      if(BM->color)
    {

        GdkRGBA couleur;
        gdk_rgba_parse(&couleur, BM->color); // Convertir la couleur de fond en format GTK

        gtk_widget_override_background_color(BM->message_box, GTK_STATE_FLAG_NORMAL, &couleur);

    }
      if(BM->icon)
    {


    GdkPixbuf *icon = gdk_pixbuf_new_from_file(BM->icon, NULL);
    if (icon != NULL) {
        gtk_window_set_icon(GTK_WINDOW(BM->message_box), icon);
        g_object_unref(icon); // Free the icon's resources when it's no longer needed
    }
     }
}

// Fonction pour lire les attributs de la boîte de message à partir d'un fichier





void ajouter_to_boite_message(Boite_message*BM,GtkWidget*widget,gint x, gint y)
{
    if(BM && widget)
        gtk_fixed_put(GTK_FIXED(BM->fixed),widget,x,y);
}

void on_button_clicked_Boite_Message(GtkWidget *widget, gpointer data) {
    gtk_widget_show_all(GTK_WIDGET(data));
}




#endif // BOITE_MESSAGE_H_INCLUDED
