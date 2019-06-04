/**
 *	@file	unit_test_type_traits_is_implicitly_move_constructible.cpp
 *
 *	@brief	is_implicitly_move_constructible のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/type_traits/is_implicitly_move_constructible.hpp>
#include <gtest/gtest.h>
#include "type_traits_test_utility.hpp"

#define BKSGE_IS_IMPLICITLY_MOVE_CONSTRUCTIBLE_TEST(b, T)	\
	static_assert(bksge::is_implicitly_move_constructible<T>::value == b, #T)

namespace bksge_type_traits_test
{

namespace is_implicitly_move_constructible_test
{

// トリビアルな move コンストラクタを持つ
struct Trivial
{
	int n;
};

// implicit な move コンストラクタを持つ
struct Implicit
{
	Implicit(Implicit&&);
};

// implicit な move コンストラクタを持つクラスをメンバに持つ
struct ImplicitMember
{
	Implicit	member;
};

// explicit な move コンストラクタを持つ
struct Explicit
{
	explicit Explicit(Explicit&&);
};

// explicit な move コンストラクタを持つクラスをメンバに持つ
struct ExplicitMember
{
	Explicit	member;
};

// move コンストラクタを持たない
struct NonMovable
{
	NonMovable(NonMovable&&) = delete;
};

// move コンストラクタを持たないクラスをメンバに持つ
struct NonMovableMember
{
	NonMovable	member;
};

GTEST_TEST(TypeTraitsTest, IsMoveConstructibleTest)
{
	IntegralConstantTest<bksge::is_implicitly_move_constructible<Trivial>,          true>();
	IntegralConstantTest<bksge::is_implicitly_move_constructible<Implicit>,         true>();
	IntegralConstantTest<bksge::is_implicitly_move_constructible<ImplicitMember>,   true>();
	IntegralConstantTest<bksge::is_implicitly_move_constructible<Explicit>,         false>();
	IntegralConstantTest<bksge::is_implicitly_move_constructible<ExplicitMember>,   true>();
	IntegralConstantTest<bksge::is_implicitly_move_constructible<NonMovable>,       false>();
	IntegralConstantTest<bksge::is_implicitly_move_constructible<NonMovableMember>, false>();

	BKSGE_IS_IMPLICITLY_MOVE_CONSTRUCTIBLE_TEST(true,                 int);
	BKSGE_IS_IMPLICITLY_MOVE_CONSTRUCTIBLE_TEST(true,  const          int);
	BKSGE_IS_IMPLICITLY_MOVE_CONSTRUCTIBLE_TEST(true,        volatile int);
	BKSGE_IS_IMPLICITLY_MOVE_CONSTRUCTIBLE_TEST(true,  const volatile int);
	BKSGE_IS_IMPLICITLY_MOVE_CONSTRUCTIBLE_TEST(true,  int*);
	BKSGE_IS_IMPLICITLY_MOVE_CONSTRUCTIBLE_TEST(true,  int&);
	BKSGE_IS_IMPLICITLY_MOVE_CONSTRUCTIBLE_TEST(true,  int&&);
	BKSGE_IS_IMPLICITLY_MOVE_CONSTRUCTIBLE_TEST(false, int[2]);
	BKSGE_IS_IMPLICITLY_MOVE_CONSTRUCTIBLE_TEST(false, int[]);
	BKSGE_IS_IMPLICITLY_MOVE_CONSTRUCTIBLE_TEST(true,  int(&)[2]);
	BKSGE_IS_IMPLICITLY_MOVE_CONSTRUCTIBLE_TEST(true,  int(&)[]);
	BKSGE_IS_IMPLICITLY_MOVE_CONSTRUCTIBLE_TEST(true,  int(&&)[2]);
	BKSGE_IS_IMPLICITLY_MOVE_CONSTRUCTIBLE_TEST(true,  int(&&)[]);

	BKSGE_IS_IMPLICITLY_MOVE_CONSTRUCTIBLE_TEST(false,                void);
	BKSGE_IS_IMPLICITLY_MOVE_CONSTRUCTIBLE_TEST(false, const          void);
	BKSGE_IS_IMPLICITLY_MOVE_CONSTRUCTIBLE_TEST(false,       volatile void);
	BKSGE_IS_IMPLICITLY_MOVE_CONSTRUCTIBLE_TEST(false, const volatile void);

	BKSGE_IS_IMPLICITLY_MOVE_CONSTRUCTIBLE_TEST(true,                 UDT);
	BKSGE_IS_IMPLICITLY_MOVE_CONSTRUCTIBLE_TEST(true,  const          UDT);
	BKSGE_IS_IMPLICITLY_MOVE_CONSTRUCTIBLE_TEST(false,       volatile UDT);
	BKSGE_IS_IMPLICITLY_MOVE_CONSTRUCTIBLE_TEST(false, const volatile UDT);
	BKSGE_IS_IMPLICITLY_MOVE_CONSTRUCTIBLE_TEST(true,  UDT*);
	BKSGE_IS_IMPLICITLY_MOVE_CONSTRUCTIBLE_TEST(true,  UDT&);
	BKSGE_IS_IMPLICITLY_MOVE_CONSTRUCTIBLE_TEST(true,  UDT&&);
	BKSGE_IS_IMPLICITLY_MOVE_CONSTRUCTIBLE_TEST(false, UDT[2]);
	BKSGE_IS_IMPLICITLY_MOVE_CONSTRUCTIBLE_TEST(false, UDT[]);
	BKSGE_IS_IMPLICITLY_MOVE_CONSTRUCTIBLE_TEST(true,  UDT(&)[2]);
	BKSGE_IS_IMPLICITLY_MOVE_CONSTRUCTIBLE_TEST(true,  UDT(&)[]);
	BKSGE_IS_IMPLICITLY_MOVE_CONSTRUCTIBLE_TEST(true,  UDT(&&)[2]);
	BKSGE_IS_IMPLICITLY_MOVE_CONSTRUCTIBLE_TEST(true,  UDT(&&)[]);

	BKSGE_IS_IMPLICITLY_MOVE_CONSTRUCTIBLE_TEST(true,                 Implicit);
	BKSGE_IS_IMPLICITLY_MOVE_CONSTRUCTIBLE_TEST(false, const          Implicit);
	BKSGE_IS_IMPLICITLY_MOVE_CONSTRUCTIBLE_TEST(false,       volatile Implicit);
	BKSGE_IS_IMPLICITLY_MOVE_CONSTRUCTIBLE_TEST(false, const volatile Implicit);
	BKSGE_IS_IMPLICITLY_MOVE_CONSTRUCTIBLE_TEST(true,  Implicit*);
	BKSGE_IS_IMPLICITLY_MOVE_CONSTRUCTIBLE_TEST(true,  Implicit&);
	BKSGE_IS_IMPLICITLY_MOVE_CONSTRUCTIBLE_TEST(true,  Implicit&&);
	BKSGE_IS_IMPLICITLY_MOVE_CONSTRUCTIBLE_TEST(false, Implicit[2]);
	BKSGE_IS_IMPLICITLY_MOVE_CONSTRUCTIBLE_TEST(false, Implicit[]);
	BKSGE_IS_IMPLICITLY_MOVE_CONSTRUCTIBLE_TEST(true,  Implicit(&)[2]);
	BKSGE_IS_IMPLICITLY_MOVE_CONSTRUCTIBLE_TEST(true,  Implicit(&)[]);
	BKSGE_IS_IMPLICITLY_MOVE_CONSTRUCTIBLE_TEST(true,  Implicit(&&)[2]);
	BKSGE_IS_IMPLICITLY_MOVE_CONSTRUCTIBLE_TEST(true,  Implicit(&&)[]);

	BKSGE_IS_IMPLICITLY_MOVE_CONSTRUCTIBLE_TEST(false,                Explicit);
	BKSGE_IS_IMPLICITLY_MOVE_CONSTRUCTIBLE_TEST(false, const          Explicit);
	BKSGE_IS_IMPLICITLY_MOVE_CONSTRUCTIBLE_TEST(false,       volatile Explicit);
	BKSGE_IS_IMPLICITLY_MOVE_CONSTRUCTIBLE_TEST(false, const volatile Explicit);
	BKSGE_IS_IMPLICITLY_MOVE_CONSTRUCTIBLE_TEST(true,  Explicit*);
	BKSGE_IS_IMPLICITLY_MOVE_CONSTRUCTIBLE_TEST(true,  Explicit&);
	BKSGE_IS_IMPLICITLY_MOVE_CONSTRUCTIBLE_TEST(true,  Explicit&&);
	BKSGE_IS_IMPLICITLY_MOVE_CONSTRUCTIBLE_TEST(false, Explicit[2]);
	BKSGE_IS_IMPLICITLY_MOVE_CONSTRUCTIBLE_TEST(false, Explicit[]);
	BKSGE_IS_IMPLICITLY_MOVE_CONSTRUCTIBLE_TEST(true,  Explicit(&)[2]);
	BKSGE_IS_IMPLICITLY_MOVE_CONSTRUCTIBLE_TEST(true,  Explicit(&)[]);
	BKSGE_IS_IMPLICITLY_MOVE_CONSTRUCTIBLE_TEST(true,  Explicit(&&)[2]);
	BKSGE_IS_IMPLICITLY_MOVE_CONSTRUCTIBLE_TEST(true,  Explicit(&&)[]);

	BKSGE_IS_IMPLICITLY_MOVE_CONSTRUCTIBLE_TEST(true,  f1);
	BKSGE_IS_IMPLICITLY_MOVE_CONSTRUCTIBLE_TEST(true,  f2);
	BKSGE_IS_IMPLICITLY_MOVE_CONSTRUCTIBLE_TEST(true,  f3);
	BKSGE_IS_IMPLICITLY_MOVE_CONSTRUCTIBLE_TEST(true,  mf1);
	BKSGE_IS_IMPLICITLY_MOVE_CONSTRUCTIBLE_TEST(true,  mf2);
	BKSGE_IS_IMPLICITLY_MOVE_CONSTRUCTIBLE_TEST(true,  mf3);
	BKSGE_IS_IMPLICITLY_MOVE_CONSTRUCTIBLE_TEST(true,  mf4);
	BKSGE_IS_IMPLICITLY_MOVE_CONSTRUCTIBLE_TEST(true,  mp);
	BKSGE_IS_IMPLICITLY_MOVE_CONSTRUCTIBLE_TEST(true,  cmf);
	BKSGE_IS_IMPLICITLY_MOVE_CONSTRUCTIBLE_TEST(false, foo0_t);
	BKSGE_IS_IMPLICITLY_MOVE_CONSTRUCTIBLE_TEST(false, foo1_t);
	BKSGE_IS_IMPLICITLY_MOVE_CONSTRUCTIBLE_TEST(false, foo2_t);
	BKSGE_IS_IMPLICITLY_MOVE_CONSTRUCTIBLE_TEST(false, foo3_t);
	BKSGE_IS_IMPLICITLY_MOVE_CONSTRUCTIBLE_TEST(false, foo4_t);
}

}	// namespace is_implicitly_move_constructible_test

}	// namespace bksge_type_traits_test

#undef BKSGE_IS_IMPLICITLY_MOVE_CONSTRUCTIBLE_TEST
