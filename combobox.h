#ifndef COMBOBOX_H_INCLUDED
#define COMBOBOX_H_INCLUDED


// Structure de la combobox
typedef struct {
    GtkWidget *comboBox;
    GtkWidget *container;
    gchar *nom;
    gchar *label;
    gint posx;
    gint posy;
} ComboBox;

// Fonction d'initialisation de la combobox
ComboBox *init_combobox(GtkWidget *pere) {
    ComboBox *cb = (ComboBox*)malloc(sizeof(ComboBox));
    cb->comboBox = NULL;
    cb->container = (GtkWidget*)malloc(sizeof(GtkWidget));
    if(pere) cb->container = pere;
    cb->nom = (gchar*)malloc(35 * sizeof(gchar));
    cb->posx = 0;
    cb->posy = 0;
    return cb;
}

// Fonction de création de la combobox
void create_combobox(ComboBox *cb) {
    cb->comboBox = gtk_combo_box_text_new();
    gtk_widget_set_name(cb->comboBox, cb->nom);
    gtk_box_pack_start(GTK_BOX(cb->container), cb->comboBox,FALSE,TRUE,0);
}

ComboBox *comboFunction(FILE* F,ComboBox* CB)
{
    int i;
    gchar* elem;
    elem=(gchar*)g_malloc(sizeof(gchar)*30);
    gchar c;
    do
    {
        fscanf(F,"%s",elem);
        printf("\nread element : %s ",elem);
        if (strcmp(elem, "label") == 0)
        {
            if ((c = epurer_blan(F)) == '=')
                if ((c = fgetc(F)) == '\"')
                {
                     i= 0;
                    while ((c = fgetc(F)) != '\"')
                        CB->nom[i++] = c;
                    CB->nom[i] = '\0';
                }
            printf("%s",CB->nom);
        } else if (strcmp(elem, "name") == 0){
            if ((c = fgetc(F)) == '=')
                if ((c = epurer_blan(F)) == '\"')
                {
                     i= 0;
                    while ((c = fgetc(F)) != '\"')
                        CB->label[i++] = c;
                    CB->label[i] = '\0';
                }
        } else if (strcmp(elem, "posx") == 0){
                if ((c = epurer_blan(F)) == '=')
                  fscanf(F, "%d", &CB->posx);
        } else if (strcmp(elem, "posy") == 0){
                if ((c = epurer_blan(F)) == '=')
                  fscanf(F, "%d", &CB->posy);
        }

    }while(strcmp(elem,">"));
    return(ComboBox*) CB;
}

ComboBox* add_comboBox(GtkWidget *pere,FILE* F)
{
    ComboBox *combobox = init_combobox(pere);
    combobox = comboFunction(F,combobox);
    create_combobox(combobox);
    return ((ComboBox*)combobox);
}

// Fonction d'ajout d'un élément à la combobox
void combobox_add(ComboBox *cb,FILE* F) {
    gchar *text;
    text=(gchar*)g_malloc(sizeof(gchar)*30);
    int i;
    gchar* elem;
    elem=(gchar*)g_malloc(sizeof(gchar)*30);
    gchar c;
    do
    {
        do
        {
            fscanf(F,"%s",elem);
            printf("\nread element : %s ",elem);
            if (strcmp(elem, "label") == 0)
            {
                if ((c = epurer_blan(F)) == '=')
                    if ((c = fgetc(F)) == '\"')
                    {
                         i= 0;
                        while ((c = fgetc(F)) != '\"')
                            text[i++] = c;
                        text[i] = '\0';
                    }
                printf("\n%s",text);
            }
        }while(strcmp(elem,">"));
        gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(cb->comboBox), NULL, text);
        gtk_combo_box_set_active(GTK_COMBO_BOX(cb->comboBox), 0);
        fscanf(F,"%s",elem);
    }while(strcmp(elem,"</combobox>"));
}


// Fonction de récupération du texte de l'élément sélectionné dans la combobox
gchar *combobox_get(ComboBox *cb) {
    return gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(cb->comboBox));
}


#endif // COMBOBOX_H_INCLUDED
