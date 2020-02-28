/**
 *	@file	unit_test_fnd_type_traits_add_rvalue_reference.cpp
 *
 *	@brief	add_rvalue_reference のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/type_traits/add_rvalue_reference.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include "type_traits_test_utility.hpp"

GTEST_TEST(TypeTraitsTest, AddRvalueReferenceTest)
{
	BKSGE_TRANSFORM_TEST(bksge::add_rvalue_reference, /**/,                          &&);
	BKSGE_TRANSFORM_TEST(bksge::add_rvalue_reference, const,          const          &&);
	BKSGE_TRANSFORM_TEST(bksge::add_rvalue_reference,       volatile,       volatile &&);
	BKSGE_TRANSFORM_TEST(bksge::add_rvalue_reference, const volatile, const volatile &&);
	BKSGE_TRANSFORM_TEST(bksge::add_rvalue_reference,                &,                &);
	BKSGE_TRANSFORM_TEST(bksge::add_rvalue_reference, const          &, const          &);
	BKSGE_TRANSFORM_TEST(bksge::add_rvalue_reference,       volatile &,       volatile &);
	BKSGE_TRANSFORM_TEST(bksge::add_rvalue_reference, const volatile &, const volatile &);
	BKSGE_TRANSFORM_TEST(bksge::add_rvalue_reference,                *&,                *&);
	BKSGE_TRANSFORM_TEST(bksge::add_rvalue_reference, const          *&, const          *&);
	BKSGE_TRANSFORM_TEST(bksge::add_rvalue_reference,       volatile *&,       volatile *&);
	BKSGE_TRANSFORM_TEST(bksge::add_rvalue_reference, const volatile *&, const volatile *&);
	BKSGE_TRANSFORM_TEST(bksge::add_rvalue_reference, *,               *               &&);
	BKSGE_TRANSFORM_TEST(bksge::add_rvalue_reference, *const,          *const          &&);
	BKSGE_TRANSFORM_TEST(bksge::add_rvalue_reference, *      volatile, *      volatile &&);
	BKSGE_TRANSFORM_TEST(bksge::add_rvalue_reference, *const volatile, *const volatile &&);
	BKSGE_TRANSFORM_TEST(bksge::add_rvalue_reference, const          *, const          *&&);
	BKSGE_TRANSFORM_TEST(bksge::add_rvalue_reference,       volatile *,       volatile *&&);
	BKSGE_TRANSFORM_TEST(bksge::add_rvalue_reference, const volatile *, const volatile *&&);
	BKSGE_TRANSFORM_TEST(bksge::add_rvalue_reference,               [2],                (&&)[2]);
	BKSGE_TRANSFORM_TEST(bksge::add_rvalue_reference, const         [2], const          (&&)[2]);
	BKSGE_TRANSFORM_TEST(bksge::add_rvalue_reference,       volatile[2],       volatile (&&)[2]);
	BKSGE_TRANSFORM_TEST(bksge::add_rvalue_reference, const volatile[2], const volatile (&&)[2]);
	BKSGE_TRANSFORM_TEST(bksge::add_rvalue_reference,                (&)[2],                (&)[2]);
	BKSGE_TRANSFORM_TEST(bksge::add_rvalue_reference, const          (&)[2], const          (&)[2]);
	BKSGE_TRANSFORM_TEST(bksge::add_rvalue_reference,       volatile (&)[2],       volatile (&)[2]);
	BKSGE_TRANSFORM_TEST(bksge::add_rvalue_reference, const volatile (&)[2], const volatile (&)[2]);
	BKSGE_TRANSFORM_TEST(bksge::add_rvalue_reference,                &&,                &&);
	BKSGE_TRANSFORM_TEST(bksge::add_rvalue_reference, const          &&, const          &&);
	BKSGE_TRANSFORM_TEST(bksge::add_rvalue_reference,       volatile &&,       volatile &&);
	BKSGE_TRANSFORM_TEST(bksge::add_rvalue_reference, const volatile &&, const volatile &&);
	BKSGE_TRANSFORM_TEST(bksge::add_rvalue_reference,                (&&)[2],                (&&)[2]);
	BKSGE_TRANSFORM_TEST(bksge::add_rvalue_reference, const          (&&)[2], const          (&&)[2]);
	BKSGE_TRANSFORM_TEST(bksge::add_rvalue_reference,       volatile (&&)[2],       volatile (&&)[2]);
	BKSGE_TRANSFORM_TEST(bksge::add_rvalue_reference, const volatile (&&)[2], const volatile (&&)[2]);

#define BKSGE_ADD_RVALUE_REFERENCE_TEST(T1, T2)	\
	static_assert(bksge::is_same<bksge::add_rvalue_reference_t<T1>, T2>::value, "");	\
	static_assert(bksge::is_same<bksge::add_rvalue_reference<T1>::type, T2>::value, "")

	BKSGE_ADD_RVALUE_REFERENCE_TEST(void(void), void(&&)(void));
	BKSGE_ADD_RVALUE_REFERENCE_TEST(int(void), int(&&)(void));
	BKSGE_ADD_RVALUE_REFERENCE_TEST(void(int), void(&&)(int));
	BKSGE_ADD_RVALUE_REFERENCE_TEST(int(int), int(&&)(int));
	BKSGE_ADD_RVALUE_REFERENCE_TEST(int(char, short), int(&&)(char, short));
	BKSGE_ADD_RVALUE_REFERENCE_TEST(int(float, double, long double), int(&&)(float, double, long double));
	BKSGE_ADD_RVALUE_REFERENCE_TEST(int(*)(int), int(*&&)(int));
	BKSGE_ADD_RVALUE_REFERENCE_TEST(int(&)(int), int(&)(int));
	BKSGE_ADD_RVALUE_REFERENCE_TEST(int(&&)(int), int(&&)(int));
	BKSGE_ADD_RVALUE_REFERENCE_TEST(void (UDT::*)(void), void (UDT::*&&)(void));
	BKSGE_ADD_RVALUE_REFERENCE_TEST(int (UDT::*)(int), int (UDT::*&&)(int));
	BKSGE_ADD_RVALUE_REFERENCE_TEST(int (UDT::*)(int, float), int (UDT::*&&)(int, float));
	BKSGE_ADD_RVALUE_REFERENCE_TEST(int (UDT::*)(int) const, int (UDT::*&&)(int) const);
	BKSGE_ADD_RVALUE_REFERENCE_TEST(int (UDT::*)(int) volatile, int (UDT::*&&)(int) volatile);
	BKSGE_ADD_RVALUE_REFERENCE_TEST(int (UDT::*)(int) const volatile, int (UDT::*&&)(int) const volatile);
	BKSGE_ADD_RVALUE_REFERENCE_TEST(int (UDT::*), int (UDT::*&&));
	BKSGE_ADD_RVALUE_REFERENCE_TEST(const float (UDT::*), const float (UDT::*&&));

#undef BKSGE_ADD_RVALUE_REFERENCE_TEST
}
