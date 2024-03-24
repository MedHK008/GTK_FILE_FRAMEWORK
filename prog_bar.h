#ifndef PROG_BAR_H_INCLUDED
#define PROG_BAR_H_INCLUDED

typedef struct
{
    GtkWidget *widget;   // Pointeur vers l'objet de la barre de progression (GtkProgressBar)
    GtkWidget *parent;   // Pointeur vers un widget parent
    gdouble fraction;    // La fraction actuelle de la barre de progression (peut varier de 0 � 1)
    gdouble unite;      // L'unit� de progression de la barre de progression
    gint h;
    gint w;

} barre_prog;

// Fonction pour initialiser une barre_prog avec des valeurs sp�cifi�es
barre_prog *initialiser_barre_prog(GtkWidget *pere,gdouble dfr, gdouble unt,gint w,gint h)
{
    // Allocation dynamique de m�moire pour une nouvelle structure barre_prog
    barre_prog *ProgressBar = (barre_prog *)g_malloc(sizeof(barre_prog));

    // Cr�ation d'une nouvelle barre de progression GtkProgressBar et assignation au champ widget
    ProgressBar->widget = gtk_progress_bar_new();
    ProgressBar->parent=pere;
    ProgressBar->w=w;
    ProgressBar->h=h;
    if(ProgressBar->w || ProgressBar->h)
          gtk_widget_set_size_request(ProgressBar->widget, ProgressBar->w, ProgressBar->h);
    // Initialisation des champs fraction et unite avec les valeurs sp�cifi�es
    ProgressBar->unite = unt;
    ProgressBar->fraction = dfr;

    // Retour de la structure initialis�e
    return ProgressBar;
}

// Fonction pour animer la progression d'une barre
void progression_animation(barre_prog *pWidget, gpointer data)
{
    gdouble dFraction;      // Fraction de progression
    gint i = (pWidget->fraction * 2000);  // Conversion de la fraction en entier
    gint iTotal = 2000;     // Valeur totale pour la boucle d'animation

    /* Initialisation de l'animation */
    gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(pWidget->widget), pWidget->fraction);

    /* Acquisition du grab sur la barre de progression pour optimiser et bloquer les actions de l'utilisateur */
    gtk_grab_add(pWidget->widget);
    printf("D�but de l'animation de progression\n");

    // Boucle d'animation
    for (i; i < iTotal; ++i)
    {
        dFraction = (gdouble)i / (gdouble)iTotal;

        /* Modification de la valeur de la barre de progression */
        gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(pWidget->widget), dFraction);

        /* Permet � GTK+ de traiter les �v�nements en cours */
        gtk_main_iteration();
    }

    /* Lib�ration du grab sur la barre de progression � la fin de l'animation */
    gtk_grab_remove(pWidget->widget);
}

void OnButton(barre_prog *pWidget, gpointer data)
{
   // R�cup�ration de la valeur actuelle de la barre de progression
   gdouble valeurCourante = gtk_progress_bar_get_fraction(GTK_PROGRESS_BAR(pWidget->widget));

   // Ajout de l'unit� � la valeur actuelle
   valeurCourante += pWidget->unite;

   // Si la nouvelle valeur d�passe 1.0, revenir � 0.0
   if (valeurCourante > 1.0)
      valeurCourante = 0.0;

   // Mise � jour de la valeur de la barre de progression dans la structure
   pWidget->fraction = valeurCourante;

   // Modification de la valeur de la barre de progression
   gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(pWidget->widget), valeurCourante);
}

void add_progress_bar(GtkWidget *pere,gdouble dfr,gdouble unite,gint x,gint y,gboolean type,gint w,gint h)
{
    barre_prog *bar=initialiser_barre_prog(pere,dfr,unite,w,h);
    GtkWidget *pVBox=gtk_vbox_new(FALSE,10);
    gtk_box_pack_start(GTK_BOX(pVBox),bar->widget, TRUE, FALSE, 0);
    switch(type)
    {
        case 0:
        case 1:
                GtkWidget *pButton = gtk_button_new_with_label("ajouter unite");
               gtk_box_pack_start(GTK_BOX(pVBox), pButton, TRUE, FALSE, 0);
               g_signal_connect_swapped(G_OBJECT(pButton), "clicked", G_CALLBACK(OnButton),bar);
               if(type==1) break;
        case 2:   GtkWidget *pButton1 = gtk_button_new_with_label(GTK_STOCK_REFRESH);
                gtk_box_pack_start(GTK_BOX(pVBox), pButton1, TRUE, FALSE, 0);
               g_signal_connect_swapped(G_OBJECT(pButton1), "clicked", G_CALLBACK(progression_animation),bar);
               break;
    }
    gtk_fixed_put(pere,pVBox,x,y);

}

#endif // PROG_BAR_H_INCLUDED
