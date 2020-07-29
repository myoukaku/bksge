/**
 *	@file	unit_test_fnd_type_traits_is_trivially_assignable.cpp
 *
 *	@brief	is_trivially_assignable のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/type_traits/is_trivially_assignable.hpp>
#include <gtest/gtest.h>
#include "type_traits_test_utility.hpp"

#define BKSGE_IS_TRIVIALLY_ASSIGNABLE_TEST(b, T, U)	\
	static_assert(bksge::is_trivially_assignable<T, U>::value == b, #T ", " #U);	\
	static_assert(bksge::is_trivially_assignable<T, U>()      == b, #T ", " #U)

namespace bksge_type_traits_test
{

namespace is_trivially_assignable_test
{

struct S1
{
};

struct S2
{
	S2& operator=(const S2&);
};

BKSGE_IS_TRIVIALLY_ASSIGNABLE_TEST(false, int,			int);
BKSGE_IS_TRIVIALLY_ASSIGNABLE_TEST(false, int&&,		int);
BKSGE_IS_TRIVIALLY_ASSIGNABLE_TEST(false, int&&,		int&&);
BKSGE_IS_TRIVIALLY_ASSIGNABLE_TEST(false, int*,			int);
BKSGE_IS_TRIVIALLY_ASSIGNABLE_TEST(false, int*,			int*);
BKSGE_IS_TRIVIALLY_ASSIGNABLE_TEST(false, int[2],		int);
BKSGE_IS_TRIVIALLY_ASSIGNABLE_TEST(false, int[2],		int[2]);
BKSGE_IS_TRIVIALLY_ASSIGNABLE_TEST(false, int[],		int);
BKSGE_IS_TRIVIALLY_ASSIGNABLE_TEST(false, int[],		int[]);
BKSGE_IS_TRIVIALLY_ASSIGNABLE_TEST(false, int(&)[2],	int);
BKSGE_IS_TRIVIALLY_ASSIGNABLE_TEST(false, int(&)[2],	int(&)[2]);
BKSGE_IS_TRIVIALLY_ASSIGNABLE_TEST(false, int(&)[],	    int);
BKSGE_IS_TRIVIALLY_ASSIGNABLE_TEST(false, int(&)[],	    int(&)[]);
BKSGE_IS_TRIVIALLY_ASSIGNABLE_TEST(false, int(&&)[2],	int);
BKSGE_IS_TRIVIALLY_ASSIGNABLE_TEST(false, int(&&)[2],	int(&&)[2]);
BKSGE_IS_TRIVIALLY_ASSIGNABLE_TEST(false, int(&&)[],	int);
BKSGE_IS_TRIVIALLY_ASSIGNABLE_TEST(false, int(&&)[],	int(&&)[]);
BKSGE_IS_TRIVIALLY_ASSIGNABLE_TEST(true,                 int&,		int);
BKSGE_IS_TRIVIALLY_ASSIGNABLE_TEST(false, const          int&,		int);
BKSGE_IS_TRIVIALLY_ASSIGNABLE_TEST(true,        volatile int&,		int);
BKSGE_IS_TRIVIALLY_ASSIGNABLE_TEST(false, const volatile int&,		int);
BKSGE_IS_TRIVIALLY_ASSIGNABLE_TEST(true,                 int&,		int&);
BKSGE_IS_TRIVIALLY_ASSIGNABLE_TEST(false, const          int&,		int&);
BKSGE_IS_TRIVIALLY_ASSIGNABLE_TEST(true,        volatile int&,		int&);
BKSGE_IS_TRIVIALLY_ASSIGNABLE_TEST(false, const volatile int&,		int&);
BKSGE_IS_TRIVIALLY_ASSIGNABLE_TEST(true,                 int&,		int&&);
BKSGE_IS_TRIVIALLY_ASSIGNABLE_TEST(false, const          int&,		int&&);
BKSGE_IS_TRIVIALLY_ASSIGNABLE_TEST(true,        volatile int&,		int&&);
BKSGE_IS_TRIVIALLY_ASSIGNABLE_TEST(false, const volatile int&,		int&&);
BKSGE_IS_TRIVIALLY_ASSIGNABLE_TEST(false, int&, int*);
BKSGE_IS_TRIVIALLY_ASSIGNABLE_TEST(false, int&, int[2]);
BKSGE_IS_TRIVIALLY_ASSIGNABLE_TEST(true,  int&, enum_UDT);
BKSGE_IS_TRIVIALLY_ASSIGNABLE_TEST(false, int&, enum_class_UDT);

BKSGE_IS_TRIVIALLY_ASSIGNABLE_TEST(false,                void,                void);
BKSGE_IS_TRIVIALLY_ASSIGNABLE_TEST(false, const          void, const          void);
BKSGE_IS_TRIVIALLY_ASSIGNABLE_TEST(false,       volatile void,       volatile void);
BKSGE_IS_TRIVIALLY_ASSIGNABLE_TEST(false, const volatile void, const volatile void);

BKSGE_IS_TRIVIALLY_ASSIGNABLE_TEST(true,                 S1,                S1);
BKSGE_IS_TRIVIALLY_ASSIGNABLE_TEST(false, const          S1,                S1);
BKSGE_IS_TRIVIALLY_ASSIGNABLE_TEST(false,       volatile S1,                S1);
BKSGE_IS_TRIVIALLY_ASSIGNABLE_TEST(false, const volatile S1,                S1);
BKSGE_IS_TRIVIALLY_ASSIGNABLE_TEST(true,                 S1, const          S1);
BKSGE_IS_TRIVIALLY_ASSIGNABLE_TEST(false, const          S1, const          S1);
BKSGE_IS_TRIVIALLY_ASSIGNABLE_TEST(false,       volatile S1, const          S1);
BKSGE_IS_TRIVIALLY_ASSIGNABLE_TEST(false, const volatile S1, const          S1);
BKSGE_IS_TRIVIALLY_ASSIGNABLE_TEST(false,                S1,       volatile S1);
BKSGE_IS_TRIVIALLY_ASSIGNABLE_TEST(false, const          S1,       volatile S1);
BKSGE_IS_TRIVIALLY_ASSIGNABLE_TEST(false,       volatile S1,       volatile S1);
BKSGE_IS_TRIVIALLY_ASSIGNABLE_TEST(false, const volatile S1,       volatile S1);
BKSGE_IS_TRIVIALLY_ASSIGNABLE_TEST(false,                S1, const volatile S1);
BKSGE_IS_TRIVIALLY_ASSIGNABLE_TEST(false, const          S1, const volatile S1);
BKSGE_IS_TRIVIALLY_ASSIGNABLE_TEST(false,       volatile S1, const volatile S1);
BKSGE_IS_TRIVIALLY_ASSIGNABLE_TEST(false, const volatile S1, const volatile S1);
BKSGE_IS_TRIVIALLY_ASSIGNABLE_TEST(true,  S1&,  S1);
BKSGE_IS_TRIVIALLY_ASSIGNABLE_TEST(true,  S1&&, S1);
BKSGE_IS_TRIVIALLY_ASSIGNABLE_TEST(false, S1[2], S1[2]);
BKSGE_IS_TRIVIALLY_ASSIGNABLE_TEST(false, S1,   int);

BKSGE_IS_TRIVIALLY_ASSIGNABLE_TEST(false, S2,   S2);
BKSGE_IS_TRIVIALLY_ASSIGNABLE_TEST(false, S2&,  S2);
BKSGE_IS_TRIVIALLY_ASSIGNABLE_TEST(false, S2&&, S2);
BKSGE_IS_TRIVIALLY_ASSIGNABLE_TEST(false, S2,   int);

BKSGE_IS_TRIVIALLY_ASSIGNABLE_TEST(true,  trivial_except_construct,		trivial_except_construct);
BKSGE_IS_TRIVIALLY_ASSIGNABLE_TEST(true,  trivial_except_destroy,		trivial_except_destroy);
BKSGE_IS_TRIVIALLY_ASSIGNABLE_TEST(true,  trivial_except_copy_ctor,		trivial_except_copy_ctor);
BKSGE_IS_TRIVIALLY_ASSIGNABLE_TEST(false, trivial_except_copy_assign,	trivial_except_copy_assign);
BKSGE_IS_TRIVIALLY_ASSIGNABLE_TEST(false, trivial_except_move_ctor,		trivial_except_move_ctor);
BKSGE_IS_TRIVIALLY_ASSIGNABLE_TEST(false, trivial_except_move_assign,	trivial_except_move_assign);
BKSGE_IS_TRIVIALLY_ASSIGNABLE_TEST(false, trivial_except_move_assign,	trivial_except_move_assign&);
BKSGE_IS_TRIVIALLY_ASSIGNABLE_TEST(false, trivial_except_move_assign,	const trivial_except_move_assign);
BKSGE_IS_TRIVIALLY_ASSIGNABLE_TEST(false, trivial_except_move_assign,	const trivial_except_move_assign&);
BKSGE_IS_TRIVIALLY_ASSIGNABLE_TEST(false, trivial_except_move_assign,	const trivial_except_move_assign&&);
BKSGE_IS_TRIVIALLY_ASSIGNABLE_TEST(false, trivial_except_move_assign&,	trivial_except_move_assign&);
BKSGE_IS_TRIVIALLY_ASSIGNABLE_TEST(false, trivial_except_move_assign&,	const trivial_except_move_assign);
BKSGE_IS_TRIVIALLY_ASSIGNABLE_TEST(false, trivial_except_move_assign&,	const trivial_except_move_assign&);
BKSGE_IS_TRIVIALLY_ASSIGNABLE_TEST(false, trivial_except_move_assign&,	const trivial_except_move_assign&&);
BKSGE_IS_TRIVIALLY_ASSIGNABLE_TEST(false, trivial_except_move_assign&&,	trivial_except_move_assign&);
BKSGE_IS_TRIVIALLY_ASSIGNABLE_TEST(false, trivial_except_move_assign&&,	const trivial_except_move_assign);
BKSGE_IS_TRIVIALLY_ASSIGNABLE_TEST(false, trivial_except_move_assign&&,	const trivial_except_move_assign&);
BKSGE_IS_TRIVIALLY_ASSIGNABLE_TEST(false, trivial_except_move_assign&&,	const trivial_except_move_assign&&);

}	// namespace is_trivially_assignable_test

}	// namespace bksge_type_traits_test

#undef BKSGE_IS_TRIVIALLY_ASSIGNABLE_TEST
