/**
 *	@file	unit_test_fnd_tuple_tuple_assign_copy.cpp
 *
 *	@brief	operator=(tuple<UTypes...> const&) のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/tuple/tuple.hpp>
#include <bksge/fnd/tuple/get.hpp>
#include <bksge/fnd/type_traits/is_assignable.hpp>
#include <bksge/fnd/type_traits/is_copy_assignable.hpp>
#include <bksge/fnd/type_traits/is_nothrow_assignable.hpp>
#include <bksge/fnd/type_traits/is_nothrow_copy_assignable.hpp>
#include <bksge/fnd/pair.hpp>
#include <bksge/fnd/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

BKSGE_WARNING_PUSH();
BKSGE_WARNING_DISABLE_MSVC(4244);

namespace bksge_tuple_test
{

namespace assign_copy_test
{

struct ThrowOnCopy
{
	BKSGE_CONSTEXPR ThrowOnCopy(int)                           noexcept(true)  {}
	BKSGE_CONSTEXPR ThrowOnCopy(ThrowOnCopy const&)            noexcept(false) {}
	BKSGE_CONSTEXPR ThrowOnCopy(ThrowOnCopy&&)                 noexcept(true)  {}
	BKSGE_CONSTEXPR ThrowOnCopy& operator=(ThrowOnCopy const&) noexcept(false) { return *this; }
	BKSGE_CONSTEXPR ThrowOnCopy& operator=(ThrowOnCopy&&)      noexcept(true)  { return *this; }
	int n = 0;
};

struct NothrowOnCopy
{
	BKSGE_CONSTEXPR NothrowOnCopy(int)                             noexcept(true) {}
	BKSGE_CONSTEXPR NothrowOnCopy(NothrowOnCopy const&)            noexcept(true) {}
	BKSGE_CONSTEXPR NothrowOnCopy(NothrowOnCopy&&)                 noexcept(true) {}
	BKSGE_CONSTEXPR NothrowOnCopy& operator=(NothrowOnCopy const&) noexcept(true) { return *this; }
	BKSGE_CONSTEXPR NothrowOnCopy& operator=(NothrowOnCopy&&)      noexcept(true) { return *this; }
	int n = 0;
};

struct NonCopyable
{
	BKSGE_CONSTEXPR NonCopyable(int)                           noexcept(true) {}
	BKSGE_CONSTEXPR NonCopyable(NonCopyable const&)            noexcept(true) = delete;
	BKSGE_CONSTEXPR NonCopyable(NonCopyable&&)                 noexcept(true) {}
	BKSGE_CONSTEXPR NonCopyable& operator=(NonCopyable const&) noexcept(true) = delete;
	BKSGE_CONSTEXPR NonCopyable& operator=(NonCopyable&&)      noexcept(true) { return *this; }
	int n = 0;
};

struct Empty {};

static_assert( bksge::is_copy_assignable<bksge::tuple<>>::value, "");
static_assert( bksge::is_copy_assignable<bksge::tuple<int>>::value, "");
static_assert( bksge::is_copy_assignable<bksge::tuple<int, int>>::value, "");
static_assert( bksge::is_copy_assignable<bksge::tuple<int, int, int>>::value, "");
static_assert( bksge::is_copy_assignable<bksge::tuple<ThrowOnCopy>>::value, "");
static_assert( bksge::is_copy_assignable<bksge::tuple<NothrowOnCopy>>::value, "");
static_assert(!bksge::is_copy_assignable<bksge::tuple<NonCopyable>>::value, "");
static_assert( bksge::is_copy_assignable<bksge::tuple<ThrowOnCopy, ThrowOnCopy>>::value, "");
static_assert( bksge::is_copy_assignable<bksge::tuple<ThrowOnCopy, NothrowOnCopy>>::value, "");
static_assert(!bksge::is_copy_assignable<bksge::tuple<ThrowOnCopy, NonCopyable>>::value, "");
static_assert( bksge::is_copy_assignable<bksge::tuple<NothrowOnCopy, ThrowOnCopy>>::value, "");
static_assert( bksge::is_copy_assignable<bksge::tuple<NothrowOnCopy, NothrowOnCopy>>::value, "");
static_assert(!bksge::is_copy_assignable<bksge::tuple<NothrowOnCopy, NonCopyable>>::value, "");
static_assert(!bksge::is_copy_assignable<bksge::tuple<NonCopyable, ThrowOnCopy>>::value, "");
static_assert(!bksge::is_copy_assignable<bksge::tuple<NonCopyable, NothrowOnCopy>>::value, "");
static_assert(!bksge::is_copy_assignable<bksge::tuple<NonCopyable, NonCopyable>>::value, "");
static_assert( bksge::is_copy_assignable<bksge::tuple<NothrowOnCopy, NothrowOnCopy, NothrowOnCopy>>::value, "");
static_assert( bksge::is_copy_assignable<bksge::tuple<ThrowOnCopy,   NothrowOnCopy, NothrowOnCopy>>::value, "");
static_assert( bksge::is_copy_assignable<bksge::tuple<NothrowOnCopy, ThrowOnCopy,   NothrowOnCopy>>::value, "");
static_assert( bksge::is_copy_assignable<bksge::tuple<NothrowOnCopy, NothrowOnCopy, ThrowOnCopy>>::value, "");
static_assert(!bksge::is_copy_assignable<bksge::tuple<NonCopyable,   NothrowOnCopy, NothrowOnCopy>>::value, "");
static_assert(!bksge::is_copy_assignable<bksge::tuple<NothrowOnCopy, NonCopyable,   NothrowOnCopy>>::value, "");
static_assert(!bksge::is_copy_assignable<bksge::tuple<NothrowOnCopy, NothrowOnCopy, NonCopyable>>::value, "");
static_assert( bksge::is_assignable<bksge::tuple<ThrowOnCopy>,   bksge::tuple<int> const&>::value, "");
static_assert( bksge::is_assignable<bksge::tuple<NothrowOnCopy>, bksge::tuple<int> const&>::value, "");
static_assert( bksge::is_assignable<bksge::tuple<NonCopyable>,   bksge::tuple<int> const&>::value, "");
static_assert(!bksge::is_assignable<bksge::tuple<ThrowOnCopy>,   bksge::tuple<NothrowOnCopy> const&>::value, "");
static_assert( bksge::is_assignable<bksge::tuple<int, int>, bksge::pair<int, int> const&>::value, "");
static_assert( bksge::is_assignable<bksge::tuple<ThrowOnCopy, ThrowOnCopy>,   bksge::pair<ThrowOnCopy, ThrowOnCopy> const&>::value, "");
static_assert( bksge::is_assignable<bksge::tuple<ThrowOnCopy, NothrowOnCopy>, bksge::pair<ThrowOnCopy, NothrowOnCopy> const&>::value, "");
static_assert(!bksge::is_assignable<bksge::tuple<ThrowOnCopy, NonCopyable>,   bksge::pair<ThrowOnCopy, NonCopyable> const&>::value, "");
static_assert( bksge::is_assignable<bksge::tuple<NothrowOnCopy, ThrowOnCopy>,   bksge::pair<NothrowOnCopy, ThrowOnCopy> const&>::value, "");
static_assert( bksge::is_assignable<bksge::tuple<NothrowOnCopy, NothrowOnCopy>, bksge::pair<NothrowOnCopy, NothrowOnCopy> const&>::value, "");
static_assert(!bksge::is_assignable<bksge::tuple<NothrowOnCopy, NonCopyable>,   bksge::pair<NothrowOnCopy, NonCopyable> const&>::value, "");

static_assert( bksge::is_nothrow_copy_assignable<bksge::tuple<>>::value, "");
static_assert( bksge::is_nothrow_copy_assignable<bksge::tuple<int>>::value, "");
static_assert( bksge::is_nothrow_copy_assignable<bksge::tuple<int, int>>::value, "");
static_assert( bksge::is_nothrow_copy_assignable<bksge::tuple<int, int, int>>::value, "");
static_assert(!bksge::is_nothrow_copy_assignable<bksge::tuple<ThrowOnCopy>>::value, "");
static_assert( bksge::is_nothrow_copy_assignable<bksge::tuple<NothrowOnCopy>>::value, "");
static_assert(!bksge::is_nothrow_copy_assignable<bksge::tuple<NonCopyable>>::value, "");
static_assert(!bksge::is_nothrow_copy_assignable<bksge::tuple<ThrowOnCopy, ThrowOnCopy>>::value, "");
static_assert(!bksge::is_nothrow_copy_assignable<bksge::tuple<ThrowOnCopy, NothrowOnCopy>>::value, "");
static_assert(!bksge::is_nothrow_copy_assignable<bksge::tuple<ThrowOnCopy, NonCopyable>>::value, "");
static_assert(!bksge::is_nothrow_copy_assignable<bksge::tuple<NothrowOnCopy, ThrowOnCopy>>::value, "");
static_assert( bksge::is_nothrow_copy_assignable<bksge::tuple<NothrowOnCopy, NothrowOnCopy>>::value, "");
static_assert(!bksge::is_nothrow_copy_assignable<bksge::tuple<NothrowOnCopy, NonCopyable>>::value, "");
static_assert(!bksge::is_nothrow_copy_assignable<bksge::tuple<NonCopyable, ThrowOnCopy>>::value, "");
static_assert(!bksge::is_nothrow_copy_assignable<bksge::tuple<NonCopyable, NothrowOnCopy>>::value, "");
static_assert(!bksge::is_nothrow_copy_assignable<bksge::tuple<NonCopyable, NonCopyable>>::value, "");
static_assert( bksge::is_nothrow_copy_assignable<bksge::tuple<NothrowOnCopy, NothrowOnCopy, NothrowOnCopy>>::value, "");
static_assert(!bksge::is_nothrow_copy_assignable<bksge::tuple<ThrowOnCopy,   NothrowOnCopy, NothrowOnCopy>>::value, "");
static_assert(!bksge::is_nothrow_copy_assignable<bksge::tuple<NothrowOnCopy, ThrowOnCopy,   NothrowOnCopy>>::value, "");
static_assert(!bksge::is_nothrow_copy_assignable<bksge::tuple<NothrowOnCopy, NothrowOnCopy, ThrowOnCopy>>::value, "");
static_assert(!bksge::is_nothrow_copy_assignable<bksge::tuple<NonCopyable,   NothrowOnCopy, NothrowOnCopy>>::value, "");
static_assert(!bksge::is_nothrow_copy_assignable<bksge::tuple<NothrowOnCopy, NonCopyable,   NothrowOnCopy>>::value, "");
static_assert(!bksge::is_nothrow_copy_assignable<bksge::tuple<NothrowOnCopy, NothrowOnCopy, NonCopyable>>::value, "");
static_assert( bksge::is_nothrow_assignable<bksge::tuple<ThrowOnCopy>,   bksge::tuple<int> const&>::value, "");
static_assert( bksge::is_nothrow_assignable<bksge::tuple<NothrowOnCopy>, bksge::tuple<int> const&>::value, "");
static_assert( bksge::is_nothrow_assignable<bksge::tuple<NonCopyable>,   bksge::tuple<int> const&>::value, "");
static_assert(!bksge::is_nothrow_assignable<bksge::tuple<ThrowOnCopy>,   bksge::tuple<NothrowOnCopy> const&>::value, "");
static_assert( bksge::is_nothrow_assignable<bksge::tuple<int, int>, bksge::pair<int, int> const&>::value, "");
static_assert(!bksge::is_nothrow_assignable<bksge::tuple<ThrowOnCopy, ThrowOnCopy>,   bksge::pair<ThrowOnCopy, ThrowOnCopy> const&>::value, "");
static_assert(!bksge::is_nothrow_assignable<bksge::tuple<ThrowOnCopy, NothrowOnCopy>, bksge::pair<ThrowOnCopy, NothrowOnCopy> const&>::value, "");
static_assert(!bksge::is_nothrow_assignable<bksge::tuple<ThrowOnCopy, NonCopyable>,   bksge::pair<ThrowOnCopy, NonCopyable> const&>::value, "");
static_assert(!bksge::is_nothrow_assignable<bksge::tuple<NothrowOnCopy, ThrowOnCopy>,   bksge::pair<NothrowOnCopy, ThrowOnCopy> const&>::value, "");
static_assert( bksge::is_nothrow_assignable<bksge::tuple<NothrowOnCopy, NothrowOnCopy>, bksge::pair<NothrowOnCopy, NothrowOnCopy> const&>::value, "");
static_assert(!bksge::is_nothrow_assignable<bksge::tuple<NothrowOnCopy, NonCopyable>,   bksge::pair<NothrowOnCopy, NonCopyable> const&>::value, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline BKSGE_CXX14_CONSTEXPR bool test()
{
	using std::get;
	{
		bksge::tuple<Empty> const t1;
		bksge::tuple<Empty>       t2;
		t2 = t1;
	}
	{
		bksge::tuple<Empty, Empty> const t1;
		bksge::tuple<Empty, Empty>       t2;
		t2 = t1;
	}
	{
		bksge::tuple<Empty, Empty, Empty> const t1;
		bksge::tuple<Empty, Empty, Empty>       t2;
		t2 = t1;
	}
	{
		bksge::tuple<int> const t1(1);
		bksge::tuple<int>       t2(2);
		VERIFY(get<0>(t2) == 2);
		t2 = t1;
		VERIFY(get<0>(t2) == 1);
	}
	{
		bksge::tuple<float> const t1(1);
		bksge::tuple<double>      t2(2);
		VERIFY(get<0>(t2) == 2);
		t2 = t1;
		VERIFY(get<0>(t2) == 1);
	}
	{
		bksge::tuple<int, float> const t1(2, 0.5f);
		bksge::tuple<int, float>       t2(3, 4.5f);
		VERIFY(get<0>(t2) == 3);
		VERIFY(get<1>(t2) == 4.5f);
		t2 = t1;
		VERIFY(get<0>(t2) == 2);
		VERIFY(get<1>(t2) == 0.5f);
	}
	{
		bksge::tuple<int, float> const t1(2, 0.5f);
		bksge::tuple<long, double>     t2(3, 4.5f);
		VERIFY(get<0>(t2) == 3);
		VERIFY(get<1>(t2) == 4.5f);
		t2 = t1;
		VERIFY(get<0>(t2) == 2);
		VERIFY(get<1>(t2) == 0.5f);
	}
	{
		bksge::pair<int, float> const t1(2, 0.5f);
		bksge::tuple<int, float>      t2(3, 4.5f);
		VERIFY(get<0>(t2) == 3);
		VERIFY(get<1>(t2) == 4.5f);
		t2 = t1;
		VERIFY(get<0>(t2) == 2);
		VERIFY(get<1>(t2) == 0.5f);
	}
	{
		bksge::pair<int, float> const t1(2, 0.5f);
		bksge::tuple<long, double>    t2(3, 4.5f);
		VERIFY(get<0>(t2) == 3);
		VERIFY(get<1>(t2) == 4.5f);
		t2 = t1;
		VERIFY(get<0>(t2) == 2);
		VERIFY(get<1>(t2) == 0.5f);
	}
	{
		bksge::tuple<int, float, char> const t1(2, 0.5f, 'a');
		bksge::tuple<int, float, char>       t2(3, 4.5f, 'b');
		VERIFY(get<0>(t2) == 3);
		VERIFY(get<1>(t2) == 4.5f);
		VERIFY(get<2>(t2) == 'b');
		t2 = t1;
		VERIFY(get<0>(t2) == 2);
		VERIFY(get<1>(t2) == 0.5f);
		VERIFY(get<2>(t2) == 'a');
	}
	{
		bksge::tuple<int, float, char> const t1(2, 0.5f, 'a');
		bksge::tuple<long, double, char>     t2(3, 4.5f, 'b');
		VERIFY(get<0>(t2) == 3);
		VERIFY(get<1>(t2) == 4.5f);
		VERIFY(get<2>(t2) == 'b');
		t2 = t1;
		VERIFY(get<0>(t2) == 2);
		VERIFY(get<1>(t2) == 0.5f);
		VERIFY(get<2>(t2) == 'a');
	}
	return true;
}

#undef VERIFY

GTEST_TEST(TupleTest, AssignCopyTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test()));
}

}	// namespace assign_copy_test

}	// namespace bksge_tuple_test

BKSGE_WARNING_POP();
