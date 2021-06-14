/**
 *	@file	unit_test_fnd_tuple_tuple_ctor_conv_move.cpp
 *
 *	@brief	tuple::tuple(tuple<UTypes...>&&) のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/tuple/tuple.hpp>
#include <bksge/fnd/tuple/get.hpp>
#include <bksge/fnd/type_traits/is_constructible.hpp>
#include <bksge/fnd/type_traits/is_implicitly_constructible.hpp>
#include <bksge/fnd/type_traits/is_nothrow_constructible.hpp>
#include <bksge/fnd/utility/move.hpp>
#include <bksge/fnd/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

BKSGE_WARNING_PUSH();
BKSGE_WARNING_DISABLE_MSVC(4244);

namespace bksge_tuple_test
{

namespace ctor_conv_move_test
{

struct Explicit
{
	explicit BKSGE_CONSTEXPR Explicit(int x) noexcept : n(x) {}
	int n;
};

struct Implicit
{
	BKSGE_CONSTEXPR Implicit(int x) : n(x) {}
	int n;
};

struct NoCtor
{
	BKSGE_CONSTEXPR NoCtor(int x) = delete;
	int n;
};

static_assert(!bksge::is_constructible<bksge::tuple<>,         bksge::tuple<int>&&>::value, "");
static_assert( bksge::is_constructible<bksge::tuple<int>,      bksge::tuple<short>&&>::value, "");
static_assert( bksge::is_constructible<bksge::tuple<Explicit>, bksge::tuple<int>&&>::value, "");
static_assert( bksge::is_constructible<bksge::tuple<Implicit>, bksge::tuple<int>&&>::value, "");
static_assert(!bksge::is_constructible<bksge::tuple<NoCtor>,   bksge::tuple<int>&&>::value, "");
static_assert(!bksge::is_constructible<bksge::tuple<Explicit>, bksge::tuple<int, int>&&>::value, "");
static_assert(!bksge::is_constructible<bksge::tuple<Implicit>, bksge::tuple<int, int>&&>::value, "");
static_assert(!bksge::is_constructible<bksge::tuple<NoCtor>,   bksge::tuple<int, int>&&>::value, "");
static_assert( bksge::is_constructible<bksge::tuple<short, float>, bksge::tuple<int, double>&&>::value, "");
static_assert( bksge::is_constructible<bksge::tuple<Explicit, Explicit, Explicit>, bksge::tuple<int, int, int>&&>::value, "");
static_assert( bksge::is_constructible<bksge::tuple<Explicit, Explicit, Implicit>, bksge::tuple<int, int, int>&&>::value, "");
static_assert(!bksge::is_constructible<bksge::tuple<Explicit, Explicit, NoCtor>,   bksge::tuple<int, int, int>&&>::value, "");
static_assert( bksge::is_constructible<bksge::tuple<Explicit, Implicit, Explicit>, bksge::tuple<int, int, int>&&>::value, "");
static_assert( bksge::is_constructible<bksge::tuple<Explicit, Implicit, Implicit>, bksge::tuple<int, int, int>&&>::value, "");
static_assert(!bksge::is_constructible<bksge::tuple<Explicit, Implicit, NoCtor>,   bksge::tuple<int, int, int>&&>::value, "");
static_assert(!bksge::is_constructible<bksge::tuple<Explicit, NoCtor,   Explicit>, bksge::tuple<int, int, int>&&>::value, "");
static_assert(!bksge::is_constructible<bksge::tuple<Explicit, NoCtor,   Implicit>, bksge::tuple<int, int, int>&&>::value, "");
static_assert(!bksge::is_constructible<bksge::tuple<Explicit, NoCtor,   NoCtor>,   bksge::tuple<int, int, int>&&>::value, "");
static_assert( bksge::is_constructible<bksge::tuple<Implicit, Explicit, Explicit>, bksge::tuple<int, int, int>&&>::value, "");
static_assert( bksge::is_constructible<bksge::tuple<Implicit, Explicit, Implicit>, bksge::tuple<int, int, int>&&>::value, "");
static_assert(!bksge::is_constructible<bksge::tuple<Implicit, Explicit, NoCtor>,   bksge::tuple<int, int, int>&&>::value, "");
static_assert( bksge::is_constructible<bksge::tuple<Implicit, Implicit, Explicit>, bksge::tuple<int, int, int>&&>::value, "");
static_assert( bksge::is_constructible<bksge::tuple<Implicit, Implicit, Implicit>, bksge::tuple<int, int, int>&&>::value, "");
static_assert(!bksge::is_constructible<bksge::tuple<Implicit, Implicit, NoCtor>,   bksge::tuple<int, int, int>&&>::value, "");
static_assert(!bksge::is_constructible<bksge::tuple<Implicit, NoCtor,   Explicit>, bksge::tuple<int, int, int>&&>::value, "");
static_assert(!bksge::is_constructible<bksge::tuple<Implicit, NoCtor,   Implicit>, bksge::tuple<int, int, int>&&>::value, "");
static_assert(!bksge::is_constructible<bksge::tuple<Implicit, NoCtor,   NoCtor>,   bksge::tuple<int, int, int>&&>::value, "");
static_assert(!bksge::is_constructible<bksge::tuple<NoCtor,   Explicit, Explicit>, bksge::tuple<int, int, int>&&>::value, "");
static_assert(!bksge::is_constructible<bksge::tuple<NoCtor,   Explicit, Implicit>, bksge::tuple<int, int, int>&&>::value, "");
static_assert(!bksge::is_constructible<bksge::tuple<NoCtor,   Explicit, NoCtor>,   bksge::tuple<int, int, int>&&>::value, "");
static_assert(!bksge::is_constructible<bksge::tuple<NoCtor,   Implicit, Explicit>, bksge::tuple<int, int, int>&&>::value, "");
static_assert(!bksge::is_constructible<bksge::tuple<NoCtor,   Implicit, Implicit>, bksge::tuple<int, int, int>&&>::value, "");
static_assert(!bksge::is_constructible<bksge::tuple<NoCtor,   Implicit, NoCtor>,   bksge::tuple<int, int, int>&&>::value, "");
static_assert(!bksge::is_constructible<bksge::tuple<NoCtor,   NoCtor,   Explicit>, bksge::tuple<int, int, int>&&>::value, "");
static_assert(!bksge::is_constructible<bksge::tuple<NoCtor,   NoCtor,   Implicit>, bksge::tuple<int, int, int>&&>::value, "");
static_assert(!bksge::is_constructible<bksge::tuple<NoCtor,   NoCtor,   NoCtor>,   bksge::tuple<int, int, int>&&>::value, "");

static_assert( bksge::is_implicitly_constructible<bksge::tuple<int>,      bksge::tuple<short>&&>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::tuple<Explicit>, bksge::tuple<int>&&>::value, "");
static_assert( bksge::is_implicitly_constructible<bksge::tuple<Implicit>, bksge::tuple<int>&&>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::tuple<NoCtor>,   bksge::tuple<int>&&>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::tuple<Explicit>, bksge::tuple<int, int>&&>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::tuple<Implicit>, bksge::tuple<int, int>&&>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::tuple<NoCtor>,   bksge::tuple<int, int>&&>::value, "");
static_assert( bksge::is_implicitly_constructible<bksge::tuple<short, float>, bksge::tuple<int, double>&&>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::tuple<Explicit, Explicit, Explicit>, bksge::tuple<int, int, int>&&>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::tuple<Explicit, Explicit, Implicit>, bksge::tuple<int, int, int>&&>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::tuple<Explicit, Explicit, NoCtor>,   bksge::tuple<int, int, int>&&>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::tuple<Explicit, Implicit, Explicit>, bksge::tuple<int, int, int>&&>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::tuple<Explicit, Implicit, Implicit>, bksge::tuple<int, int, int>&&>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::tuple<Explicit, Implicit, NoCtor>,   bksge::tuple<int, int, int>&&>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::tuple<Explicit, NoCtor,   Explicit>, bksge::tuple<int, int, int>&&>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::tuple<Explicit, NoCtor,   Implicit>, bksge::tuple<int, int, int>&&>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::tuple<Explicit, NoCtor,   NoCtor>,   bksge::tuple<int, int, int>&&>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::tuple<Implicit, Explicit, Explicit>, bksge::tuple<int, int, int>&&>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::tuple<Implicit, Explicit, Implicit>, bksge::tuple<int, int, int>&&>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::tuple<Implicit, Explicit, NoCtor>,   bksge::tuple<int, int, int>&&>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::tuple<Implicit, Implicit, Explicit>, bksge::tuple<int, int, int>&&>::value, "");
static_assert( bksge::is_implicitly_constructible<bksge::tuple<Implicit, Implicit, Implicit>, bksge::tuple<int, int, int>&&>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::tuple<Implicit, Implicit, NoCtor>,   bksge::tuple<int, int, int>&&>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::tuple<Implicit, NoCtor,   Explicit>, bksge::tuple<int, int, int>&&>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::tuple<Implicit, NoCtor,   Implicit>, bksge::tuple<int, int, int>&&>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::tuple<Implicit, NoCtor,   NoCtor>,   bksge::tuple<int, int, int>&&>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::tuple<NoCtor,   Explicit, Explicit>, bksge::tuple<int, int, int>&&>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::tuple<NoCtor,   Explicit, Implicit>, bksge::tuple<int, int, int>&&>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::tuple<NoCtor,   Explicit, NoCtor>,   bksge::tuple<int, int, int>&&>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::tuple<NoCtor,   Implicit, Explicit>, bksge::tuple<int, int, int>&&>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::tuple<NoCtor,   Implicit, Implicit>, bksge::tuple<int, int, int>&&>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::tuple<NoCtor,   Implicit, NoCtor>,   bksge::tuple<int, int, int>&&>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::tuple<NoCtor,   NoCtor,   Explicit>, bksge::tuple<int, int, int>&&>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::tuple<NoCtor,   NoCtor,   Implicit>, bksge::tuple<int, int, int>&&>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::tuple<NoCtor,   NoCtor,   NoCtor>,   bksge::tuple<int, int, int>&&>::value, "");

static_assert( bksge::is_nothrow_constructible<bksge::tuple<int>,      bksge::tuple<short>&&>::value, "");
static_assert( bksge::is_nothrow_constructible<bksge::tuple<Explicit>, bksge::tuple<int>&&>::value, "");
static_assert(!bksge::is_nothrow_constructible<bksge::tuple<Implicit>, bksge::tuple<int>&&>::value, "");
static_assert(!bksge::is_nothrow_constructible<bksge::tuple<NoCtor>,   bksge::tuple<int>&&>::value, "");
static_assert(!bksge::is_nothrow_constructible<bksge::tuple<Explicit>, bksge::tuple<int, int>&&>::value, "");
static_assert(!bksge::is_nothrow_constructible<bksge::tuple<Implicit>, bksge::tuple<int, int>&&>::value, "");
static_assert(!bksge::is_nothrow_constructible<bksge::tuple<NoCtor>,   bksge::tuple<int, int>&&>::value, "");
static_assert( bksge::is_nothrow_constructible<bksge::tuple<short, float>, bksge::tuple<int, double>&&>::value, "");
static_assert( bksge::is_nothrow_constructible<bksge::tuple<Explicit, Explicit, Explicit>, bksge::tuple<int, int, int>&&>::value, "");
static_assert(!bksge::is_nothrow_constructible<bksge::tuple<Explicit, Explicit, Implicit>, bksge::tuple<int, int, int>&&>::value, "");
static_assert(!bksge::is_nothrow_constructible<bksge::tuple<Explicit, Explicit, NoCtor>,   bksge::tuple<int, int, int>&&>::value, "");
static_assert(!bksge::is_nothrow_constructible<bksge::tuple<Explicit, Implicit, Explicit>, bksge::tuple<int, int, int>&&>::value, "");
static_assert(!bksge::is_nothrow_constructible<bksge::tuple<Explicit, Implicit, Implicit>, bksge::tuple<int, int, int>&&>::value, "");
static_assert(!bksge::is_nothrow_constructible<bksge::tuple<Explicit, Implicit, NoCtor>,   bksge::tuple<int, int, int>&&>::value, "");
static_assert(!bksge::is_nothrow_constructible<bksge::tuple<Explicit, NoCtor,   Explicit>, bksge::tuple<int, int, int>&&>::value, "");
static_assert(!bksge::is_nothrow_constructible<bksge::tuple<Explicit, NoCtor,   Implicit>, bksge::tuple<int, int, int>&&>::value, "");
static_assert(!bksge::is_nothrow_constructible<bksge::tuple<Explicit, NoCtor,   NoCtor>,   bksge::tuple<int, int, int>&&>::value, "");
static_assert(!bksge::is_nothrow_constructible<bksge::tuple<Implicit, Explicit, Explicit>, bksge::tuple<int, int, int>&&>::value, "");
static_assert(!bksge::is_nothrow_constructible<bksge::tuple<Implicit, Explicit, Implicit>, bksge::tuple<int, int, int>&&>::value, "");
static_assert(!bksge::is_nothrow_constructible<bksge::tuple<Implicit, Explicit, NoCtor>,   bksge::tuple<int, int, int>&&>::value, "");
static_assert(!bksge::is_nothrow_constructible<bksge::tuple<Implicit, Implicit, Explicit>, bksge::tuple<int, int, int>&&>::value, "");
static_assert(!bksge::is_nothrow_constructible<bksge::tuple<Implicit, Implicit, Implicit>, bksge::tuple<int, int, int>&&>::value, "");
static_assert(!bksge::is_nothrow_constructible<bksge::tuple<Implicit, Implicit, NoCtor>,   bksge::tuple<int, int, int>&&>::value, "");
static_assert(!bksge::is_nothrow_constructible<bksge::tuple<Implicit, NoCtor,   Explicit>, bksge::tuple<int, int, int>&&>::value, "");
static_assert(!bksge::is_nothrow_constructible<bksge::tuple<Implicit, NoCtor,   Implicit>, bksge::tuple<int, int, int>&&>::value, "");
static_assert(!bksge::is_nothrow_constructible<bksge::tuple<Implicit, NoCtor,   NoCtor>,   bksge::tuple<int, int, int>&&>::value, "");
static_assert(!bksge::is_nothrow_constructible<bksge::tuple<NoCtor,   Explicit, Explicit>, bksge::tuple<int, int, int>&&>::value, "");
static_assert(!bksge::is_nothrow_constructible<bksge::tuple<NoCtor,   Explicit, Implicit>, bksge::tuple<int, int, int>&&>::value, "");
static_assert(!bksge::is_nothrow_constructible<bksge::tuple<NoCtor,   Explicit, NoCtor>,   bksge::tuple<int, int, int>&&>::value, "");
static_assert(!bksge::is_nothrow_constructible<bksge::tuple<NoCtor,   Implicit, Explicit>, bksge::tuple<int, int, int>&&>::value, "");
static_assert(!bksge::is_nothrow_constructible<bksge::tuple<NoCtor,   Implicit, Implicit>, bksge::tuple<int, int, int>&&>::value, "");
static_assert(!bksge::is_nothrow_constructible<bksge::tuple<NoCtor,   Implicit, NoCtor>,   bksge::tuple<int, int, int>&&>::value, "");
static_assert(!bksge::is_nothrow_constructible<bksge::tuple<NoCtor,   NoCtor,   Explicit>, bksge::tuple<int, int, int>&&>::value, "");
static_assert(!bksge::is_nothrow_constructible<bksge::tuple<NoCtor,   NoCtor,   Implicit>, bksge::tuple<int, int, int>&&>::value, "");
static_assert(!bksge::is_nothrow_constructible<bksge::tuple<NoCtor,   NoCtor,   NoCtor>,   bksge::tuple<int, int, int>&&>::value, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline BKSGE_CXX14_CONSTEXPR bool test()
{
	using std::get;
	{
		bksge::tuple<short> t1(1);
		bksge::tuple<int>   t2(bksge::move(t1));
		VERIFY(get<0>(t2) == 1);
	}
	{
		bksge::tuple<short> const t1(1);
		bksge::tuple<int>   const t2(bksge::move(t1));
		VERIFY(get<0>(t2) == 1);
	}
	{
		bksge::tuple<int, float>   t1 = {2, 2.5};
		bksge::tuple<long, double> t2 = {bksge::move(t1)};
		VERIFY(get<0>(t2) == 2);
		VERIFY(get<1>(t2) == 2.5);
	}
	{
		bksge::tuple<int, float>   const t1 = {2, 2.5};
		bksge::tuple<long, double> const t2 = {bksge::move(t1)};
		VERIFY(get<0>(t2) == 2);
		VERIFY(get<1>(t2) == 2.5);
	}
	{
		bksge::tuple<short, char, double> t1 = {3, 'b', 4.5};
		bksge::tuple<int,   char, float>  t2 = {bksge::move(t1)};
		VERIFY(get<0>(t2) == 3);
		VERIFY(get<1>(t2) == 'b');
		VERIFY(get<2>(t2) == 4.5);
	}
	{
		bksge::tuple<short, char, double> const t1 = {3, 'b', 4.5};
		bksge::tuple<int,   char, float>  const t2 = {bksge::move(t1)};
		VERIFY(get<0>(t2) == 3);
		VERIFY(get<1>(t2) == 'b');
		VERIFY(get<2>(t2) == 4.5);
	}
	{
		bksge::tuple<int>      t1 = {5};
		bksge::tuple<Explicit> t2{bksge::move(t1)};
		VERIFY(get<0>(t2).n == 5);
	}
	{
		bksge::tuple<int>      t1 = {5};
		bksge::tuple<Implicit> t2 = {bksge::move(t1)};
		VERIFY(get<0>(t2).n == 5);
	}
	{
		bksge::tuple<int, int>           t1 = {7, 8};
		bksge::tuple<Explicit, Implicit> t2 {bksge::move(t1)};
		VERIFY(get<0>(t2).n == 7);
		VERIFY(get<1>(t2).n == 8);
	}
	{
		bksge::tuple<int, int>           t1 = {7, 8};
		bksge::tuple<Implicit, Implicit> t2 = {bksge::move(t1)};
		VERIFY(get<0>(t2).n == 7);
		VERIFY(get<1>(t2).n == 8);
	}
	{
		bksge::tuple<int, int, int>                t1 = {11, 12, 13};
		bksge::tuple<Implicit, Explicit, Implicit> t2 {bksge::move(t1)};
		VERIFY(get<0>(t2).n == 11);
		VERIFY(get<1>(t2).n == 12);
		VERIFY(get<2>(t2).n == 13);
	}
	{
		bksge::tuple<int, int, int>                t1 = {11, 12, 13};
		bksge::tuple<Implicit, Implicit, Implicit> t2 = {bksge::move(t1)};
		VERIFY(get<0>(t2).n == 11);
		VERIFY(get<1>(t2).n == 12);
		VERIFY(get<2>(t2).n == 13);
	}
	return true;
}

#undef VERIFY

GTEST_TEST(TupleTest, CtorConvMoveTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test()));
}

}	// namespace ctor_conv_move_test

}	// namespace bksge_tuple_test

BKSGE_WARNING_POP();
