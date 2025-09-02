#include <string.h>
#include <unity.h>

#include "stack.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_stack_init_and_free()
{
    Stack stack;
    stack_init(&stack, sizeof(int), 4);
    TEST_ASSERT_NOT_NULL(stack.data);
    TEST_ASSERT_EQUAL_size_t(0, stack.size);
    TEST_ASSERT_EQUAL_size_t(4, stack.capacity);
    TEST_ASSERT_EQUAL_size_t(sizeof(int), stack.item_size);

    stack_free(&stack);
    TEST_ASSERT_NULL(stack.data);
    TEST_ASSERT_EQUAL_size_t(0, stack.size);
    TEST_ASSERT_EQUAL_size_t(0, stack.capacity);
    TEST_ASSERT_EQUAL_size_t(0, stack.item_size);
}

void test_stack_push_and_top()
{
    Stack stack;
    stack_init(&stack, sizeof(int), 2);

    int a = 10, b = 20;
    stack_push(&stack, &a);
    TEST_ASSERT_EQUAL_INT(a, *(int *) stack_top(&stack));

    stack_push(&stack, &b);
    TEST_ASSERT_EQUAL_INT(b, *(int *) stack_top(&stack));

    TEST_ASSERT_EQUAL_size_t(2, stack.size);

    stack_free(&stack);
}

void test_stack_pop()
{
    Stack stack;
    stack_init(&stack, sizeof(int), 2);

    int a = 1, b = 2;
    stack_push(&stack, &a);
    stack_push(&stack, &b);

    stack_pop(&stack);
    TEST_ASSERT_EQUAL_size_t(1, stack.size);
    TEST_ASSERT_EQUAL_INT(a, *(int *) stack_top(&stack));

    stack_pop(&stack);
    TEST_ASSERT_EQUAL_size_t(0, stack.size);
    TEST_ASSERT_NULL(stack_top(&stack));

    stack_pop(&stack);
    TEST_ASSERT_EQUAL_size_t(0, stack.size);
    TEST_ASSERT_NULL(stack_top(&stack));

    stack_free(&stack);
}

int main()
{
    UNITY_BEGIN();

    RUN_TEST(test_stack_init_and_free);
    RUN_TEST(test_stack_push_and_top);
    RUN_TEST(test_stack_pop);

    return UNITY_END();
}
