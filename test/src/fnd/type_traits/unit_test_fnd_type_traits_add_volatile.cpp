/**
 *	@file	unit_test_fnd_type_traits_add_volatile.cpp
 *
 *	@brief	add_volatile のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/type_traits/add_volatile.hpp>
#include <type_traits>
#include <gtest/gtest.h>
#include "type_traits_test_utility.hpp"

GTEST_TEST(TypeTraitsTest, AddVolatileTest)
{
	BKSGE_TRANSFORM_TEST(bksge::add_volatile, /**/,                 volatile);
	BKSGE_TRANSFORM_TEST(bksge::add_volatile, const,          const volatile);
	BKSGE_TRANSFORM_TEST(bksge::add_volatile,       volatile,       volatile);
	BKSGE_TRANSFORM_TEST(bksge::add_volatile, const volatile, const volatile);
	BKSGE_TRANSFORM_TEST(bksge::add_volatile,                &,                &);
	BKSGE_TRANSFORM_TEST(bksge::add_volatile, const          &, const          &);
	BKSGE_TRANSFORM_TEST(bksge::add_volatile,       volatile &,       volatile &);
	BKSGE_TRANSFORM_TEST(bksge::add_volatile, const volatile &, const volatile &);
	BKSGE_TRANSFORM_TEST(bksge::add_volatile, *,               *      volatile);
	BKSGE_TRANSFORM_TEST(bksge::add_volatile, *const,          *const volatile);
	BKSGE_TRANSFORM_TEST(bksge::add_volatile, *      volatile, *      volatile);
	BKSGE_TRANSFORM_TEST(bksge::add_volatile, *const volatile, *const volatile);
	BKSGE_TRANSFORM_TEST(bksge::add_volatile, const          *, const          * volatile);
	BKSGE_TRANSFORM_TEST(bksge::add_volatile,       volatile *,       volatile * volatile);
	BKSGE_TRANSFORM_TEST(bksge::add_volatile, const volatile *, const volatile * volatile);
	BKSGE_TRANSFORM_TEST(bksge::add_volatile,               [2],       volatile[2]);
	BKSGE_TRANSFORM_TEST(bksge::add_volatile, const         [2], const volatile[2]);
	BKSGE_TRANSFORM_TEST(bksge::add_volatile,       volatile[2],       volatile[2]);
	BKSGE_TRANSFORM_TEST(bksge::add_volatile, const volatile[2], const volatile[2]);
	BKSGE_TRANSFORM_TEST(bksge::add_volatile,                (&)[2],                (&)[2]);
	BKSGE_TRANSFORM_TEST(bksge::add_volatile, const          (&)[2], const          (&)[2]);
	BKSGE_TRANSFORM_TEST(bksge::add_volatile,       volatile (&)[2],       volatile (&)[2]);
	BKSGE_TRANSFORM_TEST(bksge::add_volatile, const volatile (&)[2], const volatile (&)[2]);
	BKSGE_TRANSFORM_TEST(bksge::add_volatile,                &&,                &&);
	BKSGE_TRANSFORM_TEST(bksge::add_volatile, const          &&, const          &&);
	BKSGE_TRANSFORM_TEST(bksge::add_volatile,       volatile &&,       volatile &&);
	BKSGE_TRANSFORM_TEST(bksge::add_volatile, const volatile &&, const volatile &&);
	BKSGE_TRANSFORM_TEST(bksge::add_volatile,                (&&)[2],                (&&)[2]);
	BKSGE_TRANSFORM_TEST(bksge::add_volatile, const          (&&)[2], const          (&&)[2]);
	BKSGE_TRANSFORM_TEST(bksge::add_volatile,       volatile (&&)[2],       volatile (&&)[2]);
	BKSGE_TRANSFORM_TEST(bksge::add_volatile, const volatile (&&)[2], const volatile (&&)[2]);

#define BKSGE_ADD_VOLATILE_TEST(T1, T2)	\
	static_assert(std::is_same<bksge::add_volatile_t<T1>, T2>::value, "");	\
	static_assert(std::is_same<bksge::add_volatile<T1>::type, T2>::value, "")

	BKSGE_ADD_VOLATILE_TEST(               void,       volatile void);
	BKSGE_ADD_VOLATILE_TEST(const          void, const volatile void);
	BKSGE_ADD_VOLATILE_TEST(      volatile void,       volatile void);
	BKSGE_ADD_VOLATILE_TEST(const volatile void, const volatile void);
	BKSGE_ADD_VOLATILE_TEST(               void*,                void* volatile);
	BKSGE_ADD_VOLATILE_TEST(const          void*, const          void* volatile);
	BKSGE_ADD_VOLATILE_TEST(      volatile void*,       volatile void* volatile);
	BKSGE_ADD_VOLATILE_TEST(const volatile void*, const volatile void* volatile);
	BKSGE_ADD_VOLATILE_TEST(int(int), int(int));
	BKSGE_ADD_VOLATILE_TEST(void (UDT::*)(void), void (UDT::* volatile)(void));
	BKSGE_ADD_VOLATILE_TEST(int (UDT::*)(int), int (UDT::* volatile)(int));
	BKSGE_ADD_VOLATILE_TEST(int (UDT::*)(int, float), int (UDT::* volatile)(int, float));
	BKSGE_ADD_VOLATILE_TEST(int (UDT::*)(int) const, int (UDT::* volatile)(int) const);
	BKSGE_ADD_VOLATILE_TEST(int (UDT::*)(int) volatile, int (UDT::* volatile)(int) volatile);
	BKSGE_ADD_VOLATILE_TEST(int (UDT::*)(int) const volatile, int (UDT::* volatile)(int) const volatile);
	BKSGE_ADD_VOLATILE_TEST(int (UDT::*), int (UDT::* volatile));
	BKSGE_ADD_VOLATILE_TEST(const float (UDT::*), const float (UDT::* volatile));

#undef BKSGE_ADD_VOLATILE_TEST
}
