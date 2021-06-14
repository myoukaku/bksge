/**
 *	@file	unit_test_fnd_algorithm_ranges_prev_permutation.cpp
 *
 *	@brief	ranges::prev_permutation のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/algorithm/ranges/prev_permutation.hpp>
#include <bksge/fnd/algorithm/ranges/equal.hpp>
#include <bksge/fnd/functional/ranges/greater.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace bksge_algorithm_test
{

namespace ranges_prev_permutation_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

struct Abs
{
	constexpr int operator()(int x) const
	{
		return x < 0 ? -x : x;
	}
};

inline BKSGE_CXX14_CONSTEXPR bool test01()
{
	namespace ranges = bksge::ranges;
	{
		int x[] = {3,2,1};
		{
			auto res = ranges::prev_permutation(x, x);
			VERIFY(res.in == x);
			VERIFY(res.found == false);
		}
		{
			auto res = ranges::prev_permutation(x, x+1);
			VERIFY(res.in == x+1);
			VERIFY(res.found == false);
		}
		{
			test_range<int, bidirectional_iterator_wrapper> r(x);
			auto res = ranges::prev_permutation(r);
			VERIFY(res.in == r.end());
			VERIFY(res.found == true);
			int const y[] = {3,1,2};
			VERIFY(ranges::equal(x, y));
		}
		{
			test_range<int, bidirectional_iterator_wrapper> r(x);
			auto res = ranges::prev_permutation(r);
			VERIFY(res.in == r.end());
			VERIFY(res.found == true);
			int const y[] = {2,3,1};
			VERIFY(ranges::equal(x, y));
		}
		{
			test_range<int, bidirectional_iterator_wrapper> r(x);
			auto res = ranges::prev_permutation(r);
			VERIFY(res.in == r.end());
			VERIFY(res.found == true);
			int const y[] = {2,1,3};
			VERIFY(ranges::equal(x, y));
		}
		{
			test_range<int, bidirectional_iterator_wrapper> r(x);
			auto res = ranges::prev_permutation(r);
			VERIFY(res.in == r.end());
			VERIFY(res.found == true);
			int const y[] = {1,3,2};
			VERIFY(ranges::equal(x, y));
		}
		{
			test_range<int, bidirectional_iterator_wrapper> r(x);
			auto res = ranges::prev_permutation(r);
			VERIFY(res.in == r.end());
			VERIFY(res.found == true);
			int const y[] = {1,2,3};
			VERIFY(ranges::equal(x, y));
		}
		{
			test_range<int, bidirectional_iterator_wrapper> r(x);
			auto res = ranges::prev_permutation(r);
			VERIFY(res.in == r.end());
			VERIFY(res.found == false);
			int const y[] = {3,2,1};
			VERIFY(ranges::equal(x, y));
		}
	}
	{
		int x[] = {-1,2,-3,4,-5};
		{
			test_range<int, bidirectional_iterator_wrapper> r(x);
			auto res = ranges::prev_permutation(r, ranges::greater{}, Abs{});
			VERIFY(res.in == r.end());
			VERIFY(res.found == true);
			int const y[] = {-1,2,-3,-5,4};
			VERIFY(ranges::equal(x, y));
		}
		{
			test_range<int, bidirectional_iterator_wrapper> r(x);
			auto res = ranges::prev_permutation(r, ranges::greater{}, Abs{});
			VERIFY(res.in == r.end());
			VERIFY(res.found == true);
			int const y[] = {-1,2,4,-3,-5};
			VERIFY(ranges::equal(x, y));
		}
	}
	return true;
}

#undef VERIFY

GTEST_TEST(AlgorithmTest, RangesPrevPermutationTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
}

}	// namespace ranges_prev_permutation_test

}	// namespace bksge_algorithm_test
