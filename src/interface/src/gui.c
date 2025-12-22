#include <gtk-4.0/gtk/gtk.h>

static void app_main(GtkApplication *app, gpointer user_data)
{
    GtkWidget *window;
    GtkWidget *box;

    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW (window), "Emulator");
    gtk_window_set_default_size(GTK_WINDOW (window), 640, 512);
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);

    box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_widget_set_halign(box, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(box, GTK_ALIGN_CENTER);
    gtk_window_set_child (GTK_WINDOW (window), box);


    gtk_window_present(GTK_WINDOW (window));
}

int main(int argc, char **argv)
{
    GtkApplication *app;
    int status;
    
    app = gtk_application_new("org.qwystal.Amiga3000", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK (app_main), NULL);
    status = g_application_run(G_APPLICATION (app), argc, argv);
    g_object_unref(app);
    
    return status;
}