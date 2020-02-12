/**
 *	@file	unit_test_fnd_type_traits_remove_pointer.cpp
 *
 *	@brief	remove_pointer のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/type_traits/remove_pointer.hpp>
#include <type_traits>
#include <gtest/gtest.h>
#include "type_traits_test_utility.hpp"

GTEST_TEST(TypeTraitsTest, RemovePointerTest)
{
	BKSGE_TRANSFORM_TEST(bksge::remove_pointer, /**/          , /**/          );
	BKSGE_TRANSFORM_TEST(bksge::remove_pointer, const         , const         );
	BKSGE_TRANSFORM_TEST(bksge::remove_pointer,       volatile,       volatile);
	BKSGE_TRANSFORM_TEST(bksge::remove_pointer, const volatile, const volatile);
	BKSGE_TRANSFORM_TEST(bksge::remove_pointer,                &,                &);
	BKSGE_TRANSFORM_TEST(bksge::remove_pointer, const          &, const          &);
	BKSGE_TRANSFORM_TEST(bksge::remove_pointer,       volatile &,       volatile &);
	BKSGE_TRANSFORM_TEST(bksge::remove_pointer, const volatile &, const volatile &);
	BKSGE_TRANSFORM_TEST(bksge::remove_pointer, *               , /**/);
	BKSGE_TRANSFORM_TEST(bksge::remove_pointer, * const         , /**/);
	BKSGE_TRANSFORM_TEST(bksge::remove_pointer, *       volatile, /**/);
	BKSGE_TRANSFORM_TEST(bksge::remove_pointer, * const volatile, /**/);
	BKSGE_TRANSFORM_TEST(bksge::remove_pointer, const          *, const         );
	BKSGE_TRANSFORM_TEST(bksge::remove_pointer,       volatile *,       volatile);
	BKSGE_TRANSFORM_TEST(bksge::remove_pointer, const volatile *, const volatile);
	BKSGE_TRANSFORM_TEST(bksge::remove_pointer,                [2],                [2]);
	BKSGE_TRANSFORM_TEST(bksge::remove_pointer, const          [2], const          [2]);
	BKSGE_TRANSFORM_TEST(bksge::remove_pointer,       volatile [2],       volatile [2]);
	BKSGE_TRANSFORM_TEST(bksge::remove_pointer, const volatile [2], const volatile [2]);
	BKSGE_TRANSFORM_TEST(bksge::remove_pointer,                (&)[2],                (&)[2]);
	BKSGE_TRANSFORM_TEST(bksge::remove_pointer, const          (&)[2], const          (&)[2]);
	BKSGE_TRANSFORM_TEST(bksge::remove_pointer,       volatile (&)[2],       volatile (&)[2]);
	BKSGE_TRANSFORM_TEST(bksge::remove_pointer, const volatile (&)[2], const volatile (&)[2]);
	BKSGE_TRANSFORM_TEST(bksge::remove_pointer,                &&,                &&);
	BKSGE_TRANSFORM_TEST(bksge::remove_pointer, const          &&, const          &&);
	BKSGE_TRANSFORM_TEST(bksge::remove_pointer,       volatile &&,       volatile &&);
	BKSGE_TRANSFORM_TEST(bksge::remove_pointer, const volatile &&, const volatile &&);
	BKSGE_TRANSFORM_TEST(bksge::remove_pointer,                (&&)[2],                (&&)[2]);
	BKSGE_TRANSFORM_TEST(bksge::remove_pointer, const          (&&)[2], const          (&&)[2]);
	BKSGE_TRANSFORM_TEST(bksge::remove_pointer,       volatile (&&)[2],       volatile (&&)[2]);
	BKSGE_TRANSFORM_TEST(bksge::remove_pointer, const volatile (&&)[2], const volatile (&&)[2]);

#define BKSGE_REMOVE_POINTER_TEST(T1, T2)	\
	static_assert(std::is_same<bksge::remove_pointer_t<T1>, T2>::value, "");	\
	static_assert(std::is_same<bksge::remove_pointer<T1>::type, T2>::value, "")

	BKSGE_REMOVE_POINTER_TEST(               void*,                void);
	BKSGE_REMOVE_POINTER_TEST(const          void*, const          void);
	BKSGE_REMOVE_POINTER_TEST(      volatile void*,       volatile void);
	BKSGE_REMOVE_POINTER_TEST(const volatile void*, const volatile void);
	BKSGE_REMOVE_POINTER_TEST(void(void), void(void));
	BKSGE_REMOVE_POINTER_TEST(int(void), int(void));
	BKSGE_REMOVE_POINTER_TEST(void(int), void(int));
	BKSGE_REMOVE_POINTER_TEST(int(int), int(int));
	BKSGE_REMOVE_POINTER_TEST(int(char, short), int(char, short));
	BKSGE_REMOVE_POINTER_TEST(int(float, double, long double), int(float, double, long double));
	BKSGE_REMOVE_POINTER_TEST(int(*)(int), int(int));
	BKSGE_REMOVE_POINTER_TEST(int(&)(int), int(&)(int));
	BKSGE_REMOVE_POINTER_TEST(int(&&)(int), int(&&)(int));
	BKSGE_REMOVE_POINTER_TEST(void (UDT::*)(void), void (UDT::*)(void));
	BKSGE_REMOVE_POINTER_TEST(int (UDT::*)(int), int (UDT::*)(int));
	BKSGE_REMOVE_POINTER_TEST(int (UDT::*)(int, float), int (UDT::*)(int, float));
	BKSGE_REMOVE_POINTER_TEST(int (UDT::*)(int) const, int (UDT::*)(int) const);
	BKSGE_REMOVE_POINTER_TEST(int (UDT::*)(int) volatile, int (UDT::*)(int) volatile);
	BKSGE_REMOVE_POINTER_TEST(int (UDT::*)(int) const volatile, int (UDT::*)(int) const volatile);
	BKSGE_REMOVE_POINTER_TEST(int (UDT::*), int (UDT::*));
	BKSGE_REMOVE_POINTER_TEST(const float (UDT::*), const float (UDT::*));

#undef BKSGE_REMOVE_POINTER_TEST
}
