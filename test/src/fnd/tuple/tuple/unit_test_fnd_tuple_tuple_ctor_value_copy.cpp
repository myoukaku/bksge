/**
 *	@file	unit_test_fnd_tuple_tuple_ctor_value_copy.cpp
 *
 *	@brief	tuple::tuple(Types const&...) のテスト
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

namespace bksge_tuple_test
{

namespace ctor_value_copy_test
{

struct Explicit
{
	explicit BKSGE_CONSTEXPR Explicit(int x) : n(x) {}
	explicit BKSGE_CONSTEXPR Explicit(Explicit const& rhs) noexcept : n(rhs.n) {}
	int n;
};

struct Implicit
{
	BKSGE_CONSTEXPR Implicit(int x) : n(x) {}
	BKSGE_CONSTEXPR Implicit(Implicit const& rhs) : n(rhs.n) {}
	int n;
};

struct NoCopy
{
	BKSGE_CONSTEXPR NoCopy(int x) : n(x) {}
	BKSGE_CONSTEXPR NoCopy(NoCopy const& rhs) = delete;
	int n;
};

static_assert(!bksge::is_constructible<bksge::tuple<>, int const&>::value, "");
static_assert( bksge::is_constructible<bksge::tuple<int>, int const&>::value, "");
static_assert( bksge::is_constructible<bksge::tuple<Explicit>, Explicit const&>::value, "");
static_assert( bksge::is_constructible<bksge::tuple<Implicit>, Implicit const&>::value, "");
static_assert(!bksge::is_constructible<bksge::tuple<NoCopy>,   NoCopy   const&>::value, "");
static_assert(!bksge::is_constructible<bksge::tuple<Explicit>, Explicit const&, Explicit const&>::value, "");
static_assert(!bksge::is_constructible<bksge::tuple<Implicit>, Implicit const&, Implicit const&>::value, "");
static_assert(!bksge::is_constructible<bksge::tuple<NoCopy>,   NoCopy   const&, NoCopy   const&>::value, "");
static_assert( bksge::is_constructible<bksge::tuple<Explicit, Explicit, Explicit>, Explicit const&, Explicit const&, Explicit const&>::value, "");
static_assert( bksge::is_constructible<bksge::tuple<Explicit, Explicit, Implicit>, Explicit const&, Explicit const&, Implicit const&>::value, "");
static_assert(!bksge::is_constructible<bksge::tuple<Explicit, Explicit, NoCopy>,   Explicit const&, Explicit const&, NoCopy   const&>::value, "");
static_assert( bksge::is_constructible<bksge::tuple<Explicit, Implicit, Explicit>, Explicit const&, Implicit const&, Explicit const&>::value, "");
static_assert( bksge::is_constructible<bksge::tuple<Explicit, Implicit, Implicit>, Explicit const&, Implicit const&, Implicit const&>::value, "");
static_assert(!bksge::is_constructible<bksge::tuple<Explicit, Implicit, NoCopy>,   Explicit const&, Implicit const&, NoCopy   const&>::value, "");
static_assert(!bksge::is_constructible<bksge::tuple<Explicit, NoCopy,   Explicit>, Explicit const&, NoCopy   const&, Explicit const&>::value, "");
static_assert(!bksge::is_constructible<bksge::tuple<Explicit, NoCopy,   Implicit>, Explicit const&, NoCopy   const&, Implicit const&>::value, "");
static_assert(!bksge::is_constructible<bksge::tuple<Explicit, NoCopy,   NoCopy>,   Explicit const&, NoCopy   const&, NoCopy   const&>::value, "");
static_assert( bksge::is_constructible<bksge::tuple<Implicit, Explicit, Explicit>, Implicit const&, Explicit const&, Explicit const&>::value, "");
static_assert( bksge::is_constructible<bksge::tuple<Implicit, Explicit, Implicit>, Implicit const&, Explicit const&, Implicit const&>::value, "");
static_assert(!bksge::is_constructible<bksge::tuple<Implicit, Explicit, NoCopy>,   Implicit const&, Explicit const&, NoCopy   const&>::value, "");
static_assert( bksge::is_constructible<bksge::tuple<Implicit, Implicit, Explicit>, Implicit const&, Implicit const&, Explicit const&>::value, "");
static_assert( bksge::is_constructible<bksge::tuple<Implicit, Implicit, Implicit>, Implicit const&, Implicit const&, Implicit const&>::value, "");
static_assert(!bksge::is_constructible<bksge::tuple<Implicit, Implicit, NoCopy>,   Implicit const&, Implicit const&, NoCopy   const&>::value, "");
static_assert(!bksge::is_constructible<bksge::tuple<Implicit, NoCopy,   Explicit>, Implicit const&, NoCopy   const&, Explicit const&>::value, "");
static_assert(!bksge::is_constructible<bksge::tuple<Implicit, NoCopy,   Implicit>, Implicit const&, NoCopy   const&, Implicit const&>::value, "");
static_assert(!bksge::is_constructible<bksge::tuple<Implicit, NoCopy,   NoCopy>,   Implicit const&, NoCopy   const&, NoCopy   const&>::value, "");
static_assert(!bksge::is_constructible<bksge::tuple<NoCopy,   Explicit, Explicit>, NoCopy   const&, Explicit const&, Explicit const&>::value, "");
static_assert(!bksge::is_constructible<bksge::tuple<NoCopy,   Explicit, Implicit>, NoCopy   const&, Explicit const&, Implicit const&>::value, "");
static_assert(!bksge::is_constructible<bksge::tuple<NoCopy,   Explicit, NoCopy>,   NoCopy   const&, Explicit const&, NoCopy   const&>::value, "");
static_assert(!bksge::is_constructible<bksge::tuple<NoCopy,   Implicit, Explicit>, NoCopy   const&, Implicit const&, Explicit const&>::value, "");
static_assert(!bksge::is_constructible<bksge::tuple<NoCopy,   Implicit, Implicit>, NoCopy   const&, Implicit const&, Implicit const&>::value, "");
static_assert(!bksge::is_constructible<bksge::tuple<NoCopy,   Implicit, NoCopy>,   NoCopy   const&, Implicit const&, NoCopy   const&>::value, "");
static_assert(!bksge::is_constructible<bksge::tuple<NoCopy,   NoCopy,   Explicit>, NoCopy   const&, NoCopy   const&, Explicit const&>::value, "");
static_assert(!bksge::is_constructible<bksge::tuple<NoCopy,   NoCopy,   Implicit>, NoCopy   const&, NoCopy   const&, Implicit const&>::value, "");
static_assert(!bksge::is_constructible<bksge::tuple<NoCopy,   NoCopy,   NoCopy>,   NoCopy   const&, NoCopy   const&, NoCopy   const&>::value, "");

static_assert(!bksge::is_implicitly_constructible<bksge::tuple<Explicit>, Explicit const&>::value, "");
static_assert( bksge::is_implicitly_constructible<bksge::tuple<Implicit>, Implicit const&>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::tuple<NoCopy>,   NoCopy   const&>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::tuple<Explicit>, Explicit const&, Explicit const&>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::tuple<Implicit>, Implicit const&, Implicit const&>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::tuple<NoCopy>,   NoCopy   const&, NoCopy   const&>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::tuple<Explicit, Explicit, Explicit>, Explicit const&, Explicit const&, Explicit const&>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::tuple<Explicit, Explicit, Implicit>, Explicit const&, Explicit const&, Implicit const&>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::tuple<Explicit, Explicit, NoCopy>,   Explicit const&, Explicit const&, NoCopy   const&>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::tuple<Explicit, Implicit, Explicit>, Explicit const&, Implicit const&, Explicit const&>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::tuple<Explicit, Implicit, Implicit>, Explicit const&, Implicit const&, Implicit const&>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::tuple<Explicit, Implicit, NoCopy>,   Explicit const&, Implicit const&, NoCopy   const&>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::tuple<Explicit, NoCopy,   Explicit>, Explicit const&, NoCopy   const&, Explicit const&>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::tuple<Explicit, NoCopy,   Implicit>, Explicit const&, NoCopy   const&, Implicit const&>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::tuple<Explicit, NoCopy,   NoCopy>,   Explicit const&, NoCopy   const&, NoCopy   const&>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::tuple<Implicit, Explicit, Explicit>, Implicit const&, Explicit const&, Explicit const&>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::tuple<Implicit, Explicit, Implicit>, Implicit const&, Explicit const&, Implicit const&>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::tuple<Implicit, Explicit, NoCopy>,   Implicit const&, Explicit const&, NoCopy   const&>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::tuple<Implicit, Implicit, Explicit>, Implicit const&, Implicit const&, Explicit const&>::value, "");
static_assert( bksge::is_implicitly_constructible<bksge::tuple<Implicit, Implicit, Implicit>, Implicit const&, Implicit const&, Implicit const&>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::tuple<Implicit, Implicit, NoCopy>,   Implicit const&, Implicit const&, NoCopy   const&>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::tuple<Implicit, NoCopy,   Explicit>, Implicit const&, NoCopy   const&, Explicit const&>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::tuple<Implicit, NoCopy,   Implicit>, Implicit const&, NoCopy   const&, Implicit const&>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::tuple<Implicit, NoCopy,   NoCopy>,   Implicit const&, NoCopy   const&, NoCopy   const&>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::tuple<NoCopy,   Explicit, Explicit>, NoCopy   const&, Explicit const&, Explicit const&>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::tuple<NoCopy,   Explicit, Implicit>, NoCopy   const&, Explicit const&, Implicit const&>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::tuple<NoCopy,   Explicit, NoCopy>,   NoCopy   const&, Explicit const&, NoCopy   const&>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::tuple<NoCopy,   Implicit, Explicit>, NoCopy   const&, Implicit const&, Explicit const&>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::tuple<NoCopy,   Implicit, Implicit>, NoCopy   const&, Implicit const&, Implicit const&>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::tuple<NoCopy,   Implicit, NoCopy>,   NoCopy   const&, Implicit const&, NoCopy   const&>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::tuple<NoCopy,   NoCopy,   Explicit>, NoCopy   const&, NoCopy   const&, Explicit const&>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::tuple<NoCopy,   NoCopy,   Implicit>, NoCopy   const&, NoCopy   const&, Implicit const&>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::tuple<NoCopy,   NoCopy,   NoCopy>,   NoCopy   const&, NoCopy   const&, NoCopy   const&>::value, "");

static_assert( bksge::is_nothrow_constructible<bksge::tuple<Explicit>, Explicit const&>::value, "");
static_assert(!bksge::is_nothrow_constructible<bksge::tuple<Implicit>, Implicit const&>::value, "");
static_assert(!bksge::is_nothrow_constructible<bksge::tuple<NoCopy>,   NoCopy   const&>::value, "");
static_assert(!bksge::is_nothrow_constructible<bksge::tuple<Explicit>, Explicit const&, Explicit const&>::value, "");
static_assert(!bksge::is_nothrow_constructible<bksge::tuple<Implicit>, Implicit const&, Implicit const&>::value, "");
static_assert(!bksge::is_nothrow_constructible<bksge::tuple<NoCopy>,   NoCopy   const&, NoCopy   const&>::value, "");
static_assert( bksge::is_nothrow_constructible<bksge::tuple<Explicit, Explicit, Explicit>, Explicit const&, Explicit const&, Explicit const&>::value, "");
static_assert(!bksge::is_nothrow_constructible<bksge::tuple<Explicit, Explicit, Implicit>, Explicit const&, Explicit const&, Implicit const&>::value, "");
static_assert(!bksge::is_nothrow_constructible<bksge::tuple<Explicit, Explicit, NoCopy>,   Explicit const&, Explicit const&, NoCopy   const&>::value, "");
static_assert(!bksge::is_nothrow_constructible<bksge::tuple<Explicit, Implicit, Explicit>, Explicit const&, Implicit const&, Explicit const&>::value, "");
static_assert(!bksge::is_nothrow_constructible<bksge::tuple<Explicit, Implicit, Implicit>, Explicit const&, Implicit const&, Implicit const&>::value, "");
static_assert(!bksge::is_nothrow_constructible<bksge::tuple<Explicit, Implicit, NoCopy>,   Explicit const&, Implicit const&, NoCopy   const&>::value, "");
static_assert(!bksge::is_nothrow_constructible<bksge::tuple<Explicit, NoCopy,   Explicit>, Explicit const&, NoCopy   const&, Explicit const&>::value, "");
static_assert(!bksge::is_nothrow_constructible<bksge::tuple<Explicit, NoCopy,   Implicit>, Explicit const&, NoCopy   const&, Implicit const&>::value, "");
static_assert(!bksge::is_nothrow_constructible<bksge::tuple<Explicit, NoCopy,   NoCopy>,   Explicit const&, NoCopy   const&, NoCopy   const&>::value, "");
static_assert(!bksge::is_nothrow_constructible<bksge::tuple<Implicit, Explicit, Explicit>, Implicit const&, Explicit const&, Explicit const&>::value, "");
static_assert(!bksge::is_nothrow_constructible<bksge::tuple<Implicit, Explicit, Implicit>, Implicit const&, Explicit const&, Implicit const&>::value, "");
static_assert(!bksge::is_nothrow_constructible<bksge::tuple<Implicit, Explicit, NoCopy>,   Implicit const&, Explicit const&, NoCopy   const&>::value, "");
static_assert(!bksge::is_nothrow_constructible<bksge::tuple<Implicit, Implicit, Explicit>, Implicit const&, Implicit const&, Explicit const&>::value, "");
static_assert(!bksge::is_nothrow_constructible<bksge::tuple<Implicit, Implicit, Implicit>, Implicit const&, Implicit const&, Implicit const&>::value, "");
static_assert(!bksge::is_nothrow_constructible<bksge::tuple<Implicit, Implicit, NoCopy>,   Implicit const&, Implicit const&, NoCopy   const&>::value, "");
static_assert(!bksge::is_nothrow_constructible<bksge::tuple<Implicit, NoCopy,   Explicit>, Implicit const&, NoCopy   const&, Explicit const&>::value, "");
static_assert(!bksge::is_nothrow_constructible<bksge::tuple<Implicit, NoCopy,   Implicit>, Implicit const&, NoCopy   const&, Implicit const&>::value, "");
static_assert(!bksge::is_nothrow_constructible<bksge::tuple<Implicit, NoCopy,   NoCopy>,   Implicit const&, NoCopy   const&, NoCopy   const&>::value, "");
static_assert(!bksge::is_nothrow_constructible<bksge::tuple<NoCopy,   Explicit, Explicit>, NoCopy   const&, Explicit const&, Explicit const&>::value, "");
static_assert(!bksge::is_nothrow_constructible<bksge::tuple<NoCopy,   Explicit, Implicit>, NoCopy   const&, Explicit const&, Implicit const&>::value, "");
static_assert(!bksge::is_nothrow_constructible<bksge::tuple<NoCopy,   Explicit, NoCopy>,   NoCopy   const&, Explicit const&, NoCopy   const&>::value, "");
static_assert(!bksge::is_nothrow_constructible<bksge::tuple<NoCopy,   Implicit, Explicit>, NoCopy   const&, Implicit const&, Explicit const&>::value, "");
static_assert(!bksge::is_nothrow_constructible<bksge::tuple<NoCopy,   Implicit, Implicit>, NoCopy   const&, Implicit const&, Implicit const&>::value, "");
static_assert(!bksge::is_nothrow_constructible<bksge::tuple<NoCopy,   Implicit, NoCopy>,   NoCopy   const&, Implicit const&, NoCopy   const&>::value, "");
static_assert(!bksge::is_nothrow_constructible<bksge::tuple<NoCopy,   NoCopy,   Explicit>, NoCopy   const&, NoCopy   const&, Explicit const&>::value, "");
static_assert(!bksge::is_nothrow_constructible<bksge::tuple<NoCopy,   NoCopy,   Implicit>, NoCopy   const&, NoCopy   const&, Implicit const&>::value, "");
static_assert(!bksge::is_nothrow_constructible<bksge::tuple<NoCopy,   NoCopy,   NoCopy>,   NoCopy   const&, NoCopy   const&, NoCopy   const&>::value, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline BKSGE_CXX14_CONSTEXPR bool test()
{
	using std::get;
	{
		int const x1 = 1;
		bksge::tuple<int> t(x1);
		VERIFY(get<0>(t) == 1);
	}
	{
		int   const x1 = 2;
		float const x2 = 2.5f;
		bksge::tuple<int, float> t = {x1, x2};
		VERIFY(get<0>(t) == 2);
		VERIFY(get<1>(t) == 2.5f);
	}
	{
		int    const x1 = 3;
		char   const x2 = 'b';
		double const x3 = 4.5;
		bksge::tuple<int, char, double> t = {x1, x2, x3};
		VERIFY(get<0>(t) == 3);
		VERIFY(get<1>(t) == 'b');
		VERIFY(get<2>(t) == 4.5);
	}
	{
		Explicit const x1(5);
		bksge::tuple<Explicit> t{x1};
		VERIFY(get<0>(t).n == 5);
	}
	{
		Implicit const x1(6);
		bksge::tuple<Implicit> t = {x1};
		VERIFY(get<0>(t).n == 6);
	}
	{
		Implicit const x1(7);
		bksge::tuple<Implicit, Implicit> t = {x1, x1};
		VERIFY(get<0>(t).n == 7);
		VERIFY(get<1>(t).n == 7);
	}
	{
		Explicit const x1(8);
		Implicit const x2(9);
		bksge::tuple<Explicit, Implicit, Explicit> t {x1, x2, x1};
		VERIFY(get<0>(t).n == 8);
		VERIFY(get<1>(t).n == 9);
		VERIFY(get<2>(t).n == 8);
	}
	{
		Implicit const x1(1);
		Implicit const x2(2);
		Implicit const x3(3);
		bksge::tuple<Implicit, Implicit, Implicit> t = {x1, x2, x3};
		VERIFY(get<0>(t).n == 1);
		VERIFY(get<1>(t).n == 2);
		VERIFY(get<2>(t).n == 3);
	}
#if defined(BKSGE_HAS_CXX17_DEDUCTION_GUIDES)
	{
		int const x1 = 2;
		bksge::tuple t(x1);
		static_assert(bksge::is_same<decltype(t), bksge::tuple<int>>::value, "");
		VERIFY(get<0>(t) == 2);
	}
	{
		int    const x1 = 3;
		double const x2 = 4.5;
		bksge::tuple t = {x1, x2};
		static_assert(bksge::is_same<decltype(t), bksge::tuple<int, double>>::value, "");
		VERIFY(get<0>(t) == 3);
		VERIFY(get<1>(t) == 4.5f);
	}
	{
		float const x1 = 5.5f;
		int   const x2 = 6;
		char  const x3 = 'C';
		bksge::tuple t = {x1, x2, x3};
		static_assert(bksge::is_same<decltype(t), bksge::tuple<float, int, char>>::value, "");
		VERIFY(get<0>(t) == 5.5f);
		VERIFY(get<1>(t) == 6);
		VERIFY(get<2>(t) == 'C');
	}
#endif
	return true;
}

#undef VERIFY

GTEST_TEST(TupleTest, CtorValueCopyTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test()));
}

}	// namespace ctor_value_copy_test

}	// namespace bksge_tuple_test
