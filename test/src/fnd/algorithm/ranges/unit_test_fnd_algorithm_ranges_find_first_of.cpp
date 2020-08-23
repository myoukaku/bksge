/**
 *	@file	unit_test_fnd_algorithm_ranges_find_first_of.cpp
 *
 *	@brief	ranges::find_first_of のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/algorithm/ranges/find_first_of.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace bksge_algorithm_test
{

namespace ranges_find_first_of_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }


inline BKSGE_CXX14_CONSTEXPR bool test01()
{
	namespace ranges = bksge::ranges;

	{
		int x[] = { 1, 2, 3, 4, 5};
		int y[] = { 4, 2 };
		auto res1 = ranges::find_first_of(x, x+5, y, y+2);
		VERIFY(res1 == x+1);
		auto res2 = ranges::find_first_of(x+2, x+5, y, y+2);
		VERIFY(res2 == x+3);
		auto res3 = ranges::find_first_of(x, y);
		VERIFY(res3 == x+1);
	}
	{
		int x[] = { 1, 2, 3, 4, 5};
		int y[] = { 8, 7, 6, 5 };
		test_range<int, input_iterator_wrapper>   r1(x);
		test_range<int, forward_iterator_wrapper> r2(y);
		auto res1 = ranges::find_first_of(r1, r2);
		VERIFY(*res1 == 5);
		test_range<int, forward_iterator_wrapper> r3(y, y+3);
		auto res2 = ranges::find_first_of(r1, r3);
		VERIFY(res2 == r1.end());
	}

	return true;
}

struct X { int i; };

inline bool test02()
{
	namespace ranges = bksge::ranges;

	X x[] = { {2}, {2}, {6}, {8}, {10}, {11} };
	int y[] = { 2, 7, 8, 9 };
	X w[] = { {2}, {7}, {8}, {9} };

	auto res = ranges::find_first_of(x, x+6, y+1, y+4, {}, &X::i);
	VERIFY(res == x+3);
	res = ranges::find_first_of(x, x+6, w, w+4, {}, &X::i, &X::i);
	VERIFY(res == x+0);
	res = ranges::find_first_of(x, x+6, y+3, y+4, {}, &X::i);
	VERIFY(res == x+6);

	test_range<X, forward_iterator_wrapper> c(x);
	test_range<int, forward_iterator_wrapper> d1(y+1, y+4);
	auto res2 = ranges::find_first_of(c, d1, {}, &X::i);
	VERIFY(res2 != ranges::end(c) && (*res2).i == 8);

	test_range<X, forward_iterator_wrapper> d2(w+3, w+4);
	res2 = ranges::find_first_of(c, d2, {}, &X::i, &X::i);
	VERIFY(res2 == ranges::end(c));

	test_range<X, input_iterator_wrapper> r(x);
	test_range<int, forward_iterator_wrapper> s1(y+1, y+4);
	auto res3 = ranges::find_first_of(r, s1, {}, &X::i);
	VERIFY(res3 != ranges::end(r) && (*res3).i == 8);

	test_range<X, input_iterator_wrapper> r2(x);
	test_range<X, forward_iterator_wrapper> s2(w+3, w+4);
	res3 = ranges::find_first_of(r2, s2, {}, &X::i, &X::i);
	VERIFY(res3 == ranges::end(r2));

	return true;
}

struct Y { int i; int j; };

inline bool test03()
{
	namespace ranges = bksge::ranges;

	Y y[] = { {1,2}, {2,4}, {3,6} };
	VERIFY(ranges::find_first_of(y, y, {}, &Y::j, &Y::i) == y);
	VERIFY(ranges::find_first_of(y, y, {}, &Y::i, &Y::j) == y+1);

	return true;
}

#undef VERIFY

GTEST_TEST(AlgorithmTest, RangesFindFirstOfTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	EXPECT_TRUE(test02());
	EXPECT_TRUE(test03());
}

}	// namespace ranges_find_first_of_test

}	// namespace bksge_algorithm_test
