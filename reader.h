#ifndef READER_H_INCLUDED
#define READER_H_INCLUDED
#define MAX 100

///g_signal_connect(button, "clicked", G_CALLBACK(on_button_clicked), NULL);
///g_signal_connect(button, "pressed", G_CALLBACK(on_button_pressed), NULL);
///g_signal_connect(button, "released", G_CALLBACK(on_button_released), NULL);
///g_signal_connect(quit_button, "clicked", G_CALLBACK(on_quit_button_clicked), NULL);
void on_button_clicked(GtkWidget *widget, gpointer data) {
    const gchar *label = gtk_button_get_label(GTK_BUTTON(widget));
    g_print("Button '%s' clicked!\n", label);
}

void on_button_pressed(GtkWidget *widget, gpointer data) {
    const gchar *label = gtk_button_get_label(GTK_BUTTON(widget));
    g_print("Button '%s' pressed!\n", label);
}

void on_button_released(GtkWidget *widget, gpointer data) {
    const gchar *label = gtk_button_get_label(GTK_BUTTON(widget));
    g_print("Button '%s' released!\n", label);
}

void on_quit_button_clicked(GtkWidget *widget, gpointer data) {
    g_print("\nQuitting the program!\n");
    gtk_main_quit();
}

void add_to_parent(GtkWidget* child,GtkWidget* parent_w, gchar* parent,guint posx, guint posy)
{
  if(!strcmp(parent,"/fixed"))
    gtk_fixed_put(GTK_FIXED(parent_w),child,posx,posy);
 else if(!strcmp(parent,"/box"))
    gtk_box_pack_start(GTK_BOX(parent_w),child,FALSE,TRUE,0);
 else if(!strcmp(parent,"/window"))
    gtk_container_add(GTK_CONTAINER(parent_w),child);

}
void lire_fichier(FILE*F,Fenetre* W,GtkWidget* parent_w , gchar* parent_token,Boite_message*BM)
{
    gchar c ;
    gchar current_token[MAX];
    Token tok;
    int into=0;
    c=epurer_blan(F);
    ButtonSimple *Button_dial;
    GtkWidget* radiopar = gtk_radio_button_new(NULL);
    while(c!=EOF)
    {
        if(c=='<')
        {
            fscanf(F, "%s", current_token);
            printf("\n%s",current_token);
            if (!strcmp(current_token , parent_token))
            {
                if(!(strcmp(current_token,"/root")))
                {
                    gtk_widget_show_all(W->window);
                    if(W->svt)
                       gtk_widget_show_all(W->svt->window);
                    fin_programme(W);
                }
                c=epurer_blan(F);
                return ;
            }
            tok=string_to_token(current_token);
            switch(tok)
            {
                case Root:
                            c=epurer_blan(F);
                            c=epurer_blan(F);
                            break;

                case fenetre:
                            if(W->window)
                            {
                                W->svt=add_window(F);
                                W->svt->svt=NULL;
                                if(!W->scroll_bool) lire_fichier(F,W->svt,W->svt->window,"/window",BM);
                                else lire_fichier(F,W->svt,W->svt->scrollwin,"/window",BM);
                                c=epurer_blan(F);
                            }
                            else
                            {
                                W=add_window(F);
                                if(!W->scroll_bool)
                                     lire_fichier(F,W,W->window,"/window",BM);
                                else
                                    lire_fichier(F,W,W->scrollwin,"/window",BM);
                                printf("\nsortie F");
                                c=epurer_blan(F);
                            }
                            break;
                case Fixed:
                            fixed* fix=add_fixed(F,fix);
                            add_to_parent(fix->fixed,parent_w,parent_token,fix->posx,fix->posy);
                            lire_fichier(F,W,fix->fixed,"/fixed",BM);
                            free(fix);
                            c=epurer_blan(F);
                            break;
                case Label:
                            Etiquette *lab= add_label(F);
                            add_to_parent(lab->widget,parent_w,parent_token,lab->x,lab->y);
                            free(lab);
                            c=epurer_blan(F);
                            break;
                case Entry:
                            Saisie* E=Add_Entry(F);
                            add_to_parent(E->entree,parent_w,parent_token,E->x_pos,E->y_pos);
                            free(E);
                            c=epurer_blan(F);
                            break;
                case Button:
                            ButtonSimple* B=add_button(F);
                            add_to_parent(B->button,parent_w,parent_token,B->x_pos,B->y_pos);
                            switch(B->signal)
                            {
                            case 1:
                                    g_signal_connect(B->button, "clicked", G_CALLBACK(on_button_clicked), NULL);
                                    break;
                            case 2:
                                    g_signal_connect(B->button, "pressed", G_CALLBACK(on_button_pressed), NULL);
                                    break;
                            case 3:
                                    g_signal_connect(B->button, "released", G_CALLBACK(on_button_released), NULL);
                                    break;
                            case 4:
                                    g_signal_connect(B->button, "clicked", G_CALLBACK(on_quit_button_clicked), NULL);
                                    break;
                            default:
                                    break;
                            }
                            load_css();
                            free(B);
                            c=epurer_blan(F);
                            break;
                case button_dialogue :
                            ButtonSimple*Button_dial=add_button(F);
                            add_to_parent(Button_dial->button,parent_w,parent_token,Button_dial->x_pos,Button_dial->y_pos);
                            g_signal_connect(Button_dial->button,"clicked",G_CALLBACK(on_button_clicked_Boite_Message),BM->message_box);
                            c=epurer_blan(F);
                            break;
                case Radio:
                            elem_radio* R = add_radio(F, fix, radiopar);
                            if (R)
                            {
                                add_to_parent(R->pRadio,parent_w,parent_token,R->x_pos,R->y_pos);
                                switch(R->signal)
                                {
                                case 1:
                                        g_signal_connect(R->pRadio, "clicked", G_CALLBACK(on_button_clicked), NULL);
                                        break;
                                case 2:
                                        g_signal_connect(R->pRadio, "pressed", G_CALLBACK(on_button_pressed), NULL);
                                        break;
                                case 3:
                                        g_signal_connect(R->pRadio, "released", G_CALLBACK(on_button_released), NULL);
                                        break;
                                case 4:
                                        g_signal_connect(R->pRadio, "clicked", G_CALLBACK(on_quit_button_clicked), NULL);
                                        break;
                                default:
                                        break;
                                }
                                free(R);
                            }
                            c=epurer_blan(F);
                            break;
                case Checkbox:
                            cocher* C = add_cocher(F);
                            add_to_parent(C->boutcoche,parent_w,parent_token,C->x_pos,C->y_pos);
                            switch(C->signal)
                            {
                            case 1:
                                    g_signal_connect(C->boutcoche, "clicked", G_CALLBACK(on_button_clicked), NULL);
                                    break;
                            case 2:
                                    g_signal_connect(C->boutcoche, "pressed", G_CALLBACK(on_button_pressed), NULL);
                                    break;
                            case 3:
                                    g_signal_connect(C->boutcoche, "released", G_CALLBACK(on_button_released), NULL);
                                    break;
                            case 4:
                                    g_signal_connect(C->boutcoche, "clicked", G_CALLBACK(on_quit_button_clicked), NULL);
                                    break;
                            default:
                                    break;
                            }
                            free(C);
                            c=epurer_blan(F);
                            break;
                case Combobox:
                            ComboBox* CB=add_comboBox(parent_w,F);
                            combobox_add(CB,F);
                            add_to_parent(CB->comboBox,parent_w,parent_token,CB->posx,CB->posy);
                            free(CB);
                            c=epurer_blan(F);
                            break;
                case Frame:
                            frame *fr=add_frame(parent_w,F);
                            lire_son_elem(fr,F,W);
                            free(fr);
                            c=epurer_blan(F);
                            break;
                case Image:
                            image *img=add_image(F);
                            add_to_parent(img->widget,parent_w,parent_token,img->x,img->y);
                            free(img);
                            c=epurer_blan(F);
                            break;
                case ProgBar:
                            barre_prog *prog_bar=add_progress_bar(F);
                            add_to_parent(prog_bar->parent,parent_w,parent_token,prog_bar->x,prog_bar->y);
                            free(prog_bar);
                            c=epurer_blan(F);
                            break;
                 case spB:
                            SpinButton* spB=add_spin_button_from_file(F);
                            add_to_parent(spB->SpinButton,parent_w,parent_token,spB->posx,spB->posy);
                            switch(spB->signal)
                            {
                            case 1:
                                    g_signal_connect(spB->SpinButton, "clicked", G_CALLBACK(on_button_clicked), NULL);
                                    break;
                            case 2:
                                    g_signal_connect(spB->SpinButton, "pressed", G_CALLBACK(on_button_pressed), NULL);
                                    break;
                            case 3:
                                    g_signal_connect(spB->SpinButton, "released", G_CALLBACK(on_button_released), NULL);
                                    break;
                            case 4:
                                    g_signal_connect(spB->SpinButton, "clicked", G_CALLBACK(on_quit_button_clicked), NULL);
                                    break;
                            default:
                                    break;
                            }
                            free(spB);
                            c=epurer_blan(F);
                            break;
                case ToolBar:
                            toolbar *tbar=add_toolbar(F);
                            lire_son_item(tbar ,F);
                            gtk_box_pack_start(GTK_BOX(parent_w),tbar->widget,TRUE,FALSE,0);
                            free(tbar);
                            c=epurer_blan(F);
                            break;
                case Box:
                            box * bx=NULL;
                            bx=add_box(F);
                            add_to_parent(bx->box,parent_w,parent_token,bx->posx,bx->posy);
                            lire_fichier(F,W,bx->box,"/box",BM);
                            free(bx);
                            c=epurer_blan(F);
                            break;
                case MenuBar:
                            menubar *mbar =add_menubar(mbar,F);
                            ajouter_elems(mbar,F);
                            add_to_parent(mbar->menubar,parent_w,parent_token,mbar->posx,mbar->posy);
                            free(mbar);
                            c=epurer_blan(F);
                            break;
                default:
                            break;
            }
        }
        else return;
    }
}

Boite_message*ajouter_to_boite_message_fichier(FILE*F,Boite_message*BM)
{
    gchar c;
    gchar elem[50];
    gchar att[50];
    int i ;
    Token tok;
    c=epurer_blan(F);

    while(c!=EOF)
    {
        if(c=='<')
        {

            fscanf(F,"%s",elem);
            printf("\nwidget---->%s\n",elem);
            tok=string_to_token(elem);
            switch(tok)
            {
                case Entry:
                       Saisie* E=Add_Entry(F);
                        ajouter_to_boite_message(BM,E->entree,E->x_pos,E->y_pos);
                        c=epurer_blan(F);
                        break;
                case Button:
                        ButtonSimple* B=add_button(F);
                       ajouter_to_boite_message(BM,B->button,B->x_pos,B->y_pos);
                        c=epurer_blan(F);
                        break;
                 case Label:
                       Etiquette *lab= add_label(F);
                        ajouter_to_boite_message(BM,lab->widget,lab->x,lab->y);
                       c=epurer_blan(F);
                       break;
            }
        }

    }
    return(Boite_message*)(BM);



}


#endif // READER_H_INCLUDED
