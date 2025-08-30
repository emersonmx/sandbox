#include <string.h>
#include <unity.h>

#include "array.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_array_init_and_free()
{
    Array arr;
    array_init(&arr, sizeof(int), 4);
    TEST_ASSERT_NOT_NULL(arr.data);
    TEST_ASSERT_EQUAL_size_t(0, arr.size);
    TEST_ASSERT_EQUAL_size_t(4, arr.capacity);
    TEST_ASSERT_EQUAL_size_t(sizeof(int), arr.item_size);

    array_free(&arr);
    TEST_ASSERT_NULL(arr.data);
    TEST_ASSERT_EQUAL_size_t(0, arr.size);
    TEST_ASSERT_EQUAL_size_t(0, arr.capacity);
    TEST_ASSERT_EQUAL_size_t(0, arr.item_size);
}

void test_array_push_and_get()
{
    Array arr;
    array_init(&arr, sizeof(int), 2);

    int a = 10, b = 20;
    array_push(&arr, &a);
    array_push(&arr, &b);

    TEST_ASSERT_EQUAL_size_t(2, arr.size);
    TEST_ASSERT_EQUAL_INT(a, *(int *)array_get(&arr, 0));
    TEST_ASSERT_EQUAL_INT(b, *(int *)array_get(&arr, 1));

    TEST_ASSERT_NULL(array_get(&arr, 2));

    array_free(&arr);
}

void test_array_insert()
{
    Array arr;
    array_init(&arr, sizeof(int), 2);

    int a = 1, b = 2, c = 3;
    array_push(&arr, &a);
    array_push(&arr, &c);

    array_insert(&arr, 1, &b);

    TEST_ASSERT_EQUAL_size_t(3, arr.size);
    TEST_ASSERT_EQUAL_INT(a, *(int *)array_get(&arr, 0));
    TEST_ASSERT_EQUAL_INT(b, *(int *)array_get(&arr, 1));
    TEST_ASSERT_EQUAL_INT(c, *(int *)array_get(&arr, 2));

    size_t old_size = arr.size;
    array_insert(&arr, 5, &a);
    TEST_ASSERT_EQUAL_size_t(old_size, arr.size);

    array_free(&arr);
}

void test_array_remove()
{
    Array arr;
    array_init(&arr, sizeof(int), 3);

    int a = 1, b = 2, c = 3;
    array_push(&arr, &a);
    array_push(&arr, &b);
    array_push(&arr, &c);

    array_remove(&arr, 1);
    TEST_ASSERT_EQUAL_size_t(2, arr.size);
    TEST_ASSERT_EQUAL_INT(a, *(int *)array_get(&arr, 0));
    TEST_ASSERT_EQUAL_INT(c, *(int *)array_get(&arr, 1));

    size_t old_size = arr.size;
    array_remove(&arr, 5);
    TEST_ASSERT_EQUAL_size_t(old_size, arr.size);

    array_free(&arr);
}

void test_array_grow()
{
    Array arr;
    array_init(&arr, sizeof(int), 2);

    array_grow(&arr, 5);
    TEST_ASSERT_EQUAL_size_t(5, arr.capacity);

    array_grow(&arr, 3);
    TEST_ASSERT_EQUAL_size_t(5, arr.capacity);

    array_free(&arr);
}

void test_array_pop()
{
    Array arr;
    array_init(&arr, sizeof(int), 2);

    int a = 1, b = 2;
    array_push(&arr, &a);
    array_push(&arr, &b);

    array_pop(&arr);
    TEST_ASSERT_EQUAL_size_t(1, arr.size);
    TEST_ASSERT_EQUAL_INT(a, *(int *)array_get(&arr, 0));

    array_pop(&arr);
    TEST_ASSERT_EQUAL_size_t(0, arr.size);

    array_pop(&arr);
    TEST_ASSERT_EQUAL_size_t(0, arr.size);

    array_free(&arr);
}

int main()
{
    UNITY_BEGIN();

    RUN_TEST(test_array_init_and_free);
    RUN_TEST(test_array_push_and_get);
    RUN_TEST(test_array_insert);
    RUN_TEST(test_array_remove);
    RUN_TEST(test_array_grow);
    RUN_TEST(test_array_pop);

    return UNITY_END();
}
