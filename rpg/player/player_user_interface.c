#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

#include <SFML/Graphics/Color.h>
#include <SFML/Graphics/Export.h>
#include <SFML/Graphics/Rect.h>
#include <SFML/Graphics/RectangleShape.h>
#include <SFML/Graphics/RenderWindow.h>
#include <SFML/Graphics/Sprite.h>
#include <SFML/Graphics/Transform.h>
#include <SFML/Graphics/Types.h>
#include <SFML/System/Clock.h>
#include <SFML/System/Types.h>
#include <SFML/System/Vector2.h>
#include <SFML/Window/Keyboard.h>

#include "demeter_V2/game.h"
#include "player_data.h"
#include "rpg/game_core.h"

#include "../collectibles/collectibles.h"

static
void update_ui_position(game_t *game, player_t *player)
{
    sfFloatRect win = game->window.internal;
    sfVector2f item = { win.left + 8, win.top + win.height - 23 };
    sfVector2f item2 = item;

    item2.x += ITEM_SIZE + 8;
    sfSprite_setPosition(player->ui.sprite, *(sfVector2f *)&win);
    sfSprite_setPosition(player->ui.shield_spr, item);
    sfSprite_setPosition(player->ui.weapon_spr, item2);
}

static
void update_ui_inventory(player_t *player)
{
    sfIntRect rect = {
        (int)player->inventory.weapon->id * ITEM_SIZE, ITEM_WEAPON_LAYER,
        ITEM_SIZE, ITEM_SIZE
    };

    sfSprite_setTextureRect(player->ui.weapon_spr, rect);
    rect.left = (int)player->inventory.shield->id * ITEM_SIZE;
    rect.top = ITEM_SHIELD_LAYER;
    sfSprite_setTextureRect(player->ui.shield_spr, rect);
}

void update_player_ui(game_t *game, size_t id)
{
    player_t *player = game->entity_arr[id].data;

    if (player->has_move)
        update_ui_position(game, player);
    if (player->inventory.is_changing_equipment)
        update_ui_inventory(player);
}

static
void player_draw_lifebar(game_t *game, player_t *player, sfSprite *lifebar)
{
    sfVector2f position = {
        game->window.internal.left + 4, game->window.internal.top };
    sfIntRect rect = { 96, 0, 16, 16 };
    sfIntRect new_rect = { 96, 16, 16, 16 };
    int start_health = 0;

    for (; start_health <= player->stats.max_health; position.x += 16) {
        sfSprite_setPosition(lifebar, position);
        if (start_health + 5 > player->stats.max_health)
            rect.left = (player->stats.max_health - start_health) * 16;
        sfSprite_setTextureRect(lifebar, rect);
        sfRenderWindow_drawSprite(game->window.window, lifebar, NULL);
        start_health += 5;
        if (start_health > player->stats.health + 5)
            continue;
        if (start_health > player->stats.health)
            new_rect.left = (5 - (start_health - player->stats.health)) * 16;
        sfSprite_setTextureRect(lifebar, new_rect);
        sfRenderWindow_drawSprite(game->window.window, lifebar, NULL);
    }
}

static
void player_draw_stamina_helper(
    game_t *game, sfSprite *stamina, sfIntRect *rect)
{
    sfSprite_setTextureRect(stamina, *rect);
    sfRenderWindow_drawSprite(game->window.window, stamina, NULL);
}

static
void player_draw_stamina(game_t *game, player_t *player, sfSprite *stamina)
{
    float sta_stamina = 0;
    stats_t *pstat = &player->stats;
    sfIntRect rects[] = {{ 96, 32, 16, 16 }, { 224, 48, 16, 16 }};
    sfVector2f position = {
        game->window.internal.left + 4, game->window.internal.top
    };

    for (; sta_stamina <= pstat->max_endurance; position.x += 16) {
        sfSprite_setPosition(stamina, position);
        if (sta_stamina + 25 > pstat->max_endurance)
            rects[0].left = (int)(pstat->max_endurance -sta_stamina) / 5 * 16;
        player_draw_stamina_helper(game, stamina, &rects[0]);
        sta_stamina += 25;
        if (sta_stamina > pstat->endurance + 25)
            continue;
        if (sta_stamina > pstat->endurance)
            rects[1].left -= (int)(
                (sta_stamina - pstat->endurance) / 25 * 15) * 16;
        player_draw_stamina_helper(game, stamina, &rects[1]);
    }
}

void player_draw_ui(game_t *game, size_t id)
{
    player_t *p = game->entity_arr[id].data;

    sfRenderWindow_drawSprite(game->window.window, p->ui.sprite, NULL);
    sfRenderWindow_drawSprite(game->window.window, p->ui.weapon_spr, NULL);
    sfRenderWindow_drawSprite(game->window.window, p->ui.shield_spr, NULL);
    player_draw_lifebar(game, p, p->ui.bars);
    player_draw_stamina(game, p, p->ui.bars);
}
