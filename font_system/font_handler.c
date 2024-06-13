#include "font_handler.h"

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include <SFML/Graphics/Rect.h>
#include <SFML/Graphics/RenderWindow.h>
#include <SFML/Graphics/Sprite.h>
#include <SFML/Graphics/Texture.h>
#include <SFML/Graphics/Types.h>

static
sfVector2f obtain_position(pos_t *start_pos, sfVector2f *new_pos)
{
    new_pos->x = start_pos->new_pos.left;
    new_pos->y = start_pos->new_pos.top;
    return *new_pos;
}

static
bool position_check(
    size_t c, sfVector2f *pos,
    pos_t *start_pos, char const *text)
{
    if (text[c] == '\n' || ((float)strlen(&text[c]) * WIDTH_CHAR
        > (start_pos->initial_pos.left
            + start_pos->initial_pos.width) - pos->x)
        || (pos->x - HEIGHT_PLACE
            > start_pos->initial_pos.left + start_pos->initial_pos.width)) {
        pos->x = start_pos->initial_pos.left;
        pos->y += HEIGHT_PLACE;
        return (text[c] != '\n');
    }
    return true;
}

static
void write_char(game_t *game, char c, sfColor color, sfVector2f pos)
{
    sfSprite_setTextureRect(game->font_sprite,
        (sfIntRect){HEIGHT_CHAR * c, 0, HEIGHT_CHAR, HEIGHT_CHAR});
    sfSprite_setColor(game->font_sprite, color);
    sfSprite_setScale(game->font_sprite, (sfVector2f){0.25, 0.25});
    sfSprite_setPosition(game->font_sprite, pos);
    sfRenderWindow_drawSprite(game->window.window, game->font_sprite, NULL);
}

static
bool write_str(
    game_t *game, pos_t *start_pos,
    sfColor color, char const *text)
{
    sfVector2f pos = { 0 };

    pos = obtain_position(start_pos, &pos);
    for (size_t i = 0; text[i] != '\0' && text[i] != 1; i++) {
        if (position_check(i, &pos, start_pos, text) == 0)
            i++;
        if (text[i] == '\0')
            return true;
        if (pos.y > pos.y + start_pos->new_pos.height) {
            start_pos->new_pos.top = start_pos->new_pos.height;
            return false;
        }
        write_char(game, text[i], color, pos);
        pos.x += WIDTH_CHAR;
    }
    start_pos->new_pos.left = pos.x;
    start_pos->new_pos.top = pos.y;
    return true;
}

int font_handle(
    game_t *game, char const *text,
    sfFloatRect start_pos, sfColor color)
{
    char **words = parse_word(text, " ");
    sfFloatRect val = start_pos;
    pos_t pos = { start_pos, val };

    if (words == NULL)
        return 1;
    if (game == NULL)
        return free_array(words);
    for (size_t j = 1; words[j] != NULL; j++) {
        write_str(game, &pos, color, words[j]);
        write_str(game, &pos, color, " ");
        if (pos.new_pos.left > pos.new_pos.left + pos.new_pos.width)
            pos.new_pos.left = pos.initial_pos.left;
    }
    free_array(words);
    return 0;
}
