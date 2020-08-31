/**
 *	@file	unit_test_fnd_algorithm_ranges_includes.cpp
 *
 *	@brief	ranges::includes のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/algorithm/ranges/includes.hpp>
#include <bksge/fnd/functional/ranges/greater.hpp>
#include <gtest/gtest.h>
#include <vector>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace bksge_algorithm_test
{

namespace ranges_includes_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline BKSGE_CXX14_CONSTEXPR bool test01()
{
	namespace ranges = bksge::ranges;
	{
		int x[] = { 1,2,3,4,5,6,7 };
		int y[] = { 2,4,6 };
		test_range<int, input_iterator_wrapper> rx(x);
		test_range<int, input_iterator_wrapper> ry(y);
		VERIFY(ranges::includes(rx, ry));
	}
	{
		int x[] = { 7,6,5,4,3,2,1 };
		int y[] = { 6,4,2 };
		test_range<int, input_iterator_wrapper> rx(x);
		test_range<int, input_iterator_wrapper> ry(y);
		VERIFY(ranges::includes(rx, ry, ranges::greater{}));
	}
	{
		int x[] = { 1,2,3 };
		int y[] = { 1 };
		VERIFY( ranges::includes(x, y));
		VERIFY(!ranges::includes(y, x));
	}
	{
		int x[] = { 1,2,3,4 };
		int y[] = { 2,3,4,5 };
		VERIFY(!ranges::includes(x, y));
		VERIFY(!ranges::includes(y, x));
	}
	{
		int x[] = { 1,2,3 };
		int y[] = { 1,2,3,4 };
		VERIFY(!ranges::includes(x, y));
		VERIFY( ranges::includes(y, x));
	}
	{
		int x[] = { 1,2,3 };
		int y[] = { 1,2,3 };
		VERIFY( ranges::includes(x, y));
		VERIFY( ranges::includes(y, x));
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
		X x[] = { {1},{2},{3} };
		X y[] = { {1} };
		VERIFY( ranges::includes(x, y, {}, &X::i, &X::i));
		VERIFY(!ranges::includes(y, x, {}, &X::i, &X::i));
	}
	{
		std::vector<int> x = {};
		std::vector<int> y = {};
		VERIFY( ranges::includes(x, y));
		VERIFY( ranges::includes(y, x));
	}
	return true;
}

#undef VERIFY

GTEST_TEST(AlgorithmTest, RangesIncludesTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	EXPECT_TRUE(test02());
}

}	// namespace ranges_includes_test

}	// namespace bksge_algorithm_test
