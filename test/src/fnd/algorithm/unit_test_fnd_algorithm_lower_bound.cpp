/**
 *	@file	unit_test_fnd_algorithm_lower_bound.cpp
 *
 *	@brief	lower_bound のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/algorithm/lower_bound.hpp>
#include <bksge/fnd/iterator/begin.hpp>
#include <bksge/fnd/iterator/end.hpp>
#include <bksge/fnd/iterator/next.hpp>
#include <gtest/gtest.h>
#include <array>
#include <list>
#include <bksge/fnd/vector.hpp>
#include "constexpr_test.hpp"

namespace bksge_algorithm_test
{

namespace lower_bound_test
{

BKSGE_CONSTEXPR bool pred1(int x, int y)
{
	return x < y;
}

struct pred2
{
	BKSGE_CONSTEXPR bool operator()(int x, int y) const
	{
		return x < y;
	}
};

GTEST_TEST(AlgorithmTest, LowerBoundTest)
{
#if 1//!(defined(_MSC_VER) && (_MSC_VER >= 1911))
	{
		BKSGE_STATIC_CONSTEXPR int a[] { 1,2,3,4,5 };
		BKSGE_CXX14_CONSTEXPR_OR_CONST auto ret = bksge::lower_bound(bksge::begin(a), bksge::end(a), 3);
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(ret == bksge::next(bksge::begin(a), 2));
	}
	{
		BKSGE_STATIC_CONSTEXPR int a[] { 1,1,2,2,2,3,3 };
		BKSGE_CXX14_CONSTEXPR_OR_CONST auto ret = bksge::lower_bound(bksge::begin(a), bksge::end(a), 2);
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(ret == bksge::next(bksge::begin(a), 2));
	}
	{
		BKSGE_STATIC_CONSTEXPR int a[] { 1,1,2,2,2,3,3 };
		BKSGE_CXX14_CONSTEXPR_OR_CONST auto ret = bksge::lower_bound(bksge::begin(a), bksge::end(a), 3);
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(ret == bksge::next(bksge::begin(a), 5));
	}
	{
		BKSGE_STATIC_CONSTEXPR int a[] { 1,3,5,6,7,9 };
		BKSGE_CXX14_CONSTEXPR_OR_CONST auto ret = bksge::lower_bound(bksge::begin(a), bksge::end(a), 7, pred1);
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(ret == bksge::next(bksge::begin(a), 4));
	}
#endif
	{
		BKSGE_STATIC_CONSTEXPR std::array<int, 5> a {{ 3,1,4,6,5 }};
		BKSGE_CXX17_CONSTEXPR_OR_CONST auto ret = bksge::lower_bound(bksge::begin(a), bksge::end(a), 4);
		BKSGE_CXX17_CONSTEXPR_EXPECT_TRUE(ret == bksge::next(bksge::begin(a), 2));
	}
	{
		BKSGE_STATIC_CONSTEXPR std::array<int, 3> a {{ 10,20,30 }};
		BKSGE_CXX17_CONSTEXPR_OR_CONST auto ret = bksge::lower_bound(bksge::begin(a), bksge::end(a), 10, pred2());
		BKSGE_CXX17_CONSTEXPR_EXPECT_TRUE(ret == bksge::next(bksge::begin(a), 0));
	}
	{
		const bksge::vector<int> a { 1,3,5,8,13,17,25 };
		auto ret = bksge::lower_bound(bksge::begin(a), bksge::end(a), 10);
		EXPECT_TRUE(ret == bksge::next(bksge::begin(a), 4));
	}
	{
		const bksge::vector<int> a { 1,3,5,8,13,17,25 };
		auto ret = bksge::lower_bound(bksge::begin(a), bksge::end(a), 1, [](int x, int y) { return x < y; });
		EXPECT_TRUE(ret == bksge::next(bksge::begin(a), 0));
	}
	{
		const std::list<int> a { 5,1,25,13,17 };
		auto ret = bksge::lower_bound(bksge::begin(a), bksge::end(a), 10);
		EXPECT_TRUE(ret == bksge::next(bksge::begin(a), 2));
	}
	{
		const bksge::vector<int> a;
		auto ret = bksge::lower_bound(bksge::begin(a), bksge::end(a), 0);
		EXPECT_TRUE(ret == bksge::next(bksge::begin(a), 0));
	}
	{
		const std::list<int> a;
		auto ret = bksge::lower_bound(bksge::begin(a), bksge::end(a), 0, [](int x, int y) { return x < y; });
		EXPECT_TRUE(ret == bksge::next(bksge::begin(a), 0));
	}
}

}	// namespace lower_bound_test

}	// namespace bksge_algorithm_test
