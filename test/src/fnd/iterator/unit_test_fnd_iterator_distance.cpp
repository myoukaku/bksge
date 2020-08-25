/**
 *	@file	unit_test_fnd_iterator_distance.cpp
 *
 *	@brief	distance のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/iterator/distance.hpp>
#include <bksge/fnd/iterator/begin.hpp>
#include <bksge/fnd/iterator/end.hpp>
#include <bksge/fnd/config.hpp>
#include <vector>
#include <list>
#include <array>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace bksge_iterator_test
{

namespace distance_test
{

GTEST_TEST(IteratorTest, DistanceTest)
{
	{
		int a[] = {0,1,2};
		EXPECT_EQ(3, bksge::distance(bksge::begin(a), bksge::end(a)));
	}
	{
		const int a[] = {0,1,2};
		EXPECT_EQ(3, bksge::distance(bksge::begin(a), bksge::end(a)));
	}
	{
		BKSGE_CONSTEXPR int a[] = {0,1,2};
		BKSGE_CXX14_CONSTEXPR auto d = bksge::distance(bksge::begin(a), bksge::end(a));
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(3, d);
	}
	{
		std::vector<float> v {3,1,4,1,5};
		EXPECT_EQ(5, bksge::distance(bksge::begin(v), bksge::end(v)));
	}
	{
		const std::vector<float> v {3,1,4,1,5};
		EXPECT_EQ(5, bksge::distance(bksge::begin(v), bksge::end(v)));
	}
	{
		std::list<int> l {2, 3, 4, 5};
		EXPECT_EQ(4, bksge::distance(bksge::begin(l), bksge::end(l)));
	}
	{
		const std::list<int> l {2, 3, 4, 5};
		EXPECT_EQ(4, bksge::distance(bksge::begin(l), bksge::end(l)));
	}
	{
		std::array<float, 2> a{{1, 2}};
		EXPECT_EQ(2, bksge::distance(bksge::begin(a), bksge::end(a)));
	}
	{
		const std::array<float, 3> a{{1, 2, 3}};
		EXPECT_EQ(3, bksge::distance(bksge::begin(a), bksge::end(a)));
	}
	{
		BKSGE_CONSTEXPR std::array<float, 4> a{{1, 2, 3, 4}};
		BKSGE_CXX17_CONSTEXPR auto d = bksge::distance(bksge::begin(a), bksge::end(a));
		BKSGE_CXX17_CONSTEXPR_EXPECT_EQ(4, d);
	}
}

}	// namespace distance_test

}	// namespace bksge_iterator_test
