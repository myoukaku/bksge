/**
 *	@file	unit_test_fnd_algorithm_ranges_replace_if.cpp
 *
 *	@brief	ranges::replace_if のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/algorithm/ranges/replace_if.hpp>
#include <bksge/fnd/algorithm/ranges/equal.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace bksge_algorithm_test
{

namespace ranges_replace_if_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <int N>
struct Less
{
	constexpr bool operator()(int x) const
	{
		return x < N;
	}
};

template <int N>
struct Greater
{
	constexpr bool operator()(int x) const
	{
		return x > N;
	}
};

inline BKSGE_CXX14_CONSTEXPR bool test01()
{
	namespace ranges = bksge::ranges;
	{
		int x[] = { 1,2,3,4,5,6,7,8,9 };
		auto res = ranges::replace_if(x, x+9, Less<5>{}, 0);
		VERIFY(res == x+9);
		int y[] = { 0,0,0,0,5,6,7,8,9 };
		VERIFY(ranges::equal(x, y));
	}
	{
		int x[] = { 1,2,3,4,5,6,7,8,9 };
		auto res = ranges::replace_if(x, x+9, Greater<5>{}, 1);
		VERIFY(res == x+9);
		int y[] = { 1,2,3,4,5,1,1,1,1 };
		VERIFY(ranges::equal(x, y));
	}
	return true;
}

inline BKSGE_CXX14_CONSTEXPR bool test02()
{
	namespace ranges = bksge::ranges;
	{
		int x[] = { 3,1,4,1,5,9,2,6,5 };
		test_range<int, input_iterator_wrapper> rx(x);
		auto res = ranges::replace_if(rx, Less<5>{}, 0);
		VERIFY(res == rx.end());
		int y[] = { 0,0,0,0,5,9,0,6,5 };
		VERIFY(ranges::equal(x, y));
	}
	{
		int x[] = { 3,1,4,1,5,9,2,6,5 };
		test_range<int, input_iterator_wrapper> rx(x);
		auto res = ranges::replace_if(rx, Greater<3>{}, 8);
		VERIFY(res == rx.end());
		int y[] = { 3,1,8,1,8,8,2,8,8 };
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
		X x[6] = { {1}, {2}, {3}, {4}, {5}, {6} };
		auto res = ranges::replace_if(x, x+5, [](int a){return a%2 == 0; }, X{ 9 }, &X::i);
		VERIFY(res == x+5);
		X y[6] = { {1}, {9}, {3}, {9}, {5}, {6} };
		VERIFY(ranges::equal(x, y));
	}
	return true;
}

inline bool test04()
{
	namespace ranges = bksge::ranges;
	{
		Y x[] = { {1,2}, {2,4}, {3,6} };
		auto res = ranges::replace_if(x, [](int a){return a%2 == 1; }, Y{ 4,5 }, &Y::i);
		VERIFY(res == x+3);
		Y y[] = { {4,5}, {2,4}, {4,5} };
		VERIFY(ranges::equal(x, y));
	}
	{
		Y x[] = { {1,2}, {2,4}, {3,6} };
		auto res = ranges::replace_if(x, [](int a){return a%2 == 1; }, Y{ 4,5 }, &Y::j);
		VERIFY(res == x+3);
		Y y[] = { {1,2}, {2,4}, {3,6} };
		VERIFY(ranges::equal(x, y));
	}
	return true;
}

#undef VERIFY

GTEST_TEST(AlgorithmTest, RangesReplaceIfTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
	EXPECT_TRUE(test03());
	EXPECT_TRUE(test04());
}

}	// namespace ranges_replace_if_test

}	// namespace bksge_algorithm_test
