<<<<<<< Updated upstream
#ifndef EX_BUTTONS_H_INCLUDED
#define EX_BUTTONS_H_INCLUDED

GtkWidget* exemple()
{
    FILE* F=fopen("reader.txt","r");
    GtkWidget *notebook = gtk_notebook_new();

=======
#ifndef EX_BUTTONS_H_INCLUDED
#define EX_BUTTONS_H_INCLUDED

GtkWidget* exemple()
{
    FILE* F=fopen("reader.txt","r");

>>>>>>> Stashed changes
    /****************************************************** les bouttons***********************************/

    fixed* fixed0=init_gtk_fixed("fixed0");
<<<<<<< Updated upstream
    lire_fichier(F,fixed0);
    add_onglet(notebook,fixed0->fixed,"onglet 0","#FFFFFF");

    /***********************************************les bouttons fin*****************************************/
    return ((GtkWidget*)notebook);
}
#endif // EX_BUTTONS_H_INCLUDED
=======
    lire_fichier(F,fixed0);

    /***********************************************les bouttons fin*****************************************/
    return ((GtkWidget*)fixed0->fixed);
}
#endif // EX_BUTTONS_H_INCLUDED
>>>>>>> Stashed changes
