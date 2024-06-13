#include <stdbool.h>

#include <SFML/Graphics/Sprite.h>
#include <SFML/System/Vector2.h>
#include <SFML/Window/Keyboard.h>

#include "demeter_V2/game.h"

#include "player_data.h"
#include "rpg/collison_manager/collision_manager.h"
#include "rpg/game_core.h"

static
const player_input_t PLAYER_INPUT[] = {
    { KEY_UP, 2, 0, -1 },
    { KEY_DOWN, 1, 0, 1 },
    { KEY_LEFT, 8, -1, 0 },
    { KEY_RIGHT, 4, 1, 0 },
};

// checks if the sprite has the good rotation;
//returns True if the rotation nedds to be actualized

static
bool check_sprite_rotation(player_t *player, int new_rotat)
{
    int j = 0;
    int act_rotat = (int)player->rotation;

    if (new_rotat == 0) {
        player->rotation = IDLE;
        player->rect.top = PLAYER_SIZE * IDLE_KEYFRAME;
        return false;
    }
    if (new_rotat < act_rotat % (new_rotat * 2) || new_rotat == act_rotat)
        return true;
    for (int i = 1; i <= 8; i *= 2) {
        if (i <= new_rotat % (i * 2) && new_rotat <= i) {
            player->rotation = (float)i;
            player->rect.left = j * 16;
            return true;
        }
        j++;
    }
    return true;
}

static
bool validate_player_move(player_t *player, sfVector2f *direction)
{
    sfIntRect rect = player->rect;
    sfVector2f new_pos = {
        .x = player->position.x + direction->x,
        .y = player->position.y + direction->y
    };

    ((sfVector2i *)(&rect))[0] = (sfVector2i) {
        .x = (int)new_pos.x,
        .y = (int)new_pos.y
    };
    if (is_colliding(&rect, NULL))
        return false;
    player->position = new_pos;
    return true;
}

bool update_player_position(game_t *game, size_t id)
{
    player_t *player = game->entity_arr[id].data;
    sfVector2f new_position = {0, 0};
    int new_rotation = 0;

    for (size_t i = 0; i < LENGTH_OF(PLAYER_INPUT); i++)
        if (game->event.key_map[PLAYER_INPUT[i].KeyInput]) {
            new_rotation += PLAYER_INPUT[i].value;
            new_position.x +=
                PLAYER_INPUT[i].position_x * (float)game->game_delta_time * 96;
            new_position.y +=
                PLAYER_INPUT[i].position_y * (float)game->game_delta_time * 96;
        }
    if (new_position.x != 0 && new_position.y != 0) {
        new_position.x /= 1.5F;
        new_position.y /= 1.5F;
    }
    player->has_move = check_sprite_rotation(player, new_rotation);
    if (!validate_player_move(player, &new_position))
        return false;
    return player->has_move;
}
