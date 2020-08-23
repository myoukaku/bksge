/**
 *	@file	unit_test_fnd_algorithm_ranges_find.cpp
 *
 *	@brief	ranges::find のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/algorithm/ranges/find.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace bksge_algorithm_test
{

namespace ranges_find_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline BKSGE_CXX14_CONSTEXPR bool test01()
{
	namespace ranges = bksge::ranges;

	int x[] = { 2, 2, 6, 8, 10, 11 };
	{
		auto res = ranges::find(x, x+6, 8);
		VERIFY(res == x+3);
		res = ranges::find(x, x+6, 2);
		VERIFY(res == x+0);
		res = ranges::find(x, x+6, 9);
		VERIFY(res == x+6);
	}
	{
		test_range<int, forward_iterator_wrapper> c(x);
		auto res = ranges::find(c, 8);
		VERIFY(res != ranges::end(c) && *res == 8);
		res = ranges::find(c, 9);
		VERIFY(res == ranges::end(c));
	}
	{
		test_range<int, input_iterator_wrapper> r(x);
		auto res = ranges::find(r, 8);
		VERIFY(res != ranges::end(r) && *res == 8);
	}
	{
		test_range<int, input_iterator_wrapper> r(x);
		auto res = ranges::find(r, 9);
		VERIFY(res == ranges::end(r));
	}
	return true;
}

struct X { int i; };

inline bool test02()
{
	namespace ranges = bksge::ranges;

	X x[] = { {2}, {2}, {6}, {8}, {10}, {11} };
	{
		auto res = ranges::find(x, x+6, 8, &X::i);
		VERIFY(res == x+3);
		res = ranges::find(x, x+6, 2, &X::i);
		VERIFY(res == x+0);
		res = ranges::find(x, x+6, 9, &X::i);
		VERIFY(res == x+6);
	}
	{
		test_range<X, forward_iterator_wrapper> c(x);
		auto res = ranges::find(c, 8, &X::i);
		VERIFY(res != ranges::end(c) && (*res).i == 8);
		res = ranges::find(c, 9, &X::i);
		VERIFY(res == ranges::end(c));
	}
	{
		test_range<X, input_iterator_wrapper> r(x);
		auto res = ranges::find(r, 8, &X::i);
		VERIFY(res != ranges::end(r) && (*res).i == 8);
	}
	{
		test_range<X, input_iterator_wrapper> r(x);
		auto res = ranges::find(r, 9, &X::i);
		VERIFY(res == ranges::end(r));
	}
	return true;
}

struct Y { int i; int j; };

inline bool test03()
{
	namespace ranges = bksge::ranges;

	Y y[] = { {1,2}, {2,4}, {3,6} };
	VERIFY(ranges::find(y, 2, &Y::i) == y+1);
	VERIFY(ranges::find(y, 4, &Y::i) == y+3);
	VERIFY(ranges::find(y, 5, &Y::i) == y+3);
	VERIFY(ranges::find(y, 2, &Y::j) == y+0);
	VERIFY(ranges::find(y, 4, &Y::j) == y+1);
	VERIFY(ranges::find(y, 5, &Y::j) == y+3);

	return true;
}

#undef VERIFY

GTEST_TEST(AlgorithmTest, RangesFindTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	EXPECT_TRUE(test02());
	EXPECT_TRUE(test03());
}

}	// namespace ranges_find_test

}	// namespace bksge_algorithm_test
