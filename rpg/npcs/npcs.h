#ifndef NPC_T_H
    #define NPC_T_H

    #include <stdbool.h>

    #include <SFML/Graphics/Sprite.h>
    #include <SFML/Graphics/Types.h>
    #include <SFML/System/Types.h>
    #include <SFML/System/Vector2.h>

    #include "demeter_V2/game.h"

typedef enum {
    NEVER,
    QUEST_NOT,
    QUEST_ACC,
    MONEY_REQ,
    QUEST_DONE
} lvl_interact_t;

typedef struct {
    sfSprite *sprite;
    sfSprite *textbox;
    sfFloatRect size;
    int state;
    int speaking;
} npc_t;

int lvlnpc_set(game_t *game, size_t id);
int lvlnpc_unset(game_t *game, size_t id);
int lvlnpc_update(game_t *game, size_t id);
int lvlnpc_draw(game_t *game, size_t id);

int entity_lvl_up(game_t *game);
int entity_sign(game_t *game);

int sign_set(game_t *game, size_t id);
int sign_unset(game_t *game, size_t id);
int sign_update(game_t *game, size_t id);
int sign_draw(game_t *game, size_t id);

#endif
