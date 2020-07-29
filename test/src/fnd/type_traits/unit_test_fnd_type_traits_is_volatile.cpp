/**
 *	@file	unit_test_fnd_type_traits_is_volatile.cpp
 *
 *	@brief	is_volatile のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/type_traits/is_volatile.hpp>
#include <gtest/gtest.h>
#include "type_traits_test_utility.hpp"

#define BKSGE_IS_VOLATILE_TEST_IMPL(b, T)	\
	static_assert(bksge::is_volatile<T>::value == b, #T);	\
	static_assert(bksge::is_volatile<T>()      == b, #T)

#define BKSGE_IS_VOLATILE_TEST(T)	\
	BKSGE_IS_VOLATILE_TEST_IMPL(false,                T);	\
	BKSGE_IS_VOLATILE_TEST_IMPL(false, const          T);	\
	BKSGE_IS_VOLATILE_TEST_IMPL(true,        volatile T);	\
	BKSGE_IS_VOLATILE_TEST_IMPL(true,  const volatile T);	\
	BKSGE_IS_VOLATILE_TEST_IMPL(false,                T&);	\
	BKSGE_IS_VOLATILE_TEST_IMPL(false, const          T&);	\
	BKSGE_IS_VOLATILE_TEST_IMPL(false,       volatile T&);	\
	BKSGE_IS_VOLATILE_TEST_IMPL(false, const volatile T&);	\
	BKSGE_IS_VOLATILE_TEST_IMPL(false,                T&&);	\
	BKSGE_IS_VOLATILE_TEST_IMPL(false, const          T&&);	\
	BKSGE_IS_VOLATILE_TEST_IMPL(false,       volatile T&&);	\
	BKSGE_IS_VOLATILE_TEST_IMPL(false, const volatile T&&);	\
	BKSGE_IS_VOLATILE_TEST_IMPL(false,                T*);	\
	BKSGE_IS_VOLATILE_TEST_IMPL(false, const          T*);	\
	BKSGE_IS_VOLATILE_TEST_IMPL(false,       volatile T*);	\
	BKSGE_IS_VOLATILE_TEST_IMPL(false, const volatile T*);	\
	BKSGE_IS_VOLATILE_TEST_IMPL(false, T*               );	\
	BKSGE_IS_VOLATILE_TEST_IMPL(false, T* const         );	\
	BKSGE_IS_VOLATILE_TEST_IMPL(true,  T*       volatile);	\
	BKSGE_IS_VOLATILE_TEST_IMPL(true,  T* const volatile);	\
	BKSGE_IS_VOLATILE_TEST_IMPL(false,                T[2]);	\
	BKSGE_IS_VOLATILE_TEST_IMPL(false, const          T[2]);	\
	BKSGE_IS_VOLATILE_TEST_IMPL(true,        volatile T[2]);	\
	BKSGE_IS_VOLATILE_TEST_IMPL(true,  const volatile T[2]);	\
	BKSGE_IS_VOLATILE_TEST_IMPL(false,                T[]);	\
	BKSGE_IS_VOLATILE_TEST_IMPL(false, const          T[]);	\
	BKSGE_IS_VOLATILE_TEST_IMPL(true,        volatile T[]);	\
	BKSGE_IS_VOLATILE_TEST_IMPL(true,  const volatile T[]);	\
	BKSGE_IS_VOLATILE_TEST_IMPL(false,                T(*)[2]);	\
	BKSGE_IS_VOLATILE_TEST_IMPL(false, const          T(*)[2]);	\
	BKSGE_IS_VOLATILE_TEST_IMPL(false,       volatile T(*)[2]);	\
	BKSGE_IS_VOLATILE_TEST_IMPL(false, const volatile T(*)[2]);	\
	BKSGE_IS_VOLATILE_TEST_IMPL(false,                T(&)[2]);	\
	BKSGE_IS_VOLATILE_TEST_IMPL(false, const          T(&)[2]);	\
	BKSGE_IS_VOLATILE_TEST_IMPL(false,       volatile T(&)[2]);	\
	BKSGE_IS_VOLATILE_TEST_IMPL(false, const volatile T(&)[2]);	\
	BKSGE_IS_VOLATILE_TEST_IMPL(false,                T(&&)[2]);	\
	BKSGE_IS_VOLATILE_TEST_IMPL(false, const          T(&&)[2]);	\
	BKSGE_IS_VOLATILE_TEST_IMPL(false,       volatile T(&&)[2]);	\
	BKSGE_IS_VOLATILE_TEST_IMPL(false, const volatile T(&&)[2])

BKSGE_IS_VOLATILE_TEST(int);
BKSGE_IS_VOLATILE_TEST(UDT);
BKSGE_IS_VOLATILE_TEST(enum_UDT);
BKSGE_IS_VOLATILE_TEST(f1);
BKSGE_IS_VOLATILE_TEST(mf1);
BKSGE_IS_VOLATILE_TEST(mp);
BKSGE_IS_VOLATILE_TEST(cmf);
BKSGE_IS_VOLATILE_TEST_IMPL(false, foo0_t);
BKSGE_IS_VOLATILE_TEST_IMPL(false, foo1_t);
BKSGE_IS_VOLATILE_TEST_IMPL(false, foo2_t);
BKSGE_IS_VOLATILE_TEST_IMPL(false, foo3_t);
BKSGE_IS_VOLATILE_TEST_IMPL(false, foo4_t);

#undef BKSGE_IS_VOLATILE_TEST_IMPL
#undef BKSGE_IS_VOLATILE_TEST
