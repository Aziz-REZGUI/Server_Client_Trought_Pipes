#include <gtk/gtk.h>

#include "include/serv_cli_fifo.h"
GtkLabel *mylabel; // Label
GtkWidget *app;    // Window
GtkBuilder *builder;
GtkTextView *viewC, *viewS, *viewSP, *viewCP;
int test = 1;

void retour()
{
    gtk_widget_destroy(app);
    main();
}
void clientP()
{
    int f;
    f = fork();
    if (f > 0)
    {
        FILE *ptr;
        char out[500];
        char line[500] = "";

        ptr = fopen("CPIPE.txt", "r");

        if (NULL == ptr)
        {
            printf("file CPIPE.txt can't be opened \n");
            exit(1);
        }

        while (fgets(line, 500, ptr) != NULL)
        {
            strcat(out, line);
        }
     
        fclose(ptr);
        
        GtkTextBuffer *buffer = gtk_text_buffer_new(NULL);
        GtkTextIter iter;
        gtk_text_buffer_get_iter_at_offset(buffer, &iter, 0);
        gtk_text_view_set_buffer(viewCP, buffer);
        gtk_text_buffer_insert(buffer, &iter, out, -1);

        serverP();
        
    }
    else
    {
        if (f == 0)
        {
            execlp("./clientP", (char *)NULL);
        }
        else
        {
            perror("fork problem ");
        }
    }
}
void serverP()
{
    int f;
    f = fork();
    if (f > 0)
    {
        FILE *ptr;
        char out[500];
        char line[500] = "";

        ptr = fopen("SPIPE.txt", "r");

        if (NULL == ptr)
        {
            printf("file SPIPE.txt can't be opened \n");
            exit(1);
        }

     
        while (fgets(line, 500, ptr) != NULL)
        {
            strcat(out, line);
        }
      
        fclose(ptr);
        GtkTextBuffer *buffer = gtk_text_buffer_new(NULL);
        GtkTextIter iter;
        gtk_text_buffer_get_iter_at_offset(buffer, &iter, 0);
        gtk_text_view_set_buffer(viewSP, buffer);
        gtk_text_buffer_insert(buffer, &iter, out, -1);
    }
    else
    {
        if (f == 0)
        {

            execlp("./serveurP", (char *)NULL);

        }
        else
        {
            perror("fork problem ");
        }
    }
}

void server_btn()
{
    int f;
    f = fork();
    if (f > 0)
    {
        FILE *ptr;
        char out[500];
        char line[500] = "";

        ptr = fopen("STCP.txt", "r");

        if (NULL == ptr)
        {
            printf("file STCP.txt can't be opened \n");
            exit(1);
        }

        while (fgets(line, 500, ptr) != NULL)
        {
            strcat(out, line);
        }
        
        fclose(ptr);
        GtkTextBuffer *buffer = gtk_text_buffer_new(NULL);
        GtkTextIter iter;
        gtk_text_buffer_get_iter_at_offset(buffer, &iter, 0);
        gtk_text_view_set_buffer(viewS, buffer);
        gtk_text_buffer_insert(buffer, &iter, out, -1);
    }
    else
    {
        if (f == 0)
        {

            execlp("./serveurSK", (char *)NULL);

        }
        else
        {
            perror("fork problem ");
        }
    }
}

void client_btn()
{
    int f;
    f = fork();
    if (f > 0)
    {
        FILE *ptr;
        char out[500];
        char line[500] = "";

        ptr = fopen("CTCP.txt", "r");

        if (NULL == ptr)
        {
            printf("file CTCP.txt can't be opened \n");
            exit(1);
        }

     
        while (fgets(line, 500, ptr) != NULL)
        {
            strcat(out, line);
        }
      
        fclose(ptr);
        GtkTextBuffer *buffer = gtk_text_buffer_new(NULL);
        GtkTextIter iter;
        gtk_text_buffer_get_iter_at_offset(buffer, &iter, 0);
        gtk_text_view_set_buffer(viewC, buffer);
        gtk_text_buffer_insert(buffer, &iter, out, -1);
        server_btn();

    }
    else
    {
        if (f == 0)
        {
            execlp("./clientSK", (char *)NULL);
        }
        else
        {
            perror("fork problem ");
        }
    }
}
int main(int argc, char *argv[])
{



    gtk_init(&argc, &argv);

    builder = gtk_builder_new();                                
    gtk_builder_add_from_file(builder, "interface.glade", NULL); 
    app = GTK_WIDGET(gtk_builder_get_object(builder, "menu"));
    if (NULL == app)
    {
        
        fprintf(stderr, "Unable to file object with id \"menu\" \n");
      
    }
   
    gtk_builder_connect_signals(builder, NULL);
 
    g_object_unref(builder);

    gtk_widget_show_all(app); 

    gtk_main(); 

    return 0;
}


void tube()
{
    gtk_widget_destroy(app);
    builder = gtk_builder_new();                                 
    gtk_builder_add_from_file(builder, "interface.glade", NULL); 

    app = GTK_WIDGET(gtk_builder_get_object(builder, "windowP"));
    if (NULL == app)
    {
        fprintf(stderr, "Unable to file object with id \"windowP\" \n");
    }


    viewCP = GTK_TEXT_VIEW(gtk_builder_get_object(builder, "TV_CP"));
    viewSP = GTK_TEXT_VIEW(gtk_builder_get_object(builder, "TV_SP"));
    gtk_builder_connect_signals(builder, NULL);
    g_object_unref(builder);

    gtk_widget_show_all(app); 
    gtk_main(); 
}
void sock()
{
    gtk_widget_destroy(app);
    builder = gtk_builder_new(); 
    gtk_builder_add_from_file(builder, "interface.glade", NULL);
    app = GTK_WIDGET(gtk_builder_get_object(builder, "window"));
    if (NULL == app)
    {
        
        fprintf(stderr, "Unable to file object with id \"window\" \n");
       
    }
   


    viewC = GTK_TEXT_VIEW(gtk_builder_get_object(builder, "TV_CTCP"));
    viewS = GTK_TEXT_VIEW(gtk_builder_get_object(builder, "TV_STCP"));
    gtk_builder_connect_signals(builder, NULL);
    g_object_unref(builder);

    gtk_widget_show_all(app); 

    gtk_main();
}
