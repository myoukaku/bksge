/**
 *	@file	unit_test_fnd_algorithm_ranges_fill.cpp
 *
 *	@brief	ranges::fill のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/algorithm/ranges/fill.hpp>
#include <bksge/fnd/algorithm/ranges/equal.hpp>
#include <bksge/fnd/iterator/ranges/next.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace bksge_algorithm_test
{

namespace ranges_fill_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline BKSGE_CXX14_CONSTEXPR bool test01()
{
	namespace ranges = bksge::ranges;
	{
		int x[] = { 1, 2, 3, 4, 5, 6 };
		auto res = ranges::fill(x, x + 3, 17);
		VERIFY(res == ranges::next(x, 3));
		int const y[] = { 17, 17, 17, 4, 5, 6 };
		VERIFY(ranges::equal(x, y));
	}
	{
		int x[] = { 1, 2, 3, 4, 5 };
		test_range<int, output_iterator_wrapper> rx(x);
		auto res = ranges::fill(rx, 18);
		VERIFY(res == rx.end());
		int const y[] = { 18, 18, 18, 18, 18 };
		VERIFY(ranges::equal(x, y));
	}
	return true;
}

struct X
{
	int i;
};

inline bool test02()
{
	namespace ranges = bksge::ranges;
	{
		X x[] = { {1}, {2}, {3}, {4}, {5} };
		auto res = ranges::fill(x, x + 3, X{ 17 });
		VERIFY(res == ranges::next(x, 3));
		int const y[] = { 17, 17, 17, 4, 5 };
		VERIFY(ranges::equal(x, y, {}, &X::i, {}));
	}
	{
		X x[] = { {1}, {2}, {3}, {4}, {5} };
		test_range<X, output_iterator_wrapper> rx(x);
		auto res = ranges::fill(rx, X{ 18 });
		VERIFY(res == rx.end());
		int const y[] = { 18, 18, 18, 18, 18 };
		VERIFY(ranges::equal(x, y, {}, &X::i, {}));
	}
	return true;
}

#undef VERIFY

GTEST_TEST(AlgorithmTest, RangesFillTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	EXPECT_TRUE(test02());
}

}	// namespace ranges_fill_test

}	// namespace bksge_algorithm_test
