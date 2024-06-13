#include "demeter_V2/game.h"
#include "demeter_V2/scene.h"

#include "collison_manager/collision_manager.h"
#include "game_core.h"
#include "game_logic/ent_game_logic.h"

static
const window_t WINDOW = {
    .name = "Shadow of Time",
    .ext_width = 1440, .ext_height = 960,
    .internal = { 0, 0, 160, 120 },
    .framerate = 60
};

static entity_t ENTITY = {
    .name = "game logic",
    .set = &ent_game_logic_set,
    .unset = &ent_game_logic_unset,
    .update = &ent_game_logic_update,
    .priority = ENT_PRIORITY_MEDIUM,
};

static entity_t COLL = {
    "game logic",
    &ent_collision_manager_set, &ent_collision_manager_unset,
    NULL, NULL,
    NULL,
    0, 0,
    ENT_PRIORITY_MEDIUM,
    false
};

static
int game_prepare(game_t *game)
{
    if (scene_append(game, 1, 1))
        return 84;
    if (entity_set(game, &ENTITY, -1) == -1)
        return SEND_ERR("game logic set failed."), 84;
    if (entity_set(game, &COLL, -1) == -1)
        return SEND_ERR("coll manager failed"), 84;
    return 0;
}

int game_run(void)
{
    game_t game;

    if (game_set(&game, &WINDOW))
        return SEND_ERR("game set failed."), 84;
    game.is_running = true;
    if (game_prepare(&game))
        return SEND_ERR("game prepare failed."), game_unset(&game), 84;
    while (game.is_running) {
        if (game_update(&game))
            return SEND_ERR("game update failed."), game_unset(&game), 84;
        game_draw(&game);
    }
    return game_unset(&game), 0;
}
