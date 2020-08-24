/**
 *	@file	unit_test_fnd_algorithm_ranges_count.cpp
 *
 *	@brief	ranges::count のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/algorithm/ranges/count.hpp>
#include <bksge/fnd/ranges/begin.hpp>
#include <bksge/fnd/ranges/end.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace bksge_algorithm_test
{

namespace ranges_count_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }


inline BKSGE_CXX14_CONSTEXPR bool test01()
{
	namespace ranges = bksge::ranges;

	int x[] = { 4,3,1,4,1,4,5,9,4,2,6,5,5,4, };

	VERIFY(ranges::count(ranges::begin(x), ranges::end(x), 0) == 0);
	VERIFY(ranges::count(ranges::begin(x), ranges::end(x), 1) == 2);
	VERIFY(ranges::count(ranges::begin(x), ranges::end(x), 2) == 1);
	VERIFY(ranges::count(x, 3) == 1);
	VERIFY(ranges::count(x, 4) == 5);
	VERIFY(ranges::count(x, 5) == 3);
	VERIFY(ranges::count(x, 6) == 1);
	VERIFY(ranges::count(x, 7) == 0);

	return true;
}

struct X { int i; };

inline bool test02()
{
	namespace ranges = bksge::ranges;

	X x[] = { {2}, {2}, {6}, {8}, {10}, {11}, {2} };
	auto res = ranges::count(x, x+7, 2, &X::i);
	VERIFY(res == 3);
	res = ranges::count(x, x+7, 8, &X::i);
	VERIFY(res == 1);
	res = ranges::count(x, x+7, 9, &X::i);
	VERIFY(res == 0);

	test_range<X, forward_iterator_wrapper> c(x);
	res = ranges::count(c, 6, &X::i);
	VERIFY(res == 1);
	res = ranges::count(c, 9, &X::i);
	VERIFY(res == 0);

	test_range<X, input_iterator_wrapper> r(x);
	res = ranges::count(r, 2, &X::i);
	VERIFY(res == 3);

	test_range<X, input_iterator_wrapper> r2(x);
	res = ranges::count(r2, 9, &X::i);
	VERIFY(res == 0);

	return true;
}

struct Y { int i; int j; };

inline bool test03()
{
	namespace ranges = bksge::ranges;

	Y y[] = { {1,2}, {2,4}, {3,6}, {1,6} };
	VERIFY(ranges::count(y, 6, &Y::j) == 2);
	VERIFY(ranges::count(y, 5, &Y::j) == 0);

	return true;
}

#undef VERIFY

GTEST_TEST(AlgorithmTest, RangesCountTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	EXPECT_TRUE(test02());
	EXPECT_TRUE(test03());
}

}	// namespace ranges_count_test

}	// namespace bksge_algorithm_test
