#include "main.h"

typedef struct {
    float x;
    float y;
} m_pos;

m_pos m_coordinates = {0.0, 0.0};

GtkWidget *two_filled = NULL;
GtkWidget *one_filled = NULL;
GtkWidget *box = NULL;

int two = 0;
int one = 0;

char* read_json(const char* filename) {


    FILE* file = fopen(filename, "r");
    if(!file) {
        perror("Could not open file!");
        return NULL;
    }


    fseek(file, 0, FILE_END);
    long size = ftell(file);
    rewind(file);

    char* file_buffer = (char*)malloc(size + 1);
    if(!file_buffer) {
        perror("Failed to create json file buffer!");
        fclose(file);
        return NULL;
    }

    fread(file_buffer, 1, size, file);
    file_buffer[size] = '\0';

    fclose(file);
    return file_buffer;
}

static void scale_image(GtkWidget *image, const gchar *image_file, int width, int height) {
    // Load the original image into a GdkPixbuf
    GdkPixbuf *original_pixbuf = gdk_pixbuf_new_from_file(image_file, NULL);
    if (original_pixbuf == NULL) {
        g_print("Failed to load image\n");
        return;
    }

    // Scale the image to the specified width and height
    GdkPixbuf *scaled_pixbuf = gdk_pixbuf_scale_simple(original_pixbuf, width, height, GDK_INTERP_BILINEAR);

    // Set the scaled pixbuf to the GtkImage
    gtk_image_set_from_pixbuf(GTK_IMAGE(image), scaled_pixbuf);

    // Clean up the original and scaled pixbufs
    g_object_unref(original_pixbuf);
    g_object_unref(scaled_pixbuf);
}

static gboolean show_mouse_event(GtkWidget *window, GdkEventMotion *event, gpointer user_data) {

    m_coordinates.x = event->x;
    m_coordinates.y = event->y;

    if(m_coordinates.x > SCREEN_WIDTH / 2 + 5 && !two) {
        printf("2 filled is applied\n");
        two = 1;
        // GtkWidget *image = GTK_WIDGET(two_filled);
        if (two_filled == NULL) {
            two_filled = gtk_image_new();
        }
        // scale_image(two_filled, "./assets/2/png/2_filled.png", 375, 756);
        gtk_image_set_from_file(GTK_IMAGE(two_filled), "./assets/2/png/2_filled.png");
        gtk_fixed_put(GTK_FIXED(box), two_filled, ((SCREEN_WIDTH - 375) / 2) + (375 / 2) + 5, 0);
        printf("address of box : %d\n", &box);
        gtk_widget_show_all(box);
    } else if(m_coordinates.x < SCREEN_WIDTH / 2 + 5 && two) {
        two = 0;
        printf("2 filled is removed\n");
        // GtkWidget *image = GTK_WIDGET(two_filled);
        // gtk_container_remove(GTK_CONTAINER(box), image);
        // gtk_widget_destroy(image);
        // gtk_widget_show_now(box);

         if (two_filled != NULL) {
            // GtkWidget *image = two_filled;
            // GtkWidget *parent = gtk_widget_get_parent(image);  // Get parent container (fixed box)
            
            if (box != NULL) {
                printf("address of box : %d\n", &box);
                // Remove the image widget from the fixed container
                gtk_container_remove(GTK_CONTAINER(box), two_filled);

                // Destroy the image widget
                // gtk_widget_destroy(two_filled);

                // Reset the two_filled widget to NULL
                two_filled = NULL;

                // Show all widgets in the parent container after removal
                gtk_widget_show_all(box);
            }
        }
    } else if(m_coordinates.x < SCREEN_WIDTH / 2 - 5 && !one) {
        printf("2 filled is applied\n");
        one = 1;
        // GtkWidget *image = GTK_WIDGET(two_filled);
        if (one_filled == NULL) {
            one_filled = gtk_image_new();
        }
        // scale_image(two_filled, "./assets/2/png/2_filled.png", 375, 756);
        gtk_image_set_from_file(GTK_IMAGE(one_filled), "./assets/2/png/1_filled.png");
        gtk_fixed_put(GTK_FIXED(box), one_filled, ((SCREEN_WIDTH - 375) / 2) - (375 / 2) - 5, 0);
        printf("address of box : %d\n", &box);
        gtk_widget_show_all(box);
    } else if(m_coordinates.x > SCREEN_WIDTH / 2 - 5 && one) {
        one = 0;
        printf("2 filled is removed\n");
        // GtkWidget *image = GTK_WIDGET(two_filled);
        // gtk_container_remove(GTK_CONTAINER(box), image);
        // gtk_widget_destroy(image);
        // gtk_widget_show_now(box);

         if (one_filled != NULL) {
            // GtkWidget *image = two_filled;
            // GtkWidget *parent = gtk_widget_get_parent(image);  // Get parent container (fixed box)
            
            if (box != NULL) {
                printf("address of box : %d\n", &box);
                // Remove the image widget from the fixed container
                gtk_container_remove(GTK_CONTAINER(box), one_filled);

                // Destroy the image widget
                // gtk_widget_destroy(two_filled);

                // Reset the two_filled widget to NULL
                one_filled = NULL;

                // Show all widgets in the parent container after removal
                gtk_widget_show_all(box);
            }
        }
    }

    return FALSE;
}

