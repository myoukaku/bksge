/**
 *	@file	unit_test_fnd_type_traits_is_nothrow_destructible.cpp
 *
 *	@brief	is_nothrow_destructible のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/type_traits/is_nothrow_destructible.hpp>
#include <gtest/gtest.h>
#include "type_traits_test_utility.hpp"

#define BKSGE_IS_NOTHROW_DESTRUCTIBLE_TEST(b, T)	\
	static_assert(bksge::is_nothrow_destructible<T>::value == b, #T)

namespace bksge_type_traits_test
{

namespace is_nothrow_destructible_test
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

// デストラクタを持たない
struct S5
{
	~S5() = delete;
};

// デストラクタが例外を投げるクラスをメンバに持つ
struct S6
{
	S4 member;
};

GTEST_TEST(TypeTraitsTest, IsNothrowDestructibleTest)
{
	IntegralConstantTest<bksge::is_nothrow_destructible<S1>, true>();
	IntegralConstantTest<bksge::is_nothrow_destructible<S2>, true>();
	IntegralConstantTest<bksge::is_nothrow_destructible<S3>, true>();
	IntegralConstantTest<bksge::is_nothrow_destructible<S4>, false>();
	IntegralConstantTest<bksge::is_nothrow_destructible<S5>, false>();
	IntegralConstantTest<bksge::is_nothrow_destructible<S6>, false>();

	BKSGE_IS_NOTHROW_DESTRUCTIBLE_TEST(true,                 int);
	BKSGE_IS_NOTHROW_DESTRUCTIBLE_TEST(true,  const          int);
	BKSGE_IS_NOTHROW_DESTRUCTIBLE_TEST(true,        volatile int);
	BKSGE_IS_NOTHROW_DESTRUCTIBLE_TEST(true,  const volatile int);
	BKSGE_IS_NOTHROW_DESTRUCTIBLE_TEST(true,  int*);
	BKSGE_IS_NOTHROW_DESTRUCTIBLE_TEST(true,  int&);
	BKSGE_IS_NOTHROW_DESTRUCTIBLE_TEST(true,  int&&);
	BKSGE_IS_NOTHROW_DESTRUCTIBLE_TEST(true,  int[2]);
	BKSGE_IS_NOTHROW_DESTRUCTIBLE_TEST(false, int[]);
	BKSGE_IS_NOTHROW_DESTRUCTIBLE_TEST(true,  int(&)[2]);
	BKSGE_IS_NOTHROW_DESTRUCTIBLE_TEST(true,  int(&)[]);
	BKSGE_IS_NOTHROW_DESTRUCTIBLE_TEST(true,  int(&&)[2]);
	BKSGE_IS_NOTHROW_DESTRUCTIBLE_TEST(true,  int(&&)[]);

	BKSGE_IS_NOTHROW_DESTRUCTIBLE_TEST(false,                void);
	BKSGE_IS_NOTHROW_DESTRUCTIBLE_TEST(false, const          void);
	BKSGE_IS_NOTHROW_DESTRUCTIBLE_TEST(false,       volatile void);
	BKSGE_IS_NOTHROW_DESTRUCTIBLE_TEST(false, const volatile void);

	BKSGE_IS_NOTHROW_DESTRUCTIBLE_TEST(true,                 UDT);
	BKSGE_IS_NOTHROW_DESTRUCTIBLE_TEST(true,  const          UDT);
	BKSGE_IS_NOTHROW_DESTRUCTIBLE_TEST(true,        volatile UDT);
	BKSGE_IS_NOTHROW_DESTRUCTIBLE_TEST(true,  const volatile UDT);
	BKSGE_IS_NOTHROW_DESTRUCTIBLE_TEST(true,  UDT*);
	BKSGE_IS_NOTHROW_DESTRUCTIBLE_TEST(true,  UDT&);
	BKSGE_IS_NOTHROW_DESTRUCTIBLE_TEST(true,  UDT&&);
	BKSGE_IS_NOTHROW_DESTRUCTIBLE_TEST(true,  UDT[2]);
	BKSGE_IS_NOTHROW_DESTRUCTIBLE_TEST(false, UDT[]);
	BKSGE_IS_NOTHROW_DESTRUCTIBLE_TEST(true,  UDT(&)[2]);
	BKSGE_IS_NOTHROW_DESTRUCTIBLE_TEST(true,  UDT(&)[]);
	BKSGE_IS_NOTHROW_DESTRUCTIBLE_TEST(true,  UDT(&&)[2]);
	BKSGE_IS_NOTHROW_DESTRUCTIBLE_TEST(true,  UDT(&&)[]);

	BKSGE_IS_NOTHROW_DESTRUCTIBLE_TEST(true,                 S1);
	BKSGE_IS_NOTHROW_DESTRUCTIBLE_TEST(true,  const          S1);
	BKSGE_IS_NOTHROW_DESTRUCTIBLE_TEST(true,        volatile S1);
	BKSGE_IS_NOTHROW_DESTRUCTIBLE_TEST(true,  const volatile S1);
	BKSGE_IS_NOTHROW_DESTRUCTIBLE_TEST(true,  S1*);
	BKSGE_IS_NOTHROW_DESTRUCTIBLE_TEST(true,  S1&);
	BKSGE_IS_NOTHROW_DESTRUCTIBLE_TEST(true,  S1&&);
	BKSGE_IS_NOTHROW_DESTRUCTIBLE_TEST(true,  S1[2]);
	BKSGE_IS_NOTHROW_DESTRUCTIBLE_TEST(false, S1[]);
	BKSGE_IS_NOTHROW_DESTRUCTIBLE_TEST(true,  S1(&)[2]);
	BKSGE_IS_NOTHROW_DESTRUCTIBLE_TEST(true,  S1(&)[]);
	BKSGE_IS_NOTHROW_DESTRUCTIBLE_TEST(true,  S1(&&)[2]);
	BKSGE_IS_NOTHROW_DESTRUCTIBLE_TEST(true,  S1(&&)[]);

	BKSGE_IS_NOTHROW_DESTRUCTIBLE_TEST(true,                 S2);
	BKSGE_IS_NOTHROW_DESTRUCTIBLE_TEST(true,  const          S2);
	BKSGE_IS_NOTHROW_DESTRUCTIBLE_TEST(true,        volatile S2);
	BKSGE_IS_NOTHROW_DESTRUCTIBLE_TEST(true,  const volatile S2);
	BKSGE_IS_NOTHROW_DESTRUCTIBLE_TEST(true,  S2*);
	BKSGE_IS_NOTHROW_DESTRUCTIBLE_TEST(true,  S2&);
	BKSGE_IS_NOTHROW_DESTRUCTIBLE_TEST(true,  S2&&);
	BKSGE_IS_NOTHROW_DESTRUCTIBLE_TEST(true,  S2[2]);
	BKSGE_IS_NOTHROW_DESTRUCTIBLE_TEST(false, S2[]);
	BKSGE_IS_NOTHROW_DESTRUCTIBLE_TEST(true,  S2(&)[2]);
	BKSGE_IS_NOTHROW_DESTRUCTIBLE_TEST(true,  S2(&)[]);
	BKSGE_IS_NOTHROW_DESTRUCTIBLE_TEST(true,  S2(&&)[2]);
	BKSGE_IS_NOTHROW_DESTRUCTIBLE_TEST(true,  S2(&&)[]);

	BKSGE_IS_NOTHROW_DESTRUCTIBLE_TEST(true,                 S3);
	BKSGE_IS_NOTHROW_DESTRUCTIBLE_TEST(true,  const          S3);
	BKSGE_IS_NOTHROW_DESTRUCTIBLE_TEST(true,        volatile S3);
	BKSGE_IS_NOTHROW_DESTRUCTIBLE_TEST(true,  const volatile S3);
	BKSGE_IS_NOTHROW_DESTRUCTIBLE_TEST(true,  S3*);
	BKSGE_IS_NOTHROW_DESTRUCTIBLE_TEST(true,  S3&);
	BKSGE_IS_NOTHROW_DESTRUCTIBLE_TEST(true,  S3&&);
	BKSGE_IS_NOTHROW_DESTRUCTIBLE_TEST(true,  S3[2]);
	BKSGE_IS_NOTHROW_DESTRUCTIBLE_TEST(false, S3[]);
	BKSGE_IS_NOTHROW_DESTRUCTIBLE_TEST(true,  S3(&)[2]);
	BKSGE_IS_NOTHROW_DESTRUCTIBLE_TEST(true,  S3(&)[]);
	BKSGE_IS_NOTHROW_DESTRUCTIBLE_TEST(true,  S3(&&)[2]);
	BKSGE_IS_NOTHROW_DESTRUCTIBLE_TEST(true,  S3(&&)[]);

	BKSGE_IS_NOTHROW_DESTRUCTIBLE_TEST(false,                S4);
	BKSGE_IS_NOTHROW_DESTRUCTIBLE_TEST(false, const          S4);
	BKSGE_IS_NOTHROW_DESTRUCTIBLE_TEST(false,       volatile S4);
	BKSGE_IS_NOTHROW_DESTRUCTIBLE_TEST(false, const volatile S4);
	BKSGE_IS_NOTHROW_DESTRUCTIBLE_TEST(true,  S4*);
	BKSGE_IS_NOTHROW_DESTRUCTIBLE_TEST(true,  S4&);
	BKSGE_IS_NOTHROW_DESTRUCTIBLE_TEST(true,  S4&&);
	BKSGE_IS_NOTHROW_DESTRUCTIBLE_TEST(false, S4[2]);
	BKSGE_IS_NOTHROW_DESTRUCTIBLE_TEST(false, S4[]);
	BKSGE_IS_NOTHROW_DESTRUCTIBLE_TEST(true,  S4(&)[2]);
	BKSGE_IS_NOTHROW_DESTRUCTIBLE_TEST(true,  S4(&)[]);
	BKSGE_IS_NOTHROW_DESTRUCTIBLE_TEST(true,  S4(&&)[2]);
	BKSGE_IS_NOTHROW_DESTRUCTIBLE_TEST(true,  S4(&&)[]);

	BKSGE_IS_NOTHROW_DESTRUCTIBLE_TEST(false,                S5);
	BKSGE_IS_NOTHROW_DESTRUCTIBLE_TEST(false, const          S5);
	BKSGE_IS_NOTHROW_DESTRUCTIBLE_TEST(false,       volatile S5);
	BKSGE_IS_NOTHROW_DESTRUCTIBLE_TEST(false, const volatile S5);
	BKSGE_IS_NOTHROW_DESTRUCTIBLE_TEST(true,  S5*);
	BKSGE_IS_NOTHROW_DESTRUCTIBLE_TEST(true,  S5&);
	BKSGE_IS_NOTHROW_DESTRUCTIBLE_TEST(true,  S5&&);
	BKSGE_IS_NOTHROW_DESTRUCTIBLE_TEST(false, S5[2]);
	BKSGE_IS_NOTHROW_DESTRUCTIBLE_TEST(false, S5[]);
	BKSGE_IS_NOTHROW_DESTRUCTIBLE_TEST(true,  S5(&)[2]);
	BKSGE_IS_NOTHROW_DESTRUCTIBLE_TEST(true,  S5(&)[]);
	BKSGE_IS_NOTHROW_DESTRUCTIBLE_TEST(true,  S5(&&)[2]);
	BKSGE_IS_NOTHROW_DESTRUCTIBLE_TEST(true,  S5(&&)[]);

	BKSGE_IS_NOTHROW_DESTRUCTIBLE_TEST(false,                S6);
	BKSGE_IS_NOTHROW_DESTRUCTIBLE_TEST(false, const          S6);
	BKSGE_IS_NOTHROW_DESTRUCTIBLE_TEST(false,       volatile S6);
	BKSGE_IS_NOTHROW_DESTRUCTIBLE_TEST(false, const volatile S6);
	BKSGE_IS_NOTHROW_DESTRUCTIBLE_TEST(true,  S6*);
	BKSGE_IS_NOTHROW_DESTRUCTIBLE_TEST(true,  S6&);
	BKSGE_IS_NOTHROW_DESTRUCTIBLE_TEST(true,  S6&&);
	BKSGE_IS_NOTHROW_DESTRUCTIBLE_TEST(false, S6[2]);
	BKSGE_IS_NOTHROW_DESTRUCTIBLE_TEST(false, S6[]);
	BKSGE_IS_NOTHROW_DESTRUCTIBLE_TEST(true,  S6(&)[2]);
	BKSGE_IS_NOTHROW_DESTRUCTIBLE_TEST(true,  S6(&)[]);
	BKSGE_IS_NOTHROW_DESTRUCTIBLE_TEST(true,  S6(&&)[2]);
	BKSGE_IS_NOTHROW_DESTRUCTIBLE_TEST(true,  S6(&&)[]);

	BKSGE_IS_NOTHROW_DESTRUCTIBLE_TEST(true,  test_abc1);
	BKSGE_IS_NOTHROW_DESTRUCTIBLE_TEST(true,  test_abc2);
	BKSGE_IS_NOTHROW_DESTRUCTIBLE_TEST(true,  test_abc3);
	BKSGE_IS_NOTHROW_DESTRUCTIBLE_TEST(true,  test_concrete1);
	BKSGE_IS_NOTHROW_DESTRUCTIBLE_TEST(true,  test_concrete2);

	BKSGE_IS_NOTHROW_DESTRUCTIBLE_TEST(true,  f1);
	BKSGE_IS_NOTHROW_DESTRUCTIBLE_TEST(true,  f2);
	BKSGE_IS_NOTHROW_DESTRUCTIBLE_TEST(true,  f3);
	BKSGE_IS_NOTHROW_DESTRUCTIBLE_TEST(true,  mf1);
	BKSGE_IS_NOTHROW_DESTRUCTIBLE_TEST(true,  mf2);
	BKSGE_IS_NOTHROW_DESTRUCTIBLE_TEST(true,  mf3);
	BKSGE_IS_NOTHROW_DESTRUCTIBLE_TEST(true,  mf4);
	BKSGE_IS_NOTHROW_DESTRUCTIBLE_TEST(true,  mp);
	BKSGE_IS_NOTHROW_DESTRUCTIBLE_TEST(true,  cmf);
	BKSGE_IS_NOTHROW_DESTRUCTIBLE_TEST(false, foo0_t);
	BKSGE_IS_NOTHROW_DESTRUCTIBLE_TEST(false, foo1_t);
	BKSGE_IS_NOTHROW_DESTRUCTIBLE_TEST(false, foo2_t);
	BKSGE_IS_NOTHROW_DESTRUCTIBLE_TEST(false, foo3_t);
	BKSGE_IS_NOTHROW_DESTRUCTIBLE_TEST(false, foo4_t);
}

}	// namespace is_nothrow_destructible_test

}	// namespace bksge_type_traits_test

#undef BKSGE_IS_NOTHROW_DESTRUCTIBLE_TEST
