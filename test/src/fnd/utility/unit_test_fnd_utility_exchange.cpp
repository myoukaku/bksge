/**
 *	@file	unit_test_fnd_utility_exchange.cpp
 *
 *	@brief	exchange のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/utility/exchange.hpp>
#include <gtest/gtest.h>
#include <vector>
#include "constexpr_test.hpp"

namespace bksge_utility_test
{

namespace exchange_test
{

int f() { return 31; }

BKSGE_CXX14_CONSTEXPR bool test_constexpr()
{
	int v = 12;

	if (12 != bksge::exchange(v, 23) || v != 23)
	{
		return false;
	}

	if (23 != bksge::exchange(v, static_cast<short>(67)) || v != 67)
	{
		return false;
	}

	if (67 != bksge::exchange<int, short>(v, {}) || v != 0)
	{
		return false;
	}

	return true;
}

GTEST_TEST(UtilityTest, ExchangeTest)
{
	{
		int n = 42;
		int t = bksge::exchange(n, 10);
		EXPECT_EQ(10, n);
		EXPECT_EQ(42, t);
		t = bksge::exchange(n, 20);
		EXPECT_EQ(20, n);
		EXPECT_EQ(10, t);
	}
	{
		std::vector<int> v;
		auto t = bksge::exchange(v, {1, 2, 3, 4});

		EXPECT_EQ(4u, v.size());
		EXPECT_EQ(1, v[0]);
		EXPECT_EQ(2, v[1]);
		EXPECT_EQ(3, v[2]);
		EXPECT_EQ(4, v[3]);
		EXPECT_EQ(0u, t.size());

		t = bksge::exchange(v, {10, 20, 30});
		EXPECT_EQ(4u, t.size());
		EXPECT_EQ(1, t[0]);
		EXPECT_EQ(2, t[1]);
		EXPECT_EQ(3, t[2]);
		EXPECT_EQ(4, t[3]);
		EXPECT_EQ(3u, v.size());
		EXPECT_EQ(10, v[0]);
		EXPECT_EQ(20, v[1]);
		EXPECT_EQ(30, v[2]);
	}
	{
		int (*fun)();
		bksge::exchange(fun, f);
		EXPECT_EQ(31, fun());
	}

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test_constexpr());
}

}	// namespace exchange_test

}	// namespace bksge_utility_test
