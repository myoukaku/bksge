/**
 *	@file	unit_test_fnd_algorithm_ranges_replace_copy.cpp
 *
 *	@brief	ranges::replace_copy のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/algorithm/ranges/replace_copy.hpp>
#include <bksge/fnd/algorithm/ranges/equal.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace bksge_algorithm_test
{

namespace ranges_replace_copy_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline BKSGE_CXX14_CONSTEXPR bool test01()
{
	namespace ranges = bksge::ranges;
	{
		int x[] = { 3,1,4,1,5 };
		int w[5] = {};
		auto res = ranges::replace_copy(x, x+5, w, 1, 0);
		VERIFY(res.in  == x+5);
		VERIFY(res.out == w+5);
		int y[] = { 3,0,4,0,5 };
		VERIFY(ranges::equal(w, y));
	}
	return true;
}

inline BKSGE_CXX14_CONSTEXPR bool test02()
{
	namespace ranges = bksge::ranges;
	{
		int x[] = { 1,3,1,4,1,5,1 };
		int w[7] = {};
		test_range<int, input_iterator_wrapper> rx(x);
		test_range<int, output_iterator_wrapper> rw(w);
		auto res = ranges::replace_copy(rx, rw.begin(), 1, 0);
		VERIFY(res.in  == rx.end());
		VERIFY(res.out == rw.end());
		int y[] = { 0,3,0,4,0,5,0 };
		VERIFY(ranges::equal(w, y));
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
		X const x[6] = { {2}, {2}, {6}, {8}, {10}, {8} };
		X w[5] = {};
		auto res = ranges::replace_copy(x, x+5, w, 8, X{ 9 }, &X::i);
		VERIFY(res.in  == x+5);
		VERIFY(res.out == w+5);
		X const y[5] = { {2}, {2}, {6}, {9}, {10} };
		VERIFY(ranges::equal(w, y));
	}
	{
		X const x[6] = { {2}, {4}, {6}, {8}, {10}, {2} };
		X w[6] = {};
		auto res = ranges::replace_copy(x, x+6, w, 2, X{ 0 }, &X::i);
		VERIFY(res.in  == x+6);
		VERIFY(res.out == w+6);
		X const y[6] = { {0}, {4}, {6}, {8}, {10}, {0} };
		VERIFY(ranges::equal(w, y));
	}
	return true;
}

inline bool test04()
{
	namespace ranges = bksge::ranges;
	{
		Y const x[] = { {3,2}, {2,4}, {3,6} };
		Y w[3] = {};
		auto res = ranges::replace_copy(x, w, 3, Y{ 4,5 }, &Y::i);
		VERIFY(res.in  == x+3);
		VERIFY(res.out == w+3);
		Y const y[] = { {4,5}, {2,4}, {4,5} };
		VERIFY(ranges::equal(w, y));
	}
	{
		Y const x[] = { {3,2}, {2,4}, {3,6} };
		Y w[3] = {};
		auto res = ranges::replace_copy(x, w, 4, Y{ 5,6 }, &Y::j);
		VERIFY(res.in  == x+3);
		VERIFY(res.out == w+3);
		Y const y[] = { {3,2}, {5,6}, {3,6} };
		VERIFY(ranges::equal(w, y));
	}
	return true;
}

#undef VERIFY

GTEST_TEST(AlgorithmTest, RangesReplaceCopyTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
	EXPECT_TRUE(test03());
	EXPECT_TRUE(test04());
}

}	// namespace ranges_replace_copy_test

}	// namespace bksge_algorithm_test
