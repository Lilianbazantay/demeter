#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <SFML/Graphics/Rect.h>
#include <SFML/Graphics/RectangleShape.h>
#include <SFML/Graphics/RenderWindow.h>
#include <SFML/Graphics/Sprite.h>
#include <SFML/Graphics/Texture.h>
#include <SFML/Graphics/Types.h>
#include <SFML/System/Clock.h>

#include "demeter_V2/de_arr.h"
#include "demeter_V2/entity.h"
#include "demeter_V2/game.h"
#include "demeter_V2/resources.h"
#include "demeter_V2/types.h"

#include "enemy.h"
#include "quell/ql_base.h"
#include "rpg/game_core.h"

#include "../player/player_data.h"

static entity_t ENEMY_BASE;

static
int enemy_update(game_t *game, size_t id)
{
    int result = entity_get(game, -1, "player");
    de_arr_t *array = game->entity_arr[id].data;
    player_t *player;
    enemy_t *enemy;

    if (result == -1)
        return 84;
    player = game->entity_arr[result].data;
    for (size_t i = 0; i < ENEMY_COUNT; i++) {
        enemy = de_arr_get(array, i);
        if (enemy->is_dead)
            continue;
        enemy->is_active = check_if_entity_active(enemy, player->position);
        if (!enemy->is_active)
            continue;
        check_enemy_movement(enemy, player);
        check_enemy_attack(game, enemy, player);
    }
    return 0;
}

static
void set_enemy_parameters(game_t *game, de_arr_t *arr, enemy_t *enemy, int i)
{
    sfIntRect rect = { 0, 0, 16, 24 };
    sfVector2f position = { 100 + (float)i * 50, 100 + (float)i * 10 };

    if (i > 6) {
        position.x = 700 + 25 * (float)(i - 6);
        position.y = 880 + 25 * (float)(i - 6);
    }
    if (i > 15) {
        position.x += 30;
        position.y += 5;
    }
    enemy[i].position = position;
    enemy[i].start_position = position;
    enemy[i].hitbox = rect;
    sfSprite_setTextureRect(enemy[i].sprite, rect);
    sfSprite_setTexture(enemy[i].sprite, game->tex_arr[TEX_ENEMY_1], sfTrue);
    sfSprite_setPosition(enemy[i].sprite, enemy[i].position);
    sfSprite_setTextureRect(enemy[i].sprite, rect);
    de_arr_insert(arr, &enemy[i], (size_t)i);
}

static
int enemy_set(game_t *game, size_t id)
{
    de_arr_t *array = de_arr_create(sizeof(enemy_t), 10, 1);
    enemy_t enemy_arr[ENEMY_COUNT];

    if (array == NULL)
        return 84;
    for (size_t i = 0; i < ENEMY_COUNT; i++) {
        enemy_arr[i].is_active = false;
        enemy_arr[i].can_move = true;
        enemy_arr[i].is_dead = false;
        enemy_arr[i].stats.damage = 1;
        enemy_arr[i].stats.max_health = 10;
        enemy_arr[i].stats.health = 10;
        enemy_arr[i].stats.exp_money = 100;
        enemy_arr[i].sprite = sfSprite_create();
        set_enemy_parameters(game, array, enemy_arr, (int)i);
    }
    game->entity_arr[id].data = array;
    return 0;
}

static
int enemy_unset(game_t *game, size_t id)
{
    de_arr_t *array = game->entity_arr[id].data;
    enemy_t *enemy;

    for (size_t i = 0; i < ENEMY_COUNT; i++) {
        enemy = de_arr_get(array, i);
        sfSprite_destroy(enemy->sprite);
    }
    free(array->arr);
    free(array);
    return 0;
}

static
int enemy_draw(game_t *game, size_t id)
{
    de_arr_t *array = game->entity_arr[id].data;
    enemy_t *enemy;

    for (size_t i = 0; i < ENEMY_COUNT; i++) {
        enemy = (de_arr_get(array, i));
        if (!enemy->is_dead && enemy->is_active)
            sfRenderWindow_drawSprite(game->window.window,
            enemy->sprite, NULL);
    }
    return 0;
}

int entity_enemy_arr(game_t *game)
{
    entity_set(game, &ENEMY_BASE, -1);
    return EXIT_OK;
}

static entity_t ENEMY_BASE = {
    .name = "enemies",
    .set = &enemy_set,
    .unset = &enemy_unset,
    .update = &enemy_update,
    .draw = &enemy_draw,
    .priority = ENT_PRIORITY_HIGH,
    .is_used = true
};
