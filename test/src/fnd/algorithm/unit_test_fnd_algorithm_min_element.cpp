/**
 *	@file	unit_test_fnd_algorithm_min_element.cpp
 *
 *	@brief	min_element のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/algorithm/min_element.hpp>
#include <bksge/fnd/iterator/begin.hpp>
#include <bksge/fnd/iterator/end.hpp>
#include <bksge/fnd/iterator/next.hpp>
#include <bksge/fnd/cmath/abs.hpp>
#include <bksge/fnd/array.hpp>
#include <bksge/fnd/list.hpp>
#include <bksge/fnd/vector.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace bksge_algorithm_test
{

namespace min_element_test
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

GTEST_TEST(AlgorithmTest, MinElementTest)
{
	{
		BKSGE_STATIC_CONSTEXPR int a[] { 3, 1, -4, 1, 5, -9 };

		{
			BKSGE_CXX14_CONSTEXPR_OR_CONST auto ret = bksge::min_element(bksge::begin(a), bksge::end(a));
			BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(ret == bksge::next(bksge::begin(a), 5));
		}
		{
			BKSGE_CXX14_CONSTEXPR_OR_CONST auto ret = bksge::min_element(bksge::begin(a), bksge::end(a), pred1);
			BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(ret == bksge::next(bksge::begin(a), 4));
		}
		{
			BKSGE_CXX14_CONSTEXPR_OR_CONST auto ret = bksge::min_element(bksge::begin(a), bksge::end(a), pred2());
			BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(ret == bksge::next(bksge::begin(a), 1));
		}
	}
	{
		BKSGE_STATIC_CONSTEXPR bksge::array<int, 8> a {{ 2, -6, 5, -3, -5, 8, 9, 7 }};

		{
			BKSGE_CXX17_CONSTEXPR_OR_CONST auto ret = bksge::min_element(bksge::begin(a), bksge::end(a));
			BKSGE_CXX17_CONSTEXPR_EXPECT_TRUE(ret == bksge::next(bksge::begin(a), 1));
		}
		{
			BKSGE_CXX17_CONSTEXPR_OR_CONST auto ret = bksge::min_element(bksge::begin(a), bksge::end(a), pred1);
			BKSGE_CXX17_CONSTEXPR_EXPECT_TRUE(ret == bksge::next(bksge::begin(a), 6));
		}
		{
			BKSGE_CXX17_CONSTEXPR_OR_CONST auto ret = bksge::min_element(bksge::begin(a), bksge::end(a), pred2());
			BKSGE_CXX17_CONSTEXPR_EXPECT_TRUE(ret == bksge::next(bksge::begin(a), 0));
		}
	}
	{
		const bksge::vector<int> a { 9, 3, 2, 3, 8, 4, 6 };

		{
			auto ret = bksge::min_element(bksge::begin(a), bksge::end(a));
			EXPECT_TRUE(ret == bksge::next(bksge::begin(a), 2));
		}
		{
			auto ret = bksge::min_element(bksge::begin(a), bksge::end(a), pred1);
			EXPECT_TRUE(ret == bksge::next(bksge::begin(a), 0));
		}
		{
			auto ret = bksge::min_element(bksge::begin(a), bksge::end(a), [](int x, int y){return x > y; });
			EXPECT_TRUE(ret == bksge::next(bksge::begin(a), 0));
		}
	}
	{
		const bksge::list<int> a { 1, -5, 7, 3, 7, -5 };

		{
			auto ret = bksge::min_element(bksge::begin(a), bksge::end(a));
			EXPECT_TRUE(ret == bksge::next(bksge::begin(a), 1));
		}
		{
			auto ret = bksge::min_element(bksge::begin(a), bksge::end(a), pred2());
			EXPECT_TRUE(ret == bksge::next(bksge::begin(a), 0));
		}
		{
			auto ret = bksge::min_element(bksge::begin(a), bksge::end(a), [](int x, int y){return x > y; });
			EXPECT_TRUE(ret == bksge::next(bksge::begin(a), 2));
		}
	}
}

}	// namespace min_element_test

}	// namespace bksge_algorithm_test
