/**
 *	@file	unit_test_fnd_type_traits_is_move_constructible.cpp
 *
 *	@brief	is_move_constructible のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/type_traits/is_move_constructible.hpp>
#include <bksge/fnd/config.hpp>
#include <gtest/gtest.h>
#include "type_traits_test_utility.hpp"

BKSGE_WARNING_PUSH()
BKSGE_WARNING_DISABLE_MSVC(4510 4610)

#if defined(BKSGE_HAS_CXX14_VARIABLE_TEMPLATES)

#define BKSGE_IS_MOVE_CONSTRUCTIBLE_TEST(b, T)	\
	static_assert(bksge::is_move_constructible_v<T>      == b, #T);	\
	static_assert(bksge::is_move_constructible<T>::value == b, #T);	\
	static_assert(bksge::is_move_constructible<T>()      == b, #T)

#else

#define BKSGE_IS_MOVE_CONSTRUCTIBLE_TEST(b, T)	\
	static_assert(bksge::is_move_constructible<T>::value == b, #T);	\
	static_assert(bksge::is_move_constructible<T>()      == b, #T)

#endif

namespace bksge_type_traits_test
{

namespace is_move_constructible_test
{

// トリビアルなmoveコンストラクタを持つ
struct S1
{
	int n;
};

// 非トリビアルだが例外を投げないmoveコンストラクタを持つ
struct S2
{
	S2() = default;
	S2(const S2&) = default;
	S2(S2&&) BKSGE_NOEXCEPT_OR_NOTHROW;
};

// 非トリビアルだが例外を投げないmoveコンストラクタを持つクラスをメンバに持つ
struct S3
{
	S2 member;
};

// moveコンストラクタが例外を投げる
struct S4
{
	S4(S4&&) {}
};

// moveコンストラクタを持たない
struct S5
{
	S5(S5&&) = delete;
};

// moveコンストラクタを持たないクラスをメンバに持つ
struct S6
{
	S5 member;
};

BKSGE_IS_MOVE_CONSTRUCTIBLE_TEST(true,  S1);
BKSGE_IS_MOVE_CONSTRUCTIBLE_TEST(true,  S2);
BKSGE_IS_MOVE_CONSTRUCTIBLE_TEST(true,  S3);
BKSGE_IS_MOVE_CONSTRUCTIBLE_TEST(true,  S4);
BKSGE_IS_MOVE_CONSTRUCTIBLE_TEST(false, S5);
BKSGE_IS_MOVE_CONSTRUCTIBLE_TEST(false, S6);

BKSGE_IS_MOVE_CONSTRUCTIBLE_TEST(true,                 int);
BKSGE_IS_MOVE_CONSTRUCTIBLE_TEST(true,  const          int);
BKSGE_IS_MOVE_CONSTRUCTIBLE_TEST(true,        volatile int);
BKSGE_IS_MOVE_CONSTRUCTIBLE_TEST(true,  const volatile int);
BKSGE_IS_MOVE_CONSTRUCTIBLE_TEST(true,  int*);
BKSGE_IS_MOVE_CONSTRUCTIBLE_TEST(true,  int&);
BKSGE_IS_MOVE_CONSTRUCTIBLE_TEST(true,  int&&);
BKSGE_IS_MOVE_CONSTRUCTIBLE_TEST(false, int[2]);
BKSGE_IS_MOVE_CONSTRUCTIBLE_TEST(false, int[]);
BKSGE_IS_MOVE_CONSTRUCTIBLE_TEST(true,  int(&)[2]);
BKSGE_IS_MOVE_CONSTRUCTIBLE_TEST(true,  int(&)[]);
BKSGE_IS_MOVE_CONSTRUCTIBLE_TEST(true,  int(&&)[2]);
BKSGE_IS_MOVE_CONSTRUCTIBLE_TEST(true,  int(&&)[]);

BKSGE_IS_MOVE_CONSTRUCTIBLE_TEST(false,                void);
BKSGE_IS_MOVE_CONSTRUCTIBLE_TEST(false, const          void);
BKSGE_IS_MOVE_CONSTRUCTIBLE_TEST(false,       volatile void);
BKSGE_IS_MOVE_CONSTRUCTIBLE_TEST(false, const volatile void);

BKSGE_IS_MOVE_CONSTRUCTIBLE_TEST(true,                 UDT);
BKSGE_IS_MOVE_CONSTRUCTIBLE_TEST(true,  const          UDT);
BKSGE_IS_MOVE_CONSTRUCTIBLE_TEST(false,       volatile UDT);
BKSGE_IS_MOVE_CONSTRUCTIBLE_TEST(false, const volatile UDT);
BKSGE_IS_MOVE_CONSTRUCTIBLE_TEST(true,  UDT*);
BKSGE_IS_MOVE_CONSTRUCTIBLE_TEST(true,  UDT&);
BKSGE_IS_MOVE_CONSTRUCTIBLE_TEST(true,  UDT&&);
BKSGE_IS_MOVE_CONSTRUCTIBLE_TEST(false, UDT[2]);
BKSGE_IS_MOVE_CONSTRUCTIBLE_TEST(false, UDT[]);
BKSGE_IS_MOVE_CONSTRUCTIBLE_TEST(true,  UDT(&)[2]);
BKSGE_IS_MOVE_CONSTRUCTIBLE_TEST(true,  UDT(&)[]);
BKSGE_IS_MOVE_CONSTRUCTIBLE_TEST(true,  UDT(&&)[2]);
BKSGE_IS_MOVE_CONSTRUCTIBLE_TEST(true,  UDT(&&)[]);

BKSGE_IS_MOVE_CONSTRUCTIBLE_TEST(false,                S5);
BKSGE_IS_MOVE_CONSTRUCTIBLE_TEST(false, const          S5);
BKSGE_IS_MOVE_CONSTRUCTIBLE_TEST(false,       volatile S5);
BKSGE_IS_MOVE_CONSTRUCTIBLE_TEST(false, const volatile S5);
BKSGE_IS_MOVE_CONSTRUCTIBLE_TEST(true,  S5*);
BKSGE_IS_MOVE_CONSTRUCTIBLE_TEST(true,  S5&);
BKSGE_IS_MOVE_CONSTRUCTIBLE_TEST(true,  S5&&);
BKSGE_IS_MOVE_CONSTRUCTIBLE_TEST(false, S5[2]);
BKSGE_IS_MOVE_CONSTRUCTIBLE_TEST(false, S5[]);
BKSGE_IS_MOVE_CONSTRUCTIBLE_TEST(true,  S5(&)[2]);
BKSGE_IS_MOVE_CONSTRUCTIBLE_TEST(true,  S5(&)[]);
BKSGE_IS_MOVE_CONSTRUCTIBLE_TEST(true,  S5(&&)[2]);
BKSGE_IS_MOVE_CONSTRUCTIBLE_TEST(true,  S5(&&)[]);

BKSGE_IS_MOVE_CONSTRUCTIBLE_TEST(true,  f1);
BKSGE_IS_MOVE_CONSTRUCTIBLE_TEST(true,  f2);
BKSGE_IS_MOVE_CONSTRUCTIBLE_TEST(true,  f3);
BKSGE_IS_MOVE_CONSTRUCTIBLE_TEST(true,  mf1);
BKSGE_IS_MOVE_CONSTRUCTIBLE_TEST(true,  mf2);
BKSGE_IS_MOVE_CONSTRUCTIBLE_TEST(true,  mf3);
BKSGE_IS_MOVE_CONSTRUCTIBLE_TEST(true,  mf4);
BKSGE_IS_MOVE_CONSTRUCTIBLE_TEST(true,  mp);
BKSGE_IS_MOVE_CONSTRUCTIBLE_TEST(true,  cmf);
BKSGE_IS_MOVE_CONSTRUCTIBLE_TEST(false, foo0_t);
BKSGE_IS_MOVE_CONSTRUCTIBLE_TEST(false, foo1_t);
BKSGE_IS_MOVE_CONSTRUCTIBLE_TEST(false, foo2_t);
BKSGE_IS_MOVE_CONSTRUCTIBLE_TEST(false, foo3_t);
BKSGE_IS_MOVE_CONSTRUCTIBLE_TEST(false, foo4_t);

}	// namespace is_move_constructible_test

}	// namespace bksge_type_traits_test

#undef BKSGE_IS_MOVE_CONSTRUCTIBLE_TEST

BKSGE_WARNING_POP()
