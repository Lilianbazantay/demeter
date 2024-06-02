#ifndef DEMETER_V2_H
    #define DEMETER_V2_H

    #include <unistd.h>

    #define DE_COL_YEL "\x1b[33m"
    #define DE_COL_RED "\x1b[31m"
    #define DE_COL_RES "\x1b[0m"
    #define DE_SIZE_ARR(a) sizeof a / sizeof *a
    #define DE_SSTR(s) s, sizeof s - 1
    #define DE_MSG(s) write(STDERR_FILENO, DE_SSTR(s))
    #define DE_ERR(s) DE_MSG(DE_COL_RED"demeter: error: "DE_COL_RES s"\n")
    #define DE_WARN(s) DE_MSG(DE_COL_YEL"demeter: warning: "DE_COL_RES s"\n")
    #define DE_ENTITY_MAX 1024

typedef struct window_s window_t;
typedef struct game_s game_t;
typedef struct scene_s scene_t;
typedef struct entity_s entity_t;
typedef struct event_s event_t;
typedef struct mouse_s mouse_t;

typedef int (de_func_entity_t)(game_t *game, size_t id);

#endif  // DEMETER_V2_H
