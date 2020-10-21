/**
 *	@file	unit_test_fnd_compare_compare_three_way.cpp
 *
 *	@brief	compare_three_way のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/compare/compare_three_way.hpp>
#include <bksge/fnd/config.hpp>
#include <gtest/gtest.h>

#if defined(BKSGE_HAS_STD_COMPARE) && defined(BKSGE_HAS_CXX20_THREE_WAY_COMPARISON)

GTEST_TEST(CompareTest, CompareThreeWayTest)
{
	static_assert(bksge::compare_three_way{}(0, 0) == 0, "");
	static_assert(bksge::compare_three_way{}(0, 1) <  0, "");
	static_assert(bksge::compare_three_way{}(1, 0) >  0, "");
	static_assert(bksge::compare_three_way{}(1, 1) == 0, "");

	int a{}, b{};

	int* pa = &a;
	int* pb = &b;

	bksge::compare_three_way comp{};
	EXPECT_TRUE(comp(a, b) == 0);
	EXPECT_FALSE(comp(pa, pb) == 0);
	EXPECT_TRUE(comp(pa, pb) > 0 || comp(pa, pb) < 0);	// pa > pb または pa < pb (実装依存)
}

#endif
