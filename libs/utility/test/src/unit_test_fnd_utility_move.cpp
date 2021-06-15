/**
 *	@file	unit_test_fnd_utility_move.cpp
 *
 *	@brief	move のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/utility/move.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace bksge_utility_test
{

namespace move_test
{

BKSGE_CONSTEXPR
int func(const int&)
{
	return 0;
}

BKSGE_CONSTEXPR
int func(const int&&)
{
	return 1;
}

GTEST_TEST(UtilityTest, MoveTest)
{
	{
		int i = 3;
		EXPECT_EQ(0, func(i));
		EXPECT_EQ(1, func(bksge::move(i)));
		EXPECT_EQ(1, func(0));
	}
	{
		BKSGE_CONSTEXPR int i = 42;
		BKSGE_CONSTEXPR_EXPECT_EQ(0, func(i));
		BKSGE_CONSTEXPR_EXPECT_EQ(1, func(bksge::move(i)));
		BKSGE_CONSTEXPR_EXPECT_EQ(1, func(0));
	}
}

}	// namespace move_test

}	// namespace bksge_utility_test
