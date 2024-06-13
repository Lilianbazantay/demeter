#ifndef ENT_MAIN_MENU_CONTROLER_H
    #define ENT_MAIN_MENU_CONTROLER_H

    #include "demeter_V2/types.h"

typedef enum {
    MMS_MENU,
    MMS_SETTINGS,
} main_menu_status_t;

typedef struct {
    main_menu_status_t status;
    entity_t *buton_start;
    entity_t *buton_settings;
    entity_t *buton_exit;
} ent_main_menu_controler_t;

int ent_main_menu_controler_set(game_t *game, size_t id);
int ent_main_menu_controler_unset(game_t *game, size_t id);
int ent_main_menu_controler_update(game_t *game, size_t id);

#endif  // ENT_MAIN_MENU_CONTROLER_H
