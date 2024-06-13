#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <SFML/Graphics/Rect.h>
#include <SFML/Graphics/RenderWindow.h>
#include <SFML/Graphics/Sprite.h>
#include <SFML/Graphics/Types.h>
#include <SFML/Window/Keyboard.h>

#include "quell/ql_base.h"

#include "demeter_V2/entity.h"
#include "demeter_V2/game.h"
#include "demeter_V2/types.h"

#include "../npcs.h"
#include "font_system/font_handler.h"
#include "struct_player.h"

static char const TEXT_QUEST[] = {
    "You see i need a certain amount of money, it should be around %d. "
    "Can you come back once you have accumulated that amount ?"
    "Also if you need to rest, just come to see me. "
    "You'll rest long enough for the monsters to reappear.\n"
    "Also, don't forget to get your shield ! "
    "You'll find it to the laboratory.\n"
};

static char const TEXT_CONTI[] = {
    "Oh you haven't brought enough money.\n"
    "Well then rest here for the time being, "
    "monsters will reappear in the meantime.\n"
};

static char const TEXT_MONEY[] = {
    "I see, you brought enough money. "
    "As reward, here, allow me to make you stronger.\n"
    "Don't forget, as you get stronger, monsters will also grow stronger. "
    "So be wary on your travels."
};

static char const TEXT_RESET[] = {
    "Thank you for bringing me that money dear traveler.\n"
    "I wish you good luck for your travels. "
    "Don't forget that I'll stay here if you ever need to grow stronger."
};

player_t *check_interaction(game_t *game, npc_t *npc)
{
    int player_id = entity_get(game, -1, "player");
    sfFloatRect *rect_to_fill = { 0 };
    player_t *player = game->entity_arr[player_id].data;
    sfFloatRect rect = player->attack.attack_hitbox;
    int intersect = sfFloatRect_intersects(&rect, &npc->size, rect_to_fill);

    if (intersect && game->event.key_map[sfKeySpace]) {
        npc->speaking = 1;
        return player;
    }
    if (intersect)
        return NULL;
    npc->speaking = 0;
    return NULL;
}

static
char *char_quest(player_t *player)
{
    char *text = malloc(SSTRLEN(TEXT_QUEST) + 10);

    if (text == NULL)
        return NULL;
    snprintf(text,
        SSTRLEN(TEXT_QUEST), TEXT_QUEST,
        (int)player->required_money);
    return text;
}

int print_text(game_t *game, npc_t *npc, player_t *player)
{
    sfVector2f pos = { player->position.x - 60, player->position.y - 15 };
    sfFloatRect text_rect = { pos.x + 10, pos.y + 10, 120., 70. };

    if (npc->state == QUEST_NOT)
        return font_handle(game, char_quest(player), text_rect, sfWhite);
    if (npc->state == QUEST_ACC)
        return font_handle(game, TEXT_CONTI, text_rect, sfWhite);
    if (npc->state == MONEY_REQ)
        return font_handle(game, TEXT_MONEY, text_rect, sfWhite);
    if (npc->state == QUEST_DONE)
        return font_handle(game, TEXT_RESET, text_rect, sfWhite);
    return 0;
}
