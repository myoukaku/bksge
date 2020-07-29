/**
 *	@file	unit_test_fnd_type_traits_is_assignable.cpp
 *
 *	@brief	is_assignable のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/type_traits/is_assignable.hpp>
#include <cstddef>
#include <gtest/gtest.h>
#include "type_traits_test_utility.hpp"

#define BKSGE_IS_ASSIGNABLE_TEST(b, T, U)	\
	static_assert(bksge::is_assignable<T, U>::value == b, #T ", " #U " == " #b);	\
	static_assert(bksge::is_assignable<T, U>()      == b, #T ", " #U " == " #b)

namespace bksge_type_traits_test
{

namespace is_assignable_test
{

struct S1
{
	S1& operator=(const S1&);
};

struct S2
{
	S2& operator=(int);
};

#define BKSGE_IS_ASSIGNABLE_TEST_0(b, T, U)	\
	BKSGE_IS_ASSIGNABLE_TEST(b,                     T,                 U);	\
	BKSGE_IS_ASSIGNABLE_TEST(b,                     T,  const          U);	\
	BKSGE_IS_ASSIGNABLE_TEST(b,                     T,        volatile U);	\
	BKSGE_IS_ASSIGNABLE_TEST(b,                     T,  const volatile U);	\
	BKSGE_IS_ASSIGNABLE_TEST(b,      const          T,                 U);	\
	BKSGE_IS_ASSIGNABLE_TEST(b,      const          T,  const          U);	\
	BKSGE_IS_ASSIGNABLE_TEST(b,      const          T,        volatile U);	\
	BKSGE_IS_ASSIGNABLE_TEST(b,      const          T,  const volatile U);	\
	BKSGE_IS_ASSIGNABLE_TEST(b,            volatile T,                 U);	\
	BKSGE_IS_ASSIGNABLE_TEST(b,            volatile T,  const          U);	\
	BKSGE_IS_ASSIGNABLE_TEST(b,            volatile T,        volatile U);	\
	BKSGE_IS_ASSIGNABLE_TEST(b,            volatile T,  const volatile U);	\
	BKSGE_IS_ASSIGNABLE_TEST(b,      const volatile T,                 U);	\
	BKSGE_IS_ASSIGNABLE_TEST(b,      const volatile T,  const          U);	\
	BKSGE_IS_ASSIGNABLE_TEST(b,      const volatile T,        volatile U);	\
	BKSGE_IS_ASSIGNABLE_TEST(b,      const volatile T,  const volatile U)

#define BKSGE_IS_ASSIGNABLE_TEST_1(b, T, U)	\
	BKSGE_IS_ASSIGNABLE_TEST(b,                     T,                 U);	\
	BKSGE_IS_ASSIGNABLE_TEST(b,                     T,  const          U);	\
	BKSGE_IS_ASSIGNABLE_TEST(false,                 T,        volatile U);	\
	BKSGE_IS_ASSIGNABLE_TEST(false,                 T,  const volatile U);	\
	BKSGE_IS_ASSIGNABLE_TEST(false,  const          T,                 U);	\
	BKSGE_IS_ASSIGNABLE_TEST(false,  const          T,  const          U);	\
	BKSGE_IS_ASSIGNABLE_TEST(false,  const          T,        volatile U);	\
	BKSGE_IS_ASSIGNABLE_TEST(false,  const          T,  const volatile U);	\
	BKSGE_IS_ASSIGNABLE_TEST(false,        volatile T,                 U);	\
	BKSGE_IS_ASSIGNABLE_TEST(false,        volatile T,  const          U);	\
	BKSGE_IS_ASSIGNABLE_TEST(false,        volatile T,        volatile U);	\
	BKSGE_IS_ASSIGNABLE_TEST(false,        volatile T,  const volatile U);	\
	BKSGE_IS_ASSIGNABLE_TEST(false,  const volatile T,                 U);	\
	BKSGE_IS_ASSIGNABLE_TEST(false,  const volatile T,  const          U);	\
	BKSGE_IS_ASSIGNABLE_TEST(false,  const volatile T,        volatile U);	\
	BKSGE_IS_ASSIGNABLE_TEST(false,  const volatile T,  const volatile U)

#define BKSGE_IS_ASSIGNABLE_TEST_2(b, T, U)	\
	BKSGE_IS_ASSIGNABLE_TEST(b,                     T,                 U);	\
	BKSGE_IS_ASSIGNABLE_TEST(b,                     T,  const          U);	\
	BKSGE_IS_ASSIGNABLE_TEST(b,                     T,        volatile U);	\
	BKSGE_IS_ASSIGNABLE_TEST(b,                     T,  const volatile U);	\
	BKSGE_IS_ASSIGNABLE_TEST(false,  const          T,                 U);	\
	BKSGE_IS_ASSIGNABLE_TEST(false,  const          T,  const          U);	\
	BKSGE_IS_ASSIGNABLE_TEST(false,  const          T,        volatile U);	\
	BKSGE_IS_ASSIGNABLE_TEST(false,  const          T,  const volatile U);	\
	BKSGE_IS_ASSIGNABLE_TEST(b,            volatile T,                 U);	\
	BKSGE_IS_ASSIGNABLE_TEST(b,            volatile T,  const          U);	\
	BKSGE_IS_ASSIGNABLE_TEST(b,            volatile T,        volatile U);	\
	BKSGE_IS_ASSIGNABLE_TEST(b,            volatile T,  const volatile U);	\
	BKSGE_IS_ASSIGNABLE_TEST(false,  const volatile T,                 U);	\
	BKSGE_IS_ASSIGNABLE_TEST(false,  const volatile T,  const          U);	\
	BKSGE_IS_ASSIGNABLE_TEST(false,  const volatile T,        volatile U);	\
	BKSGE_IS_ASSIGNABLE_TEST(false,  const volatile T,  const volatile U)

#define BKSGE_IS_ASSIGNABLE_TEST_3(b, T, U)	\
	BKSGE_IS_ASSIGNABLE_TEST(b,                     T,                 U);	\
	BKSGE_IS_ASSIGNABLE_TEST(b,                     T,  const          U);	\
	BKSGE_IS_ASSIGNABLE_TEST(b,                     T,        volatile U);	\
	BKSGE_IS_ASSIGNABLE_TEST(b,                     T,  const volatile U);	\
	BKSGE_IS_ASSIGNABLE_TEST(false,  const          T,                 U);	\
	BKSGE_IS_ASSIGNABLE_TEST(false,  const          T,  const          U);	\
	BKSGE_IS_ASSIGNABLE_TEST(false,  const          T,        volatile U);	\
	BKSGE_IS_ASSIGNABLE_TEST(false,  const          T,  const volatile U);	\
	BKSGE_IS_ASSIGNABLE_TEST(false,        volatile T,                 U);	\
	BKSGE_IS_ASSIGNABLE_TEST(false,        volatile T,  const          U);	\
	BKSGE_IS_ASSIGNABLE_TEST(false,        volatile T,        volatile U);	\
	BKSGE_IS_ASSIGNABLE_TEST(false,        volatile T,  const volatile U);	\
	BKSGE_IS_ASSIGNABLE_TEST(false,  const volatile T,                 U);	\
	BKSGE_IS_ASSIGNABLE_TEST(false,  const volatile T,  const          U);	\
	BKSGE_IS_ASSIGNABLE_TEST(false,  const volatile T,        volatile U);	\
	BKSGE_IS_ASSIGNABLE_TEST(false,  const volatile T,  const volatile U)

#define BKSGE_IS_ASSIGNABLE_TEST_PTR(b, T, U)	\
	BKSGE_IS_ASSIGNABLE_TEST(b,                    T,                 U);	\
	BKSGE_IS_ASSIGNABLE_TEST(false,                T,  const          U);	\
	BKSGE_IS_ASSIGNABLE_TEST(false,                T,        volatile U);	\
	BKSGE_IS_ASSIGNABLE_TEST(false,                T,  const volatile U);	\
	BKSGE_IS_ASSIGNABLE_TEST(b,     const          T,                 U);	\
	BKSGE_IS_ASSIGNABLE_TEST(b,     const          T,  const          U);	\
	BKSGE_IS_ASSIGNABLE_TEST(false, const          T,        volatile U);	\
	BKSGE_IS_ASSIGNABLE_TEST(false, const          T,  const volatile U);	\
	BKSGE_IS_ASSIGNABLE_TEST(b,           volatile T,                 U);	\
	BKSGE_IS_ASSIGNABLE_TEST(false,       volatile T,  const          U);	\
	BKSGE_IS_ASSIGNABLE_TEST(b,           volatile T,        volatile U);	\
	BKSGE_IS_ASSIGNABLE_TEST(false,       volatile T,  const volatile U);	\
	BKSGE_IS_ASSIGNABLE_TEST(b,     const volatile T,                 U);	\
	BKSGE_IS_ASSIGNABLE_TEST(b,     const volatile T,  const          U);	\
	BKSGE_IS_ASSIGNABLE_TEST(b,     const volatile T,        volatile U);	\
	BKSGE_IS_ASSIGNABLE_TEST(b,     const volatile T,  const volatile U)

BKSGE_IS_ASSIGNABLE_TEST_1(true,  S1, S1);
BKSGE_IS_ASSIGNABLE_TEST_1(true,  S1, S1&);
BKSGE_IS_ASSIGNABLE_TEST_1(true,  S1, S1&&);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1, S1*);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1, S1[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1, S1[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1, S1(&)[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1, S1(&)[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1, S1(&&)[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1, S1(&&)[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1, S1(*)[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1, S1(*)[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1, S2);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1, int);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1, float);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1, bool);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1, enum_class_UDT);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1, void);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1, std::nullptr_t);
BKSGE_IS_ASSIGNABLE_TEST_1(true,  S1&, S1);
BKSGE_IS_ASSIGNABLE_TEST_1(true,  S1&, S1&);
BKSGE_IS_ASSIGNABLE_TEST_1(true,  S1&, S1&&);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1&, S1*);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1&, S1[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1&, S1[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1&, S1(&)[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1&, S1(&)[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1&, S1(&&)[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1&, S1(&&)[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1&, S1(*)[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1&, S1(*)[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1&, S2);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1&, int);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1&, float);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1&, bool);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1&, enum_class_UDT);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1&, void);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1&, std::nullptr_t);
BKSGE_IS_ASSIGNABLE_TEST_1(true,  S1&&, S1);
BKSGE_IS_ASSIGNABLE_TEST_1(true,  S1&&, S1&);
BKSGE_IS_ASSIGNABLE_TEST_1(true,  S1&&, S1&&);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1&&, S1*);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1&&, S1[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1&&, S1[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1&&, S1(&)[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1&&, S1(&)[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1&&, S1(&&)[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1&&, S1(&&)[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1&&, S1(*)[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1&&, S1(*)[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1&&, S2);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1&&, int);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1&&, float);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1&&, bool);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1&&, enum_class_UDT);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1&&, void);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1&&, std::nullptr_t);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1[2], S1);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1[2], S1&);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1[2], S1&&);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1[2], S1*);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1[2], S1[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1[2], S1[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1[2], S1(&)[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1[2], S1(&)[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1[2], S1(&&)[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1[2], S1(&&)[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1[2], S1(*)[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1[2], S1(*)[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1[2], S2);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1[2], int);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1[2], float);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1[2], bool);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1[2], enum_class_UDT);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1[2], void);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1[2], std::nullptr_t);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1[], S1);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1[], S1&);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1[], S1&&);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1[], S1*);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1[], S1[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1[], S1[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1[], S1(&)[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1[], S1(&)[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1[], S1(&&)[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1[], S1(&&)[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1[], S1(*)[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1[], S1(*)[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1[], S2);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1[], int);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1[], float);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1[], bool);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1[], enum_class_UDT);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1[], void);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1[], std::nullptr_t);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1(&)[2], S1);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1(&)[2], S1&);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1(&)[2], S1&&);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1(&)[2], S1*);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1(&)[2], S1[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1(&)[2], S1[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1(&)[2], S1(&)[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1(&)[2], S1(&)[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1(&)[2], S1(&&)[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1(&)[2], S1(&&)[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1(&)[2], S1(*)[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1(&)[2], S1(*)[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1(&)[2], S2);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1(&)[2], int);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1(&)[2], float);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1(&)[2], bool);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1(&)[2], enum_class_UDT);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1(&)[2], void);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1(&)[2], std::nullptr_t);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1(&)[], S1);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1(&)[], S1&);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1(&)[], S1&&);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1(&)[], S1*);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1(&)[], S1[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1(&)[], S1[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1(&)[], S1(&)[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1(&)[], S1(&)[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1(&)[], S1(&&)[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1(&)[], S1(&&)[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1(&)[], S1(*)[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1(&)[], S1(*)[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1(&)[], S2);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1(&)[], int);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1(&)[], float);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1(&)[], bool);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1(&)[], enum_class_UDT);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1(&)[], void);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1(&)[], std::nullptr_t);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1(&&)[2], S1);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1(&&)[2], S1&);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1(&&)[2], S1&&);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1(&&)[2], S1*);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1(&&)[2], S1[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1(&&)[2], S1[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1(&&)[2], S1(&)[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1(&&)[2], S1(&)[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1(&&)[2], S1(&&)[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1(&&)[2], S1(&&)[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1(&&)[2], S1(*)[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1(&&)[2], S1(*)[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1(&&)[2], S2);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1(&&)[2], int);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1(&&)[2], float);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1(&&)[2], bool);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1(&&)[2], enum_class_UDT);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1(&&)[2], void);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1(&&)[2], std::nullptr_t);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1(&&)[], S1);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1(&&)[], S1&);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1(&&)[], S1&&);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1(&&)[], S1*);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1(&&)[], S1[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1(&&)[], S1[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1(&&)[], S1(&)[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1(&&)[], S1(&)[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1(&&)[], S1(&&)[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1(&&)[], S1(&&)[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1(&&)[], S1(*)[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1(&&)[], S1(*)[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1(&&)[], S2);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1(&&)[], int);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1(&&)[], float);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1(&&)[], bool);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1(&&)[], enum_class_UDT);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1(&&)[], void);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1(&&)[], std::nullptr_t);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1(*)[2], S1);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1(*)[2], S1&);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1(*)[2], S1&&);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1(*)[2], S1*);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1(*)[2], S1[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1(*)[2], S1[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1(*)[2], S1(&)[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1(*)[2], S1(&)[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1(*)[2], S1(&&)[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1(*)[2], S1(&&)[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1(*)[2], S1(*)[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1(*)[2], S1(*)[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1(*)[2], S2);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1(*)[2], int);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1(*)[2], float);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1(*)[2], bool);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1(*)[2], enum_class_UDT);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1(*)[2], void);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1(*)[2], std::nullptr_t);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1(*)[], S1);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1(*)[], S1&);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1(*)[], S1&&);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1(*)[], S1*);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1(*)[], S1[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1(*)[], S1[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1(*)[], S1(&)[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1(*)[], S1(&)[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1(*)[], S1(&&)[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1(*)[], S1(&&)[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1(*)[], S1(*)[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1(*)[], S1(*)[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1(*)[], S2);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1(*)[], int);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1(*)[], float);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1(*)[], bool);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1(*)[], enum_class_UDT);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1(*)[], void);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1(*)[], std::nullptr_t);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1*, S1);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1*, S1&);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1*, S1&&);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1*, S1*);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1*, S1[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1*, S1[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1*, S1(&)[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1*, S1(&)[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1*, S1(&&)[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1*, S1(&&)[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1*, S1(*)[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1*, S1(*)[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1*, S2*);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1*, int*);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1*, float*);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1*, bool*);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1*, enum_class_UDT*);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1*, void*);
BKSGE_IS_ASSIGNABLE_TEST  (false, S1*, std::nullptr_t);
BKSGE_IS_ASSIGNABLE_TEST    (false, S1*&, S1);
BKSGE_IS_ASSIGNABLE_TEST    (false, S1*&, S1&);
BKSGE_IS_ASSIGNABLE_TEST    (false, S1*&, S1&&);
BKSGE_IS_ASSIGNABLE_TEST_PTR(true,  S1*&, S1*);
BKSGE_IS_ASSIGNABLE_TEST_PTR(true,  S1*&, S1[2]);			//
BKSGE_IS_ASSIGNABLE_TEST_PTR(true,  S1*&, S1[]);			//
BKSGE_IS_ASSIGNABLE_TEST_PTR(true,  S1*&, S1(&)[2]);		//
BKSGE_IS_ASSIGNABLE_TEST_PTR(true,  S1*&, S1(&)[]);			//
BKSGE_IS_ASSIGNABLE_TEST_PTR(true,  S1*&, S1(&&)[2]);		//
BKSGE_IS_ASSIGNABLE_TEST_PTR(true,  S1*&, S1(&&)[]);		//
BKSGE_IS_ASSIGNABLE_TEST    (false, S1*&, S1(*)[2]);
BKSGE_IS_ASSIGNABLE_TEST    (false, S1*&, S1(*)[]);
BKSGE_IS_ASSIGNABLE_TEST    (false, S1*&, S2*);
BKSGE_IS_ASSIGNABLE_TEST    (false, S1*&, int*);
BKSGE_IS_ASSIGNABLE_TEST    (false, S1*&, float*);
BKSGE_IS_ASSIGNABLE_TEST    (false, S1*&, bool*);
BKSGE_IS_ASSIGNABLE_TEST    (false, S1*&, enum_class_UDT*);
BKSGE_IS_ASSIGNABLE_TEST    (false, S1*&, void*);
BKSGE_IS_ASSIGNABLE_TEST_0  (true,  S1*&, std::nullptr_t);

BKSGE_IS_ASSIGNABLE_TEST_1(true,  S2, S2);
BKSGE_IS_ASSIGNABLE_TEST_1(true,  S2, S2&);
BKSGE_IS_ASSIGNABLE_TEST_1(true,  S2, S2&&);
BKSGE_IS_ASSIGNABLE_TEST  (false, S2, S2*);
BKSGE_IS_ASSIGNABLE_TEST  (false, S2, S2[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, S2, S2[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, S2, S2(&)[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, S2, S2(&)[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, S2, S2(&&)[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, S2, S2(&&)[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, S2, S2(*)[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, S2, S2(*)[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, S2, S1);
BKSGE_IS_ASSIGNABLE_TEST_3(true,  S2, int);
BKSGE_IS_ASSIGNABLE_TEST_3(true,  S2, float);
BKSGE_IS_ASSIGNABLE_TEST_3(true,  S2, bool);
BKSGE_IS_ASSIGNABLE_TEST  (false, S2, enum_class_UDT);
BKSGE_IS_ASSIGNABLE_TEST  (false, S2, void);
BKSGE_IS_ASSIGNABLE_TEST  (false, S2, std::nullptr_t);
BKSGE_IS_ASSIGNABLE_TEST_1(true,  S2&, S2);
BKSGE_IS_ASSIGNABLE_TEST_1(true,  S2&, S2&);
BKSGE_IS_ASSIGNABLE_TEST_1(true,  S2&, S2&&);
BKSGE_IS_ASSIGNABLE_TEST  (false, S2&, S2*);
BKSGE_IS_ASSIGNABLE_TEST  (false, S2&, S2[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, S2&, S2[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, S2&, S2(&)[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, S2&, S2(&)[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, S2&, S2(&&)[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, S2&, S2(&&)[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, S2&, S2(*)[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, S2&, S2(*)[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, S2&, S1);
BKSGE_IS_ASSIGNABLE_TEST_3(true,  S2&, int);
BKSGE_IS_ASSIGNABLE_TEST_3(true,  S2&, float);
BKSGE_IS_ASSIGNABLE_TEST_3(true,  S2&, bool);
BKSGE_IS_ASSIGNABLE_TEST  (false, S2&, enum_class_UDT);
BKSGE_IS_ASSIGNABLE_TEST  (false, S2&, void);
BKSGE_IS_ASSIGNABLE_TEST  (false, S2&, std::nullptr_t);
BKSGE_IS_ASSIGNABLE_TEST_1(true,  S2&&, S2);
BKSGE_IS_ASSIGNABLE_TEST_1(true,  S2&&, S2&);
BKSGE_IS_ASSIGNABLE_TEST_1(true,  S2&&, S2&&);
BKSGE_IS_ASSIGNABLE_TEST  (false, S2&&, S2*);
BKSGE_IS_ASSIGNABLE_TEST  (false, S2&&, S2[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, S2&&, S2[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, S2&&, S2(&)[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, S2&&, S2(&)[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, S2&&, S2(&&)[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, S2&&, S2(&&)[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, S2&&, S2(*)[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, S2&&, S2(*)[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, S2&&, S1);
BKSGE_IS_ASSIGNABLE_TEST_3(true,  S2&&, int);
BKSGE_IS_ASSIGNABLE_TEST_3(true,  S2&&, float);
BKSGE_IS_ASSIGNABLE_TEST_3(true,  S2&&, bool);
BKSGE_IS_ASSIGNABLE_TEST  (false, S2&&, enum_class_UDT);
BKSGE_IS_ASSIGNABLE_TEST  (false, S2&&, void);
BKSGE_IS_ASSIGNABLE_TEST  (false, S2&&, std::nullptr_t);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, S2[2], S2);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, S2[2], S2&);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, S2[2], S2&&);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, S2[2], S2*);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, S2[2], S2[2]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, S2[2], S2[]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, S2[2], S2(&)[2]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, S2[2], S2(&)[]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, S2[2], S2(&&)[2]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, S2[2], S2(&&)[]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, S2[2], S2(*)[2]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, S2[2], S2(*)[]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, S2[2], S1);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, S2[2], int);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, S2[2], float);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, S2[2], bool);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, S2[2], enum_class_UDT);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, S2[2], void);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, S2[2], std::nullptr_t);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, S2[], S2);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, S2[], S2&);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, S2[], S2&&);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, S2[], S2*);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, S2[], S2[2]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, S2[], S2[]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, S2[], S2(&)[2]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, S2[], S2(&)[]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, S2[], S2(&&)[2]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, S2[], S2(&&)[]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, S2[], S2(*)[2]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, S2[], S2(*)[]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, S2[], S1);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, S2[], int);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, S2[], float);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, S2[], bool);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, S2[], enum_class_UDT);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, S2[], void);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, S2[], std::nullptr_t);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, S2(&)[2], S2);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, S2(&)[2], S2&);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, S2(&)[2], S2&&);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, S2(&)[2], S2*);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, S2(&)[2], S2[2]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, S2(&)[2], S2[]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, S2(&)[2], S2(&)[2]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, S2(&)[2], S2(&)[]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, S2(&)[2], S2(&&)[2]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, S2(&)[2], S2(&&)[]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, S2(&)[2], S2(*)[2]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, S2(&)[2], S2(*)[]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, S2(&)[2], S1);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, S2(&)[2], int);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, S2(&)[2], float);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, S2(&)[2], bool);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, S2(&)[2], enum_class_UDT);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, S2(&)[2], void);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, S2(&)[2], std::nullptr_t);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, S2(&)[], S2);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, S2(&)[], S2&);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, S2(&)[], S2&&);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, S2(&)[], S2*);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, S2(&)[], S2[2]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, S2(&)[], S2[]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, S2(&)[], S2(&)[2]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, S2(&)[], S2(&)[]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, S2(&)[], S2(&&)[2]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, S2(&)[], S2(&&)[]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, S2(&)[], S2(*)[2]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, S2(&)[], S2(*)[]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, S2(&)[], S1);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, S2(&)[], int);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, S2(&)[], float);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, S2(&)[], bool);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, S2(&)[], enum_class_UDT);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, S2(&)[], void);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, S2(&)[], std::nullptr_t);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, S2(&&)[2], S2);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, S2(&&)[2], S2&);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, S2(&&)[2], S2&&);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, S2(&&)[2], S2*);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, S2(&&)[2], S2[2]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, S2(&&)[2], S2[]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, S2(&&)[2], S2(&)[2]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, S2(&&)[2], S2(&)[]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, S2(&&)[2], S2(&&)[2]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, S2(&&)[2], S2(&&)[]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, S2(&&)[2], S2(*)[2]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, S2(&&)[2], S2(*)[]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, S2(&&)[2], S1);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, S2(&&)[2], int);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, S2(&&)[2], float);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, S2(&&)[2], bool);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, S2(&&)[2], enum_class_UDT);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, S2(&&)[2], void);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, S2(&&)[2], std::nullptr_t);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, S2(&&)[], S2);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, S2(&&)[], S2&);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, S2(&&)[], S2&&);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, S2(&&)[], S2*);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, S2(&&)[], S2[2]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, S2(&&)[], S2[]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, S2(&&)[], S2(&)[2]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, S2(&&)[], S2(&)[]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, S2(&&)[], S2(&&)[2]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, S2(&&)[], S2(&&)[]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, S2(&&)[], S2(*)[2]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, S2(&&)[], S2(*)[]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, S2(&&)[], S1);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, S2(&&)[], int);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, S2(&&)[], float);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, S2(&&)[], bool);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, S2(&&)[], enum_class_UDT);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, S2(&&)[], void);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, S2(&&)[], std::nullptr_t);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, S2(*)[2], S2);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, S2(*)[2], S2&);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, S2(*)[2], S2&&);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, S2(*)[2], S2*);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, S2(*)[2], S2[2]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, S2(*)[2], S2[]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, S2(*)[2], S2(&)[2]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, S2(*)[2], S2(&)[]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, S2(*)[2], S2(&&)[2]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, S2(*)[2], S2(&&)[]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, S2(*)[2], S2(*)[2]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, S2(*)[2], S2(*)[]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, S2(*)[2], S1);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, S2(*)[2], int);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, S2(*)[2], float);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, S2(*)[2], bool);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, S2(*)[2], enum_class_UDT);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, S2(*)[2], void);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, S2(*)[2], std::nullptr_t);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, S2(*)[], S2);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, S2(*)[], S2&);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, S2(*)[], S2&&);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, S2(*)[], S2*);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, S2(*)[], S2[2]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, S2(*)[], S2[]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, S2(*)[], S2(&)[2]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, S2(*)[], S2(&)[]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, S2(*)[], S2(&&)[2]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, S2(*)[], S2(&&)[]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, S2(*)[], S2(*)[2]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, S2(*)[], S2(*)[]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, S2(*)[], S1);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, S2(*)[], int);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, S2(*)[], float);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, S2(*)[], bool);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, S2(*)[], enum_class_UDT);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, S2(*)[], void);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, S2(*)[], std::nullptr_t);
BKSGE_IS_ASSIGNABLE_TEST  (false, S2*, S2);
BKSGE_IS_ASSIGNABLE_TEST  (false, S2*, S2&);
BKSGE_IS_ASSIGNABLE_TEST  (false, S2*, S2&&);
BKSGE_IS_ASSIGNABLE_TEST  (false, S2*, S2*);
BKSGE_IS_ASSIGNABLE_TEST  (false, S2*, S2[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, S2*, S2[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, S2*, S2(&)[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, S2*, S2(&)[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, S2*, S2(&&)[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, S2*, S2(&&)[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, S2*, S2(*)[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, S2*, S2(*)[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, S2*, S1*);
BKSGE_IS_ASSIGNABLE_TEST  (false, S2*, int*);
BKSGE_IS_ASSIGNABLE_TEST  (false, S2*, float*);
BKSGE_IS_ASSIGNABLE_TEST  (false, S2*, bool*);
BKSGE_IS_ASSIGNABLE_TEST  (false, S2*, enum_class_UDT*);
BKSGE_IS_ASSIGNABLE_TEST  (false, S2*, void*);
BKSGE_IS_ASSIGNABLE_TEST  (false, S2*, std::nullptr_t);
BKSGE_IS_ASSIGNABLE_TEST    (false, S2*&, S2);
BKSGE_IS_ASSIGNABLE_TEST    (false, S2*&, S2&);
BKSGE_IS_ASSIGNABLE_TEST    (false, S2*&, S2&&);
BKSGE_IS_ASSIGNABLE_TEST_PTR(true,  S2*&, S2*);
BKSGE_IS_ASSIGNABLE_TEST_PTR(true,  S2*&, S2[2]);			//
BKSGE_IS_ASSIGNABLE_TEST_PTR(true,  S2*&, S2[]);			//
BKSGE_IS_ASSIGNABLE_TEST_PTR(true,  S2*&, S2(&)[2]);		//
BKSGE_IS_ASSIGNABLE_TEST_PTR(true,  S2*&, S2(&)[]);			//
BKSGE_IS_ASSIGNABLE_TEST_PTR(true,  S2*&, S2(&&)[2]);		//
BKSGE_IS_ASSIGNABLE_TEST_PTR(true,  S2*&, S2(&&)[]);		//
BKSGE_IS_ASSIGNABLE_TEST    (false, S2*&, S2(*)[2]);
BKSGE_IS_ASSIGNABLE_TEST    (false, S2*&, S2(*)[]);
BKSGE_IS_ASSIGNABLE_TEST    (false, S2*&, S1*);
BKSGE_IS_ASSIGNABLE_TEST    (false, S2*&, int*);
BKSGE_IS_ASSIGNABLE_TEST    (false, S2*&, float*);
BKSGE_IS_ASSIGNABLE_TEST    (false, S2*&, bool*);
BKSGE_IS_ASSIGNABLE_TEST    (false, S2*&, enum_class_UDT*);
BKSGE_IS_ASSIGNABLE_TEST    (false, S2*&, void*);
BKSGE_IS_ASSIGNABLE_TEST_0  (true,  S2*&, std::nullptr_t);

BKSGE_IS_ASSIGNABLE_TEST  (false, int, int);
BKSGE_IS_ASSIGNABLE_TEST  (false, int, int&);
BKSGE_IS_ASSIGNABLE_TEST  (false, int, int&&);
BKSGE_IS_ASSIGNABLE_TEST  (false, int, int*);
BKSGE_IS_ASSIGNABLE_TEST  (false, int, int[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, int, int[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, int, int(&)[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, int, int(&)[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, int, int(&&)[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, int, int(&&)[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, int, int(*)[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, int, int(*)[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, int, float);
BKSGE_IS_ASSIGNABLE_TEST  (false, int, bool);
BKSGE_IS_ASSIGNABLE_TEST  (false, int, enum_class_UDT);
BKSGE_IS_ASSIGNABLE_TEST  (false, int, enum_UDT);
BKSGE_IS_ASSIGNABLE_TEST  (false, int, void);
BKSGE_IS_ASSIGNABLE_TEST  (false, int, std::nullptr_t);
BKSGE_IS_ASSIGNABLE_TEST_2(true,  int&, int);				//
BKSGE_IS_ASSIGNABLE_TEST_2(true,  int&, int&);				//
BKSGE_IS_ASSIGNABLE_TEST_2(true,  int&, int&&);				//
BKSGE_IS_ASSIGNABLE_TEST  (false, int&, int*);
BKSGE_IS_ASSIGNABLE_TEST  (false, int&, int[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, int&, int[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, int&, int(&)[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, int&, int(&)[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, int&, int(&&)[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, int&, int(&&)[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, int&, int(*)[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, int&, int(*)[]);
BKSGE_IS_ASSIGNABLE_TEST_2(true,  int&, float);				//
BKSGE_IS_ASSIGNABLE_TEST_2(true,  int&, bool);				//
BKSGE_IS_ASSIGNABLE_TEST_2(false, int&, enum_class_UDT);
BKSGE_IS_ASSIGNABLE_TEST_2(true,  int&, enum_UDT);			//
BKSGE_IS_ASSIGNABLE_TEST  (false, int&, void);
BKSGE_IS_ASSIGNABLE_TEST  (false, int&, std::nullptr_t);
BKSGE_IS_ASSIGNABLE_TEST  (false, int&&, int);
BKSGE_IS_ASSIGNABLE_TEST  (false, int&&, int&);
BKSGE_IS_ASSIGNABLE_TEST  (false, int&&, int&&);
BKSGE_IS_ASSIGNABLE_TEST  (false, int&&, int*);
BKSGE_IS_ASSIGNABLE_TEST  (false, int&&, int[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, int&&, int[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, int&&, int(&)[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, int&&, int(&)[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, int&&, int(&&)[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, int&&, int(&&)[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, int&&, int(*)[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, int&&, int(*)[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, int&&, float);
BKSGE_IS_ASSIGNABLE_TEST  (false, int&&, bool);
BKSGE_IS_ASSIGNABLE_TEST  (false, int&&, enum_class_UDT);
BKSGE_IS_ASSIGNABLE_TEST  (false, int&&, enum_UDT);
BKSGE_IS_ASSIGNABLE_TEST  (false, int&&, void);
BKSGE_IS_ASSIGNABLE_TEST  (false, int&&, std::nullptr_t);
BKSGE_IS_ASSIGNABLE_TEST  (false, int[2], int);
BKSGE_IS_ASSIGNABLE_TEST  (false, int[2], int&);
BKSGE_IS_ASSIGNABLE_TEST  (false, int[2], int&&);
BKSGE_IS_ASSIGNABLE_TEST  (false, int[2], int*);
BKSGE_IS_ASSIGNABLE_TEST  (false, int[2], int[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, int[2], int[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, int[2], int(&)[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, int[2], int(&)[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, int[2], int(&&)[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, int[2], int(&&)[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, int[2], int(*)[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, int[2], int(*)[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, int[2], float);
BKSGE_IS_ASSIGNABLE_TEST  (false, int[2], bool);
BKSGE_IS_ASSIGNABLE_TEST  (false, int[2], enum_class_UDT);
BKSGE_IS_ASSIGNABLE_TEST  (false, int[2], enum_UDT);
BKSGE_IS_ASSIGNABLE_TEST  (false, int[2], void);
BKSGE_IS_ASSIGNABLE_TEST  (false, int[2], std::nullptr_t);
BKSGE_IS_ASSIGNABLE_TEST  (false, int[], int);
BKSGE_IS_ASSIGNABLE_TEST  (false, int[], int&);
BKSGE_IS_ASSIGNABLE_TEST  (false, int[], int&&);
BKSGE_IS_ASSIGNABLE_TEST  (false, int[], int*);
BKSGE_IS_ASSIGNABLE_TEST  (false, int[], int[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, int[], int[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, int[], int(&)[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, int[], int(&)[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, int[], int(&&)[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, int[], int(&&)[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, int[], int(*)[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, int[], int(*)[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, int[], float);
BKSGE_IS_ASSIGNABLE_TEST  (false, int[], bool);
BKSGE_IS_ASSIGNABLE_TEST  (false, int[], enum_class_UDT);
BKSGE_IS_ASSIGNABLE_TEST  (false, int[], enum_UDT);
BKSGE_IS_ASSIGNABLE_TEST  (false, int[], void);
BKSGE_IS_ASSIGNABLE_TEST  (false, int[], std::nullptr_t);
BKSGE_IS_ASSIGNABLE_TEST  (false, int(&)[2], int);
BKSGE_IS_ASSIGNABLE_TEST  (false, int(&)[2], int&);
BKSGE_IS_ASSIGNABLE_TEST  (false, int(&)[2], int&&);
BKSGE_IS_ASSIGNABLE_TEST  (false, int(&)[2], int*);
BKSGE_IS_ASSIGNABLE_TEST  (false, int(&)[2], int[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, int(&)[2], int[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, int(&)[2], int(&)[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, int(&)[2], int(&)[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, int(&)[2], int(&&)[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, int(&)[2], int(&&)[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, int(&)[2], int(*)[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, int(&)[2], int(*)[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, int(&)[2], float);
BKSGE_IS_ASSIGNABLE_TEST  (false, int(&)[2], bool);
BKSGE_IS_ASSIGNABLE_TEST  (false, int(&)[2], enum_class_UDT);
BKSGE_IS_ASSIGNABLE_TEST  (false, int(&)[2], enum_UDT);
BKSGE_IS_ASSIGNABLE_TEST  (false, int(&)[2], void);
BKSGE_IS_ASSIGNABLE_TEST  (false, int(&)[2], std::nullptr_t);
BKSGE_IS_ASSIGNABLE_TEST  (false, int(&)[], int);
BKSGE_IS_ASSIGNABLE_TEST  (false, int(&)[], int&);
BKSGE_IS_ASSIGNABLE_TEST  (false, int(&)[], int&&);
BKSGE_IS_ASSIGNABLE_TEST  (false, int(&)[], int*);
BKSGE_IS_ASSIGNABLE_TEST  (false, int(&)[], int[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, int(&)[], int[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, int(&)[], int(&)[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, int(&)[], int(&)[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, int(&)[], int(&&)[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, int(&)[], int(&&)[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, int(&)[], int(*)[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, int(&)[], int(*)[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, int(&)[], float);
BKSGE_IS_ASSIGNABLE_TEST  (false, int(&)[], bool);
BKSGE_IS_ASSIGNABLE_TEST  (false, int(&)[], enum_class_UDT);
BKSGE_IS_ASSIGNABLE_TEST  (false, int(&)[], enum_UDT);
BKSGE_IS_ASSIGNABLE_TEST  (false, int(&)[], void);
BKSGE_IS_ASSIGNABLE_TEST  (false, int(&)[], std::nullptr_t);
BKSGE_IS_ASSIGNABLE_TEST  (false, int(&&)[2], int);
BKSGE_IS_ASSIGNABLE_TEST  (false, int(&&)[2], int&);
BKSGE_IS_ASSIGNABLE_TEST  (false, int(&&)[2], int&&);
BKSGE_IS_ASSIGNABLE_TEST  (false, int(&&)[2], int*);
BKSGE_IS_ASSIGNABLE_TEST  (false, int(&&)[2], int[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, int(&&)[2], int[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, int(&&)[2], int(&)[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, int(&&)[2], int(&)[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, int(&&)[2], int(&&)[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, int(&&)[2], int(&&)[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, int(&&)[2], int(*)[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, int(&&)[2], int(*)[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, int(&&)[2], float);
BKSGE_IS_ASSIGNABLE_TEST  (false, int(&&)[2], bool);
BKSGE_IS_ASSIGNABLE_TEST  (false, int(&&)[2], enum_class_UDT);
BKSGE_IS_ASSIGNABLE_TEST  (false, int(&&)[2], enum_UDT);
BKSGE_IS_ASSIGNABLE_TEST  (false, int(&&)[2], void);
BKSGE_IS_ASSIGNABLE_TEST  (false, int(&&)[2], std::nullptr_t);
BKSGE_IS_ASSIGNABLE_TEST  (false, int(&&)[], int);
BKSGE_IS_ASSIGNABLE_TEST  (false, int(&&)[], int&);
BKSGE_IS_ASSIGNABLE_TEST  (false, int(&&)[], int&&);
BKSGE_IS_ASSIGNABLE_TEST  (false, int(&&)[], int*);
BKSGE_IS_ASSIGNABLE_TEST  (false, int(&&)[], int[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, int(&&)[], int[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, int(&&)[], int(&)[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, int(&&)[], int(&)[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, int(&&)[], int(&&)[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, int(&&)[], int(&&)[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, int(&&)[], int(*)[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, int(&&)[], int(*)[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, int(&&)[], float);
BKSGE_IS_ASSIGNABLE_TEST  (false, int(&&)[], bool);
BKSGE_IS_ASSIGNABLE_TEST  (false, int(&&)[], enum_class_UDT);
BKSGE_IS_ASSIGNABLE_TEST  (false, int(&&)[], enum_UDT);
BKSGE_IS_ASSIGNABLE_TEST  (false, int(&&)[], void);
BKSGE_IS_ASSIGNABLE_TEST  (false, int(&&)[], std::nullptr_t);
BKSGE_IS_ASSIGNABLE_TEST  (false, int(*)[2], int);
BKSGE_IS_ASSIGNABLE_TEST  (false, int(*)[2], int&);
BKSGE_IS_ASSIGNABLE_TEST  (false, int(*)[2], int&&);
BKSGE_IS_ASSIGNABLE_TEST  (false, int(*)[2], int*);
BKSGE_IS_ASSIGNABLE_TEST  (false, int(*)[2], int[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, int(*)[2], int[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, int(*)[2], int(&)[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, int(*)[2], int(&)[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, int(*)[2], int(&&)[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, int(*)[2], int(&&)[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, int(*)[2], int(*)[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, int(*)[2], int(*)[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, int(*)[2], float);
BKSGE_IS_ASSIGNABLE_TEST  (false, int(*)[2], bool);
BKSGE_IS_ASSIGNABLE_TEST  (false, int(*)[2], enum_class_UDT);
BKSGE_IS_ASSIGNABLE_TEST  (false, int(*)[2], enum_UDT);
BKSGE_IS_ASSIGNABLE_TEST  (false, int(*)[2], void);
BKSGE_IS_ASSIGNABLE_TEST  (false, int(*)[2], std::nullptr_t);
BKSGE_IS_ASSIGNABLE_TEST  (false, int(*)[], int);
BKSGE_IS_ASSIGNABLE_TEST  (false, int(*)[], int&);
BKSGE_IS_ASSIGNABLE_TEST  (false, int(*)[], int&&);
BKSGE_IS_ASSIGNABLE_TEST  (false, int(*)[], int*);
BKSGE_IS_ASSIGNABLE_TEST  (false, int(*)[], int[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, int(*)[], int[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, int(*)[], int(&)[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, int(*)[], int(&)[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, int(*)[], int(&&)[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, int(*)[], int(&&)[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, int(*)[], int(*)[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, int(*)[], int(*)[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, int(*)[], float);
BKSGE_IS_ASSIGNABLE_TEST  (false, int(*)[], bool);
BKSGE_IS_ASSIGNABLE_TEST  (false, int(*)[], enum_class_UDT);
BKSGE_IS_ASSIGNABLE_TEST  (false, int(*)[], enum_UDT);
BKSGE_IS_ASSIGNABLE_TEST  (false, int(*)[], void);
BKSGE_IS_ASSIGNABLE_TEST  (false, int(*)[], std::nullptr_t);
BKSGE_IS_ASSIGNABLE_TEST  (false, int*, int);
BKSGE_IS_ASSIGNABLE_TEST  (false, int*, int&);
BKSGE_IS_ASSIGNABLE_TEST  (false, int*, int&&);
BKSGE_IS_ASSIGNABLE_TEST  (false, int*, int*);
BKSGE_IS_ASSIGNABLE_TEST  (false, int*, int[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, int*, int[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, int*, int(&)[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, int*, int(&)[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, int*, int(&&)[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, int*, int(&&)[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, int*, int(*)[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, int*, int(*)[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, int*, float*);
BKSGE_IS_ASSIGNABLE_TEST  (false, int*, bool*);
BKSGE_IS_ASSIGNABLE_TEST  (false, int*, enum_class_UDT*);
BKSGE_IS_ASSIGNABLE_TEST  (false, int*, enum_UDT*);
BKSGE_IS_ASSIGNABLE_TEST  (false, int*, void);
BKSGE_IS_ASSIGNABLE_TEST  (false, int*, void*);
BKSGE_IS_ASSIGNABLE_TEST  (false, int*, std::nullptr_t);
BKSGE_IS_ASSIGNABLE_TEST    (false, int*&, int);
BKSGE_IS_ASSIGNABLE_TEST    (false, int*&, int&);
BKSGE_IS_ASSIGNABLE_TEST    (false, int*&, int&&);
BKSGE_IS_ASSIGNABLE_TEST_PTR(true,  int*&, int*);
BKSGE_IS_ASSIGNABLE_TEST_PTR(true,  int*&, int[2]);				//
BKSGE_IS_ASSIGNABLE_TEST_PTR(true,  int*&, int[]);				//
BKSGE_IS_ASSIGNABLE_TEST_PTR(true,  int*&, int(&)[2]);			//
BKSGE_IS_ASSIGNABLE_TEST_PTR(true,  int*&, int(&)[]);			//
BKSGE_IS_ASSIGNABLE_TEST_PTR(true,  int*&, int(&&)[2]);			//
BKSGE_IS_ASSIGNABLE_TEST_PTR(true,  int*&, int(&&)[]);			//
BKSGE_IS_ASSIGNABLE_TEST    (false, int*&, int(*)[2]);
BKSGE_IS_ASSIGNABLE_TEST    (false, int*&, int(*)[]);
BKSGE_IS_ASSIGNABLE_TEST    (false, int*&, float*);
BKSGE_IS_ASSIGNABLE_TEST    (false, int*&, bool*);
BKSGE_IS_ASSIGNABLE_TEST    (false, int*&, enum_class_UDT*);
BKSGE_IS_ASSIGNABLE_TEST    (false, int*&, enum_UDT*);
BKSGE_IS_ASSIGNABLE_TEST    (false, int*&, void);
BKSGE_IS_ASSIGNABLE_TEST    (false, int*&, void*);
BKSGE_IS_ASSIGNABLE_TEST_0  (true,  int*&, std::nullptr_t);

BKSGE_IS_ASSIGNABLE_TEST_2(false, float, float);				//
BKSGE_IS_ASSIGNABLE_TEST_2(false, float, float&);				//
BKSGE_IS_ASSIGNABLE_TEST_2(false, float, float&&);				//
BKSGE_IS_ASSIGNABLE_TEST  (false, float, float*);
BKSGE_IS_ASSIGNABLE_TEST  (false, float, float[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, float, float[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, float, float(&)[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, float, float(&)[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, float, float(&&)[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, float, float(&&)[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, float, float(*)[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, float, float(*)[]);
BKSGE_IS_ASSIGNABLE_TEST_2(false, float, int);					//
BKSGE_IS_ASSIGNABLE_TEST_2(false, float, bool);					//
BKSGE_IS_ASSIGNABLE_TEST_2(false, float, enum_class_UDT);
BKSGE_IS_ASSIGNABLE_TEST_2(false, float, enum_UDT);				//
BKSGE_IS_ASSIGNABLE_TEST  (false, float, void);
BKSGE_IS_ASSIGNABLE_TEST  (false, float, std::nullptr_t);
BKSGE_IS_ASSIGNABLE_TEST_2(true,  float&, float);				//
BKSGE_IS_ASSIGNABLE_TEST_2(true,  float&, float&);				//
BKSGE_IS_ASSIGNABLE_TEST_2(true,  float&, float&&);				//
BKSGE_IS_ASSIGNABLE_TEST  (false, float&, float*);
BKSGE_IS_ASSIGNABLE_TEST  (false, float&, float[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, float&, float[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, float&, float(&)[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, float&, float(&)[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, float&, float(&&)[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, float&, float(&&)[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, float&, float(*)[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, float&, float(*)[]);
BKSGE_IS_ASSIGNABLE_TEST_2(true,  float&, int);					//
BKSGE_IS_ASSIGNABLE_TEST_2(true,  float&, bool);				//
BKSGE_IS_ASSIGNABLE_TEST_2(false, float&, enum_class_UDT);
BKSGE_IS_ASSIGNABLE_TEST_2(true,  float&, enum_UDT);			//
BKSGE_IS_ASSIGNABLE_TEST  (false, float&, void);
BKSGE_IS_ASSIGNABLE_TEST  (false, float&, std::nullptr_t);
BKSGE_IS_ASSIGNABLE_TEST_2(false, float&&, float);				//
BKSGE_IS_ASSIGNABLE_TEST_2(false, float&&, float&);				//
BKSGE_IS_ASSIGNABLE_TEST_2(false, float&&, float&&);			//
BKSGE_IS_ASSIGNABLE_TEST  (false, float&&, float*);
BKSGE_IS_ASSIGNABLE_TEST  (false, float&&, float[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, float&&, float[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, float&&, float(&)[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, float&&, float(&)[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, float&&, float(&&)[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, float&&, float(&&)[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, float&&, float(*)[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, float&&, float(*)[]);
BKSGE_IS_ASSIGNABLE_TEST_2(false, float&&, int);				//
BKSGE_IS_ASSIGNABLE_TEST_2(false, float&&, bool);				//
BKSGE_IS_ASSIGNABLE_TEST  (false, float&&, enum_class_UDT);
BKSGE_IS_ASSIGNABLE_TEST_2(false, float&&, enum_UDT);			//
BKSGE_IS_ASSIGNABLE_TEST  (false, float&&, void);
BKSGE_IS_ASSIGNABLE_TEST  (false, float&&, std::nullptr_t);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, float[2], float);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, float[2], float&);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, float[2], float&&);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, float[2], float*);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, float[2], float[2]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, float[2], float[]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, float[2], float(&)[2]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, float[2], float(&)[]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, float[2], float(&&)[2]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, float[2], float(&&)[]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, float[2], float(*)[2]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, float[2], float(*)[]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, float[2], float);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, float[2], bool);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, float[2], enum_class_UDT);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, float[2], enum_UDT);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, float[2], void);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, float[2], std::nullptr_t);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, float[], float);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, float[], float&);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, float[], float&&);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, float[], float*);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, float[], float[2]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, float[], float[]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, float[], float(&)[2]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, float[], float(&)[]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, float[], float(&&)[2]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, float[], float(&&)[]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, float[], float(*)[2]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, float[], float(*)[]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, float[], int);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, float[], bool);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, float[], enum_class_UDT);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, float[], enum_UDT);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, float[], void);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, float[], std::nullptr_t);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, float(&)[2], float);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, float(&)[2], float&);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, float(&)[2], float&&);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, float(&)[2], float*);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, float(&)[2], float[2]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, float(&)[2], float[]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, float(&)[2], float(&)[2]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, float(&)[2], float(&)[]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, float(&)[2], float(&&)[2]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, float(&)[2], float(&&)[]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, float(&)[2], float(*)[2]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, float(&)[2], float(*)[]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, float(&)[2], int);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, float(&)[2], bool);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, float(&)[2], enum_class_UDT);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, float(&)[2], enum_UDT);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, float(&)[2], void);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, float(&)[2], std::nullptr_t);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, float(&)[], float);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, float(&)[], float&);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, float(&)[], float&&);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, float(&)[], float*);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, float(&)[], float[2]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, float(&)[], float[]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, float(&)[], float(&)[2]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, float(&)[], float(&)[]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, float(&)[], float(&&)[2]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, float(&)[], float(&&)[]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, float(&)[], float(*)[2]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, float(&)[], float(*)[]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, float(&)[], int);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, float(&)[], bool);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, float(&)[], enum_class_UDT);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, float(&)[], enum_UDT);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, float(&)[], void);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, float(&)[], std::nullptr_t);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, float(&&)[2], float);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, float(&&)[2], float&);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, float(&&)[2], float&&);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, float(&&)[2], float*);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, float(&&)[2], float[2]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, float(&&)[2], float[]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, float(&&)[2], float(&)[2]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, float(&&)[2], float(&)[]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, float(&&)[2], float(&&)[2]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, float(&&)[2], float(&&)[]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, float(&&)[2], float(*)[2]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, float(&&)[2], float(*)[]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, float(&&)[2], int);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, float(&&)[2], bool);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, float(&&)[2], enum_class_UDT);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, float(&&)[2], enum_UDT);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, float(&&)[2], void);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, float(&&)[2], std::nullptr_t);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, float(&&)[], float);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, float(&&)[], float&);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, float(&&)[], float&&);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, float(&&)[], float*);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, float(&&)[], float[2]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, float(&&)[], float[]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, float(&&)[], float(&)[2]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, float(&&)[], float(&)[]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, float(&&)[], float(&&)[2]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, float(&&)[], float(&&)[]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, float(&&)[], float(*)[2]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, float(&&)[], float(*)[]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, float(&&)[], int);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, float(&&)[], bool);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, float(&&)[], enum_class_UDT);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, float(&&)[], enum_UDT);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, float(&&)[], void);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, float(&&)[], std::nullptr_t);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, float(*)[2], float);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, float(*)[2], float&);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, float(*)[2], float&&);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, float(*)[2], float*);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, float(*)[2], float[2]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, float(*)[2], float[]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, float(*)[2], float(&)[2]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, float(*)[2], float(&)[]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, float(*)[2], float(&&)[2]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, float(*)[2], float(&&)[]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, float(*)[2], float(*)[2]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, float(*)[2], float(*)[]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, float(*)[2], int);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, float(*)[2], bool);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, float(*)[2], enum_class_UDT);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, float(*)[2], enum_UDT);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, float(*)[2], void);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, float(*)[2], std::nullptr_t);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, float(*)[], float);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, float(*)[], float&);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, float(*)[], float&&);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, float(*)[], float*);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, float(*)[], float[2]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, float(*)[], float[]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, float(*)[], float(&)[2]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, float(*)[], float(&)[]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, float(*)[], float(&&)[2]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, float(*)[], float(&&)[]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, float(*)[], float(*)[2]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, float(*)[], float(*)[]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, float(*)[], int);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, float(*)[], bool);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, float(*)[], enum_class_UDT);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, float(*)[], enum_UDT);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, float(*)[], void);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, float(*)[], std::nullptr_t);
BKSGE_IS_ASSIGNABLE_TEST  (false, float*, float);
BKSGE_IS_ASSIGNABLE_TEST  (false, float*, float&);
BKSGE_IS_ASSIGNABLE_TEST  (false, float*, float&&);
BKSGE_IS_ASSIGNABLE_TEST  (false, float*, float*);
BKSGE_IS_ASSIGNABLE_TEST  (false, float*, float[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, float*, float[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, float*, float(&)[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, float*, float(&)[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, float*, float(&&)[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, float*, float(&&)[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, float*, float(*)[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, float*, float(*)[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, float*, int*);
BKSGE_IS_ASSIGNABLE_TEST  (false, float*, bool*);
BKSGE_IS_ASSIGNABLE_TEST  (false, float*, enum_class_UDT*);
BKSGE_IS_ASSIGNABLE_TEST  (false, float*, enum_UDT*);
BKSGE_IS_ASSIGNABLE_TEST  (false, float*, void);
BKSGE_IS_ASSIGNABLE_TEST  (false, float*, void*);
BKSGE_IS_ASSIGNABLE_TEST  (false, float*, std::nullptr_t);
BKSGE_IS_ASSIGNABLE_TEST    (false, float*&, float);
BKSGE_IS_ASSIGNABLE_TEST    (false, float*&, float&);
BKSGE_IS_ASSIGNABLE_TEST    (false, float*&, float&&);
BKSGE_IS_ASSIGNABLE_TEST_PTR(true,  float*&, float*);
BKSGE_IS_ASSIGNABLE_TEST_PTR(true,  float*&, float[2]);			//
BKSGE_IS_ASSIGNABLE_TEST_PTR(true,  float*&, float[]);			//
BKSGE_IS_ASSIGNABLE_TEST_PTR(true,  float*&, float(&)[2]);		//
BKSGE_IS_ASSIGNABLE_TEST_PTR(true,  float*&, float(&)[]);		//
BKSGE_IS_ASSIGNABLE_TEST_PTR(true,  float*&, float(&&)[2]);		//
BKSGE_IS_ASSIGNABLE_TEST_PTR(true,  float*&, float(&&)[]);		//
BKSGE_IS_ASSIGNABLE_TEST    (false, float*&, float(*)[2]);
BKSGE_IS_ASSIGNABLE_TEST    (false, float*&, float(*)[]);
BKSGE_IS_ASSIGNABLE_TEST    (false, float*&, int*);
BKSGE_IS_ASSIGNABLE_TEST    (false, float*&, bool*);
BKSGE_IS_ASSIGNABLE_TEST    (false, float*&, enum_class_UDT*);
BKSGE_IS_ASSIGNABLE_TEST    (false, float*&, enum_UDT*);
BKSGE_IS_ASSIGNABLE_TEST    (false, float*&, void);
BKSGE_IS_ASSIGNABLE_TEST    (false, float*&, void*);
BKSGE_IS_ASSIGNABLE_TEST_0  (true,  float*&, std::nullptr_t);

BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT, enum_class_UDT);
BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT, enum_class_UDT&);
BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT, enum_class_UDT&&);
BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT, enum_class_UDT*);
BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT, enum_class_UDT[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT, enum_class_UDT[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT, enum_class_UDT(&)[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT, enum_class_UDT(&)[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT, enum_class_UDT(&&)[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT, enum_class_UDT(&&)[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT, enum_class_UDT(*)[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT, enum_class_UDT(*)[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT, float);
BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT, bool);
BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT, int);
BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT, enum_UDT);
BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT, void);
BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT, std::nullptr_t);
BKSGE_IS_ASSIGNABLE_TEST_2(true,  enum_class_UDT&, enum_class_UDT);
BKSGE_IS_ASSIGNABLE_TEST_2(true,  enum_class_UDT&, enum_class_UDT&);
BKSGE_IS_ASSIGNABLE_TEST_2(true,  enum_class_UDT&, enum_class_UDT&&);
BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT&, enum_class_UDT*);
BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT&, enum_class_UDT[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT&, enum_class_UDT[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT&, enum_class_UDT(&)[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT&, enum_class_UDT(&)[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT&, enum_class_UDT(&&)[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT&, enum_class_UDT(&&)[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT&, enum_class_UDT(*)[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT&, enum_class_UDT(*)[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT&, float);
BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT&, bool);
BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT&, int);
BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT&, enum_UDT);
BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT&, void);
BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT&, std::nullptr_t);
BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT&&, enum_class_UDT);
BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT&&, enum_class_UDT&);
BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT&&, enum_class_UDT&&);
BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT&&, enum_class_UDT*);
BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT&&, enum_class_UDT[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT&&, enum_class_UDT[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT&&, enum_class_UDT(&)[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT&&, enum_class_UDT(&)[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT&&, enum_class_UDT(&&)[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT&&, enum_class_UDT(&&)[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT&&, enum_class_UDT(*)[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT&&, enum_class_UDT(*)[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT&&, float);
BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT&&, bool);
BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT&&, int);
BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT&&, enum_UDT);
BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT&&, void);
BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT&&, std::nullptr_t);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT[2], enum_class_UDT);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT[2], enum_class_UDT&);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT[2], enum_class_UDT&&);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT[2], enum_class_UDT*);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT[2], enum_class_UDT[2]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT[2], enum_class_UDT[]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT[2], enum_class_UDT(&)[2]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT[2], enum_class_UDT(&)[]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT[2], enum_class_UDT(&&)[2]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT[2], enum_class_UDT(&&)[]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT[2], enum_class_UDT(*)[2]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT[2], enum_class_UDT(*)[]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT[2], float);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT[2], bool);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT[2], int);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT[2], enum_UDT);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT[2], void);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT[2], std::nullptr_t);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT[], enum_class_UDT);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT[], enum_class_UDT&);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT[], enum_class_UDT&&);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT[], enum_class_UDT*);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT[], enum_class_UDT[2]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT[], enum_class_UDT[]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT[], enum_class_UDT(&)[2]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT[], enum_class_UDT(&)[]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT[], enum_class_UDT(&&)[2]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT[], enum_class_UDT(&&)[]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT[], enum_class_UDT(*)[2]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT[], enum_class_UDT(*)[]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT[], float);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT[], bool);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT[], int);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT[], enum_UDT);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT[], void);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT[], std::nullptr_t);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(&)[2], enum_class_UDT);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(&)[2], enum_class_UDT&);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(&)[2], enum_class_UDT&&);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(&)[2], enum_class_UDT*);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(&)[2], enum_class_UDT[2]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(&)[2], enum_class_UDT[]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(&)[2], enum_class_UDT(&)[2]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(&)[2], enum_class_UDT(&)[]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(&)[2], enum_class_UDT(&&)[2]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(&)[2], enum_class_UDT(&&)[]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(&)[2], enum_class_UDT(*)[2]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(&)[2], enum_class_UDT(*)[]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(&)[2], float);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(&)[2], bool);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(&)[2], int);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(&)[2], enum_UDT);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(&)[2], void);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(&)[2], std::nullptr_t);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(&)[], enum_class_UDT);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(&)[], enum_class_UDT&);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(&)[], enum_class_UDT&&);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(&)[], enum_class_UDT*);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(&)[], enum_class_UDT[2]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(&)[], enum_class_UDT[]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(&)[], enum_class_UDT(&)[2]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(&)[], enum_class_UDT(&)[]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(&)[], enum_class_UDT(&&)[2]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(&)[], enum_class_UDT(&&)[]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(&)[], enum_class_UDT(*)[2]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(&)[], enum_class_UDT(*)[]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(&)[], float);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(&)[], bool);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(&)[], int);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(&)[], enum_UDT);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(&)[], void);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(&)[], std::nullptr_t);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(&&)[2], enum_class_UDT);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(&&)[2], enum_class_UDT&);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(&&)[2], enum_class_UDT&&);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(&&)[2], enum_class_UDT*);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(&&)[2], enum_class_UDT[2]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(&&)[2], enum_class_UDT[]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(&&)[2], enum_class_UDT(&)[2]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(&&)[2], enum_class_UDT(&)[]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(&&)[2], enum_class_UDT(&&)[2]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(&&)[2], enum_class_UDT(&&)[]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(&&)[2], enum_class_UDT(*)[2]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(&&)[2], enum_class_UDT(*)[]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(&&)[2], float);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(&&)[2], bool);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(&&)[2], int);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(&&)[2], enum_UDT);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(&&)[2], void);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(&&)[2], std::nullptr_t);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(&&)[], enum_class_UDT);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(&&)[], enum_class_UDT&);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(&&)[], enum_class_UDT&&);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(&&)[], enum_class_UDT*);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(&&)[], enum_class_UDT[2]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(&&)[], enum_class_UDT[]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(&&)[], enum_class_UDT(&)[2]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(&&)[], enum_class_UDT(&)[]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(&&)[], enum_class_UDT(&&)[2]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(&&)[], enum_class_UDT(&&)[]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(&&)[], enum_class_UDT(*)[2]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(&&)[], enum_class_UDT(*)[]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(&&)[], float);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(&&)[], bool);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(&&)[], enum_class_UDT);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(&&)[], enum_UDT);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(&&)[], void);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(&&)[], std::nullptr_t);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(*)[2], enum_class_UDT);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(*)[2], enum_class_UDT&);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(*)[2], enum_class_UDT&&);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(*)[2], enum_class_UDT*);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(*)[2], enum_class_UDT[2]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(*)[2], enum_class_UDT[]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(*)[2], enum_class_UDT(&)[2]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(*)[2], enum_class_UDT(&)[]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(*)[2], enum_class_UDT(&&)[2]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(*)[2], enum_class_UDT(&&)[]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(*)[2], enum_class_UDT(*)[2]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(*)[2], enum_class_UDT(*)[]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(*)[2], float);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(*)[2], bool);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(*)[2], int);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(*)[2], enum_UDT);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(*)[2], void);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(*)[2], std::nullptr_t);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(*)[], enum_class_UDT);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(*)[], enum_class_UDT&);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(*)[], enum_class_UDT&&);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(*)[], enum_class_UDT*);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(*)[], enum_class_UDT[2]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(*)[], enum_class_UDT[]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(*)[], enum_class_UDT(&)[2]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(*)[], enum_class_UDT(&)[]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(*)[], enum_class_UDT(&&)[2]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(*)[], enum_class_UDT(&&)[]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(*)[], enum_class_UDT(*)[2]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(*)[], enum_class_UDT(*)[]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(*)[], float);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(*)[], bool);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(*)[], int);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(*)[], enum_UDT);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(*)[], void);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT(*)[], std::nullptr_t);
BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT*, enum_class_UDT);
BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT*, enum_class_UDT&);
BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT*, enum_class_UDT&&);
BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT*, enum_class_UDT*);
BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT*, enum_class_UDT[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT*, enum_class_UDT[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT*, enum_class_UDT(&)[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT*, enum_class_UDT(&)[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT*, enum_class_UDT(&&)[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT*, enum_class_UDT(&&)[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT*, enum_class_UDT(*)[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT*, enum_class_UDT(*)[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT*, float*);
BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT*, bool*);
BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT*, int*);
BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT*, enum_UDT*);
BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT*, void);
BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT*, void*);
BKSGE_IS_ASSIGNABLE_TEST  (false, enum_class_UDT*, std::nullptr_t);
BKSGE_IS_ASSIGNABLE_TEST    (false, enum_class_UDT*&, enum_class_UDT);
BKSGE_IS_ASSIGNABLE_TEST    (false, enum_class_UDT*&, enum_class_UDT&);
BKSGE_IS_ASSIGNABLE_TEST    (false, enum_class_UDT*&, enum_class_UDT&&);
BKSGE_IS_ASSIGNABLE_TEST_PTR(true,  enum_class_UDT*&, enum_class_UDT*);
BKSGE_IS_ASSIGNABLE_TEST_PTR(true,  enum_class_UDT*&, enum_class_UDT[2]);			//
BKSGE_IS_ASSIGNABLE_TEST_PTR(true,  enum_class_UDT*&, enum_class_UDT[]);			//
BKSGE_IS_ASSIGNABLE_TEST_PTR(true,  enum_class_UDT*&, enum_class_UDT(&)[2]);		//
BKSGE_IS_ASSIGNABLE_TEST_PTR(true,  enum_class_UDT*&, enum_class_UDT(&)[]);			//
BKSGE_IS_ASSIGNABLE_TEST_PTR(true,  enum_class_UDT*&, enum_class_UDT(&&)[2]);		//
BKSGE_IS_ASSIGNABLE_TEST_PTR(true,  enum_class_UDT*&, enum_class_UDT(&&)[]);		//
BKSGE_IS_ASSIGNABLE_TEST    (false, enum_class_UDT*&, enum_class_UDT(*)[2]);
BKSGE_IS_ASSIGNABLE_TEST    (false, enum_class_UDT*&, enum_class_UDT(*)[]);
BKSGE_IS_ASSIGNABLE_TEST    (false, enum_class_UDT*&, float*);
BKSGE_IS_ASSIGNABLE_TEST    (false, enum_class_UDT*&, bool*);
BKSGE_IS_ASSIGNABLE_TEST    (false, enum_class_UDT*&, int*);
BKSGE_IS_ASSIGNABLE_TEST    (false, enum_class_UDT*&, enum_UDT*);
BKSGE_IS_ASSIGNABLE_TEST    (false, enum_class_UDT*&, void);
BKSGE_IS_ASSIGNABLE_TEST    (false, enum_class_UDT*&, void*);
BKSGE_IS_ASSIGNABLE_TEST_0  (true,  enum_class_UDT*&, std::nullptr_t);

BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT, enum_UDT);
BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT, enum_UDT&);
BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT, enum_UDT&&);
BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT, enum_UDT*);
BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT, enum_UDT[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT, enum_UDT[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT, enum_UDT(&)[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT, enum_UDT(&)[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT, enum_UDT(&&)[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT, enum_UDT(&&)[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT, enum_UDT(*)[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT, enum_UDT(*)[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT, float);
BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT, bool);
BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT, int);
BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT, enum_class_UDT);
BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT, void);
BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT, std::nullptr_t);
BKSGE_IS_ASSIGNABLE_TEST_2(true,  enum_UDT&, enum_UDT);
BKSGE_IS_ASSIGNABLE_TEST_2(true,  enum_UDT&, enum_UDT&);
BKSGE_IS_ASSIGNABLE_TEST_2(true,  enum_UDT&, enum_UDT&&);
BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT&, enum_UDT*);
BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT&, enum_UDT[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT&, enum_UDT[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT&, enum_UDT(&)[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT&, enum_UDT(&)[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT&, enum_UDT(&&)[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT&, enum_UDT(&&)[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT&, enum_UDT(*)[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT&, enum_UDT(*)[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT&, float);
BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT&, bool);
BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT&, int);
BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT&, enum_class_UDT);
BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT&, void);
BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT&, std::nullptr_t);
BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT&&, enum_UDT);
BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT&&, enum_UDT&);
BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT&&, enum_UDT&&);
BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT&&, enum_UDT*);
BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT&&, enum_UDT[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT&&, enum_UDT[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT&&, enum_UDT(&)[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT&&, enum_UDT(&)[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT&&, enum_UDT(&&)[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT&&, enum_UDT(&&)[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT&&, enum_UDT(*)[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT&&, enum_UDT(*)[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT&&, float);
BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT&&, bool);
BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT&&, int);
BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT&&, enum_class_UDT);
BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT&&, void);
BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT&&, std::nullptr_t);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT[2], enum_UDT);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT[2], enum_UDT&);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT[2], enum_UDT&&);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT[2], enum_UDT*);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT[2], enum_UDT[2]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT[2], enum_UDT[]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT[2], enum_UDT(&)[2]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT[2], enum_UDT(&)[]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT[2], enum_UDT(&&)[2]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT[2], enum_UDT(&&)[]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT[2], enum_UDT(*)[2]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT[2], enum_UDT(*)[]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT[2], float);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT[2], bool);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT[2], int);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT[2], enum_class_UDT);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT[2], void);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT[2], std::nullptr_t);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT[], enum_UDT);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT[], enum_UDT&);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT[], enum_UDT&&);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT[], enum_UDT*);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT[], enum_UDT[2]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT[], enum_UDT[]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT[], enum_UDT(&)[2]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT[], enum_UDT(&)[]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT[], enum_UDT(&&)[2]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT[], enum_UDT(&&)[]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT[], enum_UDT(*)[2]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT[], enum_UDT(*)[]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT[], float);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT[], bool);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT[], int);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT[], enum_class_UDT);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT[], void);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT[], std::nullptr_t);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT(&)[2], enum_UDT);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT(&)[2], enum_UDT&);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT(&)[2], enum_UDT&&);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT(&)[2], enum_UDT*);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT(&)[2], enum_UDT[2]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT(&)[2], enum_UDT[]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT(&)[2], enum_UDT(&)[2]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT(&)[2], enum_UDT(&)[]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT(&)[2], enum_UDT(&&)[2]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT(&)[2], enum_UDT(&&)[]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT(&)[2], enum_UDT(*)[2]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT(&)[2], enum_UDT(*)[]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT(&)[2], float);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT(&)[2], bool);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT(&)[2], int);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT(&)[2], enum_class_UDT);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT(&)[2], void);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT(&)[2], std::nullptr_t);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT(&)[], enum_UDT);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT(&)[], enum_UDT&);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT(&)[], enum_UDT&&);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT(&)[], enum_UDT*);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT(&)[], enum_UDT[2]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT(&)[], enum_UDT[]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT(&)[], enum_UDT(&)[2]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT(&)[], enum_UDT(&)[]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT(&)[], enum_UDT(&&)[2]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT(&)[], enum_UDT(&&)[]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT(&)[], enum_UDT(*)[2]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT(&)[], enum_UDT(*)[]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT(&)[], float);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT(&)[], bool);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT(&)[], int);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT(&)[], enum_class_UDT);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT(&)[], void);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT(&)[], std::nullptr_t);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT(&&)[2], enum_UDT);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT(&&)[2], enum_UDT&);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT(&&)[2], enum_UDT&&);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT(&&)[2], enum_UDT*);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT(&&)[2], enum_UDT[2]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT(&&)[2], enum_UDT[]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT(&&)[2], enum_UDT(&)[2]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT(&&)[2], enum_UDT(&)[]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT(&&)[2], enum_UDT(&&)[2]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT(&&)[2], enum_UDT(&&)[]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT(&&)[2], enum_UDT(*)[2]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT(&&)[2], enum_UDT(*)[]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT(&&)[2], float);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT(&&)[2], bool);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT(&&)[2], int);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT(&&)[2], enum_class_UDT);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT(&&)[2], void);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT(&&)[2], std::nullptr_t);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT(&&)[], enum_UDT);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT(&&)[], enum_UDT&);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT(&&)[], enum_UDT&&);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT(&&)[], enum_UDT*);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT(&&)[], enum_UDT[2]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT(&&)[], enum_UDT[]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT(&&)[], enum_UDT(&)[2]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT(&&)[], enum_UDT(&)[]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT(&&)[], enum_UDT(&&)[2]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT(&&)[], enum_UDT(&&)[]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT(&&)[], enum_UDT(*)[2]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT(&&)[], enum_UDT(*)[]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT(&&)[], float);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT(&&)[], bool);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT(&&)[], enum_class_UDT);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT(&&)[], void);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT(&&)[], std::nullptr_t);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT(*)[2], enum_UDT);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT(*)[2], enum_UDT&);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT(*)[2], enum_UDT&&);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT(*)[2], enum_UDT*);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT(*)[2], enum_UDT[2]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT(*)[2], enum_UDT[]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT(*)[2], enum_UDT(&)[2]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT(*)[2], enum_UDT(&)[]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT(*)[2], enum_UDT(&&)[2]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT(*)[2], enum_UDT(&&)[]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT(*)[2], enum_UDT(*)[2]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT(*)[2], enum_UDT(*)[]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT(*)[2], float);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT(*)[2], bool);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT(*)[2], int);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT(*)[2], enum_class_UDT);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT(*)[2], void);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT(*)[2], std::nullptr_t);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT(*)[], enum_UDT);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT(*)[], enum_UDT&);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT(*)[], enum_UDT&&);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT(*)[], enum_UDT*);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT(*)[], enum_UDT[2]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT(*)[], enum_UDT[]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT(*)[], enum_UDT(&)[2]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT(*)[], enum_UDT(&)[]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT(*)[], enum_UDT(&&)[2]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT(*)[], enum_UDT(&&)[]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT(*)[], enum_UDT(*)[2]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT(*)[], enum_UDT(*)[]);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT(*)[], float);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT(*)[], bool);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT(*)[], int);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT(*)[], enum_class_UDT);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT(*)[], void);
//	BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT(*)[], std::nullptr_t);
BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT*, enum_UDT);
BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT*, enum_UDT&);
BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT*, enum_UDT&&);
BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT*, enum_UDT*);
BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT*, enum_UDT[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT*, enum_UDT[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT*, enum_UDT(&)[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT*, enum_UDT(&)[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT*, enum_UDT(&&)[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT*, enum_UDT(&&)[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT*, enum_UDT(*)[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT*, enum_UDT(*)[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT*, float*);
BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT*, bool*);
BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT*, int*);
BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT*, enum_class_UDT*);
BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT*, void);
BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT*, void*);
BKSGE_IS_ASSIGNABLE_TEST  (false, enum_UDT*, std::nullptr_t);
BKSGE_IS_ASSIGNABLE_TEST    (false, enum_UDT*&, enum_UDT);
BKSGE_IS_ASSIGNABLE_TEST    (false, enum_UDT*&, enum_UDT&);
BKSGE_IS_ASSIGNABLE_TEST    (false, enum_UDT*&, enum_UDT&&);
BKSGE_IS_ASSIGNABLE_TEST_PTR(true,  enum_UDT*&, enum_UDT*);
BKSGE_IS_ASSIGNABLE_TEST_PTR(true,  enum_UDT*&, enum_UDT[2]);			//
BKSGE_IS_ASSIGNABLE_TEST_PTR(true,  enum_UDT*&, enum_UDT[]);			//
BKSGE_IS_ASSIGNABLE_TEST_PTR(true,  enum_UDT*&, enum_UDT(&)[2]);		//
BKSGE_IS_ASSIGNABLE_TEST_PTR(true,  enum_UDT*&, enum_UDT(&)[]);			//
BKSGE_IS_ASSIGNABLE_TEST_PTR(true,  enum_UDT*&, enum_UDT(&&)[2]);		//
BKSGE_IS_ASSIGNABLE_TEST_PTR(true,  enum_UDT*&, enum_UDT(&&)[]);		//
BKSGE_IS_ASSIGNABLE_TEST    (false, enum_UDT*&, enum_UDT(*)[2]);
BKSGE_IS_ASSIGNABLE_TEST    (false, enum_UDT*&, enum_UDT(*)[]);
BKSGE_IS_ASSIGNABLE_TEST    (false, enum_UDT*&, float*);
BKSGE_IS_ASSIGNABLE_TEST    (false, enum_UDT*&, bool*);
BKSGE_IS_ASSIGNABLE_TEST    (false, enum_UDT*&, int*);
BKSGE_IS_ASSIGNABLE_TEST    (false, enum_UDT*&, enum_class_UDT*);
BKSGE_IS_ASSIGNABLE_TEST    (false, enum_UDT*&, void);
BKSGE_IS_ASSIGNABLE_TEST    (false, enum_UDT*&, void*);
BKSGE_IS_ASSIGNABLE_TEST_0  (true,  enum_UDT*&, std::nullptr_t);

BKSGE_IS_ASSIGNABLE_TEST(false, void*, int);
BKSGE_IS_ASSIGNABLE_TEST(false, void*, int&);
BKSGE_IS_ASSIGNABLE_TEST(false, void*, int&&);
BKSGE_IS_ASSIGNABLE_TEST(false, void*, int*);
BKSGE_IS_ASSIGNABLE_TEST(false, void*, int[2]);
BKSGE_IS_ASSIGNABLE_TEST(false, void*, int[]);
BKSGE_IS_ASSIGNABLE_TEST(false, void*, int(&)[2]);
BKSGE_IS_ASSIGNABLE_TEST(false, void*, int(&)[]);
BKSGE_IS_ASSIGNABLE_TEST(false, void*, int(&&)[2]);
BKSGE_IS_ASSIGNABLE_TEST(false, void*, int(&&)[]);
BKSGE_IS_ASSIGNABLE_TEST(false, void*, int(*)[2]);
BKSGE_IS_ASSIGNABLE_TEST(false, void*, int(*)[]);
BKSGE_IS_ASSIGNABLE_TEST(false, void*, float*);
BKSGE_IS_ASSIGNABLE_TEST(false, void*, bool*);
BKSGE_IS_ASSIGNABLE_TEST(false, void*, enum_class_UDT*);
BKSGE_IS_ASSIGNABLE_TEST(false, void*, enum_UDT*);
BKSGE_IS_ASSIGNABLE_TEST(false, void*, void);
BKSGE_IS_ASSIGNABLE_TEST(false, void*, void*);
BKSGE_IS_ASSIGNABLE_TEST(false, void*, std::nullptr_t);
BKSGE_IS_ASSIGNABLE_TEST    (false, void*&, int);
BKSGE_IS_ASSIGNABLE_TEST    (false, void*&, int&);
BKSGE_IS_ASSIGNABLE_TEST    (false, void*&, int&&);
BKSGE_IS_ASSIGNABLE_TEST_PTR(true,  void*&, int*);
BKSGE_IS_ASSIGNABLE_TEST_PTR(true,  void*&, int[2]);		//
BKSGE_IS_ASSIGNABLE_TEST_PTR(true,  void*&, int[]);			//
BKSGE_IS_ASSIGNABLE_TEST_PTR(true,  void*&, int(&)[2]);		//
BKSGE_IS_ASSIGNABLE_TEST_PTR(true,  void*&, int(&)[]);		//
BKSGE_IS_ASSIGNABLE_TEST_PTR(true,  void*&, int(&&)[2]);	//
BKSGE_IS_ASSIGNABLE_TEST_PTR(true,  void*&, int(&&)[]);		//
BKSGE_IS_ASSIGNABLE_TEST_PTR(true,  void*&, int(*)[2]);
BKSGE_IS_ASSIGNABLE_TEST_PTR(true,  void*&, int(*)[]);
BKSGE_IS_ASSIGNABLE_TEST_PTR(true,  void*&, float*);
BKSGE_IS_ASSIGNABLE_TEST_PTR(true,  void*&, bool*);
BKSGE_IS_ASSIGNABLE_TEST_PTR(true,  void*&, enum_class_UDT*);
BKSGE_IS_ASSIGNABLE_TEST_PTR(true,  void*&, enum_UDT*);
BKSGE_IS_ASSIGNABLE_TEST_PTR(false, void*&, void);
BKSGE_IS_ASSIGNABLE_TEST_PTR(true,  void*&, void*);
BKSGE_IS_ASSIGNABLE_TEST_0  (true,  void*&, std::nullptr_t);

BKSGE_IS_ASSIGNABLE_TEST(false, void, void);
BKSGE_IS_ASSIGNABLE_TEST(false, void, int);
BKSGE_IS_ASSIGNABLE_TEST(false, void, void*);
BKSGE_IS_ASSIGNABLE_TEST(false, void, std::nullptr_t);

BKSGE_IS_ASSIGNABLE_TEST  (false, std::nullptr_t, std::nullptr_t);
BKSGE_IS_ASSIGNABLE_TEST  (false, std::nullptr_t, std::nullptr_t&);
BKSGE_IS_ASSIGNABLE_TEST  (false, std::nullptr_t, std::nullptr_t&&);
BKSGE_IS_ASSIGNABLE_TEST  (false, std::nullptr_t, std::nullptr_t*);
BKSGE_IS_ASSIGNABLE_TEST  (false, std::nullptr_t, std::nullptr_t[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, std::nullptr_t, std::nullptr_t[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, std::nullptr_t, std::nullptr_t(&)[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, std::nullptr_t, std::nullptr_t(&)[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, std::nullptr_t, std::nullptr_t(&&)[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, std::nullptr_t, std::nullptr_t(&&)[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, std::nullptr_t, std::nullptr_t(*)[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, std::nullptr_t, std::nullptr_t(*)[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, std::nullptr_t, float*);
BKSGE_IS_ASSIGNABLE_TEST  (false, std::nullptr_t, bool*);
BKSGE_IS_ASSIGNABLE_TEST  (false, std::nullptr_t, enum_class_UDT*);
BKSGE_IS_ASSIGNABLE_TEST  (false, std::nullptr_t, enum_UDT*);
BKSGE_IS_ASSIGNABLE_TEST  (false, std::nullptr_t, void);
BKSGE_IS_ASSIGNABLE_TEST  (false, std::nullptr_t, void*);
BKSGE_IS_ASSIGNABLE_TEST_2(true,  std::nullptr_t&, std::nullptr_t);
BKSGE_IS_ASSIGNABLE_TEST_2(true,  std::nullptr_t&, std::nullptr_t&);
BKSGE_IS_ASSIGNABLE_TEST_2(true,  std::nullptr_t&, std::nullptr_t&&);
BKSGE_IS_ASSIGNABLE_TEST  (false, std::nullptr_t&, std::nullptr_t*);
BKSGE_IS_ASSIGNABLE_TEST  (false, std::nullptr_t&, std::nullptr_t[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, std::nullptr_t&, std::nullptr_t[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, std::nullptr_t&, std::nullptr_t(&)[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, std::nullptr_t&, std::nullptr_t(&)[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, std::nullptr_t&, std::nullptr_t(&&)[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, std::nullptr_t&, std::nullptr_t(&&)[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, std::nullptr_t&, std::nullptr_t(*)[2]);
BKSGE_IS_ASSIGNABLE_TEST  (false, std::nullptr_t&, std::nullptr_t(*)[]);
BKSGE_IS_ASSIGNABLE_TEST  (false, std::nullptr_t&, float*);
BKSGE_IS_ASSIGNABLE_TEST  (false, std::nullptr_t&, bool*);
BKSGE_IS_ASSIGNABLE_TEST  (false, std::nullptr_t&, enum_class_UDT*);
BKSGE_IS_ASSIGNABLE_TEST  (false, std::nullptr_t&, enum_UDT*);
BKSGE_IS_ASSIGNABLE_TEST  (false, std::nullptr_t&, void);
BKSGE_IS_ASSIGNABLE_TEST  (false, std::nullptr_t&, void*);

}	// namespace is_assignable_test

}	// namespace bksge_type_traits_test

#undef BKSGE_IS_ASSIGNABLE_TEST
#undef BKSGE_IS_ASSIGNABLE_TEST_0
#undef BKSGE_IS_ASSIGNABLE_TEST_1
#undef BKSGE_IS_ASSIGNABLE_TEST_2
#undef BKSGE_IS_ASSIGNABLE_TEST_3
#undef BKSGE_IS_ASSIGNABLE_TEST_PTR
