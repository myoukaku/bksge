/**
 *	@file	unit_test_fnd_algorithm_minmax_element.cpp
 *
 *	@brief	minmax_element のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/algorithm/minmax_element.hpp>
#include <bksge/fnd/iterator/begin.hpp>
#include <bksge/fnd/iterator/end.hpp>
#include <bksge/fnd/iterator/next.hpp>
#include <bksge/fnd/cmath/abs.hpp>
#include <bksge/fnd/vector.hpp>
#include <list>
#include <array>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace bksge_algorithm_test
{

namespace minmax_element_test
{

BKSGE_CONSTEXPR bool pred1(int x, int y)
{
	return x > y;
}

struct pred2
{
	BKSGE_CONSTEXPR bool operator()(int x, int y) const
	{
		return bksge::abs(x) < bksge::abs(y);
	}
};

GTEST_TEST(AlgorithmTest, MinmaxElementTest)
{
	{
		BKSGE_STATIC_CONSTEXPR int a[] { 3, 1, -4, 1, 5, -9 };

		{
			BKSGE_CXX14_CONSTEXPR_OR_CONST auto ret = bksge::minmax_element(bksge::begin(a), bksge::end(a));
			BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(ret.first  == bksge::next(bksge::begin(a), 5));
			BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(ret.second == bksge::next(bksge::begin(a), 4));
		}
		{
			BKSGE_CXX14_CONSTEXPR_OR_CONST auto ret = bksge::minmax_element(bksge::begin(a), bksge::end(a), pred1);
			BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(ret.first  == bksge::next(bksge::begin(a), 4));
			BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(ret.second == bksge::next(bksge::begin(a), 5));
		}
		{
			BKSGE_CXX14_CONSTEXPR_OR_CONST auto ret = bksge::minmax_element(bksge::begin(a), bksge::end(a), pred2());
			BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(ret.first  == bksge::next(bksge::begin(a), 1));
			BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(ret.second == bksge::next(bksge::begin(a), 5));
		}
	}
	{
		BKSGE_STATIC_CONSTEXPR std::array<int, 8> a {{ 2, -6, 5, -3, -5, 8, 9, 7 }};

		{
			BKSGE_CXX17_CONSTEXPR_OR_CONST auto ret = bksge::minmax_element(bksge::begin(a), bksge::end(a));
			BKSGE_CXX17_CONSTEXPR_EXPECT_TRUE(ret.first  == bksge::next(bksge::begin(a), 1));
			BKSGE_CXX17_CONSTEXPR_EXPECT_TRUE(ret.second == bksge::next(bksge::begin(a), 6));
		}
		{
			BKSGE_CXX17_CONSTEXPR_OR_CONST auto ret = bksge::minmax_element(bksge::begin(a), bksge::end(a), pred1);
			BKSGE_CXX17_CONSTEXPR_EXPECT_TRUE(ret.first  == bksge::next(bksge::begin(a), 6));
			BKSGE_CXX17_CONSTEXPR_EXPECT_TRUE(ret.second == bksge::next(bksge::begin(a), 1));
		}
		{
			BKSGE_CXX17_CONSTEXPR_OR_CONST auto ret = bksge::minmax_element(bksge::begin(a), bksge::end(a), pred2());
			BKSGE_CXX17_CONSTEXPR_EXPECT_TRUE(ret.first  == bksge::next(bksge::begin(a), 0));
			BKSGE_CXX17_CONSTEXPR_EXPECT_TRUE(ret.second == bksge::next(bksge::begin(a), 6));
		}
	}
	{
		const bksge::vector<int> a { 9, 3, 2, 3, 8, 4, 6 };

		{
			auto ret = bksge::minmax_element(bksge::begin(a), bksge::end(a));
			EXPECT_TRUE(ret.first  == bksge::next(bksge::begin(a), 2));
			EXPECT_TRUE(ret.second == bksge::next(bksge::begin(a), 0));
		}
		{
			auto ret = bksge::minmax_element(bksge::begin(a), bksge::end(a), pred1);
			EXPECT_TRUE(ret.first  == bksge::next(bksge::begin(a), 0));
			EXPECT_TRUE(ret.second == bksge::next(bksge::begin(a), 2));
		}
		{
			auto ret = bksge::minmax_element(bksge::begin(a), bksge::end(a), [](int x, int y){return x > y; });
			EXPECT_TRUE(ret.first  == bksge::next(bksge::begin(a), 0));
			EXPECT_TRUE(ret.second == bksge::next(bksge::begin(a), 2));
		}
	}
	{
		const std::list<int> a { 1, -5, 7, 3, 7, -5 };

		{
			auto ret = bksge::minmax_element(bksge::begin(a), bksge::end(a));
			EXPECT_TRUE(ret.first  == bksge::next(bksge::begin(a), 1));
			EXPECT_TRUE(ret.second == bksge::next(bksge::begin(a), 4));
		}
		{
			auto ret = bksge::minmax_element(bksge::begin(a), bksge::end(a), pred2());
			EXPECT_TRUE(ret.first  == bksge::next(bksge::begin(a), 0));
			EXPECT_TRUE(ret.second == bksge::next(bksge::begin(a), 4));
		}
		{
			auto ret = bksge::minmax_element(bksge::begin(a), bksge::end(a), [](int x, int y){return x > y; });
			EXPECT_TRUE(ret.first  == bksge::next(bksge::begin(a), 2));
			EXPECT_TRUE(ret.second == bksge::next(bksge::begin(a), 5));
		}
	}
}

}	// namespace minmax_element_test

}	// namespace bksge_algorithm_test
