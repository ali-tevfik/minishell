#include "unity_fixture.h"

int add(int a, int b);

TEST_GROUP(AddNumbers);

TEST_SETUP(AddNumbers)
{
}

TEST_TEAR_DOWN(AddNumbers)
{
}

TEST(AddNumbers, Simple)
{
	TEST_ASSERT_EQUAL_INT(10, add(5, 5));
}

TEST(AddNumbers, ABC)
{
	TEST_ASSERT_EQUAL_INT(11, add(5, 6));
}