#include <stddef.h>
#include <string.h>

#include <SFML/Config.h>
#include <SFML/Graphics/RenderWindow.h>
#include <SFML/Graphics/Sprite.h>
#include <SFML/System/Clock.h>

#include "de_arr.h"
#include "event.h"
#include "game.h"
#include "resources.h"
#include "scene.h"
#include "types.h"
#include "window.h"

static
int set_clocks(game_t *game)
{
    game->main_clock = sfClock_create();
    if (game->main_clock == NULL)
        return 84;
    game->game_clock = sfClock_create();
    if (game->game_clock == NULL)
        return 84;
    game->main_delta_time = 0;
    game->game_delta_time = 0;
    game->prev_main_clock = 0;
    game->prev_game_clock = 0;
    return 0;
}

static
int font_init_sprite(game_t *game)
{
    game->font_sprite = sfSprite_create();
    if (game->font_sprite == NULL)
        return DE_ERR("sprite creation failed"), 84;
    sfSprite_setTexture(
        game->font_sprite, game->tex_arr[TEX_RPG_FONT], sfTrue);
    return 0;
}

static
int game_create(game_t *game, const window_t *win_data)
{
    if (texture_arr_create(game) || sound_arr_create(game))
        return game_unset(game), 84;
    game->scene_arr = de_arr_create(sizeof(scene_t), 4, 1);
    if (game->scene_arr == NULL)
        return DE_ERR("malloc failed"), game_unset(game), 84;
    if (set_clocks(game))
        return DE_ERR("csfml failed"), game_unset(game), 84;
    if (window_create(game, win_data))
        return DE_ERR("malloc failed"), game_unset(game), 84;
    if (font_init_sprite(game))
        return game_unset(game), 84;
    return 0;
}

int game_set(game_t *game, const window_t *win_data)
{
    memset(game->entity_arr, 0, DE_ENTITY_MAX * sizeof(entity_t));
    memset(&game->event, 0, sizeof game->event);
    if (game_create(game, win_data))
        return 84;
    game->main_delta_time = 0;
    game->game_delta_time = 0;
    game->is_running = false;
    return 0;
}

void game_unset(game_t *game)
{
    texture_arr_destroy(game);
    sound_arr_destroy(game);
    de_arr_destroy(game->scene_arr, (de_func_destroy_t *)&scene_destroy);
    sfClock_destroy(game->main_clock);
    sfClock_destroy(game->game_clock);
    window_destroy(game);
    sfSprite_destroy(game->font_sprite);
}

static
void update_clocks(game_t *game)
{
    sfInt64 curr_main_clock =
        sfClock_getElapsedTime(game->main_clock).microseconds;
    sfInt64 curr_game_clock =
        sfClock_getElapsedTime(game->game_clock).microseconds;

    game->main_delta_time =
        (double)(curr_main_clock - game->prev_main_clock) / 1000000.;
    game->game_delta_time =
        (double)(curr_game_clock - game->prev_game_clock) / 1000000.;
    game->prev_main_clock = curr_main_clock;
    game->prev_game_clock = curr_game_clock;
}

int game_update(game_t *game)
{
    scene_t *scene;

    update_clocks(game);
    event_update(game);
    for (size_t i = 0; i < game->scene_arr->data_count; i++) {
        scene = de_arr_get(game->scene_arr, i);
        if (!scene->to_update)
            continue;
        if (scene_update(game, i))
            return DE_ERR("scene update failed"), 84;
    }
    return 0;
}

void game_draw(game_t *game)
{
    scene_t *scene;

    sfRenderWindow_clear(game->window.window, sfBlack);
    for (size_t i = 0; i < game->scene_arr->data_count; i++) {
        scene = de_arr_get(game->scene_arr, i);
        if (scene->to_draw)
            scene_draw(game, i);
    }
    sfRenderWindow_display(game->window.window);
}
