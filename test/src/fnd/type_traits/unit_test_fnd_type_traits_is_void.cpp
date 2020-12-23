/**
 *	@file	unit_test_fnd_type_traits_is_void.cpp
 *
 *	@brief	is_void のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/type_traits/is_void.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>
#include <bksge/fnd/cstddef/nullptr_t.hpp>
#include <gtest/gtest.h>
#include "type_traits_test_utility.hpp"

#define BKSGE_IS_VOID_TEST(b, T)	\
	static_assert(bksge::is_void<T>::value == b, #T);	\
	static_assert(bksge::is_void<T>()      == b, #T)

BKSGE_IS_VOID_TEST(true,                 void);
BKSGE_IS_VOID_TEST(true,  const          void);
BKSGE_IS_VOID_TEST(true,        volatile void);
BKSGE_IS_VOID_TEST(true,  const volatile void);

BKSGE_IS_VOID_TEST(false,                int);
BKSGE_IS_VOID_TEST(false, const          int);
BKSGE_IS_VOID_TEST(false,       volatile int);
BKSGE_IS_VOID_TEST(false, const volatile int);
BKSGE_IS_VOID_TEST(false, int*);
BKSGE_IS_VOID_TEST(false, int&);
BKSGE_IS_VOID_TEST(false, int&&);
BKSGE_IS_VOID_TEST(false, int[2]);
BKSGE_IS_VOID_TEST(false, int[]);
BKSGE_IS_VOID_TEST(false, int(*)[2]);
BKSGE_IS_VOID_TEST(false, int(*)[]);
BKSGE_IS_VOID_TEST(false, int(&)[2]);
BKSGE_IS_VOID_TEST(false, int(&)[]);
BKSGE_IS_VOID_TEST(false, int(&&)[2]);
BKSGE_IS_VOID_TEST(false, int(&&)[]);

BKSGE_IS_VOID_TEST(false, bool);
BKSGE_IS_VOID_TEST(false, char);
BKSGE_IS_VOID_TEST(false, wchar_t);
BKSGE_IS_VOID_TEST(false, signed char);
BKSGE_IS_VOID_TEST(false, short);
BKSGE_IS_VOID_TEST(false, long);
BKSGE_IS_VOID_TEST(false, long long);
BKSGE_IS_VOID_TEST(false, unsigned char);
BKSGE_IS_VOID_TEST(false, unsigned int);
BKSGE_IS_VOID_TEST(false, unsigned short);
BKSGE_IS_VOID_TEST(false, unsigned long);
BKSGE_IS_VOID_TEST(false, unsigned long long);
BKSGE_IS_VOID_TEST(false, bksge::size_t);
BKSGE_IS_VOID_TEST(false, float);
BKSGE_IS_VOID_TEST(false, double);
BKSGE_IS_VOID_TEST(false, long double);
BKSGE_IS_VOID_TEST(false, void*);
BKSGE_IS_VOID_TEST(false, bksge::nullptr_t);
BKSGE_IS_VOID_TEST(false, decltype(nullptr));
BKSGE_IS_VOID_TEST(false, enum_UDT);
BKSGE_IS_VOID_TEST(false, enum_uint32_t_UDT);
BKSGE_IS_VOID_TEST(false, enum_class_UDT);
BKSGE_IS_VOID_TEST(false, enum_class_uint32_t_UDT);
BKSGE_IS_VOID_TEST(false, UDT);
BKSGE_IS_VOID_TEST(false, POD_UDT);
BKSGE_IS_VOID_TEST(false, union_UDT);
BKSGE_IS_VOID_TEST(false, POD_union_UDT);
BKSGE_IS_VOID_TEST(false, incomplete_type);
BKSGE_IS_VOID_TEST(false, f1);
BKSGE_IS_VOID_TEST(false, f2);
BKSGE_IS_VOID_TEST(false, f3);
BKSGE_IS_VOID_TEST(false, mf1);
BKSGE_IS_VOID_TEST(false, mf2);
BKSGE_IS_VOID_TEST(false, mf3);
BKSGE_IS_VOID_TEST(false, mf4);
BKSGE_IS_VOID_TEST(false, mp);
BKSGE_IS_VOID_TEST(false, cmf);
BKSGE_IS_VOID_TEST(false, foo0_t);
BKSGE_IS_VOID_TEST(false, foo1_t);
BKSGE_IS_VOID_TEST(false, foo2_t);
BKSGE_IS_VOID_TEST(false, foo3_t);
BKSGE_IS_VOID_TEST(false, foo4_t);

#undef BKSGE_IS_VOID_TEST
