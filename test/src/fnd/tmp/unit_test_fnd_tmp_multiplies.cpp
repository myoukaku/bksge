/**
 *	@file	unit_test_fnd_tmp_multiplies.cpp
 *
 *	@brief	multiplies のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/tmp/multiplies.hpp>
#include <gtest/gtest.h>

GTEST_TEST(TmpTest, MultipliesTest)
{
	static_assert(bksge::tmp::multiplies<int, 1, 1>::value == 1, "");
	static_assert(bksge::tmp::multiplies<int, 2, 3>::value == 6, "");
	static_assert(bksge::tmp::multiplies<int, 13, 4>::value == 52, "");
	static_assert(bksge::tmp::multiplies<int, 3, -12>::value == -36, "");
	static_assert(bksge::tmp::multiplies<int, -6, -7>::value == 42, "");

	static_assert(bksge::tmp::multiplies<unsigned int, 0, 1>::value == 0, "");
	static_assert(bksge::tmp::multiplies<unsigned int, 5, 4>::value == 20, "");
}
