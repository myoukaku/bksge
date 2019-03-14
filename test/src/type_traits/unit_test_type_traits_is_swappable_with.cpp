/**
 *	@file	unit_test_type_traits_is_swappable_with.cpp
 *
 *	@brief	is_swappable_with のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/type_traits/is_swappable_with.hpp>
#include <gtest/gtest.h>
#include "type_traits_test_utility.hpp"

#define BKSGE_IS_SWAPPABLE_WITH_TEST(b, T1, T2)	\
	static_assert(bksge::is_swappable_with<T1, T2>::value == b, #T1 ", " #T2)

GTEST_TEST(TypeTraitsTest, IsSwappableWithTest)
{
	IntegralConstantTest<bksge::is_swappable_with<int&, int&>, true>();
	IntegralConstantTest<bksge::is_swappable_with<int, int>, false>();
	IntegralConstantTest<bksge::is_swappable_with<int, void>, false>();

	BKSGE_IS_SWAPPABLE_WITH_TEST(false,                int,                int);
	BKSGE_IS_SWAPPABLE_WITH_TEST(false,                int, const          int);
	BKSGE_IS_SWAPPABLE_WITH_TEST(false,                int,       volatile int);
	BKSGE_IS_SWAPPABLE_WITH_TEST(false,                int, const volatile int);
	BKSGE_IS_SWAPPABLE_WITH_TEST(false, const          int,                int);
	BKSGE_IS_SWAPPABLE_WITH_TEST(false, const          int, const          int);
	BKSGE_IS_SWAPPABLE_WITH_TEST(false, const          int,       volatile int);
	BKSGE_IS_SWAPPABLE_WITH_TEST(false, const          int, const volatile int);
	BKSGE_IS_SWAPPABLE_WITH_TEST(false,       volatile int,                int);
	BKSGE_IS_SWAPPABLE_WITH_TEST(false,       volatile int, const          int);
	BKSGE_IS_SWAPPABLE_WITH_TEST(false,       volatile int,       volatile int);
	BKSGE_IS_SWAPPABLE_WITH_TEST(false,       volatile int, const volatile int);
	BKSGE_IS_SWAPPABLE_WITH_TEST(false, const volatile int,                int);
	BKSGE_IS_SWAPPABLE_WITH_TEST(false, const volatile int, const          int);
	BKSGE_IS_SWAPPABLE_WITH_TEST(false, const volatile int,       volatile int);
	BKSGE_IS_SWAPPABLE_WITH_TEST(false, const volatile int, const volatile int);

	BKSGE_IS_SWAPPABLE_WITH_TEST(true,                 int&,                int&);
	BKSGE_IS_SWAPPABLE_WITH_TEST(false,                int&, const          int&);
	BKSGE_IS_SWAPPABLE_WITH_TEST(false,                int&,       volatile int&);
	BKSGE_IS_SWAPPABLE_WITH_TEST(false,                int&, const volatile int&);
	BKSGE_IS_SWAPPABLE_WITH_TEST(false, const          int&,                int&);
	BKSGE_IS_SWAPPABLE_WITH_TEST(false, const          int&, const          int&);
	BKSGE_IS_SWAPPABLE_WITH_TEST(false, const          int&,       volatile int&);
	BKSGE_IS_SWAPPABLE_WITH_TEST(false, const          int&, const volatile int&);
	BKSGE_IS_SWAPPABLE_WITH_TEST(false,       volatile int&,                int&);
	BKSGE_IS_SWAPPABLE_WITH_TEST(false,       volatile int&, const          int&);
	BKSGE_IS_SWAPPABLE_WITH_TEST(true,        volatile int&,       volatile int&);
	BKSGE_IS_SWAPPABLE_WITH_TEST(false,       volatile int&, const volatile int&);
	BKSGE_IS_SWAPPABLE_WITH_TEST(false, const volatile int&,                int&);
	BKSGE_IS_SWAPPABLE_WITH_TEST(false, const volatile int&, const          int&);
	BKSGE_IS_SWAPPABLE_WITH_TEST(false, const volatile int&,       volatile int&);
	BKSGE_IS_SWAPPABLE_WITH_TEST(false, const volatile int&, const volatile int&);

	BKSGE_IS_SWAPPABLE_WITH_TEST(false, int, int*);
	BKSGE_IS_SWAPPABLE_WITH_TEST(false, int, int&);
	BKSGE_IS_SWAPPABLE_WITH_TEST(false, int, int&&);
	BKSGE_IS_SWAPPABLE_WITH_TEST(false, int, int[2]);
	BKSGE_IS_SWAPPABLE_WITH_TEST(false, int, int[]);
	BKSGE_IS_SWAPPABLE_WITH_TEST(false, int, int(&)[2]);
	BKSGE_IS_SWAPPABLE_WITH_TEST(false, int, int(&)[]);
	BKSGE_IS_SWAPPABLE_WITH_TEST(false, int, int(&&)[2]);
	BKSGE_IS_SWAPPABLE_WITH_TEST(false, int, int(&&)[]);
	BKSGE_IS_SWAPPABLE_WITH_TEST(false, int, int(*)[2]);
	BKSGE_IS_SWAPPABLE_WITH_TEST(false, int, int(*)[]);
	BKSGE_IS_SWAPPABLE_WITH_TEST(false, int, short);
	BKSGE_IS_SWAPPABLE_WITH_TEST(false, int, long);
	BKSGE_IS_SWAPPABLE_WITH_TEST(false, int, unsigned int);
	BKSGE_IS_SWAPPABLE_WITH_TEST(false, int, float);
	BKSGE_IS_SWAPPABLE_WITH_TEST(false, int, void);
	BKSGE_IS_SWAPPABLE_WITH_TEST(false, int, void*);
	BKSGE_IS_SWAPPABLE_WITH_TEST(false, int, enum_UDT);

	BKSGE_IS_SWAPPABLE_WITH_TEST(false, int*, int*);
	BKSGE_IS_SWAPPABLE_WITH_TEST(false, int*, int&);
	BKSGE_IS_SWAPPABLE_WITH_TEST(false, int*, int&&);
	BKSGE_IS_SWAPPABLE_WITH_TEST(false, int*, int[2]);
	BKSGE_IS_SWAPPABLE_WITH_TEST(false, int*, int[]);
	BKSGE_IS_SWAPPABLE_WITH_TEST(false, int*, int(&)[2]);
	BKSGE_IS_SWAPPABLE_WITH_TEST(false, int*, int(&)[]);
	BKSGE_IS_SWAPPABLE_WITH_TEST(false, int*, int(&&)[2]);
	BKSGE_IS_SWAPPABLE_WITH_TEST(false, int*, int(&&)[]);
	BKSGE_IS_SWAPPABLE_WITH_TEST(false, int*, int(*)[2]);
	BKSGE_IS_SWAPPABLE_WITH_TEST(false, int*, int(*)[]);
	BKSGE_IS_SWAPPABLE_WITH_TEST(false, int*, short*);
	BKSGE_IS_SWAPPABLE_WITH_TEST(false, int*, long*);
	BKSGE_IS_SWAPPABLE_WITH_TEST(false, int*, unsigned int*);
	BKSGE_IS_SWAPPABLE_WITH_TEST(false, int*, float*);
	BKSGE_IS_SWAPPABLE_WITH_TEST(false, int*, void);
	BKSGE_IS_SWAPPABLE_WITH_TEST(false, int*, void*);
	BKSGE_IS_SWAPPABLE_WITH_TEST(false, int*, enum_UDT);

	BKSGE_IS_SWAPPABLE_WITH_TEST(false, int&, int*);
	BKSGE_IS_SWAPPABLE_WITH_TEST(true,  int&, int&);
	BKSGE_IS_SWAPPABLE_WITH_TEST(false, int&, int&&);
	BKSGE_IS_SWAPPABLE_WITH_TEST(false, int&, int[2]);
	BKSGE_IS_SWAPPABLE_WITH_TEST(false, int&, int[]);
	BKSGE_IS_SWAPPABLE_WITH_TEST(false, int&, int(&)[2]);
	BKSGE_IS_SWAPPABLE_WITH_TEST(false, int&, int(&)[]);
	BKSGE_IS_SWAPPABLE_WITH_TEST(false, int&, int(&&)[2]);
	BKSGE_IS_SWAPPABLE_WITH_TEST(false, int&, int(&&)[]);
	BKSGE_IS_SWAPPABLE_WITH_TEST(false, int&, int(*)[2]);
	BKSGE_IS_SWAPPABLE_WITH_TEST(false, int&, int(*)[]);
	BKSGE_IS_SWAPPABLE_WITH_TEST(false, int&, short&);
	BKSGE_IS_SWAPPABLE_WITH_TEST(false, int&, long&);
	BKSGE_IS_SWAPPABLE_WITH_TEST(false, int&, unsigned int&);
	BKSGE_IS_SWAPPABLE_WITH_TEST(false, int&, float&);
	BKSGE_IS_SWAPPABLE_WITH_TEST(false, int&, void);
	BKSGE_IS_SWAPPABLE_WITH_TEST(false, int&, void*);
	BKSGE_IS_SWAPPABLE_WITH_TEST(false, int&, enum_UDT);

	BKSGE_IS_SWAPPABLE_WITH_TEST(false, int&&, int*);
	BKSGE_IS_SWAPPABLE_WITH_TEST(false, int&&, int&);
	BKSGE_IS_SWAPPABLE_WITH_TEST(false, int&&, int&&);
	BKSGE_IS_SWAPPABLE_WITH_TEST(false, int&&, int[2]);
	BKSGE_IS_SWAPPABLE_WITH_TEST(false, int&&, int[]);
	BKSGE_IS_SWAPPABLE_WITH_TEST(false, int&&, int(&)[2]);
	BKSGE_IS_SWAPPABLE_WITH_TEST(false, int&&, int(&)[]);
	BKSGE_IS_SWAPPABLE_WITH_TEST(false, int&&, int(&&)[2]);
	BKSGE_IS_SWAPPABLE_WITH_TEST(false, int&&, int(&&)[]);
	BKSGE_IS_SWAPPABLE_WITH_TEST(false, int&&, int(*)[2]);
	BKSGE_IS_SWAPPABLE_WITH_TEST(false, int&&, int(*)[]);
	BKSGE_IS_SWAPPABLE_WITH_TEST(false, int&&, short&&);
	BKSGE_IS_SWAPPABLE_WITH_TEST(false, int&&, long&&);
	BKSGE_IS_SWAPPABLE_WITH_TEST(false, int&&, unsigned int&&);
	BKSGE_IS_SWAPPABLE_WITH_TEST(false, int&&, float&&);
	BKSGE_IS_SWAPPABLE_WITH_TEST(false, int&&, void);
	BKSGE_IS_SWAPPABLE_WITH_TEST(false, int&&, void*);
	BKSGE_IS_SWAPPABLE_WITH_TEST(false, int&&, enum_UDT);
}

#undef BKSGE_IS_SWAPPABLE_WITH_TEST
