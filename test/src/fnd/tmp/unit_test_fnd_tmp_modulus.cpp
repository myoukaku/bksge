/**
 *	@file	unit_test_fnd_tmp_modulus.cpp
 *
 *	@brief	modulus のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/tmp/modulus.hpp>
#include <gtest/gtest.h>

GTEST_TEST(TmpTest, ModulusTest)
{
	static_assert(bksge::tmp::modulus<int, 1, 1>::value == 0, "");
	static_assert(bksge::tmp::modulus<int, 1, 3>::value == 1, "");
	static_assert(bksge::tmp::modulus<int, 2, 3>::value == 2, "");
	static_assert(bksge::tmp::modulus<int, 3, 3>::value == 0, "");
	static_assert(bksge::tmp::modulus<int, 4, 3>::value == 1, "");
	static_assert(bksge::tmp::modulus<int, 5, 3>::value == 2, "");

	static_assert(bksge::tmp::modulus<unsigned int, 0, 1>::value == 0, "");
	static_assert(bksge::tmp::modulus<unsigned int, 1, 1>::value == 0, "");
	static_assert(bksge::tmp::modulus<unsigned int, 2, 1>::value == 0, "");
	static_assert(bksge::tmp::modulus<unsigned int, 5, 4>::value == 1, "");
	static_assert(bksge::tmp::modulus<unsigned int, 6, 4>::value == 2, "");
	static_assert(bksge::tmp::modulus<unsigned int, 7, 4>::value == 3, "");
	static_assert(bksge::tmp::modulus<unsigned int, 8, 4>::value == 0, "");
}
