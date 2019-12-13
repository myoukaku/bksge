/**
 *	@file	unit_test_fnd_type_traits_is_implicitly_constructible.cpp
 *
 *	@brief	is_implicitly_constructible のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/type_traits/is_implicitly_constructible.hpp>
#include <gtest/gtest.h>
#include <cstddef>
#include "type_traits_test_utility.hpp"

#define BKSGE_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(b, ...)	\
	static_assert(bksge::is_implicitly_constructible<__VA_ARGS__>::value == b, #__VA_ARGS__)

namespace bksge_type_traits_test
{

namespace is_implicitly_constructible_test
{

// defaultコンストラクタを持たない
struct S1
{
	S1() = delete;
};

// トリビアルなdefaultコンストラクタを持つ
struct S2
{
	int n;
};

// defaultコンストラクタを持つ
struct S3
{
	S3();
};

// explicitなdefaultコンストラクタを持つ
struct S4
{
	explicit S4();
};

// 引数を1つ取るコンストラクタを持つ
struct S5
{
	S5(int);
};

// explicitな引数を1つ取るコンストラクタを持つ
struct S6
{
	explicit S6(int);
};

// 引数を2つ取るコンストラクタを持つ
struct S7
{
	S7(int, float);
};

// explicitな引数を2つ取るコンストラクタを持つ
struct S8
{
	explicit S8(int, float);
};

GTEST_TEST(TypeTraitsTest, IsImplicitlyConstructibleTest)
{
	IntegralConstantTest<bksge::is_implicitly_constructible<S1>, false>();
	IntegralConstantTest<bksge::is_implicitly_constructible<S2>, true>();
	IntegralConstantTest<bksge::is_implicitly_constructible<S3>, true>();
	IntegralConstantTest<bksge::is_implicitly_constructible<S4>, false>();
	IntegralConstantTest<bksge::is_implicitly_constructible<S5>, false>();
	IntegralConstantTest<bksge::is_implicitly_constructible<S6>, false>();
	IntegralConstantTest<bksge::is_implicitly_constructible<S7>, false>();
	IntegralConstantTest<bksge::is_implicitly_constructible<S8>, false>();

	BKSGE_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(false, S1);
	BKSGE_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(true,  S2);
	BKSGE_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(true,  S3);
	BKSGE_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(false, S4);
	BKSGE_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(false, S5);
	BKSGE_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(false, S6);
	BKSGE_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(false, S7);
	BKSGE_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(false, S8);

	BKSGE_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(false, S1, int);
	BKSGE_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(false, S2, int);
	BKSGE_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(false, S3, int);
	BKSGE_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(false, S4, int);
	BKSGE_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(true,  S5, int);
	BKSGE_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(false, S6, int);
	BKSGE_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(false, S7, int);
	BKSGE_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(false, S8, int);

	BKSGE_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(false, S1, float);
	BKSGE_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(false, S2, float);
	BKSGE_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(false, S3, float);
	BKSGE_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(false, S4, float);
	BKSGE_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(false, S5, float);
	BKSGE_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(false, S6, float);
	BKSGE_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(false, S7, float);
	BKSGE_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(false, S8, float);

	BKSGE_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(false, S1, int, float);
	BKSGE_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(false, S2, int, float);
	BKSGE_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(false, S3, int, float);
	BKSGE_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(false, S4, int, float);
	BKSGE_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(false, S5, int, float);
	BKSGE_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(false, S6, int, float);
	BKSGE_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(true,  S7, int, float);
	BKSGE_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(false, S8, int, float);

	BKSGE_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(false, S1, int, int);
	BKSGE_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(false, S2, int, int);
	BKSGE_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(false, S3, int, int);
	BKSGE_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(false, S4, int, int);
	BKSGE_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(false, S5, int, int);
	BKSGE_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(false, S6, int, int);
	BKSGE_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(false, S7, int, int);
	BKSGE_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(false, S8, int, int);

	BKSGE_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(true,  int);
	BKSGE_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(true,  const int);
	BKSGE_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(true,  volatile int);
	BKSGE_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(true,  const volatile int);
	BKSGE_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(true,  int*);
	BKSGE_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(false, int&);
	BKSGE_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(false, int&&);
	BKSGE_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(true,  int[2]);
	BKSGE_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(false, int[]);
	BKSGE_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(false, int(&)[2]);
	BKSGE_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(false, int(&)[]);
	BKSGE_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(false, int(&&)[2]);
	BKSGE_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(false, int(&&)[]);

	BKSGE_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(false, void);
	BKSGE_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(false, const void);
	BKSGE_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(false, volatile void);
	BKSGE_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(false, const volatile void);

	BKSGE_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(true,  void*);
	BKSGE_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(true,  std::nullptr_t);
	BKSGE_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(true,  enum_UDT);
	BKSGE_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(true,  enum_class_UDT);
	BKSGE_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(true,  UDT);
	BKSGE_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(false, int_constructible);
	BKSGE_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(true,  int_convertible);
	BKSGE_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(false, test_abc1);
	BKSGE_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(false, test_abc2);
	BKSGE_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(false, test_abc3);
	BKSGE_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(true,  test_concrete1);
	BKSGE_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(true,  test_concrete2);
	BKSGE_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(true,  trivial_except_construct);
	BKSGE_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(true,  trivial_except_destroy);
	BKSGE_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(false, trivial_except_copy_ctor);
	BKSGE_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(true,  trivial_except_copy_assign);
	BKSGE_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(false, trivial_except_move_ctor);
	BKSGE_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(true,  trivial_except_move_assign);
	BKSGE_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(true,  f1);
	BKSGE_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(true,  f2);
	BKSGE_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(true,  f3);
	BKSGE_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(true,  mf1);
	BKSGE_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(true,  mf2);
	BKSGE_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(true,  mf3);
	BKSGE_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(true,  mf4);
	BKSGE_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(true,  mp);
	BKSGE_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(true,  cmf);
	BKSGE_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(false, foo0_t);
	BKSGE_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(false, foo1_t);
	BKSGE_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(false, foo2_t);
	BKSGE_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(false, foo3_t);
	BKSGE_IS_IMPLICITLY_CONSTRUCTIBLE_TEST(false, foo4_t);
}

}	// namespace is_implicitly_constructible_test

}	// namespace bksge_type_traits_test

#undef BKSGE_IS_IMPLICITLY_CONSTRUCTIBLE_TEST
