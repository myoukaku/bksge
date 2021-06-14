/**
 *	@file	unit_test_fnd_algorithm_ranges_fill_n.cpp
 *
 *	@brief	ranges::fill_n のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/algorithm/ranges/fill_n.hpp>
#include <bksge/fnd/algorithm/ranges/equal.hpp>
#include <bksge/fnd/iterator/ranges/next.hpp>
#include <bksge/fnd/vector.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace bksge_algorithm_test
{

namespace ranges_fill_n_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline BKSGE_CXX14_CONSTEXPR bool test01()
{
	namespace ranges = bksge::ranges;
	{
		int x[] = { 1, 2, 3, 4, 5, 6 };
		auto res = ranges::fill_n(x, 3, 17);
		VERIFY(res == ranges::next(x, 3));
		int const y[] = { 17, 17, 17, 4, 5, 6 };
		VERIFY(ranges::equal(x, y));
	}
	{
		int x[] = { 1, 2, 3, 4, 5, 6 };
		auto res = ranges::fill_n(x, -1, 17);
		VERIFY(res == x);
		int const y[] = { 1, 2, 3, 4, 5, 6 };
		VERIFY(ranges::equal(x, y));
	}
	{
		int x[] = { 1, 2, 3, 4, 5, 6 };
		test_range<int, output_iterator_wrapper> rx(x);
		auto res = ranges::fill_n(rx.begin(), 3, 17);
		VERIFY(res.m_ptr == ranges::next(x, 3));
		int const y[] = { 17, 17, 17, 4, 5, 6 };
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
		X x[6] = { {1}, {2}, {3}, {4}, {5}, {6} };
		auto res = ranges::fill_n(x, 3, X{ 17 });
		VERIFY(res == ranges::next(x, 3));
		int const y[] = { 17, 17, 17, 4, 5, 6 };
		VERIFY(ranges::equal(x, y, {}, &X::i, {}));
	}
	{
		bksge::vector<int> x(5);
		auto res = ranges::fill_n(x.begin(), 2, 42);
		VERIFY(res == ranges::next(x.begin(), 2));
		int const y[] = { 42, 42, 0, 0, 0 };
		VERIFY(ranges::equal(x, y));
	}
	return true;
}

#undef VERIFY

GTEST_TEST(AlgorithmTest, RangesFillNTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	EXPECT_TRUE(test02());
}

}	// namespace ranges_fill_n_test

}	// namespace bksge_algorithm_test
