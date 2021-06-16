/**
 *	@file	unit_test_fnd_algorithm_generate_n.cpp
 *
 *	@brief	generate_n のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/algorithm/generate_n.hpp>
#include <bksge/fnd/iterator/begin.hpp>
#include <bksge/fnd/iterator/end.hpp>
#include <bksge/fnd/iterator/next.hpp>
#include <bksge/fnd/array.hpp>
#include <bksge/fnd/list.hpp>
#include <bksge/fnd/vector.hpp>
#include <gtest/gtest.h>

namespace bksge_algorithm_test
{

namespace generate_n_test
{

struct pred1
{
	int operator()()
	{
		return value++;
	}

	int value = 0;
};

struct pred2
{
	int operator()()
	{
		value += 2;
		return value;
	}

	int value = 1;
};

int pred3()
{
	return 42;
}

GTEST_TEST(AlgorithmTest, GenerateNTest)
{
	{
		int a[5] {};
		auto ret = bksge::generate_n(bksge::begin(a), 5, pred1());
		EXPECT_TRUE(ret == bksge::end(a));
		EXPECT_EQ(0, a[0]);
		EXPECT_EQ(1, a[1]);
		EXPECT_EQ(2, a[2]);
		EXPECT_EQ(3, a[3]);
		EXPECT_EQ(4, a[4]);
	}
	{
		bksge::array<int, 6> a {{}};
		auto ret = bksge::generate_n(bksge::begin(a), 4, pred2());
		EXPECT_TRUE(ret == bksge::next(bksge::begin(a), 4));
		EXPECT_EQ( 3, a[0]);
		EXPECT_EQ( 5, a[1]);
		EXPECT_EQ( 7, a[2]);
		EXPECT_EQ( 9, a[3]);
		EXPECT_EQ( 0, a[4]);
		EXPECT_EQ( 0, a[5]);
	}
	{
		bksge::vector<int> a(3);
		auto ret = bksge::generate_n(bksge::begin(a), 2, pred3);
		EXPECT_TRUE(ret == bksge::next(bksge::begin(a), 2));
		EXPECT_EQ(42, a[0]);
		EXPECT_EQ(42, a[1]);
		EXPECT_EQ( 0, a[2]);
	}
	{
		bksge::vector<int> a(4);
		auto ret = bksge::generate_n(bksge::begin(a), 0, pred3);
		EXPECT_TRUE(ret == bksge::next(bksge::begin(a), 0));
		EXPECT_EQ(0, a[0]);
		EXPECT_EQ(0, a[1]);
		EXPECT_EQ(0, a[2]);
		EXPECT_EQ(0, a[3]);
	}
	{
		int n = 1;
		bksge::list<int> a(4);
		auto ret = bksge::generate_n(bksge::begin(a), 4, [&]() { auto t = n; n *= 2; return t;});
		EXPECT_TRUE(ret == bksge::end(a));

		auto it = a.begin();
		EXPECT_EQ(1, *it++);
		EXPECT_EQ(2, *it++);
		EXPECT_EQ(4, *it++);
		EXPECT_EQ(8, *it++);
		EXPECT_TRUE(it == a.end());

		EXPECT_EQ(16, n);
	}
	{
		int n = 1;
		bksge::list<int> a;
		auto ret = bksge::generate_n(bksge::begin(a), 0, [&]() { auto t = n; n *= 2; return t;});
		EXPECT_TRUE(ret == bksge::end(a));
		EXPECT_TRUE(a.empty());
		EXPECT_EQ(1, n);
	}
}

}	// namespace generate_n_test

}	// namespace bksge_algorithm_test
