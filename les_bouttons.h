#ifndef LES_BOUTTONS_H_INCLUDED
#define LES_BOUTTONS_H_INCLUDED


#include "boutton_normal.h"
#include "cocher.h"
#include "radio.h"
#include "spin_button.h"

void add_buttons()
{
    /****************************************************** les bouttons***********************************/


    /******************************************************boutton normal***********************************/
    /// les parametres : le fixed , le label du button , path de l'image utiliser (NULL s'il y a pas d'image),height,width,bgcolor, x , y
        add_label(fixed,txt_button,TRUE,FALSE,50,50);
        add_button(fixed,"first","gtklogo.png",100,100,"#FF0000",50,100,50,50);
        add_button(fixed,NULL,"gtklogo.png",100,100,"#FF0000",290,100,150,150);
    /******************************************************boutton normal***********************************/




    /****************************************************** les cochers***********************************/
    /// les parametres : le fixed , le label , le x , le y ,le bgcolor, si le checkbox est cocher dès le début ou non
        add_label(fixed,txt_cocher,TRUE,FALSE,50,250);
        add_cocher(fixed,"testing cocher1",200,300,"#FFFFFF",TRUE);
        add_cocher(fixed,"testing cocher2",200,330,"#FFFFFF",TRUE);
        add_cocher(fixed,"testing cocher3",200,360,"#FFFFFF",TRUE);
        add_cocher(fixed,"testing cocher4",200,390,"#FFFFFF",TRUE);
    /****************************************************** les cochers***********************************/



    /****************************************************** les radios***********************************/
    /// les parametres : le fixed  , le x , le y , les labels,le bgcolor de chaque button, le radio qui soit cocher dès le début (all FALSE signifie que aucun ne sera cocher)
        add_label(fixed,txt_radio,TRUE,FALSE,50,450);
        char *labels2[NB_RADIO] = {"Option 1", "Option 2", "Option 3"};
        char *colors2[NB_RADIO] = {"#FFFFFF", "#FFFFFF", "#FFFFFF"};
        gboolean checked2[NB_RADIO] = {FALSE, FALSE, FALSE};
        add_radio(fixed, NB_RADIO,250,500, labels2, colors2,checked2);
    /****************************************************** les radios***********************************/


    /****************************************************** les spins***********************************/
    ///khdem biha wskot mafiya li ykteb lcommentaire db
        add_label(fixed,txt_spin,TRUE,FALSE,50,600);
        add_spin(fixed, 50, 650, 0.0, 100.0, 1.0, 1.0, 30, 150, 1, 2, 1, 1, "#00ff00", 1.0);
        add_spin(fixed, 250, 650, 0.0, 100.0, 50.0, 5.0, 30, 30, 1, 2, 1, 1, "#ff0000", 1.0);
        add_spin(fixed, 450, 650, 0.0, 100.0, 100.0, 100.0, 50, 150, 1, 2, 1, 1, "#ffffff", 1.0);
        add_onglet(notebook,fixed,"onglet 1","#FF00FF");
    /****************************************************** les spins***********************************/


    /***********************************************les bouttons fin*****************************************/
}
#endif // LES_BOUTTONS_H_INCLUDED
