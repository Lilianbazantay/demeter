#include <stdbool.h>
#include <unistd.h>

#include <SFML/Graphics/Rect.h>
#include <SFML/Graphics/RectangleShape.h>
#include <SFML/Graphics/RenderWindow.h>
#include <SFML/Graphics/Sprite.h>
#include <SFML/Graphics/Texture.h>
#include <SFML/Graphics/Types.h>
#include <SFML/System/Clock.h>
#include <SFML/Window/Mouse.h>

#include "demeter_V2/de_arr.h"
#include "demeter_V2/entity.h"
#include "demeter_V2/types.h"

#include "demeter_V2/game.h"
#include "player_data.h"
#include "rpg/game_core.h"

#include "../enemies/enemy.h"

static
bool can_player_attack(player_t *player)
{
    return !(
        player->attack.is_blocking
        && player->stats.endurance < player->inventory.weapon->cons_stamina
        && !player->attack.is_attacking
    );
}

static
bool check_attack_hitbox(player_t *player, enemy_t *enemy)
{
    sfFloatRect attack_hitbox = player->attack.attack_hitbox;

    return !(
        attack_hitbox.top + attack_hitbox.width < enemy->position.x
        || attack_hitbox.top > enemy->position.x + (float)enemy->hitbox.width
        || attack_hitbox.left + attack_hitbox.height < enemy->position.y
        || attack_hitbox.left > enemy->position.y + (float)enemy->hitbox.height
    );
}

static
void attack_enemy(player_t *player, enemy_t *enemy)
{
    enemy->stats.health -= player->inventory.weapon->damage;
    if (enemy->stats.health <= 0) {
        player->stats.exp_money += enemy->stats.exp_money;
        enemy->is_dead = true;
    } else {
        enemy->can_move = false;
        enemy->wait_timer = sfClock_create();
    }
}

static
void player_attack(player_t *player, game_t *game)
{
    int entity_enemy_id;
    de_arr_t *arr;
    enemy_t *enemy;

    if (!can_player_attack(player))
        return;
    player->stats.endurance -= player->inventory.weapon->cons_stamina;
    player->attack.attack_delay = sfClock_create();
    player->attack.is_attacking = true;
    entity_enemy_id = entity_get(game, -1, "enemies");
    if (entity_enemy_id <= 0)
        return;
    arr = game->entity_arr[entity_enemy_id].data;
    for (size_t i = 0; i < ENEMY_COUNT; i++) {
        enemy = de_arr_get(arr, i);
        if (enemy->is_dead || !enemy->is_active
            || !check_attack_hitbox(player, enemy))
            continue;
        attack_enemy(player, enemy);
    }
}

static
void check_mouse_input(game_t *game, player_t *player)
{
    if (game->event.mouse.button_click_map[sfMouseLeft]) {
        player_attack(player, game);
        return;
    }
    if (game->event.mouse.button_click_map[sfMouseRight]
        && !player->attack.is_blocking
        && player->stats.endurance > player->inventory.shield->cons_stamina) {
        player->attack.is_blocking = true;
        sfClock_restart(player->attack.parry);
        return;
    }
    if (player->attack.is_blocking
        && sfClock_getElapsedTime(player->attack.parry).microseconds
        > 570000
    )
        player->attack.is_blocking = false;
}

void check_player_attack(game_t *game, size_t id)
{
    player_t *player = game->entity_arr[id].data;

    if (player->attack.is_attacking
        && sfClock_getElapsedTime(player->attack.attack_delay).microseconds
        / 10000 > player->inventory.weapon->hit_speed) {
            sfClock_destroy(player->attack.attack_delay);
            player->attack.is_attacking = false;
        }
    check_mouse_input(game, player);
    if (!player->attack.is_attacking && !player->attack.is_blocking
        && player->stats.endurance < player->stats.max_endurance) {
        player->stats.endurance += 0.015F;
        return;
        }
    if (player->stats.endurance > player->stats.max_endurance)
        player->stats.endurance = player->stats.max_endurance;
}
