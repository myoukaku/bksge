/**
 *	@file	unit_test_fnd_type_traits_is_nothrow_swappable_with.cpp
 *
 *	@brief	is_nothrow_swappable_with のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/type_traits/is_nothrow_swappable_with.hpp>
#include <bksge/fnd/config.hpp>
#include <gtest/gtest.h>
#include "type_traits_test_utility.hpp"

#if defined(BKSGE_HAS_CXX14_VARIABLE_TEMPLATES)

#define BKSGE_IS_NOTHROW_SWAPPABLE_WITH_TEST(b, T1, T2)	\
	static_assert(bksge::is_nothrow_swappable_with_v<T1, T2>      == b, #T1 ", " #T2);	\
	static_assert(bksge::is_nothrow_swappable_with<T1, T2>::value == b, #T1 ", " #T2);	\
	static_assert(bksge::is_nothrow_swappable_with<T1, T2>()      == b, #T1 ", " #T2)

#else

#define BKSGE_IS_NOTHROW_SWAPPABLE_WITH_TEST(b, T1, T2)	\
	static_assert(bksge::is_nothrow_swappable_with<T1, T2>::value == b, #T1 ", " #T2);	\
	static_assert(bksge::is_nothrow_swappable_with<T1, T2>()      == b, #T1 ", " #T2)

#endif

namespace bksge_type_traits_test
{

namespace is_nothrow_swappable_with_test
{

struct SwapThrow1 {};

void swap(SwapThrow1&, SwapThrow1&);

struct SwapThrow2
{
	SwapThrow2() BKSGE_NOEXCEPT = default;
	SwapThrow2(const SwapThrow2&) BKSGE_NOEXCEPT_IF(false);
	SwapThrow2& operator=(const SwapThrow2&) BKSGE_NOEXCEPT_IF(false);
};

void swap(SwapThrow1&, SwapThrow2&);
void swap(SwapThrow2&, SwapThrow1&);

struct SwapNoThrow1
{
	SwapNoThrow1() BKSGE_NOEXCEPT = default;
	SwapNoThrow1(const SwapNoThrow1&) BKSGE_NOEXCEPT_IF(false);
	SwapNoThrow1& operator=(const SwapNoThrow1&) BKSGE_NOEXCEPT_IF(false);
};

void swap(SwapNoThrow1&, SwapNoThrow1&) BKSGE_NOEXCEPT;

struct SwapNoThrow2 {};

void swap(SwapNoThrow1&, SwapNoThrow2&) BKSGE_NOEXCEPT;
void swap(SwapNoThrow2&, SwapNoThrow1&) BKSGE_NOEXCEPT;

#if defined(BKSGE_HAS_CXX11_NOEXCEPT)
BKSGE_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, SwapThrow1&, SwapThrow1&);
BKSGE_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, SwapThrow1&, SwapThrow2&);
BKSGE_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, SwapThrow2&, SwapThrow1&);
BKSGE_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, SwapThrow2&, SwapThrow2&);
#else
BKSGE_IS_NOTHROW_SWAPPABLE_WITH_TEST(true,  SwapThrow1&, SwapThrow1&);
BKSGE_IS_NOTHROW_SWAPPABLE_WITH_TEST(true,  SwapThrow1&, SwapThrow2&);
BKSGE_IS_NOTHROW_SWAPPABLE_WITH_TEST(true,  SwapThrow2&, SwapThrow1&);
BKSGE_IS_NOTHROW_SWAPPABLE_WITH_TEST(true,  SwapThrow2&, SwapThrow2&);
#endif
BKSGE_IS_NOTHROW_SWAPPABLE_WITH_TEST(true,  SwapNoThrow1&, SwapNoThrow1&);
BKSGE_IS_NOTHROW_SWAPPABLE_WITH_TEST(true,  SwapNoThrow1&, SwapNoThrow2&);
BKSGE_IS_NOTHROW_SWAPPABLE_WITH_TEST(true,  SwapNoThrow2&, SwapNoThrow1&);
BKSGE_IS_NOTHROW_SWAPPABLE_WITH_TEST(true,  SwapNoThrow2&, SwapNoThrow2&);

BKSGE_IS_NOTHROW_SWAPPABLE_WITH_TEST(false,                int,                int);
BKSGE_IS_NOTHROW_SWAPPABLE_WITH_TEST(false,                int, const          int);
BKSGE_IS_NOTHROW_SWAPPABLE_WITH_TEST(false,                int,       volatile int);
BKSGE_IS_NOTHROW_SWAPPABLE_WITH_TEST(false,                int, const volatile int);
BKSGE_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, const          int,                int);
BKSGE_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, const          int, const          int);
BKSGE_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, const          int,       volatile int);
BKSGE_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, const          int, const volatile int);
BKSGE_IS_NOTHROW_SWAPPABLE_WITH_TEST(false,       volatile int,                int);
BKSGE_IS_NOTHROW_SWAPPABLE_WITH_TEST(false,       volatile int, const          int);
BKSGE_IS_NOTHROW_SWAPPABLE_WITH_TEST(false,       volatile int,       volatile int);
BKSGE_IS_NOTHROW_SWAPPABLE_WITH_TEST(false,       volatile int, const volatile int);
BKSGE_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, const volatile int,                int);
BKSGE_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, const volatile int, const          int);
BKSGE_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, const volatile int,       volatile int);
BKSGE_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, const volatile int, const volatile int);

BKSGE_IS_NOTHROW_SWAPPABLE_WITH_TEST(true,                 int&,                int&);
BKSGE_IS_NOTHROW_SWAPPABLE_WITH_TEST(false,                int&, const          int&);
BKSGE_IS_NOTHROW_SWAPPABLE_WITH_TEST(false,                int&,       volatile int&);
BKSGE_IS_NOTHROW_SWAPPABLE_WITH_TEST(false,                int&, const volatile int&);
BKSGE_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, const          int&,                int&);
BKSGE_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, const          int&, const          int&);
BKSGE_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, const          int&,       volatile int&);
BKSGE_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, const          int&, const volatile int&);
BKSGE_IS_NOTHROW_SWAPPABLE_WITH_TEST(false,       volatile int&,                int&);
BKSGE_IS_NOTHROW_SWAPPABLE_WITH_TEST(false,       volatile int&, const          int&);
BKSGE_IS_NOTHROW_SWAPPABLE_WITH_TEST(true,        volatile int&,       volatile int&);
BKSGE_IS_NOTHROW_SWAPPABLE_WITH_TEST(false,       volatile int&, const volatile int&);
BKSGE_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, const volatile int&,                int&);
BKSGE_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, const volatile int&, const          int&);
BKSGE_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, const volatile int&,       volatile int&);
BKSGE_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, const volatile int&, const volatile int&);

BKSGE_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, int, int*);
BKSGE_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, int, int&);
BKSGE_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, int, int&&);
BKSGE_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, int, int[2]);
BKSGE_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, int, int[]);
BKSGE_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, int, int(&)[2]);
BKSGE_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, int, int(&)[]);
BKSGE_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, int, int(&&)[2]);
BKSGE_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, int, int(&&)[]);
BKSGE_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, int, int(*)[2]);
BKSGE_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, int, int(*)[]);
BKSGE_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, int, short);
BKSGE_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, int, long);
BKSGE_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, int, unsigned int);
BKSGE_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, int, float);
BKSGE_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, int, void);
BKSGE_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, int, void*);
BKSGE_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, int, enum_UDT);

BKSGE_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, int*, int*);
BKSGE_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, int*, int&);
BKSGE_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, int*, int&&);
BKSGE_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, int*, int[2]);
BKSGE_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, int*, int[]);
BKSGE_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, int*, int(&)[2]);
BKSGE_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, int*, int(&)[]);
BKSGE_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, int*, int(&&)[2]);
BKSGE_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, int*, int(&&)[]);
BKSGE_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, int*, int(*)[2]);
BKSGE_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, int*, int(*)[]);
BKSGE_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, int*, short*);
BKSGE_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, int*, long*);
BKSGE_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, int*, unsigned int*);
BKSGE_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, int*, float*);
BKSGE_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, int*, void);
BKSGE_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, int*, void*);
BKSGE_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, int*, enum_UDT);

BKSGE_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, int&, int*);
BKSGE_IS_NOTHROW_SWAPPABLE_WITH_TEST(true,  int&, int&);
BKSGE_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, int&, int&&);
BKSGE_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, int&, int[2]);
BKSGE_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, int&, int[]);
BKSGE_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, int&, int(&)[2]);
BKSGE_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, int&, int(&)[]);
BKSGE_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, int&, int(&&)[2]);
BKSGE_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, int&, int(&&)[]);
BKSGE_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, int&, int(*)[2]);
BKSGE_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, int&, int(*)[]);
BKSGE_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, int&, short&);
BKSGE_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, int&, long&);
BKSGE_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, int&, unsigned int&);
BKSGE_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, int&, float&);
BKSGE_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, int&, void);
BKSGE_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, int&, void*);
BKSGE_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, int&, enum_UDT);

BKSGE_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, int&&, int*);
BKSGE_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, int&&, int&);
BKSGE_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, int&&, int&&);
BKSGE_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, int&&, int[2]);
BKSGE_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, int&&, int[]);
BKSGE_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, int&&, int(&)[2]);
BKSGE_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, int&&, int(&)[]);
BKSGE_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, int&&, int(&&)[2]);
BKSGE_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, int&&, int(&&)[]);
BKSGE_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, int&&, int(*)[2]);
BKSGE_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, int&&, int(*)[]);
BKSGE_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, int&&, short&&);
BKSGE_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, int&&, long&&);
BKSGE_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, int&&, unsigned int&&);
BKSGE_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, int&&, float&&);
BKSGE_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, int&&, void);
BKSGE_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, int&&, void*);
BKSGE_IS_NOTHROW_SWAPPABLE_WITH_TEST(false, int&&, enum_UDT);

}	// namespace is_nothrow_swappable_with_test

}	// namespace bksge_type_traits_test

#undef BKSGE_IS_NOTHROW_SWAPPABLE_WITH_TEST
