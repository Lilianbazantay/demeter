#ifndef PLAYER_STRUCT_H_
    #define PLAYER_STRUCT_H_

    #include <stdbool.h>
    #include <stdlib.h>

    #include <SFML/Graphics/Sprite.h>
    #include <SFML/System/Types.h>

    #include "demeter_V2/game.h"

    #include "../../player/player_data.h"
    #include "../npcs.h"

typedef struct {
    bool is_picked;
    int damage;
    float cons_stamina;
    int hit_speed;
    int req_strength;
    int req_resistance;
    size_t id;
} player_weapon_t;

int enemies_revive(game_t *game);

player_t *check_interaction(game_t *game, npc_t *npc);

int never_quest(game_t *game, npc_t *npc);

int quest_dial(game_t *game, npc_t *npc, player_t *player);
int quest_conti(game_t *game, npc_t *npc, player_t *player);

int lvl_up(game_t *game, npc_t *npc, player_t *player);

int retry(game_t *game, npc_t *npc);

int print_text(game_t *game, npc_t *npc, player_t *player);

#endif
