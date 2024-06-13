#include <stddef.h>

#include "ql_base.h"

static
byte_t eat_chunk(const byte_t *chunk, size_t csize)
{
    byte_t reduced = 0;
    size_t i = 0;

    for (; i < csize; i++)
        reduced |= chunk[i];
    return reduced;
}

size_t ql_memlen(const void *chunk, size_t csize)
{
    size_t count = 0;

    for (const byte_t *p = chunk; eat_chunk(p, csize) != '\0'; p += csize)
        count++;
    return count;
}
