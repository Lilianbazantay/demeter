#include <stdbool.h>
#include <stddef.h>
#include <string.h>

#include "de_arr.h"
#include "entity.h"
#include "game.h"
#include "scene.h"
#include "types.h"

static
int entity_avaliability(game_t *game)
{
    size_t id;

    if (game->scene_arr->data_count == 0)
        return DE_ERR("no scene."), -1;
    for (id = 0; id < DE_ENTITY_MAX; id++)
        if (!game->entity_arr[id].is_used)
            break;
    if (id == DE_ENTITY_MAX)
        return DE_ERR("out of entity memory."), -1;
    return (int)id;
}

// @param scene: if < 0 -> use current scene
// @return -1 if failed
int entity_set(game_t *game, entity_t *entity, int scene_id)
{
    int id = entity_avaliability(game);
    scene_t *scene;

    if (id == -1)
        return -1;
    memcpy(&game->entity_arr[id], entity, sizeof(entity_t));
    game->entity_arr[id].id = (size_t)id;
    scene_id = scene_id == -1 ? (int)game->scene_arr->data_count -1 : scene_id;
    game->entity_arr[id].scene = (size_t)scene_id;
    game->entity_arr[id].is_used = true;
    if (game->entity_arr[id].set != NULL
        && game->entity_arr[id].set(game, (size_t)id))
        return DE_ERR("entity set failed."), -1;
    scene = de_arr_get(game->scene_arr, (size_t)scene_id);
    if (de_arr_insert(
        scene->entity_id_arr, &id, scene->entity_id_arr->data_count))
        return DE_ERR("scene insert entity_id failed."), -1;
    return id;
}

void entity_unset(game_t *game, size_t id)
{
    entity_t *ent = &game->entity_arr[id];
    scene_t *scene = de_arr_get(game->scene_arr, ent->scene);

    if (ent->unset != NULL)
        ent->unset(game, id);
    memset(ent, 0, sizeof(entity_t));
    if (scene == NULL)
        return;
    for (size_t i = 0; i < scene->entity_id_arr->data_count; i++)
        if (*(int *)de_arr_get(scene->entity_id_arr, i) == (int)id) {
            de_arr_remove(scene->entity_id_arr, NULL, i);
            return;
        }
}

// @param scene: if < 0 -> use current scene
int entity_get(game_t *game, int scene, const char *name)
{
    scene_t *s = scene < 0
        ? de_arr_get(game->scene_arr, game->scene_arr->data_count - 1)
        : de_arr_get(game->scene_arr, (size_t)scene);
    int id;

    if (s == NULL)
        return DE_ERR("no scene."), -1;
    for (size_t i = 0; i < s->entity_id_arr->data_count; i++) {
        id = *(int *)de_arr_get(s->entity_id_arr, i);
        if (strncmp(game->entity_arr[id].name, name, DE_ENTITY_NAME_MAX) == 0)
            return id;
    }
    return DE_ERR("entity not found."), -1;
}
