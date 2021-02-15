/**
 *	@file	unit_test_fnd_type_traits_is_trivially_copy_assignable.cpp
 *
 *	@brief	is_trivially_copy_assignable のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/type_traits/is_trivially_copy_assignable.hpp>
#include <bksge/fnd/config.hpp>
#include <gtest/gtest.h>
#include "type_traits_test_utility.hpp"

#if defined(BKSGE_HAS_CXX14_VARIABLE_TEMPLATES)

#define BKSGE_IS_TRIVIALLY_COPY_ASSIGNABLE_TEST(b, T)	\
	static_assert(bksge::is_trivially_copy_assignable_v<T>      == b, #T ", " #b);	\
	static_assert(bksge::is_trivially_copy_assignable<T>::value == b, #T ", " #b);	\
	static_assert(bksge::is_trivially_copy_assignable<T>()      == b, #T ", " #b)

#else

#define BKSGE_IS_TRIVIALLY_COPY_ASSIGNABLE_TEST(b, T)	\
	static_assert(bksge::is_trivially_copy_assignable<T>::value == b, #T ", " #b);	\
	static_assert(bksge::is_trivially_copy_assignable<T>()      == b, #T ", " #b)

#endif

namespace bksge_type_traits_test
{

namespace is_trivially_copy_assignable_test
{

// トリビアルなコピー代入演算子を持つ
struct S1
{
	int n;
};

// 非トリビアルだが例外を投げないコピー代入演算子を持つ
struct S2
{
	S2& operator=(const S2&) BKSGE_NOEXCEPT_OR_NOTHROW;
};

// 非トリビアルだが例外を投げないコピー代入演算子を持つクラスをメンバに持つ
struct S3
{
	S2 member;
};

// コピー代入演算子が例外を投げる
struct S4
{
	S4& operator=(const S4&);
};

// コピー代入演算子が例外を投げる
struct S5
{
	S5& operator=(const S5&) BKSGE_NOEXCEPT_IF(false);
};

// コピー代入演算子を持たない
struct S6
{
	S6& operator=(const S6&) = delete;
};

BKSGE_IS_TRIVIALLY_COPY_ASSIGNABLE_TEST(true,  S1);
BKSGE_IS_TRIVIALLY_COPY_ASSIGNABLE_TEST(false, S2);
BKSGE_IS_TRIVIALLY_COPY_ASSIGNABLE_TEST(false, S3);
BKSGE_IS_TRIVIALLY_COPY_ASSIGNABLE_TEST(false, S4);
BKSGE_IS_TRIVIALLY_COPY_ASSIGNABLE_TEST(false, S5);
BKSGE_IS_TRIVIALLY_COPY_ASSIGNABLE_TEST(false, S6);

BKSGE_IS_TRIVIALLY_COPY_ASSIGNABLE_TEST(true,                 int);
BKSGE_IS_TRIVIALLY_COPY_ASSIGNABLE_TEST(false, const          int);
BKSGE_IS_TRIVIALLY_COPY_ASSIGNABLE_TEST(true,        volatile int);
BKSGE_IS_TRIVIALLY_COPY_ASSIGNABLE_TEST(false, const volatile int);
BKSGE_IS_TRIVIALLY_COPY_ASSIGNABLE_TEST(true,  int*);
BKSGE_IS_TRIVIALLY_COPY_ASSIGNABLE_TEST(true,  int&);
BKSGE_IS_TRIVIALLY_COPY_ASSIGNABLE_TEST(true,  int&&);
BKSGE_IS_TRIVIALLY_COPY_ASSIGNABLE_TEST(false, int[2]);
BKSGE_IS_TRIVIALLY_COPY_ASSIGNABLE_TEST(false, int[]);
BKSGE_IS_TRIVIALLY_COPY_ASSIGNABLE_TEST(false, int(&)[2]);
BKSGE_IS_TRIVIALLY_COPY_ASSIGNABLE_TEST(false, int(&)[]);
BKSGE_IS_TRIVIALLY_COPY_ASSIGNABLE_TEST(false, int(&&)[2]);
BKSGE_IS_TRIVIALLY_COPY_ASSIGNABLE_TEST(false, int(&&)[]);

BKSGE_IS_TRIVIALLY_COPY_ASSIGNABLE_TEST(false,                void);
BKSGE_IS_TRIVIALLY_COPY_ASSIGNABLE_TEST(false, const          void);
BKSGE_IS_TRIVIALLY_COPY_ASSIGNABLE_TEST(false,       volatile void);
BKSGE_IS_TRIVIALLY_COPY_ASSIGNABLE_TEST(false, const volatile void);

BKSGE_IS_TRIVIALLY_COPY_ASSIGNABLE_TEST(false,                UDT);
BKSGE_IS_TRIVIALLY_COPY_ASSIGNABLE_TEST(false, const          UDT);
BKSGE_IS_TRIVIALLY_COPY_ASSIGNABLE_TEST(false,       volatile UDT);
BKSGE_IS_TRIVIALLY_COPY_ASSIGNABLE_TEST(false, const volatile UDT);
BKSGE_IS_TRIVIALLY_COPY_ASSIGNABLE_TEST(true,  UDT*);
BKSGE_IS_TRIVIALLY_COPY_ASSIGNABLE_TEST(false, UDT&);
BKSGE_IS_TRIVIALLY_COPY_ASSIGNABLE_TEST(false, UDT&&);
BKSGE_IS_TRIVIALLY_COPY_ASSIGNABLE_TEST(false, UDT[2]);
BKSGE_IS_TRIVIALLY_COPY_ASSIGNABLE_TEST(false, UDT[]);
BKSGE_IS_TRIVIALLY_COPY_ASSIGNABLE_TEST(false, UDT(&)[2]);
BKSGE_IS_TRIVIALLY_COPY_ASSIGNABLE_TEST(false, UDT(&)[]);
BKSGE_IS_TRIVIALLY_COPY_ASSIGNABLE_TEST(false, UDT(&&)[2]);
BKSGE_IS_TRIVIALLY_COPY_ASSIGNABLE_TEST(false, UDT(&&)[]);

BKSGE_IS_TRIVIALLY_COPY_ASSIGNABLE_TEST(true,                 POD_UDT);
BKSGE_IS_TRIVIALLY_COPY_ASSIGNABLE_TEST(false, const          POD_UDT);
BKSGE_IS_TRIVIALLY_COPY_ASSIGNABLE_TEST(false,       volatile POD_UDT);
BKSGE_IS_TRIVIALLY_COPY_ASSIGNABLE_TEST(false, const volatile POD_UDT);
BKSGE_IS_TRIVIALLY_COPY_ASSIGNABLE_TEST(true,  POD_UDT*);
BKSGE_IS_TRIVIALLY_COPY_ASSIGNABLE_TEST(true,  POD_UDT&);
BKSGE_IS_TRIVIALLY_COPY_ASSIGNABLE_TEST(true,  POD_UDT&&);
BKSGE_IS_TRIVIALLY_COPY_ASSIGNABLE_TEST(false, POD_UDT[2]);
BKSGE_IS_TRIVIALLY_COPY_ASSIGNABLE_TEST(false, POD_UDT[]);
BKSGE_IS_TRIVIALLY_COPY_ASSIGNABLE_TEST(false, POD_UDT(&)[2]);
BKSGE_IS_TRIVIALLY_COPY_ASSIGNABLE_TEST(false, POD_UDT(&)[]);
BKSGE_IS_TRIVIALLY_COPY_ASSIGNABLE_TEST(false, POD_UDT(&&)[2]);
BKSGE_IS_TRIVIALLY_COPY_ASSIGNABLE_TEST(false, POD_UDT(&&)[]);

BKSGE_IS_TRIVIALLY_COPY_ASSIGNABLE_TEST(true,  trivial_except_construct);
BKSGE_IS_TRIVIALLY_COPY_ASSIGNABLE_TEST(true,  trivial_except_destroy);
BKSGE_IS_TRIVIALLY_COPY_ASSIGNABLE_TEST(true,  trivial_except_copy_ctor);
BKSGE_IS_TRIVIALLY_COPY_ASSIGNABLE_TEST(false, trivial_except_copy_assign);
BKSGE_IS_TRIVIALLY_COPY_ASSIGNABLE_TEST(false, trivial_except_move_ctor);
BKSGE_IS_TRIVIALLY_COPY_ASSIGNABLE_TEST(false, trivial_except_move_assign);

BKSGE_IS_TRIVIALLY_COPY_ASSIGNABLE_TEST(true,  f1);
BKSGE_IS_TRIVIALLY_COPY_ASSIGNABLE_TEST(true,  f2);
BKSGE_IS_TRIVIALLY_COPY_ASSIGNABLE_TEST(true,  f3);
BKSGE_IS_TRIVIALLY_COPY_ASSIGNABLE_TEST(true,  mf1);
BKSGE_IS_TRIVIALLY_COPY_ASSIGNABLE_TEST(true,  mf2);
BKSGE_IS_TRIVIALLY_COPY_ASSIGNABLE_TEST(true,  mf3);
BKSGE_IS_TRIVIALLY_COPY_ASSIGNABLE_TEST(true,  mf4);
BKSGE_IS_TRIVIALLY_COPY_ASSIGNABLE_TEST(true,  mp);
BKSGE_IS_TRIVIALLY_COPY_ASSIGNABLE_TEST(true,  cmf);
BKSGE_IS_TRIVIALLY_COPY_ASSIGNABLE_TEST(false, foo0_t);
BKSGE_IS_TRIVIALLY_COPY_ASSIGNABLE_TEST(false, foo1_t);
BKSGE_IS_TRIVIALLY_COPY_ASSIGNABLE_TEST(false, foo2_t);
BKSGE_IS_TRIVIALLY_COPY_ASSIGNABLE_TEST(false, foo3_t);
BKSGE_IS_TRIVIALLY_COPY_ASSIGNABLE_TEST(false, foo4_t);

}	// namespace is_trivially_copy_assignable_test

}	// namespace bksge_type_traits_test

#undef BKSGE_IS_TRIVIALLY_COPY_ASSIGNABLE_TEST
