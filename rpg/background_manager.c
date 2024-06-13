#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

#include <SFML/Graphics/RenderWindow.h>
#include <SFML/Graphics/Sprite.h>
#include <SFML/Graphics/Texture.h>
#include <SFML/Graphics/Types.h>

#include "demeter_V2/entity.h"
#include "demeter_V2/game.h"
#include "demeter_V2/resources.h"
#include "demeter_V2/types.h"

#include "rpg/game_core.h"

static entity_t BACKGROUND_BASE;

static
int background_set(game_t *game, size_t id)
{
    sfSprite *background = sfSprite_create();

    if (background == NULL)
        return EXIT_KO;
    game->entity_arr[id].data = background;
    return EXIT_OK;
}

static
int background_unset(game_t *game, size_t id)
{
    sfSprite *bg = game->entity_arr[id].data;

    sfSprite_destroy(bg);
    return EXIT_OK;
}

static
int background_draw(game_t *game, size_t id)
{
    sfSprite *bg = game->entity_arr[id].data;

    sfRenderWindow_drawSprite(game->window.window, bg, NULL);
    return EXIT_OK;
}

static
int background_update(game_t *game, size_t id)
{
    sfSprite *bg = game->entity_arr[id].data;

    sfSprite_setTexture(bg, game->tex_arr[TEX_BACKGROUND], sfTrue);
    return EXIT_OK;
}

int entity_background(game_t *game)
{
    entity_set(game, &BACKGROUND_BASE, -1);
    return EXIT_OK;
}

static entity_t BACKGROUND_BASE = {
    .name = "background",
    .set = &background_set,
    .unset = &background_unset,
    .update = &background_update,
    .draw = &background_draw,
    .priority = ENT_PRIORITY_LOW,
    .is_used = true
};
