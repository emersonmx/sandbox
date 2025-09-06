#include "array.h"

#include <stdlib.h>
#include <string.h>

void array_init(Array *array, size_t item_size, size_t capacity)
{
    array->data = malloc(capacity * item_size);
    array->item_size = item_size;
    array->size = 0;
    array->capacity = capacity;
}

void *array_get(Array *array, size_t index)
{
    if (index >= array->size)
        return NULL;

    return (char *) array->data + index * array->item_size;
}

static void update_capacity(Array *array, size_t new_capacity)
{
    if (new_capacity <= array->capacity)
        return;

    array->data = realloc(array->data, new_capacity * array->item_size);
    array->capacity = new_capacity;
}

void array_insert(Array *array, size_t index, void *item)
{
    if (index > array->size)
        return;

    if (array->size >= array->capacity)
        update_capacity(array, array->capacity * 2);

    void *target = (char *) array->data + index * array->item_size;
    memmove((char *) target + array->item_size, target,
            (array->size - index) * array->item_size);
    memcpy(target, item, array->item_size);
    array->size++;
}

void array_remove(Array *array, size_t index)
{
    if (index >= array->size)
        return;

    void *target = (char *) array->data + index * array->item_size;
    memmove(target, (char *) target + array->item_size,
            (array->size - index - 1) * array->item_size);
    array->size--;
}

void array_push(Array *array, void *item)
{
    array_insert(array, array->size, item);
}

void array_pop(Array *array)
{
    if (array->size == 0)
        return;

    array->size--;
}

void array_free(Array *array)
{
    free(array->data);
    *array = (Array) { 0 };
}
