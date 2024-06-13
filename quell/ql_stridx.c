#include "ql_base.h"

int ql_stridx(const char *str, char c)
{
    for (const char *p = str; *p != '\0'; p++)
        if (*p == c)
            return p - str;
    return -1;
}
