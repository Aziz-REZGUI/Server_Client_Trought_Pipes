#include <gtk/gtk.h>
#include <stdio.h>
GtkLabel *mylabel; // Label
GtkWidget *app;    // Window
GtkBuilder *builder;
// GtkButton *btnS, *btnC;
GtkTextView *viewC, *viewS, *viewSP, *viewCP;

void server_btn()
{
    int f;
    f = fork();
    if (f == 0)
    {
        FILE *ptr;
        char out[500];
        char line[500] = "";

        // Opening file in reading mode
        ptr = fopen("STCP.txt", "r");

        if (NULL == ptr)
        {
            printf("file can't be opened \n");
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
        if (f > 0)
        {
            execlp("./serveur", NULL);

            // system("./serveur");
        }
        else
        {
            perror("fork problem ");
        }
    }
}

void client_btn(GtkWidget *widget, GtkBuilder *builder)
{
    int f;
    f = fork();
    if (f == 0)
    {
        FILE *ptr;
        char  out[500];
        char line[500] = "";

        // Opening file in reading mode
        ptr = fopen("CTCP.txt", "r");

        if (NULL == ptr)
        {
            printf("file can't be opened \n");
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
        if (f > 0)
        {
            // printf("test");
            execlp("./client", NULL);
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
    app = GTK_WIDGET(gtk_builder_get_object(builder, "window"));
    if (NULL == app)
    {
        /* Print out the error. You can use GLib's message logging  */
        fprintf(stderr, "Unable to file object with id \"Window1\" \n");
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

    return 0; // Necessary for a c main function
}
// Function to exit our app
void exit_app()
{
    printf("Exit app \n"); // Not neccesary
    gtk_main_quit();       // Command to quit a GTK program
}

// Function when our button is pressed
void clicked_np()
{
}
void clicked_btn()
{
    GtkWidget *window;
    GtkBuilder *builder2; // GTK Builder variable
    // system ("./serveur");
    builder2 = gtk_builder_new();                                 // Create GTK UI Builder
    gtk_builder_add_from_file(builder2, "interface.glade", NULL); // Load our UI file

    // Assign the Variables
    window = GTK_WIDGET(gtk_builder_get_object(builder2, "window"));
    if (NULL == window)
    {
        /* Print out the error. You can use GLib's message logging  */
        fprintf(stderr, "Unable to file object with id \"Window2\" \n");
        /* Your error handling code goes here */
    }
    gtk_widget_show_all(window);
    gtk_main();
}
