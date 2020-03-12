/**
 *	@file	unit_test_fnd_algorithm_none_of.cpp
 *
 *	@brief	none_of のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/algorithm/none_of.hpp>
#include <bksge/fnd/iterator/begin.hpp>
#include <bksge/fnd/iterator/end.hpp>
#include <list>
#include <vector>
#include <array>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace bksge_algorithm_test
{

namespace none_of_test
{

BKSGE_CONSTEXPR bool pred1(int x)
{
	return x == 1;
}
BKSGE_CONSTEXPR bool pred2(int x)
{
	return x < 0;
}

struct pred3
{
	BKSGE_CONSTEXPR bool operator()(int x) const
	{
		return x % 2 == 0;
	}
};

struct pred4
{
	BKSGE_CONSTEXPR bool operator()(int x) const
	{
		return x > 3;
	}
};

GTEST_TEST(AlgorithmTest, NoneOfTest)
{
	BKSGE_STATIC_CONSTEXPR int a1[] {0,1,2};
	BKSGE_CXX14_CONSTEXPR_EXPECT_FALSE(bksge::none_of(bksge::begin(a1), bksge::end(a1), pred1));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE (bksge::none_of(bksge::begin(a1), bksge::end(a1), pred2));
	BKSGE_CXX14_CONSTEXPR_EXPECT_FALSE(bksge::none_of(bksge::begin(a1), bksge::end(a1), pred3()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE (bksge::none_of(bksge::begin(a1), bksge::end(a1), pred4()));

	BKSGE_STATIC_CONSTEXPR std::array<int, 8> a2{{2, 4, 4, 8, 6, 4, 0, 6}};
	BKSGE_CXX17_CONSTEXPR_EXPECT_TRUE (bksge::none_of(bksge::begin(a2), bksge::end(a2), pred1));
	BKSGE_CXX17_CONSTEXPR_EXPECT_TRUE (bksge::none_of(bksge::begin(a2), bksge::end(a2), pred2));
	BKSGE_CXX17_CONSTEXPR_EXPECT_FALSE(bksge::none_of(bksge::begin(a2), bksge::end(a2), pred3()));
	BKSGE_CXX17_CONSTEXPR_EXPECT_FALSE(bksge::none_of(bksge::begin(a2), bksge::end(a2), pred4()));

	const std::vector<int> v1 {7, 8, 9};
	EXPECT_TRUE (bksge::none_of(bksge::begin(v1), bksge::end(v1), pred1));
	EXPECT_TRUE (bksge::none_of(bksge::begin(v1), bksge::end(v1), pred2));
	EXPECT_FALSE(bksge::none_of(bksge::begin(v1), bksge::end(v1), pred4()));
	EXPECT_FALSE(bksge::none_of(bksge::begin(v1), bksge::end(v1), [](int x) { return x == 7; }));
	EXPECT_FALSE(bksge::none_of(bksge::begin(v1), bksge::end(v1), [](int x) { return x == 9; }));
	EXPECT_TRUE (bksge::none_of(bksge::begin(v1), bksge::end(v1), [](int x) { return x == 10; }));

	const std::vector<int> v2;
	EXPECT_TRUE (bksge::none_of(bksge::begin(v2), bksge::end(v2), pred1));
	EXPECT_TRUE (bksge::none_of(bksge::begin(v2), bksge::end(v2), [](int) { return true; }));
	EXPECT_TRUE (bksge::none_of(bksge::begin(v2), bksge::end(v2), [](int) { return false; }));

	const std::list<int> l1 {0,1,2};
	EXPECT_FALSE(bksge::none_of(bksge::begin(l1), bksge::end(l1), pred1));
	EXPECT_TRUE (bksge::none_of(bksge::begin(l1), bksge::end(l1), pred2));
	EXPECT_FALSE(bksge::none_of(bksge::begin(l1), bksge::end(l1), pred3()));
	EXPECT_TRUE (bksge::none_of(bksge::begin(l1), bksge::end(l1), pred4()));
	EXPECT_FALSE(bksge::none_of(bksge::begin(l1), bksge::end(l1), [](int x) { return x == 0; }));
	EXPECT_TRUE (bksge::none_of(bksge::begin(l1), bksge::end(l1), [](int x) { return x == 3; }));
}

}	// namespace none_of_test

}	// namespace bksge_algorithm_test
