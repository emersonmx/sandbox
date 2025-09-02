#include "deque.h"

#include <stdlib.h>
#include <string.h>

void deque_init(Deque *deque, size_t item_size, size_t capacity)
{
    deque->data = malloc(capacity * item_size);
    deque->item_size = item_size;
    deque->size = 0;
    deque->capacity = capacity;
    deque->front = 0;
    deque->back = 0;
}

void *deque_get(Deque *deque, size_t index)
{
    if (index >= deque->size)
        return NULL;

    size_t real_index = (deque->front + index) % deque->capacity;
    return (char *) deque->data + real_index * deque->item_size;
}

void deque_grow(Deque *deque, size_t new_capacity)
{
    if (new_capacity <= deque->capacity)
        return;

    void *new_data = malloc(new_capacity * deque->item_size);
    for (size_t i = 0; i < deque->size; i++) {
        size_t real_index = (deque->front + i) % deque->capacity;
        memcpy((char *) new_data + i * deque->item_size,
               (char *) deque->data + real_index * deque->item_size,
               deque->item_size);
    }

    free(deque->data);
    deque->data = new_data;
    deque->capacity = new_capacity;
    deque->front = 0;
    deque->back = deque->size % new_capacity;
}

void deque_push_front(Deque *deque, void *item)
{
    if (deque->size >= deque->capacity)
        deque_grow(deque, deque->capacity * 2);

    deque->front = (deque->front == 0) ? deque->capacity - 1 : deque->front - 1;
    memcpy((char *) deque->data + deque->front * deque->item_size, item,
           deque->item_size);
    deque->size++;
}

void deque_push_back(Deque *deque, void *item)
{
    if (deque->size >= deque->capacity)
        deque_grow(deque, deque->capacity * 2);

    memcpy((char *) deque->data + deque->back * deque->item_size, item,
           deque->item_size);
    deque->back = (deque->back + 1) % deque->capacity;
    deque->size++;
}

void deque_pop_front(Deque *deque)
{
    if (deque->size == 0)
        return;

    deque->front = (deque->front + 1) % deque->capacity;
    deque->size--;
}

void deque_pop_back(Deque *deque)
{
    if (deque->size == 0)
        return;

    deque->back = (deque->back == 0) ? deque->capacity - 1 : deque->back - 1;
    deque->size--;
}

void deque_free(Deque *deque)
{
    free(deque->data);
    *deque = (Deque) { 0 };
}
