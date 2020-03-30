/**
 *	@file	unit_test_fnd_tmp_all_of.cpp
 *
 *	@brief	all_of のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/tmp/all_of.hpp>
#include <bksge/fnd/config.hpp>
#include <gtest/gtest.h>

GTEST_TEST(TmpTest, AllOfTest)
{
	BKSGE_CONSTEXPR bool t = true;
	BKSGE_CONSTEXPR bool f = false;

	static_assert(bksge::tmp::all_of<>::value == true, "");

	static_assert(bksge::tmp::all_of<t>::value == true, "");
	static_assert(bksge::tmp::all_of<f>::value == false, "");

	static_assert(bksge::tmp::all_of<t, t>::value == true, "");
	static_assert(bksge::tmp::all_of<t, f>::value == false, "");
	static_assert(bksge::tmp::all_of<f, t>::value == false, "");
	static_assert(bksge::tmp::all_of<f, f>::value == false, "");

	static_assert(bksge::tmp::all_of<t, t, t>::value == true, "");
	static_assert(bksge::tmp::all_of<t, t, f>::value == false, "");
	static_assert(bksge::tmp::all_of<t, f, t>::value == false, "");
	static_assert(bksge::tmp::all_of<t, f, f>::value == false, "");
	static_assert(bksge::tmp::all_of<f, t, t>::value == false, "");
	static_assert(bksge::tmp::all_of<f, t, f>::value == false, "");
	static_assert(bksge::tmp::all_of<f, f, t>::value == false, "");
	static_assert(bksge::tmp::all_of<f, f, f>::value == false, "");

	static_assert(bksge::tmp::all_of<t, t, t, t, t, t, t, t, t, t>::value == true, "");
	static_assert(bksge::tmp::all_of<f, t, t, t, t, t, t, t, t, t>::value == false, "");
	static_assert(bksge::tmp::all_of<t, f, t, t, t, t, t, t, t, t>::value == false, "");
	static_assert(bksge::tmp::all_of<t, t, f, t, t, t, t, t, t, t>::value == false, "");
	static_assert(bksge::tmp::all_of<t, t, t, f, t, t, t, t, t, t>::value == false, "");
	static_assert(bksge::tmp::all_of<t, t, t, t, f, t, t, t, t, t>::value == false, "");
	static_assert(bksge::tmp::all_of<t, t, t, t, t, f, t, t, t, t>::value == false, "");
	static_assert(bksge::tmp::all_of<t, t, t, t, t, t, f, t, t, t>::value == false, "");
	static_assert(bksge::tmp::all_of<t, t, t, t, t, t, t, f, t, t>::value == false, "");
	static_assert(bksge::tmp::all_of<t, t, t, t, t, t, t, t, f, t>::value == false, "");
	static_assert(bksge::tmp::all_of<t, t, t, t, t, t, t, t, t, f>::value == false, "");
	static_assert(bksge::tmp::all_of<f, f, f, f, f, f, f, f, f, f>::value == false, "");
}
