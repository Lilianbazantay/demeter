#ifndef DE_EVENT_H
    #define DE_EVENT_H

    #include <stdbool.h>

    #include <SFML/Window/Event.h>

    #include "types.h"

    #define M_SET(e, i, w) (int)((float)e * (i / (float)w))

typedef struct mouse_s {
    bool button_press_map[sfMouseButtonCount];
    bool button_click_map[sfMouseButtonCount];
    int wheel_delta;
    int x;
    int y;
} mouse_t;

typedef struct event_s {
    bool key_map[sfKeyCount];
    mouse_t mouse;
} event_t;

void event_update(game_t *game);
void mouse_update(game_t *game, mouse_t *mouse, sfEvent *event);

#endif  // DE_EVENT_H
