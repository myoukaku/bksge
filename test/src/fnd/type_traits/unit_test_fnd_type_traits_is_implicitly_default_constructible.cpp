/**
 *	@file	unit_test_fnd_type_traits_is_implicitly_default_constructible.cpp
 *
 *	@brief	is_implicitly_default_constructible のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/type_traits/is_implicitly_default_constructible.hpp>
#include <bksge/fnd/cstddef/nullptr_t.hpp>
#include <bksge/fnd/config.hpp>
#include <gtest/gtest.h>
#include "type_traits_test_utility.hpp"

#define BKSGE_IS_IMPLICITLY_DEFAULT_CONSTRUCTIBLE_TEST(b, T)	\
	static_assert(bksge::is_implicitly_default_constructible<T>::value == b, #T)

namespace bksge_type_traits_test
{

namespace is_implicitly_default_constructible_test
{

BKSGE_WARNING_PUSH()
BKSGE_WARNING_DISABLE_MSVC(4510)	// 既定のコンストラクターを生成できません。
BKSGE_WARNING_DISABLE_MSVC(4610)	// ユーザー定義のコンストラクターが必要です。

// defaultコンストラクタを持たない
struct S1
{
	S1(int);
};

// defaultコンストラクタがdeleted
struct S2
{
	S2() = delete;
};

// トリビアルなdefaultコンストラクタを持つ
struct S3
{
	int n;
};

// defaultコンストラクタを持つ
struct S4
{
	S4();
};

// explicitなdefaultコンストラクタを持つ
struct S5
{
	explicit S5() {}
};

// defaultコンストラクタを持つ
struct S6
{
	S6() BKSGE_NOEXCEPT;
};

// explicitなdefaultコンストラクタを持つ
struct S7
{
	explicit S7() BKSGE_NOEXCEPT;
};

// defaultコンストラクタを持たないクラスをメンバに持つ
struct S1_1
{
	S1 member;
};

// defaultコンストラクタがdeletedクラスをメンバに持つ
struct S2_1
{
	S2 member;
};

// トリビアルなdefaultコンストラクタを持つクラスをメンバに持つ
struct S3_1
{
	S3 member;
};

// defaultコンストラクタを持つクラスをメンバに持つ
struct S4_1
{
	S4 member;
};

// explicitなdefaultコンストラクタを持つクラスをメンバに持つ
struct S5_1
{
	S5 member;
};

// defaultコンストラクタを持つクラスをメンバに持つ
struct S6_1
{
	S6 member;
};

// explicitなdefaultコンストラクタを持つクラスをメンバに持つ
struct S7_1
{
	S7 member;
};

// defaultコンストラクタを持たないクラスを継承する
struct S1_2 : S1
{
};

// defaultコンストラクタがdeletedクラスを継承する
struct S2_2 : S2
{
};

// トリビアルなdefaultコンストラクタを持つクラスを継承する
struct S3_2 : S3
{
};

// defaultコンストラクタを持つクラスを継承する
struct S4_2 : S4
{
};

// explicitなdefaultコンストラクタを持つクラスを継承する
struct S5_2 : S5
{
};

// defaultコンストラクタを持つクラスを継承する
struct S6_2 : S6
{
};

// explicitなdefaultコンストラクタを持つクラスを継承する
struct S7_2 : S7
{
};

BKSGE_WARNING_POP()

GTEST_TEST(TypeTraitsTest, IsImplicitlyDefaultConstructibleTest)
{
	IntegralConstantTest<bksge::is_implicitly_default_constructible<S1>, false>();
	IntegralConstantTest<bksge::is_implicitly_default_constructible<S2>, false>();
	IntegralConstantTest<bksge::is_implicitly_default_constructible<S3>, true>();
	IntegralConstantTest<bksge::is_implicitly_default_constructible<S4>, true>();
	IntegralConstantTest<bksge::is_implicitly_default_constructible<S5>, false>();
	IntegralConstantTest<bksge::is_implicitly_default_constructible<S6>, true>();
	IntegralConstantTest<bksge::is_implicitly_default_constructible<S7>, false>();

	BKSGE_IS_IMPLICITLY_DEFAULT_CONSTRUCTIBLE_TEST(false, S1);
	BKSGE_IS_IMPLICITLY_DEFAULT_CONSTRUCTIBLE_TEST(false, S2);
	BKSGE_IS_IMPLICITLY_DEFAULT_CONSTRUCTIBLE_TEST(true,  S3);
	BKSGE_IS_IMPLICITLY_DEFAULT_CONSTRUCTIBLE_TEST(true,  S4);
	BKSGE_IS_IMPLICITLY_DEFAULT_CONSTRUCTIBLE_TEST(false, S5);
	BKSGE_IS_IMPLICITLY_DEFAULT_CONSTRUCTIBLE_TEST(true,  S6);
	BKSGE_IS_IMPLICITLY_DEFAULT_CONSTRUCTIBLE_TEST(false, S7);

	BKSGE_IS_IMPLICITLY_DEFAULT_CONSTRUCTIBLE_TEST(false, S1_1);
	BKSGE_IS_IMPLICITLY_DEFAULT_CONSTRUCTIBLE_TEST(false, S2_1);
	BKSGE_IS_IMPLICITLY_DEFAULT_CONSTRUCTIBLE_TEST(true,  S3_1);
	BKSGE_IS_IMPLICITLY_DEFAULT_CONSTRUCTIBLE_TEST(true,  S4_1);
#if !(defined(_MSC_VER) && _MSC_VER <= 1924)
	BKSGE_IS_IMPLICITLY_DEFAULT_CONSTRUCTIBLE_TEST(false, S5_1);
#endif
	BKSGE_IS_IMPLICITLY_DEFAULT_CONSTRUCTIBLE_TEST(true,  S6_1);
#if !(defined(_MSC_VER) && _MSC_VER <= 1924)
	BKSGE_IS_IMPLICITLY_DEFAULT_CONSTRUCTIBLE_TEST(false, S7_1);
#endif

	BKSGE_IS_IMPLICITLY_DEFAULT_CONSTRUCTIBLE_TEST(false, S1_2);
	BKSGE_IS_IMPLICITLY_DEFAULT_CONSTRUCTIBLE_TEST(false, S2_2);
	BKSGE_IS_IMPLICITLY_DEFAULT_CONSTRUCTIBLE_TEST(true,  S3_2);
	BKSGE_IS_IMPLICITLY_DEFAULT_CONSTRUCTIBLE_TEST(true,  S4_2);
#if 0
	BKSGE_IS_IMPLICITLY_DEFAULT_CONSTRUCTIBLE_TEST(false, S5_2);
#endif
	BKSGE_IS_IMPLICITLY_DEFAULT_CONSTRUCTIBLE_TEST(true,  S6_2);
#if 0
	BKSGE_IS_IMPLICITLY_DEFAULT_CONSTRUCTIBLE_TEST(false, S7_2);
#endif

	BKSGE_IS_IMPLICITLY_DEFAULT_CONSTRUCTIBLE_TEST(true,  int);
	BKSGE_IS_IMPLICITLY_DEFAULT_CONSTRUCTIBLE_TEST(true,  const int);
	BKSGE_IS_IMPLICITLY_DEFAULT_CONSTRUCTIBLE_TEST(true,  volatile int);
	BKSGE_IS_IMPLICITLY_DEFAULT_CONSTRUCTIBLE_TEST(true,  const volatile int);
	BKSGE_IS_IMPLICITLY_DEFAULT_CONSTRUCTIBLE_TEST(true,  int*);
	BKSGE_IS_IMPLICITLY_DEFAULT_CONSTRUCTIBLE_TEST(false, int&);
	BKSGE_IS_IMPLICITLY_DEFAULT_CONSTRUCTIBLE_TEST(false, int&&);
	BKSGE_IS_IMPLICITLY_DEFAULT_CONSTRUCTIBLE_TEST(true,  int[2]);
	BKSGE_IS_IMPLICITLY_DEFAULT_CONSTRUCTIBLE_TEST(false, int[]);
	BKSGE_IS_IMPLICITLY_DEFAULT_CONSTRUCTIBLE_TEST(false, int(&)[2]);
	BKSGE_IS_IMPLICITLY_DEFAULT_CONSTRUCTIBLE_TEST(false, int(&)[]);
	BKSGE_IS_IMPLICITLY_DEFAULT_CONSTRUCTIBLE_TEST(false, int(&&)[2]);
	BKSGE_IS_IMPLICITLY_DEFAULT_CONSTRUCTIBLE_TEST(false, int(&&)[]);

	BKSGE_IS_IMPLICITLY_DEFAULT_CONSTRUCTIBLE_TEST(false, void);
	BKSGE_IS_IMPLICITLY_DEFAULT_CONSTRUCTIBLE_TEST(false, const void);
	BKSGE_IS_IMPLICITLY_DEFAULT_CONSTRUCTIBLE_TEST(false, volatile void);
	BKSGE_IS_IMPLICITLY_DEFAULT_CONSTRUCTIBLE_TEST(false, const volatile void);

	BKSGE_IS_IMPLICITLY_DEFAULT_CONSTRUCTIBLE_TEST(true,  void*);
	BKSGE_IS_IMPLICITLY_DEFAULT_CONSTRUCTIBLE_TEST(true,  bksge::nullptr_t);
	BKSGE_IS_IMPLICITLY_DEFAULT_CONSTRUCTIBLE_TEST(true,  enum_UDT);
	BKSGE_IS_IMPLICITLY_DEFAULT_CONSTRUCTIBLE_TEST(true,  enum_class_UDT);
	BKSGE_IS_IMPLICITLY_DEFAULT_CONSTRUCTIBLE_TEST(true,  UDT);
	BKSGE_IS_IMPLICITLY_DEFAULT_CONSTRUCTIBLE_TEST(false, int_constructible);
	BKSGE_IS_IMPLICITLY_DEFAULT_CONSTRUCTIBLE_TEST(true,  int_convertible);
	BKSGE_IS_IMPLICITLY_DEFAULT_CONSTRUCTIBLE_TEST(false, test_abc1);
	BKSGE_IS_IMPLICITLY_DEFAULT_CONSTRUCTIBLE_TEST(false, test_abc2);
	BKSGE_IS_IMPLICITLY_DEFAULT_CONSTRUCTIBLE_TEST(false, test_abc3);
	BKSGE_IS_IMPLICITLY_DEFAULT_CONSTRUCTIBLE_TEST(true,  test_concrete1);
	BKSGE_IS_IMPLICITLY_DEFAULT_CONSTRUCTIBLE_TEST(true,  test_concrete2);
	BKSGE_IS_IMPLICITLY_DEFAULT_CONSTRUCTIBLE_TEST(true,  trivial_except_construct);
	BKSGE_IS_IMPLICITLY_DEFAULT_CONSTRUCTIBLE_TEST(true,  trivial_except_destroy);
	BKSGE_IS_IMPLICITLY_DEFAULT_CONSTRUCTIBLE_TEST(false, trivial_except_copy_ctor);
	BKSGE_IS_IMPLICITLY_DEFAULT_CONSTRUCTIBLE_TEST(true,  trivial_except_copy_assign);
	BKSGE_IS_IMPLICITLY_DEFAULT_CONSTRUCTIBLE_TEST(false, trivial_except_move_ctor);
	BKSGE_IS_IMPLICITLY_DEFAULT_CONSTRUCTIBLE_TEST(true,  trivial_except_move_assign);
	BKSGE_IS_IMPLICITLY_DEFAULT_CONSTRUCTIBLE_TEST(true,  f1);
	BKSGE_IS_IMPLICITLY_DEFAULT_CONSTRUCTIBLE_TEST(true,  f2);
	BKSGE_IS_IMPLICITLY_DEFAULT_CONSTRUCTIBLE_TEST(true,  f3);
	BKSGE_IS_IMPLICITLY_DEFAULT_CONSTRUCTIBLE_TEST(true,  mf1);
	BKSGE_IS_IMPLICITLY_DEFAULT_CONSTRUCTIBLE_TEST(true,  mf2);
	BKSGE_IS_IMPLICITLY_DEFAULT_CONSTRUCTIBLE_TEST(true,  mf3);
	BKSGE_IS_IMPLICITLY_DEFAULT_CONSTRUCTIBLE_TEST(true,  mf4);
	BKSGE_IS_IMPLICITLY_DEFAULT_CONSTRUCTIBLE_TEST(true,  mp);
	BKSGE_IS_IMPLICITLY_DEFAULT_CONSTRUCTIBLE_TEST(true,  cmf);
	BKSGE_IS_IMPLICITLY_DEFAULT_CONSTRUCTIBLE_TEST(false, foo0_t);
	BKSGE_IS_IMPLICITLY_DEFAULT_CONSTRUCTIBLE_TEST(false, foo1_t);
	BKSGE_IS_IMPLICITLY_DEFAULT_CONSTRUCTIBLE_TEST(false, foo2_t);
	BKSGE_IS_IMPLICITLY_DEFAULT_CONSTRUCTIBLE_TEST(false, foo3_t);
	BKSGE_IS_IMPLICITLY_DEFAULT_CONSTRUCTIBLE_TEST(false, foo4_t);
}

}	// namespace is_implicitly_default_constructible_test

}	// namespace bksge_type_traits_test

#undef BKSGE_IS_IMPLICITLY_DEFAULT_CONSTRUCTIBLE_TEST
