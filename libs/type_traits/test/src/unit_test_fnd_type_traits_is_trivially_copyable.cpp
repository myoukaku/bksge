/**
 *	@file	unit_test_fnd_type_traits_is_trivially_copyable.cpp
 *
 *	@brief	is_trivially_copyable のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/type_traits/is_trivially_copyable.hpp>
#include <bksge/fnd/config.hpp>
#include <gtest/gtest.h>
#include "type_traits_test_utility.hpp"

#if defined(BKSGE_HAS_CXX14_VARIABLE_TEMPLATES)

#define BKSGE_IS_TRIVIALLY_COPYABLE_TEST(b, T)	\
	static_assert(bksge::is_trivially_copyable_v<T>      == b, #T " == " #b);	\
	static_assert(bksge::is_trivially_copyable<T>::value == b, #T " == " #b);	\
	static_assert(bksge::is_trivially_copyable<T>()      == b, #T " == " #b)

#else

#define BKSGE_IS_TRIVIALLY_COPYABLE_TEST(b, T)	\
	static_assert(bksge::is_trivially_copyable<T>::value == b, #T " == " #b);	\
	static_assert(bksge::is_trivially_copyable<T>()      == b, #T " == " #b)

#endif

BKSGE_IS_TRIVIALLY_COPYABLE_TEST(true,                 int);
BKSGE_IS_TRIVIALLY_COPYABLE_TEST(true,  const          int);
BKSGE_IS_TRIVIALLY_COPYABLE_TEST(false,       volatile int);
BKSGE_IS_TRIVIALLY_COPYABLE_TEST(false, const volatile int);
BKSGE_IS_TRIVIALLY_COPYABLE_TEST(true,                 int*);
BKSGE_IS_TRIVIALLY_COPYABLE_TEST(true,  const          int*);
BKSGE_IS_TRIVIALLY_COPYABLE_TEST(true,        volatile int*);
BKSGE_IS_TRIVIALLY_COPYABLE_TEST(true,  const volatile int*);
BKSGE_IS_TRIVIALLY_COPYABLE_TEST(true,  int* const         );
BKSGE_IS_TRIVIALLY_COPYABLE_TEST(false, int*       volatile);
BKSGE_IS_TRIVIALLY_COPYABLE_TEST(false, int* const volatile);
BKSGE_IS_TRIVIALLY_COPYABLE_TEST(false, int&);
BKSGE_IS_TRIVIALLY_COPYABLE_TEST(false, int&&);
BKSGE_IS_TRIVIALLY_COPYABLE_TEST(true,                 int[2]);
BKSGE_IS_TRIVIALLY_COPYABLE_TEST(true,  const          int[2]);
BKSGE_IS_TRIVIALLY_COPYABLE_TEST(false,       volatile int[2]);
BKSGE_IS_TRIVIALLY_COPYABLE_TEST(false, const volatile int[2]);
BKSGE_IS_TRIVIALLY_COPYABLE_TEST(true,                 int[]);
BKSGE_IS_TRIVIALLY_COPYABLE_TEST(true,  const          int[]);
BKSGE_IS_TRIVIALLY_COPYABLE_TEST(false,       volatile int[]);
BKSGE_IS_TRIVIALLY_COPYABLE_TEST(false, const volatile int[]);
BKSGE_IS_TRIVIALLY_COPYABLE_TEST(false, int(&)[2]);
BKSGE_IS_TRIVIALLY_COPYABLE_TEST(false, int(&)[]);
BKSGE_IS_TRIVIALLY_COPYABLE_TEST(false, int(&&)[2]);
BKSGE_IS_TRIVIALLY_COPYABLE_TEST(false, int(&&)[]);

BKSGE_IS_TRIVIALLY_COPYABLE_TEST(false,                void);
BKSGE_IS_TRIVIALLY_COPYABLE_TEST(false, const          void);
BKSGE_IS_TRIVIALLY_COPYABLE_TEST(false,       volatile void);
BKSGE_IS_TRIVIALLY_COPYABLE_TEST(false, const volatile void);

BKSGE_IS_TRIVIALLY_COPYABLE_TEST(false,                UDT);
BKSGE_IS_TRIVIALLY_COPYABLE_TEST(false, const          UDT);
BKSGE_IS_TRIVIALLY_COPYABLE_TEST(false,       volatile UDT);
BKSGE_IS_TRIVIALLY_COPYABLE_TEST(false, const volatile UDT);
BKSGE_IS_TRIVIALLY_COPYABLE_TEST(true,                 UDT*);
BKSGE_IS_TRIVIALLY_COPYABLE_TEST(true,  const          UDT*);
BKSGE_IS_TRIVIALLY_COPYABLE_TEST(true,        volatile UDT*);
BKSGE_IS_TRIVIALLY_COPYABLE_TEST(true,  const volatile UDT*);
BKSGE_IS_TRIVIALLY_COPYABLE_TEST(false,                UDT&);
BKSGE_IS_TRIVIALLY_COPYABLE_TEST(false,                UDT&&);
BKSGE_IS_TRIVIALLY_COPYABLE_TEST(false,                UDT[2]);
BKSGE_IS_TRIVIALLY_COPYABLE_TEST(false,                UDT[]);
BKSGE_IS_TRIVIALLY_COPYABLE_TEST(true,                 POD_UDT);
BKSGE_IS_TRIVIALLY_COPYABLE_TEST(true,  const          POD_UDT);
BKSGE_IS_TRIVIALLY_COPYABLE_TEST(false,       volatile POD_UDT);
BKSGE_IS_TRIVIALLY_COPYABLE_TEST(false, const volatile POD_UDT);
BKSGE_IS_TRIVIALLY_COPYABLE_TEST(true,                 POD_UDT*);
BKSGE_IS_TRIVIALLY_COPYABLE_TEST(false,                POD_UDT&);
BKSGE_IS_TRIVIALLY_COPYABLE_TEST(false,                POD_UDT&&);
BKSGE_IS_TRIVIALLY_COPYABLE_TEST(true,                 POD_UDT[2]);
BKSGE_IS_TRIVIALLY_COPYABLE_TEST(true,                 POD_UDT[]);

BKSGE_IS_TRIVIALLY_COPYABLE_TEST(true, f1);
BKSGE_IS_TRIVIALLY_COPYABLE_TEST(true, f2);
BKSGE_IS_TRIVIALLY_COPYABLE_TEST(true, f3);
BKSGE_IS_TRIVIALLY_COPYABLE_TEST(true, mf1);
BKSGE_IS_TRIVIALLY_COPYABLE_TEST(true, mf2);
BKSGE_IS_TRIVIALLY_COPYABLE_TEST(true, mf3);
BKSGE_IS_TRIVIALLY_COPYABLE_TEST(true, mf4);
BKSGE_IS_TRIVIALLY_COPYABLE_TEST(true, mp);
BKSGE_IS_TRIVIALLY_COPYABLE_TEST(true, cmf);
BKSGE_IS_TRIVIALLY_COPYABLE_TEST(false, foo0_t);
BKSGE_IS_TRIVIALLY_COPYABLE_TEST(false, foo1_t);
BKSGE_IS_TRIVIALLY_COPYABLE_TEST(false, foo2_t);
BKSGE_IS_TRIVIALLY_COPYABLE_TEST(false, foo3_t);
BKSGE_IS_TRIVIALLY_COPYABLE_TEST(false, foo4_t);

BKSGE_IS_TRIVIALLY_COPYABLE_TEST(true,	trivial_except_construct);
BKSGE_IS_TRIVIALLY_COPYABLE_TEST(false, trivial_except_destroy);
BKSGE_IS_TRIVIALLY_COPYABLE_TEST(false, trivial_except_copy_ctor);
BKSGE_IS_TRIVIALLY_COPYABLE_TEST(false, trivial_except_copy_assign);
BKSGE_IS_TRIVIALLY_COPYABLE_TEST(false,	trivial_except_move_ctor);
BKSGE_IS_TRIVIALLY_COPYABLE_TEST(false,	trivial_except_move_assign);

#undef BKSGE_IS_TRIVIALLY_COPYABLE_TEST
