/**
 *	@file	unit_test_fnd_variant_swap.cpp
 *
 *	@brief	swap のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/variant/variant.hpp>
#include <bksge/fnd/variant/get.hpp>
#include <bksge/fnd/type_traits/is_swappable.hpp>
#include <bksge/fnd/type_traits/is_nothrow_swappable.hpp>
#include <bksge/fnd/utility/declval.hpp>
#include <bksge/fnd/utility/in_place_index.hpp>
#include <bksge/fnd/cstdlib/abort.hpp>
#include <bksge/fnd/config.hpp>
#include <utility>
#include <gtest/gtest.h>
#include "fnd/variant/test_convertible.hpp"
#include "fnd/variant/test_macros.hpp"
#include "fnd/variant/variant_test_helpers.hpp"

BKSGE_WARNING_PUSH();
BKSGE_WARNING_DISABLE_MSVC(4702);	// 制御が渡らないコードです

namespace bksge_variant_test
{

namespace swap_test
{

struct NotSwappable {};
void swap(NotSwappable&, NotSwappable&) = delete;

struct NotCopyable
{
	NotCopyable() = default;
	NotCopyable(const NotCopyable&) = delete;
	NotCopyable& operator=(const NotCopyable&) = delete;
};

struct NotCopyableWithSwap
{
	NotCopyableWithSwap() = default;
	NotCopyableWithSwap(const NotCopyableWithSwap&) = delete;
	NotCopyableWithSwap& operator=(const NotCopyableWithSwap&) = delete;
};

void swap(NotCopyableWithSwap&, NotCopyableWithSwap) {}

struct NotMoveAssignable
{
	NotMoveAssignable() = default;
	NotMoveAssignable(NotMoveAssignable&&) = default;
	NotMoveAssignable& operator=(NotMoveAssignable&&) = delete;
};

struct NotMoveAssignableWithSwap
{
	NotMoveAssignableWithSwap() = default;
	NotMoveAssignableWithSwap(NotMoveAssignableWithSwap&&) = default;
	NotMoveAssignableWithSwap& operator=(NotMoveAssignableWithSwap&&) = delete;
};

void swap(NotMoveAssignableWithSwap&, NotMoveAssignableWithSwap&) noexcept {}

template <bool Throws> void do_throw() {}

template <> void do_throw<true>()
{
#if !defined(BKSGE_NO_EXCEPTIONS)
	throw 42;
#else
	bksge::abort();
#endif
}

template <bool NT_Copy, bool NT_Move, bool NT_CopyAssign, bool NT_MoveAssign,
	bool NT_Swap, bool EnableSwap = true>
struct NothrowTypeImp
{
	static int move_called;
	static int move_assign_called;
	static int swap_called;
	static void reset() { move_called = move_assign_called = swap_called = 0; }
	NothrowTypeImp() = default;
	explicit NothrowTypeImp(int v) : value(v) {}
	NothrowTypeImp(const NothrowTypeImp& o) noexcept(NT_Copy) : value(o.value)
	{
		assert(false);
	} // never called by test
	NothrowTypeImp(NothrowTypeImp&& o) noexcept(NT_Move) : value(o.value)
	{
		++move_called;
		do_throw<!NT_Move>();
		o.value = -1;
	}
	NothrowTypeImp& operator=(const NothrowTypeImp&) noexcept(NT_CopyAssign)
	{
		assert(false);
		return *this;
	} // never called by the tests
	NothrowTypeImp& operator=(NothrowTypeImp&& o) noexcept(NT_MoveAssign)
	{
		++move_assign_called;
		do_throw<!NT_MoveAssign>();
		value = o.value;
		o.value = -1;
		return *this;
	}
	int value;
};
template <bool NT_Copy, bool NT_Move, bool NT_CopyAssign, bool NT_MoveAssign,
	bool NT_Swap, bool EnableSwap>
	int NothrowTypeImp<NT_Copy, NT_Move, NT_CopyAssign, NT_MoveAssign, NT_Swap,
	EnableSwap>::move_called = 0;
template <bool NT_Copy, bool NT_Move, bool NT_CopyAssign, bool NT_MoveAssign,
	bool NT_Swap, bool EnableSwap>
	int NothrowTypeImp<NT_Copy, NT_Move, NT_CopyAssign, NT_MoveAssign, NT_Swap,
	EnableSwap>::move_assign_called = 0;
template <bool NT_Copy, bool NT_Move, bool NT_CopyAssign, bool NT_MoveAssign,
	bool NT_Swap, bool EnableSwap>
	int NothrowTypeImp<NT_Copy, NT_Move, NT_CopyAssign, NT_MoveAssign, NT_Swap,
	EnableSwap>::swap_called = 0;

template <bool NT_Copy, bool NT_Move, bool NT_CopyAssign, bool NT_MoveAssign,
	bool NT_Swap>
	void swap(NothrowTypeImp<NT_Copy, NT_Move, NT_CopyAssign, NT_MoveAssign,
		NT_Swap, true>& lhs,
		NothrowTypeImp<NT_Copy, NT_Move, NT_CopyAssign, NT_MoveAssign,
		NT_Swap, true>& rhs) noexcept(NT_Swap)
{
	lhs.swap_called++;
	do_throw<!NT_Swap>();
	int tmp = lhs.value;
	lhs.value = rhs.value;
	rhs.value = tmp;
}

// throwing copy, nothrow move ctor/assign, no swap provided
using NothrowMoveable = NothrowTypeImp<false, true, false, true, false, false>;
// throwing copy and move assign, nothrow move ctor, no swap provided
using NothrowMoveCtor = NothrowTypeImp<false, true, false, false, false, false>;
// nothrow move ctor, throwing move assignment, swap provided
using NothrowMoveCtorWithThrowingSwap = NothrowTypeImp<false, true, false, false, false, true>;
// throwing move ctor, nothrow move assignment, no swap provided
using ThrowingMoveCtor = NothrowTypeImp<false, false, false, true, false, false>;
// throwing special members, nothrowing swap
using ThrowingTypeWithNothrowSwap = NothrowTypeImp<false, false, false, false, true, true>;
using NothrowTypeWithThrowingSwap = NothrowTypeImp<true, true, true, true, false, true>;
// throwing move assign with nothrow move and nothrow swap
using ThrowingMoveAssignNothrowMoveCtorWithSwap = NothrowTypeImp<false, true, false, false, true, true>;
// throwing move assign with nothrow move but no swap.
using ThrowingMoveAssignNothrowMoveCtor = NothrowTypeImp<false, true, false, false, false, false>;

struct NonThrowingNonNoexceptType
{
	static int move_called;
	static void reset() { move_called = 0; }
	NonThrowingNonNoexceptType() = default;
	NonThrowingNonNoexceptType(int v) : value(v) {}
	NonThrowingNonNoexceptType(NonThrowingNonNoexceptType&& o) noexcept(false)
		: value(o.value)
	{
		++move_called;
		o.value = -1;
	}
	NonThrowingNonNoexceptType&
		operator=(NonThrowingNonNoexceptType&&) noexcept(false)
	{
		assert(false); // never called by the tests.
		return *this;
	}
	int value;
};
int NonThrowingNonNoexceptType::move_called = 0;

struct ThrowsOnSecondMove
{
	int value;
	int move_count;
	ThrowsOnSecondMove(int v) : value(v), move_count(0) {}
	ThrowsOnSecondMove(ThrowsOnSecondMove&& o) noexcept(false)
		: value(o.value), move_count(o.move_count + 1)
	{
		if (move_count == 2)
		{
			do_throw<true>();
		}
		o.value = -1;
	}
	ThrowsOnSecondMove& operator=(ThrowsOnSecondMove&&)
	{
		assert(false); // not called by test
		return *this;
	}
};

void test_swap_valueless_by_exception()
{
#if !defined(BKSGE_NO_EXCEPTIONS)
	using std::get;
	using V = bksge::variant<int, MakeEmptyT>;
	{ // both empty
		V v1;
		makeEmpty(v1);
		V v2;
		makeEmpty(v2);
		EXPECT_EQ(MakeEmptyT::alive, 0);
		{ // member swap
			v1.swap(v2);
			EXPECT_TRUE(v1.valueless_by_exception());
			EXPECT_TRUE(v2.valueless_by_exception());
			EXPECT_EQ(MakeEmptyT::alive, 0);
		}
		{ // non-member swap
			swap(v1, v2);
			EXPECT_TRUE(v1.valueless_by_exception());
			EXPECT_TRUE(v2.valueless_by_exception());
			EXPECT_EQ(MakeEmptyT::alive, 0);
		}
	}
	{ // only one empty
		V v1(42);
		V v2;
		makeEmpty(v2);
		{ // member swap
			v1.swap(v2);
			EXPECT_TRUE(v1.valueless_by_exception());
			EXPECT_EQ(get<0>(v2), 42);
			// swap again
			v2.swap(v1);
			EXPECT_TRUE(v2.valueless_by_exception());
			EXPECT_EQ(get<0>(v1), 42);
		}
		{ // non-member swap
			swap(v1, v2);
			EXPECT_TRUE(v1.valueless_by_exception());
			EXPECT_EQ(get<0>(v2), 42);
			// swap again
			swap(v1, v2);
			EXPECT_TRUE(v2.valueless_by_exception());
			EXPECT_EQ(get<0>(v1), 42);
		}
	}
#endif
}

void test_swap_same_alternative()
{
	using std::get;
	{
		using T = ThrowingTypeWithNothrowSwap;
		using V = bksge::variant<T, int>;
		T::reset();
		V v1(bksge::in_place_index_t<0>{}, 42);
		V v2(bksge::in_place_index_t<0>{}, 100);
		v1.swap(v2);
		EXPECT_EQ(T::swap_called, 1);
		EXPECT_EQ(get<0>(v1).value, 100);
		EXPECT_EQ(get<0>(v2).value, 42);
		swap(v1, v2);
		EXPECT_EQ(T::swap_called, 2);
		EXPECT_EQ(get<0>(v1).value, 42);
		EXPECT_EQ(get<0>(v2).value, 100);
	}
	{
		using T = NothrowMoveable;
		using V = bksge::variant<T, int>;
		T::reset();
		V v1(bksge::in_place_index_t<0>{}, 42);
		V v2(bksge::in_place_index_t<0>{}, 100);
		v1.swap(v2);
		EXPECT_EQ(T::swap_called, 0);
		EXPECT_EQ(T::move_called, 1);
		EXPECT_EQ(T::move_assign_called, 2);
		EXPECT_EQ(get<0>(v1).value, 100);
		EXPECT_EQ(get<0>(v2).value, 42);
		T::reset();
		swap(v1, v2);
		EXPECT_EQ(T::swap_called, 0);
		EXPECT_EQ(T::move_called, 1);
		EXPECT_EQ(T::move_assign_called, 2);
		EXPECT_EQ(get<0>(v1).value, 42);
		EXPECT_EQ(get<0>(v2).value, 100);
	}
#if !defined(BKSGE_NO_EXCEPTIONS)
	{
		using T = NothrowTypeWithThrowingSwap;
		using V = bksge::variant<T, int>;
		T::reset();
		V v1(bksge::in_place_index_t<0>{}, 42);
		V v2(bksge::in_place_index_t<0>{}, 100);
		try
		{
			v1.swap(v2);
			GTEST_FAIL();
		}
		catch (int)
		{
		}
		EXPECT_EQ(T::swap_called, 1);
		EXPECT_EQ(T::move_called, 0);
		EXPECT_EQ(T::move_assign_called, 0);
		EXPECT_EQ(get<0>(v1).value, 42);
		EXPECT_EQ(get<0>(v2).value, 100);
	}
	{
		using T = ThrowingMoveCtor;
		using V = bksge::variant<T, int>;
		T::reset();
		V v1(bksge::in_place_index_t<0>{}, 42);
		V v2(bksge::in_place_index_t<0>{}, 100);
		try
		{
			v1.swap(v2);
			GTEST_FAIL();
		}
		catch (int)
		{
		}
		EXPECT_EQ(T::move_called, 1); // call threw
		EXPECT_EQ(T::move_assign_called, 0);
		EXPECT_EQ(get<0>(v1).value, 42); // throw happened before v1 was moved from
		EXPECT_EQ(get<0>(v2).value, 100);
	}
	{
		using T = ThrowingMoveAssignNothrowMoveCtor;
		using V = bksge::variant<T, int>;
		T::reset();
		V v1(bksge::in_place_index_t<0>{}, 42);
		V v2(bksge::in_place_index_t<0>{}, 100);
		try
		{
			v1.swap(v2);
			GTEST_FAIL();
		}
		catch (int)
		{
		}
		EXPECT_EQ(T::move_called, 1);
		EXPECT_EQ(T::move_assign_called, 1);  // call threw and didn't complete
		EXPECT_EQ(get<0>(v1).value, -1); // v1 was moved from
		EXPECT_EQ(get<0>(v2).value, 100);
	}
#endif
}

void test_swap_different_alternatives()
{
	using std::get;
	{
		using T = NothrowMoveCtorWithThrowingSwap;
		using V = bksge::variant<T, int>;
		T::reset();
		V v1(bksge::in_place_index_t<0>{}, 42);
		V v2(bksge::in_place_index_t<1>{}, 100);
		v1.swap(v2);
		EXPECT_EQ(T::swap_called, 0);
		// The libc++ implementation double copies the argument, and not
		// the variant swap is called on.
//		EXPECT_TRUE(T::move_called == 1);
		EXPECT_LE(T::move_called, 2);
		EXPECT_EQ(T::move_assign_called, 0);
		EXPECT_EQ(get<1>(v1), 100);
		EXPECT_EQ(get<0>(v2).value, 42);
		T::reset();
		swap(v1, v2);
		EXPECT_EQ(T::swap_called, 0);
//		EXPECT_TRUE(T::move_called == 2);
		EXPECT_LE(T::move_called, 2);
		EXPECT_EQ(T::move_assign_called, 0);
		EXPECT_EQ(get<0>(v1).value, 42);
		EXPECT_EQ(get<1>(v2), 100);
	}
#if !defined(BKSGE_NO_EXCEPTIONS)
	{
		using T1 = ThrowingTypeWithNothrowSwap;
		using T2 = NonThrowingNonNoexceptType;
		using V = bksge::variant<T1, T2>;
		T1::reset();
		T2::reset();
		V v1(bksge::in_place_index_t<0>{}, 42);
		V v2(bksge::in_place_index_t<1>{}, 100);
		try
		{
			v1.swap(v2);
			GTEST_FAIL();
		}
		catch (int)
		{
		}
		EXPECT_EQ(T1::swap_called, 0);
		EXPECT_EQ(T1::move_called, 1); // throws
		EXPECT_EQ(T1::move_assign_called, 0);
		// FIXME: libc++ shouldn't move from T2 here.
//		EXPECT_TRUE(T2::move_called == 1);
		EXPECT_LE(T2::move_called, 1);
		EXPECT_EQ(get<0>(v1).value, 42);
		if (T2::move_called != 0)
		{
			EXPECT_TRUE(v2.valueless_by_exception());
		}
		else
		{
			EXPECT_EQ(get<1>(v2).value, 100);
		}
	}
	{
		using T1 = NonThrowingNonNoexceptType;
		using T2 = ThrowingTypeWithNothrowSwap;
		using V = bksge::variant<T1, T2>;
		T1::reset();
		T2::reset();
		V v1(bksge::in_place_index_t<0>{}, 42);
		V v2(bksge::in_place_index_t<1>{}, 100);
		try
		{
			v1.swap(v2);
			GTEST_FAIL();
		}
		catch (int)
		{
		}
//		EXPECT_TRUE(T1::move_called == 0);
		EXPECT_LE(T1::move_called, 1);
		EXPECT_EQ(T2::swap_called, 0);
		EXPECT_EQ(T2::move_called, 1); // throws
		EXPECT_EQ(T2::move_assign_called, 0);
		if (T1::move_called != 0)
		{
			EXPECT_TRUE(v1.valueless_by_exception());
		}
		else
		{
			EXPECT_EQ(get<0>(v1).value, 42);
		}
		EXPECT_EQ(get<1>(v2).value, 100);
	}
	// FIXME: The tests below are just very libc++ specific
#if 0//def _LIBCPP_VERSION
	{
		using T1 = ThrowsOnSecondMove;
		using T2 = NonThrowingNonNoexceptType;
		using V = bksge::variant<T1, T2>;
		T2::reset();
		V v1(bksge::in_place_index_t<0>{}, 42);
		V v2(bksge::in_place_index_t<1>{}, 100);
		v1.swap(v2);
		EXPECT_EQ(T2::move_called, 2);
		EXPECT_EQ(get<1>(v1).value, 100);
		EXPECT_EQ(get<0>(v2).value, 42);
		EXPECT_EQ(get<0>(v2).move_count, 1);
	}
	{
		using T1 = NonThrowingNonNoexceptType;
		using T2 = ThrowsOnSecondMove;
		using V = bksge::variant<T1, T2>;
		T1::reset();
		V v1(bksge::in_place_index_t<0>{}, 42);
		V v2(bksge::in_place_index_t<1>{}, 100);
		try {
			v1.swap(v2);
			GTEST_FAIL();
		}
		catch (int) {
		}
		EXPECT_EQ(T1::move_called, 1);
		EXPECT_TRUE(v1.valueless_by_exception());
		EXPECT_EQ(get<0>(v2).value, 42);
	}
#endif
	// testing libc++ extension. If either variant stores a nothrow move
	// constructible type v1.swap(v2) provides the strong exception safety
	// guarantee.
#if 0//def _LIBCPP_VERSION
	{

		using T1 = ThrowingTypeWithNothrowSwap;
		using T2 = NothrowMoveable;
		using V = bksge::variant<T1, T2>;
		T1::reset();
		T2::reset();
		V v1(bksge::in_place_index_t<0>{}, 42);
		V v2(bksge::in_place_index_t<1>{}, 100);
		try {
			v1.swap(v2);
			GTEST_FAIL();
		}
		catch (int) {
		}
		EXPECT_EQ(T1::swap_called, 0);
		EXPECT_EQ(T1::move_called, 1);
		EXPECT_EQ(T1::move_assign_called, 0);
		EXPECT_EQ(T2::swap_called, 0);
		EXPECT_EQ(T2::move_called, 2);
		EXPECT_EQ(T2::move_assign_called, 0);
		EXPECT_EQ(get<0>(v1).value, 42);
		EXPECT_EQ(get<1>(v2).value, 100);
		// swap again, but call v2's swap.
		T1::reset();
		T2::reset();
		try {
			v2.swap(v1);
			GTEST_FAIL();
		}
		catch (int) {
		}
		EXPECT_EQ(T1::swap_called, 0);
		EXPECT_EQ(T1::move_called, 1);
		EXPECT_EQ(T1::move_assign_called, 0);
		EXPECT_EQ(T2::swap_called, 0);
		EXPECT_EQ(T2::move_called, 2);
		EXPECT_EQ(T2::move_assign_called, 0);
		EXPECT_EQ(get<0>(v1).value, 42);
		EXPECT_EQ(get<1>(v2).value, 100);
	}
#endif
#endif
}

template <class Var>
constexpr auto has_swap_member_imp(int)
-> decltype(bksge::declval<Var&>().swap(bksge::declval<Var&>()), true)
{
	return true;
}

template <class Var> constexpr auto has_swap_member_imp(long) -> bool
{
	return false;
}

template <class Var> constexpr bool has_swap_member()
{
	return has_swap_member_imp<Var>(0);
}

void test_swap_sfinae()
{
#if 0	// TODO	bksge::swap を削除する?
	{
		// This variant type does not provide either a member or non-member swap
		// but is still swappable via the generic swap algorithm, since the
		// variant is move constructible and move assignable.
		using V = bksge::variant<int, NotSwappable>;
		LIBCPP_STATIC_ASSERT(!has_swap_member<V>(), "");
		static_assert(bksge::is_swappable<V>::value, "");
	}
#endif
	{
		using V = bksge::variant<int, NotCopyable>;
		LIBCPP_STATIC_ASSERT(!has_swap_member<V>(), "");
		static_assert(!bksge::is_swappable<V>::value, "");
	}
	{
		using V = bksge::variant<int, NotCopyableWithSwap>;
		LIBCPP_STATIC_ASSERT(!has_swap_member<V>(), "");
		static_assert(!bksge::is_swappable<V>::value, "");
	}
	{
		using V = bksge::variant<int, NotMoveAssignable>;
		LIBCPP_STATIC_ASSERT(!has_swap_member<V>(), "");
		static_assert(!bksge::is_swappable<V>::value, "");
	}
}

void test_swap_noexcept()
{
	{
		using V = bksge::variant<int, NothrowMoveable>;
		static_assert(bksge::is_swappable<V>::value && has_swap_member<V>(), "");
		static_assert(bksge::is_nothrow_swappable<V>::value, "");
		// instantiate swap
		V v1, v2;
		v1.swap(v2);
		swap(v1, v2);
	}
	{
		using V = bksge::variant<int, NothrowMoveCtor>;
		static_assert(bksge::is_swappable<V>::value && has_swap_member<V>(), "");
		static_assert(!bksge::is_nothrow_swappable<V>::value, "");
		// instantiate swap
		V v1, v2;
		v1.swap(v2);
		swap(v1, v2);
	}
	{
		using V = bksge::variant<int, ThrowingTypeWithNothrowSwap>;
		static_assert(bksge::is_swappable<V>::value && has_swap_member<V>(), "");
		static_assert(!bksge::is_nothrow_swappable<V>::value, "");
		// instantiate swap
		V v1, v2;
		v1.swap(v2);
		swap(v1, v2);
	}
	{
		using V = bksge::variant<int, ThrowingMoveAssignNothrowMoveCtor>;
		static_assert(bksge::is_swappable<V>::value && has_swap_member<V>(), "");
		static_assert(!bksge::is_nothrow_swappable<V>::value, "");
		// instantiate swap
		V v1, v2;
		v1.swap(v2);
		swap(v1, v2);
	}
	{
		using V = bksge::variant<int, ThrowingMoveAssignNothrowMoveCtorWithSwap>;
		static_assert(bksge::is_swappable<V>::value && has_swap_member<V>(), "");
		static_assert(bksge::is_nothrow_swappable<V>::value, "");
		// instantiate swap
		V v1, v2;
		v1.swap(v2);
		swap(v1, v2);
	}
#if 0	// TODO clang だけ？
	{
		using V = bksge::variant<int, NotMoveAssignableWithSwap>;
		static_assert(bksge::is_swappable<V>::value && has_swap_member<V>(), "");
		static_assert(bksge::is_nothrow_swappable<V>::value, "");
		// instantiate swap
		V v1, v2;
		v1.swap(v2);
		swap(v1, v2);
	}
#endif
#if 0	// TODO	bksge::swap を削除する?
	{
		// This variant type does not provide either a member or non-member swap
		// but is still swappable via the generic swap algorithm, since the
		// variant is move constructible and move assignable.
		using V = bksge::variant<int, NotSwappable>;
		LIBCPP_STATIC_ASSERT(!has_swap_member<V>(), "");
		static_assert(bksge::is_swappable<V>::value, "");
		static_assert(bksge::is_nothrow_swappable<V>::value, "");
		V v1, v2;
//		swap(v1, v2);	// TODO
		std::swap(v1, v2);
	}
#endif
}

#if 0//def _LIBCPP_VERSION
// This is why variant should SFINAE member swap. :-)
template class bksge::variant<int, NotSwappable>;
#endif

GTEST_TEST(VariantTest, SwapTest)
{
	test_swap_valueless_by_exception();
	test_swap_same_alternative();
	test_swap_different_alternatives();
	test_swap_sfinae();
	test_swap_noexcept();
}

}	// namespace swap_test

}	// namespace bksge_variant_test

BKSGE_WARNING_POP();
