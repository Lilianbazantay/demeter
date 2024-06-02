#include <stddef.h>

#include <SFML/Graphics/Texture.h>

#include "game.h"
#include "resources.h"
#include "types.h"

// Dont forget to add new sound to enum sound_name_t
const char *TEXTURE_FILES[] = {
    "./resources/empty.png",
    "./resources/background.png",
    "./resources/enemy_1.png",
    "./resources/equipments.png",
    "./resources/main_menu_background.png",
    "./resources/main_menu_exit.png",
    "./resources/main_menu_options.png",
    "./resources/main_menu_start.png",
    "./resources/npc_box.png",
    "./resources/npc_lvl.png",
    "./resources/player.png",
    "./resources/rpg-font.png",
    "./resources/sign.png",
    "./resources/ui_bars.png",
    "./resources/user_interface.png",
};

int texture_arr_create(game_t *game)
{
    for (size_t i = 0; i < TEX_ARR_SIZE; i++) {
        game->tex_arr[i] = sfTexture_createFromFile(TEXTURE_FILES[i], NULL);
        if (game->tex_arr[i] == NULL) {
            texture_arr_destroy(game);
            return DE_ERR("sfTexture_create failed"), 84;
        }
    }
    return 0;
}

void texture_arr_destroy(game_t *game)
{
    for (size_t i = 0; i < TEX_ARR_SIZE; i++)
        if (game->tex_arr[i] != NULL)
            sfTexture_destroy(game->tex_arr[i]);
}
