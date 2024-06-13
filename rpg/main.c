#include <stdbool.h>
#include <string.h>

#include "quell/ql_debug.h"

#include "game_core.h"

static
const char MSG_DIPLAY_ERROR[] = {
    "env failure: No Display set, cannot start a graphical context\n"
};

static
const char MSG_USAGE[] = {
    "USAGE\n"
    "\t./my_rpg\n"
    "\n"
    "AUTHORED BY:\n"
    "\tYohann Boniface\n"
    "\tLouis Persin\n"
    "\tLilian Bazantay\n"
    "\tAntoine Quillet\n"
};

static __attribute__((pure))
bool has_flag_help(char **argv)
{
    for (size_t i = 1; argv[i] != NULL; i++)
        if (strncmp(argv[i], SSTR_UNPACK("-h")) == 0
            && strncmp(argv[i], SSTR_UNPACK("--help")) == 0)
            return WRITE_ERR(MSG_USAGE), true;
    return false;
}

static __attribute__((pure))
bool is_env_ok(char **env)
{
    for (size_t i = 0; env[i] != NULL; i++)
        if (strncmp(env[i], SSTR_UNPACK("DISPLAY=")) == 0)
            return true;
    return WRITE_ERR(MSG_DIPLAY_ERROR), false;
}

int main(int argc QL_DEBUG_USED, char **argv, char **env)
{
    QL_DEBUG("Running ["BLUE"%s"RESET"] with"YELLOW" %d "RESET"arguments.",
        argv[0], argc);
    if (has_flag_help(argv))
        return EXIT_OK;
    if (!is_env_ok(env))
        return EXIT_KO;
    QL_DEBUG_MSG("Passed env check");
    if (game_run())
        return EXIT_KO;
    return EXIT_OK;
}
