/**
 *	@file	unit_test_fnd_type_traits_nth.cpp
 *
 *	@brief	nth のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/type_traits/nth.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <gtest/gtest.h>

#define BKSGE_TT_NTH_TEST(N, T, ...)	\
	static_assert(bksge::is_same<T,	bksge::nth<N, __VA_ARGS__>::type>::value, "");	\
	static_assert(bksge::is_same<T,	bksge::nth_t<N, __VA_ARGS__>>::value, "")

BKSGE_TT_NTH_TEST(0, char,   char, int, float, double);
BKSGE_TT_NTH_TEST(1, int,    char, int, float, double);
BKSGE_TT_NTH_TEST(2, float,  char, int, float, double);
BKSGE_TT_NTH_TEST(3, double, char, int, float, double);

BKSGE_TT_NTH_TEST(0, int,          int, const int, volatile int, int*, const int*, int&, const int&);
BKSGE_TT_NTH_TEST(1, const int,    int, const int, volatile int, int*, const int*, int&, const int&);
BKSGE_TT_NTH_TEST(2, volatile int, int, const int, volatile int, int*, const int*, int&, const int&);
BKSGE_TT_NTH_TEST(3, int*,         int, const int, volatile int, int*, const int*, int&, const int&);
BKSGE_TT_NTH_TEST(4, const int*,   int, const int, volatile int, int*, const int*, int&, const int&);
BKSGE_TT_NTH_TEST(5, int&,         int, const int, volatile int, int*, const int*, int&, const int&);
BKSGE_TT_NTH_TEST(6, const int&,   int, const int, volatile int, int*, const int*, int&, const int&);

#define BKSGE_100_INTS	\
			int, int, int, int, int, int, int, int, int, int,	\
			int, int, int, int, int, int, int, int, int, int,	\
			int, int, int, int, int, int, int, int, int, int,	\
			int, int, int, int, int, int, int, int, int, int,	\
			int, int, int, int, int, int, int, int, int, int,	\
			int, int, int, int, int, int, int, int, int, int,	\
			int, int, int, int, int, int, int, int, int, int,	\
			int, int, int, int, int, int, int, int, int, int,	\
			int, int, int, int, int, int, int, int, int, int,	\
			int, int, int, int, int, int, int, int, int, int

#define BKSGE_1000_INTS		\
	BKSGE_100_INTS, BKSGE_100_INTS, BKSGE_100_INTS, BKSGE_100_INTS, BKSGE_100_INTS, BKSGE_100_INTS, BKSGE_100_INTS, BKSGE_100_INTS, BKSGE_100_INTS, BKSGE_100_INTS

// 101 parameters
BKSGE_TT_NTH_TEST(  0, int,  BKSGE_100_INTS, char);
BKSGE_TT_NTH_TEST(  1, int,  BKSGE_100_INTS, char);
BKSGE_TT_NTH_TEST(  2, int,  BKSGE_100_INTS, char);
BKSGE_TT_NTH_TEST(  3, int,  BKSGE_100_INTS, char);
BKSGE_TT_NTH_TEST(  4, int,  BKSGE_100_INTS, char);
BKSGE_TT_NTH_TEST(  5, int,  BKSGE_100_INTS, char);
BKSGE_TT_NTH_TEST(  6, int,  BKSGE_100_INTS, char);
BKSGE_TT_NTH_TEST(  7, int,  BKSGE_100_INTS, char);
BKSGE_TT_NTH_TEST(  8, int,  BKSGE_100_INTS, char);
BKSGE_TT_NTH_TEST(  9, int,  BKSGE_100_INTS, char);
BKSGE_TT_NTH_TEST( 99, int,  BKSGE_100_INTS, char);
BKSGE_TT_NTH_TEST(100, char, BKSGE_100_INTS, char);

// 201 parameters
BKSGE_TT_NTH_TEST(  0, int,  BKSGE_100_INTS, BKSGE_100_INTS, char);
BKSGE_TT_NTH_TEST(  1, int,  BKSGE_100_INTS, BKSGE_100_INTS, char);
BKSGE_TT_NTH_TEST(  2, int,  BKSGE_100_INTS, BKSGE_100_INTS, char);
BKSGE_TT_NTH_TEST(  3, int,  BKSGE_100_INTS, BKSGE_100_INTS, char);
BKSGE_TT_NTH_TEST(  4, int,  BKSGE_100_INTS, BKSGE_100_INTS, char);
BKSGE_TT_NTH_TEST(  5, int,  BKSGE_100_INTS, BKSGE_100_INTS, char);
BKSGE_TT_NTH_TEST(  6, int,  BKSGE_100_INTS, BKSGE_100_INTS, char);
BKSGE_TT_NTH_TEST(  7, int,  BKSGE_100_INTS, BKSGE_100_INTS, char);
BKSGE_TT_NTH_TEST(  8, int,  BKSGE_100_INTS, BKSGE_100_INTS, char);
BKSGE_TT_NTH_TEST(  9, int,  BKSGE_100_INTS, BKSGE_100_INTS, char);
BKSGE_TT_NTH_TEST( 99, int,  BKSGE_100_INTS, BKSGE_100_INTS, char);
BKSGE_TT_NTH_TEST(100, int,  BKSGE_100_INTS, BKSGE_100_INTS, char);
BKSGE_TT_NTH_TEST(101, int,  BKSGE_100_INTS, BKSGE_100_INTS, char);
BKSGE_TT_NTH_TEST(199, int,  BKSGE_100_INTS, BKSGE_100_INTS, char);
BKSGE_TT_NTH_TEST(200, char, BKSGE_100_INTS, BKSGE_100_INTS, char);

// 1001 parameters
BKSGE_TT_NTH_TEST(   0, int,  BKSGE_1000_INTS, char);
BKSGE_TT_NTH_TEST( 100, int,  BKSGE_1000_INTS, char);
BKSGE_TT_NTH_TEST( 200, int,  BKSGE_1000_INTS, char);
BKSGE_TT_NTH_TEST( 300, int,  BKSGE_1000_INTS, char);
BKSGE_TT_NTH_TEST( 400, int,  BKSGE_1000_INTS, char);
BKSGE_TT_NTH_TEST( 500, int,  BKSGE_1000_INTS, char);
BKSGE_TT_NTH_TEST( 600, int,  BKSGE_1000_INTS, char);
BKSGE_TT_NTH_TEST( 700, int,  BKSGE_1000_INTS, char);
BKSGE_TT_NTH_TEST( 800, int,  BKSGE_1000_INTS, char);
BKSGE_TT_NTH_TEST( 900, int,  BKSGE_1000_INTS, char);
BKSGE_TT_NTH_TEST(1000, char, BKSGE_1000_INTS, char);

// 2001 parameters
BKSGE_TT_NTH_TEST(   0, int,  BKSGE_1000_INTS, BKSGE_1000_INTS, char);
BKSGE_TT_NTH_TEST( 100, int,  BKSGE_1000_INTS, BKSGE_1000_INTS, char);
BKSGE_TT_NTH_TEST( 200, int,  BKSGE_1000_INTS, BKSGE_1000_INTS, char);
BKSGE_TT_NTH_TEST( 300, int,  BKSGE_1000_INTS, BKSGE_1000_INTS, char);
BKSGE_TT_NTH_TEST( 400, int,  BKSGE_1000_INTS, BKSGE_1000_INTS, char);
BKSGE_TT_NTH_TEST( 500, int,  BKSGE_1000_INTS, BKSGE_1000_INTS, char);
BKSGE_TT_NTH_TEST( 600, int,  BKSGE_1000_INTS, BKSGE_1000_INTS, char);
BKSGE_TT_NTH_TEST( 700, int,  BKSGE_1000_INTS, BKSGE_1000_INTS, char);
BKSGE_TT_NTH_TEST( 800, int,  BKSGE_1000_INTS, BKSGE_1000_INTS, char);
BKSGE_TT_NTH_TEST( 900, int,  BKSGE_1000_INTS, BKSGE_1000_INTS, char);
BKSGE_TT_NTH_TEST(1000, int,  BKSGE_1000_INTS, BKSGE_1000_INTS, char);
BKSGE_TT_NTH_TEST(1999, int,  BKSGE_1000_INTS, BKSGE_1000_INTS, char);
BKSGE_TT_NTH_TEST(2000, char, BKSGE_1000_INTS, BKSGE_1000_INTS, char);

#undef BKSGE_100_INTS
#undef BKSGE_1000_INTS
#undef BKSGE_TT_NTH_TEST
