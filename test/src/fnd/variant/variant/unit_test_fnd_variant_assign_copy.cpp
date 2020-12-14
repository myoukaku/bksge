/**
 *	@file	unit_test_fnd_variant_assign_copy.cpp
 *
 *	@brief	variant& operator=(variant const&) のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/variant/variant.hpp>
#include <bksge/fnd/variant/variant_npos.hpp>
#include <bksge/fnd/variant/get.hpp>
#include <bksge/fnd/type_traits/is_copy_assignable.hpp>
#include <bksge/fnd/type_traits/is_nothrow_copy_assignable.hpp>
#include <bksge/fnd/type_traits/is_trivially_copy_assignable.hpp>
#include <bksge/fnd/type_traits/is_trivially_copyable.hpp>
#include <bksge/fnd/utility/in_place_index.hpp>
#include <bksge/fnd/utility/in_place_type.hpp>
#include <bksge/fnd/utility/forward.hpp>
#include <bksge/fnd/utility/move.hpp>
#include <bksge/fnd/config.hpp>
#include <string>
#include <gtest/gtest.h>
#include "fnd/variant/test_macros.hpp"

namespace bksge_variant_test
{

namespace assign_copy_test
{

struct NoCopy
{
	NoCopy(const NoCopy&) = delete;
	NoCopy& operator=(const NoCopy&) = default;
};

struct CopyOnly {
	CopyOnly(const CopyOnly&) = default;
	CopyOnly(CopyOnly&&) = delete;
	CopyOnly& operator=(const CopyOnly&) = default;
	CopyOnly& operator=(CopyOnly&&) = delete;
};

struct MoveOnly
{
	MoveOnly(const MoveOnly&) = delete;
	MoveOnly(MoveOnly&&) = default;
	MoveOnly& operator=(const MoveOnly&) = default;
};

struct MoveOnlyNT
{
	MoveOnlyNT(const MoveOnlyNT&) = delete;
	MoveOnlyNT(MoveOnlyNT&&) {}
	MoveOnlyNT& operator=(const MoveOnlyNT&) = default;
};

struct CopyAssign
{
	static int alive;
	static int copy_construct;
	static int copy_assign;
	static int move_construct;
	static int move_assign;

	static void reset()
	{
		copy_construct = copy_assign = move_construct = move_assign = alive = 0;
	}

	CopyAssign(int v) : value(v) { ++alive; }

	CopyAssign(const CopyAssign& o) : value(o.value)
	{
		++alive;
		++copy_construct;
	}

	CopyAssign(CopyAssign&& o) noexcept : value(o.value)
	{
		o.value = -1;
		++alive;
		++move_construct;
	}

	CopyAssign& operator=(const CopyAssign& o)
	{
		value = o.value;
		++copy_assign;
		return *this;
	}

	CopyAssign& operator=(CopyAssign&& o) noexcept
	{
		value = o.value;
		o.value = -1;
		++move_assign;
		return *this;
	}

	~CopyAssign() { --alive; }

	int value;
};

int CopyAssign::alive = 0;
int CopyAssign::copy_construct = 0;
int CopyAssign::copy_assign = 0;
int CopyAssign::move_construct = 0;
int CopyAssign::move_assign = 0;

struct CopyMaybeThrows
{
	CopyMaybeThrows(const CopyMaybeThrows&);
	CopyMaybeThrows& operator=(const CopyMaybeThrows&);
};

struct CopyDoesThrow
{
	CopyDoesThrow(const CopyDoesThrow&) noexcept(false);
	CopyDoesThrow& operator=(const CopyDoesThrow&) noexcept(false);
};

struct NTCopyAssign
{
	constexpr NTCopyAssign(int v) : value(v) {}
	NTCopyAssign(const NTCopyAssign&) = default;
	NTCopyAssign(NTCopyAssign&&) = default;
	NTCopyAssign& operator=(const NTCopyAssign& that)
	{
		value = that.value;
		return *this;
	}
	NTCopyAssign& operator=(NTCopyAssign&&) = delete;
	int value;
};

static_assert(!bksge::is_trivially_copy_assignable<NTCopyAssign>::value, "");
static_assert(bksge::is_copy_assignable<NTCopyAssign>::value, "");

struct TCopyAssign
{
	constexpr TCopyAssign(int v) : value(v) {}
	TCopyAssign(const TCopyAssign&) = default;
	TCopyAssign(TCopyAssign&&) = default;
	TCopyAssign& operator=(const TCopyAssign&) = default;
	TCopyAssign& operator=(TCopyAssign&&) = delete;
	int value;
};

static_assert(bksge::is_trivially_copy_assignable<TCopyAssign>::value, "");

struct TCopyAssignNTMoveAssign
{
	constexpr TCopyAssignNTMoveAssign(int v) : value(v) {}
	TCopyAssignNTMoveAssign(const TCopyAssignNTMoveAssign&) = default;
	TCopyAssignNTMoveAssign(TCopyAssignNTMoveAssign&&) = default;
	TCopyAssignNTMoveAssign& operator=(const TCopyAssignNTMoveAssign&) = default;
	TCopyAssignNTMoveAssign& operator=(TCopyAssignNTMoveAssign&& that)
	{
		value = that.value;
		that.value = -1;
		return *this;
	}
	int value;
};

static_assert(bksge::is_trivially_copy_assignable<TCopyAssignNTMoveAssign>::value, "");

#if !defined(BKSGE_NO_EXCEPTIONS)
struct CopyThrows
{
	CopyThrows() = default;
	CopyThrows(const CopyThrows&) { throw 42; }
	CopyThrows& operator=(const CopyThrows&) { throw 42; }
};

struct CopyCannotThrow
{
	static int alive;
	CopyCannotThrow() { ++alive; }
	CopyCannotThrow(const CopyCannotThrow&) noexcept { ++alive; }
	CopyCannotThrow(CopyCannotThrow&&) noexcept { assert(false); }
	CopyCannotThrow& operator=(const CopyCannotThrow&) noexcept = default;
	CopyCannotThrow& operator=(CopyCannotThrow&&) noexcept { assert(false); return *this; }
};

int CopyCannotThrow::alive = 0;

struct MoveThrows
{
	static int alive;
	MoveThrows() { ++alive; }
	MoveThrows(const MoveThrows&) { ++alive; }
	MoveThrows(MoveThrows&&) { throw 42; }
	MoveThrows& operator=(const MoveThrows&) { return *this; }
	MoveThrows& operator=(MoveThrows&&) { throw 42; }
	~MoveThrows() { --alive; }
};

int MoveThrows::alive = 0;

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

template <typename Variant>
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

void test_copy_assignment_not_noexcept()
{
	{
		using V = bksge::variant<CopyMaybeThrows>;
		static_assert(!bksge::is_nothrow_copy_assignable<V>::value, "");
	}
	{
		using V = bksge::variant<int, CopyDoesThrow>;
		static_assert(!bksge::is_nothrow_copy_assignable<V>::value, "");
	}
}

void test_copy_assignment_sfinae()
{
	{
		using V = bksge::variant<int, long>;
		static_assert(bksge::is_copy_assignable<V>::value, "");
	}
	{
		using V = bksge::variant<int, CopyOnly>;
		static_assert(bksge::is_copy_assignable<V>::value, "");
	}
	{
		using V = bksge::variant<int, NoCopy>;
		static_assert(!bksge::is_copy_assignable<V>::value, "");
	}
	{
		using V = bksge::variant<int, MoveOnly>;
		static_assert(!bksge::is_copy_assignable<V>::value, "");
	}
	{
		using V = bksge::variant<int, MoveOnlyNT>;
		static_assert(!bksge::is_copy_assignable<V>::value, "");
	}

	// Make sure we properly propagate triviality (see P0602R4).
#if BKSGE_CXX_STANDARD >= 20
	{
		using V = bksge::variant<int, long>;
		static_assert(bksge::is_trivially_copy_assignable<V>::value, "");
	}
	{
		using V = bksge::variant<int, NTCopyAssign>;
		static_assert(!bksge::is_trivially_copy_assignable<V>::value, "");
		static_assert(bksge::is_copy_assignable<V>::value, "");
	}
	{
		using V = bksge::variant<int, TCopyAssign>;
		static_assert(bksge::is_trivially_copy_assignable<V>::value, "");
	}
	{
		using V = bksge::variant<int, TCopyAssignNTMoveAssign>;
		static_assert(bksge::is_trivially_copy_assignable<V>::value, "");
	}
	{
		using V = bksge::variant<int, CopyOnly>;
		static_assert(bksge::is_trivially_copy_assignable<V>::value, "");
	}
#endif
}

void test_copy_assignment_empty_empty()
{
#if !defined(BKSGE_NO_EXCEPTIONS)
	using MET = MakeEmptyT;
	{
		using V = bksge::variant<int, long, MET>;
		V v1(bksge::in_place_index_t<0>{});
		makeEmpty(v1);
		V v2(bksge::in_place_index_t<0>{});
		makeEmpty(v2);
		V& vref = (v1 = v2);
		EXPECT_EQ(&vref, &v1);
		EXPECT_TRUE(v1.valueless_by_exception());
		EXPECT_EQ(v1.index(), bksge::variant_npos);
	}
#endif
}

void test_copy_assignment_non_empty_empty()
{
#if !defined(BKSGE_NO_EXCEPTIONS)
	using MET = MakeEmptyT;
	{
		using V = bksge::variant<int, MET>;
		V v1(bksge::in_place_index_t<0>{}, 42);
		V v2(bksge::in_place_index_t<0>{});
		makeEmpty(v2);
		V& vref = (v1 = v2);
		EXPECT_EQ(&vref, &v1);
		EXPECT_TRUE(v1.valueless_by_exception());
		EXPECT_EQ(v1.index(), bksge::variant_npos);
	}
	{
		using V = bksge::variant<int, MET, std::string>;
		V v1(bksge::in_place_index_t<2>{}, "hello");
		V v2(bksge::in_place_index_t<0>{});
		makeEmpty(v2);
		V& vref = (v1 = v2);
		EXPECT_EQ(&vref, &v1);
		EXPECT_TRUE(v1.valueless_by_exception());
		EXPECT_EQ(v1.index(), bksge::variant_npos);
	}
#endif
}

void test_copy_assignment_empty_non_empty()
{
#if !defined(BKSGE_NO_EXCEPTIONS)
	using std::get;
	using MET = MakeEmptyT;
	{
		using V = bksge::variant<int, MET>;
		V v1(bksge::in_place_index_t<0>{});
		makeEmpty(v1);
		V v2(bksge::in_place_index_t<0>{}, 42);
		V& vref = (v1 = v2);
		EXPECT_EQ(&vref, &v1);
		EXPECT_EQ(v1.index(), 0u);
		EXPECT_EQ(get<0>(v1), 42);
	}
	{
		using V = bksge::variant<int, MET, std::string>;
		V v1(bksge::in_place_index_t<0>{});
		makeEmpty(v1);
		V v2(bksge::in_place_type_t<std::string>{}, "hello");
		V& vref = (v1 = v2);
		EXPECT_EQ(&vref, &v1);
		EXPECT_EQ(v1.index(), 2u);
		EXPECT_EQ(get<2>(v1), "hello");
	}
#endif
}

template <typename T> struct Result { size_t index; T value; };

void test_copy_assignment_same_index()
{
	using std::get;
	{
		using V = bksge::variant<int>;
		V v1(43);
		V v2(42);
		V& vref = (v1 = v2);
		EXPECT_EQ(&vref, &v1);
		EXPECT_EQ(v1.index(), 0u);
		EXPECT_EQ(get<0>(v1), 42);
	}
	{
		using V = bksge::variant<int, long, unsigned>;
		V v1(43l);
		V v2(42l);
		V& vref = (v1 = v2);
		EXPECT_EQ(&vref, &v1);
		EXPECT_EQ(v1.index(), 1u);
		EXPECT_EQ(get<1>(v1), 42);
	}
	{
		using V = bksge::variant<int, CopyAssign, unsigned>;
		V v1(bksge::in_place_type_t<CopyAssign>{}, 43);
		V v2(bksge::in_place_type_t<CopyAssign>{}, 42);
		CopyAssign::reset();
		V& vref = (v1 = v2);
		EXPECT_EQ(&vref, &v1);
		EXPECT_EQ(v1.index(), 1u);
		EXPECT_EQ(get<1>(v1).value, 42);
		EXPECT_EQ(CopyAssign::copy_construct, 0);
		EXPECT_EQ(CopyAssign::move_construct, 0);
		EXPECT_EQ(CopyAssign::copy_assign, 1);
	}
#if !defined(BKSGE_NO_EXCEPTIONS)
	using MET = MakeEmptyT;
	{
		using V = bksge::variant<int, MET, std::string>;
		V v1(bksge::in_place_type_t<MET>{});
		MET& mref = get<1>(v1);
		V v2(bksge::in_place_type_t<MET>{});
		try
		{
			v1 = v2;
			GTEST_FAIL();
		}
		catch (...)
		{
		}
		EXPECT_EQ(v1.index(), 1u);
		EXPECT_EQ(&get<1>(v1), &mref);
	}
#endif

	// Make sure we properly propagate triviality, which implies constexpr-ness (see P0602R4).
#if BKSGE_CXX_STANDARD >= 20
	{
		struct
		{
			constexpr Result<int> operator()() const
			{
				using V = bksge::variant<int>;
				V v(43);
				V v2(42);
				v = v2;
				return { v.index(), get<0>(v) };
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
				using V = bksge::variant<int, long, unsigned>;
				V v(43l);
				V v2(42l);
				v = v2;
				return { v.index(), get<1>(v) };
			}
		} test;

		constexpr auto result = test();
		static_assert(result.index == 1, "");
		static_assert(result.value == 42l, "");
	}
	{
		struct
		{
			constexpr Result<int> operator()() const
			{
				using V = bksge::variant<int, TCopyAssign, unsigned>;
				V v(bksge::in_place_type_t<TCopyAssign>{}, 43);
				V v2(bksge::in_place_type_t<TCopyAssign>{}, 42);
				v = v2;
				return { v.index(), get<1>(v).value };
			}
		} test;

		constexpr auto result = test();
		static_assert(result.index == 1, "");
		static_assert(result.value == 42, "");
	}
	{
		struct
		{
			constexpr Result<int> operator()() const
			{
				using V = bksge::variant<int, TCopyAssignNTMoveAssign, unsigned>;
				V v(bksge::in_place_type_t<TCopyAssignNTMoveAssign>{}, 43);
				V v2(bksge::in_place_type_t<TCopyAssignNTMoveAssign>{}, 42);
				v = v2;
				return { v.index(), get<1>(v).value };
			}
		} test;

		constexpr auto result = test();
		static_assert(result.index == 1, "");
		static_assert(result.value == 42, "");
	}
#endif
}

void test_copy_assignment_different_index()
{
	using std::get;
	{
		using V = bksge::variant<int, long, unsigned>;
		V v1(43);
		V v2(42l);
		V& vref = (v1 = v2);
		EXPECT_EQ(&vref, &v1);
		EXPECT_EQ(v1.index(), 1u);
		EXPECT_EQ(get<1>(v1), 42);
	}
	{
		using V = bksge::variant<int, CopyAssign, unsigned>;
		CopyAssign::reset();
		V v1(bksge::in_place_type_t<unsigned>{}, 43u);
		V v2(bksge::in_place_type_t<CopyAssign>{}, 42);
		EXPECT_EQ(CopyAssign::copy_construct, 0);
		EXPECT_EQ(CopyAssign::move_construct, 0);
		EXPECT_EQ(CopyAssign::alive, 1);
		V& vref = (v1 = v2);
		EXPECT_EQ(&vref, &v1);
		EXPECT_EQ(v1.index(), 1u);
		EXPECT_EQ(get<1>(v1).value, 42);
		EXPECT_EQ(CopyAssign::alive, 2);
		EXPECT_EQ(CopyAssign::copy_construct, 1);
		EXPECT_EQ(CopyAssign::move_construct, 1);
		EXPECT_EQ(CopyAssign::copy_assign, 0);
	}
#if !defined(BKSGE_NO_EXCEPTIONS)
	{
		using V = bksge::variant<int, CopyThrows, std::string>;
		V v1(bksge::in_place_type_t<std::string>{}, "hello");
		V v2(bksge::in_place_type_t<CopyThrows>{});
		try
		{
			v1 = v2;
			GTEST_FAIL();
		}
		catch (...)
		{
			/* ... */
		}
		// Test that copy construction is used directly if move construction may throw,
		// resulting in a valueless variant if copy throws.
		EXPECT_TRUE(v1.valueless_by_exception());
	}
	{
		using V = bksge::variant<int, MoveThrows, std::string>;
		V v1(bksge::in_place_type_t<std::string>{}, "hello");
		V v2(bksge::in_place_type_t<MoveThrows>{});
		EXPECT_EQ(MoveThrows::alive, 1);
		// Test that copy construction is used directly if move construction may throw.
		v1 = v2;
		EXPECT_EQ(v1.index(), 1u);
		EXPECT_EQ(v2.index(), 1u);
		EXPECT_EQ(MoveThrows::alive, 2);
	}
	{
		// Test that direct copy construction is preferred when it cannot throw.
		using V = bksge::variant<int, CopyCannotThrow, std::string>;
		V v1(bksge::in_place_type_t<std::string>{}, "hello");
		V v2(bksge::in_place_type_t<CopyCannotThrow>{});
		EXPECT_EQ(CopyCannotThrow::alive, 1);
		v1 = v2;
		EXPECT_EQ(v1.index(), 1u);
		EXPECT_EQ(v2.index(), 1u);
		EXPECT_EQ(CopyCannotThrow::alive, 2);
	}
	{
		using V = bksge::variant<int, CopyThrows, std::string>;
		V v1(bksge::in_place_type_t<CopyThrows>{});
		V v2(bksge::in_place_type_t<std::string>{}, "hello");
		V& vref = (v1 = v2);
		EXPECT_EQ(&vref, &v1);
		EXPECT_EQ(v1.index(), 2u);
		EXPECT_EQ(get<2>(v1), "hello");
		EXPECT_EQ(v2.index(), 2u);
		EXPECT_EQ(get<2>(v2), "hello");
	}
	{
		using V = bksge::variant<int, MoveThrows, std::string>;
		V v1(bksge::in_place_type_t<MoveThrows>{});
		V v2(bksge::in_place_type_t<std::string>{}, "hello");
		V& vref = (v1 = v2);
		EXPECT_EQ(&vref, &v1);
		EXPECT_EQ(v1.index(), 2u);
		EXPECT_EQ(get<2>(v1), "hello");
		EXPECT_EQ(v2.index(), 2u);
		EXPECT_EQ(get<2>(v2), "hello");
	}
