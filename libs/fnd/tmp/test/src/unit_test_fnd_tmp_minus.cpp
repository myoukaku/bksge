/**
 *	@file	unit_test_fnd_tmp_minus.cpp
 *
 *	@brief	minus のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/tmp/minus.hpp>
#include <gtest/gtest.h>

GTEST_TEST(TmpTest, MinusTest)
{
	static_assert(bksge::tmp::minus<int, 1, 1>::value == 0, "");
	static_assert(bksge::tmp::minus<int, 2, 3>::value == -1, "");
	static_assert(bksge::tmp::minus<int, 13, 4>::value == 9, "");
	static_assert(bksge::tmp::minus<int, 3, -12>::value == 15, "");
	static_assert(bksge::tmp::minus<int, -6, -7>::value == 1, "");

	static_assert(bksge::tmp::minus<unsigned int, 10, 1>::value == 9, "");
	static_assert(bksge::tmp::minus<unsigned int, 5, 4>::value == 1, "");
}
