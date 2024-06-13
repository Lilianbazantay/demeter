#include <stdbool.h>
#include <stdlib.h>

#include "demeter_V2/entity.h"
#include "demeter_V2/game.h"
#include "demeter_V2/window.h"

#include "controler.h"
#include "rpg/main_menu/background/background.h"
#include "rpg/main_menu/button/button.h"
#include "rpg/game_core.h"

static
entity_t BACKGROUND = {
    .name = "background",
    .set = &ent_main_menu_background_set,
    .unset = &ent_main_menu_background_unset,
    .update = &ent_main_menu_background_update,
    .draw = &ent_main_menu_background_draw,
    .id = 0,
    .scene = 0,
    .priority = ENT_PRIORITY_LOW,
};

static
int main_menu_entities_set(game_t *game)
{
    if (entity_set(game, &BACKGROUND, -1) == -1)
        return SEND_ERR("entity set main menu background failed"), 84;
    if (
        ent_main_menu_button_start_set(game)
        || ent_main_menu_button_options_set(game)
        || ent_main_menu_button_exit_set(game)
    )
        return 84;
    return 0;
}

int ent_main_menu_controler_set(game_t *game, size_t id)
{
    entity_t *ent = &game->entity_arr[id];
    ent_main_menu_controler_t *data;

    ent->data = malloc(sizeof(ent_main_menu_controler_t));
    if (ent->data == NULL)
        return SEND_ERR("malloc failed"), 84;
    if (window_move(game, 0, 0))
        return free(ent->data), 84;
    if (main_menu_entities_set(game))
        return free(ent->data), 84;
    data = ent->data;
    data->status = MMS_MENU;
    return 0;
}

int ent_main_menu_controler_unset(game_t *game, size_t id)
{
    ent_main_menu_controler_t *data = game->entity_arr[id].data;

    free(data);
    return 0;
}

int ent_main_menu_controler_update(game_t *game, size_t id)
{
    ent_main_menu_controler_t *data = game->entity_arr[id].data;

    (void) data;
    return 0;
}
