/**
 *	@file	unit_test_fnd_algorithm_remove_copy_if.cpp
 *
 *	@brief	remove_copy_if のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/algorithm/remove_copy_if.hpp>
#include <bksge/fnd/iterator/begin.hpp>
#include <bksge/fnd/iterator/end.hpp>
#include <bksge/fnd/iterator/next.hpp>
#include <iterator>
#include <list>
#include <vector>
#include <array>
#include <gtest/gtest.h>

namespace bksge_algorithm_test
{

namespace remove_copy_if_test
{

bool pred1(int a)
{
	return a == 1;
}

struct pred2
{
	bool operator()(int a)
	{
		return a > 1;
	}
};

GTEST_TEST(AlgorithmTest, RemoveCopyIfTest)
{
	{
		const int a[] = {1,2,3,1,3,1,2};
		int b[10] {};
		auto ret = bksge::remove_copy_if(bksge::begin(a), bksge::end(a), bksge::begin(b), pred1);
		EXPECT_TRUE(ret == bksge::next(bksge::begin(b), 4));
		EXPECT_EQ(2, b[0]);
		EXPECT_EQ(3, b[1]);
		EXPECT_EQ(3, b[2]);
		EXPECT_EQ(2, b[3]);
	}
	{
		const int a[] = {1,2,3,1,3,1,2};
		std::vector<int> b;
		auto ret = bksge::remove_copy_if(bksge::begin(a), bksge::end(a), std::back_inserter(b), pred1);
		(void)ret;
		EXPECT_EQ(4u, b.size());
		EXPECT_EQ(2, b[0]);
		EXPECT_EQ(3, b[1]);
		EXPECT_EQ(3, b[2]);
		EXPECT_EQ(2, b[3]);
	}
	{
		const int a[] = {1,2,3,1,3,1,2};
		int b[10] {};
		auto ret = bksge::remove_copy_if(bksge::begin(a), bksge::end(a), bksge::begin(b), pred2());
		EXPECT_TRUE(ret == bksge::next(bksge::begin(b), 3));
		EXPECT_EQ(1, b[0]);
		EXPECT_EQ(1, b[1]);
		EXPECT_EQ(1, b[2]);
	}
	{
		const std::array<int, 7> a = {{1,2,3,1,3,1,2}};
		int b[10] {};
		auto ret = bksge::remove_copy_if(bksge::begin(a), bksge::end(a), bksge::begin(b), [](int a) { return a == 3; });
		EXPECT_TRUE(ret == bksge::next(bksge::begin(b), 5));
		EXPECT_EQ(1, b[0]);
		EXPECT_EQ(2, b[1]);
		EXPECT_EQ(1, b[2]);
		EXPECT_EQ(1, b[3]);
		EXPECT_EQ(2, b[4]);
	}
	{
		const std::array<int, 7> a = {{1,2,3,1,3,1,2}};
		std::list<int> b;
		auto ret = bksge::remove_copy_if(bksge::begin(a), bksge::end(a), std::back_inserter(b), [](int a) { return a >= 3; });
		(void)ret;
		auto it = b.begin();
		EXPECT_EQ(1, *it++);
		EXPECT_EQ(2, *it++);
		EXPECT_EQ(1, *it++);
		EXPECT_EQ(1, *it++);
		EXPECT_EQ(2, *it++);
		EXPECT_TRUE(it == b.end());
	}
	{
		const std::array<int, 4> a = {{1,1,1,1}};
		int b[10] {};
		auto ret = bksge::remove_copy_if(bksge::begin(a), bksge::end(a), bksge::begin(b), [](int a) { return a == 1; });
		EXPECT_TRUE(ret == bksge::begin(b));
	}
	{
		const std::array<int, 4> a = {{1,1,1,1}};
		std::vector<int> b;
		auto ret = bksge::remove_copy_if(bksge::begin(a), bksge::end(a), std::back_inserter(b), [](int a) { return a >= 0; });
		(void)ret;
		EXPECT_TRUE(b.empty());
	}
	{
		const std::vector<int> a = {1,2,3,1,3,1,2,2};
		std::array<int, 10> b {{}};
		auto ret = bksge::remove_copy_if(bksge::begin(a), bksge::end(a), bksge::begin(b), [](int a) { return a == 2; });
		EXPECT_TRUE(ret == bksge::next(bksge::begin(b), 5));
		EXPECT_EQ(1, b[0]);
		EXPECT_EQ(3, b[1]);
		EXPECT_EQ(1, b[2]);
		EXPECT_EQ(3, b[3]);
		EXPECT_EQ(1, b[4]);
	}
	{
		const std::vector<int> a;
		int b[10] {};
		auto ret = bksge::remove_copy_if(bksge::begin(a), bksge::end(a), bksge::begin(b), [](int ) { return true; });
		EXPECT_TRUE(ret == bksge::begin(b));
	}
	{
		const std::list<int> a = {1,2,3,1,3,1,2,1,1};
		int b[10] {};
		auto ret = bksge::remove_copy_if(bksge::begin(a), bksge::end(a), bksge::begin(b), [](int a) { return a == 2; });
		EXPECT_TRUE(ret == bksge::next(bksge::begin(b), 7));
		EXPECT_EQ(1, b[0]);
		EXPECT_EQ(3, b[1]);
		EXPECT_EQ(1, b[2]);
		EXPECT_EQ(3, b[3]);
		EXPECT_EQ(1, b[4]);
		EXPECT_EQ(1, b[5]);
		EXPECT_EQ(1, b[6]);
	}
	{
		const std::list<int> a;
		int b[10] {};
		auto ret = bksge::remove_copy_if(bksge::begin(a), bksge::end(a), bksge::begin(b), [](int ) { return false; });
		EXPECT_TRUE(ret == bksge::begin(b));
	}
}

}	// namespace remove_copy_if_test

}	// namespace bksge_algorithm_test