#endif

	// Make sure we properly propagate triviality, which implies constexpr-ness (see P0602R4).
#if BKSGE_CXX_STANDARD >= 20
	{
		struct
		{
			constexpr Result<long> operator()() const
			{
				using V = bksge::variant<int, long, unsigned>;
				V v(43);
				V v2(42l);
				v = v2;
				return { v.index(), get<1>(v) };
			}
		} test;

		constexpr auto result = test();
		static_assert(result.index == 1, "");
		static_assert(result.value == 42l, "");
	}
	{
		struct
		{
			constexpr Result<int> operator()() const
			{
				using V = bksge::variant<int, TCopyAssign, unsigned>;
				V v(bksge::in_place_type_t<unsigned>{}, 43u);
				V v2(bksge::in_place_type_t<TCopyAssign>{}, 42);
				v = v2;
				return { v.index(), get<1>(v).value };
			}
		} test;

		constexpr auto result = test();
		static_assert(result.index == 1, "");
		static_assert(result.value == 42, "");
	}
#endif
}

#if BKSGE_CXX_STANDARD >= 20
template <size_t NewIdx, class ValueType>
constexpr bool test_constexpr_assign_imp(
	bksge::variant<long, void*, int>&& v, ValueType&& new_value)
{
	using std::get;
	const bksge::variant<long, void*, int> cp(
		bksge::forward<ValueType>(new_value));
	v = cp;
	return v.index() == NewIdx &&
		get<NewIdx>(v) == get<NewIdx>(cp);
}
#endif

void test_constexpr_copy_assignment()
{
	// Make sure we properly propagate triviality, which implies constexpr-ness (see P0602R4).
#if BKSGE_CXX_STANDARD >= 20
	using V = bksge::variant<long, void*, int>;
	static_assert(bksge::is_trivially_copyable<V>::value, "");
	static_assert(bksge::is_trivially_copy_assignable<V>::value, "");
	static_assert(test_constexpr_assign_imp<0>(V(42l), 101l), "");
	static_assert(test_constexpr_assign_imp<0>(V(nullptr), 101l), "");
	static_assert(test_constexpr_assign_imp<1>(V(42l), nullptr), "");
	static_assert(test_constexpr_assign_imp<2>(V(42l), 101), "");
#endif
}

GTEST_TEST(VariantTest, AssignCopyTest)
{
	test_copy_assignment_empty_empty();
	test_copy_assignment_non_empty_empty();
	test_copy_assignment_empty_non_empty();
	test_copy_assignment_same_index();
	test_copy_assignment_different_index();
	test_copy_assignment_sfinae();
	test_copy_assignment_not_noexcept();
	test_constexpr_copy_assignment();
}

}	// namespace assign_copy_test

}	// namespace bksge_variant_test
