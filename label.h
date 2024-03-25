#ifndef LABEL_H_INCLUDED
#define LABEL_H_INCLUDED


/**
 fonts for the label :

Sans-Serif Fonts:

Arial
Helvetica
Calibri
Verdana
Tahoma
Trebuchet MS
Open Sans
Serif Fonts:

Times New Roman
Georgia
Garamond
Cambria
Palatino
Baskerville
Monospace (Fixed-width) Fonts:

Courier New
Consolas
Monaco
Liberation Mono
Inconsolata
Source Code Pro
Other Common Fonts:

Impact
Comic Sans MS
Lucida Console
Lucida Sans Unicode
 **/


typedef struct
{
     gchar *tex;
     guint alignement;/* L'alignement du texte
    1: GTK_JUSTIFY_LEFT pour aligner le texte � gauche (par d�faut);
    2: GTK_JUSTIFY_RIGHT pour aligner le texte � droite ;
    3: GTK_JUSTIFY_CENTER pour centrer le texte ;
    4:GTK_JUSTIFY_FILL pour justifier�le�texte*/
    gint w; // Largeur
    gint h; // Hauteur
    gchar police[30];//Pour definir la police utils�e*/
    gint taille_text;/* Pour definir la taille du texte*/
    gchar style[15];//Pour definir le style du texte*/
    gchar epaisseur[15]; /*Pour definir l'epaisseur du texte : small , large , Xlaarge... */
    gchar couleur_text[15];//Pour definir la couleur du texte*/
    gchar couleur_fond[15];//Pour definir la couleur du fond*/
    gchar underline[15];/* Pour le soulignement du texte*/
    gboolean line_through; //Pour barrer le texte/

}texte;

texte *textefunction(texte *tx,FILE *F)
{
    gchar* elem;
    elem=(gchar*)g_malloc(sizeof(gchar)*50);
    gchar c=epurer_blan(F);
    fscanf(F,"%s",elem);
    if(!strcmp(elem,"text_label"))
    do
    {
        fscanf(F,"%s",elem);

       if (strcmp(elem, "text") == 0) {
            if ((c = epurer_blan(F)) == '=') {
                if ((c = epurer_blan(F)) == '\"') {
                    int i = 0;
                    printf("%s\n ",tx->tex);
                    while ((c = fgetc(F)) != '\"')
                    {

                        tx->tex[i++] = c;
                    }

                    tx->tex[i] = '\0';

                }
            }
        } else if (strcmp(elem, "style") == 0) {
                if ((c = epurer_blan(F)) == '=') {
                if ((c = epurer_blan(F)) == '\"') {
                    int i = 0;
                    while ((c = fgetc(F)) != '\"')
                        tx->style[i++] = c;
                    tx->style[i] = '\0';
                }
            }

        } else if (strcmp(elem, "police") == 0) {
            if ((c = epurer_blan(F)) == '=') {
               if ((c = epurer_blan(F)) == '\"') {
                    int i = 0;
                    while ((c = fgetc(F)) != '\"')
                        tx->police[i++] = c;
                    tx->police[i] = '\0';
                }
            }
        }else if (strcmp(elem, "epaisseur") == 0) {
            if ((c = epurer_blan(F)) == '=') {
               if ((c = epurer_blan(F)) == '\"') {
                    int i = 0;
                    while ((c = fgetc(F)) != '\"')
                        tx->epaisseur[i++] = c;
                    tx->epaisseur[i] = '\0';
                }
            }
        }else if (strcmp(elem, "bgcolor") == 0) {
            if ((c = epurer_blan(F)) == '=') {
               if ((c = epurer_blan(F)) == '\"') {
                    int i = 0;
                    while ((c = fgetc(F)) != '\"')
                        tx->couleur_fond[i++] = c;
                    tx->couleur_fond[i] = '\0';
                }
            }
        }else if (strcmp(elem, "color") == 0) {
            if ((c = epurer_blan(F)) == '=') {
               if ((c = epurer_blan(F)) == '\"') {
                    int i = 0;
                    printf("%s\n",tx->couleur_text);
                    while ((c = fgetc(F)) != '\"')
                        tx->couleur_text[i++] = c;
                    tx->couleur_text[i] = '\0';

                }
            }
        }else if (strcmp(elem, "souligne") == 0) {
            if ((c = epurer_blan(F)) == '=') {
               if ((c = epurer_blan(F)) == '\"') {
                    int i = 0;
                    while ((c = fgetc(F)) != '\"')
                        tx->underline[i++] = c;
                    tx->underline[i] = '\0';
                }
            }
        }else if (strcmp(elem, "width") == 0) {
            if ((c = epurer_blan(F)) == '=') {
                fscanf(F, "%d", &tx->w);
            }
        }
        else if (strcmp(elem, "height") == 0) {
            if ((c = epurer_blan(F)) == '=') {
                fscanf(F, "%d", &tx->w);
            }
        }else if (strcmp(elem, "size") == 0) {
            if ((c = epurer_blan(F)) == '=') {
                fscanf(F, "%d", &tx->taille_text);
            }
        }
    }while(strcmp(elem,">"));
    return tx;
 }



