#include "demeter_V2/game.h"
#include "demeter_V2/scene.h"

#include "ent_game_logic.h"

static
void unload_menu(game_t *game, scene_t *scene)
{
    int id;

    while (0 < scene->entity_id_arr->data_count) {
        id = *(int *)de_arr_get(scene->entity_id_arr, 0);
        if (game->entity_arr[id].is_used)
            entity_unset(game, (size_t)id);
    }
    scene_pop(game);
}

void unload_main_menu(game_t *game, scene_t *scene)
{
    unload_menu(game, scene);
}

void unload_play(game_t *game, scene_t *scene)
{
    unload_menu(game, scene);
}
