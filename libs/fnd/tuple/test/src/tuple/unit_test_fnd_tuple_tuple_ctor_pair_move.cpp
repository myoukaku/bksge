/**
 *	@file	unit_test_fnd_tuple_tuple_ctor_pair_move.cpp
 *
 *	@brief	tuple::tuple(pair<U1,U2>&&) のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/tuple/tuple.hpp>
#include <bksge/fnd/tuple/get.hpp>
#include <bksge/fnd/pair.hpp>
#include <bksge/fnd/utility/move.hpp>
#include <bksge/fnd/type_traits/is_constructible.hpp>
#include <bksge/fnd/type_traits/is_implicitly_constructible.hpp>
#include <bksge/fnd/type_traits/is_nothrow_constructible.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <bksge/fnd/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

BKSGE_WARNING_PUSH();
BKSGE_WARNING_DISABLE_MSVC(4244);

namespace bksge_tuple_test
{

namespace ctor_pair_move_test
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

static_assert(!bksge::is_constructible<bksge::tuple<>, bksge::pair<int, int>&&>::value, "");
static_assert(!bksge::is_constructible<bksge::tuple<int>, bksge::pair<int, int>&&>::value, "");
static_assert( bksge::is_constructible<bksge::tuple<int, int>, bksge::pair<int, int>&&>::value, "");
static_assert( bksge::is_constructible<bksge::tuple<float, long>, bksge::pair<double, short>&&>::value, "");
static_assert(!bksge::is_constructible<bksge::tuple<int, int, int>, bksge::pair<int, int>&&>::value, "");
static_assert( bksge::is_constructible<bksge::tuple<Explicit, Explicit>, bksge::pair<int, int>&&>::value, "");
static_assert( bksge::is_constructible<bksge::tuple<Explicit, Implicit>, bksge::pair<int, int>&&>::value, "");
static_assert(!bksge::is_constructible<bksge::tuple<Explicit, NoCtor>,   bksge::pair<int, int>&&>::value, "");
static_assert( bksge::is_constructible<bksge::tuple<Implicit, Explicit>, bksge::pair<int, int>&&>::value, "");
static_assert( bksge::is_constructible<bksge::tuple<Implicit, Implicit>, bksge::pair<int, int>&&>::value, "");
static_assert(!bksge::is_constructible<bksge::tuple<Implicit, NoCtor>,   bksge::pair<int, int>&&>::value, "");
static_assert(!bksge::is_constructible<bksge::tuple<NoCtor,   Explicit>, bksge::pair<int, int>&&>::value, "");
static_assert(!bksge::is_constructible<bksge::tuple<NoCtor,   Implicit>, bksge::pair<int, int>&&>::value, "");
static_assert(!bksge::is_constructible<bksge::tuple<NoCtor,   NoCtor>,   bksge::pair<int, int>&&>::value, "");
static_assert(!bksge::is_constructible<bksge::tuple<Explicit, Explicit, Explicit>, bksge::pair<int, int>&&>::value, "");
static_assert(!bksge::is_constructible<bksge::tuple<Implicit, Implicit, Implicit>, bksge::pair<int, int>&&>::value, "");
static_assert(!bksge::is_constructible<bksge::tuple<NoCtor,   NoCtor,   NoCtor>,   bksge::pair<int, int>&&>::value, "");

static_assert(!bksge::is_implicitly_constructible<bksge::tuple<>, bksge::pair<int, int>&&>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::tuple<int>, bksge::pair<int, int>&&>::value, "");
static_assert( bksge::is_implicitly_constructible<bksge::tuple<int, int>, bksge::pair<int, int>&&>::value, "");
static_assert( bksge::is_implicitly_constructible<bksge::tuple<float, long>, bksge::pair<double, short>&&>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::tuple<int, int, int>, bksge::pair<int, int>&&>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::tuple<Explicit, Explicit>, bksge::pair<int, int>&&>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::tuple<Explicit, Implicit>, bksge::pair<int, int>&&>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::tuple<Explicit, NoCtor>,   bksge::pair<int, int>&&>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::tuple<Implicit, Explicit>, bksge::pair<int, int>&&>::value, "");
static_assert( bksge::is_implicitly_constructible<bksge::tuple<Implicit, Implicit>, bksge::pair<int, int>&&>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::tuple<Implicit, NoCtor>,   bksge::pair<int, int>&&>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::tuple<NoCtor,   Explicit>, bksge::pair<int, int>&&>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::tuple<NoCtor,   Implicit>, bksge::pair<int, int>&&>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::tuple<NoCtor,   NoCtor>,   bksge::pair<int, int>&&>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::tuple<Explicit, Explicit, Explicit>, bksge::pair<int, int>&&>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::tuple<Implicit, Implicit, Implicit>, bksge::pair<int, int>&&>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::tuple<NoCtor,   NoCtor,   NoCtor>,   bksge::pair<int, int>&&>::value, "");

static_assert(!bksge::is_nothrow_constructible<bksge::tuple<>, bksge::pair<int, int>&&>::value, "");
static_assert(!bksge::is_nothrow_constructible<bksge::tuple<int>, bksge::pair<int, int>&&>::value, "");
static_assert( bksge::is_nothrow_constructible<bksge::tuple<int, int>, bksge::pair<int, int>&&>::value, "");
static_assert( bksge::is_nothrow_constructible<bksge::tuple<float, long>, bksge::pair<double, short>&&>::value, "");
static_assert(!bksge::is_nothrow_constructible<bksge::tuple<int, int, int>, bksge::pair<int, int>&&>::value, "");
static_assert( bksge::is_nothrow_constructible<bksge::tuple<Explicit, Explicit>, bksge::pair<int, int>&&>::value, "");
static_assert(!bksge::is_nothrow_constructible<bksge::tuple<Explicit, Implicit>, bksge::pair<int, int>&&>::value, "");
static_assert(!bksge::is_nothrow_constructible<bksge::tuple<Explicit, NoCtor>,   bksge::pair<int, int>&&>::value, "");
static_assert(!bksge::is_nothrow_constructible<bksge::tuple<Implicit, Explicit>, bksge::pair<int, int>&&>::value, "");
static_assert(!bksge::is_nothrow_constructible<bksge::tuple<Implicit, Implicit>, bksge::pair<int, int>&&>::value, "");
static_assert(!bksge::is_nothrow_constructible<bksge::tuple<Implicit, NoCtor>,   bksge::pair<int, int>&&>::value, "");
static_assert(!bksge::is_nothrow_constructible<bksge::tuple<NoCtor,   Explicit>, bksge::pair<int, int>&&>::value, "");
static_assert(!bksge::is_nothrow_constructible<bksge::tuple<NoCtor,   Implicit>, bksge::pair<int, int>&&>::value, "");
static_assert(!bksge::is_nothrow_constructible<bksge::tuple<NoCtor,   NoCtor>,   bksge::pair<int, int>&&>::value, "");
static_assert(!bksge::is_nothrow_constructible<bksge::tuple<Explicit, Explicit, Explicit>, bksge::pair<int, int>&&>::value, "");
static_assert(!bksge::is_nothrow_constructible<bksge::tuple<Implicit, Implicit, Implicit>, bksge::pair<int, int>&&>::value, "");
static_assert(!bksge::is_nothrow_constructible<bksge::tuple<NoCtor,   NoCtor,   NoCtor>,   bksge::pair<int, int>&&>::value, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline BKSGE_CXX14_CONSTEXPR bool test()
{
	using std::get;
	{
		bksge::pair<int, float>  p = {2, 2.5};
		bksge::tuple<int, float> t = {bksge::move(p)};
		VERIFY(get<0>(t) == 2);
		VERIFY(get<1>(t) == 2.5);
	}
	{
		bksge::pair<int, float>  const p = {2, 2.5};
		bksge::tuple<int, float> const t = {bksge::move(p)};
		VERIFY(get<0>(t) == 2);
		VERIFY(get<1>(t) == 2.5);
	}
	{
		bksge::pair<int, float>    p = {3, 4.5};
		bksge::tuple<long, double> t = {bksge::move(p)};
		VERIFY(get<0>(t) == 3);
		VERIFY(get<1>(t) == 4.5);
	}
	{
		bksge::pair<int, float>    const p = {3, 4.5};
		bksge::tuple<long, double> const t = {bksge::move(p)};
		VERIFY(get<0>(t) == 3);
		VERIFY(get<1>(t) == 4.5);
	}
	{
		bksge::pair<int, int>            p = {1, 2};
		bksge::tuple<Explicit, Explicit> t {bksge::move(p)};
		VERIFY(get<0>(t).n == 1);
		VERIFY(get<1>(t).n == 2);
	}
	{
		bksge::pair<int, int>            p = {3, 4};
		bksge::tuple<Explicit, Implicit> t {bksge::move(p)};
		VERIFY(get<0>(t).n == 3);
		VERIFY(get<1>(t).n == 4);
	}
	{
		bksge::pair<int, int>            p = {5, 6};
		bksge::tuple<Implicit, Explicit> t {bksge::move(p)};
		VERIFY(get<0>(t).n == 5);
		VERIFY(get<1>(t).n == 6);
	}
	{
		bksge::pair<int, int>            p = {7, 8};
		bksge::tuple<Implicit, Implicit> t = {bksge::move(p)};
		VERIFY(get<0>(t).n == 7);
		VERIFY(get<1>(t).n == 8);
	}
#if defined(BKSGE_HAS_CXX17_DEDUCTION_GUIDES)
	{
		bksge::pair<int, float> p = {2, 2.5};
		bksge::tuple            t = {bksge::move(p)};
		static_assert(bksge::is_same<decltype(t), bksge::tuple<int, float>>::value, "");
		VERIFY(get<0>(t) == 2);
		VERIFY(get<1>(t) == 2.5);
	}
#endif
	return true;
}

#undef VERIFY

GTEST_TEST(TupleTest, CtorPairMoveTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test()));
}

}	// namespace ctor_pair_move_test

}	// namespace bksge_tuple_test

BKSGE_WARNING_POP();
