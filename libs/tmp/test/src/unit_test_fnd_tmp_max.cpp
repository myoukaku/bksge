/**
 *	@file	unit_test_fnd_tmp_max.cpp
 *
 *	@brief	max のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/tmp/max.hpp>
#include <gtest/gtest.h>

GTEST_TEST(TmpTest, MaxTest)
{
	static_assert(bksge::tmp::max<int, 1, 1>::value == 1, "");
	static_assert(bksge::tmp::max<int, 10, 2>::value == 10, "");
	static_assert(bksge::tmp::max<int, -3, 4>::value == 4, "");
	static_assert(bksge::tmp::max<int, -3, -4>::value == -3, "");

	static_assert(bksge::tmp::max<unsigned int, 0, 1>::value == 1, "");
	static_assert(bksge::tmp::max<unsigned int, 1, 0>::value == 1, "");
	static_assert(bksge::tmp::max<unsigned int, 2, 2>::value == 2, "");
	static_assert(bksge::tmp::max<unsigned int, 5, 6>::value == 6, "");
	static_assert(bksge::tmp::max<unsigned int, 9, 8>::value == 9, "");
}
