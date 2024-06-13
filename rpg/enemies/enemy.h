#include <stdbool.h>

#include <SFML/Graphics/Sprite.h>
#include <SFML/System/Types.h>
#include <SFML/System/Vector2.h>

#include "../player/player_data.h"

#ifndef ENEMY_H
    #define ENEMY_H

    #include <SFML/Graphics/Types.h>

    #define ENEMY_COUNT 20

typedef struct enemy_s {
    bool is_dead;
    bool is_active;
    bool can_move;
    sfClock *wait_timer;
    stats_t stats;
    sfSprite *sprite;
    sfVector2f position;
    sfVector2f start_position;
    sfIntRect hitbox;
} enemy_t;

bool check_if_entity_active(enemy_t *enemy, sfVector2f position);
void check_enemy_movement(enemy_t *enemy, player_t *player);
void check_enemy_attack(game_t *game, enemy_t *enemy, player_t *player);

#endif
