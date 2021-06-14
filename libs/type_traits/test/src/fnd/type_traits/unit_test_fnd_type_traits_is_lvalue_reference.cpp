/**
 *	@file	unit_test_fnd_type_traits_is_lvalue_reference.cpp
 *
 *	@brief	is_lvalue_reference のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/type_traits/is_lvalue_reference.hpp>
#include <bksge/fnd/config.hpp>
#include <gtest/gtest.h>
#include "type_traits_test_utility.hpp"

#if defined(BKSGE_HAS_CXX14_VARIABLE_TEMPLATES)

#define BKSGE_IS_LVALUE_REFERENCE_TEST_IMPL(b, T)	\
	static_assert(bksge::is_lvalue_reference_v<T>      == b, #T);	\
	static_assert(bksge::is_lvalue_reference<T>::value == b, #T);	\
	static_assert(bksge::is_lvalue_reference<T>()      == b, #T)

#else

#define BKSGE_IS_LVALUE_REFERENCE_TEST_IMPL(b, T)	\
	static_assert(bksge::is_lvalue_reference<T>::value == b, #T);	\
	static_assert(bksge::is_lvalue_reference<T>()      == b, #T)

#endif

#define BKSGE_IS_LVALUE_REFERENCE_TEST_CV(b, T)	                \
	BKSGE_IS_LVALUE_REFERENCE_TEST_IMPL(b,                T);	\
	BKSGE_IS_LVALUE_REFERENCE_TEST_IMPL(b, const          T);	\
	BKSGE_IS_LVALUE_REFERENCE_TEST_IMPL(b,       volatile T);	\
	BKSGE_IS_LVALUE_REFERENCE_TEST_IMPL(b, const volatile T)

#define BKSGE_IS_LVALUE_REFERENCE_TEST(T)	                        \
	BKSGE_IS_LVALUE_REFERENCE_TEST_CV(false, T);	                \
	BKSGE_IS_LVALUE_REFERENCE_TEST_CV(false, T*);	                \
	BKSGE_IS_LVALUE_REFERENCE_TEST_CV(false, T* const);	            \
	BKSGE_IS_LVALUE_REFERENCE_TEST_CV(false, T* volatile);	        \
	BKSGE_IS_LVALUE_REFERENCE_TEST_CV(false, T* const volatile);	\
	BKSGE_IS_LVALUE_REFERENCE_TEST_CV(false, T**);	                \
	BKSGE_IS_LVALUE_REFERENCE_TEST_CV(true,  T&);	                \
	BKSGE_IS_LVALUE_REFERENCE_TEST_CV(false, T&&);	                \
	BKSGE_IS_LVALUE_REFERENCE_TEST_CV(false, T[2]);	                \
	BKSGE_IS_LVALUE_REFERENCE_TEST_CV(false, T[]);	                \
	BKSGE_IS_LVALUE_REFERENCE_TEST_CV(true,  T(&)[2]);	            \
	BKSGE_IS_LVALUE_REFERENCE_TEST_CV(true,  T(&)[]);	            \
	BKSGE_IS_LVALUE_REFERENCE_TEST_CV(false, T(&&)[2]);	            \
	BKSGE_IS_LVALUE_REFERENCE_TEST_CV(false, T(&&)[])

BKSGE_IS_LVALUE_REFERENCE_TEST(int);
BKSGE_IS_LVALUE_REFERENCE_TEST(bool);
BKSGE_IS_LVALUE_REFERENCE_TEST(char);
BKSGE_IS_LVALUE_REFERENCE_TEST(float);
BKSGE_IS_LVALUE_REFERENCE_TEST(UDT);
BKSGE_IS_LVALUE_REFERENCE_TEST(POD_UDT);
BKSGE_IS_LVALUE_REFERENCE_TEST(enum_UDT);

BKSGE_IS_LVALUE_REFERENCE_TEST_CV(false, void);

BKSGE_IS_LVALUE_REFERENCE_TEST_IMPL(false, f1);
BKSGE_IS_LVALUE_REFERENCE_TEST_IMPL(false, f2);
BKSGE_IS_LVALUE_REFERENCE_TEST_IMPL(false, f3);
BKSGE_IS_LVALUE_REFERENCE_TEST_IMPL(false, mf1);
BKSGE_IS_LVALUE_REFERENCE_TEST_IMPL(false, mf2);
BKSGE_IS_LVALUE_REFERENCE_TEST_IMPL(false, mf3);
BKSGE_IS_LVALUE_REFERENCE_TEST_IMPL(false, mf4);
BKSGE_IS_LVALUE_REFERENCE_TEST_IMPL(false, mp);
BKSGE_IS_LVALUE_REFERENCE_TEST_IMPL(false, cmf);
BKSGE_IS_LVALUE_REFERENCE_TEST_IMPL(false, foo0_t);
BKSGE_IS_LVALUE_REFERENCE_TEST_IMPL(false, foo1_t);
BKSGE_IS_LVALUE_REFERENCE_TEST_IMPL(false, foo2_t);
BKSGE_IS_LVALUE_REFERENCE_TEST_IMPL(false, foo3_t);
BKSGE_IS_LVALUE_REFERENCE_TEST_IMPL(false, foo4_t);

#undef BKSGE_IS_LVALUE_REFERENCE_TEST_IMPL
#undef BKSGE_IS_LVALUE_REFERENCE_TEST_CV
#undef BKSGE_IS_LVALUE_REFERENCE_TEST
