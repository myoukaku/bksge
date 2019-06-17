/**
 *	@file	unit_test_tmp_gcd.cpp
 *
 *	@brief	gcd のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/tmp/gcd.hpp>
#include <gtest/gtest.h>

namespace bksge_tmp_test
{

namespace gcd_test
{

using TmpGcdTestTypes = ::testing::Types<int, short, long, long long>;

template <typename T>
class TmpGcdTest : public ::testing::Test {};

TYPED_TEST_SUITE(TmpGcdTest, TmpGcdTestTypes);

TYPED_TEST(TmpGcdTest, GcdTest)
{
	using T = TypeParam;

#define BKSGE_GCD_TEST(m, n, x)			\
	static_assert(bksge::tmp::gcd<T,  m,  n>::value == x, ""); \
	static_assert(bksge::tmp::gcd<T,  m, -n>::value == x, ""); \
	static_assert(bksge::tmp::gcd<T, -m,  n>::value == x, ""); \
	static_assert(bksge::tmp::gcd<T, -m, -n>::value == x, "")

	{
		BKSGE_GCD_TEST( 0,  0,  0);
		BKSGE_GCD_TEST( 0,  1,  1);
		BKSGE_GCD_TEST( 0,  2,  2);
		BKSGE_GCD_TEST( 0,  3,  3);
		BKSGE_GCD_TEST( 0,  4,  4);
		BKSGE_GCD_TEST( 0,  5,  5);
		BKSGE_GCD_TEST( 0,  6,  6);
		BKSGE_GCD_TEST( 0,  7,  7);
		BKSGE_GCD_TEST( 0,  8,  8);
		BKSGE_GCD_TEST( 0,  9,  9);
		BKSGE_GCD_TEST( 0, 10, 10);

		BKSGE_GCD_TEST( 1,  0,  1);
		BKSGE_GCD_TEST( 1,  1,  1);
		BKSGE_GCD_TEST( 1,  2,  1);
		BKSGE_GCD_TEST( 1,  3,  1);
		BKSGE_GCD_TEST( 1,  4,  1);
		BKSGE_GCD_TEST( 1,  5,  1);
		BKSGE_GCD_TEST( 1,  6,  1);
		BKSGE_GCD_TEST( 1,  7,  1);
		BKSGE_GCD_TEST( 1,  8,  1);
		BKSGE_GCD_TEST( 1,  9,  1);
		BKSGE_GCD_TEST( 1, 10,  1);

		BKSGE_GCD_TEST( 2,  0,  2);
		BKSGE_GCD_TEST( 2,  1,  1);
		BKSGE_GCD_TEST( 2,  2,  2);
		BKSGE_GCD_TEST( 2,  3,  1);
		BKSGE_GCD_TEST( 2,  4,  2);
		BKSGE_GCD_TEST( 2,  5,  1);
		BKSGE_GCD_TEST( 2,  6,  2);
		BKSGE_GCD_TEST( 2,  7,  1);
		BKSGE_GCD_TEST( 2,  8,  2);
		BKSGE_GCD_TEST( 2,  9,  1);
		BKSGE_GCD_TEST( 2, 10,  2);

		BKSGE_GCD_TEST( 3,  0,  3);
		BKSGE_GCD_TEST( 3,  1,  1);
		BKSGE_GCD_TEST( 3,  2,  1);
		BKSGE_GCD_TEST( 3,  3,  3);
		BKSGE_GCD_TEST( 3,  4,  1);
		BKSGE_GCD_TEST( 3,  5,  1);
		BKSGE_GCD_TEST( 3,  6,  3);
		BKSGE_GCD_TEST( 3,  7,  1);
		BKSGE_GCD_TEST( 3,  8,  1);
		BKSGE_GCD_TEST( 3,  9,  3);
		BKSGE_GCD_TEST( 3, 10,  1);

		BKSGE_GCD_TEST( 8,  0,  8);
		BKSGE_GCD_TEST( 8,  1,  1);
		BKSGE_GCD_TEST( 8,  2,  2);
		BKSGE_GCD_TEST( 8,  3,  1);
		BKSGE_GCD_TEST( 8,  4,  4);
		BKSGE_GCD_TEST( 8,  5,  1);
		BKSGE_GCD_TEST( 8,  6,  2);
		BKSGE_GCD_TEST( 8,  7,  1);
		BKSGE_GCD_TEST( 8,  8,  8);
		BKSGE_GCD_TEST( 8,  9,  1);
		BKSGE_GCD_TEST( 8, 10,  2);

		BKSGE_GCD_TEST(60,  0, 60);
		BKSGE_GCD_TEST(60,  1,  1);
		BKSGE_GCD_TEST(60,  2,  2);
		BKSGE_GCD_TEST(60,  3,  3);
		BKSGE_GCD_TEST(60,  4,  4);
		BKSGE_GCD_TEST(60,  5,  5);
		BKSGE_GCD_TEST(60,  6,  6);
		BKSGE_GCD_TEST(60,  7,  1);
		BKSGE_GCD_TEST(60,  8,  4);
		BKSGE_GCD_TEST(60,  9,  3);
		BKSGE_GCD_TEST(60, 10, 10);
		BKSGE_GCD_TEST(60, 11,  1);
		BKSGE_GCD_TEST(60, 12, 12);
		BKSGE_GCD_TEST(60, 13,  1);
		BKSGE_GCD_TEST(60, 14,  2);
		BKSGE_GCD_TEST(60, 15, 15);
	}

#undef BKSGE_GCD_TEST
}

}	// namespace gcd_test

}	// namespace bksge_tmp_test
