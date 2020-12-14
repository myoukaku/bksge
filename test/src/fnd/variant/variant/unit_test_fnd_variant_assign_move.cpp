/**
 *	@file	unit_test_fnd_variant_assign_move.cpp
 *
 *	@brief	variant& operator=(variant&&) のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/variant/variant.hpp>
#include <bksge/fnd/variant/variant_npos.hpp>
#include <bksge/fnd/variant/get.hpp>
#include <bksge/fnd/type_traits/is_move_assignable.hpp>
#include <bksge/fnd/type_traits/is_nothrow_move_assignable.hpp>
#include <bksge/fnd/type_traits/is_trivially_copyable.hpp>
#include <bksge/fnd/type_traits/is_trivially_copy_assignable.hpp>
#include <bksge/fnd/type_traits/is_trivially_move_assignable.hpp>
#include <bksge/fnd/utility/in_place_index.hpp>
#include <bksge/fnd/utility/in_place_type.hpp>
#include <bksge/fnd/utility/move.hpp>
#include <bksge/fnd/utility/forward.hpp>
#include <bksge/fnd/config.hpp>
#include <string>
#include <gtest/gtest.h>
#include "fnd/variant/test_macros.hpp"
#include "fnd/variant/variant_test_helpers.hpp"

namespace bksge_variant_test
{

namespace assign_move_test
{

struct NoCopy
{
	NoCopy(const NoCopy&) = delete;
	NoCopy& operator=(const NoCopy&) = default;
};

struct CopyOnly
{
	CopyOnly(const CopyOnly&) = default;
	CopyOnly(CopyOnly&&) = delete;
	CopyOnly& operator=(const CopyOnly&) = default;
	CopyOnly& operator=(CopyOnly&&) = delete;
};

struct MoveOnly
{
	MoveOnly(const MoveOnly&) = delete;
	MoveOnly(MoveOnly&&) = default;
	MoveOnly& operator=(const MoveOnly&) = delete;
	MoveOnly& operator=(MoveOnly&&) = default;
};

struct MoveOnlyNT
{
	MoveOnlyNT(const MoveOnlyNT&) = delete;
	MoveOnlyNT(MoveOnlyNT&&) {}
	MoveOnlyNT& operator=(const MoveOnlyNT&) = delete;
	MoveOnlyNT& operator=(MoveOnlyNT&&) = default;
};

struct MoveOnlyOddNothrow
{
	MoveOnlyOddNothrow(MoveOnlyOddNothrow&&) noexcept(false) {}
	MoveOnlyOddNothrow(const MoveOnlyOddNothrow&) = delete;
	MoveOnlyOddNothrow& operator=(MoveOnlyOddNothrow&&) noexcept = default;
	MoveOnlyOddNothrow& operator=(const MoveOnlyOddNothrow&) = delete;
};

struct MoveAssignOnly
{
	MoveAssignOnly(MoveAssignOnly&&) = delete;
	MoveAssignOnly& operator=(MoveAssignOnly&&) = default;
};

struct MoveAssign
{
	static int move_construct;
	static int move_assign;
	static void reset() { move_construct = move_assign = 0; }
	MoveAssign(int v) : value(v) {}
	MoveAssign(MoveAssign&& o) : value(o.value)
	{
		++move_construct;
		o.value = -1;
	}
	MoveAssign& operator=(MoveAssign&& o)
	{
		value = o.value;
		++move_assign;
		o.value = -1;
		return *this;
	}
	int value;
};

int MoveAssign::move_construct = 0;
int MoveAssign::move_assign = 0;

struct NTMoveAssign
{
	constexpr NTMoveAssign(int v) : value(v) {}
	NTMoveAssign(const NTMoveAssign&) = default;
	NTMoveAssign(NTMoveAssign&&) = default;
	NTMoveAssign& operator=(const NTMoveAssign& that) = default;
	NTMoveAssign& operator=(NTMoveAssign&& that)
	{
		value = that.value;
		that.value = -1;
		return *this;
	};
	int value;
};

static_assert(!bksge::is_trivially_move_assignable<NTMoveAssign>::value, "");
static_assert(bksge::is_move_assignable<NTMoveAssign>::value, "");

struct TMoveAssign
{
	constexpr TMoveAssign(int v) : value(v) {}
	TMoveAssign(const TMoveAssign&) = delete;
	TMoveAssign(TMoveAssign&&) = default;
	TMoveAssign& operator=(const TMoveAssign&) = delete;
	TMoveAssign& operator=(TMoveAssign&&) = default;
	int value;
};

static_assert(bksge::is_trivially_move_assignable<TMoveAssign>::value, "");

struct TMoveAssignNTCopyAssign
{
	constexpr TMoveAssignNTCopyAssign(int v) : value(v) {}
	TMoveAssignNTCopyAssign(const TMoveAssignNTCopyAssign&) = default;
	TMoveAssignNTCopyAssign(TMoveAssignNTCopyAssign&&) = default;
	TMoveAssignNTCopyAssign& operator=(const TMoveAssignNTCopyAssign& that)
	{
		value = that.value;
		return *this;
	}
	TMoveAssignNTCopyAssign& operator=(TMoveAssignNTCopyAssign&&) = default;
	int value;
};

static_assert(bksge::is_trivially_move_assignable<TMoveAssignNTCopyAssign>::value, "");

struct TrivialCopyNontrivialMove
{
	TrivialCopyNontrivialMove(TrivialCopyNontrivialMove const&) = default;
	TrivialCopyNontrivialMove(TrivialCopyNontrivialMove&&) noexcept {}
	TrivialCopyNontrivialMove& operator=(TrivialCopyNontrivialMove const&) = default;
	TrivialCopyNontrivialMove& operator=(TrivialCopyNontrivialMove&&) noexcept { return *this; }
};

static_assert(bksge::is_trivially_copy_assignable<TrivialCopyNontrivialMove>::value, "");
static_assert(!bksge::is_trivially_move_assignable<TrivialCopyNontrivialMove>::value, "");

void test_move_assignment_noexcept()
{
	{
		using V = bksge::variant<int>;
		static_assert(bksge::is_nothrow_move_assignable<V>::value, "");
	}
	{
		using V = bksge::variant<MoveOnly>;
		static_assert(bksge::is_nothrow_move_assignable<V>::value, "");
	}
	{
		using V = bksge::variant<int, long>;
		static_assert(bksge::is_nothrow_move_assignable<V>::value, "");
	}
	{
		using V = bksge::variant<int, MoveOnly>;
		static_assert(bksge::is_nothrow_move_assignable<V>::value, "");
	}
	{
		using V = bksge::variant<MoveOnlyNT>;
		static_assert(!bksge::is_nothrow_move_assignable<V>::value, "");
	}
	{
		using V = bksge::variant<MoveOnlyOddNothrow>;
		static_assert(!bksge::is_nothrow_move_assignable<V>::value, "");
	}
}

void test_move_assignment_sfinae()
{
	{
		using V = bksge::variant<int, long>;
		static_assert(bksge::is_move_assignable<V>::value, "");
	}
	{
		using V = bksge::variant<int, CopyOnly>;
		static_assert(bksge::is_move_assignable<V>::value, "");
	}
	{
		using V = bksge::variant<int, NoCopy>;
		static_assert(!bksge::is_move_assignable<V>::value, "");
	}
	{
		using V = bksge::variant<int, MoveOnly>;
		static_assert(bksge::is_move_assignable<V>::value, "");
	}
	{
		using V = bksge::variant<int, MoveOnlyNT>;
		static_assert(bksge::is_move_assignable<V>::value, "");
	}
	{
		// variant only provides move assignment when the types also provide
		// a move constructor.
		using V = bksge::variant<int, MoveAssignOnly>;
		static_assert(!bksge::is_move_assignable<V>::value, "");
	}

	// Make sure we properly propagate triviality (see P0602R4).
#if BKSGE_CXX_STANDARD >= 20
	{
		using V = bksge::variant<int, long>;
		static_assert(bksge::is_trivially_move_assignable<V>::value, "");
	}
	{
		using V = bksge::variant<int, NTMoveAssign>;
		static_assert(!bksge::is_trivially_move_assignable<V>::value, "");
		static_assert(bksge::is_move_assignable<V>::value, "");
	}
	{
		using V = bksge::variant<int, TMoveAssign>;
		static_assert(bksge::is_trivially_move_assignable<V>::value, "");
	}
	{
		using V = bksge::variant<int, TMoveAssignNTCopyAssign>;
		static_assert(bksge::is_trivially_move_assignable<V>::value, "");
	}
	{
		using V = bksge::variant<int, TrivialCopyNontrivialMove>;
		static_assert(!bksge::is_trivially_move_assignable<V>::value, "");
	}
	{
		using V = bksge::variant<int, CopyOnly>;
		static_assert(bksge::is_trivially_move_assignable<V>::value, "");
	}
#endif
}

void test_move_assignment_empty_empty()
{
#if !defined(BKSGE_NO_EXCEPTIONS)
	using MET = MakeEmptyT;
	{
		using V = bksge::variant<int, long, MET>;
		V v1(bksge::in_place_index_t<0>{});
		makeEmpty(v1);
		V v2(bksge::in_place_index_t<0>{});
		makeEmpty(v2);
		V& vref = (v1 = bksge::move(v2));
		EXPECT_EQ(&vref, &v1);
		EXPECT_TRUE(v1.valueless_by_exception());
		EXPECT_EQ(v1.index(), bksge::variant_npos);
	}
#endif
}

void test_move_assignment_non_empty_empty()
{
#if !defined(BKSGE_NO_EXCEPTIONS)
	using MET = MakeEmptyT;
	{
		using V = bksge::variant<int, MET>;
		V v1(bksge::in_place_index_t<0>{}, 42);
		V v2(bksge::in_place_index_t<0>{});
		makeEmpty(v2);
		V& vref = (v1 = bksge::move(v2));
		EXPECT_EQ(&vref, &v1);
		EXPECT_TRUE(v1.valueless_by_exception());
		EXPECT_EQ(v1.index(), bksge::variant_npos);
	}
	{
		using V = bksge::variant<int, MET, std::string>;
		V v1(bksge::in_place_index_t<2>{}, "hello");
		V v2(bksge::in_place_index_t<0>{});
		makeEmpty(v2);
		V& vref = (v1 = bksge::move(v2));
		EXPECT_EQ(&vref, &v1);
		EXPECT_TRUE(v1.valueless_by_exception());
		EXPECT_EQ(v1.index(), bksge::variant_npos);
	}
#endif
}

void test_move_assignment_empty_non_empty()
{
#if !defined(BKSGE_NO_EXCEPTIONS)
	using std::get;
	using MET = MakeEmptyT;
	{
		using V = bksge::variant<int, MET>;
		V v1(bksge::in_place_index_t<0>{});
		makeEmpty(v1);
		V v2(bksge::in_place_index_t<0>{}, 42);
		V& vref = (v1 = bksge::move(v2));
		EXPECT_EQ(&vref, &v1);
		EXPECT_EQ(v1.index(), 0u);
		EXPECT_EQ(get<0>(v1), 42);
	}
	{
		using V = bksge::variant<int, MET, std::string>;
		V v1(bksge::in_place_index_t<0>{});
		makeEmpty(v1);
		V v2(bksge::in_place_type_t<std::string>{}, "hello");
		V& vref = (v1 = bksge::move(v2));
		EXPECT_EQ(&vref, &v1);
		EXPECT_EQ(v1.index(), 2u);
		EXPECT_EQ(get<2>(v1), "hello");
	}
#endif
}

template <typename T> struct Result { size_t index; T value; };

void test_move_assignment_same_index()
{
	using std::get;
	{
		using V = bksge::variant<int>;
		V v1(43);
		V v2(42);
		V& vref = (v1 = bksge::move(v2));
		EXPECT_EQ(&vref, &v1);
		EXPECT_EQ(v1.index(), 0u);
		EXPECT_EQ(get<0>(v1), 42);
	}
	{
		using V = bksge::variant<int, long, unsigned>;
		V v1(43l);
		V v2(42l);
		V& vref = (v1 = bksge::move(v2));
		EXPECT_EQ(&vref, &v1);
		EXPECT_EQ(v1.index(), 1u);
		EXPECT_EQ(get<1>(v1), 42);
	}
	{
		using V = bksge::variant<int, MoveAssign, unsigned>;
		V v1(bksge::in_place_type_t<MoveAssign>{}, 43);
		V v2(bksge::in_place_type_t<MoveAssign>{}, 42);
		MoveAssign::reset();
		V& vref = (v1 = bksge::move(v2));
		EXPECT_EQ(&vref, &v1);
		EXPECT_EQ(v1.index(), 1u);
		EXPECT_EQ(get<1>(v1).value, 42);
		EXPECT_EQ(MoveAssign::move_construct, 0);
		EXPECT_EQ(MoveAssign::move_assign, 1);
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
			v1 = bksge::move(v2);
			assert(false);
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
				v = bksge::move(v2);
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
				v = bksge::move(v2);
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
				using V = bksge::variant<int, TMoveAssign, unsigned>;
				V v(bksge::in_place_type_t<TMoveAssign>{}, 43);
				V v2(bksge::in_place_type_t<TMoveAssign>{}, 42);
				v = bksge::move(v2);
				return { v.index(), get<1>(v).value };
			}
		} test;
		constexpr auto result = test();
		static_assert(result.index == 1, "");
		static_assert(result.value == 42, "");
	}
#endif
}

void test_move_assignment_different_index()
{
	using std::get;
	{
		using V = bksge::variant<int, long, unsigned>;
		V v1(43);
		V v2(42l);
		V& vref = (v1 = bksge::move(v2));
		EXPECT_EQ(&vref, &v1);
		EXPECT_EQ(v1.index(), 1u);
		EXPECT_EQ(get<1>(v1), 42);
	}
	{
		using V = bksge::variant<int, MoveAssign, unsigned>;
		V v1(bksge::in_place_type_t<unsigned>{}, 43u);
		V v2(bksge::in_place_type_t<MoveAssign>{}, 42);
		MoveAssign::reset();
		V& vref = (v1 = bksge::move(v2));
		EXPECT_EQ(&vref, &v1);
		EXPECT_EQ(v1.index(), 1u);
		EXPECT_EQ(get<1>(v1).value, 42);
		EXPECT_EQ(MoveAssign::move_construct, 1);
		EXPECT_EQ(MoveAssign::move_assign, 0);
	}
#if !defined(BKSGE_NO_EXCEPTIONS)
	using MET = MakeEmptyT;
	{
		using V = bksge::variant<int, MET, std::string>;
		V v1(bksge::in_place_type_t<int>{});
		V v2(bksge::in_place_type_t<MET>{});
		try
		{
			v1 = bksge::move(v2);
			assert(false);
		}
		catch (...)
		{
		}
		EXPECT_TRUE(v1.valueless_by_exception());
		EXPECT_EQ(v1.index(), bksge::variant_npos);
	}
	{
		using V = bksge::variant<int, MET, std::string>;
		V v1(bksge::in_place_type_t<MET>{});
		V v2(bksge::in_place_type_t<std::string>{}, "hello");
		V& vref = (v1 = bksge::move(v2));
		EXPECT_EQ(&vref, &v1);
		EXPECT_EQ(v1.index(), 2u);
		EXPECT_EQ(get<2>(v1), "hello");
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
				v = bksge::move(v2);
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
			constexpr Result<long> operator()() const
			{
				using V = bksge::variant<int, TMoveAssign, unsigned>;
				V v(bksge::in_place_type_t<unsigned>{}, 43u);
				V v2(bksge::in_place_type_t<TMoveAssign>{}, 42);
				v = bksge::move(v2);
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
	bksge::variant<long, void*, int> v2(
		bksge::forward<ValueType>(new_value));
	const auto cp = v2;
	v = bksge::move(v2);
	return v.index() == NewIdx &&
		get<NewIdx>(v) == get<NewIdx>(cp);
}
#endif

void test_constexpr_move_assignment()
{
	// Make sure we properly propagate triviality, which implies constexpr-ness (see P0602R4).
#if BKSGE_CXX_STANDARD >= 20
	using V = bksge::variant<long, void*, int>;
	static_assert(bksge::is_trivially_copyable<V>::value, "");
	static_assert(bksge::is_trivially_move_assignable<V>::value, "");
	static_assert(test_constexpr_assign_imp<0>(V(42l), 101l), "");
	static_assert(test_constexpr_assign_imp<0>(V(nullptr), 101l), "");
	static_assert(test_constexpr_assign_imp<1>(V(42l), nullptr), "");
	static_assert(test_constexpr_assign_imp<2>(V(42l), 101), "");
#endif
}

GTEST_TEST(VariantTest, AssignMoveTest)
{
	test_move_assignment_empty_empty();
	test_move_assignment_non_empty_empty();
	test_move_assignment_empty_non_empty();
	test_move_assignment_same_index();
	test_move_assignment_different_index();
	test_move_assignment_sfinae();
	test_move_assignment_noexcept();
	test_constexpr_move_assignment();
}

}	// namespace assign_move_test

}	// namespace bksge_variant_test
