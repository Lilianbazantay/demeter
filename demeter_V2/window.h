#ifndef DE_WINDOW_H
    #define DE_WINDOW_H

    #include <SFML/Graphics/RenderWindow.h>

    #include "types.h"

    #define DE_WINDOW_NAME_SIZE 64
    #define DE_DEFAULT_WIN_EXT_W 1920
    #define DE_DEFAULT_WIN_EXT_H 1080
    #define DE_DEFAULT_WIN_INT_W 640
    #define DE_DEFAULT_WIN_INT_H 480
    #define DE_DEFAULT_WIN_FRAMERATE 60

typedef struct window_s {
    const char name[DE_WINDOW_NAME_SIZE];
    sfRenderWindow *window; // handled by create()
    size_t ext_width; // default 1920
    size_t ext_height; // default 1080
    sfFloatRect internal; // default 640 x 480
    size_t framerate; // default 60
} window_t;

int window_create(game_t *game, const window_t *win_data);
void window_destroy(game_t *game);
int window_move(game_t *game, int int_x, int int_y);

#endif  // DE_WINDOW_H
