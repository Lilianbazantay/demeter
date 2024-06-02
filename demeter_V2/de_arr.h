#ifndef DE_ARR_H
    #define DE_ARR_H

    #include <stddef.h>
    #include <stdint.h>

typedef uint8_t byte_t;
typedef void (de_func_destroy_t)(void *);
typedef struct de_arr_s {
    byte_t *arr;
    size_t arr_size;
    size_t incr_size;
    size_t data_size;
    size_t data_count;
} de_arr_t;

// @param incr_size: if 0 -> arr_size x 2
de_arr_t *de_arr_create(size_t data_size, size_t arr_size, size_t incr_size);

// @param destroy: can be NULL
void de_arr_destroy(de_arr_t *de_arr, de_func_destroy_t *destroy);
int de_arr_insert(de_arr_t *de_arr, void *data, size_t i);

// @param destroy: can be NULL
void de_arr_remove(de_arr_t *de_arr, de_func_destroy_t *destroy, size_t i);
void *de_arr_get(de_arr_t *de_arr, size_t i);

#endif  // DE_ARR_H
