/**
 *	@file	unit_test_fnd_tmp_lcm.cpp
 *
 *	@brief	lcm のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/tmp/lcm.hpp>
#include <gtest/gtest.h>

namespace bksge_tmp_test
{

namespace lcm_test
{

using TmpLcmTestTypes = ::testing::Types<int, short, long, long long>;

template <typename T>
class TmpLcmTest : public ::testing::Test {};

TYPED_TEST_SUITE(TmpLcmTest, TmpLcmTestTypes);

TYPED_TEST(TmpLcmTest, LcmTest)
{
	using T = TypeParam;

#define BKSGE_LCM_TEST(m, n, x)			\
	static_assert(bksge::tmp::lcm<T,  m,  n>::value == x, ""); \
	static_assert(bksge::tmp::lcm<T,  m, -n>::value == x, ""); \
	static_assert(bksge::tmp::lcm<T, -m,  n>::value == x, ""); \
	static_assert(bksge::tmp::lcm<T, -m, -n>::value == x, "")

	BKSGE_LCM_TEST(  0,   1,    0);
	BKSGE_LCM_TEST(  1,   0,    0);
	BKSGE_LCM_TEST(  0,   0,    0);
	BKSGE_LCM_TEST(  1,  42,   42);
	BKSGE_LCM_TEST( 42,   1,   42);
	BKSGE_LCM_TEST(  1,   1,    1);
	BKSGE_LCM_TEST( 24,  32,   96);
	BKSGE_LCM_TEST( 24,  33,  264);
	BKSGE_LCM_TEST( 24,  34,  408);
	BKSGE_LCM_TEST( 24,  35,  840);
	BKSGE_LCM_TEST( 24,  36,   72);
	BKSGE_LCM_TEST( 25,  36,  900);
	BKSGE_LCM_TEST( 26,  36,  468);
	BKSGE_LCM_TEST( 27,  36,  108);
	BKSGE_LCM_TEST( 28,  36,  252);
	BKSGE_LCM_TEST(108, 315, 3780);

#undef BKSGE_LCM_TEST
}

}	// namespace lcm_test

}	// namespace bksge_tmp_test
