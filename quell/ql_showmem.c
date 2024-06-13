#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include "ql_base.h"

static
void ql_show_memblock(char const *mem, int n)
{
    int group = BLOCK_SIZE;

    for (int k = n; k > 0; k--) {
        printf("%.2hhx%s", (unsigned char)*mem++, &" "[!(group & 1)]);
        group--;
    }
    for (int leftover = BLOCK_SIZE - n; leftover > 0; leftover--) {
        printf("%s", &"   "[!(group & 1)]);
        group--;
    }
    for (int k = n; k--; mem++)
        putchar(isprint(*mem) ? *mem : '.');
}

int ql_showmem(char const *str, size_t size)
{
    for (char const *p = str; p <= (str + size); p += BLOCK_SIZE) {
        printf("%08lx: ", p - str);
        ql_show_memblock(p, MIN(BLOCK_SIZE, (str + size) - p));
        printf("\n");
    }
    return 0;
}
