/**
 *	@file	unit_test_fnd_type_traits_conjunction.cpp
 *
 *	@brief	conjunction のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/type_traits/conjunction.hpp>
#include <bksge/fnd/type_traits/bool_constant.hpp>
#include <bksge/fnd/type_traits/is_unsigned.hpp>
#include <bksge/fnd/config.hpp>
#include <gtest/gtest.h>

namespace bksge_type_traits_test
{

namespace conjunction_test
{

static_assert( bksge::conjunction<>::value, "");

static_assert( bksge::conjunction<bksge::is_unsigned<unsigned>>::value, "");
static_assert(!bksge::conjunction<bksge::is_unsigned<float>>::value, "");

static_assert(bksge::conjunction<
	bksge::is_unsigned<unsigned char>,
	bksge::is_unsigned<unsigned int>
>::value, "");

static_assert(!bksge::conjunction<
	bksge::is_unsigned<float>,
	bksge::is_unsigned<unsigned int>
>::value, "");

static_assert(!bksge::conjunction<
	bksge::is_unsigned<unsigned char>,
	bksge::is_unsigned<int>
>::value, "");

static_assert(!bksge::conjunction<
	bksge::is_unsigned<char>,
	bksge::is_unsigned<int>
>::value, "");

static_assert(bksge::conjunction<
	bksge::is_unsigned<unsigned char>,
	bksge::is_unsigned<unsigned short>,
	bksge::is_unsigned<unsigned int>
>::value, "");

static_assert(!bksge::conjunction<
	bksge::is_unsigned<char>,
	bksge::is_unsigned<unsigned short>,
	bksge::is_unsigned<unsigned int>
>::value, "");

static_assert(!bksge::conjunction<
	bksge::is_unsigned<unsigned char>,
	bksge::is_unsigned<short>,
	bksge::is_unsigned<unsigned int>
>::value, "");

static_assert(!bksge::conjunction<
	bksge::is_unsigned<unsigned char>,
	bksge::is_unsigned<unsigned short>,
	bksge::is_unsigned<int>
>::value, "");

static_assert(!bksge::conjunction<
	bksge::is_unsigned<char>,
	bksge::is_unsigned<short>,
	bksge::is_unsigned<int>
>::value, "");

static_assert(bksge::conjunction<
	bksge::is_unsigned<unsigned char>,
	bksge::is_unsigned<unsigned short>,
	bksge::is_unsigned<unsigned int>,
	bksge::is_unsigned<unsigned long>
>::value, "");

static_assert(!bksge::conjunction<
	bksge::is_unsigned<unsigned char>,
	bksge::is_unsigned<unsigned short>,
	bksge::is_unsigned<unsigned int>,
	bksge::is_unsigned<long>
>::value, "");

static_assert(!bksge::conjunction<
	bksge::is_unsigned<char>,
	bksge::is_unsigned<short>,
	bksge::is_unsigned<int>,
	bksge::is_unsigned<long>
>::value, "");

#if defined(BKSGE_HAS_CXX14_VARIABLE_TEMPLATES)

#define BKSGE_CONJUNCTION_TEST(x, ...)	\
	static_assert(bksge::conjunction_v<__VA_ARGS__>      == x, "");	\
	static_assert(bksge::conjunction<__VA_ARGS__>::value == x, "");	\
	static_assert(bksge::conjunction<__VA_ARGS__>()      == x, "")

#else

#define BKSGE_CONJUNCTION_TEST(x, ...)	\
	static_assert(bksge::conjunction<__VA_ARGS__>::value == x, "");	\
	static_assert(bksge::conjunction<__VA_ARGS__>()      == x, "")

#endif

using T = bksge::true_type;
using F = bksge::false_type;

BKSGE_CONJUNCTION_TEST(true, /**/);

BKSGE_CONJUNCTION_TEST(true,  T);
BKSGE_CONJUNCTION_TEST(false, F);

BKSGE_CONJUNCTION_TEST(true,  T, T);
BKSGE_CONJUNCTION_TEST(false, T, F);
BKSGE_CONJUNCTION_TEST(false, F, T);
BKSGE_CONJUNCTION_TEST(false, F, F);

BKSGE_CONJUNCTION_TEST(true,  T, T, T);
BKSGE_CONJUNCTION_TEST(false, T, T, F);
BKSGE_CONJUNCTION_TEST(false, T, F, T);
BKSGE_CONJUNCTION_TEST(false, T, F, F);
BKSGE_CONJUNCTION_TEST(false, F, T, T);
BKSGE_CONJUNCTION_TEST(false, F, T, F);
BKSGE_CONJUNCTION_TEST(false, F, F, T);
BKSGE_CONJUNCTION_TEST(false, F, F, F);

