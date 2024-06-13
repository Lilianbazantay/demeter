#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "demeter_V2/de_arr.h"
#include "demeter_V2/entity.h"
#include "demeter_V2/resources.h"
#include "demeter_V2/types.h"

#include "demeter_V2/game.h"
#include "quell/ql_base.h"
#include "rpg/game_core.h"

#include <SFML/Graphics/Color.h>
#include <SFML/Graphics/Rect.h>
#include <SFML/Graphics/RectangleShape.h>
#include <SFML/Graphics/RenderWindow.h>
#include <SFML/Graphics/Sprite.h>
#include <SFML/Graphics/Texture.h>
#include <SFML/Graphics/Types.h>
#include <SFML/System/Clock.h>
#include <SFML/System/Vector2.h>

#include "player_data.h"

static entity_t PLAYER;

static
int player_update(game_t *game, size_t id)
{
    player_t *player = game->entity_arr[id].data;

    if (player->has_move)
        player_animated_sprite(game, id);
    update_player_position(game, id);
    sfSprite_setTextureRect(player->sprite, player->rect);
    check_player_hitbox(game, id);
    check_player_attack(game, id);
    check_player_interactions(game, id);
    update_player_ui(game, id);
    return 0;
}

static
void set_player_inventory(game_t *game, player_t *player)
{
    int weapon_arr_id = entity_get(game, -1, "weapons");
    int shield_arr_id = entity_get(game, -1, "shields");
    de_arr_t *arr = game->entity_arr[weapon_arr_id].data;

    player->inventory.weapon = de_arr_get(arr, 0);
    arr = game->entity_arr[shield_arr_id].data;
    player->inventory.shield = de_arr_get(arr, 0);
    player->inventory.is_changing_equipment = false;
}

static
void set_player_stats_and_attack(player_t *player)
{
    sfFloatRect attack_hitbox = { 0, 0, PLAYER_SIZE, PLAYER_SIZE };

    player->attack.attack_hitbox = attack_hitbox;
    player->attack.parry = sfClock_create();
    player->attack.is_attacking = false;
    player->attack.is_blocking = false;
    player->stats.max_health = 10;
    player->stats.health = 10;
    player->stats.endurance = 100;
    player->stats.max_endurance = 100;
    player->stats.exp_money = 0;
    player->stats.strength = 10;
    player->stats.resistance = 10;
    player->level = 1;
    player->required_money = 100;
}

static
void set_player_parameters(game_t *game, player_t *player)
{
    sfIntRect rect = { 0, 0, PLAYER_SIZE, PLAYER_SIZE };
    sfVector2f position = { 200, 1300 };
    sfVector2f scale = { PLAYER_SIZE, PLAYER_SIZE };
    int half = PLAYER_SIZE >> 1;

    player->rect = rect;
    player->position = position;
    sfRectangleShape_setFillColor(player->attack_sprite, sfTransparent);
    sfRectangleShape_setPosition(player->attack_sprite, position);
    sfRectangleShape_setSize(player->attack_sprite, scale);
    sfSprite_setTextureRect(player->sprite, player->rect);
    sfSprite_setPosition(player->sprite, player->position);
    sfSprite_setTexture(player->sprite, game->tex_arr[TEX_PLAYER], sfTrue);
    window_move(game,
        (int)(player->position.x - game->window.internal.width / 2.+ half),
        (int)(player->position.y - game->window.internal.height / 2. + half));
}

static
void set_player_ui(game_t *game, player_t *player)
{
    sfIntRect rect = { 0, 0, PLAYER_SIZE, PLAYER_SIZE };
    sfVector2f position = {
        player->position.x - 72, player->position.y - 52
    };

    player->ui.position = position;
    player->ui.sprite = sfSprite_create();
    player->ui.weapon_spr = sfSprite_create();
    player->ui.shield_spr = sfSprite_create();
    player->ui.bars = sfSprite_create();
    sfSprite_setTexture(player->ui.sprite,
        game->tex_arr[TEX_USER_INTERFACE], sfTrue);
    sfSprite_setTexture(player->ui.weapon_spr,
        game->tex_arr[TEX_EQUIPMENTS], sfTrue);
    sfSprite_setTexture(player->ui.shield_spr,
        game->tex_arr[TEX_EQUIPMENTS], sfTrue);
    sfSprite_setTexture(player->ui.bars, game->tex_arr[TEX_UI_BARS], sfTrue);
    sfSprite_setTextureRect(player->ui.weapon_spr, rect);
    sfSprite_setTextureRect(player->ui.shield_spr, rect);
    sfSprite_setPosition(player->ui.sprite, player->ui.position);
}

static
int player_set(game_t *game, size_t id)
{
    player_t *player = malloc(sizeof(player_t));

    if (player == NULL)
        return 84;
    player->has_move = true;
    player->attack_sprite = sfRectangleShape_create();
    player->sprite = sfSprite_create();
    player->clock = sfClock_create();
    player->rotation = DOWN;
    if (player->sprite == NULL || player->attack_sprite == NULL)
        return free(player), 84;
    set_player_stats_and_attack(player);
    set_player_parameters(game, player);
    set_player_inventory(game, player);
    set_player_ui(game, player);
    game->entity_arr[id].data = (void *)player;
    return 0;
}

static
int player_unset(game_t *game, size_t id)
{
    player_t *player = (player_t *)game->entity_arr[id].data;

    sfSprite_destroy(player->ui.sprite);
    sfSprite_destroy(player->ui.weapon_spr);
    sfSprite_destroy(player->ui.shield_spr);
    sfSprite_destroy(player->sprite);
    sfRectangleShape_destroy(player->attack_sprite);
    sfClock_destroy(player->clock);
    free(player);
    return 0;
}

static
int player_draw(game_t *game, size_t id)
{
    player_t *player = (player_t *)game->entity_arr[id].data;
    sfFloatRect win = game->window.internal;
    sfVector2f pos = {
        win.left + ((win.width - (float)player->rect.width) / 2),
        win.top + ((win.height - (float)player->rect.height) / 2),
    };

    if (player->sprite == NULL)
        return 84;
    sfSprite_setPosition(player->sprite, pos);
    sfRenderWindow_drawSprite(game->window.window, player->sprite, NULL);
    sfRenderWindow_drawRectangleShape(game->window.window,
        player->attack_sprite, NULL);
    player_draw_ui(game, id);
    return 0;
}

int entity_player(game_t *game)
{
    entity_set(game, &PLAYER, -1);
    return EXIT_OK;
}

static entity_t PLAYER = {
    .name = "player",
    .set = &player_set,
    .unset = &player_unset,
    .update = &player_update,
    .draw = &player_draw,
    .priority = ENT_PRIORITY_MEDIUM,
    .is_used = true
};
