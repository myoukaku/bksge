/**
 *	@file	unit_test_fnd_type_traits_is_nothrow_constructible.cpp
 *
 *	@brief	is_nothrow_constructible のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/type_traits/is_nothrow_constructible.hpp>
#include <gtest/gtest.h>
#include <string>
#include "type_traits_test_utility.hpp"

#define BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(b, ...)	\
	static_assert(bksge::is_nothrow_constructible<__VA_ARGS__>::value == b, "");	\
	static_assert(bksge::is_nothrow_constructible<__VA_ARGS__>()      == b, "")

namespace bksge_type_traits_test
{

namespace is_nothrow_constructible_test
{

struct S1
{
	S1() BKSGE_NOEXCEPT_OR_NOTHROW;
	S1(const S1&);
	S1(S1&&) BKSGE_NOEXCEPT_OR_NOTHROW;
	S1(int) BKSGE_NOEXCEPT_OR_NOTHROW;
	S1(int, float) BKSGE_NOEXCEPT_OR_NOTHROW;
	S1(int, UDT, std::string);
	S1(int, int, int) BKSGE_NOEXCEPT_OR_NOTHROW;
};

struct S2
{
	S2(const S2&) BKSGE_NOEXCEPT_OR_NOTHROW;
	S2(S2&&);
	~S2() BKSGE_NOEXCEPT_OR_NOTHROW;
	S2(UDT);
};

BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(true,  int);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(true,  int, int);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, int, int, int);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, int, std::string);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, int&, int);

BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, trivial_except_construct);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(true,  trivial_except_destroy);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, trivial_except_copy_ctor);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(true,  trivial_except_copy_assign);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, trivial_except_move_ctor);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(true,  trivial_except_move_assign);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(true,  trivial_except_construct,		trivial_except_construct);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(true,  trivial_except_destroy,		trivial_except_destroy);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, trivial_except_copy_ctor,		trivial_except_copy_ctor);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(true,  trivial_except_copy_assign,	trivial_except_copy_assign);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, trivial_except_move_ctor,		trivial_except_move_ctor);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, trivial_except_move_assign,	trivial_except_move_assign);

BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(true,	S1);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(true,	const S1);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(true,	volatile S1);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(true,	const volatile S1);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(true,	S1*);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false,	S1&);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false,	S1&&);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(true,	S1[2]);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false,	S1[]);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false,	S1(&)[2]);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false,	S1(&)[]);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false,	S1(&&)[2]);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false,	S1(&&)[]);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false,	S2);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(true,	S2*);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false,	S2[2]);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(true,	int);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(true,	int*);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false,	int&);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false,	int&&);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(true,	int[2]);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false,	int[]);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false,	int(&)[2]);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false,	int(&)[]);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false,	int(&&)[2]);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false,	int(&&)[]);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false,	UDT);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(true,	POD_UDT);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(true,	union_UDT);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(true,	POD_union_UDT);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(true,	enum_UDT);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(true,	enum_class_UDT);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false,	foo0_t);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false,	foo1_t);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false,	foo2_t);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false,	foo3_t);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false,	foo4_t);

BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(true,  S1, S1);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, S1, const S1);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, S1, volatile S1);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, S1, const volatile S1);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, S1, S1*);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, S1, S1&);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(true,  S1, S1&&);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, S1, const S1&&);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, S1, volatile S1&&);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, S1, const volatile S1&&);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, S1, S1[2]);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(true,  S1, int);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, S1, int*);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(true,  S1, int&);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(true,  S1, int&&);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, S1, UDT);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, S1, std::string);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(true,  S1, int, float);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, S1, int, UDT);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, S1, UDT, int);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, S1, int, UDT, std::string);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, S1, int, int, std::string);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, S1, UDT, int, std::string);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, S1, int, UDT, std::string, int);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(true,  S1, int, int, int);
	
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, S2, S2);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, S2, S2*);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(true,  S2, S2&);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(true,  S2, const S2&);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, S2, volatile S2&);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, S2, const volatile S2&);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, S2, S2&&);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(true,  S2, const S2&&);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, S2, volatile S2&&);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, S2, const volatile S2&&);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, S2, S2[2]);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, S2, UDT);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, S2, int);

BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(true,  int,        int);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, int,        int*);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(true,  int,        int&);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(true,  int,        int&&);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, int,        int[2]);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, int,        int[]);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, int,        int(&)[2]);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, int,        int(&)[]);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, int,        int(&&)[2]);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, int,        int(&&)[]);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, int*,       int);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(true,                 int*,                int*);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(true,  const          int*,                int*);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(true,        volatile int*,                int*);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(true,  const volatile int*,                int*);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false,                int*, const          int*);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(true,  const          int*, const          int*);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false,       volatile int*, const          int*);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(true,  const volatile int*, const          int*);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false,                int*,       volatile int*);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, const          int*,       volatile int*);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(true,        volatile int*,       volatile int*);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(true,  const volatile int*,       volatile int*);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false,                int*, const volatile int*);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, const          int*, const volatile int*);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false,       volatile int*, const volatile int*);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(true,  const volatile int*, const volatile int*);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, int*,       int&);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, int*,       int&&);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(true,  int*,       int[2]);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(true,  int*,       int[]);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(true,  int*,       int(&)[2]);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(true,  int*,       int(&)[]);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(true,  int*,       int(&&)[2]);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(true,  int*,       int(&&)[]);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false,                int&,                int);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(true,  const          int&,                int);	// const参照だけ特別
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false,       volatile int&,                int);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, const volatile int&,                int);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false,                int&, const          int);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(true,  const          int&, const          int);	// const参照だけ特別
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false,       volatile int&, const          int);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, const volatile int&, const          int);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false,                int&,       volatile int);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, const          int&,       volatile int);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false,       volatile int&,       volatile int);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, const volatile int&,       volatile int);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false,                int&, const volatile int);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, const          int&, const volatile int);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false,       volatile int&, const volatile int);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, const volatile int&, const volatile int);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, int&,       int*);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(true,                 int&,                int&);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(true,  const          int&,                int&);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(true,        volatile int&,                int&);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(true,  const volatile int&,                int&);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false,                int&, const          int&);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(true,  const          int&, const          int&);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false,       volatile int&, const          int&);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(true,  const volatile int&, const          int&);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false,                int&,       volatile int&);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, const          int&,       volatile int&);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(true,        volatile int&,       volatile int&);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(true,  const volatile int&,       volatile int&);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false,                int&, const volatile int&);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, const          int&, const volatile int&);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false,       volatile int&, const volatile int&);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(true,  const volatile int&, const volatile int&);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, int&,       int&&);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, int&,       int[2]);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, int&,       int[]);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, int&,       int(&)[2]);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, int&,       int(&)[]);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, int&,       int(&&)[2]);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, int&,       int(&&)[]);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(true,  int&&,      int);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, int&&,      int*);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, int&&,      int&);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(true,  int&&,      int&&);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, int&&,      int[2]);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, int&&,      int[]);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, int&&,      int(&)[2]);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, int&&,      int(&)[]);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, int&&,      int(&&)[2]);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, int&&,      int(&&)[]);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, int[2],     int);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, int[2],     int*);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, int[2],     int&);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, int[2],     int&&);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, int[2],     int[2]);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, int[2],     int[]);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, int[2],     int(&)[2]);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, int[2],     int(&)[]);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, int[2],     int(&&)[2]);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, int[2],     int(&&)[]);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, int[],      int);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, int[],      int*);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, int[],      int&);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, int[],      int&&);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, int[],      int[2]);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, int[],      int[]);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, int[],      int(&)[2]);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, int[],      int(&)[]);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, int[],      int(&&)[2]);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, int[],      int(&&)[]);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, int(&)[2],  int);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, int(&)[2],  int*);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, int(&)[2],  int&);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, int(&)[2],  int&&);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, int(&)[2],  int[2]);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, int(&)[2],  int[]);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(true,  int(&)[2],  int(&)[2]);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, int(&)[2],  int(&)[]);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, int(&)[2],  int(&&)[2]);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, int(&)[2],  int(&&)[]);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, int(&)[],   int);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, int(&)[],   int*);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, int(&)[],   int&);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, int(&)[],   int&&);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, int(&)[],   int[2]);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, int(&)[],   int[]);
//	BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, int(&)[],   int(&)[2]);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(true,  int(&)[],   int(&)[]);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, int(&)[],   int(&&)[2]);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, int(&)[],   int(&&)[]);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, int(&&)[2], int);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, int(&&)[2], int*);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, int(&&)[2], int&);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, int(&&)[2], int&&);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(true,  int(&&)[2], int[2]);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, int(&&)[2], int[]);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, int(&&)[2], int(&)[2]);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, int(&&)[2], int(&)[]);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(true,  int(&&)[2], int(&&)[2]);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, int(&&)[2], int(&&)[]);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, int(&&)[],  int);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, int(&&)[],  int*);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, int(&&)[],  int&);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, int(&&)[],  int&&);
//	BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, int(&&)[],  int[2]);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(true,  int(&&)[],  int[]);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, int(&&)[],  int(&)[2]);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, int(&&)[],  int(&)[]);
//	BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, int(&&)[],  int(&&)[2]);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(true,  int(&&)[],  int(&&)[]);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, int,        UDT);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, int, int, int);

BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false,                void);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, const          void);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false,       volatile void);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, const volatile void);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false,                void,                void);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, const          void, const          void);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false,       volatile void,       volatile void);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false, const volatile void, const volatile void);

BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false,	UDT,			UDT);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(true,	POD_UDT,		               POD_UDT);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(true,	POD_UDT,		const          POD_UDT);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false,	POD_UDT,		      volatile POD_UDT);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false,	POD_UDT,		const volatile POD_UDT);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(true,	union_UDT,		union_UDT);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false,	union_UDT,		volatile union_UDT);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(true,	POD_union_UDT,	POD_union_UDT);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false,	POD_union_UDT,	const volatile POD_union_UDT);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(true,	enum_UDT,		enum_UDT);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(true,	enum_UDT,		volatile enum_UDT);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(true,	enum_class_UDT,	enum_class_UDT);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(true,	enum_class_UDT,	const volatile enum_class_UDT);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false,	enum_UDT,		int);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false,	enum_class_UDT,	int);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false,	foo0_t,	foo0_t);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false,	foo1_t,	foo1_t);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false,	foo2_t,	foo2_t);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false,	foo3_t,	foo3_t);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false,	foo4_t,	foo4_t);

BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(true,	nothrow_default_ctor_UDT);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false,	nothrow_dtor_UDT);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false,	nothrow_copy_ctor_UDT);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false,	nothrow_copy_assign_UDT);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false,	nothrow_move_ctor_UDT);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false,	nothrow_move_assign_UDT);

BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false,	nothrow_default_ctor_UDT,	nothrow_default_ctor_UDT);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false,	nothrow_dtor_UDT,			nothrow_dtor_UDT);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false,	nothrow_copy_ctor_UDT,		nothrow_copy_ctor_UDT);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false,	nothrow_copy_assign_UDT,	nothrow_copy_assign_UDT);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(true,	nothrow_move_ctor_UDT,		nothrow_move_ctor_UDT);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false,	nothrow_move_assign_UDT,	nothrow_move_assign_UDT);

BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false,	nothrow_default_ctor_UDT,	nothrow_default_ctor_UDT&);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false,	nothrow_dtor_UDT,			nothrow_dtor_UDT&);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(true,	nothrow_copy_ctor_UDT,		nothrow_copy_ctor_UDT&);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false,	nothrow_copy_assign_UDT,	nothrow_copy_assign_UDT&);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false,	nothrow_move_ctor_UDT,		nothrow_move_ctor_UDT&);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false,	nothrow_move_assign_UDT,	nothrow_move_assign_UDT&);

BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false,	nothrow_default_ctor_UDT,	nothrow_default_ctor_UDT&&);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false,	nothrow_dtor_UDT,			nothrow_dtor_UDT&&);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false,	nothrow_copy_ctor_UDT,		nothrow_copy_ctor_UDT&&);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false,	nothrow_copy_assign_UDT,	nothrow_copy_assign_UDT&&);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(true,	nothrow_move_ctor_UDT,		nothrow_move_ctor_UDT&&);
BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST(false,	nothrow_move_assign_UDT,	nothrow_move_assign_UDT&&);

}	// namespace is_nothrow_constructible_test

}	// namespace bksge_type_traits_test

#undef BKSGE_IS_NOTHROW_CONSTRUCTIBLE_TEST
