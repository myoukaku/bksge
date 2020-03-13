/**
 *	@file	unit_test_fnd_algorithm_prev_permutation.cpp
 *
 *	@brief	prev_permutation のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/algorithm/prev_permutation.hpp>
#include <bksge/fnd/algorithm/equal.hpp>
#include <bksge/fnd/functional/greater.hpp>
#include <bksge/fnd/iterator/begin.hpp>
#include <bksge/fnd/iterator/end.hpp>
#include <bksge/fnd/iterator/size.hpp>
#include <array>
#include <string>
#include <gtest/gtest.h>

namespace bksge_algorithm_test
{

namespace prev_permutation_test
{

BKSGE_CONSTEXPR bool pred1(int x, int y)
{
	return x < y;
}

GTEST_TEST(AlgorithmTest, PrevPermutationTest)
{
	{
		int a[] {3,2,1};

		{
			auto ret = bksge::prev_permutation(bksge::begin(a), bksge::end(a));
			EXPECT_EQ(true, ret);
			EXPECT_EQ(3, a[0]);
			EXPECT_EQ(1, a[1]);
			EXPECT_EQ(2, a[2]);
		}
		{
			auto ret = bksge::prev_permutation(bksge::begin(a), bksge::end(a));
			EXPECT_EQ(true, ret);
			EXPECT_EQ(2, a[0]);
			EXPECT_EQ(3, a[1]);
			EXPECT_EQ(1, a[2]);
		}
		{
			auto ret = bksge::prev_permutation(bksge::begin(a), bksge::end(a));
			EXPECT_EQ(true, ret);
			EXPECT_EQ(2, a[0]);
			EXPECT_EQ(1, a[1]);
			EXPECT_EQ(3, a[2]);
		}
		{
			auto ret = bksge::prev_permutation(bksge::begin(a), bksge::end(a));
			EXPECT_EQ(true, ret);
			EXPECT_EQ(1, a[0]);
			EXPECT_EQ(3, a[1]);
			EXPECT_EQ(2, a[2]);
		}
		{
			auto ret = bksge::prev_permutation(bksge::begin(a), bksge::end(a));
			EXPECT_EQ(true, ret);
			EXPECT_EQ(1, a[0]);
			EXPECT_EQ(2, a[1]);
			EXPECT_EQ(3, a[2]);
		}
		{
			auto ret = bksge::prev_permutation(bksge::begin(a), bksge::end(a));
			EXPECT_EQ(false, ret);
			EXPECT_EQ(3, a[0]);
			EXPECT_EQ(2, a[1]);
			EXPECT_EQ(1, a[2]);
		}
	}
	{
		std::array<int, 4> a {{7,6,5,4}};

		const int expected[][4]
		{
			{ 7, 6, 5, 4 },
			{ 7, 6, 4, 5 },
			{ 7, 5, 6, 4 },
			{ 7, 5, 4, 6 },
			{ 7, 4, 6, 5 },
			{ 7, 4, 5, 6 },
			{ 6, 7, 5, 4 },
			{ 6, 7, 4, 5 },
			{ 6, 5, 7, 4 },
			{ 6, 5, 4, 7 },
			{ 6, 4, 7, 5 },
			{ 6, 4, 5, 7 },
			{ 5, 7, 6, 4 },
			{ 5, 7, 4, 6 },
			{ 5, 6, 7, 4 },
			{ 5, 6, 4, 7 },
			{ 5, 4, 7, 6 },
			{ 5, 4, 6, 7 },
			{ 4, 7, 6, 5 },
			{ 4, 7, 5, 6 },
			{ 4, 6, 7, 5 },
			{ 4, 6, 5, 7 },
			{ 4, 5, 7, 6 },
			{ 4, 5, 6, 7 },
		};

		std::size_t i = 0;

		do
		{
			EXPECT_TRUE(
				bksge::equal(
					bksge::begin(a), bksge::end(a),
					bksge::begin(expected[i])));
			++i;
		}
		while (bksge::prev_permutation(bksge::begin(a), bksge::end(a), pred1));

		EXPECT_EQ(bksge::size(expected), i);
	}
	{
		std::string a = "abb";
		{
			auto ret = bksge::prev_permutation(bksge::begin(a), bksge::end(a), bksge::greater<>());
			EXPECT_EQ(true, ret);
			EXPECT_EQ("bab", a);
		}
		{
			auto ret = bksge::prev_permutation(bksge::begin(a), bksge::end(a), bksge::greater<>());
			EXPECT_EQ(true, ret);
			EXPECT_EQ("bba", a);
		}
		{
			auto ret = bksge::prev_permutation(bksge::begin(a), bksge::end(a), bksge::greater<>());
			EXPECT_EQ(false, ret);
			EXPECT_EQ("abb", a);
		}
	}
}

}	// namespace prev_permutation_test

}	// namespace bksge_algorithm_test