BKSGE_CONJUNCTION_TEST(true,  T, T, T, T, T, T, T, T, T, T);
BKSGE_CONJUNCTION_TEST(false, F, T, T, T, T, T, T, T, T, T);
BKSGE_CONJUNCTION_TEST(false, T, F, T, T, T, T, T, T, T, T);
BKSGE_CONJUNCTION_TEST(false, T, T, F, T, T, T, T, T, T, T);
BKSGE_CONJUNCTION_TEST(false, T, T, T, F, T, T, T, T, T, T);
BKSGE_CONJUNCTION_TEST(false, T, T, T, T, F, T, T, T, T, T);
BKSGE_CONJUNCTION_TEST(false, T, T, T, T, T, F, T, T, T, T);
BKSGE_CONJUNCTION_TEST(false, T, T, T, T, T, T, F, T, T, T);
BKSGE_CONJUNCTION_TEST(false, T, T, T, T, T, T, T, F, T, T);
BKSGE_CONJUNCTION_TEST(false, T, T, T, T, T, T, T, T, F, T);
BKSGE_CONJUNCTION_TEST(false, T, T, T, T, T, T, T, T, T, F);
BKSGE_CONJUNCTION_TEST(false, T, F, F, F, F, F, F, F, F, F);
BKSGE_CONJUNCTION_TEST(false, F, T, F, F, F, F, F, F, F, F);
BKSGE_CONJUNCTION_TEST(false, F, F, T, F, F, F, F, F, F, F);
BKSGE_CONJUNCTION_TEST(false, F, F, F, T, F, F, F, F, F, F);
BKSGE_CONJUNCTION_TEST(false, F, F, F, F, T, F, F, F, F, F);
BKSGE_CONJUNCTION_TEST(false, F, F, F, F, F, T, F, F, F, F);
BKSGE_CONJUNCTION_TEST(false, F, F, F, F, F, F, T, F, F, F);
BKSGE_CONJUNCTION_TEST(false, F, F, F, F, F, F, F, T, F, F);
BKSGE_CONJUNCTION_TEST(false, F, F, F, F, F, F, F, F, T, F);
BKSGE_CONJUNCTION_TEST(false, F, F, F, F, F, F, F, F, F, T);
BKSGE_CONJUNCTION_TEST(false, F, F, F, F, F, F, F, F, F, F);

static_assert(
	bksge::conjunction<
		// 0
		T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T,
		T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T,
		T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T,
		T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T,
		T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T,
		// 100
		T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T,
		T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T,
		T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T,
		T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T,
		T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T,
#if 0
		// 200
		T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T,
		T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T,
		T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T,
		T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T,
		T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T,
		// 300
		T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T,
		T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T,
		T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T,
		T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T,
		T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T,
		// 400
		T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T,
		T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T,
		T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T,
		T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T,
		T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T,
		// 500
		T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T,
		T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T,
		T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T,
		T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T,
		T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T,
		// 600
		T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T,
		T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T,
		T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T,
		T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T,
		T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T,
		// 700
		T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T,
		T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T,
		T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T,
		T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T,
		T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T,
		// 800
		T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T,
		T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T,
		T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T,
		T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T,
		T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T,
		// 900
		T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T,
		T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T,
		T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T,
		T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T,
		T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T,
#endif

		T
	>::value, "");

static_assert(
	!bksge::conjunction<
		// 0
		T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T,
		T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T,
		T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T,
		T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T,
		T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T,
		// 100
		T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T,
		T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T,
		T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T,
		T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T,
		T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T,
#if 0
		// 200
		T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T,
		T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T,
		T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T,
		T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T,
		T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T,
		// 300
		T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T,
		T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T,
		T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T,
		T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T,
		T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T,
		// 400
		T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T,
		T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T,
		T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T,
		T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T,
		T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T,
		// 500
		T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T,
		T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T,
		T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T,
		T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T,
		T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T,
		// 600
		T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T,
		T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T,
		T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T,
		T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T,
		T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T,
		// 700
		T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T,
		T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T,
		T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T,
		T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T,
		T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T,
		// 800
		T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T,
		T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T,
		T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T,
		T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T,
		T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T,
		// 900
		T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T,
		T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T,
		T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T,
		T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T,
		T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T, T,
#endif

		F
	>::value, "");

#undef BKSGE_CONJUNCTION_TEST

}	// namespace conjunction_test

}	// namespace bksge_type_traits_test