// Fonction pour initialiser une structure texte
texte *initialiser_texte()
{
    // Allouer dynamiquement de la m�moire pour une nouvelle structure texte
    texte *tex = (texte *)g_malloc(sizeof(texte));

    // Copier le texte pass� en param�tre dans la structure texte
    //strcpy(tex->text, lb);

    // Si alg est non nul, utiliser sa valeur, sinon, utiliser 1 (GTK_JUSTIFY_LEFT) par d�faut
    tex->alignement = 0;
    tex->tex=(gchar *)g_malloc(sizeof(gchar)*200);
    tex->tex[0]='\0';
    // Si une police est sp�cifi�e, l'utiliser, sinon, utiliser "Sans" par d�faut
        strcpy(tex->police, "Sans");

    // Si une taille de texte est sp�cifi�e, l'utiliser, sinon, utiliser 10 par d�faut
        tex->taille_text = 10;

    // Si un style est sp�cifi�, l'utiliser, sinon, utiliser "normal" par d�faut
        strcpy(tex->style, "normal");
         printf("%s ",tex->style);

    // Si une couleur de texte est sp�cifi�e, l'utiliser, sinon, utiliser "#000000" (noir) par d�faut
        strcpy(tex->couleur_text, "#000000");

    // Si un soulignement est sp�cifi�, l'utiliser, sinon, utiliser "none" par d�faut
        strcpy(tex->underline, "none");
        printf("%s ",tex->underline);
       tex->couleur_fond[0]='\0';
    // Initialiser la structure style � partir des valeurs de largeur (w) et hauteur (h)
    tex->w = 20;
    tex->h = 30;

    // Renvoyer un pointeur vers la structure texte nouvellement cr��e
    return tex;
}

// Fonction pour appliquer un style � un �l�ment GTK en fonction d'un type donn�
GtkWidget *style_texte(GtkWidget *element, texte *text, gint type)
{
    gchar *sUtf8; // Cha�ne de caract�res pour le formatage du texte en UTF-8

    // Utiliser un commutateur (switch) pour g�rer diff�rents types d'�l�ments GTK
    switch (type)
    {
        case 1: // Cas o� l'�l�ment est un label (GTK_LABEL)
            element = gtk_label_new(NULL);
            if(text->couleur_fond[0]=='\0')
            // Formater le texte avec les propri�t�s sp�cifi�es dans la structure texte
            sUtf8 = g_strdup_printf("<span  font_desc=\"%d\" style=\"%s\" foreground=\"%s\" font_family=\"%s\" underline=\"%s\">%s</span> ",
                                    text->taille_text, text->style, text->couleur_text, text->police, text->underline, text->tex);
            else
             sUtf8 = g_strdup_printf("<span  font_desc=\"%d\" style=\"%s\" foreground=\"%s\" font_family=\"%s\" underline=\"%s\" background=\"%s\">%s</span> ",
                                    text->taille_text, text->style, text->couleur_text, text->police, text->underline,text->couleur_fond, text->tex);


            // Appliquer le texte format� au label
            gtk_label_set_markup(GTK_LABEL(element), sUtf8);

            // Lib�rer la m�moire allou�e pour la cha�ne sUtf8
            g_free(sUtf8);
            break;

        // Ajouter d'autres cas pour d'autres types d'�l�ments GTK si n�cessaire

    }

    // Renvoyer l'�l�ment GTK avec le style appliqu�
    return element;
}



