#include <string.h>

#include <SFML/Graphics/Rect.h>
#include <SFML/Graphics/RenderWindow.h>
#include <SFML/Graphics/Types.h>
#include <SFML/Graphics/View.h>
#include <SFML/Window/VideoMode.h>
#include <SFML/Window/Window.h>

#include "game.h"
#include "types.h"
#include "window.h"


static
void center_window(sfRenderWindow *win, sfVideoMode *vwin)
{
    sfVideoMode desktop = sfVideoMode_getDesktopMode();

    sfRenderWindow_setPosition(win, (sfVector2i){
        (int)(desktop.width - vwin->width) / 2,
        (int)(desktop.height - vwin->height) / 2
    });
}

static
int set_csfml_data(window_t *win_data)
{
    sfView *view;
    sfVideoMode mode = {
        (unsigned int)win_data->ext_width,
        (unsigned int)win_data->ext_height,
        32
    };

    win_data->window = sfRenderWindow_create(
        mode, win_data->name, sfTitlebar | sfClose, NULL);
    if (win_data->window == NULL)
        return 84;
    view = sfView_createFromRect(win_data->internal);
    if (view == NULL)
        return sfRenderWindow_destroy(win_data->window), 84;
    sfRenderWindow_setView(win_data->window, view);
    sfView_destroy(view);
    center_window(win_data->window, &mode);
    return 0;
}

int window_create(game_t *game, const window_t *win_data)
{
    if (win_data->window != NULL) {
        DE_ERR("error : window musn't be set beforehand.");
        return 84;
    }
    memcpy(&game->window, win_data, sizeof(window_t));
    if (game->window.ext_width == 0)
        game->window.ext_width = DE_DEFAULT_WIN_EXT_W;
    if (game->window.ext_height == 0)
        game->window.ext_width = DE_DEFAULT_WIN_EXT_H;
    if ((int)game->window.internal.width == 0)
        game->window.internal.width = DE_DEFAULT_WIN_INT_W;
    if ((int)game->window.internal.height == 0)
        game->window.internal.height = DE_DEFAULT_WIN_INT_H;
    if (game->window.framerate == 0)
        game->window.framerate = DE_DEFAULT_WIN_FRAMERATE;
    if (set_csfml_data(&game->window))
        return 84;
    return 0;
}

void window_destroy(game_t *game)
{
    sfRenderWindow_destroy(game->window.window);
}

int window_move(game_t *game, int int_x, int int_y)
{
    sfFloatRect *internal = &game->window.internal;
    sfView *view;

    if ((int)internal->left == int_x && (int)internal->top == int_y)
        return 0;
    internal->left = (float)int_x;
    internal->top = (float)int_y;
    view = sfView_createFromRect(*internal);
    if (view == NULL)
        return 84;
    sfRenderWindow_setView(game->window.window, view);
    sfView_destroy(view);
    return 0;
}
