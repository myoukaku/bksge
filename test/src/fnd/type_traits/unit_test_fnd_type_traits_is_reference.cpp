/**
 *	@file	unit_test_fnd_type_traits_is_reference.cpp
 *
 *	@brief	is_reference のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/type_traits/is_reference.hpp>
#include <gtest/gtest.h>
#include "type_traits_test_utility.hpp"

#define BKSGE_IS_REFERENCE_TEST_IMPL(b, T)	\
	static_assert(bksge::is_reference<T>::value == b, #T);	\
	static_assert(bksge::is_reference<T>()      == b, #T)

#define BKSGE_IS_REFERENCE_TEST(T)	\
	BKSGE_IS_REFERENCE_TEST_IMPL(false,                T);	\
	BKSGE_IS_REFERENCE_TEST_IMPL(false, const          T);	\
	BKSGE_IS_REFERENCE_TEST_IMPL(false,       volatile T);	\
	BKSGE_IS_REFERENCE_TEST_IMPL(false, const volatile T);	\
	BKSGE_IS_REFERENCE_TEST_IMPL(false, T*);				\
	BKSGE_IS_REFERENCE_TEST_IMPL(false, T* const);			\
	BKSGE_IS_REFERENCE_TEST_IMPL(false, T* volatile);		\
	BKSGE_IS_REFERENCE_TEST_IMPL(false, T* const volatile);	\
	BKSGE_IS_REFERENCE_TEST_IMPL(false, T**);				\
	BKSGE_IS_REFERENCE_TEST_IMPL(true,                 T&);	\
	BKSGE_IS_REFERENCE_TEST_IMPL(true,  const          T&);	\
	BKSGE_IS_REFERENCE_TEST_IMPL(true,        volatile T&);	\
	BKSGE_IS_REFERENCE_TEST_IMPL(true,  const volatile T&);	\
	BKSGE_IS_REFERENCE_TEST_IMPL(true,                 T&&);	\
	BKSGE_IS_REFERENCE_TEST_IMPL(true,  const          T&&);	\
	BKSGE_IS_REFERENCE_TEST_IMPL(true,        volatile T&&);	\
	BKSGE_IS_REFERENCE_TEST_IMPL(true,  const volatile T&&);	\
	BKSGE_IS_REFERENCE_TEST_IMPL(false, T[2]);	\
	BKSGE_IS_REFERENCE_TEST_IMPL(false, T[]);	\
	BKSGE_IS_REFERENCE_TEST_IMPL(false, T(*)[2]);	\
	BKSGE_IS_REFERENCE_TEST_IMPL(false, T(*)[]);	\
	BKSGE_IS_REFERENCE_TEST_IMPL(true,  T(&)[2]);	\
	BKSGE_IS_REFERENCE_TEST_IMPL(true,  T(&)[]);	\
	BKSGE_IS_REFERENCE_TEST_IMPL(true,  T(&&)[2]);	\
	BKSGE_IS_REFERENCE_TEST_IMPL(true,  T(&&)[])

BKSGE_IS_REFERENCE_TEST(int);
BKSGE_IS_REFERENCE_TEST(bool);
BKSGE_IS_REFERENCE_TEST(char);
BKSGE_IS_REFERENCE_TEST(float);
BKSGE_IS_REFERENCE_TEST(UDT);
BKSGE_IS_REFERENCE_TEST(POD_UDT);
BKSGE_IS_REFERENCE_TEST(enum_UDT);

BKSGE_IS_REFERENCE_TEST_IMPL(false,                void);
BKSGE_IS_REFERENCE_TEST_IMPL(false, const          void);
BKSGE_IS_REFERENCE_TEST_IMPL(false,       volatile void);
BKSGE_IS_REFERENCE_TEST_IMPL(false, const volatile void);

BKSGE_IS_REFERENCE_TEST_IMPL(false, f1);
BKSGE_IS_REFERENCE_TEST_IMPL(false, f2);
BKSGE_IS_REFERENCE_TEST_IMPL(false, f3);
BKSGE_IS_REFERENCE_TEST_IMPL(false, mf1);
BKSGE_IS_REFERENCE_TEST_IMPL(false, mf2);
BKSGE_IS_REFERENCE_TEST_IMPL(false, mf3);
BKSGE_IS_REFERENCE_TEST_IMPL(false, mf4);
BKSGE_IS_REFERENCE_TEST_IMPL(false, mp);
BKSGE_IS_REFERENCE_TEST_IMPL(false, cmf);
BKSGE_IS_REFERENCE_TEST_IMPL(false, foo0_t);
BKSGE_IS_REFERENCE_TEST_IMPL(false, foo1_t);
BKSGE_IS_REFERENCE_TEST_IMPL(false, foo2_t);
BKSGE_IS_REFERENCE_TEST_IMPL(false, foo3_t);
BKSGE_IS_REFERENCE_TEST_IMPL(false, foo4_t);

#undef BKSGE_IS_REFERENCE_TEST_IMPL
#undef BKSGE_IS_REFERENCE_TEST
