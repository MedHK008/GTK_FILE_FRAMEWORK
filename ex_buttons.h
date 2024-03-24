#ifndef EX_BUTTONS_H_INCLUDED
#define EX_BUTTONS_H_INCLUDED

GtkWidget* exemple()
{
    FILE* F=fopen("reader.txt","r");
    GtkWidget *notebook = gtk_notebook_new();

    /****************************************************** les bouttons***********************************/

    fixed* fixed0=init_gtk_fixed("fixed0");
    lire_fichier(F,fixed0);
    add_onglet(notebook,fixed0->fixed,"onglet 0","#FFFFFF");

    /***********************************************les bouttons fin*****************************************/
    return ((GtkWidget*)notebook);
}
#endif // EX_BUTTONS_H_INCLUDED
