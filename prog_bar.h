#ifndef PROG_BAR_H_INCLUDED
#define PROG_BAR_H_INCLUDED

typedef struct
{
    GtkWidget *widget;   // Pointeur vers l'objet de la barre de progression (GtkProgressBar)
    GtkWidget *parent;   // Pointeur vers un widget parent
    gdouble fraction;    // La fraction actuelle de la barre de progression (peut varier de 0 � 1)
    gdouble unite;      // L'unit� de progression de la barre de progression
    gint type;
    gchar *name;
    gint x;
    gint y;
    gint h;
    gint w;

} barre_prog;

// Fonction pour initialiser une barre_prog avec des valeurs sp�cifi�es
barre_prog *initialiser_barre_prog()
{
    // Allocation dynamique de m�moire pour une nouvelle structure barre_prog
    barre_prog *ProgressBar = (barre_prog *)g_malloc(sizeof(barre_prog));

    // Cr�ation d'une nouvelle barre de progression GtkProgressBar et assignation au champ widget
    ProgressBar->widget = gtk_progress_bar_new();
//    ProgressBar->parent=pere;
    ProgressBar->w=0;
    ProgressBar->h=0;
 //   if(ProgressBar->w || ProgressBar->h)
 //         gtk_widget_set_size_request(ProgressBar->widget, ProgressBar->w, ProgressBar->h);
    // Initialisation des champs fraction et unite avec les valeurs sp�cifi�es
    ProgressBar->unite = 0.1;
    ProgressBar->fraction = 1.0;
    ProgressBar->type=1;
    ProgressBar->name=(gchar*)g_malloc(sizeof(gchar)*30);
    ProgressBar->name[0]='\0';

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
barre_prog *progBarFunction(barre_prog*p,FILE *F)
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
                        p->name[i++] = c;
                    p->name[i] = '\0';
                }
            }
        } else if (strcmp(elem, "fraction") == 0) {
            if ((c = epurer_blan(F)) == '=')
               fscanf(F, "%f", &p->fraction);
        } else if (strcmp(elem, "unite") == 0) {
            if ((c = epurer_blan(F)) == '=') {
               fscanf(F, "%f", &p->unite);
            }
        } else if (strcmp(elem, "width") == 0) {
            if ((c = epurer_blan(F)) == '=') {
                fscanf(F, "%d", &p->w);
            }
        } else if (strcmp(elem, "height") == 0) {
            if ((c = epurer_blan(F)) == '=') {
                fscanf(F, "%d", &p->h);
            }
        } else if (strcmp(elem, "type") == 0) {
            if ((c = epurer_blan(F)) == '=') {
                fscanf(F, "%d", &p->type);
            }
        }else if (strcmp(elem, "xligne") == 0) {
            if ((c = epurer_blan(F)) == '=') {
                fscanf(F, "%d", &p->x);
            }
        }
        else if (strcmp(elem, "yligne") == 0) {
            if ((c = epurer_blan(F)) == '=') {
                fscanf(F, "%d", &p->y);
            }
        }
    }while(strcmp(elem,">"));
    return p;
}

//GtkWidget *pere,gdouble dfr,gdouble unite,gint x,gint y,gboolean type,gint w,gint h
GtkWidget *add_progress_bar(FILE *F)
{
    barre_prog *bar=initialiser_barre_prog();
    GtkWidget *pVBox=gtk_vbox_new(FALSE,10);
    gtk_box_pack_start(GTK_BOX(pVBox),bar->widget, TRUE, FALSE, 0);
    bar=progBarFunction(bar,F);
    switch(bar->type)
    {
        case 0:
        case 1:
                GtkWidget *pButton = gtk_button_new_with_label("ajouter unite");
               gtk_box_pack_start(GTK_BOX(pVBox), pButton, TRUE, FALSE, 0);
               g_signal_connect_swapped(G_OBJECT(pButton), "clicked", G_CALLBACK(OnButton),bar);
               if(bar->type==1) break;
        case 2:   GtkWidget *pButton1 = gtk_button_new_with_label(GTK_STOCK_REFRESH);
                gtk_box_pack_start(GTK_BOX(pVBox), pButton1, TRUE, FALSE, 0);
               g_signal_connect_swapped(G_OBJECT(pButton1), "clicked", G_CALLBACK(progression_animation),bar);
               break;
    }
    bar->parent=pVBox;
     //gtk_fixed_put(pere,pVBox,x,y);
     return bar;
}

#endif // PROG_BAR_H_INCLUDED
