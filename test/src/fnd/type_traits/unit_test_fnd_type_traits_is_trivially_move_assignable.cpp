﻿/**
 *	@file	unit_test_fnd_type_traits_is_trivially_move_assignable.cpp
 *
 *	@brief	is_trivially_move_assignable のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/type_traits/is_trivially_move_assignable.hpp>
#include <gtest/gtest.h>
#include "type_traits_test_utility.hpp"

#define BKSGE_IS_TRIVIALLY_MOVE_ASSIGNABLE_TEST(b, T)	\
	static_assert(bksge::is_trivially_move_assignable<T>::value == b, #T ", " #b)

namespace bksge_type_traits_test
{

namespace is_trivially_move_assignable_test
{

// トリビアルなムーブ代入演算子を持つ
struct S1
{
	int n;
};

// 非トリビアルだが例外を投げないムーブ代入演算子を持つ
struct S2
{
	S2& operator=(S2&&) BKSGE_NOEXCEPT_OR_NOTHROW;
};

// 非トリビアルだが例外を投げないムーブ代入演算子を持つクラスをメンバに持つ
struct S3
{
	S2 member;
};

// ムーブ代入演算子が例外を投げる
struct S4
{
	S4& operator=(S4&&);
};

// ムーブ代入演算子が例外を投げる
struct S5
{
	S5& operator=(S5&&) BKSGE_NOEXCEPT_IF(false);
};

// ムーブ代入演算子を持たない
struct S6
{
	S6& operator=(S6&&) = delete;
};

GTEST_TEST(TypeTraitsTest, IsTriviallyMoveAssignableTest)
{
	IntegralConstantTest<bksge::is_trivially_move_assignable<S1>, true>();
	IntegralConstantTest<bksge::is_trivially_move_assignable<S2>, false>();
	IntegralConstantTest<bksge::is_trivially_move_assignable<S3>, false>();
	IntegralConstantTest<bksge::is_trivially_move_assignable<S4>, false>();
	IntegralConstantTest<bksge::is_trivially_move_assignable<S5>, false>();
	IntegralConstantTest<bksge::is_trivially_move_assignable<S6>, false>();

	BKSGE_IS_TRIVIALLY_MOVE_ASSIGNABLE_TEST(true,                 int);
	BKSGE_IS_TRIVIALLY_MOVE_ASSIGNABLE_TEST(false, const          int);
	BKSGE_IS_TRIVIALLY_MOVE_ASSIGNABLE_TEST(true,        volatile int);
	BKSGE_IS_TRIVIALLY_MOVE_ASSIGNABLE_TEST(false, const volatile int);
	BKSGE_IS_TRIVIALLY_MOVE_ASSIGNABLE_TEST(true,  int*);
	BKSGE_IS_TRIVIALLY_MOVE_ASSIGNABLE_TEST(true,  int&);
	BKSGE_IS_TRIVIALLY_MOVE_ASSIGNABLE_TEST(true,  int&&);
	BKSGE_IS_TRIVIALLY_MOVE_ASSIGNABLE_TEST(false, int[2]);
	BKSGE_IS_TRIVIALLY_MOVE_ASSIGNABLE_TEST(false, int[]);
	BKSGE_IS_TRIVIALLY_MOVE_ASSIGNABLE_TEST(false, int(&)[2]);
	BKSGE_IS_TRIVIALLY_MOVE_ASSIGNABLE_TEST(false, int(&)[]);
	BKSGE_IS_TRIVIALLY_MOVE_ASSIGNABLE_TEST(false, int(&&)[2]);
	BKSGE_IS_TRIVIALLY_MOVE_ASSIGNABLE_TEST(false, int(&&)[]);

	BKSGE_IS_TRIVIALLY_MOVE_ASSIGNABLE_TEST(false,                void);
	BKSGE_IS_TRIVIALLY_MOVE_ASSIGNABLE_TEST(false, const          void);
	BKSGE_IS_TRIVIALLY_MOVE_ASSIGNABLE_TEST(false,       volatile void);
	BKSGE_IS_TRIVIALLY_MOVE_ASSIGNABLE_TEST(false, const volatile void);

	BKSGE_IS_TRIVIALLY_MOVE_ASSIGNABLE_TEST(false,                UDT);
	BKSGE_IS_TRIVIALLY_MOVE_ASSIGNABLE_TEST(false, const          UDT);
	BKSGE_IS_TRIVIALLY_MOVE_ASSIGNABLE_TEST(false,       volatile UDT);
	BKSGE_IS_TRIVIALLY_MOVE_ASSIGNABLE_TEST(false, const volatile UDT);
	BKSGE_IS_TRIVIALLY_MOVE_ASSIGNABLE_TEST(true,  UDT*);
	BKSGE_IS_TRIVIALLY_MOVE_ASSIGNABLE_TEST(false, UDT&);
	BKSGE_IS_TRIVIALLY_MOVE_ASSIGNABLE_TEST(false, UDT&&);
	BKSGE_IS_TRIVIALLY_MOVE_ASSIGNABLE_TEST(false, UDT[2]);
	BKSGE_IS_TRIVIALLY_MOVE_ASSIGNABLE_TEST(false, UDT[]);
	BKSGE_IS_TRIVIALLY_MOVE_ASSIGNABLE_TEST(false, UDT(&)[2]);
	BKSGE_IS_TRIVIALLY_MOVE_ASSIGNABLE_TEST(false, UDT(&)[]);
	BKSGE_IS_TRIVIALLY_MOVE_ASSIGNABLE_TEST(false, UDT(&&)[2]);
	BKSGE_IS_TRIVIALLY_MOVE_ASSIGNABLE_TEST(false, UDT(&&)[]);

	BKSGE_IS_TRIVIALLY_MOVE_ASSIGNABLE_TEST(true,                 POD_UDT);
	BKSGE_IS_TRIVIALLY_MOVE_ASSIGNABLE_TEST(false, const          POD_UDT);
	BKSGE_IS_TRIVIALLY_MOVE_ASSIGNABLE_TEST(false,       volatile POD_UDT);
	BKSGE_IS_TRIVIALLY_MOVE_ASSIGNABLE_TEST(false, const volatile POD_UDT);
	BKSGE_IS_TRIVIALLY_MOVE_ASSIGNABLE_TEST(true,  POD_UDT*);
	BKSGE_IS_TRIVIALLY_MOVE_ASSIGNABLE_TEST(true,  POD_UDT&);
	BKSGE_IS_TRIVIALLY_MOVE_ASSIGNABLE_TEST(true,  POD_UDT&&);
	BKSGE_IS_TRIVIALLY_MOVE_ASSIGNABLE_TEST(false, POD_UDT[2]);
	BKSGE_IS_TRIVIALLY_MOVE_ASSIGNABLE_TEST(false, POD_UDT[]);
	BKSGE_IS_TRIVIALLY_MOVE_ASSIGNABLE_TEST(false, POD_UDT(&)[2]);
	BKSGE_IS_TRIVIALLY_MOVE_ASSIGNABLE_TEST(false, POD_UDT(&)[]);
	BKSGE_IS_TRIVIALLY_MOVE_ASSIGNABLE_TEST(false, POD_UDT(&&)[2]);
	BKSGE_IS_TRIVIALLY_MOVE_ASSIGNABLE_TEST(false, POD_UDT(&&)[]);

	BKSGE_IS_TRIVIALLY_MOVE_ASSIGNABLE_TEST(true,  trivial_except_construct);
	BKSGE_IS_TRIVIALLY_MOVE_ASSIGNABLE_TEST(true,  trivial_except_destroy);
	BKSGE_IS_TRIVIALLY_MOVE_ASSIGNABLE_TEST(true,  trivial_except_copy_ctor);
	BKSGE_IS_TRIVIALLY_MOVE_ASSIGNABLE_TEST(false, trivial_except_copy_assign);
	BKSGE_IS_TRIVIALLY_MOVE_ASSIGNABLE_TEST(false, trivial_except_move_ctor);
	BKSGE_IS_TRIVIALLY_MOVE_ASSIGNABLE_TEST(false, trivial_except_move_ctor&);
	BKSGE_IS_TRIVIALLY_MOVE_ASSIGNABLE_TEST(false, trivial_except_move_ctor&&);
	BKSGE_IS_TRIVIALLY_MOVE_ASSIGNABLE_TEST(false, trivial_except_move_assign);
	BKSGE_IS_TRIVIALLY_MOVE_ASSIGNABLE_TEST(false, trivial_except_move_assign&);
	BKSGE_IS_TRIVIALLY_MOVE_ASSIGNABLE_TEST(false, trivial_except_move_assign&&);

	BKSGE_IS_TRIVIALLY_MOVE_ASSIGNABLE_TEST(true,  f1);
	BKSGE_IS_TRIVIALLY_MOVE_ASSIGNABLE_TEST(true,  f2);
	BKSGE_IS_TRIVIALLY_MOVE_ASSIGNABLE_TEST(true,  f3);
	BKSGE_IS_TRIVIALLY_MOVE_ASSIGNABLE_TEST(true,  mf1);
	BKSGE_IS_TRIVIALLY_MOVE_ASSIGNABLE_TEST(true,  mf2);
	BKSGE_IS_TRIVIALLY_MOVE_ASSIGNABLE_TEST(true,  mf3);
	BKSGE_IS_TRIVIALLY_MOVE_ASSIGNABLE_TEST(true,  mf4);
	BKSGE_IS_TRIVIALLY_MOVE_ASSIGNABLE_TEST(true,  mp);
	BKSGE_IS_TRIVIALLY_MOVE_ASSIGNABLE_TEST(true,  cmf);
	BKSGE_IS_TRIVIALLY_MOVE_ASSIGNABLE_TEST(false, foo0_t);
	BKSGE_IS_TRIVIALLY_MOVE_ASSIGNABLE_TEST(false, foo1_t);
	BKSGE_IS_TRIVIALLY_MOVE_ASSIGNABLE_TEST(false, foo2_t);
	BKSGE_IS_TRIVIALLY_MOVE_ASSIGNABLE_TEST(false, foo3_t);
	BKSGE_IS_TRIVIALLY_MOVE_ASSIGNABLE_TEST(false, foo4_t);
}

}	// namespace is_trivially_move_assignable_test

}	// namespace bksge_type_traits_test

#undef BKSGE_IS_TRIVIALLY_MOVE_ASSIGNABLE_TEST