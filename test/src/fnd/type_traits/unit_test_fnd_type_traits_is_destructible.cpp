/**
 *	@file	unit_test_fnd_type_traits_is_destructible.cpp
 *
 *	@brief	is_destructible のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/type_traits/is_destructible.hpp>
#include <gtest/gtest.h>
#include "type_traits_test_utility.hpp"

#define BKSGE_IS_DESTRUCTIBLE_TEST(b, T)	\
	static_assert(bksge::is_destructible<T>::value == b, #T)

namespace bksge_type_traits_test
{

namespace is_destructible_test
{

// トリビアルなデストラクタを持つ
struct S1
{
	int n;
};

// 非トリビアルだが例外を投げないデストラクタを持つ
struct S2
{
	~S2() BKSGE_NOEXCEPT_OR_NOTHROW;
};

// 非トリビアルだが例外を投げないデストラクタを持つクラスをメンバに持つ
struct S3
{
	S2 member;
};

// デストラクタが例外を投げる
struct S4
{
	~S4() BKSGE_NOEXCEPT_IF(false);
};

// デストラクタが例外を投げるクラスをメンバに持つ
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

GTEST_TEST(TypeTraitsTest, IsDestructibleTest)
{
	IntegralConstantTest<bksge::is_destructible<S1>, true>();
	IntegralConstantTest<bksge::is_destructible<S2>, true>();
	IntegralConstantTest<bksge::is_destructible<S3>, true>();
	IntegralConstantTest<bksge::is_destructible<S4>, true>();
	IntegralConstantTest<bksge::is_destructible<S5>, true>();
	IntegralConstantTest<bksge::is_destructible<S6>, false>();
	IntegralConstantTest<bksge::is_destructible<S7>, false>();

	BKSGE_IS_DESTRUCTIBLE_TEST(true,                 int);
	BKSGE_IS_DESTRUCTIBLE_TEST(true,  const          int);
	BKSGE_IS_DESTRUCTIBLE_TEST(true,        volatile int);
	BKSGE_IS_DESTRUCTIBLE_TEST(true,  const volatile int);
	BKSGE_IS_DESTRUCTIBLE_TEST(true,  int*);
	BKSGE_IS_DESTRUCTIBLE_TEST(true,  int&);
	BKSGE_IS_DESTRUCTIBLE_TEST(true,  int&&);
	BKSGE_IS_DESTRUCTIBLE_TEST(true,  int[2]);
	BKSGE_IS_DESTRUCTIBLE_TEST(false, int[]);
	BKSGE_IS_DESTRUCTIBLE_TEST(true,  int(&)[2]);
	BKSGE_IS_DESTRUCTIBLE_TEST(true,  int(&)[]);
	BKSGE_IS_DESTRUCTIBLE_TEST(true,  int(&&)[2]);
	BKSGE_IS_DESTRUCTIBLE_TEST(true,  int(&&)[]);

	BKSGE_IS_DESTRUCTIBLE_TEST(false,                void);
	BKSGE_IS_DESTRUCTIBLE_TEST(false, const          void);
	BKSGE_IS_DESTRUCTIBLE_TEST(false,       volatile void);
	BKSGE_IS_DESTRUCTIBLE_TEST(false, const volatile void);

	BKSGE_IS_DESTRUCTIBLE_TEST(true,                 UDT);
	BKSGE_IS_DESTRUCTIBLE_TEST(true,  const          UDT);
	BKSGE_IS_DESTRUCTIBLE_TEST(true,        volatile UDT);
	BKSGE_IS_DESTRUCTIBLE_TEST(true,  const volatile UDT);
	BKSGE_IS_DESTRUCTIBLE_TEST(true,  UDT*);
	BKSGE_IS_DESTRUCTIBLE_TEST(true,  UDT&);
	BKSGE_IS_DESTRUCTIBLE_TEST(true,  UDT&&);
	BKSGE_IS_DESTRUCTIBLE_TEST(true,  UDT[2]);
	BKSGE_IS_DESTRUCTIBLE_TEST(false, UDT[]);
	BKSGE_IS_DESTRUCTIBLE_TEST(true,  UDT(&)[2]);
	BKSGE_IS_DESTRUCTIBLE_TEST(true,  UDT(&)[]);
	BKSGE_IS_DESTRUCTIBLE_TEST(true,  UDT(&&)[2]);
	BKSGE_IS_DESTRUCTIBLE_TEST(true,  UDT(&&)[]);

	BKSGE_IS_DESTRUCTIBLE_TEST(false,                S6);
	BKSGE_IS_DESTRUCTIBLE_TEST(false, const          S6);
	BKSGE_IS_DESTRUCTIBLE_TEST(false,       volatile S6);
	BKSGE_IS_DESTRUCTIBLE_TEST(false, const volatile S6);
	BKSGE_IS_DESTRUCTIBLE_TEST(true,  S6*);
	BKSGE_IS_DESTRUCTIBLE_TEST(true,  S6&);
	BKSGE_IS_DESTRUCTIBLE_TEST(true,  S6&&);
	BKSGE_IS_DESTRUCTIBLE_TEST(false, S6[2]);
	BKSGE_IS_DESTRUCTIBLE_TEST(false, S6[]);
	BKSGE_IS_DESTRUCTIBLE_TEST(true,  S6(&)[2]);
	BKSGE_IS_DESTRUCTIBLE_TEST(true,  S6(&)[]);
	BKSGE_IS_DESTRUCTIBLE_TEST(true,  S6(&&)[2]);
	BKSGE_IS_DESTRUCTIBLE_TEST(true,  S6(&&)[]);

	BKSGE_IS_DESTRUCTIBLE_TEST(true,  test_abc1);
	BKSGE_IS_DESTRUCTIBLE_TEST(true,  test_abc2);
	BKSGE_IS_DESTRUCTIBLE_TEST(true,  test_abc3);
	BKSGE_IS_DESTRUCTIBLE_TEST(true,  test_concrete1);
	BKSGE_IS_DESTRUCTIBLE_TEST(true,  test_concrete2);

	BKSGE_IS_DESTRUCTIBLE_TEST(true,  f1);
	BKSGE_IS_DESTRUCTIBLE_TEST(true,  f2);
	BKSGE_IS_DESTRUCTIBLE_TEST(true,  f3);
	BKSGE_IS_DESTRUCTIBLE_TEST(true,  mf1);
	BKSGE_IS_DESTRUCTIBLE_TEST(true,  mf2);
	BKSGE_IS_DESTRUCTIBLE_TEST(true,  mf3);
	BKSGE_IS_DESTRUCTIBLE_TEST(true,  mf4);
	BKSGE_IS_DESTRUCTIBLE_TEST(true,  mp);
	BKSGE_IS_DESTRUCTIBLE_TEST(true,  cmf);
	BKSGE_IS_DESTRUCTIBLE_TEST(false, foo0_t);
	BKSGE_IS_DESTRUCTIBLE_TEST(false, foo1_t);
	BKSGE_IS_DESTRUCTIBLE_TEST(false, foo2_t);
	BKSGE_IS_DESTRUCTIBLE_TEST(false, foo3_t);
	BKSGE_IS_DESTRUCTIBLE_TEST(false, foo4_t);
}

}	// namespace is_destructible_test

}	// namespace bksge_type_traits_test

#undef BKSGE_IS_DESTRUCTIBLE_TEST
