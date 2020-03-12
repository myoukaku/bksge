/**
 *	@file	unit_test_fnd_algorithm_copy_backward.cpp
 *
 *	@brief	copy_backward のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/algorithm/copy_backward.hpp>
#include <bksge/fnd/iterator/begin.hpp>
#include <bksge/fnd/iterator/end.hpp>
#include <bksge/fnd/iterator/next.hpp>
#include <list>
#include <vector>
#include <array>
#include <gtest/gtest.h>

namespace bksge_algorithm_test
{

namespace copy_backward_test
{

GTEST_TEST(AlgorithmTest, CopyBackwardTest)
{
	{
		const int a1[] { 1, 2, 3 };
		int a2[3];

		auto it = bksge::copy_backward(bksge::begin(a1), bksge::end(a1), bksge::end(a2));

		EXPECT_EQ(1, a2[0]);
		EXPECT_EQ(2, a2[1]);
		EXPECT_EQ(3, a2[2]);
		EXPECT_TRUE(it == bksge::begin(a2));
	}
	{
		const int a1[] { 1, 2, 3 };
		std::array<int, 5> a2{{}};

		auto it = bksge::copy_backward(bksge::begin(a1), bksge::end(a1), bksge::end(a2));

		EXPECT_EQ(0, a2[0]);
		EXPECT_EQ(0, a2[1]);
		EXPECT_EQ(1, a2[2]);
		EXPECT_EQ(2, a2[3]);
		EXPECT_EQ(3, a2[4]);
		EXPECT_TRUE(it == bksge::begin(a2) + 2);
	}
	{
		std::vector<int> v{ 1, 2, 3, 4, 5 };

		auto it = bksge::copy_backward(bksge::begin(v), bksge::begin(v) + 3, bksge::end(v));

		EXPECT_EQ(1, v[0]);
		EXPECT_EQ(2, v[1]);
		EXPECT_EQ(1, v[2]);
		EXPECT_EQ(2, v[3]);
		EXPECT_EQ(3, v[4]);
		EXPECT_TRUE(it == bksge::begin(v) + 2);
	}
	{
		const std::vector<int> v{ 1, 2, 3, 4, 5 };
		std::list<int> l{ 6, 7, 8, 9 };

		{
			auto it = bksge::copy_backward(bksge::begin(v), bksge::begin(v) + 2, bksge::end(l));
			EXPECT_TRUE(it == bksge::next(l.begin(), 2));
		}
		{
			auto it = l.begin();
			EXPECT_EQ(6, *it++);
			EXPECT_EQ(7, *it++);
			EXPECT_EQ(1, *it++);
			EXPECT_EQ(2, *it++);
			EXPECT_TRUE(it == l.end());
		}
	}
}

}	// namespace copy_backward_test

}	// namespace bksge_algorithm_test
