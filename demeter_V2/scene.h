#ifndef DE_SCENE_H
    #define DE_SCENE_H

    #include <stdbool.h>

    #include "de_arr.h"
    #include "types.h"

typedef struct scene_s {
    de_arr_t *entity_id_arr; // sorted by priority then id
    bool to_draw;
    bool to_update;
} scene_t;

int scene_append(game_t *game, size_t entity_arr_size, size_t incr);
void scene_pop(game_t *game);
void scene_destroy(scene_t *scene);
int scene_update(game_t *game, size_t i);
void scene_draw(game_t *game, size_t i);

#endif  // DE_SCENE_H
