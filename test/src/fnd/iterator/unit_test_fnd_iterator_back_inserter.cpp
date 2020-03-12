/**
 *	@file	unit_test_fnd_iterator_back_inserter.cpp
 *
 *	@brief	back_inserter のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/iterator/back_inserter.hpp>
#include <bksge/fnd/algorithm/copy.hpp>
#include <vector>
#include <bksge/fnd/list.hpp>
#include <gtest/gtest.h>

GTEST_TEST(IteratorTest, BackInserterTest)
{
	{
		std::vector<int> src = {1, 2, 3};
		std::vector<int> dst;

		bksge::copy(src.begin(), src.end(), bksge::back_inserter(dst));

		EXPECT_EQ(3u, dst.size());
		EXPECT_EQ(1, dst[0]);
		EXPECT_EQ(2, dst[1]);
		EXPECT_EQ(3, dst[2]);
	}
	{
		const int src[] = {10, 20, 30, 40, 50};
		bksge::list<int> dst;

		bksge::copy(src, src + 5, bksge::back_inserter(dst));

		EXPECT_EQ(5u, dst.size());
		auto it = dst.begin();
		EXPECT_EQ(10, *it++);
		EXPECT_EQ(20, *it++);
		EXPECT_EQ(30, *it++);
		EXPECT_EQ(40, *it++);
		EXPECT_EQ(50, *it++);
	}
}
