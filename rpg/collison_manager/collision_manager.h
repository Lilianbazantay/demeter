#ifndef COLLISION_MANAGER_H
    #define COLLISION_MANAGER_H

    #include <stdint.h>

    #include "demeter_V2/de_arr.h"
    #include "demeter_V2/game.h"

    #define COL_MAP_SIZE (150 * 150 / 8 + 1)
    #define PATH "resources/real map.tmx"

typedef struct {
    uint8_t map[COL_MAP_SIZE];
    de_arr_t *ent;
} ent_collision_manager_t;

int ent_collision_manager_set(game_t *game, size_t id);
int ent_collision_manager_unset(game_t *game, size_t id);

bool is_colliding(sfIntRect *rect, ent_collision_manager_t *dont_use);

#endif  // COLLISION_MANAGER_H
