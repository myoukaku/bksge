/**
 *	@file	unit_test_fnd_type_traits_is_const.cpp
 *
 *	@brief	is_const のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/type_traits/is_const.hpp>
#include <gtest/gtest.h>
#include "type_traits_test_utility.hpp"

#define BKSGE_IS_CONST_TEST_IMPL(b, T)	\
	static_assert(bksge::is_const<T>::value == b, #T)

#define BKSGE_IS_CONST_TEST_CV(T)	\
	BKSGE_IS_CONST_TEST_IMPL(false,                T);	\
	BKSGE_IS_CONST_TEST_IMPL(true,  const          T);	\
	BKSGE_IS_CONST_TEST_IMPL(false,       volatile T);	\
	BKSGE_IS_CONST_TEST_IMPL(true,  const volatile T)

#define BKSGE_IS_CONST_TEST(T)	\
	BKSGE_IS_CONST_TEST_IMPL(false,                T);	\
	BKSGE_IS_CONST_TEST_IMPL(true,  const          T);	\
	BKSGE_IS_CONST_TEST_IMPL(false,       volatile T);	\
	BKSGE_IS_CONST_TEST_IMPL(true,  const volatile T);	\
	BKSGE_IS_CONST_TEST_IMPL(false,                T&);	\
	BKSGE_IS_CONST_TEST_IMPL(false, const          T&);	\
	BKSGE_IS_CONST_TEST_IMPL(false,       volatile T&);	\
	BKSGE_IS_CONST_TEST_IMPL(false, const volatile T&);	\
	BKSGE_IS_CONST_TEST_IMPL(false,                T&&);	\
	BKSGE_IS_CONST_TEST_IMPL(false, const          T&&);	\
	BKSGE_IS_CONST_TEST_IMPL(false,       volatile T&&);	\
	BKSGE_IS_CONST_TEST_IMPL(false, const volatile T&&);	\
	BKSGE_IS_CONST_TEST_IMPL(false,                T*);	\
	BKSGE_IS_CONST_TEST_IMPL(false, const          T*);	\
	BKSGE_IS_CONST_TEST_IMPL(false,       volatile T*);	\
	BKSGE_IS_CONST_TEST_IMPL(false, const volatile T*);	\
	BKSGE_IS_CONST_TEST_IMPL(false, T*               );	\
	BKSGE_IS_CONST_TEST_IMPL(true,  T* const         );	\
	BKSGE_IS_CONST_TEST_IMPL(false, T*       volatile);	\
	BKSGE_IS_CONST_TEST_IMPL(true,  T* const volatile);	\
	BKSGE_IS_CONST_TEST_IMPL(false,                T[2]);	\
	BKSGE_IS_CONST_TEST_IMPL(true,  const          T[2]);	\
	BKSGE_IS_CONST_TEST_IMPL(false,       volatile T[2]);	\
	BKSGE_IS_CONST_TEST_IMPL(true,  const volatile T[2]);	\
	BKSGE_IS_CONST_TEST_IMPL(false,                T[]);	\
	BKSGE_IS_CONST_TEST_IMPL(true,  const          T[]);	\
	BKSGE_IS_CONST_TEST_IMPL(false,       volatile T[]);	\
	BKSGE_IS_CONST_TEST_IMPL(true,  const volatile T[]);	\
	BKSGE_IS_CONST_TEST_IMPL(false,                T(*)[2]);	\
	BKSGE_IS_CONST_TEST_IMPL(false, const          T(*)[2]);	\
	BKSGE_IS_CONST_TEST_IMPL(false,       volatile T(*)[2]);	\
	BKSGE_IS_CONST_TEST_IMPL(false, const volatile T(*)[2]);	\
	BKSGE_IS_CONST_TEST_IMPL(false,                T(&)[2]);	\
	BKSGE_IS_CONST_TEST_IMPL(false, const          T(&)[2]);	\
	BKSGE_IS_CONST_TEST_IMPL(false,       volatile T(&)[2]);	\
	BKSGE_IS_CONST_TEST_IMPL(false, const volatile T(&)[2]);	\
	BKSGE_IS_CONST_TEST_IMPL(false,                T(&&)[2]);	\
	BKSGE_IS_CONST_TEST_IMPL(false, const          T(&&)[2]);	\
	BKSGE_IS_CONST_TEST_IMPL(false,       volatile T(&&)[2]);	\
	BKSGE_IS_CONST_TEST_IMPL(false, const volatile T(&&)[2])

GTEST_TEST(TypeTraitsTest, IsConstTest)
{
	IntegralConstantTest<bksge::is_const<int>, false>();
	IntegralConstantTest<bksge::is_const<const int>, true>();
	IntegralConstantTest<bksge::is_const<volatile int>, false>();
	IntegralConstantTest<bksge::is_const<const volatile int>, true>();

	BKSGE_IS_CONST_TEST(int);
	BKSGE_IS_CONST_TEST(float);
	BKSGE_IS_CONST_TEST(enum_UDT);
	BKSGE_IS_CONST_TEST(enum_class_UDT);
	BKSGE_IS_CONST_TEST(UDT);
	BKSGE_IS_CONST_TEST(union_UDT);
	BKSGE_IS_CONST_TEST_CV(void);
	BKSGE_IS_CONST_TEST_CV(f1);
	BKSGE_IS_CONST_TEST_CV(f2);
	BKSGE_IS_CONST_TEST_CV(f3);
	BKSGE_IS_CONST_TEST_CV(mf1);
	BKSGE_IS_CONST_TEST_CV(mf2);
	BKSGE_IS_CONST_TEST_CV(mf3);
	BKSGE_IS_CONST_TEST_CV(mf4);
	BKSGE_IS_CONST_TEST_CV(mp);
	BKSGE_IS_CONST_TEST_CV(cmf);
	BKSGE_IS_CONST_TEST_IMPL(false, foo0_t);
	BKSGE_IS_CONST_TEST_IMPL(false, foo1_t);
	BKSGE_IS_CONST_TEST_IMPL(false, foo2_t);
	BKSGE_IS_CONST_TEST_IMPL(false, foo3_t);
	BKSGE_IS_CONST_TEST_IMPL(false, foo4_t);
}

#undef BKSGE_IS_CONST_TEST_IMPL
#undef BKSGE_IS_CONST_TEST_CV
#undef BKSGE_IS_CONST_TEST
