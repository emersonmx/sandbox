#ifndef DEQUE_H
#define DEQUE_H

#include <stddef.h>

typedef struct {
    void *data;
    size_t size;
    size_t item_size;
    size_t capacity;
    size_t front;
    size_t back;
} Deque;

void deque_init(Deque *deque, size_t item_size, size_t capacity);
void *deque_get(Deque *deque, size_t index);
void deque_push_front(Deque *deque, void *item);
void deque_push_back(Deque *deque, void *item);
void deque_pop_front(Deque *deque);
void deque_pop_back(Deque *deque);
void deque_free(Deque *deque);

#endif // DEQUE_H
