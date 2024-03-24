#ifndef FIXED_H_INCLUDED
#define FIXED_H_INCLUDED

typedef struct {
    gchar* name;
    guint posx,posy;
    GtkWidget* fixed;
} fixed;


fixed* init_gtk_fixed()
{
    fixed* info =(fixed*)malloc(sizeof(fixed));
    if (!info) {
        g_print("Error: Failed to allocate memory for fixed\n");
        exit(-1);
    }
    info->name=(gchar*)malloc(sizeof(gchar)*30);
    info->name[0]='\0';
    info->posx=0;
    info->posy=0;
    return info;
}
fixed *fixedFunction(FILE* F,fixed* fix)
{
     int i;
    gchar* elem;
    elem=(gchar*)g_malloc(sizeof(gchar)*30);
    gchar c;
    do
    {
        fscanf(F,"%s",elem);
       if (strcmp(elem, "name") == 0)
        {
            if ((c = epurer_blan(F)) == '=')
                if ((c = epurer_blan(F)) == '\"')
                {
                     i= 0;
                    while ((c = fgetc(F)) != '\"')
                        fix->name[i++] = c;
                    fix->name[i] = '\0';
                }
        }else if (strcmp(elem, "posx") == 0)
        {
                if ((c = epurer_blan(F)) == '=')
                  fscanf(F, "%d", &fix->posx);
        }
        else if (strcmp(elem, "posy") == 0)
        {
                if ((c = epurer_blan(F)) == '=')
                  fscanf(F, "%d", &fix->posy);
        }

    }while(strcmp(elem,">"));
    return(fixed*) fix;
}

fixed *add_fixed(FILE* F,fixed* fix)
{
    fixed* f1=NULL;
    f1=init_gtk_fixed();
    f1=fixedFunction(F,f1);
    f1->fixed = gtk_fixed_new();
    
    return (fixed *)f1;
}

#endif // FIXED_H_INCLUDED
