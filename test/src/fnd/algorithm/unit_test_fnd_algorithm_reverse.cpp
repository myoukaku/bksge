/**
 *	@file	unit_test_fnd_algorithm_reverse.cpp
 *
 *	@brief	reverse のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/algorithm/reverse.hpp>
#include <bksge/fnd/iterator/begin.hpp>
#include <bksge/fnd/iterator/end.hpp>
#include <bksge/fnd/array.hpp>
#include <bksge/fnd/list.hpp>
#include <bksge/fnd/vector.hpp>
#include <gtest/gtest.h>

namespace bksge_algorithm_test
{

namespace reverse_test
{

GTEST_TEST(AlgorithmTest, ReverseTest)
{
	{
		int a[] { 1,2,3 };
		bksge::reverse(bksge::begin(a), bksge::end(a));
		EXPECT_EQ(3, a[0]);
		EXPECT_EQ(2, a[1]);
		EXPECT_EQ(1, a[2]);
	}
	{
		int a[] { 4 };
		bksge::reverse(bksge::begin(a), bksge::end(a));
		EXPECT_EQ(4, a[0]);
	}
	{
		bksge::array<int, 4> a {{ 1,2,3,4 }};
		bksge::reverse(bksge::begin(a), bksge::end(a));
		EXPECT_EQ(4, a[0]);
		EXPECT_EQ(3, a[1]);
		EXPECT_EQ(2, a[2]);
		EXPECT_EQ(1, a[3]);
	}
	{
		bksge::vector<int> a { 1,2,3,4,5 };
		bksge::reverse(bksge::begin(a), bksge::end(a));
		EXPECT_EQ(5, a[0]);
		EXPECT_EQ(4, a[1]);
		EXPECT_EQ(3, a[2]);
		EXPECT_EQ(2, a[3]);
		EXPECT_EQ(1, a[4]);
	}
	{
		bksge::vector<int> a;
		bksge::reverse(bksge::begin(a), bksge::end(a));
		EXPECT_TRUE(a.empty());
	}
	{
		bksge::list<int> a { 1,2 };
		bksge::reverse(bksge::begin(a), bksge::end(a));
		auto it = a.begin();
		EXPECT_EQ(2, *it++);
		EXPECT_EQ(1, *it++);
		EXPECT_TRUE(it == a.end());
	}
	{
		bksge::list<int> a;
		bksge::reverse(bksge::begin(a), bksge::end(a));
		EXPECT_TRUE(a.empty());
	}
}

}	// namespace reverse_test

}	// namespace bksge_algorithm_test
