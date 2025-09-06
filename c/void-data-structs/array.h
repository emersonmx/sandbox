#ifndef ARRAY_H
#define ARRAY_H

#include <stddef.h>

typedef struct {
    void *data;
    size_t size;
    size_t item_size;
    size_t capacity;
} Array;

void array_init(Array *array, size_t item_size, size_t capacity);
void *array_get(Array *array, size_t index);
void array_insert(Array *array, size_t index, void *item);
void array_remove(Array *array, size_t index);
void array_push(Array *array, void *item);
void array_pop(Array *array);
void array_free(Array *array);

#endif // ARRAY_H
