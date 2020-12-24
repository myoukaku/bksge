/**
 *	@file	unit_test_fnd_algorithm_inplace_merge.cpp
 *
 *	@brief	inplace_merge のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/algorithm/inplace_merge.hpp>
#include <bksge/fnd/functional/greater.hpp>
#include <bksge/fnd/iterator/begin.hpp>
#include <bksge/fnd/iterator/end.hpp>
#include <bksge/fnd/array.hpp>
#include <bksge/fnd/vector.hpp>
#include <gtest/gtest.h>

namespace bksge_algorithm_test
{

namespace inplace_merge_test
{

GTEST_TEST(AlgorithmTest, InplaceMergeTest)
{
	{
		int a[] { 1,4,5,  2,3,6 };

		bksge::inplace_merge(bksge::begin(a), bksge::begin(a) + 3, bksge::end(a));

		EXPECT_EQ(1, a[0]);
		EXPECT_EQ(2, a[1]);
		EXPECT_EQ(3, a[2]);
		EXPECT_EQ(4, a[3]);
		EXPECT_EQ(5, a[4]);
		EXPECT_EQ(6, a[5]);
	}
	{
		int a[] { 5,4,1,  6,3,2 };

		bksge::inplace_merge(bksge::begin(a), bksge::begin(a) + 3, bksge::end(a), bksge::greater<>());

		EXPECT_EQ(6, a[0]);
		EXPECT_EQ(5, a[1]);
		EXPECT_EQ(4, a[2]);
		EXPECT_EQ(3, a[3]);
		EXPECT_EQ(2, a[4]);
		EXPECT_EQ(1, a[5]);
	}
	{
		int a[] { 1, 2, 3 };

		bksge::inplace_merge(bksge::begin(a), bksge::begin(a), bksge::end(a));

		EXPECT_EQ(1, a[0]);
		EXPECT_EQ(2, a[1]);
		EXPECT_EQ(3, a[2]);
	}
	{
		int a[] { 3, 2, 1 };

		bksge::inplace_merge(bksge::begin(a), bksge::begin(a), bksge::end(a), bksge::greater<>());

		EXPECT_EQ(3, a[0]);
		EXPECT_EQ(2, a[1]);
		EXPECT_EQ(1, a[2]);
	}
	{
		bksge::array<int, 10> a {{ 1,2,5,7,  2,2,3,3,5,6 }};

		bksge::inplace_merge(bksge::begin(a), bksge::begin(a) + 4, bksge::end(a));

		EXPECT_EQ(1, a[0]);
		EXPECT_EQ(2, a[1]);
		EXPECT_EQ(2, a[2]);
		EXPECT_EQ(2, a[3]);
		EXPECT_EQ(3, a[4]);
		EXPECT_EQ(3, a[5]);
		EXPECT_EQ(5, a[6]);
		EXPECT_EQ(5, a[7]);
		EXPECT_EQ(6, a[8]);
		EXPECT_EQ(7, a[9]);
	}
	{
		bksge::array<int, 10> a {{ 7,5,2,1,  6,5,3,3,2,2 }};

		bksge::inplace_merge(bksge::begin(a), bksge::begin(a) + 4, bksge::end(a), bksge::greater<>());

		EXPECT_EQ(7, a[0]);
		EXPECT_EQ(6, a[1]);
		EXPECT_EQ(5, a[2]);
		EXPECT_EQ(5, a[3]);
		EXPECT_EQ(3, a[4]);
		EXPECT_EQ(3, a[5]);
		EXPECT_EQ(2, a[6]);
		EXPECT_EQ(2, a[7]);
		EXPECT_EQ(2, a[8]);
		EXPECT_EQ(1, a[9]);
	}
	{
		bksge::array<int, 2> a {{ 3, 1 }};

		bksge::inplace_merge(bksge::begin(a), bksge::begin(a) + 1, bksge::end(a));

		EXPECT_EQ(1, a[0]);
		EXPECT_EQ(3, a[1]);
	}
	{
		bksge::array<int, 2> a {{ 1, 3 }};

		bksge::inplace_merge(bksge::begin(a), bksge::begin(a) + 1, bksge::end(a), bksge::greater<>());

		EXPECT_EQ(3, a[0]);
		EXPECT_EQ(1, a[1]);
	}
	{
		bksge::vector<int> a { 1,2,4,5,6,  3 };

		bksge::inplace_merge(bksge::begin(a), bksge::begin(a) + 5, bksge::end(a));

		EXPECT_EQ(1, a[0]);
		EXPECT_EQ(2, a[1]);
		EXPECT_EQ(3, a[2]);
		EXPECT_EQ(4, a[3]);
		EXPECT_EQ(5, a[4]);
		EXPECT_EQ(6, a[5]);
	}
	{
		bksge::vector<int> a { 6,5,4,2,1,  3 };

		bksge::inplace_merge(bksge::begin(a), bksge::begin(a) + 5, bksge::end(a), bksge::greater<>());

		EXPECT_EQ(6, a[0]);
		EXPECT_EQ(5, a[1]);
		EXPECT_EQ(4, a[2]);
		EXPECT_EQ(3, a[3]);
		EXPECT_EQ(2, a[4]);
		EXPECT_EQ(1, a[5]);
	}
	{
		bksge::vector<int> a;

		bksge::inplace_merge(bksge::begin(a), bksge::begin(a), bksge::end(a));

		EXPECT_TRUE(a.empty());
	}
}

}	// namespace inplace_merge_test

}	// namespace bksge_algorithm_test
