#ifndef ENT_MAIN_MENU_BACKGROUND_H
    #define ENT_MAIN_MENU_BACKGROUND_H

    #include <SFML/Graphics/Types.h>
    #include <SFML/System/Vector2.h>

    #include "demeter_V2/types.h"

typedef struct {
    sfSprite *sprite;
    sfVector2f pos;
} ent_main_menu_background_t;

int ent_main_menu_background_set(game_t *game, size_t id);
int ent_main_menu_background_unset(game_t *game, size_t id);
int ent_main_menu_background_draw(game_t *game, size_t id);
int ent_main_menu_background_update(game_t *game, size_t id);

#endif  // ENT_MAIN_MENU_BACKGROUND_H
