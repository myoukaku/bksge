/**
 *	@file	unit_test_fnd_type_traits_is_array.cpp
 *
 *	@brief	is_array のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/type_traits/is_array.hpp>
#include <gtest/gtest.h>
#include "type_traits_test_utility.hpp"

namespace bksge_type_traits_test
{

namespace is_array_test
{

struct convertible_to_pointer
{
	operator char*() const;
};

#define BKSGE_IS_ARRAY_TEST_IMPL(b, T)	\
	static_assert(bksge::is_array<T>::value == b, #T);	\
	static_assert(bksge::is_array<T>()      == b, #T)

#define BKSGE_IS_ARRAY_TEST(T)	\
	BKSGE_IS_ARRAY_TEST_IMPL(false,                T);	\
	BKSGE_IS_ARRAY_TEST_IMPL(false, const          T);	\
	BKSGE_IS_ARRAY_TEST_IMPL(false,       volatile T);	\
	BKSGE_IS_ARRAY_TEST_IMPL(false, const volatile T);	\
	BKSGE_IS_ARRAY_TEST_IMPL(false, T*);	\
	BKSGE_IS_ARRAY_TEST_IMPL(false, T* const);	\
	BKSGE_IS_ARRAY_TEST_IMPL(false, T* volatile);	\
	BKSGE_IS_ARRAY_TEST_IMPL(false, T* const volatile);	\
	BKSGE_IS_ARRAY_TEST_IMPL(false, T**);	\
	BKSGE_IS_ARRAY_TEST_IMPL(true,                 T[]);	\
	BKSGE_IS_ARRAY_TEST_IMPL(true,  const          T[]);	\
	BKSGE_IS_ARRAY_TEST_IMPL(true,        volatile T[]);	\
	BKSGE_IS_ARRAY_TEST_IMPL(true,  const volatile T[]);	\
	BKSGE_IS_ARRAY_TEST_IMPL(true,                 T[2]);	\
	BKSGE_IS_ARRAY_TEST_IMPL(true,  const          T[2]);	\
	BKSGE_IS_ARRAY_TEST_IMPL(true,        volatile T[2]);	\
	BKSGE_IS_ARRAY_TEST_IMPL(true,  const volatile T[2]);	\
	BKSGE_IS_ARRAY_TEST_IMPL(true,                 T[2][3]);	\
	BKSGE_IS_ARRAY_TEST_IMPL(true,  const          T[2][3]);	\
	BKSGE_IS_ARRAY_TEST_IMPL(true,        volatile T[2][3]);	\
	BKSGE_IS_ARRAY_TEST_IMPL(true,  const volatile T[2][3]);	\
	BKSGE_IS_ARRAY_TEST_IMPL(false, T(*)[2]);	\
	BKSGE_IS_ARRAY_TEST_IMPL(false, T(&)[2]);	\
	BKSGE_IS_ARRAY_TEST_IMPL(false, T(&&)[2]);	\
	BKSGE_IS_ARRAY_TEST_IMPL(false, T&);		\
	BKSGE_IS_ARRAY_TEST_IMPL(false, T&&)

BKSGE_IS_ARRAY_TEST(int);
BKSGE_IS_ARRAY_TEST(char);
BKSGE_IS_ARRAY_TEST(float);
BKSGE_IS_ARRAY_TEST(void*);
BKSGE_IS_ARRAY_TEST(enum_UDT);
BKSGE_IS_ARRAY_TEST(enum_class_UDT);
BKSGE_IS_ARRAY_TEST(UDT);
BKSGE_IS_ARRAY_TEST(empty_UDT);
BKSGE_IS_ARRAY_TEST(union_UDT);

BKSGE_IS_ARRAY_TEST_IMPL(false, f1);
BKSGE_IS_ARRAY_TEST_IMPL(false, f2);
BKSGE_IS_ARRAY_TEST_IMPL(false, f3);
BKSGE_IS_ARRAY_TEST_IMPL(false, mf1);
BKSGE_IS_ARRAY_TEST_IMPL(false, mf2);
BKSGE_IS_ARRAY_TEST_IMPL(false, mf3);
BKSGE_IS_ARRAY_TEST_IMPL(false, mf4);
BKSGE_IS_ARRAY_TEST_IMPL(false, mp);
BKSGE_IS_ARRAY_TEST_IMPL(false, cmf);
BKSGE_IS_ARRAY_TEST_IMPL(false, void);
BKSGE_IS_ARRAY_TEST_IMPL(false, test_abc1);
BKSGE_IS_ARRAY_TEST_IMPL(false, test_abc3);
BKSGE_IS_ARRAY_TEST_IMPL(false, test_abc3);
BKSGE_IS_ARRAY_TEST_IMPL(false, convertible_to_pointer);
BKSGE_IS_ARRAY_TEST_IMPL(false, foo0_t);
BKSGE_IS_ARRAY_TEST_IMPL(false, foo1_t);
BKSGE_IS_ARRAY_TEST_IMPL(false, foo2_t);
BKSGE_IS_ARRAY_TEST_IMPL(false, foo3_t);
BKSGE_IS_ARRAY_TEST_IMPL(false, foo4_t);

#undef BKSGE_IS_ARRAY_TEST
#undef BKSGE_IS_ARRAY_TEST_IMPL

}	// namespace is_array_test

}	// namespace bksge_type_traits_test
