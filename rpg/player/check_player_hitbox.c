#include <stdbool.h>
#include <stddef.h>

#include <SFML/Graphics/Color.h>
#include <SFML/Graphics/Export.h>
#include <SFML/Graphics/RectangleShape.h>
#include <SFML/Graphics/Sprite.h>
#include <SFML/Graphics/Transform.h>
#include <SFML/Graphics/Types.h>
#include <SFML/System/Vector2.h>
#include <SFML/Window/Keyboard.h>

#include "demeter_V2/game.h"
#include "demeter_V2/window.h"
#include "player_data.h"
#include "rpg/game_core.h"

static
const hitbox_tab_t HITBOX_TAB[] = {
    { DOWN, -0.17F, 1.5F, 1, 1 },
    { TOP, -0.17F, -1.15F, 1, 1 },
    { LEFT, -0.9F, 0, 0.8F, 1.4F },
    { RIGHT, 0.75F, 0, 0.8F, 1.4F }
};

static
void set_player_hitbox_direction(player_t *player)
{
    sfVector2f hitbox_pos = { 25, 17 };
    sfVector2f hitbox_scale = { 25, 17 };

    for (size_t i = 0; i < LENGTH_OF(HITBOX_TAB); i++)
        if (HITBOX_TAB[i].rotation == player->rotation) {
            hitbox_pos.x = (float)HITBOX_TAB[i].x *
                hitbox_pos.x + player->position.x;
            player->attack.attack_hitbox.top = hitbox_pos.x;
            hitbox_pos.y = (float)HITBOX_TAB[i].y *
                hitbox_pos.y + player->position.y;
            player->attack.attack_hitbox.left = hitbox_pos.y;
            hitbox_scale.x = HITBOX_TAB[i].whidth * hitbox_scale.x;
            hitbox_scale.y = HITBOX_TAB[i].height * hitbox_scale.y;
            sfRectangleShape_setPosition(player->attack_sprite,
                hitbox_pos);
            sfRectangleShape_setSize(player->attack_sprite, hitbox_scale);
            return;
        }
}

bool check_player_hitbox(game_t *game, size_t id)
{
    player_t *player = game->entity_arr[id].data;

    if (!player->has_move)
        return false;
    window_move(game,
        (int)(player->position.x - game->window.internal.width / 2. + 8),
        (int)(player->position.y- game->window.internal.height / 2. + 8));
    set_player_hitbox_direction(player);
    return true;
}
