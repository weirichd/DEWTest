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
	DEW_assert_false(1); // This too

	DEW_assert_true(mul(3,4) == 12);

	DEW_assert_equal(3, 3);
	DEW_assert_equal(3, 5);

	return 0;
}
