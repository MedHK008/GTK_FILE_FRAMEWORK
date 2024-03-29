#include "headers.h"


int main(int argc, char *argv[]) {
    debut_programme(argc,argv);
    Fenetre* ma_fenetre=add_window("ma fenetre","gtklogo.png","window","#000000",3840,2160,GTK_WIN_POS_CENTER,-1,-1,5,TRUE);
    ///matqissch hadchi li qbel had lcomment

    GtkWidget *notebook = exemple();
    // Afficher la fenêtre principale
    add_to_window(notebook,ma_fenetre->window);
    gtk_widget_show_all(ma_fenetre->window);
    fin_programme(ma_fenetre);
    return 0;
}



