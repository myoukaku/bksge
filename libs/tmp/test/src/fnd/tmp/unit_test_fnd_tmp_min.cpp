/**
 *	@file	unit_test_fnd_tmp_min.cpp
 *
 *	@brief	min のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/tmp/min.hpp>
#include <gtest/gtest.h>

GTEST_TEST(TmpTest, MinTest)
{
	static_assert(bksge::tmp::min<int, 1, 1>::value == 1, "");
	static_assert(bksge::tmp::min<int, 10, 2>::value == 2, "");
	static_assert(bksge::tmp::min<int, -3, 4>::value == -3, "");
	static_assert(bksge::tmp::min<int, -3, -4>::value == -4, "");

	static_assert(bksge::tmp::min<unsigned int, 0, 1>::value == 0, "");
	static_assert(bksge::tmp::min<unsigned int, 1, 0>::value == 0, "");
	static_assert(bksge::tmp::min<unsigned int, 2, 2>::value == 2, "");
	static_assert(bksge::tmp::min<unsigned int, 5, 6>::value == 5, "");
	static_assert(bksge::tmp::min<unsigned int, 9, 8>::value == 8, "");
}
