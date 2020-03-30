/**
 *	@file	unit_test_fnd_tmp_plus.cpp
 *
 *	@brief	plus のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/tmp/plus.hpp>
#include <gtest/gtest.h>

GTEST_TEST(TmpTest, PlusTest)
{
	static_assert(bksge::tmp::plus<int, 1, 1>::value == 2, "");
	static_assert(bksge::tmp::plus<int, 2, 3>::value == 5, "");
	static_assert(bksge::tmp::plus<int, 13, 4>::value == 17, "");
	static_assert(bksge::tmp::plus<int, 3, -12>::value == -9, "");
	static_assert(bksge::tmp::plus<int, -6, -7>::value == -13, "");

	static_assert(bksge::tmp::plus<unsigned int, 0, 1>::value == 1, "");
	static_assert(bksge::tmp::plus<unsigned int, 5, 4>::value == 9, "");
}
