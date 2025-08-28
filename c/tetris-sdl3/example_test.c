#include <unity.h>

void setUp(void)
{
}

void tearDown(void)
{
}

void example_test()
{
    TEST_ASSERT_EQUAL_INT32(4, 2 + 2);
}

int main()
{
    UNITY_BEGIN();
    RUN_TEST(example_test);
    return UNITY_END();
}
