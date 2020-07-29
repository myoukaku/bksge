/**
 *	@file	unit_test_fnd_type_traits_is_object.cpp
 *
 *	@brief	is_object のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/type_traits/is_object.hpp>
#include <gtest/gtest.h>
#include "type_traits_test_utility.hpp"

#define BKSGE_IS_OBJECT_TEST(b, T)	\
	static_assert(bksge::is_object<T>::value == b, #T);	\
	static_assert(bksge::is_object<T>()      == b, #T)

BKSGE_IS_OBJECT_TEST(true,                 int);
BKSGE_IS_OBJECT_TEST(true,  const          int);
BKSGE_IS_OBJECT_TEST(true,        volatile int);
BKSGE_IS_OBJECT_TEST(true,  const volatile int);
BKSGE_IS_OBJECT_TEST(true,                 int*);
BKSGE_IS_OBJECT_TEST(true,  const          int*);
BKSGE_IS_OBJECT_TEST(true,        volatile int*);
BKSGE_IS_OBJECT_TEST(true,  const volatile int*);
BKSGE_IS_OBJECT_TEST(false,                int&);
BKSGE_IS_OBJECT_TEST(false, const          int&);
BKSGE_IS_OBJECT_TEST(false,       volatile int&);
BKSGE_IS_OBJECT_TEST(false, const volatile int&);
BKSGE_IS_OBJECT_TEST(false,                int&&);
BKSGE_IS_OBJECT_TEST(false, const          int&&);
BKSGE_IS_OBJECT_TEST(false,       volatile int&&);
BKSGE_IS_OBJECT_TEST(false, const volatile int&&);
BKSGE_IS_OBJECT_TEST(true,                 int[2]);
BKSGE_IS_OBJECT_TEST(true,  const          int[2]);
BKSGE_IS_OBJECT_TEST(true,        volatile int[2]);
BKSGE_IS_OBJECT_TEST(true,  const volatile int[2]);
BKSGE_IS_OBJECT_TEST(true,                 int[]);
BKSGE_IS_OBJECT_TEST(true,  const          int[]);
BKSGE_IS_OBJECT_TEST(true,        volatile int[]);
BKSGE_IS_OBJECT_TEST(true,  const volatile int[]);
BKSGE_IS_OBJECT_TEST(true,  int(*)[2]);
BKSGE_IS_OBJECT_TEST(true,  int(*)[]);
BKSGE_IS_OBJECT_TEST(false, int(&)[2]);
BKSGE_IS_OBJECT_TEST(false, int(&)[]);
BKSGE_IS_OBJECT_TEST(false, int(&&)[2]);
BKSGE_IS_OBJECT_TEST(false, int(&&)[]);

BKSGE_IS_OBJECT_TEST(false,                void);
BKSGE_IS_OBJECT_TEST(false, const          void);
BKSGE_IS_OBJECT_TEST(false,       volatile void);
BKSGE_IS_OBJECT_TEST(false, const volatile void);

BKSGE_IS_OBJECT_TEST(true,  bool);
BKSGE_IS_OBJECT_TEST(true,  char);
BKSGE_IS_OBJECT_TEST(true,  float);
BKSGE_IS_OBJECT_TEST(true,  void*);
BKSGE_IS_OBJECT_TEST(true,  enum_UDT);
BKSGE_IS_OBJECT_TEST(true,  enum_class_UDT);
BKSGE_IS_OBJECT_TEST(true,  UDT);
BKSGE_IS_OBJECT_TEST(true,  POD_UDT);
BKSGE_IS_OBJECT_TEST(true,  f1);
BKSGE_IS_OBJECT_TEST(true,  f2);
BKSGE_IS_OBJECT_TEST(true,  f3);
BKSGE_IS_OBJECT_TEST(true,  mf1);
BKSGE_IS_OBJECT_TEST(true,  mf2);
BKSGE_IS_OBJECT_TEST(true,  mf3);
BKSGE_IS_OBJECT_TEST(true,  mf4);
BKSGE_IS_OBJECT_TEST(true,  mp);
BKSGE_IS_OBJECT_TEST(true,  cmf);
BKSGE_IS_OBJECT_TEST(false, foo0_t);
BKSGE_IS_OBJECT_TEST(false, foo1_t);
BKSGE_IS_OBJECT_TEST(false, foo2_t);
BKSGE_IS_OBJECT_TEST(false, foo3_t);
BKSGE_IS_OBJECT_TEST(false, foo4_t);

#undef BKSGE_IS_OBJECT_TEST
