#include "stack.h"

#include <stdlib.h>
#include <string.h>

void stack_init(Stack *stack, size_t item_size, size_t capacity)
{
    stack->data = malloc(capacity * item_size);
    stack->item_size = item_size;
    stack->size = 0;
    stack->capacity = capacity;
}

void *stack_top(Stack *stack)
{
    if (stack->size == 0)
        return NULL;

    return (char *)stack->data + (stack->size - 1) * stack->item_size;
}

void stack_push(Stack *stack, void *item)
{
    if (stack->size >= stack->capacity) {
        stack->data =
            realloc(stack->data, stack->capacity * 2 * stack->item_size);
        stack->capacity *= 2;
    }

    memcpy((char *)stack->data + stack->size * stack->item_size, item,
           stack->item_size);
    stack->size++;
}

void stack_pop(Stack *stack)
{
    if (stack->size == 0)
        return;

    stack->size--;
}

void stack_free(Stack *stack)
{
    free(stack->data);
    stack->data = NULL;
    stack->size = 0;
    stack->capacity = 0;
    stack->item_size = 0;
}
