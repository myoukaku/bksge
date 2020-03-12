/**
 *	@file	unit_test_fnd_algorithm_shuffle.cpp
 *
 *	@brief	shuffle のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/algorithm/shuffle.hpp>
#include <bksge/fnd/algorithm/is_sorted.hpp>
#include <bksge/fnd/iterator/begin.hpp>
#include <bksge/fnd/iterator/end.hpp>
#include <bksge/fnd/random/engines/xorshift.hpp>
#include <array>
#include <vector>
#include <gtest/gtest.h>

namespace bksge_algorithm_test
{

namespace shuffle_test
{

GTEST_TEST(AlgorithmTest, ShuffleTest)
{
	auto g = bksge::xorshift32();

	{
		int a[] {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
		EXPECT_TRUE (bksge::is_sorted(bksge::begin(a), bksge::end(a)));
		bksge::shuffle(bksge::begin(a), bksge::end(a), g);
		EXPECT_FALSE(bksge::is_sorted(bksge::begin(a), bksge::end(a)));
	}
	{
		std::array<int, 10> a{ { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 } };
		EXPECT_TRUE (bksge::is_sorted(bksge::begin(a), bksge::end(a)));
		bksge::shuffle(bksge::begin(a), bksge::end(a), g);
		EXPECT_FALSE(bksge::is_sorted(bksge::begin(a), bksge::end(a)));
	}
	{
		std::vector<int> a{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
		EXPECT_TRUE (bksge::is_sorted(bksge::begin(a), bksge::end(a)));
		bksge::shuffle(bksge::begin(a), bksge::end(a), g);
		EXPECT_FALSE(bksge::is_sorted(bksge::begin(a), bksge::end(a)));
	}
}

}	// namespace shuffle_test

}	// namespace bksge_algorithm_test
