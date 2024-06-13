#include "demeter_V2/game.h"
#include "demeter_V2/scene.h"

#include "rpg/game_core.h"
#include "rpg/main_menu/controler/controler.h"
#include "rpg/npcs/npcs.h"

#include "ent_game_logic.h"

static
entity_t MAIN_MENU_CONTROLER = {
    .name = "m._m._controler",
    .set = &ent_main_menu_controler_set,
    .unset = &ent_main_menu_controler_unset,
    .update = &ent_main_menu_controler_update,
    .priority = ENT_PRIORITY_MEDIUM,
};

int load_main_menu(game_t *game, ent_game_logic_t *data)
{
    if (scene_append(game, 10, 1))
        return SEND_ERR("scene menu create failed"), 84;
    data->scene_id = game->scene_arr->data_count - 1;
    if (entity_set(game, &MAIN_MENU_CONTROLER, -1) == -1)
        return SEND_ERR("entity main_menu create failed"), 84;
    return 0;
}

int load_play(game_t *game, ent_game_logic_t *data)
{
    if (scene_append(game, 10, 1))
        return SEND_ERR("scene menu create failed"), 84;
    data->scene_id = game->scene_arr->data_count - 1;
    if (entity_background(game))
        return 84;
    if (entity_weapons(game) || entity_shields(game))
        return 84;
    if (entity_collectibles(game))
        return 84;
    if (entity_player(game))
        return 84;
    if (entity_enemy_arr(game))
        return 84;
    if (entity_lvl_up(game))
        return 84;
    if (entity_sign(game))
        return 84;
    return 0;
}
