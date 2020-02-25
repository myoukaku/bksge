/**
 *	@file	unit_test_fnd_algorithm_generate.cpp
 *
 *	@brief	generate のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/algorithm/generate.hpp>
#include <bksge/fnd/iterator/begin.hpp>
#include <bksge/fnd/iterator/end.hpp>
#include <gtest/gtest.h>
#include <array>
#include <list>
#include <vector>
#include "constexpr_test.hpp"

namespace bksge_algorithm_test
{

namespace generate_test
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

GTEST_TEST(AlgorithmTest, GenerateTest)
{
	{
		int a[5] {};
		bksge::generate(bksge::begin(a), bksge::end(a), pred1());
		EXPECT_EQ(0, a[0]);
		EXPECT_EQ(1, a[1]);
		EXPECT_EQ(2, a[2]);
		EXPECT_EQ(3, a[3]);
		EXPECT_EQ(4, a[4]);
	}
	{
		std::array<int, 6> a {{}};
		bksge::generate(bksge::begin(a), bksge::end(a), pred2());
		EXPECT_EQ( 3, a[0]);
		EXPECT_EQ( 5, a[1]);
		EXPECT_EQ( 7, a[2]);
		EXPECT_EQ( 9, a[3]);
		EXPECT_EQ(11, a[4]);
		EXPECT_EQ(13, a[5]);
	}
	{
		std::vector<int> a(3);
		bksge::generate(bksge::begin(a), bksge::end(a), pred3);
		EXPECT_EQ(42, a[0]);
		EXPECT_EQ(42, a[1]);
		EXPECT_EQ(42, a[2]);
	}
	{
		int n = 1;
		std::list<int> a(4);
		bksge::generate(bksge::begin(a), bksge::end(a), [&]() { auto t = n; n *= 2; return t;});

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
		std::list<int> a;
		bksge::generate(bksge::begin(a), bksge::end(a), [&]() { auto t = n; n *= 2; return t;});
		EXPECT_TRUE(a.empty());

		EXPECT_EQ(1, n);
	}
}

}	// namespace generate_test

}	// namespace bksge_algorithm_test
