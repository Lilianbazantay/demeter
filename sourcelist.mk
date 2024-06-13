VPATH += demeter_V2
SRC += de_arr.c
SRC += de_entity.c
SRC += de_event.c
SRC += de_game.c
SRC += de_mouse.c
SRC += de_scene.c
SRC += de_sound.c
SRC += de_texture.c
SRC += de_window.c

VPATH += font_system
SRC += font_handler.c
SRC += parse_word.c

VPATH += rpg
SRC += main.c
SRC += background_manager.c
SRC += game_prepare.c

VPATH += rpg/game_logic
SRC += ent_game_logic.c
SRC += ent_game_logic_load.c
SRC += ent_game_logic_unload.c

VPATH += rpg/main_menu/controler
SRC += controler.c

VPATH += rpg/main_menu/background
SRC += background.c

VPATH += rpg/main_menu/button
SRC += button.c
SRC += button_click.c
SRC += button_set.c

VPATH += rpg/player
SRC += player_manager.c
SRC += player_update_position.c
SRC += check_player_hitbox.c
SRC += player_animated_sprite.c
SRC += player_attack.c
SRC += player_user_interface.c

VPATH += rpg/enemies
SRC += enemies_manager.c
SRC += check_entity_active_collision.c
SRC += enemy_movement.c
SRC += check_enemy_attack.c
SRC += check_player_interactions.c

VPATH += rpg/weapons
SRC += weapon_manager.c
SRC += shield_manager.c

VPATH += rpg/collectibles
SRC += collectibles_manager.c

VPATH += rpg/npcs/lvl_up_npc
SRC += lvl_up_statue.c
SRC += interactions_statue.c
SRC += dialogue.c
SRC += player_lvl_up.c

VPATH += rpg/npcs/help_sign
SRC += sign.c

VPATH += rpg/collison_manager
SRC += collison_manager.c
