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

using T = bksge::true_type;
using F = bksge::false_type;

static_assert( bksge::conjunction<>::value, "");

static_assert( bksge::conjunction<T>::value, "");
static_assert(!bksge::conjunction<F>::value, "");

static_assert( bksge::conjunction<T, T>::value, "");
static_assert(!bksge::conjunction<T, F>::value, "");
static_assert(!bksge::conjunction<F, T>::value, "");
static_assert(!bksge::conjunction<F, F>::value, "");

static_assert( bksge::conjunction<T, T, T>::value, "");
static_assert(!bksge::conjunction<T, T, F>::value, "");
static_assert(!bksge::conjunction<T, F, T>::value, "");
static_assert(!bksge::conjunction<T, F, F>::value, "");
static_assert(!bksge::conjunction<F, T, T>::value, "");
static_assert(!bksge::conjunction<F, T, F>::value, "");
static_assert(!bksge::conjunction<F, F, T>::value, "");
static_assert(!bksge::conjunction<F, F, F>::value, "");

static_assert( bksge::conjunction<T, T, T, T, T, T, T, T, T, T>::value, "");
static_assert(!bksge::conjunction<F, T, T, T, T, T, T, T, T, T>::value, "");
static_assert(!bksge::conjunction<T, F, T, T, T, T, T, T, T, T>::value, "");
static_assert(!bksge::conjunction<T, T, F, T, T, T, T, T, T, T>::value, "");
static_assert(!bksge::conjunction<T, T, T, F, T, T, T, T, T, T>::value, "");
static_assert(!bksge::conjunction<T, T, T, T, F, T, T, T, T, T>::value, "");
static_assert(!bksge::conjunction<T, T, T, T, T, F, T, T, T, T>::value, "");
static_assert(!bksge::conjunction<T, T, T, T, T, T, F, T, T, T>::value, "");
static_assert(!bksge::conjunction<T, T, T, T, T, T, T, F, T, T>::value, "");
static_assert(!bksge::conjunction<T, T, T, T, T, T, T, T, F, T>::value, "");
static_assert(!bksge::conjunction<T, T, T, T, T, T, T, T, T, F>::value, "");
static_assert(!bksge::conjunction<T, F, F, F, F, F, F, F, F, F>::value, "");
static_assert(!bksge::conjunction<F, T, F, F, F, F, F, F, F, F>::value, "");
static_assert(!bksge::conjunction<F, F, T, F, F, F, F, F, F, F>::value, "");
static_assert(!bksge::conjunction<F, F, F, T, F, F, F, F, F, F>::value, "");
static_assert(!bksge::conjunction<F, F, F, F, T, F, F, F, F, F>::value, "");
static_assert(!bksge::conjunction<F, F, F, F, F, T, F, F, F, F>::value, "");
static_assert(!bksge::conjunction<F, F, F, F, F, F, T, F, F, F>::value, "");
static_assert(!bksge::conjunction<F, F, F, F, F, F, F, T, F, F>::value, "");
static_assert(!bksge::conjunction<F, F, F, F, F, F, F, F, T, F>::value, "");
static_assert(!bksge::conjunction<F, F, F, F, F, F, F, F, F, T>::value, "");
static_assert(!bksge::conjunction<F, F, F, F, F, F, F, F, F, F>::value, "");

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

}	// namespace conjunction_test

}	// namespace bksge_type_traits_test
