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

static entity_t WEAPONS_BASE;

static
const weapon_t WEAPON_ARR[] = {
    { true, 1, 10, 50, 10, 10, 0 },
    { false, 2, 30, 80, 10, 10, 1 },
    { false, 3, 25, 60, 15, 10, 2 },
    { false, 5, 40, 85, 20, 10, 3 },
    { false, 5, 30, 60, 25, 10, 4 },
};

static
int weapons_set(game_t *game, size_t id)
{
    weapon_t weapon[LENGTH_OF(WEAPON_ARR)];
    de_arr_t *array = de_arr_create(sizeof(weapon_t), 10, 1);

    if (array == NULL)
        return 84;
    for (size_t i = 0; i < LENGTH_OF(WEAPON_ARR); i++) {
        weapon[i] = WEAPON_ARR[i];
        de_arr_insert(array, &weapon[i], (size_t)i);
    }
    game->entity_arr[id].data = array;
    return 0;
}

static
int weapons_unset(game_t *game, size_t id)
{
    de_arr_t *array = game->entity_arr[id].data;

    free(array->arr);
    free(array);
    return 0;
}

int entity_weapons(game_t *game)
{
    entity_set(game, &WEAPONS_BASE, -1);
    return EXIT_OK;
}

static entity_t WEAPONS_BASE = {
    .name = "weapons",
    .set = &weapons_set,
    .unset = &weapons_unset,
    .priority = ENT_PRIORITY_HIGH,
    .is_used = true
};
