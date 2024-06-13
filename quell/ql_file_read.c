#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

#include "ql_base.h"

int ql_file_read_n(char const *filepath, char *buff, size_t size)
{
    int fd = open(filepath, O_RDONLY);
    int rd;

    if (fd < 0)
        return fd;
    rd = read(fd, buff, size);
    close(fd);
    return rd;
}

char *ql_file_read(char const *filepath)
{
    struct stat fi;
    char *content;

    if (stat(filepath, &fi) < 0)
        return NULL;
    content = malloc((fi.st_size + 1) * sizeof(char));
    if (content == NULL)
        return NULL;
    content[fi.st_size] = '\0';
    if (ql_file_read_n(filepath, content, fi.st_size) == fi.st_size)
        return content;
    free(content);
    return NULL;
}
