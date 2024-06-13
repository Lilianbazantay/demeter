#ifndef ENT_GAME_LOGIC_H
    #define ENT_GAME_LOGIC_H

    #include "demeter_V2/types.h"

typedef enum {
    GAME_STATUS_NONE,
    GAME_STATUS_MAIN_MENU,
    GAME_STATUS_PLAY,
    GAME_STATUS_PAUSE
} game_status_t;


typedef struct {
    game_status_t current_state;
    game_status_t new_state;
    size_t scene_id;
} ent_game_logic_t;

int ent_game_logic_set(game_t *game, size_t id);
int ent_game_logic_unset(game_t *game, size_t id);
int ent_game_logic_update(game_t *game, size_t id);

int load_main_menu(game_t *game, ent_game_logic_t *data);
void unload_main_menu(game_t *game, scene_t *scene);

int load_play(game_t *game, ent_game_logic_t *data);
void unload_play(game_t *game, scene_t *scene);

#endif  // ENT_GAME_LOGIC_H
