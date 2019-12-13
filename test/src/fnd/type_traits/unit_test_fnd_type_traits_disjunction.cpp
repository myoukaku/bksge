/**
 *	@file	unit_test_fnd_type_traits_disjunction.cpp
 *
 *	@brief	disjunction のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/type_traits/disjunction.hpp>
#include <gtest/gtest.h>
#include <type_traits>

GTEST_TEST(TypeTraitsTest, DisjunctionTest)
{
	static_assert(!bksge::disjunction<>::value, "");

	static_assert( bksge::disjunction<std::is_unsigned<unsigned>>::value, "");
	static_assert(!bksge::disjunction<std::is_unsigned<float>>::value, "");

	static_assert(bksge::disjunction<
		std::is_unsigned<unsigned char>,
		std::is_unsigned<unsigned int>
	>::value, "");

	static_assert(bksge::disjunction<
		std::is_unsigned<float>,
		std::is_unsigned<unsigned int>
	>::value, "");

	static_assert(bksge::disjunction<
		std::is_unsigned<unsigned char>,
		std::is_unsigned<int>
	>::value, "");

	static_assert(!bksge::disjunction<
		std::is_unsigned<char>,
		std::is_unsigned<int>
	>::value, "");

	static_assert(bksge::disjunction<
		std::is_unsigned<unsigned char>,
		std::is_unsigned<unsigned short>,
		std::is_unsigned<unsigned int>
	>::value, "");

	static_assert(bksge::disjunction<
		std::is_unsigned<char>,
		std::is_unsigned<unsigned short>,
		std::is_unsigned<unsigned int>
	>::value, "");

	static_assert(bksge::disjunction<
		std::is_unsigned<unsigned char>,
		std::is_unsigned<short>,
		std::is_unsigned<unsigned int>
	>::value, "");

	static_assert(bksge::disjunction<
		std::is_unsigned<unsigned char>,
		std::is_unsigned<unsigned short>,
		std::is_unsigned<int>
	>::value, "");

	static_assert(!bksge::disjunction<
		std::is_unsigned<char>,
		std::is_unsigned<short>,
		std::is_unsigned<int>
	>::value, "");

	static_assert(bksge::disjunction<
		std::is_unsigned<unsigned char>,
		std::is_unsigned<unsigned short>,
		std::is_unsigned<unsigned int>,
		std::is_unsigned<unsigned long>
	>::value, "");

	static_assert(bksge::disjunction<
		std::is_unsigned<unsigned char>,
		std::is_unsigned<unsigned short>,
		std::is_unsigned<unsigned int>,
		std::is_unsigned<long>
	>::value, "");

	static_assert(!bksge::disjunction<
		std::is_unsigned<char>,
		std::is_unsigned<short>,
		std::is_unsigned<int>,
		std::is_unsigned<long>
	>::value, "");

	using T = std::true_type;
	using F = std::false_type;

	static_assert(!bksge::disjunction<>::value, "");

	static_assert( bksge::disjunction<T>::value, "");
	static_assert(!bksge::disjunction<F>::value, "");

	static_assert( bksge::disjunction<T, T>::value, "");
	static_assert( bksge::disjunction<T, F>::value, "");
	static_assert( bksge::disjunction<F, T>::value, "");
	static_assert(!bksge::disjunction<F, F>::value, "");

	static_assert( bksge::disjunction<T, T, T>::value, "");
	static_assert( bksge::disjunction<T, T, F>::value, "");
	static_assert( bksge::disjunction<T, F, T>::value, "");
	static_assert( bksge::disjunction<T, F, F>::value, "");
	static_assert( bksge::disjunction<F, T, T>::value, "");
	static_assert( bksge::disjunction<F, T, F>::value, "");
	static_assert( bksge::disjunction<F, F, T>::value, "");
	static_assert(!bksge::disjunction<F, F, F>::value, "");

	static_assert( bksge::disjunction<T, T, T, T, T, T, T, T, T, T>::value, "");
	static_assert( bksge::disjunction<F, T, T, T, T, T, T, T, T, T>::value, "");
	static_assert( bksge::disjunction<T, F, T, T, T, T, T, T, T, T>::value, "");
	static_assert( bksge::disjunction<T, T, F, T, T, T, T, T, T, T>::value, "");
	static_assert( bksge::disjunction<T, T, T, F, T, T, T, T, T, T>::value, "");
	static_assert( bksge::disjunction<T, T, T, T, F, T, T, T, T, T>::value, "");
	static_assert( bksge::disjunction<T, T, T, T, T, F, T, T, T, T>::value, "");
	static_assert( bksge::disjunction<T, T, T, T, T, T, F, T, T, T>::value, "");
	static_assert( bksge::disjunction<T, T, T, T, T, T, T, F, T, T>::value, "");
	static_assert( bksge::disjunction<T, T, T, T, T, T, T, T, F, T>::value, "");
	static_assert( bksge::disjunction<T, T, T, T, T, T, T, T, T, F>::value, "");
	static_assert( bksge::disjunction<T, F, F, F, F, F, F, F, F, F>::value, "");
	static_assert( bksge::disjunction<F, T, F, F, F, F, F, F, F, F>::value, "");
	static_assert( bksge::disjunction<F, F, T, F, F, F, F, F, F, F>::value, "");
	static_assert( bksge::disjunction<F, F, F, T, F, F, F, F, F, F>::value, "");
	static_assert( bksge::disjunction<F, F, F, F, T, F, F, F, F, F>::value, "");
	static_assert( bksge::disjunction<F, F, F, F, F, T, F, F, F, F>::value, "");
	static_assert( bksge::disjunction<F, F, F, F, F, F, T, F, F, F>::value, "");
	static_assert( bksge::disjunction<F, F, F, F, F, F, F, T, F, F>::value, "");
	static_assert( bksge::disjunction<F, F, F, F, F, F, F, F, T, F>::value, "");
	static_assert( bksge::disjunction<F, F, F, F, F, F, F, F, F, T>::value, "");
	static_assert(!bksge::disjunction<F, F, F, F, F, F, F, F, F, F>::value, "");

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
}
