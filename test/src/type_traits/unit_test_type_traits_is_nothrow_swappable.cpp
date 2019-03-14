/**
 *	@file	unit_test_type_traits_is_nothrow_swappable.cpp
 *
 *	@brief	is_nothrow_swappable のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/type_traits/is_nothrow_swappable.hpp>
#include <bksge/config.hpp>
#include <gtest/gtest.h>
#include "type_traits_test_utility.hpp"

#define BKSGE_IS_NOTHROW_SWAPPABLE_TEST(b, T)	\
	static_assert(bksge::is_nothrow_swappable<T>::value == b, #T)

namespace bksge_type_traits_test
{

namespace is_nothrow_swappable_test
{

struct SwapThrow1 {};

void swap(SwapThrow1&, SwapThrow1&);

struct SwapThrow2
{
	SwapThrow2() BKSGE_NOEXCEPT = default;
	SwapThrow2(const SwapThrow2&) BKSGE_NOEXCEPT_IF(false);
	SwapThrow2& operator=(const SwapThrow2&) BKSGE_NOEXCEPT_IF(false);
};

struct SwapNoThrow1
{
	SwapNoThrow1() BKSGE_NOEXCEPT = default;
	SwapNoThrow1(const SwapNoThrow1&) BKSGE_NOEXCEPT_IF(false);
	SwapNoThrow1& operator=(const SwapNoThrow1&) BKSGE_NOEXCEPT_IF(false);
};

void swap(SwapNoThrow1&, SwapNoThrow1&) BKSGE_NOEXCEPT;

struct SwapNoThrow2 {};

GTEST_TEST(TypeTraitsTest, IsNothrowSwappableTest)
{
	IntegralConstantTest<bksge::is_nothrow_swappable<int>, true>();
	IntegralConstantTest<bksge::is_nothrow_swappable<void>, false>();

#if !defined(BKSGE_NO_CXX11_NOEXCEPT)
	BKSGE_IS_NOTHROW_SWAPPABLE_TEST(false, SwapThrow1);
	BKSGE_IS_NOTHROW_SWAPPABLE_TEST(false, SwapThrow2);
#else
	BKSGE_IS_NOTHROW_SWAPPABLE_TEST(true,  SwapThrow1);
	BKSGE_IS_NOTHROW_SWAPPABLE_TEST(true,  SwapThrow2);
#endif
	BKSGE_IS_NOTHROW_SWAPPABLE_TEST(true,  SwapNoThrow1);
	BKSGE_IS_NOTHROW_SWAPPABLE_TEST(true,  SwapNoThrow2);

	BKSGE_IS_NOTHROW_SWAPPABLE_TEST(true,                 int);
	BKSGE_IS_NOTHROW_SWAPPABLE_TEST(false, const          int);
	BKSGE_IS_NOTHROW_SWAPPABLE_TEST(true,        volatile int);
	BKSGE_IS_NOTHROW_SWAPPABLE_TEST(false, const volatile int);
	BKSGE_IS_NOTHROW_SWAPPABLE_TEST(true,                 bool);
	BKSGE_IS_NOTHROW_SWAPPABLE_TEST(false, const          bool);
	BKSGE_IS_NOTHROW_SWAPPABLE_TEST(true,        volatile bool);
	BKSGE_IS_NOTHROW_SWAPPABLE_TEST(false, const volatile bool);
	BKSGE_IS_NOTHROW_SWAPPABLE_TEST(false,                int[]);
	BKSGE_IS_NOTHROW_SWAPPABLE_TEST(false, const          int[]);
	BKSGE_IS_NOTHROW_SWAPPABLE_TEST(false,       volatile int[]);
	BKSGE_IS_NOTHROW_SWAPPABLE_TEST(false, const volatile int[]);
	BKSGE_IS_NOTHROW_SWAPPABLE_TEST(true,                 int[2]);
	BKSGE_IS_NOTHROW_SWAPPABLE_TEST(false, const          int[2]);
	BKSGE_IS_NOTHROW_SWAPPABLE_TEST(true,        volatile int[2]);
	BKSGE_IS_NOTHROW_SWAPPABLE_TEST(false, const volatile int[2]);
	BKSGE_IS_NOTHROW_SWAPPABLE_TEST(false,                int[][3]);
	BKSGE_IS_NOTHROW_SWAPPABLE_TEST(false, const          int[][3]);
	BKSGE_IS_NOTHROW_SWAPPABLE_TEST(false,       volatile int[][3]);
	BKSGE_IS_NOTHROW_SWAPPABLE_TEST(false, const volatile int[][3]);
	BKSGE_IS_NOTHROW_SWAPPABLE_TEST(true,                 int[1][2][3]);
	BKSGE_IS_NOTHROW_SWAPPABLE_TEST(false, const          int[1][2][3]);
	BKSGE_IS_NOTHROW_SWAPPABLE_TEST(true,        volatile int[1][2][3]);
	BKSGE_IS_NOTHROW_SWAPPABLE_TEST(false, const volatile int[1][2][3]);
	BKSGE_IS_NOTHROW_SWAPPABLE_TEST(false,                int[][2][3]);
	BKSGE_IS_NOTHROW_SWAPPABLE_TEST(false, const          int[][2][3]);
	BKSGE_IS_NOTHROW_SWAPPABLE_TEST(false,       volatile int[][2][3]);
	BKSGE_IS_NOTHROW_SWAPPABLE_TEST(false, const volatile int[][2][3]);
	BKSGE_IS_NOTHROW_SWAPPABLE_TEST(true,                 int&);
	BKSGE_IS_NOTHROW_SWAPPABLE_TEST(false, const          int&);
	BKSGE_IS_NOTHROW_SWAPPABLE_TEST(true,        volatile int&);
	BKSGE_IS_NOTHROW_SWAPPABLE_TEST(false, const volatile int&);
	BKSGE_IS_NOTHROW_SWAPPABLE_TEST(true,                 int&&);
	BKSGE_IS_NOTHROW_SWAPPABLE_TEST(false, const          int&&);
	BKSGE_IS_NOTHROW_SWAPPABLE_TEST(true,        volatile int&&);
	BKSGE_IS_NOTHROW_SWAPPABLE_TEST(false, const volatile int&&);
	BKSGE_IS_NOTHROW_SWAPPABLE_TEST(true,                 int*);
	BKSGE_IS_NOTHROW_SWAPPABLE_TEST(true,  const          int*);
	BKSGE_IS_NOTHROW_SWAPPABLE_TEST(true,        volatile int*);
	BKSGE_IS_NOTHROW_SWAPPABLE_TEST(true,  const volatile int*);
	BKSGE_IS_NOTHROW_SWAPPABLE_TEST(true,                 int(&)[2]);
	BKSGE_IS_NOTHROW_SWAPPABLE_TEST(false, const          int(&)[2]);
	BKSGE_IS_NOTHROW_SWAPPABLE_TEST(true,        volatile int(&)[2]);
	BKSGE_IS_NOTHROW_SWAPPABLE_TEST(false, const volatile int(&)[2]);
	BKSGE_IS_NOTHROW_SWAPPABLE_TEST(false,                int(&)[]);
	BKSGE_IS_NOTHROW_SWAPPABLE_TEST(false, const          int(&)[]);
	BKSGE_IS_NOTHROW_SWAPPABLE_TEST(false,       volatile int(&)[]);
	BKSGE_IS_NOTHROW_SWAPPABLE_TEST(false, const volatile int(&)[]);
	BKSGE_IS_NOTHROW_SWAPPABLE_TEST(true,                 int(&&)[2]);
	BKSGE_IS_NOTHROW_SWAPPABLE_TEST(false, const          int(&&)[2]);
	BKSGE_IS_NOTHROW_SWAPPABLE_TEST(true,        volatile int(&&)[2]);
	BKSGE_IS_NOTHROW_SWAPPABLE_TEST(false, const volatile int(&&)[2]);
	BKSGE_IS_NOTHROW_SWAPPABLE_TEST(false,                int(&&)[]);
	BKSGE_IS_NOTHROW_SWAPPABLE_TEST(false, const          int(&&)[]);
	BKSGE_IS_NOTHROW_SWAPPABLE_TEST(false,       volatile int(&&)[]);
	BKSGE_IS_NOTHROW_SWAPPABLE_TEST(false, const volatile int(&&)[]);
	BKSGE_IS_NOTHROW_SWAPPABLE_TEST(true,                 int(*)[2]);
	BKSGE_IS_NOTHROW_SWAPPABLE_TEST(true,  const          int(*)[2]);
	BKSGE_IS_NOTHROW_SWAPPABLE_TEST(true,        volatile int(*)[2]);
	BKSGE_IS_NOTHROW_SWAPPABLE_TEST(true,  const volatile int(*)[2]);
	BKSGE_IS_NOTHROW_SWAPPABLE_TEST(true,                 int(*)[]);
	BKSGE_IS_NOTHROW_SWAPPABLE_TEST(true,  const          int(*)[]);
	BKSGE_IS_NOTHROW_SWAPPABLE_TEST(true,        volatile int(*)[]);
	BKSGE_IS_NOTHROW_SWAPPABLE_TEST(true,  const volatile int(*)[]);
	BKSGE_IS_NOTHROW_SWAPPABLE_TEST(false,                void);
	BKSGE_IS_NOTHROW_SWAPPABLE_TEST(false, const          void);
	BKSGE_IS_NOTHROW_SWAPPABLE_TEST(false,       volatile void);
	BKSGE_IS_NOTHROW_SWAPPABLE_TEST(false, const volatile void);
	BKSGE_IS_NOTHROW_SWAPPABLE_TEST(true,                 void*);
	BKSGE_IS_NOTHROW_SWAPPABLE_TEST(true,  const          void*);
	BKSGE_IS_NOTHROW_SWAPPABLE_TEST(true,        volatile void*);
	BKSGE_IS_NOTHROW_SWAPPABLE_TEST(true,  const volatile void*);
#if !defined(BKSGE_NO_CXX11_NOEXCEPT)
	BKSGE_IS_NOTHROW_SWAPPABLE_TEST(false,                UDT);
#else
	BKSGE_IS_NOTHROW_SWAPPABLE_TEST(true,                 UDT);
#endif
	BKSGE_IS_NOTHROW_SWAPPABLE_TEST(false, const          UDT);
	BKSGE_IS_NOTHROW_SWAPPABLE_TEST(false,       volatile UDT);
	BKSGE_IS_NOTHROW_SWAPPABLE_TEST(false, const volatile UDT);
	BKSGE_IS_NOTHROW_SWAPPABLE_TEST(true,                 POD_UDT);
	BKSGE_IS_NOTHROW_SWAPPABLE_TEST(false, const          POD_UDT);
	BKSGE_IS_NOTHROW_SWAPPABLE_TEST(false,       volatile POD_UDT);
	BKSGE_IS_NOTHROW_SWAPPABLE_TEST(false, const volatile POD_UDT);
	BKSGE_IS_NOTHROW_SWAPPABLE_TEST(true,                 enum_UDT);
	BKSGE_IS_NOTHROW_SWAPPABLE_TEST(false, const          enum_UDT);
	BKSGE_IS_NOTHROW_SWAPPABLE_TEST(true,        volatile enum_UDT);
	BKSGE_IS_NOTHROW_SWAPPABLE_TEST(false, const volatile enum_UDT);
	BKSGE_IS_NOTHROW_SWAPPABLE_TEST(true,                 enum_class_UDT);
	BKSGE_IS_NOTHROW_SWAPPABLE_TEST(false, const          enum_class_UDT);
	BKSGE_IS_NOTHROW_SWAPPABLE_TEST(true,        volatile enum_class_UDT);
	BKSGE_IS_NOTHROW_SWAPPABLE_TEST(false, const volatile enum_class_UDT);
	BKSGE_IS_NOTHROW_SWAPPABLE_TEST(false,                test_abc1);
	BKSGE_IS_NOTHROW_SWAPPABLE_TEST(false, const          test_abc1);
	BKSGE_IS_NOTHROW_SWAPPABLE_TEST(false,       volatile test_abc1);
	BKSGE_IS_NOTHROW_SWAPPABLE_TEST(false, const volatile test_abc1);
	BKSGE_IS_NOTHROW_SWAPPABLE_TEST(false,                test_abc2);
	BKSGE_IS_NOTHROW_SWAPPABLE_TEST(false, const          test_abc2);
	BKSGE_IS_NOTHROW_SWAPPABLE_TEST(false,       volatile test_abc2);
	BKSGE_IS_NOTHROW_SWAPPABLE_TEST(false, const volatile test_abc2);
	BKSGE_IS_NOTHROW_SWAPPABLE_TEST(false,                test_abc3);
	BKSGE_IS_NOTHROW_SWAPPABLE_TEST(false, const          test_abc3);
	BKSGE_IS_NOTHROW_SWAPPABLE_TEST(false,       volatile test_abc3);
	BKSGE_IS_NOTHROW_SWAPPABLE_TEST(false, const volatile test_abc3);

	BKSGE_IS_NOTHROW_SWAPPABLE_TEST(true, f1);
	BKSGE_IS_NOTHROW_SWAPPABLE_TEST(true, f2);
	BKSGE_IS_NOTHROW_SWAPPABLE_TEST(true, f3);
	BKSGE_IS_NOTHROW_SWAPPABLE_TEST(true, mf1);
	BKSGE_IS_NOTHROW_SWAPPABLE_TEST(true, mf2);
	BKSGE_IS_NOTHROW_SWAPPABLE_TEST(true, mf3);
	BKSGE_IS_NOTHROW_SWAPPABLE_TEST(true, mf4);
	BKSGE_IS_NOTHROW_SWAPPABLE_TEST(true, mp);
	BKSGE_IS_NOTHROW_SWAPPABLE_TEST(true, cmf);
	BKSGE_IS_NOTHROW_SWAPPABLE_TEST(false, void());
	BKSGE_IS_NOTHROW_SWAPPABLE_TEST(false, foo0_t);
	BKSGE_IS_NOTHROW_SWAPPABLE_TEST(false, foo1_t);
	BKSGE_IS_NOTHROW_SWAPPABLE_TEST(false, foo2_t);
	BKSGE_IS_NOTHROW_SWAPPABLE_TEST(false, foo3_t);
	BKSGE_IS_NOTHROW_SWAPPABLE_TEST(false, foo4_t);
}

}	// namespace is_nothrow_swappable_test

}	// namespace bksge_type_traits_test

#undef BKSGE_IS_NOTHROW_SWAPPABLE_TEST
