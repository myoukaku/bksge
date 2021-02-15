/**
 *	@file	unit_test_fnd_type_traits_is_nothrow_copy_constructible.cpp
 *
 *	@brief	is_nothrow_copy_constructible のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/type_traits/is_nothrow_copy_constructible.hpp>
#include <bksge/fnd/config.hpp>
#include <gtest/gtest.h>
#include "type_traits_test_utility.hpp"

#if defined(BKSGE_HAS_CXX14_VARIABLE_TEMPLATES)

#define BKSGE_IS_NOTHROW_COPY_CONSTRUCTIBLE_TEST(b, T)	\
	static_assert(bksge::is_nothrow_copy_constructible_v<T>      == b, #T);	\
	static_assert(bksge::is_nothrow_copy_constructible<T>::value == b, #T);	\
	static_assert(bksge::is_nothrow_copy_constructible<T>()      == b, #T)

#else

#define BKSGE_IS_NOTHROW_COPY_CONSTRUCTIBLE_TEST(b, T)	\
	static_assert(bksge::is_nothrow_copy_constructible<T>::value == b, #T);	\
	static_assert(bksge::is_nothrow_copy_constructible<T>()      == b, #T)

#endif

namespace bksge_type_traits_test
{

namespace is_nothrow_copy_constructible_test
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

BKSGE_IS_NOTHROW_COPY_CONSTRUCTIBLE_TEST(true,  S1);
BKSGE_IS_NOTHROW_COPY_CONSTRUCTIBLE_TEST(true,  S2);
BKSGE_IS_NOTHROW_COPY_CONSTRUCTIBLE_TEST(true,  S3);
BKSGE_IS_NOTHROW_COPY_CONSTRUCTIBLE_TEST(false, S4);
BKSGE_IS_NOTHROW_COPY_CONSTRUCTIBLE_TEST(false, S5);

BKSGE_IS_NOTHROW_COPY_CONSTRUCTIBLE_TEST(true,	               int);
BKSGE_IS_NOTHROW_COPY_CONSTRUCTIBLE_TEST(true,	const          int);
BKSGE_IS_NOTHROW_COPY_CONSTRUCTIBLE_TEST(true,	      volatile int);
BKSGE_IS_NOTHROW_COPY_CONSTRUCTIBLE_TEST(true,	const volatile int);
BKSGE_IS_NOTHROW_COPY_CONSTRUCTIBLE_TEST(true,	int*);
BKSGE_IS_NOTHROW_COPY_CONSTRUCTIBLE_TEST(true,	int&);
BKSGE_IS_NOTHROW_COPY_CONSTRUCTIBLE_TEST(false,	int&&);
BKSGE_IS_NOTHROW_COPY_CONSTRUCTIBLE_TEST(false,	int[2]);
BKSGE_IS_NOTHROW_COPY_CONSTRUCTIBLE_TEST(false,	int[]);
BKSGE_IS_NOTHROW_COPY_CONSTRUCTIBLE_TEST(true,	int(&)[2]);
BKSGE_IS_NOTHROW_COPY_CONSTRUCTIBLE_TEST(true,	int(&)[]);
BKSGE_IS_NOTHROW_COPY_CONSTRUCTIBLE_TEST(false,	int(&&)[2]);
BKSGE_IS_NOTHROW_COPY_CONSTRUCTIBLE_TEST(false,	int(&&)[]);

BKSGE_IS_NOTHROW_COPY_CONSTRUCTIBLE_TEST(false,                void);
BKSGE_IS_NOTHROW_COPY_CONSTRUCTIBLE_TEST(false, const          void);
BKSGE_IS_NOTHROW_COPY_CONSTRUCTIBLE_TEST(false,       volatile void);
BKSGE_IS_NOTHROW_COPY_CONSTRUCTIBLE_TEST(false, const volatile void);

BKSGE_IS_NOTHROW_COPY_CONSTRUCTIBLE_TEST(false,	               UDT);
BKSGE_IS_NOTHROW_COPY_CONSTRUCTIBLE_TEST(false,	const          UDT);
BKSGE_IS_NOTHROW_COPY_CONSTRUCTIBLE_TEST(false,	      volatile UDT);
BKSGE_IS_NOTHROW_COPY_CONSTRUCTIBLE_TEST(false,	const volatile UDT);
BKSGE_IS_NOTHROW_COPY_CONSTRUCTIBLE_TEST(true,	UDT*);
BKSGE_IS_NOTHROW_COPY_CONSTRUCTIBLE_TEST(true,	UDT&);
BKSGE_IS_NOTHROW_COPY_CONSTRUCTIBLE_TEST(false,	UDT&&);
BKSGE_IS_NOTHROW_COPY_CONSTRUCTIBLE_TEST(false,	UDT[2]);
BKSGE_IS_NOTHROW_COPY_CONSTRUCTIBLE_TEST(false,	UDT[]);
BKSGE_IS_NOTHROW_COPY_CONSTRUCTIBLE_TEST(true,	UDT(&)[2]);
BKSGE_IS_NOTHROW_COPY_CONSTRUCTIBLE_TEST(true,	UDT(&)[]);
BKSGE_IS_NOTHROW_COPY_CONSTRUCTIBLE_TEST(false,	UDT(&&)[2]);
BKSGE_IS_NOTHROW_COPY_CONSTRUCTIBLE_TEST(false,	UDT(&&)[]);

BKSGE_IS_NOTHROW_COPY_CONSTRUCTIBLE_TEST(true,	               POD_UDT);
BKSGE_IS_NOTHROW_COPY_CONSTRUCTIBLE_TEST(true,	const          POD_UDT);
BKSGE_IS_NOTHROW_COPY_CONSTRUCTIBLE_TEST(false,	      volatile POD_UDT);
BKSGE_IS_NOTHROW_COPY_CONSTRUCTIBLE_TEST(false,	const volatile POD_UDT);

BKSGE_IS_NOTHROW_COPY_CONSTRUCTIBLE_TEST(false,                nothrow_default_ctor_UDT);
BKSGE_IS_NOTHROW_COPY_CONSTRUCTIBLE_TEST(false, const          nothrow_default_ctor_UDT);
BKSGE_IS_NOTHROW_COPY_CONSTRUCTIBLE_TEST(false,       volatile nothrow_default_ctor_UDT);
BKSGE_IS_NOTHROW_COPY_CONSTRUCTIBLE_TEST(false, const volatile nothrow_default_ctor_UDT);
BKSGE_IS_NOTHROW_COPY_CONSTRUCTIBLE_TEST(false,                nothrow_dtor_UDT);
BKSGE_IS_NOTHROW_COPY_CONSTRUCTIBLE_TEST(false, const          nothrow_dtor_UDT);
BKSGE_IS_NOTHROW_COPY_CONSTRUCTIBLE_TEST(false,       volatile nothrow_dtor_UDT);
BKSGE_IS_NOTHROW_COPY_CONSTRUCTIBLE_TEST(false, const volatile nothrow_dtor_UDT);
BKSGE_IS_NOTHROW_COPY_CONSTRUCTIBLE_TEST(true,                 nothrow_copy_ctor_UDT);
BKSGE_IS_NOTHROW_COPY_CONSTRUCTIBLE_TEST(true,  const          nothrow_copy_ctor_UDT);
BKSGE_IS_NOTHROW_COPY_CONSTRUCTIBLE_TEST(false,       volatile nothrow_copy_ctor_UDT);
BKSGE_IS_NOTHROW_COPY_CONSTRUCTIBLE_TEST(false, const volatile nothrow_copy_ctor_UDT);
BKSGE_IS_NOTHROW_COPY_CONSTRUCTIBLE_TEST(false,                nothrow_copy_assign_UDT);
BKSGE_IS_NOTHROW_COPY_CONSTRUCTIBLE_TEST(false, const          nothrow_copy_assign_UDT);
BKSGE_IS_NOTHROW_COPY_CONSTRUCTIBLE_TEST(false,       volatile nothrow_copy_assign_UDT);
BKSGE_IS_NOTHROW_COPY_CONSTRUCTIBLE_TEST(false, const volatile nothrow_copy_assign_UDT);
BKSGE_IS_NOTHROW_COPY_CONSTRUCTIBLE_TEST(false,                nothrow_move_ctor_UDT);
BKSGE_IS_NOTHROW_COPY_CONSTRUCTIBLE_TEST(false, const          nothrow_move_ctor_UDT);
BKSGE_IS_NOTHROW_COPY_CONSTRUCTIBLE_TEST(false,       volatile nothrow_move_ctor_UDT);
BKSGE_IS_NOTHROW_COPY_CONSTRUCTIBLE_TEST(false, const volatile nothrow_move_ctor_UDT);
BKSGE_IS_NOTHROW_COPY_CONSTRUCTIBLE_TEST(false,                nothrow_move_assign_UDT);
BKSGE_IS_NOTHROW_COPY_CONSTRUCTIBLE_TEST(false, const          nothrow_move_assign_UDT);
BKSGE_IS_NOTHROW_COPY_CONSTRUCTIBLE_TEST(false,       volatile nothrow_move_assign_UDT);
BKSGE_IS_NOTHROW_COPY_CONSTRUCTIBLE_TEST(false, const volatile nothrow_move_assign_UDT);

BKSGE_IS_NOTHROW_COPY_CONSTRUCTIBLE_TEST(true, f1);
BKSGE_IS_NOTHROW_COPY_CONSTRUCTIBLE_TEST(true, f2);
BKSGE_IS_NOTHROW_COPY_CONSTRUCTIBLE_TEST(true, f3);
BKSGE_IS_NOTHROW_COPY_CONSTRUCTIBLE_TEST(true, mf1);
BKSGE_IS_NOTHROW_COPY_CONSTRUCTIBLE_TEST(true, mf2);
BKSGE_IS_NOTHROW_COPY_CONSTRUCTIBLE_TEST(true, mf3);
BKSGE_IS_NOTHROW_COPY_CONSTRUCTIBLE_TEST(true, mf4);
BKSGE_IS_NOTHROW_COPY_CONSTRUCTIBLE_TEST(true, mp);
BKSGE_IS_NOTHROW_COPY_CONSTRUCTIBLE_TEST(true, cmf);
BKSGE_IS_NOTHROW_COPY_CONSTRUCTIBLE_TEST(false, foo0_t);
BKSGE_IS_NOTHROW_COPY_CONSTRUCTIBLE_TEST(false, foo1_t);
BKSGE_IS_NOTHROW_COPY_CONSTRUCTIBLE_TEST(false, foo2_t);
BKSGE_IS_NOTHROW_COPY_CONSTRUCTIBLE_TEST(false, foo3_t);
BKSGE_IS_NOTHROW_COPY_CONSTRUCTIBLE_TEST(false, foo4_t);

}	// namespace is_nothrow_copy_constructible_test

}	// namespace bksge_type_traits_test

#undef BKSGE_IS_NOTHROW_COPY_CONSTRUCTIBLE_TEST
