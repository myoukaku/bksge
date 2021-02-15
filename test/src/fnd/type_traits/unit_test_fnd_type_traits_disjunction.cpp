/**
 *	@file	unit_test_fnd_type_traits_disjunction.cpp
 *
 *	@brief	disjunction のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/type_traits/disjunction.hpp>
#include <bksge/fnd/type_traits/bool_constant.hpp>
#include <bksge/fnd/type_traits/is_unsigned.hpp>
#include <bksge/fnd/config.hpp>
#include <gtest/gtest.h>

namespace bksge_type_traits_test
{

namespace disjunction_test
{

static_assert(!bksge::disjunction<>::value, "");

static_assert( bksge::disjunction<bksge::is_unsigned<unsigned>>::value, "");
static_assert(!bksge::disjunction<bksge::is_unsigned<float>>::value, "");

static_assert(bksge::disjunction<
	bksge::is_unsigned<unsigned char>,
	bksge::is_unsigned<unsigned int>
>::value, "");

static_assert(bksge::disjunction<
	bksge::is_unsigned<float>,
	bksge::is_unsigned<unsigned int>
>::value, "");

static_assert(bksge::disjunction<
	bksge::is_unsigned<unsigned char>,
	bksge::is_unsigned<int>
>::value, "");

static_assert(!bksge::disjunction<
	bksge::is_unsigned<char>,
	bksge::is_unsigned<int>
>::value, "");

static_assert(bksge::disjunction<
	bksge::is_unsigned<unsigned char>,
	bksge::is_unsigned<unsigned short>,
	bksge::is_unsigned<unsigned int>
>::value, "");

static_assert(bksge::disjunction<
	bksge::is_unsigned<char>,
	bksge::is_unsigned<unsigned short>,
	bksge::is_unsigned<unsigned int>
>::value, "");

static_assert(bksge::disjunction<
	bksge::is_unsigned<unsigned char>,
	bksge::is_unsigned<short>,
	bksge::is_unsigned<unsigned int>
>::value, "");

static_assert(bksge::disjunction<
	bksge::is_unsigned<unsigned char>,
	bksge::is_unsigned<unsigned short>,
	bksge::is_unsigned<int>
>::value, "");

static_assert(!bksge::disjunction<
	bksge::is_unsigned<char>,
	bksge::is_unsigned<short>,
	bksge::is_unsigned<int>
>::value, "");

static_assert(bksge::disjunction<
	bksge::is_unsigned<unsigned char>,
	bksge::is_unsigned<unsigned short>,
	bksge::is_unsigned<unsigned int>,
	bksge::is_unsigned<unsigned long>
>::value, "");

static_assert(bksge::disjunction<
	bksge::is_unsigned<unsigned char>,
	bksge::is_unsigned<unsigned short>,
	bksge::is_unsigned<unsigned int>,
	bksge::is_unsigned<long>
>::value, "");

static_assert(!bksge::disjunction<
	bksge::is_unsigned<char>,
	bksge::is_unsigned<short>,
	bksge::is_unsigned<int>,
	bksge::is_unsigned<long>
>::value, "");

#if defined(BKSGE_HAS_CXX14_VARIABLE_TEMPLATES)

#define BKSGE_DISJUNCTION_TEST(x, ...)	\
	static_assert(bksge::disjunction_v<__VA_ARGS__>      == x, "");	\
	static_assert(bksge::disjunction<__VA_ARGS__>::value == x, "");	\
	static_assert(bksge::disjunction<__VA_ARGS__>()      == x, "")

#else

#define BKSGE_DISJUNCTION_TEST(x, ...)	\
	static_assert(bksge::disjunction<__VA_ARGS__>::value == x, "");	\
	static_assert(bksge::disjunction<__VA_ARGS__>()      == x, "")

#endif

using T = bksge::true_type;
using F = bksge::false_type;

BKSGE_DISJUNCTION_TEST(false, /**/);

