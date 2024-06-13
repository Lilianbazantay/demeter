#include <stdbool.h>
#include <unistd.h>

#include <SFML/Graphics/Rect.h>
#include <SFML/Graphics/RenderWindow.h>
#include <SFML/Graphics/Sprite.h>
#include <SFML/Graphics/Types.h>
#include <SFML/Window/Keyboard.h>

#include "demeter_V2/game.h"
#include "demeter_V2/types.h"

#include "../npcs.h"
#include "struct_player.h"

static
void wait_for_input(game_t *game)
{
    while (game->event.key_map[sfKeySpace])
        event_update(game);
}

int retry(game_t *game, npc_t *npc)
{
    wait_for_input(game);
    npc->state = QUEST_NOT;
    enemies_revive(game);
    return 0;
}

int lvl_up(game_t *game, npc_t *npc, player_t *player)
{
    wait_for_input(game);
    player_lvl_up(game, player);
    npc->state = QUEST_DONE;
    return 0;
}

int quest_conti(game_t *game, npc_t *npc, player_t *player)
{
    wait_for_input(game);
    if (player->required_money > player->stats.exp_money)
        return 0;
    npc->state = MONEY_REQ;
    enemies_revive(game);
    return 0;
}

int quest_dial(game_t *game, npc_t *npc, player_t *player)
{
    wait_for_input(game);
    if (player->required_money < player->stats.exp_money) {
        npc->state = MONEY_REQ;
        return 0;
    }
    enemies_revive(game);
    npc->state = QUEST_ACC;
    return 0;
}

int never_quest(game_t *game, npc_t *npc)
{
    while (game->event.key_map[sfKeySpace])
        event_update(game);
    npc->state = QUEST_NOT;
    return 0;
}
