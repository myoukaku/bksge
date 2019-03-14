/**
 *	@file	unit_test_utility_swap.cpp
 *
 *	@brief	swap のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/utility/swap.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace bksge_utility_test
{

namespace swap_test
{

class Foo
{
public:
	Foo(int v) : value(v) {}

	Foo(Foo&& rhs) = delete;

	int get() const { return value; }

	void swap(Foo& b)
	{
		using bksge::swap;
		swap(value, b.value);
	}

private:
	int value;
};

void swap(Foo& a, Foo& b)
{
	a.swap(b);
}

GTEST_TEST(UtilityTest, SwapTest)
{
	using bksge::swap;

	{
		int a = 1;
		int b = 2;
		swap(a, b);

		EXPECT_EQ(2, a);
		EXPECT_EQ(1, b);
	}
	{
		float a = 1.5;
		float b = 2.5;
		swap(a, b);

		EXPECT_EQ(2.5, a);
		EXPECT_EQ(1.5, b);
	}
	{
		int a[] = { 1, 2, 3 };
		int b[] = { 4, 5, 6 };
		swap(a, b);

		EXPECT_EQ(4, a[0]);
		EXPECT_EQ(5, a[1]);
		EXPECT_EQ(6, a[2]);
		EXPECT_EQ(1, b[0]);
		EXPECT_EQ(2, b[1]);
		EXPECT_EQ(3, b[2]);
	}
	{
		Foo a(1);
		Foo b(2);
		swap(a, b);

		EXPECT_EQ(2, a.get());
		EXPECT_EQ(1, b.get());
	}
}

}	// namespace swap_test

}	// namespace bksge_utility_test
