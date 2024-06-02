#ifndef DE_GAME_H
    #define DE_GAME_H

    #include <SFML/Config.h>
    #include <stdbool.h>

    #include <SFML/Audio/SoundBuffer.h>
    #include <SFML/Config.h>
    #include <SFML/Graphics/Texture.h>
    #include <SFML/System/Clock.h>

    #include "de_arr.h"
    #include "entity.h"
    #include "event.h"
    #include "resources.h"
    #include "window.h"

typedef struct game_s {
    entity_t entity_arr[DE_ENTITY_MAX];
    event_t event;
    sfTexture *tex_arr[TEX_ARR_SIZE];
    sfSoundBuffer *snd_arr[SND_ARR_SIZE];
    de_arr_t *scene_arr;
    sfClock *main_clock;
    sfClock *game_clock; // can get paused
    sfSprite *font_sprite;
    window_t window;
    sfInt64 prev_main_clock;
    sfInt64 prev_game_clock;
    double main_delta_time;
    double game_delta_time;
    bool is_running;
} game_t;

int game_set(game_t *game, const window_t *win_data);
void game_unset(game_t *game);
int game_update(game_t *game);
void game_draw(game_t *game);

#endif  // DE_GAME_H
