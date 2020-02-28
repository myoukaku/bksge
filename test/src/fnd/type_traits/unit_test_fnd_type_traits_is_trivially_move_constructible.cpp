/**
 *	@file	unit_test_fnd_type_traits_is_trivially_move_constructible.cpp
 *
 *	@brief	is_trivially_move_constructible のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/type_traits/is_trivially_move_constructible.hpp>
#include <gtest/gtest.h>
#include "type_traits_test_utility.hpp"

BKSGE_WARNING_PUSH()
BKSGE_WARNING_DISABLE_MSVC(4510)	// 既定のコンストラクターを生成できません。
BKSGE_WARNING_DISABLE_MSVC(4610)	// '...'を初期化できません。ユーザー定義のコンストラクターが必要です。

#define BKSGE_IS_TRIVIALLY_MOVE_CONSTRUCTIBLE_TEST(b, T)	\
	static_assert(bksge::is_trivially_move_constructible<T>::value == b, #T)

namespace bksge_type_traits_test
{

namespace is_trivially_move_constructible_test
{

// トリビアルなmoveコンストラクタを持つ
struct S1
{
	int n;
};

// 非トリビアルだが例外を投げないmoveコンストラクタを持つ
struct S2
{
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
	S5(const S5&);
};

// moveコンストラクタを持たないクラスをメンバに持つ
struct S6
{
	S5 member;
};

GTEST_TEST(TypeTraitsTest, IsTriviallyMoveConstructibleTest)
{
	IntegralConstantTest<bksge::is_trivially_move_constructible<S1>, true>();
	IntegralConstantTest<bksge::is_trivially_move_constructible<S2>, false>();
	IntegralConstantTest<bksge::is_trivially_move_constructible<S3>, false>();
	IntegralConstantTest<bksge::is_trivially_move_constructible<S4>, false>();
	IntegralConstantTest<bksge::is_trivially_move_constructible<S5>, false>();
	IntegralConstantTest<bksge::is_trivially_move_constructible<S6>, false>();

	BKSGE_IS_TRIVIALLY_MOVE_CONSTRUCTIBLE_TEST(true,                 int);
	BKSGE_IS_TRIVIALLY_MOVE_CONSTRUCTIBLE_TEST(true,  const          int);
	BKSGE_IS_TRIVIALLY_MOVE_CONSTRUCTIBLE_TEST(true,        volatile int);
	BKSGE_IS_TRIVIALLY_MOVE_CONSTRUCTIBLE_TEST(true,  const volatile int);
	BKSGE_IS_TRIVIALLY_MOVE_CONSTRUCTIBLE_TEST(true,  int*);
	BKSGE_IS_TRIVIALLY_MOVE_CONSTRUCTIBLE_TEST(true,  int&);
	BKSGE_IS_TRIVIALLY_MOVE_CONSTRUCTIBLE_TEST(true,  int&&);
	BKSGE_IS_TRIVIALLY_MOVE_CONSTRUCTIBLE_TEST(false, int[2]);
	BKSGE_IS_TRIVIALLY_MOVE_CONSTRUCTIBLE_TEST(false, int[]);
	BKSGE_IS_TRIVIALLY_MOVE_CONSTRUCTIBLE_TEST(true,  int(&)[2]);
	BKSGE_IS_TRIVIALLY_MOVE_CONSTRUCTIBLE_TEST(true,  int(&)[]);
	BKSGE_IS_TRIVIALLY_MOVE_CONSTRUCTIBLE_TEST(true,  int(&&)[2]);
	BKSGE_IS_TRIVIALLY_MOVE_CONSTRUCTIBLE_TEST(true,  int(&&)[]);

	BKSGE_IS_TRIVIALLY_MOVE_CONSTRUCTIBLE_TEST(false,                void);
	BKSGE_IS_TRIVIALLY_MOVE_CONSTRUCTIBLE_TEST(false, const          void);
	BKSGE_IS_TRIVIALLY_MOVE_CONSTRUCTIBLE_TEST(false,       volatile void);
	BKSGE_IS_TRIVIALLY_MOVE_CONSTRUCTIBLE_TEST(false, const volatile void);

	BKSGE_IS_TRIVIALLY_MOVE_CONSTRUCTIBLE_TEST(false,                UDT);
	BKSGE_IS_TRIVIALLY_MOVE_CONSTRUCTIBLE_TEST(false, const          UDT);
	BKSGE_IS_TRIVIALLY_MOVE_CONSTRUCTIBLE_TEST(false,       volatile UDT);
	BKSGE_IS_TRIVIALLY_MOVE_CONSTRUCTIBLE_TEST(false, const volatile UDT);
	BKSGE_IS_TRIVIALLY_MOVE_CONSTRUCTIBLE_TEST(true,  UDT*);
	BKSGE_IS_TRIVIALLY_MOVE_CONSTRUCTIBLE_TEST(true,  UDT&);
	BKSGE_IS_TRIVIALLY_MOVE_CONSTRUCTIBLE_TEST(true,  UDT&&);
	BKSGE_IS_TRIVIALLY_MOVE_CONSTRUCTIBLE_TEST(false, UDT[2]);
	BKSGE_IS_TRIVIALLY_MOVE_CONSTRUCTIBLE_TEST(false, UDT[]);
	BKSGE_IS_TRIVIALLY_MOVE_CONSTRUCTIBLE_TEST(true,  UDT(&)[2]);
	BKSGE_IS_TRIVIALLY_MOVE_CONSTRUCTIBLE_TEST(true,  UDT(&)[]);
	BKSGE_IS_TRIVIALLY_MOVE_CONSTRUCTIBLE_TEST(true,  UDT(&&)[2]);
	BKSGE_IS_TRIVIALLY_MOVE_CONSTRUCTIBLE_TEST(true,  UDT(&&)[]);

	BKSGE_IS_TRIVIALLY_MOVE_CONSTRUCTIBLE_TEST(true,                 POD_UDT);
	BKSGE_IS_TRIVIALLY_MOVE_CONSTRUCTIBLE_TEST(true,  const          POD_UDT);
	BKSGE_IS_TRIVIALLY_MOVE_CONSTRUCTIBLE_TEST(false,       volatile POD_UDT);
	BKSGE_IS_TRIVIALLY_MOVE_CONSTRUCTIBLE_TEST(false, const volatile POD_UDT);
	BKSGE_IS_TRIVIALLY_MOVE_CONSTRUCTIBLE_TEST(true,  POD_UDT*);
	BKSGE_IS_TRIVIALLY_MOVE_CONSTRUCTIBLE_TEST(true,  POD_UDT&);
	BKSGE_IS_TRIVIALLY_MOVE_CONSTRUCTIBLE_TEST(true,  POD_UDT&&);
	BKSGE_IS_TRIVIALLY_MOVE_CONSTRUCTIBLE_TEST(false, POD_UDT[2]);
	BKSGE_IS_TRIVIALLY_MOVE_CONSTRUCTIBLE_TEST(false, POD_UDT[]);
	BKSGE_IS_TRIVIALLY_MOVE_CONSTRUCTIBLE_TEST(true,  POD_UDT(&)[2]);
	BKSGE_IS_TRIVIALLY_MOVE_CONSTRUCTIBLE_TEST(true,  POD_UDT(&)[]);
	BKSGE_IS_TRIVIALLY_MOVE_CONSTRUCTIBLE_TEST(true,  POD_UDT(&&)[2]);
	BKSGE_IS_TRIVIALLY_MOVE_CONSTRUCTIBLE_TEST(true,  POD_UDT(&&)[]);

	BKSGE_IS_TRIVIALLY_MOVE_CONSTRUCTIBLE_TEST(false,                trivial_except_move_ctor);
	BKSGE_IS_TRIVIALLY_MOVE_CONSTRUCTIBLE_TEST(false, const          trivial_except_move_ctor);
	BKSGE_IS_TRIVIALLY_MOVE_CONSTRUCTIBLE_TEST(false,       volatile trivial_except_move_ctor);
	BKSGE_IS_TRIVIALLY_MOVE_CONSTRUCTIBLE_TEST(false, const volatile trivial_except_move_ctor);
	BKSGE_IS_TRIVIALLY_MOVE_CONSTRUCTIBLE_TEST(false,                trivial_except_move_assign);
	BKSGE_IS_TRIVIALLY_MOVE_CONSTRUCTIBLE_TEST(false, const          trivial_except_move_assign);
	BKSGE_IS_TRIVIALLY_MOVE_CONSTRUCTIBLE_TEST(false,       volatile trivial_except_move_assign);
	BKSGE_IS_TRIVIALLY_MOVE_CONSTRUCTIBLE_TEST(false, const volatile trivial_except_move_assign);

	BKSGE_IS_TRIVIALLY_MOVE_CONSTRUCTIBLE_TEST(true,  f1);
	BKSGE_IS_TRIVIALLY_MOVE_CONSTRUCTIBLE_TEST(true,  f2);
	BKSGE_IS_TRIVIALLY_MOVE_CONSTRUCTIBLE_TEST(true,  f3);
	BKSGE_IS_TRIVIALLY_MOVE_CONSTRUCTIBLE_TEST(true,  mf1);
	BKSGE_IS_TRIVIALLY_MOVE_CONSTRUCTIBLE_TEST(true,  mf2);
	BKSGE_IS_TRIVIALLY_MOVE_CONSTRUCTIBLE_TEST(true,  mf3);
	BKSGE_IS_TRIVIALLY_MOVE_CONSTRUCTIBLE_TEST(true,  mf4);
	BKSGE_IS_TRIVIALLY_MOVE_CONSTRUCTIBLE_TEST(true,  mp);
	BKSGE_IS_TRIVIALLY_MOVE_CONSTRUCTIBLE_TEST(true,  cmf);
	BKSGE_IS_TRIVIALLY_MOVE_CONSTRUCTIBLE_TEST(false, foo0_t);
	BKSGE_IS_TRIVIALLY_MOVE_CONSTRUCTIBLE_TEST(false, foo1_t);
	BKSGE_IS_TRIVIALLY_MOVE_CONSTRUCTIBLE_TEST(false, foo2_t);
	BKSGE_IS_TRIVIALLY_MOVE_CONSTRUCTIBLE_TEST(false, foo3_t);
	BKSGE_IS_TRIVIALLY_MOVE_CONSTRUCTIBLE_TEST(false, foo4_t);
}

}	// namespace is_trivially_move_constructible_test

}	// namespace bksge_type_traits_test

#undef BKSGE_IS_TRIVIALLY_MOVE_CONSTRUCTIBLE_TEST

BKSGE_WARNING_POP()
