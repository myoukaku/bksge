/**
 *	@file	unit_test_fnd_algorithm_ranges_partition_point.cpp
 *
 *	@brief	ranges::partition_point のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/algorithm/ranges/partition_point.hpp>
#include <bksge/fnd/iterator/ranges/next.hpp>
#include <bksge/fnd/vector.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace bksge_algorithm_test
{

namespace ranges_partition_point_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

struct LessEqual
{
	int k;
	constexpr bool operator()(int a) const
	{
		return a <= k;
	}
};

inline BKSGE_CXX14_CONSTEXPR bool test01()
{
	namespace ranges = bksge::ranges;
	for (int k = 1; k <= 7; k++)
	{
		int x[] = { 1,2,3,4,5,6,7 };
		test_range<int, forward_iterator_wrapper> r(x);
		auto pred = LessEqual{k};
		auto middle = ranges::partition_point(r, pred);
		VERIFY(middle == ranges::next(r.begin(), k));
	}
	{
		int x[] = { 1,2,3,4,5,6,7 };
		test_range<int, forward_iterator_wrapper> r(x);
		auto pred = LessEqual{0};
		auto middle = ranges::partition_point(r, pred);
		VERIFY(middle == r.begin());
	}
	{
		int x[] = { 1,2,3,4,5,6,7 };
		test_range<int, forward_iterator_wrapper> r(x);
		auto pred = LessEqual{8};
		auto middle = ranges::partition_point(r, pred);
		VERIFY(middle == ranges::next(r.begin(), 7));
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
		X x[] = { {1},{2},{3},{4},{5} };
		auto middle = ranges::partition_point(x, [](int a) { return a < 6; }, &X::i);
		VERIFY(middle == x+5);
	}
	{
		X x[] = { {1},{2},{3},{4},{5} };
		auto middle = ranges::partition_point(x, [](int a) { return a < 0; }, &X::i);
		VERIFY(middle == x+0);
	}
	{
		bksge::vector<int> x {};
		auto middle = ranges::partition_point(x, [](int a) { return a < 0; });
		VERIFY(middle == x.begin());
	}
	return true;
}

#undef VERIFY

GTEST_TEST(AlgorithmTest, RangesPartitionPointTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	EXPECT_TRUE(test02());
}

}	// namespace ranges_partition_point_test

}	// namespace bksge_algorithm_test
