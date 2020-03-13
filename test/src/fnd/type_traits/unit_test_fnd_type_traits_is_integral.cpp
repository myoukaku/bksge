﻿/**
 *	@file	unit_test_fnd_type_traits_is_integral.cpp
 *
 *	@brief	is_integral のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/type_traits/is_integral.hpp>
#include <bksge/fnd/cstdint.hpp>
#include <cstddef>
#include <gtest/gtest.h>
#include "type_traits_test_utility.hpp"

#define BKSGE_IS_INTEGRAL_TEST(b, T)	\
	static_assert(bksge::is_integral<T>::value == b, #T)

#define BKSGE_IS_INTEGRAL_TEST_CV(b, T)	\
	BKSGE_IS_INTEGRAL_TEST(b,                T);	\
	BKSGE_IS_INTEGRAL_TEST(b, const          T);	\
	BKSGE_IS_INTEGRAL_TEST(b,       volatile T);	\
	BKSGE_IS_INTEGRAL_TEST(b, const volatile T)

GTEST_TEST(TypeTraitsTest, IsIntegralTest)
{
	IntegralConstantTest<bksge::is_integral<int>, true>();
	IntegralConstantTest<bksge::is_integral<float>, false>();

	BKSGE_IS_INTEGRAL_TEST_CV(true, bool);
	BKSGE_IS_INTEGRAL_TEST_CV(true, char);
	BKSGE_IS_INTEGRAL_TEST_CV(true, wchar_t);
	BKSGE_IS_INTEGRAL_TEST_CV(true, char16_t);
	BKSGE_IS_INTEGRAL_TEST_CV(true, char32_t);
	BKSGE_IS_INTEGRAL_TEST_CV(true, signed char);
	BKSGE_IS_INTEGRAL_TEST_CV(true, short);
	BKSGE_IS_INTEGRAL_TEST_CV(true, int);
	BKSGE_IS_INTEGRAL_TEST_CV(true, long);
	BKSGE_IS_INTEGRAL_TEST_CV(true, long long);
	BKSGE_IS_INTEGRAL_TEST_CV(true, unsigned char);
	BKSGE_IS_INTEGRAL_TEST_CV(true, unsigned short);
	BKSGE_IS_INTEGRAL_TEST_CV(true, unsigned int);
	BKSGE_IS_INTEGRAL_TEST_CV(true, unsigned long);
	BKSGE_IS_INTEGRAL_TEST_CV(true, unsigned long long);
	BKSGE_IS_INTEGRAL_TEST_CV(true, std::size_t);
	BKSGE_IS_INTEGRAL_TEST_CV(true, bksge::int8_t);
	BKSGE_IS_INTEGRAL_TEST_CV(true, bksge::int16_t);
	BKSGE_IS_INTEGRAL_TEST_CV(true, bksge::int32_t);
	BKSGE_IS_INTEGRAL_TEST_CV(true, bksge::int64_t);
	BKSGE_IS_INTEGRAL_TEST_CV(true, bksge::uint8_t);
	BKSGE_IS_INTEGRAL_TEST_CV(true, bksge::uint16_t);
	BKSGE_IS_INTEGRAL_TEST_CV(true, bksge::uint32_t);
	BKSGE_IS_INTEGRAL_TEST_CV(true, bksge::uint64_t);

	BKSGE_IS_INTEGRAL_TEST_CV(false, float);
	BKSGE_IS_INTEGRAL_TEST_CV(false, double);
	BKSGE_IS_INTEGRAL_TEST_CV(false, long double);
	BKSGE_IS_INTEGRAL_TEST_CV(false, int*);
	BKSGE_IS_INTEGRAL_TEST_CV(false, int**);
	BKSGE_IS_INTEGRAL_TEST_CV(false, int&);
	BKSGE_IS_INTEGRAL_TEST_CV(false, int&&);
	BKSGE_IS_INTEGRAL_TEST_CV(false, int[2]);
	BKSGE_IS_INTEGRAL_TEST_CV(false, int[]);
	BKSGE_IS_INTEGRAL_TEST_CV(false, int(*)[2]);
	BKSGE_IS_INTEGRAL_TEST_CV(false, int(*)[]);
	BKSGE_IS_INTEGRAL_TEST_CV(false, int(&)[2]);
	BKSGE_IS_INTEGRAL_TEST_CV(false, int(&)[]);
	BKSGE_IS_INTEGRAL_TEST_CV(false, int(&&)[2]);
	BKSGE_IS_INTEGRAL_TEST_CV(false, int(&&)[]);
	BKSGE_IS_INTEGRAL_TEST_CV(false, void);
	BKSGE_IS_INTEGRAL_TEST_CV(false, void*);
	BKSGE_IS_INTEGRAL_TEST_CV(false, std::nullptr_t);
	BKSGE_IS_INTEGRAL_TEST_CV(false, decltype(nullptr));
	BKSGE_IS_INTEGRAL_TEST_CV(false, enum_UDT);
	BKSGE_IS_INTEGRAL_TEST_CV(false, enum_uint32_t_UDT);
	BKSGE_IS_INTEGRAL_TEST_CV(false, enum_uint16_t_UDT);
	BKSGE_IS_INTEGRAL_TEST_CV(false, enum_uint8_t_UDT);
	BKSGE_IS_INTEGRAL_TEST_CV(false, enum_int32_t_UDT);
	BKSGE_IS_INTEGRAL_TEST_CV(false, enum_int16_t_UDT);
	BKSGE_IS_INTEGRAL_TEST_CV(false, enum_int8_t_UDT);
	BKSGE_IS_INTEGRAL_TEST_CV(false, enum_class_UDT);
	BKSGE_IS_INTEGRAL_TEST_CV(false, enum_class_uint32_t_UDT);
	BKSGE_IS_INTEGRAL_TEST_CV(false, enum_class_uint16_t_UDT);
	BKSGE_IS_INTEGRAL_TEST_CV(false, enum_class_uint8_t_UDT);
	BKSGE_IS_INTEGRAL_TEST_CV(false, enum_class_int32_t_UDT);
	BKSGE_IS_INTEGRAL_TEST_CV(false, enum_class_int16_t_UDT);
	BKSGE_IS_INTEGRAL_TEST_CV(false, enum_class_int8_t_UDT);
	BKSGE_IS_INTEGRAL_TEST_CV(false, UDT);
	BKSGE_IS_INTEGRAL_TEST_CV(false, union_UDT);
	BKSGE_IS_INTEGRAL_TEST_CV(false, non_pointer);
	BKSGE_IS_INTEGRAL_TEST_CV(false, non_int_pointer);
	BKSGE_IS_INTEGRAL_TEST_CV(false, int_constructible);
	BKSGE_IS_INTEGRAL_TEST_CV(false, int_convertible);
	BKSGE_IS_INTEGRAL_TEST_CV(false, incomplete_type);
	BKSGE_IS_INTEGRAL_TEST(false, f1);
	BKSGE_IS_INTEGRAL_TEST(false, f2);
	BKSGE_IS_INTEGRAL_TEST(false, f3);
	BKSGE_IS_INTEGRAL_TEST(false, mf1);
	BKSGE_IS_INTEGRAL_TEST(false, mf2);
	BKSGE_IS_INTEGRAL_TEST(false, mf3);
	BKSGE_IS_INTEGRAL_TEST(false, mf4);
	BKSGE_IS_INTEGRAL_TEST(false, mp);
	BKSGE_IS_INTEGRAL_TEST(false, cmf);
	BKSGE_IS_INTEGRAL_TEST(false, foo0_t);
	BKSGE_IS_INTEGRAL_TEST(false, foo1_t);
	BKSGE_IS_INTEGRAL_TEST(false, foo2_t);
	BKSGE_IS_INTEGRAL_TEST(false, foo3_t);
	BKSGE_IS_INTEGRAL_TEST(false, foo4_t);
}

#undef BKSGE_IS_INTEGRAL_TEST
#undef BKSGE_IS_INTEGRAL_TEST_CV
