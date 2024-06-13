#ifndef RPG_FONT_SYSTEM_H
    #define RPG_FONT_SYSTEM_H

    #include "demeter_V2/game.h"

    #include <SFML/Graphics.h>
    #include <SFML/Graphics/Rect.h>
    #include <SFML/Graphics/RenderWindow.h>
    #include <SFML/Graphics/Types.h>
    #define HEIGHT_CHAR 16
    #define WIDTH_CHAR 3
    #define HEIGHT_PLACE 4

typedef struct pos_s {
    sfFloatRect initial_pos;
    sfFloatRect new_pos;
} pos_t;

int font_handle(
    game_t *game, char const *text,
    sfFloatRect start_pos, sfColor color);

char **parse_word(char const *str, char const *separator);

int free_array(char **array);
#endif
