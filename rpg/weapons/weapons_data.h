#include <stdbool.h>
#include <string.h>

#ifndef WEAPON_DATA_H
    #define WEAPON_DATA_H

typedef struct weapon_s {
    bool is_picked;
    int damage;
    float cons_stamina;
    int hit_speed;
    int req_strength;
    int req_resistance;
    size_t id;
} weapon_t;

typedef struct shield_s {
    bool is_picked;
    float cons_stamina;
    int req_strength;
    int req_resistance;
    size_t id;
} shield_t;

#endif
