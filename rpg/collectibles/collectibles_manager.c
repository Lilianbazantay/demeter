#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "demeter_V2/de_arr.h"
#include "demeter_V2/entity.h"
#include "demeter_V2/resources.h"
#include "demeter_V2/types.h"

#include "demeter_V2/game.h"
#include "quell/ql_base.h"
#include "rpg/game_core.h"

#include <SFML/Graphics/Rect.h>
#include <SFML/Graphics/RectangleShape.h>
#include <SFML/Graphics/RenderWindow.h>
#include <SFML/Graphics/Sprite.h>
#include <SFML/Graphics/Texture.h>
#include <SFML/Graphics/Types.h>
#include <SFML/System/Clock.h>

#include "collectibles.h"

static entity_t COLLECTIBLES_BASE;

static
const collectibles_t COLLECTIBLES_ARR[] = {
    { WEAPON, true, 1, { 655.F, 1350.F }, NULL, NULL },
    { WEAPON, true, 2, { 745.F, 465.F }, NULL, NULL },
    { WEAPON, true, 3, { 765.F, 465.F }, NULL, NULL },
    { WEAPON, true, 4, { 1115.F, 770.F }, NULL, NULL },
    { SHIELD, true, 1, { 900.F, 1500.F }, NULL, NULL },
    { SHIELD, true, 2, { 720.F, 465.F }, NULL, NULL },
    { SHIELD, true, 3, { 1135.F, 770.F }, NULL, NULL },
};

static
int collectibles_set(game_t *game, size_t id)
{
    sfTexture *eqmt_texture = game->tex_arr[TEX_EQUIPMENTS];
    collectibles_t clt[LENGTH_OF(COLLECTIBLES_ARR)];
    de_arr_t *array = de_arr_create(
        sizeof *clt, LENGTH_OF(COLLECTIBLES_ARR), 1);

    if (array == NULL)
        return 84;
    for (size_t i = 0; i < LENGTH_OF(COLLECTIBLES_ARR); i++) {
        clt[i] = COLLECTIBLES_ARR[i];
        clt[i].sprite = sfSprite_create();
        sfSprite_setTexture(clt[i].sprite, eqmt_texture, sfTrue);
        sfSprite_setPosition(clt[i].sprite, clt[i].position);
        de_arr_insert(array, &clt[i], (size_t)i);
    }
    game->entity_arr[id].data = array;
    return 0;
}

static
int collectibles_unset(game_t *game, size_t id)
{
    de_arr_t *array = game->entity_arr[id].data;

    free(array->arr);
    free(array);
    return 0;
}

static
void set_new_rect(collectibles_t *collectibles)
{
    sfIntRect rect = {
        16 * (int)collectibles->collectible_id,
        16 * (int)collectibles->type,
        16, 16
    };

    sfSprite_setTextureRect(collectibles->sprite, rect);
}

static
int collectibles_draw(game_t *game, size_t id)
{
    de_arr_t *array = game->entity_arr[id].data;
    collectibles_t *clts;

    for (size_t i = 0; i < LENGTH_OF(COLLECTIBLES_ARR); i++) {
        clts = (collectibles_t *)de_arr_get(array, i);
        if (clts->has_changed)
            set_new_rect(clts);
        sfRenderWindow_drawSprite(game->window.window, clts->sprite, NULL);
    }
    return 0;
}

int entity_collectibles(game_t *game)
{
    entity_set(game, &COLLECTIBLES_BASE, -1);
    return EXIT_OK;
}

static entity_t COLLECTIBLES_BASE = {
    .name = "collectibles",
    .set = &collectibles_set,
    .unset = &collectibles_unset,
    .draw = &collectibles_draw,
    .priority = ENT_PRIORITY_LOW,
    .is_used = true
};
