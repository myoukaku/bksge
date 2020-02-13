/**
 *	@file	unit_test_fnd_type_traits_add_const.cpp
 *
 *	@brief	add_const のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/type_traits/add_const.hpp>
#include <type_traits>
#include <gtest/gtest.h>
#include "type_traits_test_utility.hpp"

GTEST_TEST(TypeTraitsTest, AddConstTest)
{
	BKSGE_TRANSFORM_TEST(bksge::add_const, /**/,           const);
	BKSGE_TRANSFORM_TEST(bksge::add_const, const,          const);
	BKSGE_TRANSFORM_TEST(bksge::add_const,       volatile, const volatile);
	BKSGE_TRANSFORM_TEST(bksge::add_const, const volatile, const volatile);
	BKSGE_TRANSFORM_TEST(bksge::add_const,                &,                &);
	BKSGE_TRANSFORM_TEST(bksge::add_const, const          &, const          &);
	BKSGE_TRANSFORM_TEST(bksge::add_const,       volatile &,       volatile &);
	BKSGE_TRANSFORM_TEST(bksge::add_const, const volatile &, const volatile &);
	BKSGE_TRANSFORM_TEST(bksge::add_const, *,               *const);
	BKSGE_TRANSFORM_TEST(bksge::add_const, *const,          *const);
	BKSGE_TRANSFORM_TEST(bksge::add_const, *      volatile, *const volatile);
	BKSGE_TRANSFORM_TEST(bksge::add_const, *const volatile, *const volatile);
	BKSGE_TRANSFORM_TEST(bksge::add_const, const          *, const          * const);
	BKSGE_TRANSFORM_TEST(bksge::add_const,       volatile *,       volatile * const);
	BKSGE_TRANSFORM_TEST(bksge::add_const, const volatile *, const volatile * const);
	BKSGE_TRANSFORM_TEST(bksge::add_const,               [2], const         [2]);
	BKSGE_TRANSFORM_TEST(bksge::add_const, const         [2], const         [2]);
	BKSGE_TRANSFORM_TEST(bksge::add_const,       volatile[2], const volatile[2]);
	BKSGE_TRANSFORM_TEST(bksge::add_const, const volatile[2], const volatile[2]);
	BKSGE_TRANSFORM_TEST(bksge::add_const,                (&)[2],                (&)[2]);
	BKSGE_TRANSFORM_TEST(bksge::add_const, const          (&)[2], const          (&)[2]);
	BKSGE_TRANSFORM_TEST(bksge::add_const,       volatile (&)[2],       volatile (&)[2]);
	BKSGE_TRANSFORM_TEST(bksge::add_const, const volatile (&)[2], const volatile (&)[2]);
	BKSGE_TRANSFORM_TEST(bksge::add_const,                &&,                &&);
	BKSGE_TRANSFORM_TEST(bksge::add_const, const          &&, const          &&);
	BKSGE_TRANSFORM_TEST(bksge::add_const,       volatile &&,       volatile &&);
	BKSGE_TRANSFORM_TEST(bksge::add_const, const volatile &&, const volatile &&);
	BKSGE_TRANSFORM_TEST(bksge::add_const,                (&&)[2],                (&&)[2]);
	BKSGE_TRANSFORM_TEST(bksge::add_const, const          (&&)[2], const          (&&)[2]);
	BKSGE_TRANSFORM_TEST(bksge::add_const,       volatile (&&)[2],       volatile (&&)[2]);
	BKSGE_TRANSFORM_TEST(bksge::add_const, const volatile (&&)[2], const volatile (&&)[2]);

#define BKSGE_ADD_CONST_TEST(T1, T2)	\
	static_assert(std::is_same<bksge::add_const_t<T1>, T2>::value, "");	\
	static_assert(std::is_same<bksge::add_const<T1>::type, T2>::value, "")

	BKSGE_ADD_CONST_TEST(               void, const          void);
	BKSGE_ADD_CONST_TEST(const          void, const          void);
	BKSGE_ADD_CONST_TEST(      volatile void, const volatile void);
	BKSGE_ADD_CONST_TEST(const volatile void, const volatile void);
	BKSGE_ADD_CONST_TEST(               void*,                void* const);
	BKSGE_ADD_CONST_TEST(const          void*, const          void* const);
	BKSGE_ADD_CONST_TEST(      volatile void*,       volatile void* const);
	BKSGE_ADD_CONST_TEST(const volatile void*, const volatile void* const);
	BKSGE_ADD_CONST_TEST(int(int), int(int));
	BKSGE_ADD_CONST_TEST(void (UDT::*)(void), void (UDT::* const)(void));
	BKSGE_ADD_CONST_TEST(int (UDT::*)(int), int (UDT::* const)(int));
	BKSGE_ADD_CONST_TEST(int (UDT::*)(int, float), int (UDT::* const)(int, float));
	BKSGE_ADD_CONST_TEST(int (UDT::*)(int) const, int (UDT::* const)(int) const);
	BKSGE_ADD_CONST_TEST(int (UDT::*)(int) volatile, int (UDT::* const)(int) volatile);
	BKSGE_ADD_CONST_TEST(int (UDT::*)(int) const volatile, int (UDT::* const)(int) const volatile);
	BKSGE_ADD_CONST_TEST(int (UDT::*), int (UDT::* const));
	BKSGE_ADD_CONST_TEST(const float (UDT::*), const float (UDT::* const));

#undef BKSGE_ADD_CONST_TEST
}
