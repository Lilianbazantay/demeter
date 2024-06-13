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

#include "../player/player_data.h"

static const float ENEMY_SPEED = 0.03F;

static
void get_enemy_movement(enemy_t *enemy, player_t *player)
{
    if (player->position.x < enemy->position.x) {
        enemy->position.x -= ENEMY_SPEED;
        if (enemy->hitbox.left != 0) {
            enemy->hitbox.left = 0;
            sfSprite_setTextureRect(enemy->sprite, enemy->hitbox);
        }
    } else {
        enemy->position.x += ENEMY_SPEED;
        if (enemy->hitbox.left != 16) {
            enemy->hitbox.left = 16;
            sfSprite_setTextureRect(enemy->sprite, enemy->hitbox);
        }
    }
    if (player->position.y < enemy->position.y)
        enemy->position.y -= ENEMY_SPEED;
    else
        enemy->position.y += ENEMY_SPEED;
}

void check_enemy_movement(enemy_t *enemy, player_t *player)
{
    if (!enemy->can_move)
        return;
    get_enemy_movement(enemy, player);
    sfSprite_setPosition(enemy->sprite, enemy->position);
}
