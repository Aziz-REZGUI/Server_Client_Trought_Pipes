#include <gtk/gtk.h>

#include "include/serv_cli_fifo.h"
GtkLabel *mylabel; // Label
GtkWidget *app;    // Window
GtkBuilder *builder;
// GtkButton *btnS, *btnC;
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

        // Opening file in reading mode
        ptr = fopen("CPIPE.txt", "r");

        if (NULL == ptr)
        {
            printf("file CPIPE.txt can't be opened \n");
            exit(1);
        }

        // printf("content of this file are \n");

        // Printing what is written in file
        // character by character using loop.
        // // out = "";
        while (fgets(line, 500, ptr) != NULL)
        {
            // printf("%s\n", line);
            strcat(out, line);
        }
        // out = ch;
        // Closing the file
        fclose(ptr);
        // g_print("test");
        GtkTextBuffer *buffer = gtk_text_buffer_new(NULL);
        GtkTextIter iter;
        gtk_text_buffer_get_iter_at_offset(buffer, &iter, 0);
        gtk_text_view_set_buffer(viewCP, buffer);
        gtk_text_buffer_insert(buffer, &iter, out, -1);

        serverP();
        // GtkTextView *view = (GtkTextView *)gtk_builder_get_object(builder, "TV_CTCP");
        // // GtkEntry* entry = (GtkEntry*) gtk_builder_get_object (builder,"entry1");
        // // input = gtk_entry_get_text(entry);

        // gtk_text_view_set_buffer(view, buffer);
        // gtk_text_view_set_buffer(view, 't');
    }
    else
    {
        if (f == 0)
        {
            // printf("test");
            execlp("./clientP", (char *)NULL);
            // system("./client");
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

        // Opening file in reading mode
        ptr = fopen("SPIPE.txt", "r");

        if (NULL == ptr)
        {
            printf("file SPIPE.txt can't be opened \n");
            exit(1);
        }

        // printf("content of this file are \n");

        // Printing what is written in file
        // character by character using loop.
        // // out = "";
        while (fgets(line, 500, ptr) != NULL)
        {
            // printf("%s\n", line);
            strcat(out, line);
        }
        // out = ch;
        // Closing the file
        fclose(ptr);
        // g_print("test");
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

            // system("./serveur");
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

        // Opening file in reading mode
        ptr = fopen("STCP.txt", "r");

        if (NULL == ptr)
        {
            printf("file STCP.txt can't be opened \n");
            exit(1);
        }

        // printf("content of this file are \n");

        // Printing what is written in file
        // character by character using loop.
        // // out = "";
        while (fgets(line, 500, ptr) != NULL)
        {
            // printf("%s\n", line);
            strcat(out, line);
        }
        // out = ch;
        // Closing the file
        fclose(ptr);
        // g_print("test");
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

            // system("./serveur");
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

        // Opening file in reading mode
        ptr = fopen("CTCP.txt", "r");

        if (NULL == ptr)
        {
            printf("file CTCP.txt can't be opened \n");
            exit(1);
        }

        // printf("content of this file are \n");

        // Printing what is written in file
        // character by character using loop.
        // // out = "";
        while (fgets(line, 500, ptr) != NULL)
        {
            // printf("%s\n", line);
            strcat(out, line);
        }
        // out = ch;
        // Closing the file
        fclose(ptr);
        // g_print("test");
        GtkTextBuffer *buffer = gtk_text_buffer_new(NULL);
        GtkTextIter iter;
        gtk_text_buffer_get_iter_at_offset(buffer, &iter, 0);
        gtk_text_view_set_buffer(viewC, buffer);
        gtk_text_buffer_insert(buffer, &iter, out, -1);
        server_btn();
        // GtkTextView *view = (GtkTextView *)gtk_builder_get_object(builder, "TV_CTCP");
        // // GtkEntry* entry = (GtkEntry*) gtk_builder_get_object (builder,"entry1");
        // // input = gtk_entry_get_text(entry);

        // gtk_text_view_set_buffer(view, buffer);
        // gtk_text_view_set_buffer(view, 't');
    }
    else
    {
        if (f == 0)
        {
            // printf("test");
            execlp("./clientSK", (char *)NULL);
            // system("./client");
        }
        else
        {
            perror("fork problem ");
        }
    }
}
// Main function
int main(int argc, char *argv[])
{

    // Window

    // Variables

    gtk_init(&argc, &argv); // Start GTK

    builder = gtk_builder_new();                                 // Create GTK UI Builder
    gtk_builder_add_from_file(builder, "interface.glade", NULL); // Load our UI file

    // Assign the Variables
    app = GTK_WIDGET(gtk_builder_get_object(builder, "menu"));
    if (NULL == app)
    {
        /* Print out the error. You can use GLib's message logging  */
        fprintf(stderr, "Unable to file object with id \"menu\" \n");
        /* Your error handling code goes here */
    }
    // mylabel = GTK_LABEL(gtk_builder_get_object(builder, "lbc")); // Load our label named MyLabel
    //  Essential for a GTK based program
    //  GtkTextView *view = (GtkTextView *)gtk_builder_get_object(builder, "TV_CTCP");
    //  gtk_text_view_set_buffer(view, 't');
    // printf("test");

    // viewC = GTK_TEXT_VIEW(gtk_builder_get_object(builder, "TV_CTCP"));
    // viewS = GTK_TEXT_VIEW(gtk_builder_get_object(builder, "TV_STCP"));
    // g_signal_connect(btnC, "clicked", G_CALLBACK(client_btn), NULL);
    gtk_builder_connect_signals(builder, NULL);
    // g_signal_connect(btnC, "clicked", G_CALLBACK(client_btn), NULL);
    g_object_unref(builder);

    gtk_widget_show_all(app); // Show our window

    gtk_main(); // Run our program

    return 0; // Necessary for a c main function
}
// Function to exit our app
void exit_app()
{
    printf("Exit app \n");
    kill(getpid(), SIGKILL);
    // Not neccesary
    gtk_main_quit(); // Command to quit a GTK program
}

