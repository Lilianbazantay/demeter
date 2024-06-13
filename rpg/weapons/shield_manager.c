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
#include "demeter_V2/types.h"

#include "demeter_V2/game.h"
#include "quell/ql_base.h"
#include "rpg/game_core.h"

#include "weapons_data.h"

static entity_t WEAPONS;

static
const shield_t SHIELD_ARR[] = {
    { true, 40, 10, 10, 0 },
    { false, 35, 10, 15, 1 },
    { false, 30, 10, 20, 2 },
    { false, 20, 10, 30, 3 },
};

static
int shields_set(game_t *game, size_t id)
{
    shield_t shield[LENGTH_OF(SHIELD_ARR)];
    de_arr_t *array = de_arr_create(sizeof(shield_t), 10, 1);

    if (array == NULL)
        return 84;
    for (size_t i = 0; i < LENGTH_OF(SHIELD_ARR); i++) {
        shield[i] = SHIELD_ARR[i];
        de_arr_insert(array, &shield[i], (size_t)i);
    }
    game->entity_arr[id].data = array;
    return 0;
}

static
int shields_unset(game_t *game, size_t id)
{
    de_arr_t *array = game->entity_arr[id].data;

    free(array->arr);
    free(array);
    return 0;
}

int entity_shields(game_t *game)
{
    entity_set(game, &WEAPONS, -1);
    return EXIT_OK;
}

static entity_t WEAPONS = {
    .name = "shields",
    .set = &shields_set,
    .unset = &shields_unset,
    .priority = ENT_PRIORITY_HIGH,
    .is_used = true
};
