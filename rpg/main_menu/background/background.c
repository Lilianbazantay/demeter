#include <stdbool.h>
#include <stdlib.h>

#include <SFML/Graphics/RenderWindow.h>
#include <SFML/Graphics/Sprite.h>

#include "demeter_V2/entity.h"
#include "demeter_V2/game.h"

#include "background.h"
#include "demeter_V2/resources.h"
#include "rpg/game_core.h"

int ent_main_menu_background_set(game_t *game, size_t id)
{
    entity_t *ent = &game->entity_arr[id];
    ent_main_menu_background_t *data;
    long int zero = 0UL;

    ent->data = malloc(sizeof(ent_main_menu_background_t));
    if (ent->data == NULL)
        return SEND_ERR("malloc failed"), 84;
    data = ent->data;
    data->sprite = sfSprite_create();
    if (data->sprite == NULL)
        return SEND_ERR("sfml failed"), free(data), 84;
    data->pos = *(sfVector2f *)&zero;
    sfSprite_setScale(data->sprite, (sfVector2f){ 1.2F, 1.2F });
    sfSprite_setTexture(
        data->sprite, game->tex_arr[TEX_MAIN_MENU_BACKGROUND], true);
    return 0;
}

int ent_main_menu_background_unset(game_t *game, size_t id)
{
    ent_main_menu_background_t *data = game->entity_arr[id].data;

    sfSprite_destroy(data->sprite);
    free(data);
    return 0;
}

int ent_main_menu_background_draw(game_t *game, size_t id)
{
    ent_main_menu_background_t *data = game->entity_arr[id].data;

    sfRenderWindow_drawSprite(game->window.window, data->sprite, NULL);
    return 0;
}

int ent_main_menu_background_update(game_t *game, size_t id)
{
    ent_main_menu_background_t *data = game->entity_arr[id].data;
    static float sign = 1.F;

    data->pos.x += 0.001F * sign;
    if (data->pos.x < -10.F)
        sign = 1.F;
    if (data->pos.x > -5.F)
        sign = -1.F;
    sfSprite_setPosition(data->sprite, data->pos);
    return 0;
}
