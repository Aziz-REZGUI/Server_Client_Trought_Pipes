#include <gtk/gtk.h>
#include <stdio.h>
GtkLabel *mylabel;   // Label
GtkWidget *app;      // Window
GtkBuilder *builder; // GTK Builder variable

// Main function
int main(int argc, char *argv[])
{
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
    mylabel = GTK_LABEL(gtk_builder_get_object(builder, "lbc")); // Load our label named MyLabel
    // Essential for a GTK based program
    gtk_builder_connect_signals(builder, NULL);
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
    GtkLabel *mylabel2;
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
    mylabel2 = GTK_LABEL(gtk_builder_get_object(builder2, "lbc")); // Load our label named MyLabel
    gtk_widget_show_all(window);
    gtk_main();
}
void client_btn()
{
    int f;
    f = fork();
    if (f == 0)
    {
        system("./client");
    }
}
void server_btn()
{
    int f;
    f = fork();
    if (f == 0)
    {
        system("./serveur");
    }
}