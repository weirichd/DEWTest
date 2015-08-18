/*
 * dewtest.c
 */

/*
 * This is a simple example of a test using DEWTest.
 */

#include "dewtest.h"

int mul(int a, int b)
{
	return a * b;
}

int main()
{
	DEW_assert_true(1);
	DEW_assert_true(0); // This should fail
	DEW_assert_false(0);
	DEW_assert_false(10); // This too

	int x = 1;
	DEW_assert_true(x);

	// It works for complicated stuff like this too!
	DEW_assert_true(mul(3,4) == 12);
	DEW_assert_true(mul(3,4) != 2);

	// For assert equals, you need to pass a format string
	// for it to use while printing the error
	DEW_assert_equal(3, 3, "%d");
	DEW_assert_equal(3, 5, "%d");
	DEW_assert_not_equal(5.2f, 15.2f, "%f");
	DEW_assert_not_equal(15.2f, 15.2f, "%f");

	// Default value for epsilon
	DEW_assert_close(2.0f, 2.00001f, "%f");
	DEW_assert_close(2.0f, 2.5f, "%f");

	// Or refdefine it
	#undef DEWTEST_EPSILON
	#define DEWTEST_EPSILON 1.0f

	DEW_assert_close(2.0f, 2.5f, "%f");

	return 0;
}
