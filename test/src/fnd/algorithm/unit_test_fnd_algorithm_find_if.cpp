/**
 *	@file	unit_test_fnd_algorithm_find_if.cpp
 *
 *	@brief	find_if のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/algorithm/find_if.hpp>
#include <bksge/fnd/iterator/begin.hpp>
#include <bksge/fnd/iterator/end.hpp>
#include <gtest/gtest.h>
#include <array>
#include <list>
#include <bksge/fnd/vector.hpp>
#include "constexpr_test.hpp"

namespace bksge_algorithm_test
{

namespace find_if_test
{

BKSGE_CONSTEXPR bool pred1(int x)
{
	return x == 1;
}
BKSGE_CONSTEXPR bool pred2(int x)
{
	return x > 2;
}

struct pred3
{
	BKSGE_CONSTEXPR bool operator()(int x) const
	{
		return x % 2 == 0;
	}
};

struct pred4
{
	BKSGE_CONSTEXPR bool operator()(int x) const
	{
		return x % 2 == 1;
	}
};

GTEST_TEST(AlgorithmTest, FindIfTest)
{
	BKSGE_STATIC_CONSTEXPR int a1[] {0,1,2};
	{
		BKSGE_CXX14_CONSTEXPR_OR_CONST auto it = bksge::find_if(bksge::begin(a1), bksge::end(a1), pred1);
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(it == bksge::begin(a1) + 1);
	}
	{
		BKSGE_CXX14_CONSTEXPR_OR_CONST auto it = bksge::find_if(bksge::begin(a1), bksge::end(a1), pred2);
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(it == bksge::end(a1));
	}
	{
		BKSGE_CXX14_CONSTEXPR_OR_CONST auto it = bksge::find_if(bksge::begin(a1), bksge::end(a1), pred3());
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(it == bksge::begin(a1));
	}
	{
		BKSGE_CXX14_CONSTEXPR_OR_CONST auto it = bksge::find_if(bksge::begin(a1), bksge::end(a1), pred4());
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(it == bksge::begin(a1) + 1);
	}

	BKSGE_STATIC_CONSTEXPR std::array<int, 8> a2{{3, 4, 4, 5, 5, 5, 3, 6}};
	{
		BKSGE_CXX17_CONSTEXPR_OR_CONST auto it = bksge::find_if(bksge::begin(a2), bksge::end(a2), pred1);
		BKSGE_CXX17_CONSTEXPR_EXPECT_TRUE(it == bksge::end(a2));
	}
	{
		BKSGE_CXX17_CONSTEXPR_OR_CONST auto it = bksge::find_if(bksge::begin(a2), bksge::end(a2), pred2);
		BKSGE_CXX17_CONSTEXPR_EXPECT_TRUE(it == bksge::begin(a2));
	}
	{
		BKSGE_CXX17_CONSTEXPR_OR_CONST auto it = bksge::find_if(bksge::begin(a2), bksge::end(a2), pred3());
		BKSGE_CXX17_CONSTEXPR_EXPECT_TRUE(it == bksge::begin(a2) + 1);
	}
	{
		BKSGE_CXX17_CONSTEXPR_OR_CONST auto it = bksge::find_if(bksge::begin(a2), bksge::end(a2), pred4());
		BKSGE_CXX17_CONSTEXPR_EXPECT_TRUE(it == bksge::begin(a2));
	}

	int a3[] {0,1,2};
	{
		auto it = bksge::find_if(bksge::begin(a3), bksge::end(a3), pred3());
		EXPECT_TRUE(it == bksge::begin(a3));
		*it = 10;
	}
	{
		auto it = bksge::find_if(bksge::begin(a3), bksge::end(a3), [](int x) { return x == 2; });
		EXPECT_TRUE(it == bksge::begin(a3) + 2);
		*it = 20;
	}
	{
		auto it = bksge::find_if(bksge::begin(a3), bksge::end(a3), [](int x) { return x < 0; });
		EXPECT_TRUE(it == bksge::end(a3));
	}
	EXPECT_EQ(10, a3[0]);
	EXPECT_EQ( 1, a3[1]);
	EXPECT_EQ(20, a3[2]);

	const bksge::vector<int> v1 {7, 8, 9};
	{
		auto it = bksge::find_if(bksge::begin(v1), bksge::end(v1), [](int x) { return x == 7; });
		EXPECT_TRUE(it == bksge::begin(v1));
	}
	{
		auto it = bksge::find_if(bksge::begin(v1), bksge::end(v1), [](int x) { return x > 8; });
		EXPECT_TRUE(it == bksge::begin(v1) + 2);
	}
	{
		auto it = bksge::find_if(bksge::begin(v1), bksge::end(v1), [](int x) { return x == 10; });
		EXPECT_TRUE(it == bksge::end(v1));
	}

	const std::list<int> l1 {0,1,2};
	{
		auto it = bksge::find_if(bksge::begin(l1), bksge::end(l1), pred1);
		EXPECT_TRUE(it == ++bksge::begin(l1));
	}
	{
		auto it = bksge::find_if(bksge::begin(l1), bksge::end(l1), pred3());
		EXPECT_TRUE(it == bksge::begin(l1));
	}
	{
		auto it = bksge::find_if(bksge::begin(l1), bksge::end(l1), [](int x) { return x < 0; });
		EXPECT_TRUE(it == bksge::end(l1));
	}

	std::list<int> l2 {0,1,2};
	{
		auto it = bksge::find_if(bksge::begin(l2), bksge::end(l2), [](int x) { return x % 2 == 1; });
		EXPECT_TRUE(it == ++bksge::begin(l2));
		*it = 30;
	}
	{
		auto it = bksge::find_if(bksge::begin(l2), bksge::end(l2), [](int x) { return x == 10; });
		EXPECT_TRUE(it == bksge::end(l2));
	}
	{
		auto it = l2.begin();
		EXPECT_EQ( 0, *it++);
		EXPECT_EQ(30, *it++);
		EXPECT_EQ( 2, *it++);
	}
}

}	// namespace find_if_test

}	// namespace bksge_algorithm_test
