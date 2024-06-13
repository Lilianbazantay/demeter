#ifndef WEAPON_DATA_H
    #define WEAPON_DATA_H

    #include <stdbool.h>

typedef struct requirement_s {
    int strength;
    int dexterity;
    int intelligence;
    int faith;
} requirement_t;

typedef struct weapon_s {
    bool can_be_equipped;
    int damage;
    float wheight;
    requirement_t requirements;
} weapon_t;

#endif
