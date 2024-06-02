#include <stdbool.h>
#include <string.h>

#include <SFML/Graphics/RenderWindow.h>
#include <SFML/Window/Event.h>
#include <SFML/Window/Keyboard.h>

#include "event.h"
#include "game.h"

const unsigned int FPS_CAP[] = {
    0, /* Unlimited */
    1,
    2,
    5,
    10,
    20,
    30,
    40,
    50,
    60,
};

static
void handle_fps(game_t *game, sfEvent *evt)
{
    if (evt->type != sfEvtKeyReleased
        || evt->key.code < sfKeyNum0 || sfKeyNum9 < evt->key.code)
        return;
    sfRenderWindow_setFramerateLimit(
        game->window.window, FPS_CAP[evt->key.code - sfKeyNum0]);
}

void event_update(game_t *game)
{
    sfEvent evt;
    event_t *event = &game->event;

    memset(event->mouse.button_click_map, false, sfMouseButtonCount);
    while (sfRenderWindow_pollEvent(game->window.window, &evt)) {
        if (evt.type == sfEvtClosed) {
            game->is_running = false;
            return;
        }
        if (evt.type == sfEvtMouseMoved
            || evt.type == sfEvtMouseWheelScrolled
            || evt.type == sfEvtMouseButtonPressed
            || evt.type == sfEvtMouseButtonReleased) {
            mouse_update(game, &event->mouse, &evt);
            continue;
        }
        if (evt.type == sfEvtKeyPressed || evt.type == sfEvtKeyReleased)
            event->key_map[evt.key.code] = evt.type == sfEvtKeyPressed;
        handle_fps(game, &evt);
    }
}
