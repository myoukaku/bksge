/**
 *	@file	unit_test_fnd_tmp_any_of.cpp
 *
 *	@brief	any_of のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/tmp/any_of.hpp>
#include <gtest/gtest.h>

GTEST_TEST(TmpTest, AnyOfTest)
{
	constexpr bool t = true;
	constexpr bool f = false;

	static_assert(bksge::tmp::any_of<>::value == false, "");

	static_assert(bksge::tmp::any_of<t>::value == true, "");
	static_assert(bksge::tmp::any_of<f>::value == false, "");

	static_assert(bksge::tmp::any_of<t, t>::value == true, "");
	static_assert(bksge::tmp::any_of<t, f>::value == true, "");
	static_assert(bksge::tmp::any_of<f, t>::value == true, "");
	static_assert(bksge::tmp::any_of<f, f>::value == false, "");

	static_assert(bksge::tmp::any_of<t, t, t>::value == true, "");
	static_assert(bksge::tmp::any_of<t, t, f>::value == true, "");
	static_assert(bksge::tmp::any_of<t, f, t>::value == true, "");
	static_assert(bksge::tmp::any_of<t, f, f>::value == true, "");
	static_assert(bksge::tmp::any_of<f, t, t>::value == true, "");
	static_assert(bksge::tmp::any_of<f, t, f>::value == true, "");
	static_assert(bksge::tmp::any_of<f, f, t>::value == true, "");
	static_assert(bksge::tmp::any_of<f, f, f>::value == false, "");

	static_assert(bksge::tmp::any_of<t, t, t, t, t, t, t, t, t, t>::value == true, "");
	static_assert(bksge::tmp::any_of<t, f, f, f, f, f, f, f, f, f>::value == true, "");
	static_assert(bksge::tmp::any_of<f, t, f, f, f, f, f, f, f, f>::value == true, "");
	static_assert(bksge::tmp::any_of<f, f, t, f, f, f, f, f, f, f>::value == true, "");
	static_assert(bksge::tmp::any_of<f, f, f, t, f, f, f, f, f, f>::value == true, "");
	static_assert(bksge::tmp::any_of<f, f, f, f, t, f, f, f, f, f>::value == true, "");
	static_assert(bksge::tmp::any_of<f, f, f, f, f, t, f, f, f, f>::value == true, "");
	static_assert(bksge::tmp::any_of<f, f, f, f, f, f, t, f, f, f>::value == true, "");
	static_assert(bksge::tmp::any_of<f, f, f, f, f, f, f, t, f, f>::value == true, "");
	static_assert(bksge::tmp::any_of<f, f, f, f, f, f, f, f, t, f>::value == true, "");
	static_assert(bksge::tmp::any_of<f, f, f, f, f, f, f, f, f, t>::value == true, "");
	static_assert(bksge::tmp::any_of<f, f, f, f, f, f, f, f, f, f>::value == false, "");
}
