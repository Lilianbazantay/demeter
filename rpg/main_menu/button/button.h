#ifndef ENT_MAIN_MENU_BUTTON_H
    #define ENT_MAIN_MENU_BUTTON_H

    #include <stdbool.h>

    #include <SFML/Graphics/Rect.h>
    #include <SFML/Graphics/Types.h>

    #include "demeter_V2/types.h"

typedef int (button_on_click_func_t)(game_t *game, bool is_hovered);

typedef struct {
    sfFloatRect transform;
    sfSprite *sprite;
    button_on_click_func_t *on_click;
    bool is_hovered;
} ent_main_menu_button_t;

int ent_main_menu_button_set(game_t *game, size_t id);
int ent_main_menu_button_unset(game_t *game, size_t id);
int ent_main_menu_button_update(game_t *game, size_t id);
int ent_main_menu_button_draw(game_t *game, size_t id);

int ent_main_menu_button_start_set(game_t *game);
int ent_main_menu_button_options_set(game_t *game);
int ent_main_menu_button_exit_set(game_t *game);

int button_exit_on_click(game_t *game, bool is_hovered);
int button_options_on_click(game_t *game, bool is_hovered);
int button_start_on_click(game_t *game, bool is_hovered);

#endif  // ENT_MAIN_MENU_BUTTON_H
