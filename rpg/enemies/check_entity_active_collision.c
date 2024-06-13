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

__attribute__((pure))
bool check_if_entity_active(enemy_t *enemy, sfVector2f position)
{
    return !(
        (enemy->position.x < position.x - 96)
        || (enemy->position.x > position.x + 96)
        || (enemy->position.y < position.y - 84)
        || (enemy->position.y > position.y + 84)
    );
}
