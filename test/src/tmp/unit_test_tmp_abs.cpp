/**
 *	@file	unit_test_tmp_abs.cpp
 *
 *	@brief	abs のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/tmp/abs.hpp>
#include <gtest/gtest.h>

namespace bksge_tmp_test
{

namespace abs_test
{

using TmpAbsTestTypes = ::testing::Types<int, short, long, long long>;

template <typename T>
class TmpAbsTest : public ::testing::Test {};

TYPED_TEST_SUITE(TmpAbsTest, TmpAbsTestTypes);

TYPED_TEST(TmpAbsTest, AbsTest)
{
	using T = TypeParam;

	static_assert(bksge::tmp::abs<T,   0>::value ==  0, "");
	static_assert(bksge::tmp::abs<T,   1>::value ==  1, "");
	static_assert(bksge::tmp::abs<T,   2>::value ==  2, "");
	static_assert(bksge::tmp::abs<T,  42>::value == 42, "");
	static_assert(bksge::tmp::abs<T,  -1>::value ==  1, "");
	static_assert(bksge::tmp::abs<T,  -2>::value ==  2, "");
	static_assert(bksge::tmp::abs<T, -42>::value == 42, "");
}

}	// namespace abs_test

}	// namespace bksge_tmp_test
