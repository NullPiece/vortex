#ifndef MAIN_H
#define MAIN_H

#include<gtk-3.0/gtk/gtk.h>
#include <gtk-3.0/gtk/gtktypes.h>
#include <glib-2.0/glib/gtypes.h>
#include <gtk-3.0/gtk/gtkapplication.h>
#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<cairo/cairo.h>
#include "./utils/cjson/cJSON.h"
#include<math.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800
#define OUTER_WHEEL_RADIUS ((SCREEN_WIDTH / 2) - 100)
#define INNER_WHEEL_RADIUS (OUTER_WHEEL_RADIUS - 150)
#define PI 3.14
#define HALF_PI (PI / 2)
#define FULL_ARC (PI * 2)
#define OFFSET (PI / 50)

#endif // MAIN_H