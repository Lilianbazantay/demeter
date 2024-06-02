#ifndef DE_RESOURCES_H
    #define DE_RESOURCES_H

    #include <SFML/Audio/SoundBuffer.h>
    #include <SFML/Graphics/Texture.h>

    #include "types.h"

typedef enum texture_name_s {
    TEX_EMPTY,
    TEX_BACKGROUND,
    TEX_ENEMY_1,
    TEX_EQUIPMENTS,
    TEX_MAIN_MENU_BACKGROUND,
    TEX_MAIN_MENU_EXIT,
    TEX_MAIN_MENU_OPTIONS,
    TEX_MAIN_MENU_START,
    TEX_NPC_BOX,
    TEX_NPC_LVL,
    TEX_PLAYER,
    TEX_RPG_FONT,
    TEX_SIGN,
    TEX_UI_BARS,
    TEX_USER_INTERFACE,
    TEX_ARR_SIZE,
} texture_name_t;

typedef enum sound_name_s {
    SND_EMPTY,
    SND_ARR_SIZE
} sound_name_t;

int texture_arr_create(game_t *game);
void texture_arr_destroy(game_t *game);

int sound_arr_create(game_t *game);
void sound_arr_destroy(game_t *game);

#endif  // DE_RESOURCES_H
