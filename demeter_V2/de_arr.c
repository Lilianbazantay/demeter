#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "de_arr.h"
#include "types.h"

de_arr_t *de_arr_create(size_t data_size, size_t arr_size, size_t incr_size)
{
    de_arr_t *out;

    if (arr_size == 0)
        return DE_ERR("arr_size must be > 0"), NULL;
    out = malloc(sizeof(de_arr_t));
    if (out == NULL)
        return DE_ERR("malloc failed"), NULL;
    out->arr = malloc(arr_size * data_size);
    if (out->arr == NULL) {
        free(out);
        return DE_ERR("malloc failed"), NULL;
    }
    out->data_size = data_size;
    out->data_count = 0;
    out->arr_size = arr_size;
    out->incr_size = incr_size;
    return out;
}

void de_arr_destroy(de_arr_t *de_arr, de_func_destroy_t *destroy)
{
    if (destroy != NULL)
        for (size_t i = 0; i < de_arr->data_count; i++)
            destroy(de_arr_get(de_arr, i));
    free(de_arr->arr);
    free(de_arr);
}

static
void insert(de_arr_t *de_arr, byte_t *data, size_t i)
{
    i *= de_arr->data_size;
    for (size_t j = de_arr->data_count * de_arr->data_size;
        i < j; j -= de_arr->data_size)
        memcpy(&de_arr->arr[j], &de_arr->arr[j - 1], de_arr->data_size);
    memcpy(&de_arr->arr[i], data, de_arr->data_size);
}

static
int increase_size(de_arr_t *de_arr)
{
    if (de_arr->incr_size == 0)
        de_arr->arr_size *= 2;
    else
        de_arr->arr_size += de_arr->incr_size;
    de_arr->arr = realloc(de_arr->arr, de_arr->arr_size * de_arr->data_size);
    if (de_arr->arr == NULL)
        return DE_ERR("malloc failed"), 84;
    return 0;
}

int de_arr_insert(de_arr_t *de_arr, void *data, size_t i)
{
    if (de_arr->data_count < i)
        return DE_ERR("index is out of scope"), 84;
    if (de_arr->data_count + 1 > de_arr->arr_size)
        if (increase_size(de_arr))
            return 84;
    insert(de_arr, data, i);
    de_arr->data_count++;
    return 0;
}

void de_arr_remove(de_arr_t *de_arr, de_func_destroy_t *destroy, size_t i)
{
    if (de_arr == NULL)
        return;
    if (de_arr->data_count <= i) {
        DE_WARN("index is out of scope");
        return;
    }
    if (destroy != NULL)
        destroy(de_arr_get(de_arr, i));
    for (size_t j = i; j < de_arr->data_count; j++)
        memcpy(&de_arr->arr[j * de_arr->data_size],
            &de_arr->arr[(j + 1) * de_arr->data_size], de_arr->data_size);
    de_arr->data_count--;
}

__attribute__((pure))
void *de_arr_get(de_arr_t *de_arr, size_t i)
{
    return &de_arr->arr[de_arr->data_size * i];
}
