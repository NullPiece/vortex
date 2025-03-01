#include<gtk-3.0/gtk/gtk.h>
#include <gtk-3.0/gtk/gtktypes.h>
#include <glib-2.0/glib/gtypes.h>
#include <gtk-3.0/gtk/gtkapplication.h>
#include<stdio.h>
#include<stdlib.h>

static void on_activate(GtkApplication *app, gpointer user_data) {
    GtkWidget *window;
    GtkWidget *label;

    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Papa App");
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 200);

    label = gtk_label_new("PAPA HU PAPA, TERA PAPA🫵");

    gtk_container_add(GTK_CONTAINER(window), label);

    gtk_widget_show_all(window);
}

int main(int argc, char **argv) {
    GtkApplication *app;
    int status;

    app = gtk_application_new("com.example.HelloWorld", G_APPLICATION_DEFAULT_FLAGS);

    g_signal_connect(app, "activate", G_CALLBACK(on_activate), NULL);

    status = g_application_run(G_APPLICATION(app), argc, argv);

    g_object_unref(app);

    return status;
}