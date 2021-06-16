/**
 *	@file	unit_test_fnd_type_traits_make_unsigned.cpp
 *
 *	@brief	make_unsigned のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/type_traits/make_unsigned.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <bksge/fnd/type_traits/is_integral.hpp>
#include <bksge/fnd/type_traits/is_unsigned.hpp>
#include <gtest/gtest.h>
#include "type_traits_test_utility.hpp"

#define BKSGE_MAKE_UNSIGNED_TEST_1(T)	\
	static_assert(bksge::is_integral<bksge::make_unsigned<T>::type>::value, "");	\
	static_assert(bksge::is_unsigned<bksge::make_unsigned<T>::type>::value, "");	\
	static_assert(sizeof(bksge::make_unsigned<T>::type) == sizeof(T), "")

#define BKSGE_MAKE_UNSIGNED_TEST_2(T1, T2)	\
	static_assert(bksge::is_same<bksge::make_unsigned<T1>::type, T2>::value, #T1 ", " #T2);	\
	static_assert(bksge::is_same<bksge::make_unsigned_t<T1>,     T2>::value, #T1 ", " #T2)

#define BKSGE_MAKE_UNSIGNED_TEST(T1, T2)	\
	BKSGE_MAKE_UNSIGNED_TEST_1(T1);	\
	BKSGE_MAKE_UNSIGNED_TEST_2(               T1,                T2);	\
	BKSGE_MAKE_UNSIGNED_TEST_2(const          T1, const          T2);	\
	BKSGE_MAKE_UNSIGNED_TEST_2(      volatile T1,       volatile T2);	\
	BKSGE_MAKE_UNSIGNED_TEST_2(const volatile T1, const volatile T2)

BKSGE_MAKE_UNSIGNED_TEST(char,					unsigned char);
BKSGE_MAKE_UNSIGNED_TEST(signed char,			unsigned char);
BKSGE_MAKE_UNSIGNED_TEST(short,					unsigned short);
BKSGE_MAKE_UNSIGNED_TEST(int,					unsigned int);
BKSGE_MAKE_UNSIGNED_TEST(long,					unsigned long);
BKSGE_MAKE_UNSIGNED_TEST(long long,				unsigned long long);
BKSGE_MAKE_UNSIGNED_TEST(unsigned char,			unsigned char);
BKSGE_MAKE_UNSIGNED_TEST(unsigned short,		unsigned short);
BKSGE_MAKE_UNSIGNED_TEST(unsigned int,			unsigned int);
BKSGE_MAKE_UNSIGNED_TEST(unsigned long,			unsigned long);
BKSGE_MAKE_UNSIGNED_TEST(unsigned long long,	unsigned long long);

BKSGE_MAKE_UNSIGNED_TEST_1(wchar_t);
BKSGE_MAKE_UNSIGNED_TEST_1(enum_UDT);
BKSGE_MAKE_UNSIGNED_TEST_1(enum_uint32_t_UDT);
BKSGE_MAKE_UNSIGNED_TEST_1(enum_uint16_t_UDT);
BKSGE_MAKE_UNSIGNED_TEST_1(enum_uint8_t_UDT);
BKSGE_MAKE_UNSIGNED_TEST_1(enum_int32_t_UDT);
BKSGE_MAKE_UNSIGNED_TEST_1(enum_int16_t_UDT);
BKSGE_MAKE_UNSIGNED_TEST_1(enum_int8_t_UDT);
BKSGE_MAKE_UNSIGNED_TEST_1(enum_class_UDT);
BKSGE_MAKE_UNSIGNED_TEST_1(enum_class_uint32_t_UDT);
BKSGE_MAKE_UNSIGNED_TEST_1(enum_class_uint16_t_UDT);
BKSGE_MAKE_UNSIGNED_TEST_1(enum_class_uint8_t_UDT);
BKSGE_MAKE_UNSIGNED_TEST_1(enum_class_int32_t_UDT);
BKSGE_MAKE_UNSIGNED_TEST_1(enum_class_int16_t_UDT);
BKSGE_MAKE_UNSIGNED_TEST_1(enum_class_int8_t_UDT);

// integralでもenumでもないとき、またはboolのときはエラーになる
//BKSGE_MAKE_UNSIGNED_TEST_1(bool);
//BKSGE_MAKE_UNSIGNED_TEST_1(float);
//BKSGE_MAKE_UNSIGNED_TEST_1(double);
//BKSGE_MAKE_UNSIGNED_TEST_1(long double);
//BKSGE_MAKE_UNSIGNED_TEST_1(UDT);

#undef BKSGE_MAKE_UNSIGNED_TEST_1
#undef BKSGE_MAKE_UNSIGNED_TEST_2
#undef BKSGE_MAKE_UNSIGNED_TEST