BKSGE_DISJUNCTION_TEST(true,  T);
BKSGE_DISJUNCTION_TEST(false, F);

BKSGE_DISJUNCTION_TEST(true,  T, T);
BKSGE_DISJUNCTION_TEST(true,  T, F);
BKSGE_DISJUNCTION_TEST(true,  F, T);
BKSGE_DISJUNCTION_TEST(false, F, F);

BKSGE_DISJUNCTION_TEST(true,  T, T, T);
BKSGE_DISJUNCTION_TEST(true,  T, T, F);
BKSGE_DISJUNCTION_TEST(true,  T, F, T);
BKSGE_DISJUNCTION_TEST(true,  T, F, F);
BKSGE_DISJUNCTION_TEST(true,  F, T, T);
BKSGE_DISJUNCTION_TEST(true,  F, T, F);
BKSGE_DISJUNCTION_TEST(true,  F, F, T);
BKSGE_DISJUNCTION_TEST(false, F, F, F);

BKSGE_DISJUNCTION_TEST(true,  T, T, T, T, T, T, T, T, T, T);
BKSGE_DISJUNCTION_TEST(true,  F, T, T, T, T, T, T, T, T, T);
BKSGE_DISJUNCTION_TEST(true,  T, F, T, T, T, T, T, T, T, T);
BKSGE_DISJUNCTION_TEST(true,  T, T, F, T, T, T, T, T, T, T);
BKSGE_DISJUNCTION_TEST(true,  T, T, T, F, T, T, T, T, T, T);
BKSGE_DISJUNCTION_TEST(true,  T, T, T, T, F, T, T, T, T, T);
BKSGE_DISJUNCTION_TEST(true,  T, T, T, T, T, F, T, T, T, T);
BKSGE_DISJUNCTION_TEST(true,  T, T, T, T, T, T, F, T, T, T);
BKSGE_DISJUNCTION_TEST(true,  T, T, T, T, T, T, T, F, T, T);
BKSGE_DISJUNCTION_TEST(true,  T, T, T, T, T, T, T, T, F, T);
BKSGE_DISJUNCTION_TEST(true,  T, T, T, T, T, T, T, T, T, F);
BKSGE_DISJUNCTION_TEST(true,  T, F, F, F, F, F, F, F, F, F);
BKSGE_DISJUNCTION_TEST(true,  F, T, F, F, F, F, F, F, F, F);
BKSGE_DISJUNCTION_TEST(true,  F, F, T, F, F, F, F, F, F, F);
BKSGE_DISJUNCTION_TEST(true,  F, F, F, T, F, F, F, F, F, F);
BKSGE_DISJUNCTION_TEST(true,  F, F, F, F, T, F, F, F, F, F);
BKSGE_DISJUNCTION_TEST(true,  F, F, F, F, F, T, F, F, F, F);
BKSGE_DISJUNCTION_TEST(true,  F, F, F, F, F, F, T, F, F, F);
BKSGE_DISJUNCTION_TEST(true,  F, F, F, F, F, F, F, T, F, F);
BKSGE_DISJUNCTION_TEST(true,  F, F, F, F, F, F, F, F, T, F);
BKSGE_DISJUNCTION_TEST(true,  F, F, F, F, F, F, F, F, F, T);
BKSGE_DISJUNCTION_TEST(false, F, F, F, F, F, F, F, F, F, F);

static_assert(
	bksge::disjunction<
		// 0
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		// 100
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
#if 0
		// 200
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		// 300
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		// 400
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		// 500
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		// 600
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		// 700
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		// 800
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		// 900
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
#endif

		T
	>::value, "");

static_assert(
	!bksge::disjunction<
		// 0
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		// 100
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
#if 0
		// 200
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		// 300
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		// 400
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		// 500
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		// 600
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		// 700
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		// 800
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		// 900
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
		F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F,
#endif

		F
	>::value, "");

#undef BKSGE_DISJUNCTION_TEST

}	// namespace disjunction_test

}	// namespace bksge_type_traits_test
