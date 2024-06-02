#ifndef DE_ENTITY_H
    #define DE_ENTITY_H

    #include <stdbool.h>

    #include "types.h"

    #define DE_ENTITY_NAME_MAX 16

typedef enum priority_s {
    ENT_PRIORITY_LOW,
    ENT_PRIORITY_MEDIUM,
    ENT_PRIORITY_HIGH
} priority_t;

typedef struct entity_s {
    char name[DE_ENTITY_NAME_MAX];
    de_func_entity_t *set; // can be NULL
    de_func_entity_t *unset; // can be NULL
    de_func_entity_t *update; // can be NULL
    de_func_entity_t *draw; // can be NULL
    void *data;
    size_t id;
    size_t scene;
    priority_t priority;
    bool is_used;
} entity_t;

// @param scene: if < 0 -> use current scene
int entity_set(game_t *game, entity_t *entity, int scene);
void entity_unset(game_t *game, size_t id);
// @param scene: if < 0 -> use current scene
int entity_get(game_t *game, int scene, const char *name);

#endif  // DE_ENTITY_H
