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

#include "demeter_V2/entity.h"
#include "demeter_V2/game.h"
#include "demeter_V2/types.h"

#include "quell/ql_base.h"

#include "font_system/font_handler.h"

#include "../../player/player_data.h"
#include "../npcs.h"

static entity_t SIGN_BASE;

static
const char CONTROLS[] = {
    "Move with ZQSD (or WASD)\n"
    "Interactions:\n"
    "* Attacking: Left click\n"
    "* Defending; Right click\n"
    "* Talking: Space\n"
    "* Picking up items: F\n"
};

int sign_draw(game_t *game, size_t id)
{
    npc_t *sign = game->entity_arr[id].data;
    int player_id = entity_get(game, -1, "player");
    player_t *player = game->entity_arr[player_id].data;
    sfIntRect rect = { 0, 0, 100, 50 };
    sfVector2f pos = { player->position.x - 45, player->position.y };

    if (sign->sprite == NULL || sign->textbox == NULL)
        return 84;
    sfRenderWindow_drawSprite(game->window.window, sign->sprite, NULL);
    if (sign->speaking == 1) {
        sfSprite_setPosition(sign->textbox, pos);
        sfSprite_setTextureRect(sign->textbox, rect);
        sfRenderWindow_drawSprite(game->window.window, sign->textbox, NULL);
        font_handle(game, CONTROLS,
            (sfFloatRect){ pos.x + 10, pos.y + 10, 120.F, 120.F }, sfWhite);
    }
    return 0;
}

int sign_update(game_t *game, size_t id)
{
    npc_t *sign = game->entity_arr[id].data;
    int player_id = entity_get(game, -1, "player");
    player_t *player = game->entity_arr[player_id].data;
    sfFloatRect *rect_fill = { 0 };

    if (sfFloatRect_intersects(&sign->size,
        &player->attack.attack_hitbox, rect_fill)
        || (player->position.x == 200. && player->position.y == 1300.))
        sign->speaking = 1;
    else
        sign->speaking = 0;
    return 0;
}

int sign_unset(game_t *game, size_t id)
{
    npc_t *sign = (npc_t *)game->entity_arr[id].data;

    sfSprite_destroy(sign->sprite);
    free(sign);
    return 0;
}

int sign_set(game_t *game, size_t id)
{
    npc_t *sign = malloc(sizeof(npc_t));

    if (sign == NULL)
        return 84;
    sign->state = NEVER;
    sign->size = (sfFloatRect){1320., 200., 24., 16.};
    sign->speaking = 0;
    sign->sprite = sfSprite_create();
    sign->textbox = sfSprite_create();
    if (sign->sprite == NULL || sign->textbox == NULL)
        return free(sign), 84;
    sfSprite_setScale(sign->textbox, (sfVector2f){1.05F, 1.05F});
    sfSprite_setPosition(sign->textbox, (sfVector2f){125, 1285});
    sfSprite_setTexture(sign->textbox, game->tex_arr[TEX_NPC_BOX], true);
    sfSprite_setPosition(sign->sprite,
        (sfVector2f){sign->size.top, sign->size.left});
    sfSprite_setTexture(sign->sprite, game->tex_arr[TEX_SIGN], false);
    game->entity_arr[id].data = (void *)sign;
    return 0;
}

int entity_sign(game_t *game)
{
    entity_set(game, &SIGN_BASE, -1);
    return EXIT_OK;
}

static entity_t SIGN_BASE = {
    .name = "sign",
    .set = &sign_set,
    .unset = &sign_unset,
    .update = &sign_update,
    .draw = &sign_draw,
    .priority = ENT_PRIORITY_HIGH,
    .is_used = true
};
