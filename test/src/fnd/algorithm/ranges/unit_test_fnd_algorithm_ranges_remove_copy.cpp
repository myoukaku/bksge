/**
 *	@file	unit_test_fnd_algorithm_ranges_remove_copy.cpp
 *
 *	@brief	ranges::remove_copy のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/algorithm/ranges/remove_copy.hpp>
#include <bksge/fnd/algorithm/ranges/equal.hpp>
#include <bksge/fnd/iterator/ranges/next.hpp>
#include <bksge/fnd/forward_list.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace bksge_algorithm_test
{

namespace ranges_remove_copy_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline BKSGE_CXX14_CONSTEXPR bool test01()
{
	namespace ranges = bksge::ranges;
	{
		int const x[] = { 1, 2, 3, 4, 5 };
		int w[5] = {};
		auto res = ranges::remove_copy(x, x+5, w, 3);
		VERIFY(res.in  == x+5);
		VERIFY(res.out == w+4);
		const int y[] = { 1, 2, 4, 5 };
		VERIFY(ranges::equal(w, w+4, y, y+4));
	}
	{
		int const x[] = { 1, 2, 3, 4, 5 };
		test_range<int const, forward_iterator_wrapper> rx(x);
		int w[5] = {};
		auto res = ranges::remove_copy(rx, w, 2);
		VERIFY(res.in  == rx.end());
		VERIFY(res.out == w+4);
		const int y[] = { 1, 3, 4, 5 };
		VERIFY(ranges::equal(w, w+4, y, y+4));
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
		X x[] = { {0}, {1}, {0}, {0}, {2}, {3}, {0}, {0}, {0} };
		X w[3] = {};
		auto res = ranges::remove_copy(x, x+9, w, 0, &X::i);
		VERIFY(res.in  == x+9);
		VERIFY(res.out == w+3);
		const int y[] = { 1, 2, 3 };
		VERIFY(ranges::equal(w, w+3, y, y+3, {}, &X::i));
	}
	{
		X x[] = { {1}, {2}, {3} };
		test_range<X, forward_iterator_wrapper> rx(x);
		X w[3] = {};
		auto res = ranges::remove_copy(rx, w, 0, &X::i);
		VERIFY(res.in  == rx.end());
		VERIFY(res.out == w+3);
		const int y[] = { 1, 2, 3 };
		VERIFY(ranges::equal(w, w+3, y, y+3, {}, &X::i));
	}
	{
		bksge::forward_list<int> x = {};
		int w[3] = {};
		auto res = ranges::remove_copy(x, w, 0);
		VERIFY(res.in  == x.end());
		VERIFY(res.out == w+0);
	}
	return true;
}

#undef VERIFY

GTEST_TEST(AlgorithmTest, RangesRemoveCopyTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	EXPECT_TRUE(test02());
}

}	// namespace ranges_remove_copy_test

}	// namespace bksge_algorithm_test
