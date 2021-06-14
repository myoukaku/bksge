/**
 *	@file	unit_test_fnd_type_traits_is_nothrow_assignable.cpp
 *
 *	@brief	is_nothrow_assignable のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/type_traits/is_nothrow_assignable.hpp>
#include <bksge/fnd/config.hpp>
#include <gtest/gtest.h>
#include <string>
#include "type_traits_test_utility.hpp"

#if defined(BKSGE_HAS_CXX14_VARIABLE_TEMPLATES)

#define BKSGE_IS_NOTHROW_ASSIGNABLE_TEST(b, T, U)	\
	static_assert(bksge::is_nothrow_assignable_v<T, U>      == b, #T ", " #U);	\
	static_assert(bksge::is_nothrow_assignable<T, U>::value == b, #T ", " #U);	\
	static_assert(bksge::is_nothrow_assignable<T, U>()      == b, #T ", " #U)

#else

#define BKSGE_IS_NOTHROW_ASSIGNABLE_TEST(b, T, U)	\
	static_assert(bksge::is_nothrow_assignable<T, U>::value == b, #T ", " #U);	\
	static_assert(bksge::is_nothrow_assignable<T, U>()      == b, #T ", " #U)

#endif

namespace bksge_type_traits_test
{

namespace is_nothrow_assignable_test
{

struct S1
{
	S1& operator=(const S1&);
	S1& operator=(const int&) BKSGE_NOEXCEPT_OR_NOTHROW;
};

struct S2
{
	S2& operator=(const S2&) BKSGE_NOEXCEPT_OR_NOTHROW;
	S2& operator=(const std::string&) BKSGE_NOEXCEPT_OR_NOTHROW;
};

BKSGE_IS_NOTHROW_ASSIGNABLE_TEST(false, int,		int);
BKSGE_IS_NOTHROW_ASSIGNABLE_TEST(false, int&&,		int);
BKSGE_IS_NOTHROW_ASSIGNABLE_TEST(false, int&&,		int&&);
BKSGE_IS_NOTHROW_ASSIGNABLE_TEST(false, int*,		int);
BKSGE_IS_NOTHROW_ASSIGNABLE_TEST(false, int*,		int*);
BKSGE_IS_NOTHROW_ASSIGNABLE_TEST(false, int[2],		int);
BKSGE_IS_NOTHROW_ASSIGNABLE_TEST(false, int[2],		int[2]);
BKSGE_IS_NOTHROW_ASSIGNABLE_TEST(false, int[],		int);
BKSGE_IS_NOTHROW_ASSIGNABLE_TEST(false, int[],		int[]);
BKSGE_IS_NOTHROW_ASSIGNABLE_TEST(false, int(&)[2],	int);
BKSGE_IS_NOTHROW_ASSIGNABLE_TEST(false, int(&)[2],	int(&)[2]);
BKSGE_IS_NOTHROW_ASSIGNABLE_TEST(false, int(&)[],	int);
BKSGE_IS_NOTHROW_ASSIGNABLE_TEST(false, int(&)[],	int(&)[]);
BKSGE_IS_NOTHROW_ASSIGNABLE_TEST(false, int(&&)[2],	int);
BKSGE_IS_NOTHROW_ASSIGNABLE_TEST(false, int(&&)[2],	int(&&)[2]);
BKSGE_IS_NOTHROW_ASSIGNABLE_TEST(false, int(&&)[],	int);
BKSGE_IS_NOTHROW_ASSIGNABLE_TEST(false, int(&&)[],	int(&&)[]);
BKSGE_IS_NOTHROW_ASSIGNABLE_TEST(true,                 int&,		int);
BKSGE_IS_NOTHROW_ASSIGNABLE_TEST(false, const          int&,		int);
BKSGE_IS_NOTHROW_ASSIGNABLE_TEST(true,        volatile int&,		int);
BKSGE_IS_NOTHROW_ASSIGNABLE_TEST(false, const volatile int&,		int);
BKSGE_IS_NOTHROW_ASSIGNABLE_TEST(true,                 int&,		int&);
BKSGE_IS_NOTHROW_ASSIGNABLE_TEST(false, const          int&,		int&);
BKSGE_IS_NOTHROW_ASSIGNABLE_TEST(true,        volatile int&,		int&);
BKSGE_IS_NOTHROW_ASSIGNABLE_TEST(false, const volatile int&,		int&);
BKSGE_IS_NOTHROW_ASSIGNABLE_TEST(true,                 int&,		int&&);
BKSGE_IS_NOTHROW_ASSIGNABLE_TEST(false, const          int&,		int&&);
BKSGE_IS_NOTHROW_ASSIGNABLE_TEST(true,        volatile int&,		int&&);
BKSGE_IS_NOTHROW_ASSIGNABLE_TEST(false, const volatile int&,		int&&);
BKSGE_IS_NOTHROW_ASSIGNABLE_TEST(false, int&, int*);
BKSGE_IS_NOTHROW_ASSIGNABLE_TEST(false, int&, int[2]);
BKSGE_IS_NOTHROW_ASSIGNABLE_TEST(true,  int&, enum_UDT);
BKSGE_IS_NOTHROW_ASSIGNABLE_TEST(false, int&, enum_class_UDT);

BKSGE_IS_NOTHROW_ASSIGNABLE_TEST(false,                void,                void);
BKSGE_IS_NOTHROW_ASSIGNABLE_TEST(false, const          void, const          void);
BKSGE_IS_NOTHROW_ASSIGNABLE_TEST(false,       volatile void,       volatile void);
BKSGE_IS_NOTHROW_ASSIGNABLE_TEST(false, const volatile void, const volatile void);

BKSGE_IS_NOTHROW_ASSIGNABLE_TEST(false, S1, S1);
BKSGE_IS_NOTHROW_ASSIGNABLE_TEST(false, S1&, S1);
BKSGE_IS_NOTHROW_ASSIGNABLE_TEST(false, S1&&, S1);
BKSGE_IS_NOTHROW_ASSIGNABLE_TEST(true,                 S1,                int);
BKSGE_IS_NOTHROW_ASSIGNABLE_TEST(false, const          S1,                int);
BKSGE_IS_NOTHROW_ASSIGNABLE_TEST(false,       volatile S1,                int);
BKSGE_IS_NOTHROW_ASSIGNABLE_TEST(false, const volatile S1,                int);
BKSGE_IS_NOTHROW_ASSIGNABLE_TEST(true,                 S1, const          int);
BKSGE_IS_NOTHROW_ASSIGNABLE_TEST(false, const          S1, const          int);
BKSGE_IS_NOTHROW_ASSIGNABLE_TEST(false,       volatile S1, const          int);
BKSGE_IS_NOTHROW_ASSIGNABLE_TEST(false, const volatile S1, const          int);
BKSGE_IS_NOTHROW_ASSIGNABLE_TEST(false,                S1,       volatile int);
BKSGE_IS_NOTHROW_ASSIGNABLE_TEST(false, const          S1,       volatile int);
BKSGE_IS_NOTHROW_ASSIGNABLE_TEST(false,       volatile S1,       volatile int);
BKSGE_IS_NOTHROW_ASSIGNABLE_TEST(false, const volatile S1,       volatile int);
BKSGE_IS_NOTHROW_ASSIGNABLE_TEST(false,                S1, const volatile int);
BKSGE_IS_NOTHROW_ASSIGNABLE_TEST(false, const          S1, const volatile int);
BKSGE_IS_NOTHROW_ASSIGNABLE_TEST(false,       volatile S1, const volatile int);
BKSGE_IS_NOTHROW_ASSIGNABLE_TEST(false, const volatile S1, const volatile int);
BKSGE_IS_NOTHROW_ASSIGNABLE_TEST(true,  S1&,	int);
BKSGE_IS_NOTHROW_ASSIGNABLE_TEST(true,  S1&&,	int);
BKSGE_IS_NOTHROW_ASSIGNABLE_TEST(false, S1&,	int[2]);
BKSGE_IS_NOTHROW_ASSIGNABLE_TEST(false, S1,	std::string);

BKSGE_IS_NOTHROW_ASSIGNABLE_TEST(true,  S2, S2);
BKSGE_IS_NOTHROW_ASSIGNABLE_TEST(false, S2, int);
BKSGE_IS_NOTHROW_ASSIGNABLE_TEST(true,  S2, std::string);

BKSGE_IS_NOTHROW_ASSIGNABLE_TEST(true,  trivial_except_construct,		trivial_except_construct);
BKSGE_IS_NOTHROW_ASSIGNABLE_TEST(true,  trivial_except_destroy,			trivial_except_destroy);
BKSGE_IS_NOTHROW_ASSIGNABLE_TEST(true,  trivial_except_copy_ctor,		trivial_except_copy_ctor);
BKSGE_IS_NOTHROW_ASSIGNABLE_TEST(false, trivial_except_copy_assign,		trivial_except_copy_assign);
BKSGE_IS_NOTHROW_ASSIGNABLE_TEST(false, trivial_except_move_ctor,		trivial_except_move_ctor);
BKSGE_IS_NOTHROW_ASSIGNABLE_TEST(false, trivial_except_move_assign,		trivial_except_move_assign);

BKSGE_IS_NOTHROW_ASSIGNABLE_TEST(false, nothrow_default_ctor_UDT,		nothrow_default_ctor_UDT);
BKSGE_IS_NOTHROW_ASSIGNABLE_TEST(false, nothrow_dtor_UDT,				nothrow_dtor_UDT);
BKSGE_IS_NOTHROW_ASSIGNABLE_TEST(false, nothrow_copy_ctor_UDT,			nothrow_copy_ctor_UDT);
BKSGE_IS_NOTHROW_ASSIGNABLE_TEST(false, nothrow_copy_assign_UDT,		nothrow_copy_assign_UDT);
BKSGE_IS_NOTHROW_ASSIGNABLE_TEST(true,  nothrow_copy_assign_UDT,		nothrow_copy_assign_UDT&);
BKSGE_IS_NOTHROW_ASSIGNABLE_TEST(false, nothrow_copy_assign_UDT,		nothrow_copy_assign_UDT&&);
BKSGE_IS_NOTHROW_ASSIGNABLE_TEST(false, nothrow_copy_assign_UDT&,		nothrow_copy_assign_UDT);
BKSGE_IS_NOTHROW_ASSIGNABLE_TEST(true,  nothrow_copy_assign_UDT&,		nothrow_copy_assign_UDT&);
BKSGE_IS_NOTHROW_ASSIGNABLE_TEST(false, nothrow_copy_assign_UDT&,		nothrow_copy_assign_UDT&&);
BKSGE_IS_NOTHROW_ASSIGNABLE_TEST(false, nothrow_copy_assign_UDT&&,		nothrow_copy_assign_UDT);
BKSGE_IS_NOTHROW_ASSIGNABLE_TEST(true,  nothrow_copy_assign_UDT&&,		nothrow_copy_assign_UDT&);
BKSGE_IS_NOTHROW_ASSIGNABLE_TEST(false, nothrow_copy_assign_UDT&&,		nothrow_copy_assign_UDT&&);
BKSGE_IS_NOTHROW_ASSIGNABLE_TEST(false, nothrow_move_ctor_UDT,			nothrow_move_ctor_UDT);
BKSGE_IS_NOTHROW_ASSIGNABLE_TEST(true,  nothrow_move_assign_UDT,		nothrow_move_assign_UDT);
BKSGE_IS_NOTHROW_ASSIGNABLE_TEST(false, nothrow_move_assign_UDT,		nothrow_move_assign_UDT&);
BKSGE_IS_NOTHROW_ASSIGNABLE_TEST(true,  nothrow_move_assign_UDT,		nothrow_move_assign_UDT&&);
BKSGE_IS_NOTHROW_ASSIGNABLE_TEST(true,  nothrow_move_assign_UDT&,		nothrow_move_assign_UDT);
BKSGE_IS_NOTHROW_ASSIGNABLE_TEST(false, nothrow_move_assign_UDT&,		nothrow_move_assign_UDT&);
BKSGE_IS_NOTHROW_ASSIGNABLE_TEST(true,  nothrow_move_assign_UDT&,		nothrow_move_assign_UDT&&);
BKSGE_IS_NOTHROW_ASSIGNABLE_TEST(true,  nothrow_move_assign_UDT&&,		nothrow_move_assign_UDT);
BKSGE_IS_NOTHROW_ASSIGNABLE_TEST(false, nothrow_move_assign_UDT&&,		nothrow_move_assign_UDT&);
BKSGE_IS_NOTHROW_ASSIGNABLE_TEST(true,  nothrow_move_assign_UDT&&,		nothrow_move_assign_UDT&&);

}	// namespace is_nothrow_assignable_test

}	// namespace bksge_type_traits_test

#undef BKSGE_IS_NOTHROW_ASSIGNABLE_TEST
