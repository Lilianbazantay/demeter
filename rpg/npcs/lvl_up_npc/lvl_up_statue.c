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

#include "../npcs.h"
#include "quell/ql_base.h"
#include "struct_player.h"

static entity_t NPC_BASE;

int lvlnpc_draw(game_t *game, size_t id)
{
    npc_t *lvl_npc = game->entity_arr[id].data;
    int player_id = entity_get(game, -1, "player");
    player_t *player = game->entity_arr[player_id].data;
    sfIntRect rect = {
        (int)(player->position.x - 60),
        (int)(player->position.y - 15),
        140, 60
    };

    if (lvl_npc->sprite == NULL || lvl_npc->textbox == NULL)
        return 84;
    sfRenderWindow_drawSprite(game->window.window, lvl_npc->sprite, NULL);
    if (lvl_npc->speaking == 1) {
        sfSprite_setTextureRect(lvl_npc->textbox, rect);
        sfSprite_setPosition(lvl_npc->textbox,
            (sfVector2f){player->position.x - 60, player->position.y - 15});
        sfRenderWindow_drawSprite(game->window.window, lvl_npc->textbox, NULL);
        print_text(game, lvl_npc, player);
    }
    return 0;
}

static
int check_quest_status(game_t *game, npc_t *npc, player_t *player)
{
    switch (npc->state) {
        case NEVER:
            return never_quest(game, npc);
        case QUEST_NOT:
            return quest_dial(game, npc, player);
        case QUEST_ACC:
            return quest_conti(game, npc, player);
        case MONEY_REQ:
            return lvl_up(game, npc, player);
        case QUEST_DONE:
            return retry(game, npc);
        default:
            return 84;
    }
}

int lvlnpc_update(game_t *game, size_t id)
{
    npc_t *lvl_npc = game->entity_arr[id].data;
    player_t *player = check_interaction(game, lvl_npc);

    if (player != NULL)
        return check_quest_status(game, lvl_npc, player);
    return 0;
}

int lvlnpc_unset(game_t *game, size_t id)
{
    npc_t *lvl_npc = game->entity_arr[id].data;

    sfSprite_destroy(lvl_npc->sprite);
    free(lvl_npc);
    return 0;
}

int lvlnpc_set(game_t *game, size_t id)
{
    npc_t *lvl_npc = malloc(sizeof(npc_t));

    if (lvl_npc == NULL)
        return 84;
    lvl_npc->state = NEVER;
    lvl_npc->size = (sfFloatRect){1182., 265., 24., 16.};
    lvl_npc->speaking = 0;
    lvl_npc->sprite = sfSprite_create();
    lvl_npc->textbox = sfSprite_create();
    if (lvl_npc->sprite == NULL || lvl_npc->textbox == NULL)
        return free(lvl_npc), 84;
    sfSprite_setTexture(lvl_npc->textbox, game->tex_arr[TEX_NPC_BOX], false);
    sfSprite_setPosition(lvl_npc->sprite,
        (sfVector2f){lvl_npc->size.top, lvl_npc->size.left});
    sfSprite_setTexture(lvl_npc->sprite, game->tex_arr[TEX_NPC_LVL], true);
    game->entity_arr[id].data = (void *)lvl_npc;
    return 0;
}

int entity_lvl_up(game_t *game)
{
    entity_set(game, &NPC_BASE, -1);
    return EXIT_OK;
}

static entity_t NPC_BASE = {
    .name = "npc",
    .set = &lvlnpc_set,
    .unset = &lvlnpc_unset,
    .update = &lvlnpc_update,
    .draw = &lvlnpc_draw,
    .priority = ENT_PRIORITY_HIGH,
    .is_used = true
};
