/**
 *	@file	unit_test_fnd_algorithm_unique_copy.cpp
 *
 *	@brief	unique_copy のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/algorithm/unique_copy.hpp>
#include <bksge/fnd/iterator/begin.hpp>
#include <bksge/fnd/iterator/end.hpp>
#include <bksge/fnd/iterator/next.hpp>
#include <bksge/fnd/iterator/back_inserter.hpp>
#include <bksge/fnd/sstream/stringstream.hpp>
#include <bksge/fnd/array.hpp>
#include <bksge/fnd/list.hpp>
#include <bksge/fnd/vector.hpp>
#include <iterator>	// istream_iterator
#include <gtest/gtest.h>

namespace bksge_algorithm_test
{

namespace unique_copy_test
{

bool pred1(int x, int y)
{
	return x == y;
}

struct pred2
{
	bool operator()(int x, int y) const
	{
		return x == y;
	}
};

GTEST_TEST(AlgorithmTest, UniqueCopyTest)
{
	{
		const int a[] { 2,5,3,3,1,2,4,2,1,1,4,4,3,3,3 };
		bksge::array<int, 12> b {{}};
		auto ret = bksge::unique_copy(bksge::begin(a), bksge::end(a), bksge::begin(b));
		EXPECT_TRUE(ret == bksge::next(bksge::begin(b), 10));

		EXPECT_EQ(2, b[0]);
		EXPECT_EQ(5, b[1]);
		EXPECT_EQ(3, b[2]);
		EXPECT_EQ(1, b[3]);
		EXPECT_EQ(2, b[4]);
		EXPECT_EQ(4, b[5]);
		EXPECT_EQ(2, b[6]);
		EXPECT_EQ(1, b[7]);
		EXPECT_EQ(4, b[8]);
		EXPECT_EQ(3, b[9]);
		EXPECT_EQ(0, b[10]);
		EXPECT_EQ(0, b[11]);
	}
	{
		const bksge::array<int, 10> a {{ 1,1,2,2,2,3,4,4,5,5 }};
		bksge::vector<int> b(10);
		auto ret = bksge::unique_copy(bksge::begin(a), bksge::end(a), bksge::begin(b));
		EXPECT_TRUE(ret == bksge::next(bksge::begin(b), 5));

		EXPECT_EQ(1, b[0]);
		EXPECT_EQ(2, b[1]);
		EXPECT_EQ(3, b[2]);
		EXPECT_EQ(4, b[3]);
		EXPECT_EQ(5, b[4]);
		EXPECT_EQ(0, b[5]);
		EXPECT_EQ(0, b[6]);
		EXPECT_EQ(0, b[7]);
		EXPECT_EQ(0, b[8]);
		EXPECT_EQ(0, b[9]);
	}
	{
		const bksge::vector<int> a { 1,4,4,2,1,1,3,3,3 };
		bksge::list<int> b;
		auto ret = bksge::unique_copy(bksge::begin(a), bksge::end(a), bksge::back_inserter(b), pred1);
		(void)ret;

		auto it = b.begin();
		EXPECT_EQ(1, *it++);
		EXPECT_EQ(4, *it++);
		EXPECT_EQ(2, *it++);
		EXPECT_EQ(1, *it++);
		EXPECT_EQ(3, *it++);
		EXPECT_TRUE(it == b.end());
	}
	{
		const bksge::vector<int> a;
		int b[3] {};
		auto ret = bksge::unique_copy(bksge::begin(a), bksge::end(a), bksge::begin(b), [](int, int){ return true; });
		EXPECT_TRUE(ret == bksge::next(bksge::begin(b), 0));
		EXPECT_EQ(0, b[0]);
		EXPECT_EQ(0, b[1]);
		EXPECT_EQ(0, b[2]);
	}
	{
		const bksge::list<int> a { 1,1,1,4,4,2,3,3,2 };
		bksge::vector<int> b;
		auto ret = bksge::unique_copy(bksge::begin(a), bksge::end(a), bksge::back_inserter(b), pred2());
		(void)ret;

		EXPECT_EQ(1, b[0]);
		EXPECT_EQ(4, b[1]);
		EXPECT_EQ(2, b[2]);
		EXPECT_EQ(3, b[3]);
		EXPECT_EQ(2, b[4]);
	}
	{
		const bksge::list<int> a;
		bksge::vector<int> b;
		auto ret = bksge::unique_copy(bksge::begin(a), bksge::end(a), bksge::back_inserter(b), [](int, int){ return false; });
		(void)ret;
		EXPECT_TRUE(b.empty());
	}
	{
		bksge::stringstream ss("1 1 1 2 2 3 33");
		std::istream_iterator<int> ii_first(ss);
		std::istream_iterator<int> ii_last;
		bksge::vector<int> b;
		auto ret = bksge::unique_copy(ii_first, ii_last, bksge::back_inserter(b));
		(void)ret;
		EXPECT_EQ( 4u, b.size());
		EXPECT_EQ( 1, b[0]);
		EXPECT_EQ( 2, b[1]);
		EXPECT_EQ( 3, b[2]);
		EXPECT_EQ(33, b[3]);
	}
}

}	// namespace unique_copy_test

}	// namespace bksge_algorithm_test
