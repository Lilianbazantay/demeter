#ifndef PLAYER_DATA_H
    #define PLAYER_DATA_H

    #include <stdbool.h>

    #include <SFML/Graphics/Rect.h>
    #include <SFML/Graphics/Sprite.h>
    #include <SFML/Graphics/Types.h>
    #include <SFML/System/Types.h>
    #include <SFML/System/Vector2.h>

    #include "demeter_V2/game.h"

    #include "../weapons/weapons_data.h"

    #define KEY(c) (sfKey ## c)

    #ifdef USE_QWERTY_LAYOUT
        #define KEY_UP KEY(W)
        #define KEY_LEFT KEY(A)
        #define KEY_DOWN KEY(S)
        #define KEY_RIGHT KEY(D)
    #else
        #define KEY_UP KEY(Z)
        #define KEY_LEFT KEY(Q)
        #define KEY_DOWN KEY(S)
        #define KEY_RIGHT KEY(D)
    #endif

    #define PLAYER_SIZE 16
    #define IDLE_KEYFRAME 4

enum {
    ITEM_SIZE = 16,
    ITEM_WEAPON_LAYER = 0,
    ITEM_SHIELD_LAYER = ITEM_WEAPON_LAYER + ITEM_SIZE
};

typedef enum rotate_side_s {
    IDLE = 0,
    DOWN = 1,
    TOP = 2,
    RIGHT = 4,
    LEFT = 8,
} rotate_side_t;

typedef struct player_input_s {
    int KeyInput;
    int value;
    float position_x;
    float position_y;
} player_input_t;

typedef struct hitbox_tab_s {
    rotate_side_t rotation;
    float x;
    float y;
    float whidth;
    float height;
} hitbox_tab_t;

typedef struct attack_s {
    bool is_blocking;
    bool is_attacking;
    sfFloatRect attack_hitbox;
    sfClock *attack_delay;
    sfClock *parry;
} attack_t;

typedef struct inventory_s {
    bool is_changing_equipment;
    sfClock *clock;
    weapon_t *weapon;
    shield_t *shield;
} inventory_t;

typedef struct stats_s {
    float endurance;
    float max_endurance;
    int health;
    int max_health;
    int exp_money;
    int strength;
    int resistance;
    int damage;
} stats_t;

typedef struct player_ui_s {
    sfSprite *sprite;
    sfSprite *weapon_spr;
    sfSprite *shield_spr;
    sfSprite *bars;
    sfVector2f position;
    sfIntRect rect;
} player_ui_t;

typedef struct player_s {
    bool has_move;
    int level;
    double required_money;
    sfClock *clock;
    sfRectangleShape *attack_sprite;
    sfIntRect rect;
    sfVector2f position;
    sfSprite *sprite;
    inventory_t inventory;
    stats_t stats;
    attack_t attack;
    rotate_side_t rotation;
    player_ui_t ui;
} player_t;

int player_lvl_up(game_t *game, player_t *player);

#endif
