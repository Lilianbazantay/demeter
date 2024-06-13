#include <fcntl.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#include <SFML/Graphics/Rect.h>

#include "collision_manager.h"
#include "demeter_V2/de_arr.h"
#include "rpg/game_core.h"

static
const char NEEDLE[] = {
    " <layer id=\"4\" name=\"Collision\" width=\"150\" height=\"150\">\n"
    "  <data encoding=\"csv\">\n"
};

static
void set_bit(uint8_t map[COL_MAP_SIZE], size_t x, size_t y, bool b)
{
    size_t pos = y * 150 + x;

    map[pos / 8] &= (uint8_t)~(1 << (7 - pos % 8));
    map[pos / 8] |= b << (7 - pos % 8);
}

static
bool get_bit(uint8_t const map[COL_MAP_SIZE], size_t x, size_t y)
{
    size_t pos = y * 150 + x;

    return map[pos / 8] & (1 << (7 - pos % 8));
}

static
void get_data(uint8_t map[COL_MAP_SIZE], char *buf)
{
    char *ptr = strstr(buf, NEEDLE) + sizeof NEEDLE - 1;

    if (ptr == (void *)(sizeof NEEDLE - 1)) {
        SEND_ERR("cannot parse file");
        return;
    }
    for (size_t y = 0; y < 150; y++)
        for (size_t x = 0; x < 150; x++)
            set_bit(map, x, y, ptr[y * (150 * 2 + 1) + x * 2] != '0');
}

static
int load(uint8_t map[COL_MAP_SIZE], size_t size)
{
    char buf[size];
    int fd = open(PATH, O_RDONLY);

    if (fd == -1)
        return SEND_ERR("cannot open \""PATH"\""), 84;
    if (read(fd, buf, size) == -1)
        return SEND_ERR("cannot read \""PATH"\""), close(fd), 84;
    close(fd);
    get_data(map, buf);
    return 0;
}

int ent_collision_manager_set(game_t *game, size_t id)
{
    struct stat buf;
    ent_collision_manager_t *data = malloc(sizeof(ent_collision_manager_t));

    if (data == NULL)
        return SEND_ERR("malloc failed"), 84;
    game->entity_arr[id].data = data;
    data->ent = de_arr_create(sizeof(sfIntRect), 10, 2);
    if (data->ent == NULL)
        return 84;
    if (stat(PATH, &buf))
        return SEND_ERR("cannot stat \""PATH"\""), 84;
    if (load(data->map, (size_t)buf.st_size))
        return 84;
    is_colliding(NULL, data);
    return 0;
}

int ent_collision_manager_unset(game_t *game, size_t id)
{
    ent_collision_manager_t *data = game->entity_arr[id].data;

    de_arr_destroy(data->ent, NULL);
    free(data);
    return 0;
}

static __attribute__((pure))
bool dlc(ent_collision_manager_t *data, sfIntRect *pos, size_t y)
{
    for (size_t x = (size_t)pos->left;
        x < (size_t)(pos->left + pos->width); x++)
        if (get_bit(data->map, x, y))
            return true;
    return false;
}

bool is_colliding(sfIntRect *rect, ent_collision_manager_t *dont_use)
{
    static ent_collision_manager_t *data = NULL;
    sfIntRect pos;

    if (dont_use != NULL) {
        data = dont_use;
        return false;
    }
    pos.left = rect->left / 16;
    pos.top = rect->top / 16;
    pos.width = rect->width / 16 + (rect->left % 16 != 0);
    pos.height = rect->height / 16 + (rect->top % 16 != 0);
    for (size_t y = (size_t)pos.top; y < (size_t)(pos.top + pos.height); y++)
        if (dlc(data, &pos, y))
            return true;
    return false;
}
