#include <stdbool.h>

#include "demeter_V2/game.h"

#include "rpg/game_core.h"
#include "rpg/game_logic/ent_game_logic.h"

#include "button.h"

int button_start_on_click(game_t *game, bool is_hovered)
{
    int id;
    ent_game_logic_t *game_logic;
    char name[DE_ENTITY_NAME_MAX] = "game logic";

    if (!is_hovered || !game->event.mouse.button_click_map[sfMouseLeft])
        return 0;
    id = entity_get(game, 0, name);
    if (id == -1)
        return SEND_WARN("ENT NOT FOUND"), 0;
    game_logic = game->entity_arr[id].data;
    game_logic->new_state = GAME_STATUS_PLAY;
    return 0;
}

int button_exit_on_click(game_t *game, bool is_hovered)
{
    if (!is_hovered || !game->event.mouse.button_click_map[sfMouseLeft])
        return 0;
    game->is_running = false;
    return 0;
}

int button_options_on_click(game_t *game, bool is_hovered)
{
    if (!is_hovered || !game->event.mouse.button_click_map[sfMouseLeft])
        return 0;
    SEND_WARN("Button \"option\" is currently not implemented");
    return 0;
}
