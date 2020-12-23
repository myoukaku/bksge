/**
 *	@file	unit_test_fnd_type_traits_is_pointer.cpp
 *
 *	@brief	is_pointer のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/type_traits/is_pointer.hpp>
#include <bksge/fnd/cstddef/nullptr_t.hpp>
#include <gtest/gtest.h>
#include "type_traits_test_utility.hpp"

#define BKSGE_IS_POINTER_TEST_IMPL(b, T)	\
	static_assert(bksge::is_pointer<T>::value == b, #T);	\
	static_assert(bksge::is_pointer<T>()      == b, #T)

BKSGE_IS_POINTER_TEST_IMPL(false,                int);
BKSGE_IS_POINTER_TEST_IMPL(false, const          int);
BKSGE_IS_POINTER_TEST_IMPL(false,       volatile int);
BKSGE_IS_POINTER_TEST_IMPL(false, const volatile int);
BKSGE_IS_POINTER_TEST_IMPL(true,                 int*);
BKSGE_IS_POINTER_TEST_IMPL(true,  const          int*);
BKSGE_IS_POINTER_TEST_IMPL(true,        volatile int*);
BKSGE_IS_POINTER_TEST_IMPL(true,  const volatile int*);
BKSGE_IS_POINTER_TEST_IMPL(true,                 int* const);
BKSGE_IS_POINTER_TEST_IMPL(true,  const          int* const);
BKSGE_IS_POINTER_TEST_IMPL(true,        volatile int* const);
BKSGE_IS_POINTER_TEST_IMPL(true,  const volatile int* const);
BKSGE_IS_POINTER_TEST_IMPL(true,                 int* volatile);
BKSGE_IS_POINTER_TEST_IMPL(true,  const          int* volatile);
BKSGE_IS_POINTER_TEST_IMPL(true,        volatile int* volatile);
BKSGE_IS_POINTER_TEST_IMPL(true,  const volatile int* volatile);
BKSGE_IS_POINTER_TEST_IMPL(true,                 int* const volatile);
BKSGE_IS_POINTER_TEST_IMPL(true,  const          int* const volatile);
BKSGE_IS_POINTER_TEST_IMPL(true,        volatile int* const volatile);
BKSGE_IS_POINTER_TEST_IMPL(true,  const volatile int* const volatile);
BKSGE_IS_POINTER_TEST_IMPL(true,  int**);
BKSGE_IS_POINTER_TEST_IMPL(false, int*&);
BKSGE_IS_POINTER_TEST_IMPL(false, int*&&);
BKSGE_IS_POINTER_TEST_IMPL(false, int&);
BKSGE_IS_POINTER_TEST_IMPL(false, int&&);
BKSGE_IS_POINTER_TEST_IMPL(false, int[2]);
BKSGE_IS_POINTER_TEST_IMPL(false, int[]);
BKSGE_IS_POINTER_TEST_IMPL(true,  int(*)[2]);
BKSGE_IS_POINTER_TEST_IMPL(true,  int(*)[]);
BKSGE_IS_POINTER_TEST_IMPL(false, int(&)[2]);
BKSGE_IS_POINTER_TEST_IMPL(false, int(&)[]);
BKSGE_IS_POINTER_TEST_IMPL(false, int(&&)[2]);
BKSGE_IS_POINTER_TEST_IMPL(false, int(&&)[]);

BKSGE_IS_POINTER_TEST_IMPL(false,                UDT);
BKSGE_IS_POINTER_TEST_IMPL(false, const          UDT);
BKSGE_IS_POINTER_TEST_IMPL(false,       volatile UDT);
BKSGE_IS_POINTER_TEST_IMPL(false, const volatile UDT);
BKSGE_IS_POINTER_TEST_IMPL(true,                 UDT*);
BKSGE_IS_POINTER_TEST_IMPL(true,  const          UDT*);
BKSGE_IS_POINTER_TEST_IMPL(true,        volatile UDT*);
BKSGE_IS_POINTER_TEST_IMPL(true,  const volatile UDT*);
BKSGE_IS_POINTER_TEST_IMPL(true,                 UDT* const);
BKSGE_IS_POINTER_TEST_IMPL(true,  const          UDT* const);
BKSGE_IS_POINTER_TEST_IMPL(true,        volatile UDT* const);
BKSGE_IS_POINTER_TEST_IMPL(true,  const volatile UDT* const);
BKSGE_IS_POINTER_TEST_IMPL(true,                 UDT* volatile);
BKSGE_IS_POINTER_TEST_IMPL(true,  const          UDT* volatile);
BKSGE_IS_POINTER_TEST_IMPL(true,        volatile UDT* volatile);
BKSGE_IS_POINTER_TEST_IMPL(true,  const volatile UDT* volatile);
BKSGE_IS_POINTER_TEST_IMPL(true,                 UDT* const volatile);
BKSGE_IS_POINTER_TEST_IMPL(true,  const          UDT* const volatile);
BKSGE_IS_POINTER_TEST_IMPL(true,        volatile UDT* const volatile);
BKSGE_IS_POINTER_TEST_IMPL(true,  const volatile UDT* const volatile);
BKSGE_IS_POINTER_TEST_IMPL(true,  UDT**);
BKSGE_IS_POINTER_TEST_IMPL(false, UDT*&);
BKSGE_IS_POINTER_TEST_IMPL(false, UDT*&&);
BKSGE_IS_POINTER_TEST_IMPL(false, UDT&);
BKSGE_IS_POINTER_TEST_IMPL(false, UDT&&);
BKSGE_IS_POINTER_TEST_IMPL(false, UDT[2]);
BKSGE_IS_POINTER_TEST_IMPL(false, UDT[]);
BKSGE_IS_POINTER_TEST_IMPL(true,  UDT(*)[2]);
BKSGE_IS_POINTER_TEST_IMPL(true,  UDT(*)[]);
BKSGE_IS_POINTER_TEST_IMPL(false, UDT(&)[2]);
BKSGE_IS_POINTER_TEST_IMPL(false, UDT(&)[]);
BKSGE_IS_POINTER_TEST_IMPL(false, UDT(&&)[2]);
BKSGE_IS_POINTER_TEST_IMPL(false, UDT(&&)[]);

BKSGE_IS_POINTER_TEST_IMPL(false,                void);
BKSGE_IS_POINTER_TEST_IMPL(false, const          void);
BKSGE_IS_POINTER_TEST_IMPL(false,       volatile void);
BKSGE_IS_POINTER_TEST_IMPL(false, const volatile void);
BKSGE_IS_POINTER_TEST_IMPL(true,                 void*);
BKSGE_IS_POINTER_TEST_IMPL(true,  const          void*);
BKSGE_IS_POINTER_TEST_IMPL(true,        volatile void*);
BKSGE_IS_POINTER_TEST_IMPL(true,  const volatile void*);

BKSGE_IS_POINTER_TEST_IMPL(false, bksge::nullptr_t);
BKSGE_IS_POINTER_TEST_IMPL(false, decltype(nullptr));
BKSGE_IS_POINTER_TEST_IMPL(true,  f1);
BKSGE_IS_POINTER_TEST_IMPL(true,  f2);
BKSGE_IS_POINTER_TEST_IMPL(true,  f3);
BKSGE_IS_POINTER_TEST_IMPL(false, mf1);
BKSGE_IS_POINTER_TEST_IMPL(false, mf2);
BKSGE_IS_POINTER_TEST_IMPL(false, mf3);
BKSGE_IS_POINTER_TEST_IMPL(false, mf4);
BKSGE_IS_POINTER_TEST_IMPL(false, mp);
BKSGE_IS_POINTER_TEST_IMPL(false, cmf);
BKSGE_IS_POINTER_TEST_IMPL(false, foo0_t);
BKSGE_IS_POINTER_TEST_IMPL(false, foo1_t);
BKSGE_IS_POINTER_TEST_IMPL(false, foo2_t);
BKSGE_IS_POINTER_TEST_IMPL(false, foo3_t);
BKSGE_IS_POINTER_TEST_IMPL(false, foo4_t);

#undef BKSGE_IS_POINTER_TEST_IMPL
