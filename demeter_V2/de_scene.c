#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

#include "de_arr.h"
#include "entity.h"
#include "game.h"
#include "scene.h"

int scene_append(game_t *game, size_t entity_arr_size, size_t incr)
{
    scene_t scene = { 0 };

    scene.entity_id_arr = de_arr_create(sizeof(int), entity_arr_size, incr);
    scene.to_update = true;
    scene.to_draw = true;
    if (scene.entity_id_arr == NULL)
        return 84;
    if (de_arr_insert(game->scene_arr, &scene, game->scene_arr->data_count))
        return de_arr_destroy(scene.entity_id_arr, NULL), 84;
    return 0;
}

void scene_pop(game_t *game)
{
    if (game->scene_arr->data_count == 0) {
        DE_WARN("no scene to pop.");
        return;
    }
    de_arr_remove(
        game->scene_arr,
        (de_func_destroy_t *)&scene_destroy,
        game->scene_arr->data_count - 1);
}

void scene_destroy(scene_t *scene)
{
    de_arr_destroy(scene->entity_id_arr, NULL);
}

int scene_update(game_t *game, size_t i)
{
    scene_t *scene = de_arr_get(game->scene_arr, i);
    entity_t *ent;
    int id;

    if (scene == NULL) {
        DE_WARN("no scene to update.");
        return 0;
    }
    for (size_t j = 0; j < scene->entity_id_arr->data_count; j++) {
        id = *(int *)de_arr_get(scene->entity_id_arr, j);
        ent = &(game->entity_arr[id]);
        if (ent->update != NULL && ent->update(game, (size_t)id)) {
            DE_ERR("entity update failed");
            return 84;
        }
    }
    return 0;
}

void scene_draw(game_t *game, size_t i)
{
    scene_t *scene = de_arr_get(game->scene_arr, i);
    entity_t *ent;
    int id;
    priority_t priority = ENT_PRIORITY_LOW;

    if (scene == NULL) {
        DE_WARN("no scene %i to draw.");
        return;
    }
    for (size_t j = 0; priority <= ENT_PRIORITY_HIGH; j++) {
        if (j >= scene->entity_id_arr->data_count) {
            j = 0;
            priority++;
            continue;
        }
        id = *(int *)de_arr_get(scene->entity_id_arr, j);
        ent = &(game->entity_arr[id]);
        if (priority == ent->priority && ent->draw != NULL)
            ent->draw(game, (size_t)id);
    }
}
