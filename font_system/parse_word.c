#include <stdlib.h>
#include <string.h>

#include "font_handler.h"

int free_array(char **array)
{
    free(array[0]);
    free(array);
    return 1;
}

static
size_t count_nb_word(char const *str, char const *sep)
{
    size_t nb_word = 0;

    if (str == NULL || sep == NULL)
        return 0;
    for (size_t i = 0; i < strlen(str); i++)
        if (strchr(sep, str[i]) == NULL && strchr(sep, str[i + 1]) != NULL)
            nb_word++;
    return nb_word;
}

static
char **doing_population(
    char *str, char **word_array,
    char const *sep, size_t nb_word)
{
    int pos = 1;
    int in_word = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        if (strchr(sep, str[i]) != NULL) {
            str[i] = '\0';
            in_word = 0;
            continue;
        }
        if (in_word == 0) {
            in_word = 1;
            word_array[pos] = &(str[i]);
            pos++;
        }
    }
    word_array[nb_word + 1] = NULL;
    word_array[0] = str;
    return word_array;
}

static
char **populate_word_array(
    char *str,
    const char *separator,
    size_t nb_word)
{
    char **word_array = malloc((nb_word + 3) * sizeof(char *));

    if (word_array != NULL)
        return doing_population(str, word_array, separator, nb_word);
    free(str);
    return NULL;
}

char **parse_word(char const *str, char const *separator)
{
    char *dupe;
    size_t nb_word = 0;

    if (str == NULL)
        return NULL;
    dupe = strdup(str);
    if (dupe == NULL)
        return NULL;
    nb_word = count_nb_word(str, separator);
    return populate_word_array(dupe, separator, nb_word);
}