int main(int argc, char *argv[]) {

    GtkWidget *window;
    GtkCssProvider *provider;
    GdkScreen *screen;

    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "vortex");
    gtk_window_set_default_size(GTK_WINDOW(window), SCREEN_WIDTH, SCREEN_HEIGHT);
    gtk_window_maximize(GTK_WINDOW(window));

    box = gtk_fixed_new();
    // gtk_widget_set_app_paintable(window, TRUE);
    gtk_window_set_decorated(GTK_WINDOW(window), FALSE);
    gtk_container_add(GTK_CONTAINER(window), box);

    // provider = gtk_css_provider_new();
    // gtk_css_provider_load_from_data(provider, "window { background-color : rgba(255, 255, 255, 0.5); }", -1, NULL);

    // display = gdk_display_get_default();
    // screen = gdk_display_get_default_screen(display);

    // gtk_style_context_add_provider_for_screen(screen,
    //                                           GTK_STYLE_PROVIDER(provider),
    //                                           GTK_STYLE_PROVIDER_PRIORITY_USER);

    GtkWidget *image1 = gtk_image_new();
    GtkWidget *image2 = gtk_image_new();
    GtkWidget *image3 = gtk_image_new();
    GtkWidget *image4 = gtk_image_new();
    GtkWidget *image5 = gtk_image_new();
    GtkWidget *image6 = gtk_image_new();
    GtkWidget *image7 = gtk_image_new();
    GtkWidget *image8 = gtk_image_new();

    float width1 = 248;
    float height1 = 210;

    float width2 = height1;
    float height2 = width1;
    int offset = 5;

    int screen_width;
    int screen_height;

    screen = gdk_window_get_screen(GTK_WINDOW(window));
    screen_width = gdk_screen_get_width(screen);
    screen_height = gdk_screen_get_height(screen);
    scale_image(image1, "./assets/8/filled/1.png", width1, height1);
    scale_image(image2, "./assets/8/unfilled/2.png", width1, height1);
    scale_image(image3, "./assets/8/unfilled/3.png", width2, height2);
    scale_image(image4, "./assets/8/unfilled/4.png", width2, height2);
    scale_image(image5, "./assets/8/unfilled/5.png", width1, height1);
    scale_image(image6, "./assets/8/unfilled/6.png", width1, height1);
    scale_image(image7, "./assets/8/unfilled/7.png", width2, height2);
    scale_image(image8, "./assets/8/unfilled/8.png", width2, height2);

    GdkDisplay *display = gdk_display_get_default();
    GdkMonitor *monitor = gdk_display_get_primary_monitor(display);
    GdkRectangle geometry;
    gdk_monitor_get_geometry(monitor, &geometry);
    
    gtk_fixed_put(GTK_FIXED(box), image1, ((geometry.width - width1) / 2) - (width1 / 2), 0 + (geometry.height / 2 - 400));
    gtk_fixed_put(GTK_FIXED(box), image2, ((geometry.width - width1) / 2) + (width1 / 2), 0 + (geometry.height / 2 - 400));
    gtk_fixed_put(GTK_FIXED(box), image3, ((geometry.width - width1) / 2) + (width1 / 2) + 141.5, 103 + + (geometry.height / 2 - 400));
    gtk_fixed_put(GTK_FIXED(box), image4, ((geometry.width - width1) / 2) + (width1 / 2) + 141.5, 103.578 + 248 + (geometry.height / 2 - 400));
    gtk_fixed_put(GTK_FIXED(box), image5, ((geometry.width - width1) / 2) + (width1 / 2), 492 + (geometry.height / 2 - 400));
    gtk_fixed_put(GTK_FIXED(box), image6, ((geometry.width - width1) / 2) - (width1 / 2), 492 + (geometry.height / 2 - 400));
    gtk_fixed_put(GTK_FIXED(box), image7, ((geometry.width - width1) / 2) - (width1 / 2) - 103, 103.578 + 248 + (geometry.height / 2 - 400));
    gtk_fixed_put(GTK_FIXED(box), image8, ((geometry.width - width1) / 2) - (width1 / 2) - 103, 103 + (geometry.height / 2 - 400));
    
    GdkRGBA bg_color = {0, 0, 0, 0.5};
    GdkRGBA img_bg_color = {255, 255, 255, 1};
    gtk_widget_override_background_color(window, GTK_STATE_FLAG_NORMAL, &bg_color);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    // g_signal_connect(GTK_WINDOW(window), "motion-notify-event", G_CALLBACK(show_mouse_event), NULL);
    // gtk_widget_set_events(window, GDK_POINTER_MOTION_MASK);

    gtk_widget_show_all(window);

    // Main GTK loop
    gtk_main();

    // char* settings_content = read_json("settings.json");

    // cJSON* settings = cJSON_Parse(settings_content);
    // if(!settings) {
    //     perror("Failed to parse settings file!");
    //     free(settings);
    //     return 1;
    // }
    
    // cJSON* name = cJSON_GetObjectItem(settings, "name");
    // if(name) {
    //     printf("Name : %s\n", name->valuestring);
    // }

    // cJSON_Delete(settings);
    // free(settings_content);

    return 0;
}