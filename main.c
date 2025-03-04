#include "main.h"

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

gboolean on_draw(GtkWidget *widget, cairo_t *cr, gpointer data) {
    
    int num_process = 12;
    float percent = FULL_ARC / num_process;
    
    for(int i = 0; i < num_process; ++i) {
        
        // outer wheel border
        cairo_set_source_rgb(cr, 0, 0, 1);
        cairo_arc(cr, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, OUTER_WHEEL_RADIUS, i * percent + OFFSET - (OFFSET / 2), (i + 1) * percent - OFFSET + (OFFSET / 2));
        cairo_stroke(cr);

        // inner wheel border
        cairo_set_source_rgb(cr, 0, 0, 1);
        cairo_new_path(cr);
        cairo_arc(cr, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, INNER_WHEEL_RADIUS, i * percent + OFFSET, (i + 1) * percent - OFFSET);
        cairo_stroke(cr);

        // straight border line right
        cairo_set_source_rgb(cr, 0, 0, 1);
        cairo_new_path(cr);
        cairo_set_line_width(cr, 2.0);
        cairo_move_to(cr, (SCREEN_WIDTH / 2) + INNER_WHEEL_RADIUS * cos(percent * i - OFFSET), (SCREEN_HEIGHT/ 2) + INNER_WHEEL_RADIUS * sin(percent * i - OFFSET));
        cairo_line_to(cr, (SCREEN_WIDTH / 2) + OUTER_WHEEL_RADIUS * cos(percent * i - OFFSET + (OFFSET / 2)), (SCREEN_HEIGHT / 2) + OUTER_WHEEL_RADIUS * sin(percent * i - OFFSET + (OFFSET / 2)));
        cairo_stroke(cr);

        // straight border line left
        cairo_set_source_rgb(cr, 0, 0, 1);
        cairo_new_path(cr);
        cairo_set_line_width(cr, 2.0);
        cairo_move_to(cr, (SCREEN_WIDTH / 2) + INNER_WHEEL_RADIUS * cos(percent * i + OFFSET), (SCREEN_HEIGHT/ 2) + INNER_WHEEL_RADIUS * sin(percent * i + OFFSET));
        cairo_line_to(cr, (SCREEN_WIDTH / 2) + OUTER_WHEEL_RADIUS * cos(percent * i + OFFSET - (OFFSET / 2)), (SCREEN_HEIGHT / 2) + OUTER_WHEEL_RADIUS * sin(percent * i + OFFSET - (OFFSET / 2)));
        cairo_stroke(cr);
    }

    // for(int i = 0; i < num_process; ++i) {
        
    //     cairo_set_source_rgb(cr, 0, 0, 1);
    //     cairo_new_path(cr);
    //     cairo_set_line_width(cr, 2.0);
    //     cairo_move_to(cr, 400, 400);
    //     cairo_line_to(cr, 400 + 200 * cos(percent * i), 400 + 200 * sin(percent * i));
    //     // cairo_line_to(cr, pow(pow(300, 2.0) - pow(400, 2.0), 0.5) + 400, pow(pow(300, 2.0) - pow(400, 2.0), 0.5) + 400);
    //     cairo_stroke(cr);
    // }
    
    
    
    // cairo_arc(cr, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, OUTER_WHEEL_RADIUS, 0 + OFFSET, HALF_PI - OFFSET);
    // cairo_stroke(cr);
    // cairo_new_path(cr);
    // cairo_arc(cr, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, INNER_WHEEL_RADIUS, OFFSET, HALF_PI - OFFSET);
    // cairo_stroke(cr);

    return FALSE;
}

int main(int argc, char *argv[]) {

    gtk_init(&argc, &argv);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "GTK Arc Example");
    gtk_window_set_default_size(GTK_WINDOW(window), SCREEN_WIDTH, SCREEN_HEIGHT);

    // gtk_widget_set_app_paintable(GTK_WIDGET(window), TRUE);
    // gtk_window_set_decorated(GTK_WINDOW(window), FALSE);

    GtkWidget *drawing_area = gtk_drawing_area_new();
    gtk_container_add(GTK_CONTAINER(window), drawing_area);

    g_signal_connect(G_OBJECT(drawing_area), "draw", G_CALLBACK(on_draw), NULL);

    gtk_widget_show_all(window);

    // Main GTK loop
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
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