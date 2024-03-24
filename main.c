#include "headers.h"



int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    // Créer une fenêtre principale
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Test Boîte de Dialogue");
    gtk_window_set_default_size(GTK_WINDOW(window), 1000, 2000);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    fixed *fix=init_gtk_fixed("hello");

    gtk_container_add(GTK_CONTAINER(window),fix->fixed);
    FILE*F=fopen("reader.txt","r");
    BoiteDialogue*bd=lire_fichier(F,fix);
    bd->parent=window;
    GtkWidget *bouton_test = gtk_button_new_with_label("Cliquez ici");
    gtk_fixed_put(GTK_FIXED(fix->fixed),bouton_test,50,50);
    g_signal_connect(bouton_test, "clicked", G_CALLBACK(on_button_clicked),bd->dialogue);



    // Afficher la fenêtre principale
    gtk_widget_show_all(window);

    gtk_main();
    return 0;
}

// Fonction pour gérer le clic sur le bouton



