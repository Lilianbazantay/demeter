#include <stdbool.h>
#include <unistd.h>

#include <SFML/Graphics/Rect.h>
#include <SFML/Graphics/RectangleShape.h>
#include <SFML/Graphics/RenderWindow.h>
#include <SFML/Graphics/Sprite.h>
#include <SFML/Graphics/Texture.h>
#include <SFML/Graphics/Types.h>
#include <SFML/System/Clock.h>

#include "enemy.h"

#include "rpg/game_logic/ent_game_logic.h"
#include "rpg/player/player_data.h"

static const float ATTACK_RANGE = 10.F;

static
void game_back_to_menu(game_t *game)
{
    ent_game_logic_t *game_logic;
    char name[DE_ENTITY_NAME_MAX] = "game logic";
    int id = entity_get(game, 0, name);

    if (id == -1)
        return;
    game_logic = game->entity_arr[id].data;
    game_logic->new_state = GAME_STATUS_MAIN_MENU;
}

static
void check_attack_range(game_t *game, enemy_t *enemy, player_t *player)
{
    if (enemy->position .x > player->position.x + ATTACK_RANGE
        || enemy->position .x < player->position.x - ATTACK_RANGE)
        return;
    if (enemy->position .y > player->position.y + ATTACK_RANGE
        || enemy->position .y < player->position.y - ATTACK_RANGE)
        return;
    enemy->wait_timer = sfClock_create();
    enemy->can_move = false;
    if (player->attack.is_blocking)
        player->stats.endurance -= player->inventory.shield->cons_stamina;
    else
        player->stats.health -= enemy->stats.damage;
    if (player->stats.health <= 0)
        game_back_to_menu(game);
}

void check_enemy_attack(game_t *game, enemy_t *enemy, player_t *player)
{
    if (enemy->can_move) {
        check_attack_range(game, enemy, player);
        return;
    }
    if (sfClock_getElapsedTime(enemy->wait_timer).microseconds / 100000 > 8) {
        sfClock_destroy(enemy->wait_timer);
        enemy->can_move = true;
    }
}
