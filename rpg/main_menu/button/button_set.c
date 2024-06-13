#include <stdbool.h>

#include <SFML/Graphics/Sprite.h>

#include "demeter_V2/entity.h"
#include "demeter_V2/game.h"
#include "demeter_V2/resources.h"

#include "rpg/game_core.h"
#include "rpg/main_menu/button/button.h"

static
entity_t START = {
    .name = "mmb start",
    .set = &ent_main_menu_button_set,
    .unset = &ent_main_menu_button_unset,
    .update = &ent_main_menu_button_update,
    .draw = &ent_main_menu_button_draw,
    .data = NULL,
    .id = 0,
    .scene = 0,
    .priority = ENT_PRIORITY_MEDIUM,
    .is_used = false
};

static
entity_t OPTIONS = {
    .name = "mmb options",
    .set = &ent_main_menu_button_set,
    .unset = &ent_main_menu_button_unset,
    .update = &ent_main_menu_button_update,
    .draw = &ent_main_menu_button_draw,
    .data = NULL,
    .id = 0,
    .scene = 0,
    .priority = ENT_PRIORITY_MEDIUM,
    .is_used = false
};

static
entity_t EXIT = {
    .name = "mmb exit",
    .set = &ent_main_menu_button_set,
    .unset = &ent_main_menu_button_unset,
    .update = &ent_main_menu_button_update,
    .draw = &ent_main_menu_button_draw,
    .data = NULL,
    .id = 0,
    .scene = 0,
    .priority = ENT_PRIORITY_MEDIUM,
    .is_used = false
};

int ent_main_menu_button_start_set(game_t *game)
{
    int id = entity_set(game, &START, -1);
    ent_main_menu_button_t *data;

    if (id == -1)
        return SEND_ERR("entity set main menu button start failed"), 84;
    data = game->entity_arr[id].data;
    data->transform = (sfFloatRect){ 16, 16, 64, 23 };
    data->on_click = &button_start_on_click;
    sfSprite_setTexture(
        data->sprite, game->tex_arr[TEX_MAIN_MENU_START], true);
    sfSprite_setPosition(
        data->sprite, (sfVector2f){data->transform.left, data->transform.top});
    return 0;
}

int ent_main_menu_button_options_set(game_t *game)
{
    int id = entity_set(game, &OPTIONS, -1);
    ent_main_menu_button_t *data;

    if (id == -1)
        return SEND_ERR("entity set main menu button options failed"), 84;
    data = game->entity_arr[id].data;
    data->transform = (sfFloatRect){ 16, 47, 64, 23 };
    data->on_click = &button_options_on_click;
    sfSprite_setTexture(
        data->sprite, game->tex_arr[TEX_MAIN_MENU_OPTIONS], true);
    sfSprite_setPosition(
        data->sprite, (sfVector2f){data->transform.left, data->transform.top});
    return 0;
}

int ent_main_menu_button_exit_set(game_t *game)
{
    int id = entity_set(game, &EXIT, -1);
    ent_main_menu_button_t *data;

    if (id == -1)
        return SEND_ERR("entity set main menu button exit failed"), 84;
    data = game->entity_arr[id].data;
    data->transform = (sfFloatRect){ 16, 78, 64, 23 };
    data->on_click = &button_exit_on_click;
    sfSprite_setTexture(
        data->sprite, game->tex_arr[TEX_MAIN_MENU_EXIT], true);
    sfSprite_setPosition(
        data->sprite, (sfVector2f){data->transform.left, data->transform.top});
    return 0;
}