/**********************************************************************************************************/

// Structure pour repr�senter une �tiquette avec un texte stylis�
typedef struct Label_et
{
    GtkWidget *widget;    /// Pointeur vers le widget du label
    GtkWidget *pere;      /// Pointeur vers le parent du label
    texte *text;          /// Texte du label
    gboolean selectable;  /// Indique si le texte peut �tre s�lectionn�
    gboolean wrap;        /// Indique si le texte peut �tre coup� en lignes
    gchar *name;
    gint x;
    gint y;
} Etiquette;

// Fonction pour initialiser une �tiquette (label) avec un texte stylis�
Etiquette *initialiser_label()
{
    // Allouer dynamiquement de la m�moire pour une nouvelle �tiquette
    Etiquette *label = (Etiquette *)g_malloc(sizeof(Etiquette));
    label->name=(gchar*)g_malloc(sizeof(gchar)*30);
    label->name[0]='\0';
    // Initialiser les champs de la structure Etiquette
    label->widget = gtk_label_new(NULL); // Cr�er un nouveau widget label
    //label->pere = parent; // Stocker le widget parent
    //label->text = stext; // Stocker le texte � afficher
    //label->widget = style_texte(label->widget, label->text, 1); // Appliquer le style au label
    label->selectable = 1; // Indiquer si le texte peut �tre s�lectionn�
    //gtk_label_set_selectable(GTK_LABEL(label->widget), label->selectable);
    label->wrap=1;
    //gtk_label_set_line_wrap(GTK_LABEL(label->widget), label->wrap);

    // Renvoyer un pointeur vers la structure Etiquette nouvellement cr��e
    return label;
}
Etiquette *labelfunction(Etiquette *lab ,FILE *F)
{
    gchar* elem;
    elem=(gchar*)g_malloc(sizeof(gchar)*50);
    gchar c;
    do
    {
        fscanf(F,"%s",elem);
        printf("%s\n",elem);
       if (strcmp(elem, "name") == 0) {
            if ((c = epurer_blan(F)) == '=') {
                if ((c = epurer_blan(F)) == '\"') {
                    int i = 0;
                    while ((c = fgetc(F)) != '\"')
                        lab->name[i++] = c;
                    lab->name[i] = '\0';
                }
            }
        } else if (strcmp(elem, "selectable") == 0) {
            if ((c = epurer_blan(F)) == '=')
               fscanf(F, "%d", &lab->selectable);
        } else if (strcmp(elem, "wrap") == 0) {
            if ((c = epurer_blan(F)) == '=') {
               fscanf(F, "%d", &lab->wrap);
            }
        }else if (strcmp(elem, "xligne") == 0) {
            if ((c = epurer_blan(F)) == '=') {
                fscanf(F, "%d", &lab->x);
            }
        }
        else if (strcmp(elem, "yligne") == 0) {
            if ((c = epurer_blan(F)) == '=') {
                fscanf(F, "%d", &lab->y);
            }
        }
    }while(strcmp(elem,">"));
    return lab;
}

Etiquette *creer_label(Etiquette *lab)
{
    lab->widget = style_texte(lab->widget, lab->text, 1);
    gtk_label_set_selectable(GTK_LABEL(lab->widget), lab->selectable);
    gtk_label_set_line_wrap(GTK_LABEL(lab->widget), lab->wrap);
    return lab;
}
Etiquette *add_label(FILE *F)
{
    Etiquette *lab=initialiser_label();
    lab=labelfunction(lab,F);
    lab->text=initialiser_texte();
    lab->text=textefunction(lab->text,F);
    lab=creer_label(lab);
    if(lab->text->h && lab->text->w)
            gtk_widget_set_size_request(lab->widget,lab->text->w,lab->text->h);
    return lab;

}



#endif // LABEL_H_INCLUDED
