#ifndef SPIN_BUTTON_H_INCLUDED
#define SPIN_BUTTON_H_INCLUDED


typedef struct
{
    GtkWidget *SpinButton;//SpinButton
    gchar* name;
    gdouble min;//la valeur minimale
    gdouble max;//la valeur maximale
    gdouble step;//le pas
    gdouble value;//valeur par defaut
    gint height; //Hauteur du SpinButton
    gint width; //Longueur du SpinButton
    gint wrap;//:FALSE, 1:TRUE
    gint digits;//nombre de chiffres en partie d�cimale
    gint numeric;//0:(tapez de caracteres en generale), 1:(juste les chiffres)
    gint arrondissement;//0,1
    gchar* bgcolor;//background color
}SpinButton;


SpinButton * init_spin_button(gchar* name,gdouble val_min ,gdouble val_max, gdouble pas,gdouble val_defaut,
        gint height, gint width, gint wrap, gint digits,gint numeric , gint arrondis,gchar* color,gfloat color_opc)
{
    SpinButton *Sb = NULL;
    //allocation mémoire
    Sb =(SpinButton*)malloc(sizeof(SpinButton));
    //test d'allocation
    if(!Sb)
    {
        printf("\nErreur d'allocation!!!!!!\n");
        exit(0);
    }

    Sb->SpinButton =NULL;
    Sb->min=val_min;
    Sb->max=val_max;
    Sb->step=pas;
    Sb->name=name;
    Sb->value=val_defaut;
    Sb->height=height;
    Sb->width=width;
    Sb->wrap=wrap;
    Sb->digits=digits;
    Sb->numeric = numeric;
    Sb->arrondissement=arrondis;
    if(color) {
        Sb->bgcolor = (gchar*)malloc(30*sizeof(gchar));
        if(Sb->bgcolor)
        {
            strcpy(Sb->bgcolor, color);
        }
        else
        {
            printf("\nErreur d'allocation\n");
        }
    }

    return ((SpinButton*)Sb);
}

void add_bgcolor(GtkWidget* widget, const gchar* color, gdouble opacity) {
    GdkRGBA rgba;
    if (gdk_rgba_parse(&rgba, color))
    {
        rgba.alpha = opacity;
        gtk_widget_override_background_color(widget, GTK_STATE_NORMAL, &rgba);
    }
    else
    {
        g_print("Erreur : Impossible de parser la couleur %s\n", color);
    }
}

/*
    fonction: create spin_button
    entrees :
    sorties :
    desciprion:
    SpinButtonObjet "Sb: indique notre spinbutton object � cr�er SpinButton bien cr�e
    cette fonction sert � cr�er spinbutton en utilisant des fonctions de base sur ses caract�ristiques
*/
void create_spin_button(SpinButton* Sb) {
    //L'intervalle du SpinButton avec le pas
    if ((Sb->max) >= (Sb->min)) {
        Sb->SpinButton = gtk_spin_button_new_with_range(Sb->min, Sb->max, Sb->step); //Valeur par defaut
        gtk_spin_button_set_value(GTK_SPIN_BUTTON(Sb->SpinButton), Sb->value);
        //largeur et hauteur
        if (Sb->name) gtk_widget_set_name(Sb->SpinButton,Sb->name);
        if ((Sb->height > 0) && (Sb->width > 0))
            gtk_widget_set_size_request(GTK_WIDGET(Sb->SpinButton), Sb->width, Sb->height);
        else
            printf("Height & Width should be positive\n");
        if (Sb->digits >= 0)
            gtk_spin_button_set_digits(GTK_SPIN_BUTTON(Sb->SpinButton), Sb->digits);
        else
            printf("\nDigits should be positive\n");
        if (Sb->wrap == 1)
            gtk_spin_button_set_wrap(GTK_SPIN_BUTTON(Sb->SpinButton), TRUE);
        if (!(Sb->numeric))
            gtk_spin_button_set_numeric(GTK_SPIN_BUTTON(Sb->SpinButton), FALSE);
        if (Sb->arrondissement == 1)
            gtk_spin_button_set_snap_to_ticks(GTK_SPIN_BUTTON(Sb->SpinButton), TRUE);

        // Set background color
        if (Sb->bgcolor)
            add_bgcolor(GTK_WIDGET(Sb->SpinButton), Sb->bgcolor, 1.0); // Setting opacity to 1.0

    } else {
        printf("\nIntervalle du SpinButton n'est pas correct\n");
        exit(0);
    }
}

SpinButton* add_spin(gint x,gint y, gdouble val_min, gdouble val_max, gdouble pas, gdouble val_defaut,
              gint height, gint width, gint wrap, gint digits, gint numeric, gint arrondis,
              gchar* color, gfloat color_opc,gchar* name) {
    // Initialize SpinButton with provided parameters
    SpinButton *spin = init_spin_button(name,val_min, val_max, pas, val_defaut,
                                                    height, width, wrap, digits, numeric, arrondis, color, color_opc);
    // Create SpinButton
    create_spin_button(spin);
    return ((SpinButton*)spin);
}



#endif // SPIN_BUTTON_H_INCLUDED
