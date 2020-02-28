/**
 *	@file	unit_test_fnd_type_traits_make_signed.cpp
 *
 *	@brief	make_signed のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/type_traits/make_signed.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <bksge/fnd/type_traits/is_integral.hpp>
#include <bksge/fnd/type_traits/is_signed.hpp>
#include <gtest/gtest.h>
#include "type_traits_test_utility.hpp"

GTEST_TEST(TypeTraitsTest, MakeSignedTest)
{
#define BKSGE_MAKE_SIGNED_TEST_1(T)	\
	static_assert(bksge::is_integral<bksge::make_signed<T>::type>::value, "");	\
	static_assert(bksge::is_signed<bksge::make_signed<T>::type>::value, "");	\
	static_assert(sizeof(bksge::make_signed<T>::type) == sizeof(T), "")

#define BKSGE_MAKE_SIGNED_TEST_2(T1, T2)	\
	static_assert(bksge::is_same<bksge::make_signed<T1>::type, T2>::value, #T1 ", " #T2);	\
	static_assert(bksge::is_same<bksge::make_signed_t<T1>,     T2>::value, #T1 ", " #T2)

#define BKSGE_MAKE_SIGNED_TEST(T1, T2)	\
	BKSGE_MAKE_SIGNED_TEST_1(T1);	\
	BKSGE_MAKE_SIGNED_TEST_2(               T1,                T2);	\
	BKSGE_MAKE_SIGNED_TEST_2(const          T1, const          T2);	\
	BKSGE_MAKE_SIGNED_TEST_2(      volatile T1,       volatile T2);	\
	BKSGE_MAKE_SIGNED_TEST_2(const volatile T1, const volatile T2)

	BKSGE_MAKE_SIGNED_TEST(char,				signed char);
	BKSGE_MAKE_SIGNED_TEST(signed char,			signed char);
	BKSGE_MAKE_SIGNED_TEST(short,				signed short);
	BKSGE_MAKE_SIGNED_TEST(int,					signed int);
	BKSGE_MAKE_SIGNED_TEST(long,				signed long);
	BKSGE_MAKE_SIGNED_TEST(long long,			signed long long);
	BKSGE_MAKE_SIGNED_TEST(unsigned char,		signed char);
	BKSGE_MAKE_SIGNED_TEST(unsigned short,		signed short);
	BKSGE_MAKE_SIGNED_TEST(unsigned int,		signed int);
	BKSGE_MAKE_SIGNED_TEST(unsigned long,		signed long);
	BKSGE_MAKE_SIGNED_TEST(unsigned long long,	signed long long);

	BKSGE_MAKE_SIGNED_TEST_1(wchar_t);
	BKSGE_MAKE_SIGNED_TEST_1(enum_UDT);
	BKSGE_MAKE_SIGNED_TEST_1(enum_uint32_t_UDT);
	BKSGE_MAKE_SIGNED_TEST_1(enum_uint16_t_UDT);
	BKSGE_MAKE_SIGNED_TEST_1(enum_uint8_t_UDT);
	BKSGE_MAKE_SIGNED_TEST_1(enum_int32_t_UDT);
	BKSGE_MAKE_SIGNED_TEST_1(enum_int16_t_UDT);
	BKSGE_MAKE_SIGNED_TEST_1(enum_int8_t_UDT);
	BKSGE_MAKE_SIGNED_TEST_1(enum_class_UDT);
	BKSGE_MAKE_SIGNED_TEST_1(enum_class_uint32_t_UDT);
	BKSGE_MAKE_SIGNED_TEST_1(enum_class_uint16_t_UDT);
	BKSGE_MAKE_SIGNED_TEST_1(enum_class_uint8_t_UDT);
	BKSGE_MAKE_SIGNED_TEST_1(enum_class_int32_t_UDT);
	BKSGE_MAKE_SIGNED_TEST_1(enum_class_int16_t_UDT);
	BKSGE_MAKE_SIGNED_TEST_1(enum_class_int8_t_UDT);

	// integralでもenumでもないとき、またはboolのときはエラーになる
	//BKSGE_MAKE_SIGNED_TEST_1(bool);
	//BKSGE_MAKE_SIGNED_TEST_1(float);
	//BKSGE_MAKE_SIGNED_TEST_1(double);
	//BKSGE_MAKE_SIGNED_TEST_1(long double);
	//BKSGE_MAKE_SIGNED_TEST_1(UDT);

#undef BKSGE_MAKE_SIGNED_TEST_1
#undef BKSGE_MAKE_SIGNED_TEST_2
#undef BKSGE_MAKE_SIGNED_TEST
}
