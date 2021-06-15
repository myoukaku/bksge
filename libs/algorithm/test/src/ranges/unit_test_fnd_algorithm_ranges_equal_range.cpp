/**
 *	@file	unit_test_fnd_algorithm_ranges_equal_range.cpp
 *
 *	@brief	ranges::equal_range のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/algorithm/ranges/equal_range.hpp>
#include <bksge/fnd/iterator/ranges/next.hpp>
#include <bksge/fnd/functional/ranges/greater.hpp>
#include <bksge/fnd/forward_list.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace bksge_algorithm_test
{

namespace ranges_equal_range_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline BKSGE_CXX14_CONSTEXPR bool test01()
{
	namespace ranges = bksge::ranges;
	{
		int const x[] = { 1,2,2,3,3,3,5,5,5 };
		test_range<int const, forward_iterator_wrapper> r(x);
		{
			auto res = ranges::equal_range(r, 0);
			VERIFY(res.begin() == ranges::next(r.begin(), 0));
			VERIFY(res.end()   == ranges::next(r.begin(), 0));
		}
		{
			auto res = ranges::equal_range(r, 1);
			VERIFY(res.begin() == ranges::next(r.begin(), 0));
			VERIFY(res.end()   == ranges::next(r.begin(), 1));
		}
		{
			auto res = ranges::equal_range(r, 2);
			VERIFY(res.begin() == ranges::next(r.begin(), 1));
			VERIFY(res.end()   == ranges::next(r.begin(), 3));
		}
		{
			auto res = ranges::equal_range(r, 3);
			VERIFY(res.begin() == ranges::next(r.begin(), 3));
			VERIFY(res.end()   == ranges::next(r.begin(), 6));
		}
		{
			auto res = ranges::equal_range(r, 4);
			VERIFY(res.begin() == ranges::next(r.begin(), 6));
			VERIFY(res.end()   == ranges::next(r.begin(), 6));
		}
		{
			auto res = ranges::equal_range(r, 5);
			VERIFY(res.begin() == ranges::next(r.begin(), 6));
			VERIFY(res.end()   == ranges::next(r.begin(), 9));
		}
		{
			auto res = ranges::equal_range(r, 6);
			VERIFY(res.begin() == ranges::next(r.begin(), 9));
			VERIFY(res.end()   == ranges::next(r.begin(), 9));
		}
	}
	{
		int const x[] = { 8,7,7,5,3,3,3 };
		test_range<int const, forward_iterator_wrapper> r(x);
		{
			auto res = ranges::equal_range(r, 9, ranges::greater{});
			VERIFY(res.begin() == ranges::next(r.begin(), 0));
			VERIFY(res.end()   == ranges::next(r.begin(), 0));
		}
		{
			auto res = ranges::equal_range(r, 8, ranges::greater{});
			VERIFY(res.begin() == ranges::next(r.begin(), 0));
			VERIFY(res.end()   == ranges::next(r.begin(), 1));
		}
		{
			auto res = ranges::equal_range(r, 7, ranges::greater{});
			VERIFY(res.begin() == ranges::next(r.begin(), 1));
			VERIFY(res.end()   == ranges::next(r.begin(), 3));
		}
		{
			auto res = ranges::equal_range(r, 6, ranges::greater{});
			VERIFY(res.begin() == ranges::next(r.begin(), 3));
			VERIFY(res.end()   == ranges::next(r.begin(), 3));
		}
		{
			auto res = ranges::equal_range(r, 5, ranges::greater{});
			VERIFY(res.begin() == ranges::next(r.begin(), 3));
			VERIFY(res.end()   == ranges::next(r.begin(), 4));
		}
		{
			auto res = ranges::equal_range(r, 4, ranges::greater{});
			VERIFY(res.begin() == ranges::next(r.begin(), 4));
			VERIFY(res.end()   == ranges::next(r.begin(), 4));
		}
		{
			auto res = ranges::equal_range(r, 3, ranges::greater{});
			VERIFY(res.begin() == ranges::next(r.begin(), 4));
			VERIFY(res.end()   == ranges::next(r.begin(), 7));
		}
		{
			auto res = ranges::equal_range(r, 2, ranges::greater{});
			VERIFY(res.begin() == ranges::next(r.begin(), 7));
			VERIFY(res.end()   == ranges::next(r.begin(), 7));
		}
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
		X const x[] = { {0},{1},{1},{2},{2},{2} };
		auto res = ranges::equal_range(x, x+6, 2, {}, &X::i);
		VERIFY(res.begin() == ranges::next(x, 3));
		VERIFY(res.end()   == ranges::next(x, 6));
	}
	{
		X const x[] = { {2},{2},{1},{1},{0},{0} };
		auto res = ranges::equal_range(x, x+6, 1, ranges::greater{}, &X::i);
		VERIFY(res.begin() == ranges::next(x, 2));
		VERIFY(res.end()   == ranges::next(x, 4));
	}
	{
		bksge::forward_list<int> x {};
		auto res = ranges::equal_range(x, 1);
		VERIFY(res.begin() == x.end());
		VERIFY(res.end()   == x.end());
	}
	return true;
}

#undef VERIFY

GTEST_TEST(AlgorithmTest, RangesEqualRangeTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	EXPECT_TRUE(test02());
}

}	// namespace ranges_equal_range_test

}	// namespace bksge_algorithm_test
