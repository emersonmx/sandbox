#include <string.h>
#include <unity.h>

#include "deque.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_deque_init_and_free(void)
{
    Deque deque;
    deque_init(&deque, sizeof(int), 4);
    TEST_ASSERT_NOT_NULL(deque.data);
    TEST_ASSERT_EQUAL_size_t(0, deque.size);
    TEST_ASSERT_EQUAL_size_t(4, deque.capacity);
    TEST_ASSERT_EQUAL_size_t(sizeof(int), deque.item_size);
    TEST_ASSERT_EQUAL_size_t(0, deque.front);
    TEST_ASSERT_EQUAL_size_t(0, deque.back);

    deque_free(&deque);
    TEST_ASSERT_NULL(deque.data);
    TEST_ASSERT_EQUAL_size_t(0, deque.size);
    TEST_ASSERT_EQUAL_size_t(0, deque.capacity);
    TEST_ASSERT_EQUAL_size_t(0, deque.item_size);
    TEST_ASSERT_EQUAL_size_t(0, deque.front);
    TEST_ASSERT_EQUAL_size_t(0, deque.back);
}

void test_deque_push_and_get(void)
{
    Deque deque;
    deque_init(&deque, sizeof(int), 2);

    int a = 10, b = 20;
    deque_push_back(&deque, &a);
    deque_push_back(&deque, &b);

    TEST_ASSERT_EQUAL_size_t(2, deque.size);
    TEST_ASSERT_EQUAL_INT(a, *(int *) deque_get(&deque, 0));
    TEST_ASSERT_EQUAL_INT(b, *(int *) deque_get(&deque, 1));

    TEST_ASSERT_NULL(deque_get(&deque, 2));

    deque_free(&deque);
}

void test_deque_push_front_and_back(void)
{
    Deque deque;
    deque_init(&deque, sizeof(int), 2);

    int a = 1, b = 2, c = 3;
    deque_push_back(&deque, &a);
    deque_push_front(&deque, &b);
    deque_push_back(&deque, &c);

    TEST_ASSERT_EQUAL_size_t(3, deque.size);
    TEST_ASSERT_EQUAL_INT(b, *(int *) deque_get(&deque, 0));
    TEST_ASSERT_EQUAL_INT(a, *(int *) deque_get(&deque, 1));
    TEST_ASSERT_EQUAL_INT(c, *(int *) deque_get(&deque, 2));

    size_t old_size = deque.size;
    deque_push_front(&deque, &b);
    TEST_ASSERT_EQUAL_size_t(old_size + 1, deque.size);
    TEST_ASSERT_EQUAL_INT(b, *(int *) deque_get(&deque, 0));

    deque_free(&deque);
}

void test_deque_pop_front_and_back(void)
{
    Deque deque;
    deque_init(&deque, sizeof(int), 2);

    int a = 1, b = 2, c = 3;
    deque_push_back(&deque, &a);
    deque_push_back(&deque, &b);
    deque_push_back(&deque, &c);

    deque_pop_front(&deque);
    TEST_ASSERT_EQUAL_size_t(2, deque.size);
    TEST_ASSERT_EQUAL_INT(b, *(int *) deque_get(&deque, 0));
    TEST_ASSERT_EQUAL_INT(c, *(int *) deque_get(&deque, 1));

    deque_pop_back(&deque);
    TEST_ASSERT_EQUAL_size_t(1, deque.size);
    TEST_ASSERT_EQUAL_INT(b, *(int *) deque_get(&deque, 0));

    deque_pop_front(&deque);
    TEST_ASSERT_EQUAL_size_t(0, deque.size);

    deque_pop_back(&deque);
    TEST_ASSERT_EQUAL_size_t(0, deque.size);

    deque_free(&deque);
}

void test_deque_update_capacity(void)
{
    Deque deque;
    deque_init(&deque, sizeof(int), 2);

    int a = 1, b = 2, c = 3;
    deque_push_back(&deque, &a);
    deque_push_back(&deque, &b);
    deque_push_back(&deque, &c);

    TEST_ASSERT_EQUAL_size_t(3, deque.size);
    TEST_ASSERT_EQUAL_size_t(4, deque.capacity);
    TEST_ASSERT_EQUAL_INT(a, *(int *) deque_get(&deque, 0));
    TEST_ASSERT_EQUAL_INT(b, *(int *) deque_get(&deque, 1));
    TEST_ASSERT_EQUAL_INT(c, *(int *) deque_get(&deque, 2));

    deque_free(&deque);
}

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_deque_init_and_free);
    RUN_TEST(test_deque_push_and_get);
    RUN_TEST(test_deque_push_front_and_back);
    RUN_TEST(test_deque_pop_front_and_back);
    RUN_TEST(test_deque_update_capacity);

    return UNITY_END();
}
