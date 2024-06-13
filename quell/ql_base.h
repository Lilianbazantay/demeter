#ifndef QL_BASE_H
    #define QL_BASE_H

    #include <limits.h>
    #include <stddef.h>

    #define ABS(x) (((x) > 0) ? (x) : (-x))

    #define MIN(x, y) (((x) < (y)) ? (x) : (y))
    #define MAX(x, y) (((x) > (y)) ? (x) : (y))

    #define ATTR(key) __attribute__((key))

    #define UNUSED ATTR(unused)

    #define CFMT(n) "\033[" #n "m"

    #define RESET CFMT(0)
    #define BOLD CFMT(1)

    #define RED CFMT(31)
    #define GREEN CFMT(32)
    #define YELLOW CFMT(33)
    #define BLUE CFMT(34)
    #define PURPLE CFMT(35)
    #define CYAN CFMT(36)

    #define GET_STATUS(st) ((st) ? EXIT_KO : EXIT_OK)

    #define LENGTH_OF(arr) (sizeof (arr) / sizeof *(arr))

    #define SSTR_UNPACK(s) s, SSTRLEN(s)
    #define SSTRLEN(s) ((sizeof(s) - 1) / sizeof(char))

    #define C_UP(c) ((c) | ' ')
    #define BOUNDS(c, lo, hi) (((c) >= (lo)) && ((c) <= (hi)))

    #define BLOCK_SIZE (CHAR_BIT << 1)

enum {
    EXIT_KO = 84,
    EXIT_OK = 0
};

typedef unsigned char byte_t;
typedef unsigned int uint_t;
typedef unsigned long long ull_t;

int ql_showmem(char const *str, size_t size)
__attribute__((nonnull));

int ql_showstr(char const *str)
__attribute__((pure, nonnull));

size_t ql_memlen(const void *chunk, size_t csize)
__attribute__((pure, nonnull));

int ql_stridx(const char *str, char c)
__attribute__((pure, nonnull));

char *ql_file_read(char const *filepath)
__attribute__((nonnull));

int ql_file_read_n(char const *filepath, char *buff, size_t size)
__attribute__((nonnull));

#endif
