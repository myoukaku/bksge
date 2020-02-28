/**
 *	@file	unit_test_fnd_type_traits_is_implicitly_copy_constructible.cpp
 *
 *	@brief	is_implicitly_copy_constructible のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/type_traits/is_implicitly_copy_constructible.hpp>
#include <gtest/gtest.h>
#include "type_traits_test_utility.hpp"

#define BKSGE_IS_IMPLICITLY_COPY_CONSTRUCTIBLE_TEST(b, T)	\
	static_assert(bksge::is_implicitly_copy_constructible<T>::value == b, #T ", " #b)

namespace bksge_type_traits_test
{

namespace is_implicitly_copy_constructible_test
{

// トリビアルな copy コンストラクタを持つ
struct Trivial
{
	int n;
};

// implicit な copy コンストラクタを持つ
struct Implicit
{
	Implicit(const Implicit&);
};

// implicit な copy コンストラクタを持つクラスをメンバに持つ
struct ImplicitMember
{
	Implicit	member;
};

// explicit な copy コンストラクタを持つ
struct Explicit
{
	explicit Explicit(const Explicit&);
};

// explicit な copy コンストラクタを持つクラスをメンバに持つ
struct ExplicitMember
{
	Explicit	member;
};

// copyコンストラクタを持たない
struct NonCopyable
{
	NonCopyable(const NonCopyable&) = delete;
};

// copyコンストラクタを持たないクラスをメンバに持つ
struct NonCopyableMember
{
	NonCopyable	member;
};

GTEST_TEST(TypeTraitsTest, IsImplicitlyCopyConstructibleTest)
{
	IntegralConstantTest<bksge::is_implicitly_copy_constructible<Trivial>,           true>();
	IntegralConstantTest<bksge::is_implicitly_copy_constructible<Implicit>,          true>();
	IntegralConstantTest<bksge::is_implicitly_copy_constructible<ImplicitMember>,    true>();
	IntegralConstantTest<bksge::is_implicitly_copy_constructible<Explicit>,          false>();
	IntegralConstantTest<bksge::is_implicitly_copy_constructible<ExplicitMember>,    true>();
	IntegralConstantTest<bksge::is_implicitly_copy_constructible<NonCopyable>,       false>();
	IntegralConstantTest<bksge::is_implicitly_copy_constructible<NonCopyableMember>, false>();

	BKSGE_IS_IMPLICITLY_COPY_CONSTRUCTIBLE_TEST(true,	               int);
	BKSGE_IS_IMPLICITLY_COPY_CONSTRUCTIBLE_TEST(true,	const          int);
	BKSGE_IS_IMPLICITLY_COPY_CONSTRUCTIBLE_TEST(true,	      volatile int);
	BKSGE_IS_IMPLICITLY_COPY_CONSTRUCTIBLE_TEST(true,	const volatile int);
	BKSGE_IS_IMPLICITLY_COPY_CONSTRUCTIBLE_TEST(true,	int*);
	BKSGE_IS_IMPLICITLY_COPY_CONSTRUCTIBLE_TEST(true,	int&);
	BKSGE_IS_IMPLICITLY_COPY_CONSTRUCTIBLE_TEST(false,	int&&);
	BKSGE_IS_IMPLICITLY_COPY_CONSTRUCTIBLE_TEST(false,	int[2]);
	BKSGE_IS_IMPLICITLY_COPY_CONSTRUCTIBLE_TEST(false,	int[]);
	BKSGE_IS_IMPLICITLY_COPY_CONSTRUCTIBLE_TEST(true,	int(&)[2]);
	BKSGE_IS_IMPLICITLY_COPY_CONSTRUCTIBLE_TEST(true,	int(&)[]);
	BKSGE_IS_IMPLICITLY_COPY_CONSTRUCTIBLE_TEST(false,	int(&&)[2]);
	BKSGE_IS_IMPLICITLY_COPY_CONSTRUCTIBLE_TEST(false,	int(&&)[]);

	BKSGE_IS_IMPLICITLY_COPY_CONSTRUCTIBLE_TEST(false,                void);
	BKSGE_IS_IMPLICITLY_COPY_CONSTRUCTIBLE_TEST(false, const          void);
	BKSGE_IS_IMPLICITLY_COPY_CONSTRUCTIBLE_TEST(false,       volatile void);
	BKSGE_IS_IMPLICITLY_COPY_CONSTRUCTIBLE_TEST(false, const volatile void);

	BKSGE_IS_IMPLICITLY_COPY_CONSTRUCTIBLE_TEST(true,	               UDT);
	BKSGE_IS_IMPLICITLY_COPY_CONSTRUCTIBLE_TEST(true,	const          UDT);
	BKSGE_IS_IMPLICITLY_COPY_CONSTRUCTIBLE_TEST(false,	      volatile UDT);
	BKSGE_IS_IMPLICITLY_COPY_CONSTRUCTIBLE_TEST(false,	const volatile UDT);
	BKSGE_IS_IMPLICITLY_COPY_CONSTRUCTIBLE_TEST(true,	UDT*);
	BKSGE_IS_IMPLICITLY_COPY_CONSTRUCTIBLE_TEST(true,	UDT&);
	BKSGE_IS_IMPLICITLY_COPY_CONSTRUCTIBLE_TEST(false,	UDT&&);
	BKSGE_IS_IMPLICITLY_COPY_CONSTRUCTIBLE_TEST(false,	UDT[2]);
	BKSGE_IS_IMPLICITLY_COPY_CONSTRUCTIBLE_TEST(false,	UDT[]);
	BKSGE_IS_IMPLICITLY_COPY_CONSTRUCTIBLE_TEST(true,	UDT(&)[2]);
	BKSGE_IS_IMPLICITLY_COPY_CONSTRUCTIBLE_TEST(true,	UDT(&)[]);
	BKSGE_IS_IMPLICITLY_COPY_CONSTRUCTIBLE_TEST(false,	UDT(&&)[2]);
	BKSGE_IS_IMPLICITLY_COPY_CONSTRUCTIBLE_TEST(false,	UDT(&&)[]);

	BKSGE_IS_IMPLICITLY_COPY_CONSTRUCTIBLE_TEST(true,                 Implicit);
	BKSGE_IS_IMPLICITLY_COPY_CONSTRUCTIBLE_TEST(true,  const          Implicit);
	BKSGE_IS_IMPLICITLY_COPY_CONSTRUCTIBLE_TEST(false,       volatile Implicit);
	BKSGE_IS_IMPLICITLY_COPY_CONSTRUCTIBLE_TEST(false, const volatile Implicit);
	BKSGE_IS_IMPLICITLY_COPY_CONSTRUCTIBLE_TEST(true,  Implicit*);
	BKSGE_IS_IMPLICITLY_COPY_CONSTRUCTIBLE_TEST(true,  Implicit&);
	BKSGE_IS_IMPLICITLY_COPY_CONSTRUCTIBLE_TEST(false, Implicit&&);
	BKSGE_IS_IMPLICITLY_COPY_CONSTRUCTIBLE_TEST(false, Implicit[2]);
	BKSGE_IS_IMPLICITLY_COPY_CONSTRUCTIBLE_TEST(false, Implicit[]);
	BKSGE_IS_IMPLICITLY_COPY_CONSTRUCTIBLE_TEST(true,  Implicit(&)[2]);
	BKSGE_IS_IMPLICITLY_COPY_CONSTRUCTIBLE_TEST(true,  Implicit(&)[]);
	BKSGE_IS_IMPLICITLY_COPY_CONSTRUCTIBLE_TEST(false, Implicit(&&)[2]);
	BKSGE_IS_IMPLICITLY_COPY_CONSTRUCTIBLE_TEST(false, Implicit(&&)[]);

	BKSGE_IS_IMPLICITLY_COPY_CONSTRUCTIBLE_TEST(false,                Explicit);
	BKSGE_IS_IMPLICITLY_COPY_CONSTRUCTIBLE_TEST(false, const          Explicit);
	BKSGE_IS_IMPLICITLY_COPY_CONSTRUCTIBLE_TEST(false,       volatile Explicit);
	BKSGE_IS_IMPLICITLY_COPY_CONSTRUCTIBLE_TEST(false, const volatile Explicit);
	BKSGE_IS_IMPLICITLY_COPY_CONSTRUCTIBLE_TEST(true,  Explicit*);
	BKSGE_IS_IMPLICITLY_COPY_CONSTRUCTIBLE_TEST(true,  Explicit&);
	BKSGE_IS_IMPLICITLY_COPY_CONSTRUCTIBLE_TEST(false, Explicit&&);
	BKSGE_IS_IMPLICITLY_COPY_CONSTRUCTIBLE_TEST(false, Explicit[2]);
	BKSGE_IS_IMPLICITLY_COPY_CONSTRUCTIBLE_TEST(false, Explicit[]);
	BKSGE_IS_IMPLICITLY_COPY_CONSTRUCTIBLE_TEST(true,  Explicit(&)[2]);
	BKSGE_IS_IMPLICITLY_COPY_CONSTRUCTIBLE_TEST(true,  Explicit(&)[]);
	BKSGE_IS_IMPLICITLY_COPY_CONSTRUCTIBLE_TEST(false, Explicit(&&)[2]);
	BKSGE_IS_IMPLICITLY_COPY_CONSTRUCTIBLE_TEST(false, Explicit(&&)[]);

	BKSGE_IS_IMPLICITLY_COPY_CONSTRUCTIBLE_TEST(true, trivial_except_construct);
	BKSGE_IS_IMPLICITLY_COPY_CONSTRUCTIBLE_TEST(true, trivial_except_destroy);
	BKSGE_IS_IMPLICITLY_COPY_CONSTRUCTIBLE_TEST(true, trivial_except_copy_ctor);
	BKSGE_IS_IMPLICITLY_COPY_CONSTRUCTIBLE_TEST(true, trivial_except_copy_assign);
	BKSGE_IS_IMPLICITLY_COPY_CONSTRUCTIBLE_TEST(false, trivial_except_move_ctor);
	BKSGE_IS_IMPLICITLY_COPY_CONSTRUCTIBLE_TEST(false, trivial_except_move_assign);

	BKSGE_IS_IMPLICITLY_COPY_CONSTRUCTIBLE_TEST(true, f1);
	BKSGE_IS_IMPLICITLY_COPY_CONSTRUCTIBLE_TEST(true, f2);
	BKSGE_IS_IMPLICITLY_COPY_CONSTRUCTIBLE_TEST(true, f3);
	BKSGE_IS_IMPLICITLY_COPY_CONSTRUCTIBLE_TEST(true, mf1);
	BKSGE_IS_IMPLICITLY_COPY_CONSTRUCTIBLE_TEST(true, mf2);
	BKSGE_IS_IMPLICITLY_COPY_CONSTRUCTIBLE_TEST(true, mf3);
	BKSGE_IS_IMPLICITLY_COPY_CONSTRUCTIBLE_TEST(true, mf4);
	BKSGE_IS_IMPLICITLY_COPY_CONSTRUCTIBLE_TEST(true, mp);
	BKSGE_IS_IMPLICITLY_COPY_CONSTRUCTIBLE_TEST(true, cmf);
	BKSGE_IS_IMPLICITLY_COPY_CONSTRUCTIBLE_TEST(false, foo0_t);
	BKSGE_IS_IMPLICITLY_COPY_CONSTRUCTIBLE_TEST(false, foo1_t);
	BKSGE_IS_IMPLICITLY_COPY_CONSTRUCTIBLE_TEST(false, foo2_t);
	BKSGE_IS_IMPLICITLY_COPY_CONSTRUCTIBLE_TEST(false, foo3_t);
	BKSGE_IS_IMPLICITLY_COPY_CONSTRUCTIBLE_TEST(false, foo4_t);
}

}	// namespace is_implicitly_copy_constructible_test

}	// namespace bksge_type_traits_test

#undef BKSGE_IS_IMPLICITLY_COPY_CONSTRUCTIBLE_TEST
