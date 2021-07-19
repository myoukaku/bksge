/**
 *	@file	unit_test_fnd_type_traits_is_swappable_with.cpp
 *
 *	@brief	is_swappable_with のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/type_traits/is_swappable_with.hpp>
#include <bksge/fnd/config.hpp>
#include <gtest/gtest.h>
#include "type_traits_test_utility.hpp"

#if defined(BKSGE_HAS_CXX14_VARIABLE_TEMPLATES)

#define BKSGE_IS_SWAPPABLE_WITH_TEST(b, T1, T2)	\
	static_assert(bksge::is_swappable_with_v<T1, T2>      == b, #T1 ", " #T2);	\
	static_assert(bksge::is_swappable_with<T1, T2>::value == b, #T1 ", " #T2);	\
	static_assert(bksge::is_swappable_with<T1, T2>()      == b, #T1 ", " #T2)

#else

#define BKSGE_IS_SWAPPABLE_WITH_TEST(b, T1, T2)	\
	static_assert(bksge::is_swappable_with<T1, T2>::value == b, #T1 ", " #T2);	\
	static_assert(bksge::is_swappable_with<T1, T2>()      == b, #T1 ", " #T2)

#endif

BKSGE_IS_SWAPPABLE_WITH_TEST(false,                int,                int);
BKSGE_IS_SWAPPABLE_WITH_TEST(false,                int, const          int);
BKSGE_IS_SWAPPABLE_WITH_TEST(false,                int,       volatile int);
BKSGE_IS_SWAPPABLE_WITH_TEST(false,                int, const volatile int);
BKSGE_IS_SWAPPABLE_WITH_TEST(false, const          int,                int);
#if BKSGE_CXX_STANDARD >= 17
BKSGE_IS_SWAPPABLE_WITH_TEST(false, const          int, const          int);
#endif
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
#if BKSGE_CXX_STANDARD >= 17
BKSGE_IS_SWAPPABLE_WITH_TEST(false, const          int&, const          int&);
#endif
BKSGE_IS_SWAPPABLE_WITH_TEST(false, const          int&,       volatile int&);
BKSGE_IS_SWAPPABLE_WITH_TEST(false, const          int&, const volatile int&);
BKSGE_IS_SWAPPABLE_WITH_TEST(false,       volatile int&,                int&);
BKSGE_IS_SWAPPABLE_WITH_TEST(false,       volatile int&, const          int&);
BKSGE_IS_SWAPPABLE_WITH_TEST(true,        volatile int&,       volatile int&);
BKSGE_IS_SWAPPABLE_WITH_TEST(false,       volatile int&, const volatile int&);
BKSGE_IS_SWAPPABLE_WITH_TEST(false, const volatile int&,                int&);
BKSGE_IS_SWAPPABLE_WITH_TEST(false, const volatile int&, const          int&);
BKSGE_IS_SWAPPABLE_WITH_TEST(false, const volatile int&,       volatile int&);
#if BKSGE_CXX_STANDARD >= 17
BKSGE_IS_SWAPPABLE_WITH_TEST(false, const volatile int&, const volatile int&);
#endif

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

#undef BKSGE_IS_SWAPPABLE_WITH_TEST
