#include <stdbool.h>
#include <stdlib.h>

#include <SFML/Graphics/Sprite.h>
#include <SFML/System/Vector2.h>

#include "demeter_V2/entity.h"
#include "demeter_V2/game.h"

#include "button.h"
#include "rpg/game_core.h"

int ent_main_menu_button_set(game_t *game, size_t id)
{
    entity_t *ent = &game->entity_arr[id];
    ent_main_menu_button_t *data;

    ent->data = malloc(sizeof(ent_main_menu_button_t));
    if (ent->data == NULL)
        return SEND_ERR("malloc failed"), 84;
    data = ent->data;
    data->sprite = sfSprite_create();
    if (data->sprite == NULL)
        return SEND_ERR("SFML failed"), 84;
    data->on_click = NULL;
    data->is_hovered = false;
    return 0;
}

int ent_main_menu_button_unset(game_t *game, size_t id)
{
    ent_main_menu_button_t *data = game->entity_arr[id].data;

    sfSprite_destroy(data->sprite);
    free(data);
    return 0;
}

int ent_main_menu_button_update(game_t *game, size_t id)
{
    ent_main_menu_button_t *data = game->entity_arr[id].data;
    sfVector2f mouse = {
        (float)game->event.mouse.x, (float)game->event.mouse.y };

    data->is_hovered = data->transform.left <= mouse.x
        && mouse.x < data->transform.left + data->transform.width
        && data->transform.top <= mouse.y
        && mouse.y < data->transform.top + data->transform.height;
    if (data->on_click != NULL && data->on_click(game, data->is_hovered))
        return 84;
    return 0;
}

int ent_main_menu_button_draw(game_t *game, size_t id)
{
    ent_main_menu_button_t *data = game->entity_arr[id].data;
    sfVector2f pos = *(sfVector2f *)&data->transform;

    pos.x += data->is_hovered * 4;
    sfSprite_setPosition(data->sprite, pos);
    sfSprite_setTextureRect(data->sprite,
        (sfIntRect){64 * data->is_hovered, 0, 64, 23});
    sfRenderWindow_drawSprite(game->window.window, data->sprite, NULL);
    return 0;
}
