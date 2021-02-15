/**
 *	@file	unit_test_fnd_type_traits_is_unsigned.cpp
 *
 *	@brief	is_unsigned のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/type_traits/is_unsigned.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>
#include <bksge/fnd/cstddef/nullptr_t.hpp>
#include <bksge/fnd/config.hpp>
#include <cstdint>	// WCHAR_MIN
#include <climits>	// CHAR_MIN
#include <gtest/gtest.h>
#include "type_traits_test_utility.hpp"

#if defined(BKSGE_HAS_CXX14_VARIABLE_TEMPLATES)

#define BKSGE_IS_UNSIGNED_TEST(b, T)	\
	static_assert(bksge::is_unsigned_v<T>      == b, #T);	\
	static_assert(bksge::is_unsigned<T>::value == b, #T);	\
	static_assert(bksge::is_unsigned<T>()      == b, #T)

#else

#define BKSGE_IS_UNSIGNED_TEST(b, T)	\
	static_assert(bksge::is_unsigned<T>::value == b, #T);	\
	static_assert(bksge::is_unsigned<T>()      == b, #T)

#endif

BKSGE_IS_UNSIGNED_TEST(true,                 unsigned int);
BKSGE_IS_UNSIGNED_TEST(true,  const          unsigned int);
BKSGE_IS_UNSIGNED_TEST(true,        volatile unsigned int);
BKSGE_IS_UNSIGNED_TEST(true,  const volatile unsigned int);
BKSGE_IS_UNSIGNED_TEST(false, unsigned int*);
BKSGE_IS_UNSIGNED_TEST(false, unsigned int&);
BKSGE_IS_UNSIGNED_TEST(false, unsigned int&&);
BKSGE_IS_UNSIGNED_TEST(false, unsigned int[2]);
BKSGE_IS_UNSIGNED_TEST(false, unsigned int[]);
BKSGE_IS_UNSIGNED_TEST(false, unsigned int(*)[2]);
BKSGE_IS_UNSIGNED_TEST(false, unsigned int(*)[]);
BKSGE_IS_UNSIGNED_TEST(false, unsigned int(&)[2]);
BKSGE_IS_UNSIGNED_TEST(false, unsigned int(&)[]);
BKSGE_IS_UNSIGNED_TEST(false, unsigned int(&&)[2]);
BKSGE_IS_UNSIGNED_TEST(false, unsigned int(&&)[]);

BKSGE_IS_UNSIGNED_TEST(true, bool);
#if CHAR_MIN < 0
BKSGE_IS_UNSIGNED_TEST(false, char);
#else
BKSGE_IS_UNSIGNED_TEST(true, char);
#endif
#if WCHAR_MIN < 0
BKSGE_IS_UNSIGNED_TEST(false, wchar_t);
#else
BKSGE_IS_UNSIGNED_TEST(true, wchar_t);
#endif
BKSGE_IS_UNSIGNED_TEST(false, signed char);
BKSGE_IS_UNSIGNED_TEST(false, int);
BKSGE_IS_UNSIGNED_TEST(false, short);
BKSGE_IS_UNSIGNED_TEST(false, long);
BKSGE_IS_UNSIGNED_TEST(false, long long);
BKSGE_IS_UNSIGNED_TEST(true, unsigned char);
BKSGE_IS_UNSIGNED_TEST(true, unsigned int);
BKSGE_IS_UNSIGNED_TEST(true, unsigned short);
BKSGE_IS_UNSIGNED_TEST(true, unsigned long);
BKSGE_IS_UNSIGNED_TEST(true, unsigned long long);
BKSGE_IS_UNSIGNED_TEST(true, bksge::size_t);
BKSGE_IS_UNSIGNED_TEST(false, float);
BKSGE_IS_UNSIGNED_TEST(false, double);
BKSGE_IS_UNSIGNED_TEST(false, long double);
BKSGE_IS_UNSIGNED_TEST(false, void);
BKSGE_IS_UNSIGNED_TEST(false, void*);
BKSGE_IS_UNSIGNED_TEST(false, bksge::nullptr_t);
BKSGE_IS_UNSIGNED_TEST(false, decltype(nullptr));
BKSGE_IS_UNSIGNED_TEST(false, enum_UDT);
BKSGE_IS_UNSIGNED_TEST(false, enum_uint32_t_UDT);
BKSGE_IS_UNSIGNED_TEST(false, enum_uint16_t_UDT);
BKSGE_IS_UNSIGNED_TEST(false, enum_uint8_t_UDT);
BKSGE_IS_UNSIGNED_TEST(false, enum_int32_t_UDT);
BKSGE_IS_UNSIGNED_TEST(false, enum_int16_t_UDT);
BKSGE_IS_UNSIGNED_TEST(false, enum_int8_t_UDT);
BKSGE_IS_UNSIGNED_TEST(false, enum_class_UDT);
BKSGE_IS_UNSIGNED_TEST(false, enum_class_uint32_t_UDT);
BKSGE_IS_UNSIGNED_TEST(false, enum_class_uint16_t_UDT);
BKSGE_IS_UNSIGNED_TEST(false, enum_class_uint8_t_UDT);
BKSGE_IS_UNSIGNED_TEST(false, enum_class_int32_t_UDT);
BKSGE_IS_UNSIGNED_TEST(false, enum_class_int16_t_UDT);
BKSGE_IS_UNSIGNED_TEST(false, enum_class_int8_t_UDT);
BKSGE_IS_UNSIGNED_TEST(false, UDT);
BKSGE_IS_UNSIGNED_TEST(false, POD_UDT);
BKSGE_IS_UNSIGNED_TEST(false, union_UDT);
BKSGE_IS_UNSIGNED_TEST(false, POD_union_UDT);
BKSGE_IS_UNSIGNED_TEST(false, f1);
BKSGE_IS_UNSIGNED_TEST(false, f2);
BKSGE_IS_UNSIGNED_TEST(false, f3);
BKSGE_IS_UNSIGNED_TEST(false, mf1);
BKSGE_IS_UNSIGNED_TEST(false, mf2);
BKSGE_IS_UNSIGNED_TEST(false, mf3);
BKSGE_IS_UNSIGNED_TEST(false, mf4);
BKSGE_IS_UNSIGNED_TEST(false, mp);
BKSGE_IS_UNSIGNED_TEST(false, cmf);
BKSGE_IS_UNSIGNED_TEST(false, foo0_t);
BKSGE_IS_UNSIGNED_TEST(false, foo1_t);
BKSGE_IS_UNSIGNED_TEST(false, foo2_t);
BKSGE_IS_UNSIGNED_TEST(false, foo3_t);
BKSGE_IS_UNSIGNED_TEST(false, foo4_t);

#undef BKSGE_IS_UNSIGNED_TEST
