/**
 *	@file	unit_test_fnd_type_traits_is_swappable.cpp
 *
 *	@brief	is_swappable のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/type_traits/is_swappable.hpp>
#include <gtest/gtest.h>
#include "type_traits_test_utility.hpp"

#define BKSGE_IS_SWAPPABLE_TEST(b, T)	\
	static_assert(bksge::is_swappable<T>::value == b, #T);	\
	static_assert(bksge::is_swappable<T>()      == b, #T)

BKSGE_IS_SWAPPABLE_TEST(true,                 int);
BKSGE_IS_SWAPPABLE_TEST(false, const          int);
BKSGE_IS_SWAPPABLE_TEST(true,        volatile int);
BKSGE_IS_SWAPPABLE_TEST(false, const volatile int);
BKSGE_IS_SWAPPABLE_TEST(true,                 bool);
BKSGE_IS_SWAPPABLE_TEST(false, const          bool);
BKSGE_IS_SWAPPABLE_TEST(true,        volatile bool);
BKSGE_IS_SWAPPABLE_TEST(false, const volatile bool);
BKSGE_IS_SWAPPABLE_TEST(false,                int[]);
BKSGE_IS_SWAPPABLE_TEST(false, const          int[]);
BKSGE_IS_SWAPPABLE_TEST(false,       volatile int[]);
BKSGE_IS_SWAPPABLE_TEST(false, const volatile int[]);
BKSGE_IS_SWAPPABLE_TEST(true,                 int[2]);
BKSGE_IS_SWAPPABLE_TEST(false, const          int[2]);
BKSGE_IS_SWAPPABLE_TEST(true,        volatile int[2]);
BKSGE_IS_SWAPPABLE_TEST(false, const volatile int[2]);
BKSGE_IS_SWAPPABLE_TEST(false,                int[][3]);
BKSGE_IS_SWAPPABLE_TEST(false, const          int[][3]);
BKSGE_IS_SWAPPABLE_TEST(false,       volatile int[][3]);
BKSGE_IS_SWAPPABLE_TEST(false, const volatile int[][3]);
BKSGE_IS_SWAPPABLE_TEST(true,                 int[1][2][3]);
BKSGE_IS_SWAPPABLE_TEST(false, const          int[1][2][3]);
BKSGE_IS_SWAPPABLE_TEST(true,        volatile int[1][2][3]);
BKSGE_IS_SWAPPABLE_TEST(false, const volatile int[1][2][3]);
BKSGE_IS_SWAPPABLE_TEST(false,                int[][2][3]);
BKSGE_IS_SWAPPABLE_TEST(false, const          int[][2][3]);
BKSGE_IS_SWAPPABLE_TEST(false,       volatile int[][2][3]);
BKSGE_IS_SWAPPABLE_TEST(false, const volatile int[][2][3]);
BKSGE_IS_SWAPPABLE_TEST(true,                 int&);
BKSGE_IS_SWAPPABLE_TEST(false, const          int&);
BKSGE_IS_SWAPPABLE_TEST(true,        volatile int&);
BKSGE_IS_SWAPPABLE_TEST(false, const volatile int&);
BKSGE_IS_SWAPPABLE_TEST(true,                 int&&);
BKSGE_IS_SWAPPABLE_TEST(false, const          int&&);
BKSGE_IS_SWAPPABLE_TEST(true,        volatile int&&);
BKSGE_IS_SWAPPABLE_TEST(false, const volatile int&&);
BKSGE_IS_SWAPPABLE_TEST(true,                 int*);
BKSGE_IS_SWAPPABLE_TEST(true,  const          int*);
BKSGE_IS_SWAPPABLE_TEST(true,        volatile int*);
BKSGE_IS_SWAPPABLE_TEST(true,  const volatile int*);
BKSGE_IS_SWAPPABLE_TEST(true,                 int(&)[2]);
BKSGE_IS_SWAPPABLE_TEST(false, const          int(&)[2]);
BKSGE_IS_SWAPPABLE_TEST(true,        volatile int(&)[2]);
BKSGE_IS_SWAPPABLE_TEST(false, const volatile int(&)[2]);
BKSGE_IS_SWAPPABLE_TEST(false,                int(&)[]);
BKSGE_IS_SWAPPABLE_TEST(false, const          int(&)[]);
BKSGE_IS_SWAPPABLE_TEST(false,       volatile int(&)[]);
BKSGE_IS_SWAPPABLE_TEST(false, const volatile int(&)[]);
BKSGE_IS_SWAPPABLE_TEST(true,                 int(&&)[2]);
BKSGE_IS_SWAPPABLE_TEST(false, const          int(&&)[2]);
BKSGE_IS_SWAPPABLE_TEST(true,        volatile int(&&)[2]);
BKSGE_IS_SWAPPABLE_TEST(false, const volatile int(&&)[2]);
BKSGE_IS_SWAPPABLE_TEST(false,                int(&&)[]);
BKSGE_IS_SWAPPABLE_TEST(false, const          int(&&)[]);
BKSGE_IS_SWAPPABLE_TEST(false,       volatile int(&&)[]);
BKSGE_IS_SWAPPABLE_TEST(false, const volatile int(&&)[]);
BKSGE_IS_SWAPPABLE_TEST(true,                 int(*)[2]);
BKSGE_IS_SWAPPABLE_TEST(true,  const          int(*)[2]);
BKSGE_IS_SWAPPABLE_TEST(true,        volatile int(*)[2]);
BKSGE_IS_SWAPPABLE_TEST(true,  const volatile int(*)[2]);
BKSGE_IS_SWAPPABLE_TEST(true,                 int(*)[]);
BKSGE_IS_SWAPPABLE_TEST(true,  const          int(*)[]);
BKSGE_IS_SWAPPABLE_TEST(true,        volatile int(*)[]);
BKSGE_IS_SWAPPABLE_TEST(true,  const volatile int(*)[]);
BKSGE_IS_SWAPPABLE_TEST(false,                void);
BKSGE_IS_SWAPPABLE_TEST(false, const          void);
BKSGE_IS_SWAPPABLE_TEST(false,       volatile void);
BKSGE_IS_SWAPPABLE_TEST(false, const volatile void);
BKSGE_IS_SWAPPABLE_TEST(true,                 void*);
BKSGE_IS_SWAPPABLE_TEST(true,  const          void*);
BKSGE_IS_SWAPPABLE_TEST(true,        volatile void*);
BKSGE_IS_SWAPPABLE_TEST(true,  const volatile void*);
BKSGE_IS_SWAPPABLE_TEST(true,                 UDT);
BKSGE_IS_SWAPPABLE_TEST(false, const          UDT);
BKSGE_IS_SWAPPABLE_TEST(false,       volatile UDT);
BKSGE_IS_SWAPPABLE_TEST(false, const volatile UDT);
BKSGE_IS_SWAPPABLE_TEST(true,                 POD_UDT);
BKSGE_IS_SWAPPABLE_TEST(false, const          POD_UDT);
BKSGE_IS_SWAPPABLE_TEST(false,       volatile POD_UDT);
BKSGE_IS_SWAPPABLE_TEST(false, const volatile POD_UDT);
BKSGE_IS_SWAPPABLE_TEST(true,                 enum_UDT);
BKSGE_IS_SWAPPABLE_TEST(false, const          enum_UDT);
BKSGE_IS_SWAPPABLE_TEST(true,        volatile enum_UDT);
BKSGE_IS_SWAPPABLE_TEST(false, const volatile enum_UDT);
BKSGE_IS_SWAPPABLE_TEST(true,                 enum_class_UDT);
BKSGE_IS_SWAPPABLE_TEST(false, const          enum_class_UDT);
BKSGE_IS_SWAPPABLE_TEST(true,        volatile enum_class_UDT);
BKSGE_IS_SWAPPABLE_TEST(false, const volatile enum_class_UDT);
BKSGE_IS_SWAPPABLE_TEST(false,                test_abc1);
BKSGE_IS_SWAPPABLE_TEST(false, const          test_abc1);
BKSGE_IS_SWAPPABLE_TEST(false,       volatile test_abc1);
BKSGE_IS_SWAPPABLE_TEST(false, const volatile test_abc1);
BKSGE_IS_SWAPPABLE_TEST(false,                test_abc2);
BKSGE_IS_SWAPPABLE_TEST(false, const          test_abc2);
BKSGE_IS_SWAPPABLE_TEST(false,       volatile test_abc2);
BKSGE_IS_SWAPPABLE_TEST(false, const volatile test_abc2);
BKSGE_IS_SWAPPABLE_TEST(false,                test_abc3);
BKSGE_IS_SWAPPABLE_TEST(false, const          test_abc3);
BKSGE_IS_SWAPPABLE_TEST(false,       volatile test_abc3);
BKSGE_IS_SWAPPABLE_TEST(false, const volatile test_abc3);

BKSGE_IS_SWAPPABLE_TEST(true, f1);
BKSGE_IS_SWAPPABLE_TEST(true, f2);
BKSGE_IS_SWAPPABLE_TEST(true, f3);
BKSGE_IS_SWAPPABLE_TEST(true, mf1);
BKSGE_IS_SWAPPABLE_TEST(true, mf2);
BKSGE_IS_SWAPPABLE_TEST(true, mf3);
BKSGE_IS_SWAPPABLE_TEST(true, mf4);
BKSGE_IS_SWAPPABLE_TEST(true, mp);
BKSGE_IS_SWAPPABLE_TEST(true, cmf);
BKSGE_IS_SWAPPABLE_TEST(false, void());
BKSGE_IS_SWAPPABLE_TEST(false, foo0_t);
BKSGE_IS_SWAPPABLE_TEST(false, foo1_t);
BKSGE_IS_SWAPPABLE_TEST(false, foo2_t);
BKSGE_IS_SWAPPABLE_TEST(false, foo3_t);
BKSGE_IS_SWAPPABLE_TEST(false, foo4_t);

#undef BKSGE_IS_SWAPPABLE_TEST
