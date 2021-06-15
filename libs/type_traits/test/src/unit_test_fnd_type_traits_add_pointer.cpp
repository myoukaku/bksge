/**
 *	@file	unit_test_fnd_type_traits_add_pointer.cpp
 *
 *	@brief	add_pointer のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/type_traits/add_pointer.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include "type_traits_test_utility.hpp"

BKSGE_TRANSFORM_TEST(bksge::add_pointer, /**/,                          *);
BKSGE_TRANSFORM_TEST(bksge::add_pointer, const,          const          *);
BKSGE_TRANSFORM_TEST(bksge::add_pointer,       volatile,       volatile *);
BKSGE_TRANSFORM_TEST(bksge::add_pointer, const volatile, const volatile *);
BKSGE_TRANSFORM_TEST(bksge::add_pointer,                &,                *);
BKSGE_TRANSFORM_TEST(bksge::add_pointer, const          &, const          *);
BKSGE_TRANSFORM_TEST(bksge::add_pointer,       volatile &,       volatile *);
BKSGE_TRANSFORM_TEST(bksge::add_pointer, const volatile &, const volatile *);
BKSGE_TRANSFORM_TEST(bksge::add_pointer,                *&,                **);
BKSGE_TRANSFORM_TEST(bksge::add_pointer, const          *&, const          **);
BKSGE_TRANSFORM_TEST(bksge::add_pointer,       volatile *&,       volatile **);
BKSGE_TRANSFORM_TEST(bksge::add_pointer, const volatile *&, const volatile **);
BKSGE_TRANSFORM_TEST(bksge::add_pointer, *,               *               *);
BKSGE_TRANSFORM_TEST(bksge::add_pointer, *const,          *const          *);
BKSGE_TRANSFORM_TEST(bksge::add_pointer, *      volatile, *      volatile *);
BKSGE_TRANSFORM_TEST(bksge::add_pointer, *const volatile, *const volatile *);
BKSGE_TRANSFORM_TEST(bksge::add_pointer, const          *, const          **);
BKSGE_TRANSFORM_TEST(bksge::add_pointer,       volatile *,       volatile **);
BKSGE_TRANSFORM_TEST(bksge::add_pointer, const volatile *, const volatile **);
BKSGE_TRANSFORM_TEST(bksge::add_pointer,               [2],                (*)[2]);
BKSGE_TRANSFORM_TEST(bksge::add_pointer, const         [2], const          (*)[2]);
BKSGE_TRANSFORM_TEST(bksge::add_pointer,       volatile[2],       volatile (*)[2]);
BKSGE_TRANSFORM_TEST(bksge::add_pointer, const volatile[2], const volatile (*)[2]);
BKSGE_TRANSFORM_TEST(bksge::add_pointer,                (&)[2],                (*)[2]);
BKSGE_TRANSFORM_TEST(bksge::add_pointer, const          (&)[2], const          (*)[2]);
BKSGE_TRANSFORM_TEST(bksge::add_pointer,       volatile (&)[2],       volatile (*)[2]);
BKSGE_TRANSFORM_TEST(bksge::add_pointer, const volatile (&)[2], const volatile (*)[2]);
BKSGE_TRANSFORM_TEST(bksge::add_pointer,                &&,                *);
BKSGE_TRANSFORM_TEST(bksge::add_pointer, const          &&, const          *);
BKSGE_TRANSFORM_TEST(bksge::add_pointer,       volatile &&,       volatile *);
BKSGE_TRANSFORM_TEST(bksge::add_pointer, const volatile &&, const volatile *);
BKSGE_TRANSFORM_TEST(bksge::add_pointer,                (&&)[2],                (*)[2]);
BKSGE_TRANSFORM_TEST(bksge::add_pointer, const          (&&)[2], const          (*)[2]);
BKSGE_TRANSFORM_TEST(bksge::add_pointer,       volatile (&&)[2],       volatile (*)[2]);
BKSGE_TRANSFORM_TEST(bksge::add_pointer, const volatile (&&)[2], const volatile (*)[2]);

#define BKSGE_ADD_POINTER_TEST(T1, T2)	\
	static_assert(bksge::is_same<bksge::add_pointer_t<T1>, T2>::value, "");	\
	static_assert(bksge::is_same<bksge::add_pointer<T1>::type, T2>::value, "")

BKSGE_ADD_POINTER_TEST(               void,                void*);
BKSGE_ADD_POINTER_TEST(const          void, const          void*);
BKSGE_ADD_POINTER_TEST(      volatile void,       volatile void*);
BKSGE_ADD_POINTER_TEST(const volatile void, const volatile void*);
BKSGE_ADD_POINTER_TEST(void(void), void(*)(void));
BKSGE_ADD_POINTER_TEST(int(void), int(*)(void));
BKSGE_ADD_POINTER_TEST(void(int), void(*)(int));
BKSGE_ADD_POINTER_TEST(int(int), int(*)(int));
BKSGE_ADD_POINTER_TEST(int(char, short), int(*)(char, short));
BKSGE_ADD_POINTER_TEST(int(float, double, long double), int(*)(float, double, long double));
BKSGE_ADD_POINTER_TEST(int(*)(int), int(**)(int));
BKSGE_ADD_POINTER_TEST(int(&)(int), int(*)(int));
BKSGE_ADD_POINTER_TEST(int(&&)(int), int(*)(int));
BKSGE_ADD_POINTER_TEST(void (UDT::*)(void), void (UDT::**)(void));
BKSGE_ADD_POINTER_TEST(int (UDT::*)(int), int (UDT::**)(int));
BKSGE_ADD_POINTER_TEST(int (UDT::*)(int, float), int (UDT::**)(int, float));
BKSGE_ADD_POINTER_TEST(int (UDT::*)(int) const, int (UDT::**)(int) const);
BKSGE_ADD_POINTER_TEST(int (UDT::*)(int) volatile, int (UDT::**)(int) volatile);
BKSGE_ADD_POINTER_TEST(int (UDT::*)(int) const volatile, int (UDT::**)(int) const volatile);
BKSGE_ADD_POINTER_TEST(int (UDT::*), int (UDT::**));
BKSGE_ADD_POINTER_TEST(const float (UDT::*), const float (UDT::**));

#undef BKSGE_ADD_POINTER_TEST
