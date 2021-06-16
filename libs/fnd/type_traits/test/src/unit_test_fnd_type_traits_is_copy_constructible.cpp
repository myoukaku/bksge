/**
 *	@file	unit_test_fnd_type_traits_is_copy_constructible.cpp
 *
 *	@brief	is_copy_constructible のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/type_traits/is_copy_constructible.hpp>
#include <bksge/fnd/config.hpp>
#include <gtest/gtest.h>
#include "type_traits_test_utility.hpp"

BKSGE_WARNING_PUSH()
BKSGE_WARNING_DISABLE_MSVC(4510 4610)

#if defined(BKSGE_HAS_CXX14_VARIABLE_TEMPLATES)

#define BKSGE_IS_COPY_CONSTRUCTIBLE_TEST(b, T)	\
	static_assert(bksge::is_copy_constructible_v<T>      == b, #T ", " #b);	\
	static_assert(bksge::is_copy_constructible<T>::value == b, #T ", " #b);	\
	static_assert(bksge::is_copy_constructible<T>()      == b, #T ", " #b)

#else

#define BKSGE_IS_COPY_CONSTRUCTIBLE_TEST(b, T)	\
	static_assert(bksge::is_copy_constructible<T>::value == b, #T ", " #b);	\
	static_assert(bksge::is_copy_constructible<T>()      == b, #T ", " #b)

#endif

namespace bksge_type_traits_test
{

namespace is_copy_constructible_test
{

// トリビアルなcopyコンストラクタを持つ
struct S1
{
	int n;
};

// 非トリビアルだが例外を投げないcopyコンストラクタを持つ
struct S2
{
	S2() = default;
	S2(const S2&) BKSGE_NOEXCEPT_OR_NOTHROW;
	S2(S2&&);
};

// 非トリビアルだが例外を投げないcopyコンストラクタを持つクラスをメンバに持つ
struct S3
{
	S2 member;
};

// copyコンストラクタが例外を投げる
struct S4
{
	S4(const S4&) {}
};

// copyコンストラクタを持たない
struct S5
{
	S5(const S5&) = delete;
};

// copyコンストラクタを持たないクラスをメンバに持つ
struct S6
{
	S5	member;
};

BKSGE_IS_COPY_CONSTRUCTIBLE_TEST(true,  S1);
BKSGE_IS_COPY_CONSTRUCTIBLE_TEST(true,  S2);
BKSGE_IS_COPY_CONSTRUCTIBLE_TEST(true,  S3);
BKSGE_IS_COPY_CONSTRUCTIBLE_TEST(true,  S4);
BKSGE_IS_COPY_CONSTRUCTIBLE_TEST(false, S5);
BKSGE_IS_COPY_CONSTRUCTIBLE_TEST(false, S6);

BKSGE_IS_COPY_CONSTRUCTIBLE_TEST(true,	               int);
BKSGE_IS_COPY_CONSTRUCTIBLE_TEST(true,	const          int);
BKSGE_IS_COPY_CONSTRUCTIBLE_TEST(true,	      volatile int);
BKSGE_IS_COPY_CONSTRUCTIBLE_TEST(true,	const volatile int);
BKSGE_IS_COPY_CONSTRUCTIBLE_TEST(true,	int*);
BKSGE_IS_COPY_CONSTRUCTIBLE_TEST(true,	int&);
BKSGE_IS_COPY_CONSTRUCTIBLE_TEST(false,	int&&);
BKSGE_IS_COPY_CONSTRUCTIBLE_TEST(false,	int[2]);
BKSGE_IS_COPY_CONSTRUCTIBLE_TEST(false,	int[]);
BKSGE_IS_COPY_CONSTRUCTIBLE_TEST(true,	int(&)[2]);
BKSGE_IS_COPY_CONSTRUCTIBLE_TEST(true,	int(&)[]);
BKSGE_IS_COPY_CONSTRUCTIBLE_TEST(false,	int(&&)[2]);
BKSGE_IS_COPY_CONSTRUCTIBLE_TEST(false,	int(&&)[]);

BKSGE_IS_COPY_CONSTRUCTIBLE_TEST(false,                void);
BKSGE_IS_COPY_CONSTRUCTIBLE_TEST(false, const          void);
BKSGE_IS_COPY_CONSTRUCTIBLE_TEST(false,       volatile void);
BKSGE_IS_COPY_CONSTRUCTIBLE_TEST(false, const volatile void);

BKSGE_IS_COPY_CONSTRUCTIBLE_TEST(true,	               UDT);
BKSGE_IS_COPY_CONSTRUCTIBLE_TEST(true,	const          UDT);
BKSGE_IS_COPY_CONSTRUCTIBLE_TEST(false,	      volatile UDT);
BKSGE_IS_COPY_CONSTRUCTIBLE_TEST(false,	const volatile UDT);
BKSGE_IS_COPY_CONSTRUCTIBLE_TEST(true,	UDT*);
BKSGE_IS_COPY_CONSTRUCTIBLE_TEST(true,	UDT&);
BKSGE_IS_COPY_CONSTRUCTIBLE_TEST(false,	UDT&&);
BKSGE_IS_COPY_CONSTRUCTIBLE_TEST(false,	UDT[2]);
BKSGE_IS_COPY_CONSTRUCTIBLE_TEST(false,	UDT[]);
BKSGE_IS_COPY_CONSTRUCTIBLE_TEST(true,	UDT(&)[2]);
BKSGE_IS_COPY_CONSTRUCTIBLE_TEST(true,	UDT(&)[]);
BKSGE_IS_COPY_CONSTRUCTIBLE_TEST(false,	UDT(&&)[2]);
BKSGE_IS_COPY_CONSTRUCTIBLE_TEST(false,	UDT(&&)[]);

BKSGE_IS_COPY_CONSTRUCTIBLE_TEST(true, trivial_except_construct);
BKSGE_IS_COPY_CONSTRUCTIBLE_TEST(true, trivial_except_destroy);
BKSGE_IS_COPY_CONSTRUCTIBLE_TEST(true, trivial_except_copy_ctor);
BKSGE_IS_COPY_CONSTRUCTIBLE_TEST(true, trivial_except_copy_assign);
BKSGE_IS_COPY_CONSTRUCTIBLE_TEST(false, trivial_except_move_ctor);
BKSGE_IS_COPY_CONSTRUCTIBLE_TEST(false, trivial_except_move_assign);

BKSGE_IS_COPY_CONSTRUCTIBLE_TEST(true, f1);
BKSGE_IS_COPY_CONSTRUCTIBLE_TEST(true, f2);
BKSGE_IS_COPY_CONSTRUCTIBLE_TEST(true, f3);
BKSGE_IS_COPY_CONSTRUCTIBLE_TEST(true, mf1);
BKSGE_IS_COPY_CONSTRUCTIBLE_TEST(true, mf2);
BKSGE_IS_COPY_CONSTRUCTIBLE_TEST(true, mf3);
BKSGE_IS_COPY_CONSTRUCTIBLE_TEST(true, mf4);
BKSGE_IS_COPY_CONSTRUCTIBLE_TEST(true, mp);
BKSGE_IS_COPY_CONSTRUCTIBLE_TEST(true, cmf);
BKSGE_IS_COPY_CONSTRUCTIBLE_TEST(false, foo0_t);
BKSGE_IS_COPY_CONSTRUCTIBLE_TEST(false, foo1_t);
BKSGE_IS_COPY_CONSTRUCTIBLE_TEST(false, foo2_t);
BKSGE_IS_COPY_CONSTRUCTIBLE_TEST(false, foo3_t);
BKSGE_IS_COPY_CONSTRUCTIBLE_TEST(false, foo4_t);

}	// namespace is_copy_constructible_test

}	// namespace bksge_type_traits_test

#undef BKSGE_IS_COPY_CONSTRUCTIBLE_TEST

BKSGE_WARNING_POP()
