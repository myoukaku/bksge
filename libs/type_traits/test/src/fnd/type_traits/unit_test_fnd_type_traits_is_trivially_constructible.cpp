/**
 *	@file	unit_test_fnd_type_traits_is_trivially_constructible.cpp
 *
 *	@brief	is_trivially_constructible のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/type_traits/is_trivially_constructible.hpp>
#include <bksge/fnd/string/string.hpp>
#include <bksge/fnd/config.hpp>
#include <gtest/gtest.h>
#include "type_traits_test_utility.hpp"

#if defined(BKSGE_HAS_CXX14_VARIABLE_TEMPLATES)

#define BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(b, ...)	\
	static_assert(bksge::is_trivially_constructible_v<__VA_ARGS__>      == b, "");	\
	static_assert(bksge::is_trivially_constructible<__VA_ARGS__>::value == b, "");	\
	static_assert(bksge::is_trivially_constructible<__VA_ARGS__>()      == b, "")

#else

#define BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(b, ...)	\
	static_assert(bksge::is_trivially_constructible<__VA_ARGS__>::value == b, "");	\
	static_assert(bksge::is_trivially_constructible<__VA_ARGS__>()      == b, "")

#endif

namespace bksge_type_traits_test
{

namespace is_trivially_constructible_test
{

#if !(defined(BKSGE_GCC_VERSION) && (BKSGE_GCC_VERSION == 80100))	// gcc 8.1.0ではis_trivially_constructibleが正しくない

BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(true,  int);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(true,  int, int);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, int, int, int);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, int, bksge::string);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, int&, int);

BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, trivial_except_construct);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, trivial_except_destroy);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, trivial_except_copy_ctor);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(true,  trivial_except_copy_assign);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, trivial_except_move_ctor);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(true,  trivial_except_move_assign);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(true,  trivial_except_construct,		trivial_except_construct);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, trivial_except_destroy,		trivial_except_destroy);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, trivial_except_copy_ctor,		trivial_except_copy_ctor);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(true,  trivial_except_copy_assign,	trivial_except_copy_assign);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, trivial_except_move_ctor,		trivial_except_move_ctor);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, trivial_except_move_assign,	trivial_except_move_assign);
	
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(true,                 int);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(true,  const          int);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(true,        volatile int);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(true,  const volatile int);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(true,  int*);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, int&);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, int&&);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(true,  int[2]);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, int[]);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, int(&)[2]);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, int(&)[]);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, int(&&)[2]);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, int(&&)[]);

BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(true,  int,        int);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, int,        int*);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(true,  int,        int&);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(true,  int,        int&&);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, int,        int[2]);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, int,        int[]);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, int,        int(&)[2]);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, int,        int(&)[]);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, int,        int(&&)[2]);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, int,        int(&&)[]);

BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, int*,       int);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(true,                 int*,                int*);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(true,  const          int*,                int*);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(true,        volatile int*,                int*);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(true,  const volatile int*,                int*);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false,                int*, const          int*);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(true,  const          int*, const          int*);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false,       volatile int*, const          int*);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(true,  const volatile int*, const          int*);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false,                int*,       volatile int*);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, const          int*,       volatile int*);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(true,        volatile int*,       volatile int*);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(true,  const volatile int*,       volatile int*);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false,                int*, const volatile int*);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, const          int*, const volatile int*);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false,       volatile int*, const volatile int*);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(true,  const volatile int*, const volatile int*);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, int*,       int&);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, int*,       int&&);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(true,  int*,       int[2]);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(true,  int*,       int[]);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(true,  int*,       int(&)[2]);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(true,  int*,       int(&)[]);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(true,  int*,       int(&&)[2]);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(true,  int*,       int(&&)[]);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false,                int&, int);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(true,  const          int&, int);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false,       volatile int&, int);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, const volatile int&, int);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false,                int&, int*);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, const          int&, int*);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false,       volatile int&, int*);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, const volatile int&, int*);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(true,                 int&,                int&);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(true,  const          int&,                int&);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(true,        volatile int&,                int&);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(true,  const volatile int&,                int&);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false,                int&, const          int&);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(true,  const          int&, const          int&);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false,       volatile int&, const          int&);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(true,  const volatile int&, const          int&);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false,                int&,       volatile int&);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, const          int&,       volatile int&);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(true,        volatile int&,       volatile int&);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(true,  const volatile int&,       volatile int&);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false,                int&, const volatile int&);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, const          int&, const volatile int&);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false,       volatile int&, const volatile int&);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(true,  const volatile int&, const volatile int&);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false,                int&,                int&&);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(true,  const          int&,                int&&);	// const参照だけ特別
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false,       volatile int&,                int&&);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, const volatile int&,                int&&);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false,                int&, const          int&&);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(true,  const          int&, const          int&&);	// const参照だけ特別
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false,       volatile int&, const          int&&);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, const volatile int&, const          int&&);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false,                int&,       volatile int&&);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, const          int&,       volatile int&&);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false,       volatile int&,       volatile int&&);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, const volatile int&,       volatile int&&);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false,                int&, const volatile int&&);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, const          int&, const volatile int&&);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false,       volatile int&, const volatile int&&);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, const volatile int&, const volatile int&&);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, int&,       int[2]);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, int&,       int[]);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, int&,       int(&)[2]);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, int&,       int(&)[]);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, int&,       int(&&)[2]);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, int&,       int(&&)[]);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(true,  int&&,      int);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, int&&,      int*);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, int&&,      int&);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(true,  int&&,      int&&);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, int&&,      int[2]);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, int&&,      int[]);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, int&&,      int(&)[2]);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, int&&,      int(&)[]);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, int&&,      int(&&)[2]);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, int&&,      int(&&)[]);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, int[2],     int);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, int[2],     int*);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, int[2],     int&);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, int[2],     int&&);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, int[2],     int[2]);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, int[2],     int[]);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, int[2],     int(&)[2]);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, int[2],     int(&)[]);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, int[2],     int(&&)[2]);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, int[2],     int(&&)[]);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, int[],      int);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, int[],      int*);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, int[],      int&);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, int[],      int&&);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, int[],      int[2]);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, int[],      int[]);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, int[],      int(&)[2]);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, int[],      int(&)[]);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, int[],      int(&&)[2]);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, int[],      int(&&)[]);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, int(&)[2],  int);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, int(&)[2],  int*);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, int(&)[2],  int&);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, int(&)[2],  int&&);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, int(&)[2],  int[2]);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, int(&)[2],  int[]);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(true,  int(&)[2],  int(&)[2]);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, int(&)[2],  int(&)[]);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, int(&)[2],  int(&&)[2]);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, int(&)[2],  int(&&)[]);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, int(&)[],   int);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, int(&)[],   int*);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, int(&)[],   int&);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, int(&)[],   int&&);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, int(&)[],   int[2]);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, int(&)[],   int[]);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, int(&)[],   int(&)[2]);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(true,  int(&)[],   int(&)[]);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, int(&)[],   int(&&)[2]);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, int(&)[],   int(&&)[]);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, int(&&)[2], int);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, int(&&)[2], int*);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, int(&&)[2], int&);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, int(&&)[2], int&&);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(true,  int(&&)[2], int[2]);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, int(&&)[2], int[]);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, int(&&)[2], int(&)[2]);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, int(&&)[2], int(&)[]);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(true,  int(&&)[2], int(&&)[2]);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, int(&&)[2], int(&&)[]);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, int(&&)[],  int);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, int(&&)[],  int*);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, int(&&)[],  int&);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, int(&&)[],  int&&);
//	BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, int(&&)[],  int[2]);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(true,  int(&&)[],  int[]);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, int(&&)[],  int(&)[2]);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, int(&&)[],  int(&)[]);
//	BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, int(&&)[],  int(&&)[2]);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(true,  int(&&)[],  int(&&)[]);

BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, int, UDT);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, int, int, int);

BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false,                 UDT);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false,  const          UDT);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false,        volatile UDT);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false,  const volatile UDT);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(true,  UDT*);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, UDT&);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, UDT&&);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, UDT[2]);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, UDT[]);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, UDT(&)[2]);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, UDT(&)[]);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, UDT(&&)[2]);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, UDT(&&)[]);

BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(true,                 POD_UDT);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(true,  const          POD_UDT);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(true,        volatile POD_UDT);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(true,  const volatile POD_UDT);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(true,  POD_UDT*);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, POD_UDT&);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, POD_UDT&&);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(true,  POD_UDT[2]);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, POD_UDT[]);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, POD_UDT(&)[2]);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, POD_UDT(&)[]);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, POD_UDT(&&)[2]);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false, POD_UDT(&&)[]);

BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false,	foo0_t);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false,	foo1_t);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false,	foo2_t);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false,	foo3_t);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false,	foo4_t);

BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false,	UDT,		UDT);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(true,		POD_UDT,	POD_UDT);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false,	foo0_t,		foo0_t);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false,	foo1_t,		foo1_t);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false,	foo2_t,		foo2_t);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false,	foo3_t,		foo3_t);
BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST(false,	foo4_t,		foo4_t);

#endif

}	// namespace is_trivially_constructible_test

}	// namespace bksge_type_traits_test

#undef BKSGE_IS_TRIVIALLY_CONSTRUCTIBLE_TEST
