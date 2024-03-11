#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NBC 100

#include "menu.h"
#include "window.h"
#include "boutton_normal.h"
#include "cocher.h"
#include "radio.h"
#include "spin_button.h"
#include "onglet.h"
#include "tool_bar.h"


void add_button(GtkWidget* fixed)
{
    boutton *myButton = init_button(NULL,"Click Me", FALSE, FALSE,10,50,"image.png");
    create_button(myButton, fixed,50,50);
}

void add_radio(GtkWidget* fixed)
{
    elem_radio *liste_radio = NULL;
    liste_radio = ajouter_radio_fin(liste_radio, "Option 1");
    liste_radio = ajouter_radio_fin(liste_radio, "Option 2");
    liste_radio = ajouter_radio_fin(liste_radio, "Option 3");
    radio *grouped_radio = grouper_radio(liste_radio, fixed);
    grouped_radio->fixed = fixed;
    create_radio(grouped_radio);
}

void add_cocher(GtkWidget* fixed)
{
    cocher *checkbox1 = init_cocher(fixed, "Check 1", 150, 50);
    cocher *checkbox2 = init_cocher(fixed, "Check 2", 150, 100);
    cocher *checkbox3 = init_cocher(fixed, "Check 3", 150, 150);
    gtk_fixed_put(fixed,checkbox1->boutcoche,checkbox1->x,checkbox1->y);
    gtk_fixed_put(fixed,checkbox2->boutcoche,checkbox2->x,checkbox2->y);
    gtk_fixed_put(fixed,checkbox3->boutcoche,checkbox3->x,checkbox3->y);
}

void add_spin(GtkWidget* fixed)
{
    // Initialize SpinButtonObject
    SpinButtonObject *spinButton = init_spin_button(0.0, 100.0, 5.0, 50.0, 30, 150, 1, 2, 1, 1, "#00ff00", 1.0);
    // Create SpinButton
    create_spin_button(spinButton);
    // Create a fixed widget to hold cocher buttons
    gtk_fixed_put(GTK_FIXED(fixed), spinButton->SpinButton, 450, 50); // Adjust position as needed
}


void add_menu(GtkWidget* Fixed1)
{
    menubar *maMenuBar = creer_menubar(0, Fixed1);
   gtk_fixed_put(GTK_FIXED(Fixed1), maMenuBar->menubar, 0, 0);
    menu *menu_file = init_menu_item(0, "File", TRUE);
    ajouter_menu(maMenuBar, menu_file);
    menu *menu_open = init_menu_item(0, "Open", FALSE);
    ajouter_menu_item(menu_file, menu_open,NULL);
    menu *menu_save = init_menu_item(1, "Save", FALSE);
    ajouter_menu_item(menu_file, menu_save, NULL);
    menu *menu_edit = init_menu_item(0, "Edit", TRUE);
    ajouter_menu(maMenuBar, menu_edit);
    menu *menu_cut = init_menu_item(1, "Cut", FALSE);
    ajouter_menu_item(menu_edit, menu_cut, NULL);
    menu *menu_copy = init_menu_item(1, "Copy", FALSE);
    ajouter_menu_item(menu_edit, menu_copy, NULL);
    menu *menu_paste = init_menu_item(1, "Paste", FALSE);
    ajouter_menu_item(menu_edit, menu_paste, NULL);
     menu *menu_S = init_menu_item(0, "Search", TRUE);
    ajouter_menu(maMenuBar, menu_S);
     menu *menu_B = init_menu_item(0, "Build", TRUE);
    ajouter_menu(maMenuBar, menu_B);
    menu *menu_D = init_menu_item(0, "Debug", TRUE);
    ajouter_menu(maMenuBar, menu_D);
     menu *menu_Set= init_menu_item(0, "Settings", TRUE);
    ajouter_menu(maMenuBar, menu_Set);
    menu *menu_Help = init_menu_item(0, "Help", TRUE);
    ajouter_menu(maMenuBar, menu_Help);
}

void add_onglet(GtkWidget* window,GtkWidget* fixed, gchar* label)
{
    GtkWidget *notebook = gtk_notebook_new();
    gtk_notebook_set_tab_pos(GTK_NOTEBOOK(notebook), GTK_POS_TOP); // Set tab position to the bottom
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), fixed, gtk_label_new(label));
    gtk_container_add(GTK_CONTAINER(window), notebook);
}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);
    Fenetre *ma_fenetre = initialiser_win("Instagram", NULL, "F1", "#f72585", 500, 500, 2, 0, 0, 25, TRUE);
    create_window(ma_fenetre);
    GtkFixed *fixed = GTK_FIXED(gtk_fixed_new());
    GtkFixed *Fixed1 = GTK_FIXED(gtk_fixed_new());


    add_button(fixed);
    add_cocher(fixed);
    add_radio(fixed);
    add_spin(fixed);
    add_onglet(ma_fenetre->window,fixed,"one");
    add_menu(Fixed1);
    add_onglet(ma_fenetre->window,Fixed1,"two");



    gtk_widget_show_all(ma_fenetre->window);
    gtk_main();

    return 0;
}



