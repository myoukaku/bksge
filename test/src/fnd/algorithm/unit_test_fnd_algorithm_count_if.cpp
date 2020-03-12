/**
 *	@file	unit_test_fnd_algorithm_count_if.cpp
 *
 *	@brief	count_if のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/algorithm/count_if.hpp>
#include <bksge/fnd/iterator/begin.hpp>
#include <bksge/fnd/iterator/end.hpp>
#include <bksge/fnd/list.hpp>
#include <vector>
#include <gtest/gtest.h>
#include <array>
#include "constexpr_test.hpp"

namespace bksge_algorithm_test
{

namespace count_if_test
{

BKSGE_CONSTEXPR bool pred1(int x)
{
	return x == 1;
}

BKSGE_CONSTEXPR bool pred2(int x)
{
	return (x % 2) == 0;
}

struct pred3
{
	BKSGE_CONSTEXPR bool operator()(int x) const
	{
		return x >= 3;
	}
};

struct pred4
{
	BKSGE_CONSTEXPR bool operator()(int x) const
	{
		return x < 3;
	}
};

GTEST_TEST(AlgorithmTest, CountIfTest)
{
	{
		BKSGE_CONSTEXPR_OR_CONST int a[] {1, 3, 1, 2, 3, 1, 2, 2, 1};
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(4, bksge::count_if(bksge::begin(a), bksge::end(a), pred1));
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(3, bksge::count_if(bksge::begin(a), bksge::end(a), pred2));
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(2, bksge::count_if(bksge::begin(a), bksge::end(a), pred3()));
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(7, bksge::count_if(bksge::begin(a), bksge::end(a), pred4()));
	}
	{
		BKSGE_CONSTEXPR_OR_CONST std::array<int, 21> a{ { 3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5, 8, 9, 7, 9, 3, 2, 3, 8, 4, 6 } };
		BKSGE_CXX17_CONSTEXPR_EXPECT_EQ( 2, bksge::count_if(bksge::begin(a), bksge::end(a), pred1));
		BKSGE_CXX17_CONSTEXPR_EXPECT_EQ( 8, bksge::count_if(bksge::begin(a), bksge::end(a), pred2));
		BKSGE_CXX17_CONSTEXPR_EXPECT_EQ(17, bksge::count_if(bksge::begin(a), bksge::end(a), pred3()));
		BKSGE_CXX17_CONSTEXPR_EXPECT_EQ( 4, bksge::count_if(bksge::begin(a), bksge::end(a), pred4()));
	}
	{
		const std::vector<int> v{10, 20, 10, 30, 10, 20};
		EXPECT_EQ(0, bksge::count_if(bksge::begin(v), bksge::end(v), pred1));
		EXPECT_EQ(6, bksge::count_if(bksge::begin(v), bksge::end(v), pred2));
		EXPECT_EQ(6, bksge::count_if(bksge::begin(v), bksge::end(v), pred3()));
		EXPECT_EQ(0, bksge::count_if(bksge::begin(v), bksge::end(v), pred4()));
		EXPECT_EQ(2, bksge::count_if(bksge::begin(v), bksge::end(v), [](int x) { return x == 20;}));
		EXPECT_EQ(4, bksge::count_if(bksge::begin(v), bksge::end(v), [](int x) { return x != 20;}));
	}
	{
		const std::vector<int> v;
		EXPECT_EQ(0, bksge::count_if(bksge::begin(v), bksge::end(v), pred1));
		EXPECT_EQ(0, bksge::count_if(bksge::begin(v), bksge::end(v), pred2));
		EXPECT_EQ(0, bksge::count_if(bksge::begin(v), bksge::end(v), pred3()));
		EXPECT_EQ(0, bksge::count_if(bksge::begin(v), bksge::end(v), pred4()));
		EXPECT_EQ(0, bksge::count_if(bksge::begin(v), bksge::end(v), [](int x) { return x == 0;}));
		EXPECT_EQ(0, bksge::count_if(bksge::begin(v), bksge::end(v), [](int  ) { return true;}));
	}
	{
		const bksge::list<int> l{10, 20, 40, 40, 10};
		EXPECT_EQ(0, bksge::count_if(bksge::begin(l), bksge::end(l), pred1));
		EXPECT_EQ(5, bksge::count_if(bksge::begin(l), bksge::end(l), pred2));
		EXPECT_EQ(5, bksge::count_if(bksge::begin(l), bksge::end(l), pred3()));
		EXPECT_EQ(0, bksge::count_if(bksge::begin(l), bksge::end(l), pred4()));
		EXPECT_EQ(3, bksge::count_if(bksge::begin(l), bksge::end(l), [](int x) { return x >= 20;}));
		EXPECT_EQ(4, bksge::count_if(bksge::begin(l), bksge::end(l), [](int x) { return x != 20;}));
	}
	{
		const bksge::list<int> l;
		EXPECT_EQ(0, bksge::count_if(bksge::begin(l), bksge::end(l), pred1));
		EXPECT_EQ(0, bksge::count_if(bksge::begin(l), bksge::end(l), pred2));
		EXPECT_EQ(0, bksge::count_if(bksge::begin(l), bksge::end(l), pred3()));
		EXPECT_EQ(0, bksge::count_if(bksge::begin(l), bksge::end(l), pred4()));
		EXPECT_EQ(0, bksge::count_if(bksge::begin(l), bksge::end(l), [](int x) { return x >= 20;}));
		EXPECT_EQ(0, bksge::count_if(bksge::begin(l), bksge::end(l), [](int x) { return x == 0;}));
		EXPECT_EQ(0, bksge::count_if(bksge::begin(l), bksge::end(l), [](int  ) { return true;}));
	}
}

}	// namespace count_if_test

}	// namespace bksge_algorithm_test
