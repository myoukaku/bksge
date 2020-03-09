/**
 *	@file	unit_test_fnd_algorithm_copy_if.cpp
 *
 *	@brief	copy_if のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/algorithm/copy_if.hpp>
#include <bksge/fnd/iterator/begin.hpp>
#include <bksge/fnd/iterator/end.hpp>
#include <gtest/gtest.h>
#include <array>
#include <iterator>
#include <list>
#include <bksge/fnd/vector.hpp>

namespace bksge_algorithm_test
{

namespace copy_if_test
{

GTEST_TEST(AlgorithmTest, CopyIfTest)
{
	{
		const int a1[] { 1, 2, 3 };
		int a2[3]{};

		auto it = bksge::copy_if(bksge::begin(a1), bksge::end(a1), bksge::begin(a2), [](int x) { return x > 1; });

		EXPECT_EQ(2, a2[0]);
		EXPECT_EQ(3, a2[1]);
		EXPECT_EQ(0, a2[2]);
		EXPECT_TRUE(it == bksge::begin(a2) + 2);
	}
	{
		const std::array<int, 4> a1 {{ 4, 5, 6, 7 }};
		int a2[5] {{}};

		auto it = bksge::copy_if(bksge::begin(a1), bksge::end(a1), bksge::begin(a2), [](int x) { return (x % 2) == 0; });

		EXPECT_EQ(4, a2[0]);
		EXPECT_EQ(6, a2[1]);
		EXPECT_EQ(0, a2[2]);
		EXPECT_EQ(0, a2[3]);
		EXPECT_EQ(0, a2[4]);
		EXPECT_TRUE(it == bksge::begin(a2) + 2);
	}
	{
		const bksge::vector<int> v { 5, 6, 7, 8, 9 };
		std::list<int> l;

		bksge::copy_if(bksge::begin(v), bksge::end(v), std::back_inserter(l), [](int x) { return (x % 2) == 1; });

		auto it = l.begin();
		EXPECT_EQ(5, *it++);
		EXPECT_EQ(7, *it++);
		EXPECT_EQ(9, *it++);
		EXPECT_TRUE(it == l.end());
	}
}

}	// namespace copy_if_test

}	// namespace bksge_algorithm_test
