/**
 *	@file	unit_test_fnd_tuple_tuple_ctor_value_move.cpp
 *
 *	@brief	tuple::tuple(UTypes&&...) のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/tuple/tuple.hpp>
#include <bksge/fnd/tuple/get.hpp>
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

namespace ctor_value_move_test
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

static_assert(!bksge::is_constructible<bksge::tuple<>, int>::value, "");
static_assert( bksge::is_constructible<bksge::tuple<int>, int>::value, "");
static_assert( bksge::is_constructible<bksge::tuple<Explicit>, int>::value, "");
static_assert( bksge::is_constructible<bksge::tuple<Implicit>, int>::value, "");
static_assert(!bksge::is_constructible<bksge::tuple<NoCtor>,   int>::value, "");
static_assert(!bksge::is_constructible<bksge::tuple<Explicit>, int, int>::value, "");
static_assert(!bksge::is_constructible<bksge::tuple<Implicit>, int, int>::value, "");
static_assert(!bksge::is_constructible<bksge::tuple<NoCtor>,   int, int>::value, "");
static_assert( bksge::is_constructible<bksge::tuple<Explicit, Explicit, Explicit>, int, int, int>::value, "");
static_assert( bksge::is_constructible<bksge::tuple<Explicit, Explicit, Implicit>, int, int, int>::value, "");
static_assert(!bksge::is_constructible<bksge::tuple<Explicit, Explicit, NoCtor>,   int, int, int>::value, "");
static_assert( bksge::is_constructible<bksge::tuple<Explicit, Implicit, Explicit>, int, int, int>::value, "");
static_assert( bksge::is_constructible<bksge::tuple<Explicit, Implicit, Implicit>, int, int, int>::value, "");
static_assert(!bksge::is_constructible<bksge::tuple<Explicit, Implicit, NoCtor>,   int, int, int>::value, "");
static_assert(!bksge::is_constructible<bksge::tuple<Explicit, NoCtor,   Explicit>, int, int, int>::value, "");
static_assert(!bksge::is_constructible<bksge::tuple<Explicit, NoCtor,   Implicit>, int, int, int>::value, "");
static_assert(!bksge::is_constructible<bksge::tuple<Explicit, NoCtor,   NoCtor>,   int, int, int>::value, "");
static_assert( bksge::is_constructible<bksge::tuple<Implicit, Explicit, Explicit>, int, int, int>::value, "");
static_assert( bksge::is_constructible<bksge::tuple<Implicit, Explicit, Implicit>, int, int, int>::value, "");
static_assert(!bksge::is_constructible<bksge::tuple<Implicit, Explicit, NoCtor>,   int, int, int>::value, "");
static_assert( bksge::is_constructible<bksge::tuple<Implicit, Implicit, Explicit>, int, int, int>::value, "");
static_assert( bksge::is_constructible<bksge::tuple<Implicit, Implicit, Implicit>, int, int, int>::value, "");
static_assert(!bksge::is_constructible<bksge::tuple<Implicit, Implicit, NoCtor>,   int, int, int>::value, "");
static_assert(!bksge::is_constructible<bksge::tuple<Implicit, NoCtor,   Explicit>, int, int, int>::value, "");
static_assert(!bksge::is_constructible<bksge::tuple<Implicit, NoCtor,   Implicit>, int, int, int>::value, "");
static_assert(!bksge::is_constructible<bksge::tuple<Implicit, NoCtor,   NoCtor>,   int, int, int>::value, "");
static_assert(!bksge::is_constructible<bksge::tuple<NoCtor,   Explicit, Explicit>, int, int, int>::value, "");
static_assert(!bksge::is_constructible<bksge::tuple<NoCtor,   Explicit, Implicit>, int, int, int>::value, "");
static_assert(!bksge::is_constructible<bksge::tuple<NoCtor,   Explicit, NoCtor>,   int, int, int>::value, "");
static_assert(!bksge::is_constructible<bksge::tuple<NoCtor,   Implicit, Explicit>, int, int, int>::value, "");
static_assert(!bksge::is_constructible<bksge::tuple<NoCtor,   Implicit, Implicit>, int, int, int>::value, "");
static_assert(!bksge::is_constructible<bksge::tuple<NoCtor,   Implicit, NoCtor>,   int, int, int>::value, "");
static_assert(!bksge::is_constructible<bksge::tuple<NoCtor,   NoCtor,   Explicit>, int, int, int>::value, "");
static_assert(!bksge::is_constructible<bksge::tuple<NoCtor,   NoCtor,   Implicit>, int, int, int>::value, "");
static_assert(!bksge::is_constructible<bksge::tuple<NoCtor,   NoCtor,   NoCtor>,   int, int, int>::value, "");

static_assert(!bksge::is_implicitly_constructible<bksge::tuple<Explicit>, int>::value, "");
static_assert( bksge::is_implicitly_constructible<bksge::tuple<Implicit>, int>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::tuple<NoCtor>,   int>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::tuple<Explicit>, int, int>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::tuple<Implicit>, int, int>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::tuple<NoCtor>,   int, int>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::tuple<Explicit, Explicit, Explicit>, int, int, int>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::tuple<Explicit, Explicit, Implicit>, int, int, int>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::tuple<Explicit, Explicit, NoCtor>,   int, int, int>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::tuple<Explicit, Implicit, Explicit>, int, int, int>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::tuple<Explicit, Implicit, Implicit>, int, int, int>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::tuple<Explicit, Implicit, NoCtor>,   int, int, int>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::tuple<Explicit, NoCtor,   Explicit>, int, int, int>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::tuple<Explicit, NoCtor,   Implicit>, int, int, int>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::tuple<Explicit, NoCtor,   NoCtor>,   int, int, int>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::tuple<Implicit, Explicit, Explicit>, int, int, int>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::tuple<Implicit, Explicit, Implicit>, int, int, int>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::tuple<Implicit, Explicit, NoCtor>,   int, int, int>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::tuple<Implicit, Implicit, Explicit>, int, int, int>::value, "");
static_assert( bksge::is_implicitly_constructible<bksge::tuple<Implicit, Implicit, Implicit>, int, int, int>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::tuple<Implicit, Implicit, NoCtor>,   int, int, int>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::tuple<Implicit, NoCtor,   Explicit>, int, int, int>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::tuple<Implicit, NoCtor,   Implicit>, int, int, int>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::tuple<Implicit, NoCtor,   NoCtor>,   int, int, int>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::tuple<NoCtor,   Explicit, Explicit>, int, int, int>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::tuple<NoCtor,   Explicit, Implicit>, int, int, int>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::tuple<NoCtor,   Explicit, NoCtor>,   int, int, int>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::tuple<NoCtor,   Implicit, Explicit>, int, int, int>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::tuple<NoCtor,   Implicit, Implicit>, int, int, int>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::tuple<NoCtor,   Implicit, NoCtor>,   int, int, int>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::tuple<NoCtor,   NoCtor,   Explicit>, int, int, int>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::tuple<NoCtor,   NoCtor,   Implicit>, int, int, int>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::tuple<NoCtor,   NoCtor,   NoCtor>,   int, int, int>::value, "");

static_assert( bksge::is_nothrow_constructible<bksge::tuple<Explicit>, int>::value, "");
static_assert(!bksge::is_nothrow_constructible<bksge::tuple<Implicit>, int>::value, "");
static_assert(!bksge::is_nothrow_constructible<bksge::tuple<NoCtor>,   int>::value, "");
static_assert(!bksge::is_nothrow_constructible<bksge::tuple<Explicit>, int, int>::value, "");
static_assert(!bksge::is_nothrow_constructible<bksge::tuple<Implicit>, int, int>::value, "");
static_assert(!bksge::is_nothrow_constructible<bksge::tuple<NoCtor>,   int, int>::value, "");
static_assert( bksge::is_nothrow_constructible<bksge::tuple<Explicit, Explicit, Explicit>, int, int, int>::value, "");
static_assert(!bksge::is_nothrow_constructible<bksge::tuple<Explicit, Explicit, Implicit>, int, int, int>::value, "");
static_assert(!bksge::is_nothrow_constructible<bksge::tuple<Explicit, Explicit, NoCtor>,   int, int, int>::value, "");
static_assert(!bksge::is_nothrow_constructible<bksge::tuple<Explicit, Implicit, Explicit>, int, int, int>::value, "");
static_assert(!bksge::is_nothrow_constructible<bksge::tuple<Explicit, Implicit, Implicit>, int, int, int>::value, "");
static_assert(!bksge::is_nothrow_constructible<bksge::tuple<Explicit, Implicit, NoCtor>,   int, int, int>::value, "");
static_assert(!bksge::is_nothrow_constructible<bksge::tuple<Explicit, NoCtor,   Explicit>, int, int, int>::value, "");
static_assert(!bksge::is_nothrow_constructible<bksge::tuple<Explicit, NoCtor,   Implicit>, int, int, int>::value, "");
static_assert(!bksge::is_nothrow_constructible<bksge::tuple<Explicit, NoCtor,   NoCtor>,   int, int, int>::value, "");
static_assert(!bksge::is_nothrow_constructible<bksge::tuple<Implicit, Explicit, Explicit>, int, int, int>::value, "");
static_assert(!bksge::is_nothrow_constructible<bksge::tuple<Implicit, Explicit, Implicit>, int, int, int>::value, "");
static_assert(!bksge::is_nothrow_constructible<bksge::tuple<Implicit, Explicit, NoCtor>,   int, int, int>::value, "");
static_assert(!bksge::is_nothrow_constructible<bksge::tuple<Implicit, Implicit, Explicit>, int, int, int>::value, "");
static_assert(!bksge::is_nothrow_constructible<bksge::tuple<Implicit, Implicit, Implicit>, int, int, int>::value, "");
static_assert(!bksge::is_nothrow_constructible<bksge::tuple<Implicit, Implicit, NoCtor>,   int, int, int>::value, "");
static_assert(!bksge::is_nothrow_constructible<bksge::tuple<Implicit, NoCtor,   Explicit>, int, int, int>::value, "");
static_assert(!bksge::is_nothrow_constructible<bksge::tuple<Implicit, NoCtor,   Implicit>, int, int, int>::value, "");
static_assert(!bksge::is_nothrow_constructible<bksge::tuple<Implicit, NoCtor,   NoCtor>,   int, int, int>::value, "");
static_assert(!bksge::is_nothrow_constructible<bksge::tuple<NoCtor,   Explicit, Explicit>, int, int, int>::value, "");
static_assert(!bksge::is_nothrow_constructible<bksge::tuple<NoCtor,   Explicit, Implicit>, int, int, int>::value, "");
static_assert(!bksge::is_nothrow_constructible<bksge::tuple<NoCtor,   Explicit, NoCtor>,   int, int, int>::value, "");
static_assert(!bksge::is_nothrow_constructible<bksge::tuple<NoCtor,   Implicit, Explicit>, int, int, int>::value, "");
static_assert(!bksge::is_nothrow_constructible<bksge::tuple<NoCtor,   Implicit, Implicit>, int, int, int>::value, "");
static_assert(!bksge::is_nothrow_constructible<bksge::tuple<NoCtor,   Implicit, NoCtor>,   int, int, int>::value, "");
static_assert(!bksge::is_nothrow_constructible<bksge::tuple<NoCtor,   NoCtor,   Explicit>, int, int, int>::value, "");
static_assert(!bksge::is_nothrow_constructible<bksge::tuple<NoCtor,   NoCtor,   Implicit>, int, int, int>::value, "");
static_assert(!bksge::is_nothrow_constructible<bksge::tuple<NoCtor,   NoCtor,   NoCtor>,   int, int, int>::value, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline BKSGE_CXX14_CONSTEXPR bool test()
{
	using std::get;
	{
		bksge::tuple<int> t(1);
		VERIFY(get<0>(t) == 1);
	}
	{
		bksge::tuple<int, float> t = {2, 2.5};
		VERIFY(get<0>(t) == 2);
		VERIFY(get<1>(t) == 2.5f);
	}
	{
		bksge::tuple<short, char, double> t = {3, 'b', 4.5};
		VERIFY(get<0>(t) == 3);
		VERIFY(get<1>(t) == 'b');
		VERIFY(get<2>(t) == 4.5);
	}
	{
		bksge::tuple<Explicit> t{5};
		VERIFY(get<0>(t).n == 5);
	}
	{
		bksge::tuple<Implicit> t = {6};
		VERIFY(get<0>(t).n == 6);
	}
	{
		bksge::tuple<Explicit, Implicit> t {7, 8};
		VERIFY(get<0>(t).n == 7);
		VERIFY(get<1>(t).n == 8);
	}
	{
		bksge::tuple<Implicit, Implicit> t = {7, 8};
		VERIFY(get<0>(t).n == 7);
		VERIFY(get<1>(t).n == 8);
	}
	{
		bksge::tuple<Explicit, Implicit, Explicit> t {8, 9, 10};
		VERIFY(get<0>(t).n == 8);
		VERIFY(get<1>(t).n == 9);
		VERIFY(get<2>(t).n == 10);
	}
	{
		bksge::tuple<Implicit, Implicit, Implicit> t = {11, 12, 13};
		VERIFY(get<0>(t).n == 11);
		VERIFY(get<1>(t).n == 12);
		VERIFY(get<2>(t).n == 13);
	}
#if defined(BKSGE_HAS_CXX17_DEDUCTION_GUIDES)
	{
		bksge::tuple t(2);
		static_assert(bksge::is_same<decltype(t), bksge::tuple<int>>::value, "");
		VERIFY(get<0>(t) == 2);
	}
	{
		bksge::tuple t = {3, 4.5};
		static_assert(bksge::is_same<decltype(t), bksge::tuple<int, double>>::value, "");
		VERIFY(get<0>(t) == 3);
		VERIFY(get<1>(t) == 4.5f);
	}
	{
		bksge::tuple t = {5.5f, 6, 'C'};
		static_assert(bksge::is_same<decltype(t), bksge::tuple<float, int, char>>::value, "");
		VERIFY(get<0>(t) == 5.5f);
		VERIFY(get<1>(t) == 6);
		VERIFY(get<2>(t) == 'C');
	}
#endif
	return true;
}

#undef VERIFY

GTEST_TEST(TupleTest, CtorValueMoveTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test()));
}

}	// namespace ctor_value_move_test

}	// namespace bksge_tuple_test

BKSGE_WARNING_POP();
