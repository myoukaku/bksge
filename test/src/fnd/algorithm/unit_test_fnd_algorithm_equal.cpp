/**
 *	@file	unit_test_fnd_algorithm_equal.cpp
 *
 *	@brief	equal のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/algorithm/equal.hpp>
#include <bksge/fnd/iterator/begin.hpp>
#include <bksge/fnd/iterator/end.hpp>
#include <list>
#include <vector>
#include <array>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace bksge_algorithm_test
{

namespace equal_test
{

GTEST_TEST(AlgorithmTest, EqualTest)
{
	BKSGE_CONSTEXPR_OR_CONST int a1[] {0,1,2};
	BKSGE_CONSTEXPR_OR_CONST int a2[] {0,1,2};
	BKSGE_CONSTEXPR_OR_CONST int a3[] {0,1,3};
	BKSGE_CONSTEXPR_OR_CONST int a4[] {2,1,2};
	BKSGE_CONSTEXPR_OR_CONST int a5[] {0,1};
	BKSGE_CONSTEXPR_OR_CONST int a6[] {0,1,2,3};

	BKSGE_CONSTEXPR_OR_CONST std::array<float, 3> a7{{0, 1, 2}};
	BKSGE_CONSTEXPR_OR_CONST std::array<float, 3> a8{{1, 1, 2}};
	BKSGE_CONSTEXPR_OR_CONST std::array<float, 2> a9{{0, 1}};
	BKSGE_CONSTEXPR_OR_CONST std::array<float, 4> a10{{0, 1, 2, 3}};

	const std::vector<int> v1 {0,1,2};
	const std::vector<int> v2 {0,1,2,3};
	const std::vector<int> v3 {0,1,2,3};

	const std::list<int> l1 {0,1,2};
	const std::list<int> l2 {0,1,2,3};
	const std::list<int> l3 {0,1,4,3};

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE (bksge::equal(bksge::begin(a1), bksge::end(a1), bksge::begin(a1), bksge::end(a1)));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE (bksge::equal(bksge::begin(a1), bksge::end(a1), bksge::begin(a2), bksge::end(a2)));
	BKSGE_CXX14_CONSTEXPR_EXPECT_FALSE(bksge::equal(bksge::begin(a1), bksge::end(a1), bksge::begin(a3), bksge::end(a3)));
	BKSGE_CXX14_CONSTEXPR_EXPECT_FALSE(bksge::equal(bksge::begin(a1), bksge::end(a1), bksge::begin(a4), bksge::end(a4)));
	BKSGE_CXX14_CONSTEXPR_EXPECT_FALSE(bksge::equal(bksge::begin(a1), bksge::end(a1), bksge::begin(a5), bksge::end(a5)));
	BKSGE_CXX14_CONSTEXPR_EXPECT_FALSE(bksge::equal(bksge::begin(a1), bksge::end(a1), bksge::begin(a6), bksge::end(a6)));
	BKSGE_CXX17_CONSTEXPR_EXPECT_TRUE (bksge::equal(bksge::begin(a1), bksge::end(a1), bksge::begin(a7), bksge::end(a7)));
	BKSGE_CXX17_CONSTEXPR_EXPECT_FALSE(bksge::equal(bksge::begin(a1), bksge::end(a1), bksge::begin(a8), bksge::end(a8)));
	BKSGE_CXX17_CONSTEXPR_EXPECT_FALSE(bksge::equal(bksge::begin(a1), bksge::end(a1), bksge::begin(a9), bksge::end(a9)));
	BKSGE_CXX17_CONSTEXPR_EXPECT_FALSE(bksge::equal(bksge::begin(a1), bksge::end(a1), bksge::begin(a10), bksge::end(a10)));

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE (bksge::equal(bksge::begin(a1), bksge::end(a1), bksge::begin(a1)));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE (bksge::equal(bksge::begin(a1), bksge::end(a1), bksge::begin(a2)));
	BKSGE_CXX14_CONSTEXPR_EXPECT_FALSE(bksge::equal(bksge::begin(a1), bksge::end(a1), bksge::begin(a3)));
	BKSGE_CXX14_CONSTEXPR_EXPECT_FALSE(bksge::equal(bksge::begin(a1), bksge::end(a1), bksge::begin(a4)));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_FALSE(bksge::equal(bksge::begin(a1), bksge::end(a1), bksge::begin(a5)));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE (bksge::equal(bksge::begin(a1), bksge::end(a1), bksge::begin(a6)));
	BKSGE_CXX17_CONSTEXPR_EXPECT_TRUE (bksge::equal(bksge::begin(a1), bksge::end(a1), bksge::begin(a7)));
	BKSGE_CXX17_CONSTEXPR_EXPECT_FALSE(bksge::equal(bksge::begin(a1), bksge::end(a1), bksge::begin(a8)));
//	BKSGE_CXX17_CONSTEXPR_EXPECT_FALSE(bksge::equal(bksge::begin(a1), bksge::end(a1), bksge::begin(a9)));
	BKSGE_CXX17_CONSTEXPR_EXPECT_TRUE (bksge::equal(bksge::begin(a1), bksge::end(a1), bksge::begin(a10)));

	EXPECT_TRUE (bksge::equal(bksge::begin(a1), bksge::end(a1), bksge::begin(v1), bksge::end(v1)));
	EXPECT_FALSE(bksge::equal(bksge::begin(a1), bksge::end(a1), bksge::begin(v2), bksge::end(v2)));
	EXPECT_TRUE (bksge::equal(bksge::begin(v2), bksge::end(v2), bksge::begin(v3), bksge::end(v3)));
	EXPECT_TRUE (bksge::equal(bksge::begin(a1), bksge::end(a1), bksge::begin(l1), bksge::end(l1)));
	EXPECT_FALSE(bksge::equal(bksge::begin(a1), bksge::end(a1), bksge::begin(l2), bksge::end(l2)));
	EXPECT_TRUE (bksge::equal(bksge::begin(l1), bksge::end(l1), bksge::begin(l1), bksge::end(l1)));
	EXPECT_FALSE(bksge::equal(bksge::begin(l1), bksge::end(l1), bksge::begin(l2), bksge::end(l2)));
	EXPECT_FALSE(bksge::equal(bksge::begin(l2), bksge::end(l2), bksge::begin(l1), bksge::end(l1)));
	EXPECT_FALSE(bksge::equal(bksge::begin(l2), bksge::end(l2), bksge::begin(l3), bksge::end(l3)));
	EXPECT_TRUE (bksge::equal(bksge::begin(v1), bksge::end(v1), bksge::begin(l1), bksge::end(l1)));
	EXPECT_FALSE(bksge::equal(bksge::begin(v1), bksge::end(v1), bksge::begin(l2), bksge::end(l2)));
	EXPECT_FALSE(bksge::equal(bksge::begin(v2), bksge::end(v2), bksge::begin(l1), bksge::end(l1)));
	EXPECT_FALSE(bksge::equal(bksge::begin(v3), bksge::end(v3), bksge::begin(l3), bksge::end(l3)));

	EXPECT_TRUE (bksge::equal(bksge::begin(a1), bksge::end(a1), bksge::begin(v1)));
	EXPECT_TRUE (bksge::equal(bksge::begin(a1), bksge::end(a1), bksge::begin(v2)));
	EXPECT_TRUE (bksge::equal(bksge::begin(v2), bksge::end(v2), bksge::begin(v3)));
	EXPECT_TRUE (bksge::equal(bksge::begin(a1), bksge::end(a1), bksge::begin(l1)));
	EXPECT_TRUE (bksge::equal(bksge::begin(a1), bksge::end(a1), bksge::begin(l2)));
	EXPECT_TRUE (bksge::equal(bksge::begin(l1), bksge::end(l1), bksge::begin(l1)));
	EXPECT_TRUE (bksge::equal(bksge::begin(l1), bksge::end(l1), bksge::begin(l2)));
//	EXPECT_TRUE (bksge::equal(bksge::begin(l2), bksge::end(l2), bksge::begin(l1)));
	EXPECT_FALSE(bksge::equal(bksge::begin(l2), bksge::end(l2), bksge::begin(l3)));
	EXPECT_TRUE (bksge::equal(bksge::begin(v1), bksge::end(v1), bksge::begin(l1)));
	EXPECT_TRUE (bksge::equal(bksge::begin(v1), bksge::end(v1), bksge::begin(l2)));
//	EXPECT_TRUE (bksge::equal(bksge::begin(v2), bksge::end(v2), bksge::begin(l1)));
	EXPECT_FALSE(bksge::equal(bksge::begin(v3), bksge::end(v3), bksge::begin(l3)));
}

}	// namespace equal_test

}	// namespace bksge_algorithm_test
