#include <stdbool.h>
#include <string.h>

#include <SFML/Graphics/Types.h>
#include <SFML/System/Types.h>
#include <SFML/System/Vector2.h>

#ifndef COLLECTIBLES_H
    #define COLLECTIBLES_H

typedef enum collectible_type_s {
    WEAPON = 0,
    SHIELD = 1,
} collectible_type_t;

typedef struct collectibles_s {
    collectible_type_t type;
    bool has_changed;
    size_t collectible_id;
    sfVector2f position;
    sfTexture *texture;
    sfSprite *sprite;
} collectibles_t;

#endif
