/**
 *	@file	unit_test_fnd_algorithm_next_permutation.cpp
 *
 *	@brief	next_permutation のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/algorithm/next_permutation.hpp>
#include <bksge/fnd/algorithm/equal.hpp>
#include <bksge/fnd/functional/greater.hpp>
#include <bksge/fnd/iterator/begin.hpp>
#include <bksge/fnd/iterator/end.hpp>
#include <bksge/fnd/iterator/size.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>
#include <array>
#include <string>
#include <gtest/gtest.h>

namespace bksge_algorithm_test
{

namespace next_permutation_test
{

BKSGE_CONSTEXPR bool pred1(int x, int y)
{
	return x < y;
}

GTEST_TEST(AlgorithmTest, NextPermutationTest)
{
	{
		int a[] {1,2,3};

		{
			auto ret = bksge::next_permutation(bksge::begin(a), bksge::end(a));
			EXPECT_EQ(true, ret);
			EXPECT_EQ(1, a[0]);
			EXPECT_EQ(3, a[1]);
			EXPECT_EQ(2, a[2]);
		}
		{
			auto ret = bksge::next_permutation(bksge::begin(a), bksge::end(a));
			EXPECT_EQ(true, ret);
			EXPECT_EQ(2, a[0]);
			EXPECT_EQ(1, a[1]);
			EXPECT_EQ(3, a[2]);
		}
		{
			auto ret = bksge::next_permutation(bksge::begin(a), bksge::end(a));
			EXPECT_EQ(true, ret);
			EXPECT_EQ(2, a[0]);
			EXPECT_EQ(3, a[1]);
			EXPECT_EQ(1, a[2]);
		}
		{
			auto ret = bksge::next_permutation(bksge::begin(a), bksge::end(a));
			EXPECT_EQ(true, ret);
			EXPECT_EQ(3, a[0]);
			EXPECT_EQ(1, a[1]);
			EXPECT_EQ(2, a[2]);
		}
		{
			auto ret = bksge::next_permutation(bksge::begin(a), bksge::end(a));
			EXPECT_EQ(true, ret);
			EXPECT_EQ(3, a[0]);
			EXPECT_EQ(2, a[1]);
			EXPECT_EQ(1, a[2]);
		}
		{
			auto ret = bksge::next_permutation(bksge::begin(a), bksge::end(a));
			EXPECT_EQ(false, ret);
			EXPECT_EQ(1, a[0]);
			EXPECT_EQ(2, a[1]);
			EXPECT_EQ(3, a[2]);
		}
	}
	{
		std::array<int, 4> a {{4,5,6,7}};

		const int expected[][4]
		{
			{ 4, 5, 6, 7 },
			{ 4, 5, 7, 6 },
			{ 4, 6, 5, 7 },
			{ 4, 6, 7, 5 },
			{ 4, 7, 5, 6 },
			{ 4, 7, 6, 5 },
			{ 5, 4, 6, 7 },
			{ 5, 4, 7, 6 },
			{ 5, 6, 4, 7 },
			{ 5, 6, 7, 4 },
			{ 5, 7, 4, 6 },
			{ 5, 7, 6, 4 },
			{ 6, 4, 5, 7 },
			{ 6, 4, 7, 5 },
			{ 6, 5, 4, 7 },
			{ 6, 5, 7, 4 },
			{ 6, 7, 4, 5 },
			{ 6, 7, 5, 4 },
			{ 7, 4, 5, 6 },
			{ 7, 4, 6, 5 },
			{ 7, 5, 4, 6 },
			{ 7, 5, 6, 4 },
			{ 7, 6, 4, 5 },
			{ 7, 6, 5, 4 },
		};

		bksge::size_t i = 0;

		do
		{
			EXPECT_TRUE(
				bksge::equal(
					bksge::begin(a), bksge::end(a),
					bksge::begin(expected[i])));
			++i;
		}
		while (bksge::next_permutation(bksge::begin(a), bksge::end(a), pred1));

		EXPECT_EQ(bksge::size(expected), i);
	}
	{
		std::string a = "baa";
		{
			auto ret = bksge::next_permutation(bksge::begin(a), bksge::end(a), bksge::greater<>());
			EXPECT_EQ(true, ret);
			EXPECT_EQ("aba", a);
		}
		{
			auto ret = bksge::next_permutation(bksge::begin(a), bksge::end(a), bksge::greater<>());
			EXPECT_EQ(true, ret);
			EXPECT_EQ("aab", a);
		}
		{
			auto ret = bksge::next_permutation(bksge::begin(a), bksge::end(a), bksge::greater<>());
			EXPECT_EQ(false, ret);
			EXPECT_EQ("baa", a);
		}
	}
}

}	// namespace next_permutation_test

}	// namespace bksge_algorithm_test
