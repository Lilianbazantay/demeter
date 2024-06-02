#include <SFML/Graphics/Rect.h>
#include <SFML/Graphics/RenderWindow.h>
#include <SFML/System/Vector2.h>
#include <SFML/Window/Event.h>

#include "game.h"

#include "event.h"

void mouse_update(game_t *game, mouse_t *mouse, sfEvent *event)
{
    sfVector2u win_size = sfRenderWindow_getSize(game->window.window);
    sfMouseButton bt = event->mouseButton.button;
    sfFloatRect *internal = &game->window.internal;

    mouse->x = M_SET(event->mouseMove.x, internal->width, win_size.x);
    mouse->y = M_SET(event->mouseMove.y, internal->height, win_size.y);
    if (event->type == sfEvtMouseMoved)
        return;
    if (event->type == sfEvtMouseWheelScrolled) {
        mouse->wheel_delta = event->mouseWheel.delta;
        mouse->x = event->mouseWheel.x;
        mouse->y = event->mouseWheel.y;
        return;
    }
    mouse->button_press_map[bt] = event->type == sfEvtMouseButtonPressed;
    mouse->button_click_map[bt] = event->type == sfEvtMouseButtonReleased;
    mouse->x = M_SET(event->mouseButton.x, internal->width, win_size.x);
    mouse->y = M_SET(event->mouseButton.y, internal->height, win_size.y);
}
