/**
 *	@file	unit_test_fnd_variant_ctor_move.cpp
 *
 *	@brief	variant::variant(variant&&) のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/variant/variant.hpp>
#include <bksge/fnd/variant/get.hpp>
#include <bksge/fnd/type_traits/is_copy_assignable.hpp>
#include <bksge/fnd/type_traits/is_move_assignable.hpp>
#include <bksge/fnd/type_traits/is_move_constructible.hpp>
#include <bksge/fnd/type_traits/is_nothrow_move_constructible.hpp>
#include <bksge/fnd/type_traits/is_trivially_copyable.hpp>
#include <bksge/fnd/type_traits/is_trivially_copy_constructible.hpp>
#include <bksge/fnd/type_traits/is_trivially_destructible.hpp>
#include <bksge/fnd/type_traits/is_trivially_move_constructible.hpp>
#include <bksge/fnd/utility/in_place_index.hpp>
#include <bksge/fnd/utility/in_place_type.hpp>
#include <bksge/fnd/config.hpp>
#include <gtest/gtest.h>
#include <cstddef>
#include <utility>
#include "test_macros.hpp"
#include "test_workarounds.hpp"

namespace bksge_variant_test
{

namespace ctor_move_test
{

struct ThrowsMove
{
	ThrowsMove(ThrowsMove&&) noexcept(false) {}
};

struct NoCopy
{
	NoCopy(const NoCopy&) = delete;
};

struct MoveOnly
{
	int value;
	MoveOnly(int v) : value(v) {}
	MoveOnly(const MoveOnly&) = delete;
	MoveOnly(MoveOnly&&) = default;
};

struct MoveOnlyNT
{
	int value;
	MoveOnlyNT(int v) : value(v) {}
	MoveOnlyNT(const MoveOnlyNT&) = delete;
	MoveOnlyNT(MoveOnlyNT&& other) : value(other.value) { other.value = -1; }
};

struct NTMove
{
	constexpr NTMove(int v) : value(v) {}
	NTMove(const NTMove&) = delete;
	NTMove(NTMove&& that) : value(that.value) { that.value = -1; }
	int value;
};

static_assert(!bksge::is_trivially_move_constructible<NTMove>::value, "");
static_assert(bksge::is_move_constructible<NTMove>::value, "");

struct TMove
{
	constexpr TMove(int v) : value(v) {}
	TMove(const TMove&) = delete;
	TMove(TMove&&) = default;
	int value;
};

static_assert(bksge::is_trivially_move_constructible<TMove>::value, "");

struct TMoveNTCopy
{
	constexpr TMoveNTCopy(int v) : value(v) {}
	TMoveNTCopy(const TMoveNTCopy& that) : value(that.value) {}
	TMoveNTCopy(TMoveNTCopy&&) = default;
	int value;
};

static_assert(bksge::is_trivially_move_constructible<TMoveNTCopy>::value, "");

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
		v = std::move(v2);
		GTEST_FAIL();
	}
	catch (...)
	{
		EXPECT_TRUE(v.valueless_by_exception());
	}
}

#endif

void test_move_noexcept()
{
	{
		using V = bksge::variant<int, long>;
		static_assert(bksge::is_nothrow_move_constructible<V>::value, "");
	}
	{
		using V = bksge::variant<int, MoveOnly>;
		static_assert(bksge::is_nothrow_move_constructible<V>::value, "");
	}
	{
		using V = bksge::variant<int, MoveOnlyNT>;
		static_assert(!bksge::is_nothrow_move_constructible<V>::value, "");
	}
	{
		using V = bksge::variant<int, ThrowsMove>;
		static_assert(!bksge::is_nothrow_move_constructible<V>::value, "");
	}
}

void test_move_ctor_sfinae()
{
	{
		using V = bksge::variant<int, long>;
		static_assert(bksge::is_move_constructible<V>::value, "");
	}
	{
		using V = bksge::variant<int, MoveOnly>;
		static_assert(bksge::is_move_constructible<V>::value, "");
	}
	{
		using V = bksge::variant<int, MoveOnlyNT>;
		static_assert(bksge::is_move_constructible<V>::value, "");
	}
	{
		using V = bksge::variant<int, NoCopy>;
		static_assert(!bksge::is_move_constructible<V>::value, "");
	}

	// Make sure we properly propagate triviality (see P0602R4).
#if BKSGE_CXX_STANDARD >= 20
	{
		using V = bksge::variant<int, long>;
		static_assert(bksge::is_trivially_move_constructible<V>::value, "");
	}
	{
		using V = bksge::variant<int, NTMove>;
		static_assert(!bksge::is_trivially_move_constructible<V>::value, "");
		static_assert(bksge::is_move_constructible<V>::value, "");
	}
	{
		using V = bksge::variant<int, TMove>;
		static_assert(bksge::is_trivially_move_constructible<V>::value, "");
	}
	{
		using V = bksge::variant<int, TMoveNTCopy>;
		static_assert(bksge::is_trivially_move_constructible<V>::value, "");
	}
#endif
}

template <typename T>
struct Result { std::size_t index; T value; };

void test_move_ctor_basic()
{
	using std::get;
	{
		bksge::variant<int> v(bksge::in_place_index_t<0>{}, 42);
		bksge::variant<int> v2 = std::move(v);
		EXPECT_EQ(v2.index(), 0u);
		EXPECT_EQ(get<0>(v2), 42);
	}
	{
		bksge::variant<int, long> v(bksge::in_place_index_t<1>{}, 42);
		bksge::variant<int, long> v2 = std::move(v);
		EXPECT_EQ(v2.index(), 1u);
		EXPECT_EQ(get<1>(v2), 42);
	}
	{
		bksge::variant<MoveOnly> v(bksge::in_place_index_t<0>{}, 42);
		EXPECT_EQ(v.index(), 0u);
		bksge::variant<MoveOnly> v2(std::move(v));
		EXPECT_EQ(v2.index(), 0u);
		EXPECT_EQ(get<0>(v2).value, 42);
	}
	{
		bksge::variant<int, MoveOnly> v(bksge::in_place_index_t<1>{}, 42);
		EXPECT_EQ(v.index(), 1u);
		bksge::variant<int, MoveOnly> v2(std::move(v));
		EXPECT_EQ(v2.index(), 1u);
		EXPECT_EQ(get<1>(v2).value, 42);
	}
	{
		bksge::variant<MoveOnlyNT> v(bksge::in_place_index_t<0>{}, 42);
		EXPECT_EQ(v.index(), 0u);
		bksge::variant<MoveOnlyNT> v2(std::move(v));
		EXPECT_EQ(v2.index(), 0u);
		EXPECT_EQ(get<0>(v).value, -1);
		EXPECT_EQ(get<0>(v2).value, 42);
	}
	{
		bksge::variant<int, MoveOnlyNT> v(bksge::in_place_index_t<1>{}, 42);
		EXPECT_EQ(v.index(), 1u);
		bksge::variant<int, MoveOnlyNT> v2(std::move(v));
		EXPECT_EQ(v2.index(), 1u);
		EXPECT_EQ(get<1>(v).value, -1);
		EXPECT_EQ(get<1>(v2).value, 42);
	}

	// Make sure we properly propagate triviality, which implies constexpr-ness (see P0602R4).
#if BKSGE_CXX_STANDARD >= 20
	{
		struct
		{
			constexpr Result<int> operator()() const
			{
				bksge::variant<int> v(bksge::in_place_index_t<0>{}, 42);
				bksge::variant<int> v2 = std::move(v);
				return { v2.index(), get<0>(std::move(v2)) };
			}
		} test;
		constexpr auto result = test();
		static_assert(result.index == 0, "");
		static_assert(result.value == 42, "");
	}
	{
		struct
		{
			constexpr Result<long> operator()() const
			{
				bksge::variant<int, long> v(bksge::in_place_index_t<1>{}, 42);
				bksge::variant<int, long> v2 = std::move(v);
				return { v2.index(), get<1>(std::move(v2)) };
			}
		} test;
		constexpr auto result = test();
		static_assert(result.index == 1, "");
		static_assert(result.value == 42, "");
	}
	{
		struct
		{
			constexpr Result<TMove> operator()() const
			{
				bksge::variant<TMove> v(bksge::in_place_index_t<0>{}, 42);
				bksge::variant<TMove> v2(std::move(v));
				return { v2.index(), get<0>(std::move(v2)) };
			}
		} test;
		constexpr auto result = test();
		static_assert(result.index == 0, "");
		static_assert(result.value.value == 42, "");
	}
	{
		struct
		{
			constexpr Result<TMove> operator()() const
			{
				bksge::variant<int, TMove> v(bksge::in_place_index_t<1>{}, 42);
				bksge::variant<int, TMove> v2(std::move(v));
				return { v2.index(), get<1>(std::move(v2)) };
			}
		} test;
		constexpr auto result = test();
		static_assert(result.index == 1, "");
		static_assert(result.value.value == 42, "");
	}
	{
		struct
		{
			constexpr Result<TMoveNTCopy> operator()() const
			{
				bksge::variant<TMoveNTCopy> v(bksge::in_place_index_t<0>{}, 42);
				bksge::variant<TMoveNTCopy> v2(std::move(v));
				return { v2.index(), get<0>(std::move(v2)) };
			}
		} test;
		constexpr auto result = test();
		static_assert(result.index == 0, "");
		static_assert(result.value.value == 42, "");
	}
	{
		struct
		{
			constexpr Result<TMoveNTCopy> operator()() const
			{
				bksge::variant<int, TMoveNTCopy> v(bksge::in_place_index_t<1>{}, 42);
				bksge::variant<int, TMoveNTCopy> v2(std::move(v));
				return { v2.index(), get<1>(std::move(v2)) };
			}
		} test;
		constexpr auto result = test();
		static_assert(result.index == 1, "");
		static_assert(result.value.value == 42, "");
	}
#endif
}

void test_move_ctor_valueless_by_exception()
{
#if !defined(BKSGE_NO_EXCEPTIONS)
	using V = bksge::variant<int, MakeEmptyT>;
	V v1;
	makeEmpty(v1);
	V v(std::move(v1));
	EXPECT_TRUE(v.valueless_by_exception());
#endif
}

#if BKSGE_CXX_STANDARD >= 20
template <std::size_t Idx>
constexpr bool
test_constexpr_ctor_imp(bksge::variant<long, void*, const int> const& v)
{
	using std::get;
	auto copy = v;
	auto v2 = std::move(copy);
	return v2.index() == v.index() &&
		v2.index() == Idx &&
		get<Idx>(v2) == get<Idx>(v);
}
#endif

void test_constexpr_move_ctor()
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
	static_assert(bksge::is_trivially_move_constructible<V>::value, "");
	static_assert(test_constexpr_ctor_imp<0>(V(42l)), "");
	static_assert(test_constexpr_ctor_imp<1>(V(nullptr)), "");
	static_assert(test_constexpr_ctor_imp<2>(V(101)), "");
#endif
}

GTEST_TEST(VariantTest, CtorMoveTest)
{
	test_move_ctor_basic();
	test_move_ctor_valueless_by_exception();
	test_move_noexcept();
	test_move_ctor_sfinae();
	test_constexpr_move_ctor();
}

}	// namespace ctor_move_test

}	// namespace bksge_variant_test

//#undef TEST_WORKAROUND_C1XX_BROKEN_IS_TRIVIALLY_COPYABLE
