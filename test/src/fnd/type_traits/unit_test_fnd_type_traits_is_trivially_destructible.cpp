﻿/**
 *	@file	unit_test_fnd_type_traits_is_trivially_destructible.cpp
 *
 *	@brief	is_trivially_destructible のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/type_traits/is_trivially_destructible.hpp>
#include <gtest/gtest.h>
#include "type_traits_test_utility.hpp"

#define BKSGE_IS_TRIVIALLY_DESTRUCTIBLE_TEST(b, T)	\
	static_assert(bksge::is_trivially_destructible<T>::value == b, #T)

namespace bksge_type_traits_test
{

namespace is_trivially_destructible_test
{

// トリビアルなデストラクタを持つ
struct S1
{
	int n;
};

// 非トリビアルなデストラクタを持つ
struct S2
{
	~S2();
};

// 非トリビアルなデストラクタを持つクラスをメンバに持つ
struct S3
{
	S2 member;
};

// default指定されたデストラクタを持つ
struct S4
{
	~S4() = default;
};

// default指定されたデストラクタを持つクラスをメンバに持つ
struct S5
{
	S4 member;
};

// デストラクタを持たない
struct S6
{
	~S6() = delete;
};

BKSGE_WARNING_PUSH()
BKSGE_WARNING_DISABLE_MSVC(4624)	// 基底クラスのデストラクターへのアクセスまたはその削除ができないため、デストラクターを生成できませんでした

// デストラクタを持たないクラスをメンバに持つ
struct S7
{
	S6 member;
};

BKSGE_WARNING_POP()

GTEST_TEST(TypeTraitsTest, IsTriviallyDestructibleTest)
{
	IntegralConstantTest<bksge::is_trivially_destructible<S1>, true>();
	IntegralConstantTest<bksge::is_trivially_destructible<S2>, false>();
	IntegralConstantTest<bksge::is_trivially_destructible<S3>, false>();
	IntegralConstantTest<bksge::is_trivially_destructible<S4>, true>();
	IntegralConstantTest<bksge::is_trivially_destructible<S5>, true>();
	IntegralConstantTest<bksge::is_trivially_destructible<S6>, false>();
	IntegralConstantTest<bksge::is_trivially_destructible<S7>, false>();

	BKSGE_IS_TRIVIALLY_DESTRUCTIBLE_TEST(true,                 int);
	BKSGE_IS_TRIVIALLY_DESTRUCTIBLE_TEST(true,  const          int);
	BKSGE_IS_TRIVIALLY_DESTRUCTIBLE_TEST(true,        volatile int);
	BKSGE_IS_TRIVIALLY_DESTRUCTIBLE_TEST(true,  const volatile int);
	BKSGE_IS_TRIVIALLY_DESTRUCTIBLE_TEST(true,  int*);
	BKSGE_IS_TRIVIALLY_DESTRUCTIBLE_TEST(true,  int&);
	BKSGE_IS_TRIVIALLY_DESTRUCTIBLE_TEST(true,  int&&);
	BKSGE_IS_TRIVIALLY_DESTRUCTIBLE_TEST(true,  int[2]);
	BKSGE_IS_TRIVIALLY_DESTRUCTIBLE_TEST(false, int[]);
	BKSGE_IS_TRIVIALLY_DESTRUCTIBLE_TEST(true,  int(&)[2]);
	BKSGE_IS_TRIVIALLY_DESTRUCTIBLE_TEST(true,  int(&)[]);
	BKSGE_IS_TRIVIALLY_DESTRUCTIBLE_TEST(true,  int(&&)[2]);
	BKSGE_IS_TRIVIALLY_DESTRUCTIBLE_TEST(true,  int(&&)[]);

	BKSGE_IS_TRIVIALLY_DESTRUCTIBLE_TEST(false,                void);
	BKSGE_IS_TRIVIALLY_DESTRUCTIBLE_TEST(false, const          void);
	BKSGE_IS_TRIVIALLY_DESTRUCTIBLE_TEST(false,       volatile void);
	BKSGE_IS_TRIVIALLY_DESTRUCTIBLE_TEST(false, const volatile void);

	BKSGE_IS_TRIVIALLY_DESTRUCTIBLE_TEST(false,                UDT);
	BKSGE_IS_TRIVIALLY_DESTRUCTIBLE_TEST(false, const          UDT);
	BKSGE_IS_TRIVIALLY_DESTRUCTIBLE_TEST(false,       volatile UDT);
	BKSGE_IS_TRIVIALLY_DESTRUCTIBLE_TEST(false, const volatile UDT);
	BKSGE_IS_TRIVIALLY_DESTRUCTIBLE_TEST(true,  UDT*);
	BKSGE_IS_TRIVIALLY_DESTRUCTIBLE_TEST(true,  UDT&);
	BKSGE_IS_TRIVIALLY_DESTRUCTIBLE_TEST(true,  UDT&&);
	BKSGE_IS_TRIVIALLY_DESTRUCTIBLE_TEST(false, UDT[2]);
	BKSGE_IS_TRIVIALLY_DESTRUCTIBLE_TEST(false, UDT[]);
	BKSGE_IS_TRIVIALLY_DESTRUCTIBLE_TEST(true,  UDT(&)[2]);
	BKSGE_IS_TRIVIALLY_DESTRUCTIBLE_TEST(true,  UDT(&)[]);
	BKSGE_IS_TRIVIALLY_DESTRUCTIBLE_TEST(true,  UDT(&&)[2]);
	BKSGE_IS_TRIVIALLY_DESTRUCTIBLE_TEST(true,  UDT(&&)[]);

	BKSGE_IS_TRIVIALLY_DESTRUCTIBLE_TEST(true,                 POD_UDT);
	BKSGE_IS_TRIVIALLY_DESTRUCTIBLE_TEST(true,  const          POD_UDT);
	BKSGE_IS_TRIVIALLY_DESTRUCTIBLE_TEST(true,        volatile POD_UDT);
	BKSGE_IS_TRIVIALLY_DESTRUCTIBLE_TEST(true,  const volatile POD_UDT);
	BKSGE_IS_TRIVIALLY_DESTRUCTIBLE_TEST(true,  POD_UDT*);
	BKSGE_IS_TRIVIALLY_DESTRUCTIBLE_TEST(true,  POD_UDT&);
	BKSGE_IS_TRIVIALLY_DESTRUCTIBLE_TEST(true,  POD_UDT&&);
	BKSGE_IS_TRIVIALLY_DESTRUCTIBLE_TEST(true,  POD_UDT[2]);
	BKSGE_IS_TRIVIALLY_DESTRUCTIBLE_TEST(false, POD_UDT[]);
	BKSGE_IS_TRIVIALLY_DESTRUCTIBLE_TEST(true,  POD_UDT(&)[2]);
	BKSGE_IS_TRIVIALLY_DESTRUCTIBLE_TEST(true,  POD_UDT(&)[]);
	BKSGE_IS_TRIVIALLY_DESTRUCTIBLE_TEST(true,  POD_UDT(&&)[2]);
	BKSGE_IS_TRIVIALLY_DESTRUCTIBLE_TEST(true,  POD_UDT(&&)[]);

	BKSGE_IS_TRIVIALLY_DESTRUCTIBLE_TEST(true,  trivial_except_construct);
	BKSGE_IS_TRIVIALLY_DESTRUCTIBLE_TEST(false, trivial_except_destroy);
	BKSGE_IS_TRIVIALLY_DESTRUCTIBLE_TEST(true,  trivial_except_copy_ctor);
	BKSGE_IS_TRIVIALLY_DESTRUCTIBLE_TEST(true,  trivial_except_move_ctor);
	BKSGE_IS_TRIVIALLY_DESTRUCTIBLE_TEST(true,  trivial_except_copy_assign);
	BKSGE_IS_TRIVIALLY_DESTRUCTIBLE_TEST(true,  trivial_except_move_assign);

	BKSGE_IS_TRIVIALLY_DESTRUCTIBLE_TEST(false, test_abc1);
	BKSGE_IS_TRIVIALLY_DESTRUCTIBLE_TEST(true,  test_abc2);
	BKSGE_IS_TRIVIALLY_DESTRUCTIBLE_TEST(false, test_abc3);
	BKSGE_IS_TRIVIALLY_DESTRUCTIBLE_TEST(true,  test_concrete1);
	BKSGE_IS_TRIVIALLY_DESTRUCTIBLE_TEST(false, test_concrete2);

	BKSGE_IS_TRIVIALLY_DESTRUCTIBLE_TEST(true,  f1);
	BKSGE_IS_TRIVIALLY_DESTRUCTIBLE_TEST(true,  f2);
	BKSGE_IS_TRIVIALLY_DESTRUCTIBLE_TEST(true,  f3);
	BKSGE_IS_TRIVIALLY_DESTRUCTIBLE_TEST(true,  mf1);
	BKSGE_IS_TRIVIALLY_DESTRUCTIBLE_TEST(true,  mf2);
	BKSGE_IS_TRIVIALLY_DESTRUCTIBLE_TEST(true,  mf3);
	BKSGE_IS_TRIVIALLY_DESTRUCTIBLE_TEST(true,  mf4);
	BKSGE_IS_TRIVIALLY_DESTRUCTIBLE_TEST(true,  mp);
	BKSGE_IS_TRIVIALLY_DESTRUCTIBLE_TEST(true,  cmf);
	BKSGE_IS_TRIVIALLY_DESTRUCTIBLE_TEST(false, foo0_t);
	BKSGE_IS_TRIVIALLY_DESTRUCTIBLE_TEST(false, foo1_t);
	BKSGE_IS_TRIVIALLY_DESTRUCTIBLE_TEST(false, foo2_t);
	BKSGE_IS_TRIVIALLY_DESTRUCTIBLE_TEST(false, foo3_t);
	BKSGE_IS_TRIVIALLY_DESTRUCTIBLE_TEST(false, foo4_t);
}

}	// namespace is_trivially_destructible_test

}	// namespace bksge_type_traits_test

#undef BKSGE_IS_TRIVIALLY_DESTRUCTIBLE_TEST