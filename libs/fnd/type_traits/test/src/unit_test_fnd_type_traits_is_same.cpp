/**
 *	@file	unit_test_fnd_type_traits_is_same.cpp
 *
 *	@brief	is_same のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/type_traits/is_same.hpp>
#include <bksge/fnd/config.hpp>
#include <gtest/gtest.h>
#include <cstddef>
#include "type_traits_test_utility.hpp"

#if defined(BKSGE_HAS_CXX14_VARIABLE_TEMPLATES)

#define BKSGE_IS_SAME_TEST(b, T1, T2)	\
	static_assert(bksge::is_same_v<T1, T2>      == b, #T1 ", " #T2);	\
	static_assert(bksge::is_same<T1, T2>::value == b, #T1 ", " #T2);	\
	static_assert(bksge::is_same<T1, T2>()      == b, #T1 ", " #T2)

#else

#define BKSGE_IS_SAME_TEST(b, T1, T2)	\
	static_assert(bksge::is_same<T1, T2>::value == b, #T1 ", " #T2);	\
	static_assert(bksge::is_same<T1, T2>()      == b, #T1 ", " #T2)

#endif

BKSGE_IS_SAME_TEST(true,                 int,                int);
BKSGE_IS_SAME_TEST(false,                int, const          int);
BKSGE_IS_SAME_TEST(false,                int,       volatile int);
BKSGE_IS_SAME_TEST(false,                int, const volatile int);
BKSGE_IS_SAME_TEST(false, const          int,                int);
BKSGE_IS_SAME_TEST(true,  const          int, const          int);
BKSGE_IS_SAME_TEST(false, const          int,       volatile int);
BKSGE_IS_SAME_TEST(false, const          int, const volatile int);
BKSGE_IS_SAME_TEST(false,       volatile int,                int);
BKSGE_IS_SAME_TEST(false,       volatile int, const          int);
BKSGE_IS_SAME_TEST(true,        volatile int,       volatile int);
BKSGE_IS_SAME_TEST(false,       volatile int, const volatile int);
BKSGE_IS_SAME_TEST(false, const volatile int,                int);
BKSGE_IS_SAME_TEST(false, const volatile int, const          int);
BKSGE_IS_SAME_TEST(false, const volatile int,       volatile int);
BKSGE_IS_SAME_TEST(true,  const volatile int, const volatile int);
BKSGE_IS_SAME_TEST(false, int, int*);
BKSGE_IS_SAME_TEST(false, int, int&);
BKSGE_IS_SAME_TEST(false, int, int&&);
BKSGE_IS_SAME_TEST(false, int, int[2]);
BKSGE_IS_SAME_TEST(false, int, int[]);
BKSGE_IS_SAME_TEST(false, int, int(&)[2]);
BKSGE_IS_SAME_TEST(false, int, int(&)[]);
BKSGE_IS_SAME_TEST(false, int, int(&&)[2]);
BKSGE_IS_SAME_TEST(false, int, int(&&)[]);

BKSGE_IS_SAME_TEST(false, int*, int);
BKSGE_IS_SAME_TEST(true,  int*, int*);
BKSGE_IS_SAME_TEST(false, int*, int&);
BKSGE_IS_SAME_TEST(false, int*, int&&);
BKSGE_IS_SAME_TEST(false, int*, int[2]);
BKSGE_IS_SAME_TEST(false, int*, int[]);
BKSGE_IS_SAME_TEST(false, int*, int(&)[2]);
BKSGE_IS_SAME_TEST(false, int*, int(&)[]);
BKSGE_IS_SAME_TEST(false, int*, int(&&)[2]);
BKSGE_IS_SAME_TEST(false, int*, int(&&)[]);

BKSGE_IS_SAME_TEST(false, int&, int);
BKSGE_IS_SAME_TEST(false, int&, int*);
BKSGE_IS_SAME_TEST(true,  int&, int&);
BKSGE_IS_SAME_TEST(false, int&, int&&);
BKSGE_IS_SAME_TEST(false, int&, int[2]);
BKSGE_IS_SAME_TEST(false, int&, int[]);
BKSGE_IS_SAME_TEST(false, int&, int(&)[2]);
BKSGE_IS_SAME_TEST(false, int&, int(&)[]);
BKSGE_IS_SAME_TEST(false, int&, int(&&)[2]);
BKSGE_IS_SAME_TEST(false, int&, int(&&)[]);

BKSGE_IS_SAME_TEST(false, int&&, int);
BKSGE_IS_SAME_TEST(false, int&&, int*);
BKSGE_IS_SAME_TEST(false, int&&, int&);
BKSGE_IS_SAME_TEST(true,  int&&, int&&);
BKSGE_IS_SAME_TEST(false, int&&, int[2]);
BKSGE_IS_SAME_TEST(false, int&&, int[]);
BKSGE_IS_SAME_TEST(false, int&&, int(&)[2]);
BKSGE_IS_SAME_TEST(false, int&&, int(&)[]);
BKSGE_IS_SAME_TEST(false, int&&, int(&&)[2]);
BKSGE_IS_SAME_TEST(false, int&&, int(&&)[]);

BKSGE_IS_SAME_TEST(false, int[2], int);
BKSGE_IS_SAME_TEST(false, int[2], int*);
BKSGE_IS_SAME_TEST(false, int[2], int&);
BKSGE_IS_SAME_TEST(false, int[2], int&&);
BKSGE_IS_SAME_TEST(true,  int[2], int[2]);
BKSGE_IS_SAME_TEST(false, int[2], int[]);
BKSGE_IS_SAME_TEST(false, int[2], int(&)[2]);
BKSGE_IS_SAME_TEST(false, int[2], int(&)[]);
BKSGE_IS_SAME_TEST(false, int[2], int(&&)[2]);
BKSGE_IS_SAME_TEST(false, int[2], int(&&)[]);

BKSGE_IS_SAME_TEST(false, int[], int);
BKSGE_IS_SAME_TEST(false, int[], int*);
BKSGE_IS_SAME_TEST(false, int[], int&);
BKSGE_IS_SAME_TEST(false, int[], int&&);
BKSGE_IS_SAME_TEST(false, int[], int[2]);
BKSGE_IS_SAME_TEST(true,  int[], int[]);
BKSGE_IS_SAME_TEST(false, int[], int(&)[2]);
BKSGE_IS_SAME_TEST(false, int[], int(&)[]);
BKSGE_IS_SAME_TEST(false, int[], int(&&)[2]);
BKSGE_IS_SAME_TEST(false, int[], int(&&)[]);

BKSGE_IS_SAME_TEST(false, int(&)[2], int);
BKSGE_IS_SAME_TEST(false, int(&)[2], int*);
BKSGE_IS_SAME_TEST(false, int(&)[2], int&);
BKSGE_IS_SAME_TEST(false, int(&)[2], int&&);
BKSGE_IS_SAME_TEST(false, int(&)[2], int[2]);
BKSGE_IS_SAME_TEST(false, int(&)[2], int[]);
BKSGE_IS_SAME_TEST(true,  int(&)[2], int(&)[2]);
BKSGE_IS_SAME_TEST(false, int(&)[2], int(&)[]);
BKSGE_IS_SAME_TEST(false, int(&)[2], int(&&)[2]);
BKSGE_IS_SAME_TEST(false, int(&)[2], int(&&)[]);

BKSGE_IS_SAME_TEST(false, int(&)[], int);
BKSGE_IS_SAME_TEST(false, int(&)[], int*);
BKSGE_IS_SAME_TEST(false, int(&)[], int&);
BKSGE_IS_SAME_TEST(false, int(&)[], int&&);
BKSGE_IS_SAME_TEST(false, int(&)[], int[2]);
BKSGE_IS_SAME_TEST(false, int(&)[], int[]);
BKSGE_IS_SAME_TEST(false, int(&)[], int(&)[2]);
BKSGE_IS_SAME_TEST(true,  int(&)[], int(&)[]);
BKSGE_IS_SAME_TEST(false, int(&)[], int(&&)[2]);
BKSGE_IS_SAME_TEST(false, int(&)[], int(&&)[]);

BKSGE_IS_SAME_TEST(false, int(&&)[2], int);
BKSGE_IS_SAME_TEST(false, int(&&)[2], int*);
BKSGE_IS_SAME_TEST(false, int(&&)[2], int&);
BKSGE_IS_SAME_TEST(false, int(&&)[2], int&&);
BKSGE_IS_SAME_TEST(false, int(&&)[2], int[2]);
BKSGE_IS_SAME_TEST(false, int(&&)[2], int[]);
BKSGE_IS_SAME_TEST(false, int(&&)[2], int(&)[2]);
BKSGE_IS_SAME_TEST(false, int(&&)[2], int(&)[]);
BKSGE_IS_SAME_TEST(true,  int(&&)[2], int(&&)[2]);
BKSGE_IS_SAME_TEST(false, int(&&)[2], int(&&)[]);

BKSGE_IS_SAME_TEST(false, int(&&)[], int);
BKSGE_IS_SAME_TEST(false, int(&&)[], int*);
BKSGE_IS_SAME_TEST(false, int(&&)[], int&);
BKSGE_IS_SAME_TEST(false, int(&&)[], int&&);
BKSGE_IS_SAME_TEST(false, int(&&)[], int[2]);
BKSGE_IS_SAME_TEST(false, int(&&)[], int[]);
BKSGE_IS_SAME_TEST(false, int(&&)[], int(&)[2]);
BKSGE_IS_SAME_TEST(false, int(&&)[], int(&)[]);
BKSGE_IS_SAME_TEST(false, int(&&)[], int(&&)[2]);
BKSGE_IS_SAME_TEST(true,  int(&&)[], int(&&)[]);

BKSGE_IS_SAME_TEST(true,                 void,                void);
BKSGE_IS_SAME_TEST(false,                void, const          void);
BKSGE_IS_SAME_TEST(false,                void,       volatile void);
BKSGE_IS_SAME_TEST(false,                void, const volatile void);
BKSGE_IS_SAME_TEST(false, const          void,                void);
BKSGE_IS_SAME_TEST(true,  const          void, const          void);
BKSGE_IS_SAME_TEST(false, const          void,       volatile void);
BKSGE_IS_SAME_TEST(false, const          void, const volatile void);
BKSGE_IS_SAME_TEST(false,       volatile void,                void);
BKSGE_IS_SAME_TEST(false,       volatile void, const          void);
BKSGE_IS_SAME_TEST(true,        volatile void,       volatile void);
BKSGE_IS_SAME_TEST(false,       volatile void, const volatile void);
BKSGE_IS_SAME_TEST(false, const volatile void,                void);
BKSGE_IS_SAME_TEST(false, const volatile void, const          void);
BKSGE_IS_SAME_TEST(false, const volatile void,       volatile void);
BKSGE_IS_SAME_TEST(true,  const volatile void, const volatile void);

BKSGE_IS_SAME_TEST(true, decltype(nullptr), std::nullptr_t);
BKSGE_IS_SAME_TEST(false, int, char);
BKSGE_IS_SAME_TEST(false, int, unsigned int);
BKSGE_IS_SAME_TEST(false, int[2], int[3]);
BKSGE_IS_SAME_TEST(false, int[2], long[2]);
BKSGE_IS_SAME_TEST(false, int, enum_UDT);
BKSGE_IS_SAME_TEST(false, int, enum_class_UDT);
BKSGE_IS_SAME_TEST(false, int, int_constructible);
BKSGE_IS_SAME_TEST(false, int, int_convertible);
BKSGE_IS_SAME_TEST(false, Base, Derived);
BKSGE_IS_SAME_TEST(false, Base, Derived2);

#undef BKSGE_IS_SAME_TEST
