/**
 *	@file	unit_test_fnd_type_traits_extent.cpp
 *
 *	@brief	extent のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/type_traits/extent.hpp>
#include <gtest/gtest.h>
#include "type_traits_test_utility.hpp"

#define BKSGE_EXTENT_TEST(n, T)	\
	static_assert(n == bksge::extent<T>::value, #T)

#define BKSGE_EXTENT_TEST_2(n, T, i)	\
	static_assert(n == bksge::extent<T, i>::value, #T)

GTEST_TEST(TypeTraitsTest, ExtentTest)
{
	IntegralConstantTest<bksge::extent<int>, 0>();
	IntegralConstantTest<bksge::extent<int[2]>, 2>();
	IntegralConstantTest<bksge::extent<int[3]>, 3>();
	IntegralConstantTest<bksge::extent<int[4][5][6], 0>, 4>();
	IntegralConstantTest<bksge::extent<int[4][5][6], 1>, 5>();
	IntegralConstantTest<bksge::extent<int[4][5][6], 2>, 6>();
	IntegralConstantTest<bksge::extent<int[4][5][6], 3>, 0>();

	BKSGE_EXTENT_TEST  ( 0, int);
	BKSGE_EXTENT_TEST  ( 0, int*);
	BKSGE_EXTENT_TEST  ( 0, int&);
	BKSGE_EXTENT_TEST  ( 0, int&&);
	BKSGE_EXTENT_TEST  ( 0, int[]);
	BKSGE_EXTENT_TEST  ( 2, int[2]);
	BKSGE_EXTENT_TEST  ( 3, int[3]);
	BKSGE_EXTENT_TEST_2( 2, int[2], 0);
	BKSGE_EXTENT_TEST_2( 0, int[2], 1);
	BKSGE_EXTENT_TEST  ( 2, int[2][3]);
	BKSGE_EXTENT_TEST_2( 2, int[2][3], 0);
	BKSGE_EXTENT_TEST_2( 3, int[2][3], 1);
	BKSGE_EXTENT_TEST_2( 0, int[2][3], 2);
	BKSGE_EXTENT_TEST_2( 5, int[5][10][40], 0);
	BKSGE_EXTENT_TEST_2(10, int[5][10][40], 1);
	BKSGE_EXTENT_TEST_2(40, int[5][10][40], 2);
	BKSGE_EXTENT_TEST_2( 0, int[5][10][40], 3);
	BKSGE_EXTENT_TEST  ( 0, int(&)[2]);
	BKSGE_EXTENT_TEST  ( 0, int(&)[]);
	BKSGE_EXTENT_TEST  ( 0, int(&&)[2]);
	BKSGE_EXTENT_TEST  ( 0, int(&&)[]);

	BKSGE_EXTENT_TEST  ( 0, UDT);
	BKSGE_EXTENT_TEST  ( 0, UDT*);
	BKSGE_EXTENT_TEST  ( 0, UDT&);
	BKSGE_EXTENT_TEST  ( 0, UDT&&);
	BKSGE_EXTENT_TEST  ( 0, UDT[]);
	BKSGE_EXTENT_TEST  ( 2, UDT[2]);
	BKSGE_EXTENT_TEST  ( 3, UDT[3]);
	BKSGE_EXTENT_TEST_2( 2, UDT[2], 0);
	BKSGE_EXTENT_TEST_2( 0, UDT[2], 1);
	BKSGE_EXTENT_TEST  ( 2, UDT[2][3]);
	BKSGE_EXTENT_TEST_2( 2, UDT[2][3], 0);
	BKSGE_EXTENT_TEST_2( 3, UDT[2][3], 1);
	BKSGE_EXTENT_TEST_2( 0, UDT[2][3], 2);
	BKSGE_EXTENT_TEST_2( 5, UDT[5][10][40], 0);
	BKSGE_EXTENT_TEST_2(10, UDT[5][10][40], 1);
	BKSGE_EXTENT_TEST_2(40, UDT[5][10][40], 2);
	BKSGE_EXTENT_TEST_2( 0, UDT[5][10][40], 3);
	BKSGE_EXTENT_TEST  ( 0, UDT(&)[2]);
	BKSGE_EXTENT_TEST  ( 0, UDT(&)[]);
	BKSGE_EXTENT_TEST  ( 0, UDT(&&)[2]);
	BKSGE_EXTENT_TEST  ( 0, UDT(&&)[]);
}

#undef BKSGE_EXTENT_TEST
#undef BKSGE_EXTENT_TEST_2
