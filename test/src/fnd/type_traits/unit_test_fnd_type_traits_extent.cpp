/**
 *	@file	unit_test_fnd_type_traits_extent.cpp
 *
 *	@brief	extent のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/type_traits/extent.hpp>
#include <bksge/fnd/config.hpp>
#include <gtest/gtest.h>
#include "type_traits_test_utility.hpp"

namespace type_traits_test
{

namespace alignment_of_test
{

#if defined(BKSGE_HAS_CXX14_VARIABLE_TEMPLATES)

#define BKSGE_EXTENT_TEST(n, T)	\
	static_assert(n == bksge::extent_v<T>,      #T);	\
	static_assert(n == bksge::extent<T>::value, #T);	\
	static_assert(n == bksge::extent<T>(),      #T)

#define BKSGE_EXTENT_TEST_2(n, T, i)	\
	static_assert(n == bksge::extent_v<T, i>,      #T);	\
	static_assert(n == bksge::extent<T, i>::value, #T);	\
	static_assert(n == bksge::extent<T, i>(),      #T)

#else

#define BKSGE_EXTENT_TEST(n, T)	\
	static_assert(n == bksge::extent<T>::value, #T);	\
	static_assert(n == bksge::extent<T>(),      #T)

#define BKSGE_EXTENT_TEST_2(n, T, i)	\
	static_assert(n == bksge::extent<T, i>::value, #T);	\
	static_assert(n == bksge::extent<T, i>(),      #T)

#endif

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

#undef BKSGE_EXTENT_TEST
#undef BKSGE_EXTENT_TEST_2

}	// namespace alignment_of_test

}	// namespace type_traits_test
