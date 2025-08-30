#ifndef STACK_H
#define STACK_H

#include <stddef.h>

typedef struct {
    void *data;
    size_t size;
    size_t item_size;
    size_t capacity;
} Stack;

void stack_init(Stack *stack, size_t item_size, size_t capacity);
void *stack_top(Stack *stack);
void stack_push(Stack *stack, void *item);
void stack_pop(Stack *stack);
void stack_free(Stack *stack);

#endif // STACK_H
