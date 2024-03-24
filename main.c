#include "headers.h"


//void on_button_clicked(GtkWidget *widget, gpointer data) {
//    // Créer une boîte de dialogue avec vos fonctions
//    BoiteDialogue *dialogue = Add_boite_dialogue(GTK_WINDOW(data), "Boîte de Dialogue", "", TRUE, 300, 300, 0, "#FFFFFF");
//
//    // Créer deux boutons à ajouter à la boîte de dialogue
//    GtkWidget *button1 = gtk_button_new_with_label("Bouton 1");
//    GtkWidget *button2 = gtk_button_new_with_label("Bouton 2");
//
//    // Ajouter les boutons à la boîte de dialogue
//    ajouter_a_boite_dialogue(dialogue, button1, 50, 50);
//    ajouter_a_boite_dialogue(dialogue, button2, 150, 50);
//
//    // Ajouter les actions pour les boutons
//    ajouter_action_a_boite_dialogue(dialogue, button1, GTK_RESPONSE_OK);
//    ajouter_action_a_boite_dialogue(dialogue, button2, GTK_RESPONSE_CANCEL);
//
//    // Afficher la boîte de dialogue
//    gtk_widget_show_all(dialogue->dialogue);
//}

// Inclure le fichier d'en-tête contenant vos fonctions

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
    lire_fichier(F,fix);


    // Afficher la fenêtre principale
    gtk_widget_show_all(window);

    gtk_main();
    return 0;
}

// Fonction pour gérer le clic sur le bouton



