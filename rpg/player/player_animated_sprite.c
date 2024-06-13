#include <stdbool.h>

#include <SFML/Graphics/Sprite.h>
#include <SFML/System/Clock.h>
#include <SFML/System/Vector2.h>
#include <SFML/Window/Keyboard.h>

#include "demeter_V2/game.h"
#include "player_data.h"
#include "rpg/game_core.h"

void player_animated_sprite(game_t *game, size_t id)
{
    player_t *player = game->entity_arr[id].data;
    sfInt64 ms = sfClock_getElapsedTime(player->clock).microseconds;
    int new_sprite = 0;

    ms /= 10000;
    for (int i = 25; i < ms % 100; i += 25)
        new_sprite += PLAYER_SIZE;
    player->rect.top = new_sprite;
}
