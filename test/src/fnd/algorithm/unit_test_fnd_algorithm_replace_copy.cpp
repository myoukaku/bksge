/**
 *	@file	unit_test_fnd_algorithm_replace_copy.cpp
 *
 *	@brief	replace_copy のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/algorithm/replace_copy.hpp>
#include <bksge/fnd/iterator/begin.hpp>
#include <bksge/fnd/iterator/end.hpp>
#include <bksge/fnd/iterator/next.hpp>
#include <bksge/fnd/array.hpp>
#include <bksge/fnd/list.hpp>
#include <bksge/fnd/vector.hpp>
#include <iterator>	// back_inserter
#include <gtest/gtest.h>

namespace bksge_algorithm_test
{

namespace replace_copy_test
{

GTEST_TEST(AlgorithmTest, ReplaceCopyTest)
{
	{
		const int a[] { 3,1,2,1,2 };
		int b[7]{};
		auto ret = bksge::replace_copy(bksge::begin(a), bksge::end(a), bksge::begin(b), 1, 4);
		EXPECT_TRUE(ret == bksge::next(bksge::begin(b), 5));
		EXPECT_EQ(3, b[0]);
		EXPECT_EQ(4, b[1]);
		EXPECT_EQ(2, b[2]);
		EXPECT_EQ(4, b[3]);
		EXPECT_EQ(2, b[4]);
		EXPECT_EQ(0, b[5]);
		EXPECT_EQ(0, b[6]);
	}
	{
		const int a[] { 3,1,2,1,2 };
		bksge::vector<int> b;
		auto ret = bksge::replace_copy(bksge::begin(a), bksge::end(a), std::back_inserter(b), 2, 5);
		(void)ret;
		EXPECT_EQ(5u, b.size());
		EXPECT_EQ(3, b[0]);
		EXPECT_EQ(1, b[1]);
		EXPECT_EQ(5, b[2]);
		EXPECT_EQ(1, b[3]);
		EXPECT_EQ(5, b[4]);
	}
	{
		const bksge::array<int, 6> a {{ 3,1,2,1,2,3 }};
		bksge::list<int> b;
		auto ret = bksge::replace_copy(bksge::begin(a), bksge::end(a), std::back_inserter(b), 3, 5);
		(void)ret;
		auto it = b.begin();
		EXPECT_EQ(5, *it++);
		EXPECT_EQ(1, *it++);
		EXPECT_EQ(2, *it++);
		EXPECT_EQ(1, *it++);
		EXPECT_EQ(2, *it++);
		EXPECT_EQ(5, *it++);
		EXPECT_TRUE(it == b.end());
	}
	{
		const bksge::vector<int> a { 3,1,4,1,5,9,2 };
		bksge::array<int, 7> b{{}};
		auto ret = bksge::replace_copy(bksge::begin(a), bksge::end(a), bksge::begin(b), 2, 0);
		EXPECT_TRUE(ret == bksge::next(bksge::begin(b), 7));
		EXPECT_EQ(3, b[0]);
		EXPECT_EQ(1, b[1]);
		EXPECT_EQ(4, b[2]);
		EXPECT_EQ(1, b[3]);
		EXPECT_EQ(5, b[4]);
		EXPECT_EQ(9, b[5]);
		EXPECT_EQ(0, b[6]);
	}
	{
		bksge::vector<int> a;
		int b[5] {};
		auto ret = bksge::replace_copy(bksge::begin(a), bksge::end(a), bksge::begin(b), 0, 10);
		EXPECT_TRUE(ret == bksge::next(bksge::begin(b), 0));
		EXPECT_EQ(0, b[0]);
		EXPECT_EQ(0, b[1]);
		EXPECT_EQ(0, b[2]);
		EXPECT_EQ(0, b[3]);
		EXPECT_EQ(0, b[4]);
	}
	{
		const bksge::list<int> a { 1,1,2,3,5,8,13 };
		int b[9] {};
		auto ret = bksge::replace_copy(bksge::begin(a), bksge::end(a), bksge::begin(b), 9, 0);
		EXPECT_TRUE(ret == bksge::next(bksge::begin(b), 7));
		EXPECT_EQ( 1, b[0]);
		EXPECT_EQ( 1, b[1]);
		EXPECT_EQ( 2, b[2]);
		EXPECT_EQ( 3, b[3]);
		EXPECT_EQ( 5, b[4]);
		EXPECT_EQ( 8, b[5]);
		EXPECT_EQ(13, b[6]);
		EXPECT_EQ( 0, b[7]);
		EXPECT_EQ( 0, b[8]);
	}
	{
		bksge::list<int> a;
		bksge::vector<int> b;
		auto ret = bksge::replace_copy(bksge::begin(a), bksge::end(a), std::back_inserter(b), 0, 1);
		(void)ret;
		EXPECT_TRUE(a.empty());
		EXPECT_TRUE(b.empty());
	}
}

}	// namespace replace_copy_test

}	// namespace bksge_algorithm_test
