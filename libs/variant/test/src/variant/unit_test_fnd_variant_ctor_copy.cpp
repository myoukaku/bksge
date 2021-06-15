/**
 *	@file	unit_test_fnd_variant_ctor_copy.cpp
 *
 *	@brief	variant::variant(variant const&) のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/variant/variant.hpp>
#include <bksge/fnd/variant/get.hpp>
#include <bksge/fnd/type_traits/is_copy_assignable.hpp>
#include <bksge/fnd/type_traits/is_copy_constructible.hpp>
#include <bksge/fnd/type_traits/is_move_assignable.hpp>
#include <bksge/fnd/type_traits/is_trivially_copyable.hpp>
#include <bksge/fnd/type_traits/is_trivially_copy_constructible.hpp>
#include <bksge/fnd/type_traits/is_trivially_destructible.hpp>
#include <bksge/fnd/type_traits/is_trivially_move_constructible.hpp>
#include <bksge/fnd/utility/in_place_index.hpp>
#include <bksge/fnd/utility/in_place_type.hpp>
#include <bksge/fnd/utility/move.hpp>
#include <bksge/fnd/config.hpp>
#include <gtest/gtest.h>
#include "test_macros.hpp"
#include "test_workarounds.hpp"

namespace bksge_variant_test
{

namespace ctor_copy_test
{

struct NonT
{
	NonT(int v) : value(v) {}
	NonT(const NonT& o) : value(o.value) {}
	int value;
};

static_assert(!bksge::is_trivially_copy_constructible<NonT>::value, "");

struct NoCopy
{
	NoCopy(const NoCopy&) = delete;
};

struct MoveOnly
{
	MoveOnly(const MoveOnly&) = delete;
	MoveOnly(MoveOnly&&) = default;
};

struct MoveOnlyNT
{
	MoveOnlyNT(const MoveOnlyNT&) = delete;
	MoveOnlyNT(MoveOnlyNT&&) {}
};

struct NTCopy
{
	constexpr NTCopy(int v) : value(v) {}
	NTCopy(const NTCopy& that) : value(that.value) {}
	NTCopy(NTCopy&&) = delete;
	int value;
};

static_assert(!bksge::is_trivially_copy_constructible<NTCopy>::value, "");
static_assert(bksge::is_copy_constructible<NTCopy>::value, "");

struct TCopy
{
	constexpr TCopy(int v) : value(v) {}
	TCopy(TCopy const&) = default;
	TCopy(TCopy&&) = delete;
	int value;
};

static_assert(bksge::is_trivially_copy_constructible<TCopy>::value, "");

struct TCopyNTMove
{
	constexpr TCopyNTMove(int v) : value(v) {}
	TCopyNTMove(const TCopyNTMove&) = default;
	TCopyNTMove(TCopyNTMove&& that) : value(that.value) { that.value = -1; }
	int value;
};

static_assert(bksge::is_trivially_copy_constructible<TCopyNTMove>::value, "");

#if !defined(BKSGE_NO_EXCEPTIONS)

struct MakeEmptyT
{
	static int alive;
	MakeEmptyT() { ++alive; }
	MakeEmptyT(const MakeEmptyT&)
	{
		++alive;
		// Don't throw from the copy constructor since variant's assignment
		// operator performs a copy before committing to the assignment.
	}
	MakeEmptyT(MakeEmptyT&&) { throw 42; }
	MakeEmptyT& operator=(const MakeEmptyT&) { throw 42; }
	MakeEmptyT& operator=(MakeEmptyT&&) { throw 42; }
	~MakeEmptyT() { --alive; }
};

int MakeEmptyT::alive = 0;

template <class Variant>
void makeEmpty(Variant& v)
{
	Variant v2(bksge::in_place_type_t<MakeEmptyT>{});
	try
	{
		v = bksge::move(v2);
		GTEST_FAIL();
	}
	catch (...)
	{
		EXPECT_TRUE(v.valueless_by_exception());
	}
}

#endif

void test_copy_ctor_sfinae()
{
	{
		using V = bksge::variant<int, long>;
		static_assert(bksge::is_copy_constructible<V>::value, "");
	}
	{
		using V = bksge::variant<int, NoCopy>;
		static_assert(!bksge::is_copy_constructible<V>::value, "");
	}
	{
		using V = bksge::variant<int, MoveOnly>;
		static_assert(!bksge::is_copy_constructible<V>::value, "");
	}
	{
		using V = bksge::variant<int, MoveOnlyNT>;
		static_assert(!bksge::is_copy_constructible<V>::value, "");
	}

	// Make sure we properly propagate triviality (see P0602R4).
#if BKSGE_CXX_STANDARD >= 20
	{
		using V = bksge::variant<int, long>;
		static_assert(bksge::is_trivially_copy_constructible<V>::value, "");
	}
	{
		using V = bksge::variant<int, NTCopy>;
		static_assert(!bksge::is_trivially_copy_constructible<V>::value, "");
		static_assert(bksge::is_copy_constructible<V>::value, "");
	}
	{
		using V = bksge::variant<int, TCopy>;
		static_assert(bksge::is_trivially_copy_constructible<V>::value, "");
	}
	{
		using V = bksge::variant<int, TCopyNTMove>;
		static_assert(bksge::is_trivially_copy_constructible<V>::value, "");
	}
#endif
}

void test_copy_ctor_basic()
{
	using std::get;
	{
		bksge::variant<int> v(bksge::in_place_index_t<0>{}, 42);
		bksge::variant<int> v2 = v;
		EXPECT_EQ(v2.index(), 0u);
		EXPECT_EQ(get<0>(v2), 42);
	}
	{
		bksge::variant<int, long> v(bksge::in_place_index_t<1>{}, 42);
		bksge::variant<int, long> v2 = v;
		EXPECT_EQ(v2.index(), 1u);
		EXPECT_EQ(get<1>(v2), 42);
	}
	{
		bksge::variant<NonT> v(bksge::in_place_index_t<0>{}, 42);
		EXPECT_EQ(v.index(), 0u);
		bksge::variant<NonT> v2(v);
		EXPECT_EQ(v2.index(), 0u);
		EXPECT_EQ(get<0>(v2).value, 42);
	}
	{
		bksge::variant<int, NonT> v(bksge::in_place_index_t<1>{}, 42);
		EXPECT_EQ(v.index(), 1u);
		bksge::variant<int, NonT> v2(v);
		EXPECT_EQ(v2.index(), 1u);
		EXPECT_EQ(get<1>(v2).value, 42);
	}

	// Make sure we properly propagate triviality, which implies constexpr-ness (see P0602R4).
#if BKSGE_CXX_STANDARD >= 20
	{
		constexpr bksge::variant<int> v(bksge::in_place_index_t<0>{}, 42);
		static_assert(v.index() == 0, "");
		constexpr bksge::variant<int> v2 = v;
		static_assert(v2.index() == 0, "");
		static_assert(get<0>(v2) == 42, "");
	}
	{
		constexpr bksge::variant<int, long> v(bksge::in_place_index_t<1>{}, 42);
		static_assert(v.index() == 1, "");
		constexpr bksge::variant<int, long> v2 = v;
		static_assert(v2.index() == 1, "");
		static_assert(get<1>(v2) == 42, "");
	}
	{
		constexpr bksge::variant<TCopy> v(bksge::in_place_index_t<0>{}, 42);
		static_assert(v.index() == 0, "");
		constexpr bksge::variant<TCopy> v2(v);
		static_assert(v2.index() == 0, "");
		static_assert(get<0>(v2).value == 42, "");
	}
	{
		constexpr bksge::variant<int, TCopy> v(bksge::in_place_index_t<1>{}, 42);
		static_assert(v.index() == 1, "");
		constexpr bksge::variant<int, TCopy> v2(v);
		static_assert(v2.index() == 1, "");
		static_assert(get<1>(v2).value == 42, "");
	}
	{
		constexpr bksge::variant<TCopyNTMove> v(bksge::in_place_index_t<0>{}, 42);
		static_assert(v.index() == 0, "");
		constexpr bksge::variant<TCopyNTMove> v2(v);
		static_assert(v2.index() == 0, "");
		static_assert(get<0>(v2).value == 42, "");
	}
	{
		constexpr bksge::variant<int, TCopyNTMove> v(bksge::in_place_index_t<1>{}, 42);
		static_assert(v.index() == 1, "");
		constexpr bksge::variant<int, TCopyNTMove> v2(v);
		static_assert(v2.index() == 1, "");
		static_assert(get<1>(v2).value == 42, "");
	}
#endif
}

void test_copy_ctor_valueless_by_exception()
{
#if !defined(BKSGE_NO_EXCEPTIONS)
	using V = bksge::variant<int, MakeEmptyT>;
	V v1;
	makeEmpty(v1);
	const V& cv1 = v1;
	V v(cv1);
	EXPECT_TRUE(v.valueless_by_exception());
#endif
}

#if BKSGE_CXX_STANDARD >= 20
template <size_t Idx>
constexpr bool
test_constexpr_copy_ctor_imp(
	bksge::variant<long, void*, const int> const& v)
{
	using std::get;
	auto v2 = v;
	return v2.index() == v.index() &&
		v2.index() == Idx &&
		get<Idx>(v2) == get<Idx>(v);
}
#endif

void test_constexpr_copy_ctor()
{
	// Make sure we properly propagate triviality, which implies constexpr-ness (see P0602R4).
#if BKSGE_CXX_STANDARD >= 20
	using V = bksge::variant<long, void*, const int>;
#if defined(TEST_WORKAROUND_C1XX_BROKEN_IS_TRIVIALLY_COPYABLE)
	static_assert(bksge::is_trivially_destructible<V>::value, "");
	static_assert(bksge::is_trivially_copy_constructible<V>::value, "");
	static_assert(bksge::is_trivially_move_constructible<V>::value, "");
	static_assert(!bksge::is_copy_assignable<V>::value, "");
	static_assert(!bksge::is_move_assignable<V>::value, "");
#else // TEST_WORKAROUND_C1XX_BROKEN_IS_TRIVIALLY_COPYABLE
	static_assert(bksge::is_trivially_copyable<V>::value, "");
#endif // TEST_WORKAROUND_C1XX_BROKEN_IS_TRIVIALLY_COPYABLE
	static_assert(test_constexpr_copy_ctor_imp<0>(V(42l)), "");
	static_assert(test_constexpr_copy_ctor_imp<1>(V(nullptr)), "");
	static_assert(test_constexpr_copy_ctor_imp<2>(V(101)), "");
#endif
}

GTEST_TEST(VariantTest, CtorCopyTest)
{
	test_copy_ctor_basic();
	test_copy_ctor_valueless_by_exception();
	test_copy_ctor_sfinae();
	test_constexpr_copy_ctor();
#if 0
	// disable this for the moment; it fails on older compilers.
	//  Need to figure out which compilers will support it.
	{ // This is the motivating example from P0739R0
		bksge::variant<int, double> v1(3);
		bksge::variant v2 = v1;
		(void)v2;
	}
#endif
}

}	// namespace ctor_copy_test

}	// namespace bksge_variant_test
