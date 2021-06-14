/**
 *	@file	unit_test_fnd_type_traits_is_member_pointer.cpp
 *
 *	@brief	is_member_pointer のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/type_traits/is_member_pointer.hpp>
#include <bksge/fnd/config.hpp>
#include <gtest/gtest.h>
#include "type_traits_test_utility.hpp"

#if defined(BKSGE_HAS_CXX14_VARIABLE_TEMPLATES)

#define BKSGE_IS_MEMBER_POINTER_TEST_IMPL(b, T)	\
	static_assert(bksge::is_member_pointer_v<T>      == b, #T);	\
	static_assert(bksge::is_member_pointer<T>::value == b, #T);	\
	static_assert(bksge::is_member_pointer<T>()      == b, #T)

#else

#define BKSGE_IS_MEMBER_POINTER_TEST_IMPL(b, T)	\
	static_assert(bksge::is_member_pointer<T>::value == b, #T);	\
	static_assert(bksge::is_member_pointer<T>()      == b, #T)

#endif

BKSGE_IS_MEMBER_POINTER_TEST_IMPL(false, int);
BKSGE_IS_MEMBER_POINTER_TEST_IMPL(false, int*);
BKSGE_IS_MEMBER_POINTER_TEST_IMPL(false, int**);
BKSGE_IS_MEMBER_POINTER_TEST_IMPL(false, int&);
BKSGE_IS_MEMBER_POINTER_TEST_IMPL(false, int&&);
BKSGE_IS_MEMBER_POINTER_TEST_IMPL(false, int[2]);
BKSGE_IS_MEMBER_POINTER_TEST_IMPL(false, int[]);
BKSGE_IS_MEMBER_POINTER_TEST_IMPL(false, int(*)[2]);
BKSGE_IS_MEMBER_POINTER_TEST_IMPL(false, int(*)[]);
BKSGE_IS_MEMBER_POINTER_TEST_IMPL(false, int(&)[2]);
BKSGE_IS_MEMBER_POINTER_TEST_IMPL(false, int(&)[]);
BKSGE_IS_MEMBER_POINTER_TEST_IMPL(false, int(&&)[2]);
BKSGE_IS_MEMBER_POINTER_TEST_IMPL(false, int(&&)[]);
BKSGE_IS_MEMBER_POINTER_TEST_IMPL(true, int(UDT::*));
BKSGE_IS_MEMBER_POINTER_TEST_IMPL(true, char(UDT::*));
BKSGE_IS_MEMBER_POINTER_TEST_IMPL(true, char(UDT::* const));
BKSGE_IS_MEMBER_POINTER_TEST_IMPL(true, char(UDT::* volatile));
BKSGE_IS_MEMBER_POINTER_TEST_IMPL(true, char(UDT::* const volatile));
BKSGE_IS_MEMBER_POINTER_TEST_IMPL(true, int*(UDT::*));
BKSGE_IS_MEMBER_POINTER_TEST_IMPL(true, void*(UDT::*));
BKSGE_IS_MEMBER_POINTER_TEST_IMPL(true, int(UDT::*)());
BKSGE_IS_MEMBER_POINTER_TEST_IMPL(true, int(UDT::* const)());
BKSGE_IS_MEMBER_POINTER_TEST_IMPL(true, int(UDT::* volatile)());
BKSGE_IS_MEMBER_POINTER_TEST_IMPL(true, int(UDT::* const volatile)());
BKSGE_IS_MEMBER_POINTER_TEST_IMPL(true, float(UDT::*)() const);
BKSGE_IS_MEMBER_POINTER_TEST_IMPL(true, short(UDT::*)() volatile);
BKSGE_IS_MEMBER_POINTER_TEST_IMPL(true, double(UDT::*)() const volatile);
BKSGE_IS_MEMBER_POINTER_TEST_IMPL(true, void(UDT::*)(int));
BKSGE_IS_MEMBER_POINTER_TEST_IMPL(true, void(UDT::*)(int, int) const);
BKSGE_IS_MEMBER_POINTER_TEST_IMPL(true, void(UDT::*)(int, int, int) volatile);
BKSGE_IS_MEMBER_POINTER_TEST_IMPL(true, void(UDT::*)(int, float, char, long) const volatile);
BKSGE_IS_MEMBER_POINTER_TEST_IMPL(false, f1);
BKSGE_IS_MEMBER_POINTER_TEST_IMPL(false, f2);
BKSGE_IS_MEMBER_POINTER_TEST_IMPL(false, f3);
BKSGE_IS_MEMBER_POINTER_TEST_IMPL(true,  mf1);
BKSGE_IS_MEMBER_POINTER_TEST_IMPL(true,  mf2);
BKSGE_IS_MEMBER_POINTER_TEST_IMPL(true,  mf3);
BKSGE_IS_MEMBER_POINTER_TEST_IMPL(true,  mf4);
BKSGE_IS_MEMBER_POINTER_TEST_IMPL(true,  mp);
BKSGE_IS_MEMBER_POINTER_TEST_IMPL(true,  cmf);
BKSGE_IS_MEMBER_POINTER_TEST_IMPL(false, mf1&);
BKSGE_IS_MEMBER_POINTER_TEST_IMPL(false, mf2&);
BKSGE_IS_MEMBER_POINTER_TEST_IMPL(false, mf3&);
BKSGE_IS_MEMBER_POINTER_TEST_IMPL(false, mf4&);
BKSGE_IS_MEMBER_POINTER_TEST_IMPL(false, mp&);
BKSGE_IS_MEMBER_POINTER_TEST_IMPL(false, cmf&);
BKSGE_IS_MEMBER_POINTER_TEST_IMPL(false, foo0_t);
BKSGE_IS_MEMBER_POINTER_TEST_IMPL(false, foo1_t);
BKSGE_IS_MEMBER_POINTER_TEST_IMPL(false, foo2_t);
BKSGE_IS_MEMBER_POINTER_TEST_IMPL(false, foo3_t);
BKSGE_IS_MEMBER_POINTER_TEST_IMPL(false, foo4_t);

#undef BKSGE_IS_MEMBER_POINTER_TEST_IMPL
