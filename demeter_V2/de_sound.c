#include <stddef.h>

#include <SFML/Audio/SoundBuffer.h>

#include "game.h"
#include "resources.h"
#include "types.h"

// Dont forget to add new sound to enum sound_name_t
const char *SOUND_FILES[] = {
    "./resources/empty.ogg",
};

int sound_arr_create(game_t *game)
{
    for (size_t i = 0; i < SND_ARR_SIZE; i++) {
        game->snd_arr[i] = sfSoundBuffer_createFromFile(SOUND_FILES[i]);
        if (game->tex_arr[i] == NULL) {
            sound_arr_destroy(game);
            return DE_ERR("sfSoundBuffer_create failed"), 84;
        }
    }
    return 0;
}

void sound_arr_destroy(game_t *game)
{
    for (size_t i = 0; i < SND_ARR_SIZE; i++)
        if (game->tex_arr[i] != NULL)
            sfSoundBuffer_destroy(game->snd_arr[i]);
}
