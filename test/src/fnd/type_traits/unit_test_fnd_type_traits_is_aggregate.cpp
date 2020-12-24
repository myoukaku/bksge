/**
 *	@file	unit_test_fnd_type_traits_is_aggregate.cpp
 *
 *	@brief	is_aggregate のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/type_traits/is_aggregate.hpp>
#include <bksge/fnd/array.hpp>
#include <bksge/fnd/config.hpp>
#include <gtest/gtest.h>
#include "type_traits_test_utility.hpp"

namespace bksge_type_traits_test
{

namespace is_aggregate_test
{

#define BKSGE_IS_AGGREGATE_TEST(b, T)	\
	static_assert(bksge::is_aggregate<T>::value == b, #T);	\
	static_assert(bksge::is_aggregate<T>()      == b, #T)

#define BKSGE_IS_AGGREGATE_TEST_CV(b, T)	\
	BKSGE_IS_AGGREGATE_TEST(b,                T);	\
	BKSGE_IS_AGGREGATE_TEST(b, const          T);	\
	BKSGE_IS_AGGREGATE_TEST(b,       volatile T);	\
	BKSGE_IS_AGGREGATE_TEST(b, const volatile T)

struct Base {};

struct HasBase : Base
{
	int x;
};

struct HasCtor { HasCtor(int){} };

struct HasPrivateMember
{
	void PreventUnusedPrivateMemberWarning();
private:
	int x;
};

struct HasVirtualFunc
{
	virtual void f() {}
};

struct Aggregate1
{
	int x;
};

struct Aggregate2
{
	int x, y;
};

BKSGE_WARNING_PUSH()
BKSGE_WARNING_DISABLE_MSVC(4510)	// 既定のコンストラクターを生成できません。
BKSGE_WARNING_DISABLE_MSVC(4610)	// 'Aggregate3' を初期化できません。ユーザー定義のコンストラクターが必要です。

struct Aggregate3
{
	double d = 0.5;
	HasBase b;
	HasCtor c;
	HasPrivateMember p;
	HasVirtualFunc v;
private:
	void g() {}
};

BKSGE_WARNING_POP()

#if defined(BKSGE_HAS_CXX17_IS_AGGREGATE)

BKSGE_IS_AGGREGATE_TEST_CV(true,  Aggregate1);
BKSGE_IS_AGGREGATE_TEST_CV(true,  Aggregate1[]);
BKSGE_IS_AGGREGATE_TEST_CV(true,  Aggregate1[2][3]);
BKSGE_IS_AGGREGATE_TEST_CV(false, Aggregate1&);
BKSGE_IS_AGGREGATE_TEST_CV(false, Aggregate1&&);
BKSGE_IS_AGGREGATE_TEST_CV(false, Aggregate1*);
BKSGE_IS_AGGREGATE_TEST   (false, void(Aggregate1::*)(int) const);
BKSGE_IS_AGGREGATE_TEST_CV(true,  Aggregate2);
BKSGE_IS_AGGREGATE_TEST_CV(true,  Aggregate2);
BKSGE_IS_AGGREGATE_TEST_CV(true,  Aggregate2[3]);
BKSGE_IS_AGGREGATE_TEST_CV(false, Aggregate2&);
BKSGE_IS_AGGREGATE_TEST_CV(false, Aggregate2&&);
BKSGE_IS_AGGREGATE_TEST_CV(false, Aggregate2*);
BKSGE_IS_AGGREGATE_TEST_CV(true,  Aggregate3);
BKSGE_IS_AGGREGATE_TEST_CV(false, HasCtor);
BKSGE_IS_AGGREGATE_TEST_CV(true,  HasCtor[3]);
BKSGE_IS_AGGREGATE_TEST_CV(false, HasPrivateMember);
BKSGE_IS_AGGREGATE_TEST_CV(false, int);
BKSGE_IS_AGGREGATE_TEST_CV(false, int*);
BKSGE_IS_AGGREGATE_TEST_CV(false, int&);
BKSGE_IS_AGGREGATE_TEST_CV(true,  int[3]);
BKSGE_IS_AGGREGATE_TEST_CV(false, void);
BKSGE_IS_AGGREGATE_TEST_CV(false, void*);
BKSGE_IS_AGGREGATE_TEST   (false, void());
using ArrayType = bksge::array<Aggregate1, 4>;
BKSGE_IS_AGGREGATE_TEST_CV(true,  ArrayType);

#endif

#undef BKSGE_IS_AGGREGATE_TEST
#undef BKSGE_IS_AGGREGATE_TEST_CV

}	// namespace is_aggregate_test

}	// namespace bksge_type_traits_test