// Function when our button is pressed
void tube()
{
    gtk_widget_destroy(app);
    builder = gtk_builder_new();                                 // Create GTK UI Builder
    gtk_builder_add_from_file(builder, "interface.glade", NULL); // Load our UI file

    app = GTK_WIDGET(gtk_builder_get_object(builder, "windowP"));
    if (NULL == app)
    {
        /* Print out the error. You can use GLib's message logging  */
        fprintf(stderr, "Unable to file object with id \"windowP\" \n");
        /* Your error handling code goes here */
    }
    // mylabel = GTK_LABEL(gtk_builder_get_object(builder, "lbc")); // Load our label named MyLabel
    //  Essential for a GTK based program
    //  GtkTextView *view = (GtkTextView *)gtk_builder_get_object(builder, "TV_CTCP");
    //  gtk_text_view_set_buffer(view, 't');
    // printf("test");

    viewCP = GTK_TEXT_VIEW(gtk_builder_get_object(builder, "TV_CP"));
    viewSP = GTK_TEXT_VIEW(gtk_builder_get_object(builder, "TV_SP"));
    // g_signal_connect(btnC, "clicked", G_CALLBACK(client_btn), NULL);
    gtk_builder_connect_signals(builder, NULL);
    // g_signal_connect(btnC, "clicked", G_CALLBACK(client_btn), NULL);
    g_object_unref(builder);

    gtk_widget_show_all(app); // Show our window

    gtk_main(); // Run our program
}
void sock()
{
    gtk_widget_destroy(app);
    builder = gtk_builder_new(); // Create GTK UI Builder
    gtk_builder_add_from_file(builder, "interface.glade", NULL);
    app = GTK_WIDGET(gtk_builder_get_object(builder, "window"));
    if (NULL == app)
    {
        /* Print out the error. You can use GLib's message logging  */
        fprintf(stderr, "Unable to file object with id \"window\" \n");
        /* Your error handling code goes here */
    }
    // mylabel = GTK_LABEL(gtk_builder_get_object(builder, "lbc")); // Load our label named MyLabel
    //  Essential for a GTK based program
    //  GtkTextView *view = (GtkTextView *)gtk_builder_get_object(builder, "TV_CTCP");
    //  gtk_text_view_set_buffer(view, 't');
    // printf("test");

    viewC = GTK_TEXT_VIEW(gtk_builder_get_object(builder, "TV_CTCP"));
    viewS = GTK_TEXT_VIEW(gtk_builder_get_object(builder, "TV_STCP"));
    // g_signal_connect(btnC, "clicked", G_CALLBACK(client_btn), NULL);
    gtk_builder_connect_signals(builder, NULL);
    // g_signal_connect(btnC, "clicked", G_CALLBACK(client_btn), NULL);
    g_object_unref(builder);

    gtk_widget_show_all(app); // Show our window

    gtk_main(); // Run our program
}
