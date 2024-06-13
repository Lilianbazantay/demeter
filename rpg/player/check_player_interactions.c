#include <stdbool.h>
#include <stddef.h>

#include <SFML/Graphics/Color.h>
#include <SFML/Graphics/Export.h>
#include <SFML/Graphics/RectangleShape.h>
#include <SFML/Graphics/Sprite.h>
#include <SFML/Graphics/Transform.h>
#include <SFML/Graphics/Types.h>
#include <SFML/System/Clock.h>
#include <SFML/System/Types.h>
#include <SFML/System/Vector2.h>
#include <SFML/Window/Keyboard.h>

#include "demeter_V2/de_arr.h"
#include "demeter_V2/game.h"
#include "player_data.h"
#include "rpg/game_core.h"

#include "../collectibles/collectibles.h"

static
bool is_position_in_hitbox(sfVector2f target_pos, player_t *player)
{
    sfFloatRect area = player->attack.attack_hitbox;

    return !(
        area.top > target_pos.x
        || area.left > target_pos.y
        || area.top + area.height < target_pos.x
        || area.left + area.width < target_pos.y
    );
}

static
void switch_weapon(game_t *game, collectibles_t *collect, player_t *player)
{
    int equipment_id;
    de_arr_t *arr;
    weapon_t *weapon;

    equipment_id = entity_get(game, -1, "weapons");
    arr = game->entity_arr[equipment_id].data;
    weapon = de_arr_get(arr, collect->collectible_id);
    if (weapon->req_strength > player->stats.strength)
        return;
    collect->collectible_id = player->inventory.weapon->id;
    player->inventory.weapon = weapon;
    player->inventory.is_changing_equipment = true;
    player->inventory.clock = sfClock_create();
}

static
void switch_shield(game_t *game, collectibles_t *collect, player_t *player)
{
    int equipment_id;
    de_arr_t *arr;
    shield_t *shield;

    equipment_id = entity_get(game, -1, "shields");
    arr = game->entity_arr[equipment_id].data;
    shield = de_arr_get(arr, collect->collectible_id);
    if (shield->req_resistance > player->stats.resistance)
        return;
    collect->collectible_id = player->inventory.shield->id;
    player->inventory.shield = shield;
    player->inventory.is_changing_equipment = true;
    player->inventory.clock = sfClock_create();
}

static
void check_collectibles_in_hibox(game_t *game, player_t *player, int coll_id)
{
    de_arr_t *arr = game->entity_arr[coll_id].data;
    collectibles_t *clts;

    for (size_t i = 0; i < arr->data_count; i++) {
        clts = de_arr_get(arr, i);
        if (!is_position_in_hitbox(clts->position, player))
            continue;
        if (clts->type == WEAPON)
            switch_weapon(game, clts, player);
        else
            switch_shield(game, clts, player);
        break;
    }
}

static bool
is_already_took(player_t *player)
{
    sfInt64 ms;

    if (!player->inventory.is_changing_equipment)
        return false;
    ms = sfClock_getElapsedTime(player->inventory.clock).microseconds;
    if (ms / 10000 > 85) {
        sfClock_destroy(player->inventory.clock);
        player->inventory.is_changing_equipment = false;
        return false;
    }
    return true;
}

void check_player_interactions(game_t *game, size_t id)
{
    player_t *player = game->entity_arr[id].data;
    int collectibles_arr_id;

    if (is_already_took(player))
        return;
    if (player->attack.is_attacking || player->attack.is_blocking)
        return;
    if (!game->event.key_map[sfKeyF])
        return;
    collectibles_arr_id = entity_get(game, -1, "collectibles");
    check_collectibles_in_hibox(game, player, collectibles_arr_id);
}
