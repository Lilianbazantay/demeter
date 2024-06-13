#include <stdbool.h>
#include <stdlib.h>

#include "demeter_V2/de_arr.h"
#include "demeter_V2/entity.h"
#include "demeter_V2/game.h"
#include "demeter_V2/scene.h"

#include "ent_game_logic.h"
#include "rpg/game_core.h"

int ent_game_logic_set(game_t *game, size_t id)
{
    entity_t *ent = &game->entity_arr[id];
    ent_game_logic_t *data;

    ent->data = malloc(sizeof(ent_game_logic_t));
    if (ent->data == NULL)
        return SEND_ERR("malloc failed"), 84;
    data = ent->data;
    data->current_state = GAME_STATUS_NONE;
    data->new_state = GAME_STATUS_MAIN_MENU;
    return 0;
}

int ent_game_logic_unset(game_t *game, size_t id)
{
    ent_game_logic_t *data = game->entity_arr[id].data;

    free(data);
    return 0;
}

static
void unload_current(game_t *game, ent_game_logic_t *data)
{
    scene_t *scene = de_arr_get(game->scene_arr, data->scene_id);

    if (scene == NULL) {
        SEND_WARN("No scene");
        return;
    }
    switch (data->current_state) {
        case GAME_STATUS_NONE:
            return;
        case GAME_STATUS_MAIN_MENU:
            unload_main_menu(game, scene);
            return;
        case GAME_STATUS_PLAY:
            unload_play(game, scene);
            return;
        case GAME_STATUS_PAUSE:
            return;
    }
}

static
int load_new(game_t *game, ent_game_logic_t *data)
{
    switch (data->new_state) {
        case GAME_STATUS_NONE:
            break;
        case GAME_STATUS_MAIN_MENU:
            if (load_main_menu(game, data))
                return SEND_ERR("failed to load main menu"), 84;
            break;
        case GAME_STATUS_PLAY:
            if (load_play(game, data))
                return SEND_ERR("failed to load play"), 84;
            break;
        case GAME_STATUS_PAUSE:
            break;
    }
    return 0;
}

int ent_game_logic_update(game_t *game, size_t id)
{
    ent_game_logic_t *data = game->entity_arr[id].data;

    if (data->current_state == data->new_state)
        return 0;
    if (data->current_state != GAME_STATUS_NONE)
        unload_current(game, data);
    data->current_state = data->new_state;
    return load_new(game, data);
}
