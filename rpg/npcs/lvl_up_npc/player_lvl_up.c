#include <stdbool.h>

#include <SFML/Graphics/Sprite.h>
#include <SFML/System/Clock.h>
#include <SFML/System/Vector2.h>
#include <SFML/Window/Keyboard.h>

#include "demeter_V2/game.h"

#include "../../enemies/enemy.h"
#include "struct_player.h"

static
bool player_stat_increase(player_t *player)
{
    player->stats.max_endurance += 10;
    player->stats.endurance = player->stats.max_endurance;
    player->stats.max_health += 2;
    player->stats.health = player->stats.max_health;
    player->stats.resistance += 2;
    player->stats.strength += 2;
    player->required_money *= 1.1;
    return true;
}

static
int world_level_increase(game_t *game)
{
    int enemy = entity_get(game, -1, "enemies");
    de_arr_t *arr;
    enemy_t *enemies;

    arr = game->entity_arr[enemy].data;
    for (size_t i = 0; i < 3; i++) {
        enemies = de_arr_get(arr, i);
        enemies->stats.damage += 2;
        enemies->stats.max_health += 5;
        enemies->stats.health = enemies->stats.max_health;
        enemies->stats.exp_money += 5;
        enemies->is_dead = false;
    }
    return 0;
}

int player_lvl_up(game_t *game, player_t *player)
{
    if (player->stats.exp_money >= (int)player->required_money) {
        player->level++;
        player->stats.exp_money -= (int)player->required_money;
        player_stat_increase(player);
        world_level_increase(game);
    }
    return 0;
}

int enemies_revive(game_t *game)
{
    int enemy = entity_get(game, -1, "enemies");
    de_arr_t *arr;
    enemy_t *enemies;

    arr = game->entity_arr[enemy].data;
    for (size_t i = 0; i < 3; i++) {
        enemies = de_arr_get(arr, i);
        enemies->stats.health = enemies->stats.max_health;
        enemies->is_dead = false;
    }
    return 0;
}
