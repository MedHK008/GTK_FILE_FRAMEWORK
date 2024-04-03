#ifndef SCROLLBAR_H_INCLUDED
#define SCROLLBAR_H_INCLUDED

// D�finition de la structure barre_def
typedef struct
{
    GtkWidget *widget;   // Widget de la barre de d�filement
    GtkWidget *parent;   // Widget parent de la barre de d�filement
    GtkWidget *fils;     // Widget fils (conteneur) associ� � la barre de d�filement
    guint hpolic;        // Politique de d�filement horizontal (GTK_POLICY_AUTOMATIC, GTK_POLICY_ALWAYS, GTK_POLICY_NEVER)
    guint vpolic;        // Politique de d�filement vertical (GTK_POLICY_AUTOMATIC, GTK_POLICY_ALWAYS, GTK_POLICY_NEVER)
    gint w; // Largeur
    gint h; // Hauteur
    gchar *name;
} barre_def;

// Fonction pour initialiser une barre de d�filement avec des param�tres sp�cifi�s
barre_def *initialiser_barre_def()
{
    // Allocation dynamique de m�moire pour une nouvelle structure barre_def
    barre_def *scrBar = (barre_def *)g_malloc(sizeof(barre_def));

    // Cr�ation d'une nouvelle barre de d�filement GtkScrolledWindo
    scrBar->widget = gtk_scrolled_window_new(NULL, NULL);
    if(scrBar->widget) printf("\n fffffffffffffffffffff");
    // Initialisation des champs de style
    scrBar->h = 0;
    scrBar->w = 0;
    scrBar->name=(gchar *)g_malloc(sizeof(gchar));
    scrBar->name[0]='\0';

    // Initialisation des champs de politique de d�filement
    scrBar->hpolic = 2;
    scrBar->vpolic = 2;

    // Retour de la structure initialis�e
    return(barre_def*) scrBar;
}
barre_def *scrollbarfunction(barre_def *scbar,FILE *F)
{
     gchar* elem;
    elem=(gchar*)g_malloc(sizeof(gchar)*50);
    gchar c;
    do
    {
        fscanf(F,"%s",elem);
       if (strcmp(elem, "name") == 0) {
            if ((c = epurer_blan(F)) == '=') {
                if ((c = epurer_blan(F)) == '\"') {
                    int i = 0;
                    while ((c = fgetc(F)) != '\"')
                        scbar->name[i++] = c;
                    scbar->name[i] = '\0';
                }
            }
        } else if (strcmp(elem, "hpolic") == 0) {
            if ((c = epurer_blan(F)) == '=')
               fscanf(F, "%d", &scbar->hpolic);
        } else if (strcmp(elem, "vpolic") == 0) {
            if ((c = epurer_blan(F)) == '=') {
               fscanf(F, "%d", &scbar->vpolic);
            }
        } else if (strcmp(elem, "width") == 0) {
            if ((c = epurer_blan(F)) == '=') {
                fscanf(F, "%d", &scbar->w);
            }
        } else if (strcmp(elem, "height") == 0) {
            if ((c = epurer_blan(F)) == '=') {
                fscanf(F, "%d", &scbar->h);
            }
        }
    }while(strcmp(elem,">"));
    return(barre_def*) scbar;
}

// Fonction pour cr�er une barre de d�filement avec un conteneur associ�
GtkWidget* creer_scrollbar(barre_def *scrbar,GtkWidget *pere)
{
    GtkWidget *conteneur=gtk_fixed_new();
    // Ajout de la barre de d�filement en tant que fils du widget parent
    gtk_container_add(GTK_CONTAINER(pere), scrbar->widget);
   //gtk_box_pack_start(GTK_BOX(pere), scrbar->widget, FALSE, FALSE,10);
    // D�finition de la taille demand�e pour la barre de d�filement
    gtk_widget_set_size_request(scrbar->widget, scrbar->w, scrbar->h);
    gtk_container_add(GTK_CONTAINER(scrbar->widget),conteneur);
    // D�finition des politiques de d�filement (horizontal et vertical)
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrbar->widget),polic(scrbar->vpolic), polic(scrbar->hpolic));
    return(GtkWidget*) conteneur;
}
gint polic(gint type)
{
    switch(type)
    {
        case 1: return GTK_POLICY_ALWAYS;
        case 2: return GTK_POLICY_AUTOMATIC;
        case 3: return GTK_POLICY_NEVER;
        case 4: return GTK_POLICY_EXTERNAL;
    }
    return NULL;
}
GtkWidget *add_scrollbar(FILE *F,GtkWidget *pere)
{

    barre_def *scrolled=initialiser_barre_def();
    scrolled=scrollbarfunction(scrolled,F);
   GtkWidget *conteneur= creer_scrollbar(scrolled,pere);
    return(GtkWidget*) conteneur;
}



#endif // SCROLLBAR_H_INCLUDED
