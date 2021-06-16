/**
 *	@file	unit_test_fnd_algorithm_ranges_replace.cpp
 *
 *	@brief	ranges::replace のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/algorithm/ranges/replace.hpp>
#include <bksge/fnd/algorithm/ranges/equal.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace bksge_algorithm_test
{

namespace ranges_replace_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline BKSGE_CXX14_CONSTEXPR bool test01()
{
	namespace ranges = bksge::ranges;
	{
		int x[] = { 3,1,4,1,5 };
		auto res = ranges::replace(x, x+5, 1, 0);
		VERIFY(res == x+5);
		int y[] = { 3,0,4,0,5 };
		VERIFY(ranges::equal(x, y));
	}
	return true;
}

inline BKSGE_CXX14_CONSTEXPR bool test02()
{
	namespace ranges = bksge::ranges;
	{
		int x[] = { 1,3,1,4,1,5,1 };
		test_range<int, input_iterator_wrapper> rx(x);
		auto res = ranges::replace(rx, 1, 0);
		VERIFY(res == rx.end());
		int y[] = { 0,3,0,4,0,5,0 };
		VERIFY(ranges::equal(x, y));
	}
	return true;
}

struct X
{
	int i;

	friend constexpr bool
	operator==(const X& a, const X& b)
	{
		return a.i == b.i;
	}

	friend constexpr bool
	operator!=(const X& a, const X& b)
	{
		return !(a == b);
	}
};

struct Y
{
	int i;
	int j;

	friend constexpr bool
	operator==(const Y& a, const Y& b)
	{
		return a.i == b.i && a.j == b.j;
	}

	friend constexpr bool
	operator!=(const Y& a, const Y& b)
	{
		return !(a == b);
	}
};

inline bool test03()
{
	namespace ranges = bksge::ranges;
	{
		X x[6] = { {2}, {2}, {6}, {8}, {10}, {8} };
		auto res = ranges::replace(x, x+5, 8, X{ 9 }, &X::i);
		VERIFY(res == x+5);
		X y[6] = { {2}, {2}, {6}, {9}, {10}, {8} };
		VERIFY(ranges::equal(x, y));
	}
	return true;
}

inline bool test04()
{
	namespace ranges = bksge::ranges;
	{
		Y x[] = { {3,2}, {2,4}, {3,6} };
		auto res = ranges::replace(x, 3, Y{ 4,5 }, &Y::i);
		VERIFY(res == x+3);
		Y y[] = { {4,5}, {2,4}, {4,5} };
		VERIFY(ranges::equal(x, y));
	}
	return true;
}

#undef VERIFY

GTEST_TEST(AlgorithmTest, RangesReplaceTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
	EXPECT_TRUE(test03());
	EXPECT_TRUE(test04());
}

}	// namespace ranges_replace_test

}	// namespace bksge_algorithm_test
