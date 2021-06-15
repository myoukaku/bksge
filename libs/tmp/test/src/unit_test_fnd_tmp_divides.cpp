/**
 *	@file	unit_test_fnd_tmp_divides.cpp
 *
 *	@brief	divides のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/tmp/divides.hpp>
#include <gtest/gtest.h>

GTEST_TEST(TmpTest, DividesTest)
{
	static_assert(bksge::tmp::divides<int, 1, 1>::value == 1, "");
	static_assert(bksge::tmp::divides<int, 2, 3>::value == 0, "");
	static_assert(bksge::tmp::divides<int, 3, 3>::value == 1, "");
	static_assert(bksge::tmp::divides<int, 4, 3>::value == 1, "");
	static_assert(bksge::tmp::divides<int, 14, 4>::value == 3, "");
	static_assert(bksge::tmp::divides<int, 15, 4>::value == 3, "");
	static_assert(bksge::tmp::divides<int, 16, 4>::value == 4, "");

	static_assert(bksge::tmp::divides<unsigned int, 0, 1>::value == 0, "");
	static_assert(bksge::tmp::divides<unsigned int, 1, 1>::value == 1, "");
	static_assert(bksge::tmp::divides<unsigned int, 2, 1>::value == 2, "");
	static_assert(bksge::tmp::divides<unsigned int, 3, 1>::value == 3, "");
	static_assert(bksge::tmp::divides<unsigned int, 7, 4>::value == 1, "");
	static_assert(bksge::tmp::divides<unsigned int, 8, 4>::value == 2, "");
	static_assert(bksge::tmp::divides<unsigned int, 9, 4>::value == 2, "");
}
