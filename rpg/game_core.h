#ifndef RPG_GAME_CORE_H
    #define RPG_GAME_CORE_H

    #include <stdbool.h>

    #include <SFML/Graphics/Types.h>

    #include "quell/ql_base.h"
    #include "demeter_V2/types.h"

    #define WRITE(fd, s) write(fd, SSTR_UNPACK(s))
    #define WRITE_OUT(s) WRITE(STDOUT_FILENO, s)
    #define WRITE_ERR(s) WRITE(STDERR_FILENO, s)

    #define ERR_STR(s) RED "rpg: error: " RESET s "\n"
    #define WARN_STR(s) YELLOW "rpg: warning: " RESET s "\n"
    #define COMM_STR(s) BLUE "rpg: --- " s " ---" RESET "\n"

    #define PRINT_ERR(s, ...) fprintf(STDERR_FILENO, s, __VA_ARGS__)

    #define SEND_ERR(s) WRITE_ERR(ERR_STR(s))
    #define SEND_WARN(s) WRITE_ERR(WARN_STR(s))
    #define SEND_COMM(s) WRITE_ERR(COMM_STR(s))
    #define SEND_P_ERR(s, ...) PRINT_ERR(ERR_STR(s), __VA_ARGS__)
    #define SEND_P_WARN(s, ...) PRINT_ERR(WARN_STR(s), __VA_ARGS__)
    #define SEND_P_COMM(s, ...) PRINT_ERR(COMM_STR(s), __VA_ARGS__)
//--- GAME_PREPARE.C ----------------------------------------------------------

int game_run(void);

int entity_background(game_t *game);

int entity_player(game_t *game);
bool update_player_position(game_t *game, size_t id);
void player_animated_sprite(game_t *game, size_t id);
bool check_player_hitbox(game_t *game, size_t id);
void check_player_attack(game_t *game, size_t id);
void check_player_interactions(game_t *game, size_t id);
void update_player_ui(game_t *game, size_t id);
void player_draw_ui(game_t *game, size_t id);

int entity_enemy_arr(game_t *game);

int entity_weapons(game_t *game);
int entity_shields(game_t *game);
int entity_collectibles(game_t *game);

#endif
