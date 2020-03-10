/**
 *	@file	unit_test_fnd_algorithm_equal_range.cpp
 *
 *	@brief	equal_range のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/algorithm/equal_range.hpp>
#include <bksge/fnd/iterator/begin.hpp>
#include <bksge/fnd/iterator/end.hpp>
#include <bksge/fnd/iterator/next.hpp>
#include <bksge/fnd/list.hpp>
#include <bksge/fnd/vector.hpp>
#include <gtest/gtest.h>
#include <array>
#include "constexpr_test.hpp"

namespace bksge_algorithm_test
{

namespace equal_range_test
{

BKSGE_CONSTEXPR bool pred1(int x, int y)
{
	return x < y;
}

struct pred2
{
	BKSGE_CONSTEXPR bool operator()(int x, int y) const
	{
		return x > y;
	}
};

GTEST_TEST(AlgorithmTest, EqualRangeTest)
{
	{
		const int a[] { 1,2,2,3,3,3,4,4,5,5,5 };
		{
			const auto ret = bksge::equal_range(bksge::begin(a), bksge::end(a), 1);
			EXPECT_TRUE(ret.first  == bksge::next(bksge::begin(a), 0));
			EXPECT_TRUE(ret.second == bksge::next(bksge::begin(a), 1));
		}
		{
			const auto ret = bksge::equal_range(bksge::begin(a), bksge::end(a), 3, pred1);
			EXPECT_TRUE(ret.first  == bksge::next(bksge::begin(a), 3));
			EXPECT_TRUE(ret.second == bksge::next(bksge::begin(a), 6));
		}
		{
			const auto ret = bksge::equal_range(bksge::begin(a), bksge::end(a), 5);
			EXPECT_TRUE(ret.first  == bksge::next(bksge::begin(a), 8));
			EXPECT_TRUE(ret.second == bksge::next(bksge::begin(a), 11));
		}
		{
			const auto ret = bksge::equal_range(bksge::begin(a), bksge::end(a), 0);
			EXPECT_TRUE(ret.first  == bksge::next(bksge::begin(a), 0));
			EXPECT_TRUE(ret.second == bksge::next(bksge::begin(a), 0));
		}
		{
			const auto ret = bksge::equal_range(bksge::begin(a), bksge::end(a), 10);
			EXPECT_TRUE(ret.first  == bksge::end(a));
			EXPECT_TRUE(ret.second == bksge::end(a));
		}
	}
	{
		BKSGE_STATIC_CONSTEXPR std::array<int, 9> a {{ 5,5,4,2,2,2,1,0,0 }};
		{
			BKSGE_CXX17_CONSTEXPR_OR_CONST auto ret = bksge::equal_range(bksge::begin(a), bksge::end(a), 2, pred2());
			BKSGE_CXX17_CONSTEXPR_EXPECT_TRUE(ret.first  == bksge::next(bksge::begin(a), 3));
			BKSGE_CXX17_CONSTEXPR_EXPECT_TRUE(ret.second == bksge::next(bksge::begin(a), 6));
		}
		{
			BKSGE_CXX17_CONSTEXPR_OR_CONST auto ret = bksge::equal_range(bksge::begin(a), bksge::end(a), -1, pred2());
			BKSGE_CXX17_CONSTEXPR_EXPECT_TRUE(ret.first  == bksge::end(a));
			BKSGE_CXX17_CONSTEXPR_EXPECT_TRUE(ret.second == bksge::end(a));
		}
		{
			BKSGE_CXX17_CONSTEXPR_OR_CONST auto ret = bksge::equal_range(bksge::begin(a), bksge::end(a), 6, pred2());
			BKSGE_CXX17_CONSTEXPR_EXPECT_TRUE(ret.first  == bksge::begin(a));
			BKSGE_CXX17_CONSTEXPR_EXPECT_TRUE(ret.second == bksge::begin(a));
		}
	}
	{
		// ソートされていなくても区分化されていれば良い
		const bksge::vector<int> a { 2,1,2,3,3,4,7,5,5 };
		{
			auto ret = bksge::equal_range(bksge::begin(a), bksge::end(a), 3);
			EXPECT_TRUE(ret.first  == bksge::next(bksge::begin(a), 3));
			EXPECT_TRUE(ret.second == bksge::next(bksge::begin(a), 5));
		}
	}
	{
		const bksge::list<int> a { 8, 6, 6, 7, 5, 5, 5, 3, 4, 2, 2 };
		{
			auto ret = bksge::equal_range(bksge::begin(a), bksge::end(a), 5, [] (int x, int y) { return x > y; });
			EXPECT_TRUE(ret.first  == bksge::next(bksge::begin(a), 4));
			EXPECT_TRUE(ret.second == bksge::next(bksge::begin(a), 7));
		}
	}
	{
		const bksge::vector<int> a;
		{
			auto ret = bksge::equal_range(bksge::begin(a), bksge::end(a), 0);
			EXPECT_TRUE(ret.first  == bksge::begin(a));
			EXPECT_TRUE(ret.second == bksge::end(a));
		}
	}
	{
		const bksge::list<int> a;
		{
			auto ret = bksge::equal_range(bksge::begin(a), bksge::end(a), 0, pred1);
			EXPECT_TRUE(ret.first  == bksge::begin(a));
			EXPECT_TRUE(ret.second == bksge::end(a));
		}
	}
}

}	// namespace equal_range_test

}	// namespace bksge_algorithm_test
