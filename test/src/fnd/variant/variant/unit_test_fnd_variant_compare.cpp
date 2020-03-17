/**
 *	@file	unit_test_fnd_variant_compare.cpp
 *
 *	@brief	variant のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/variant/variant.hpp>
#include <bksge/fnd/utility/in_place_type.hpp>
#include <bksge/fnd/utility/in_place_index.hpp>
#include <bksge/fnd/utility/move.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <bksge/fnd/config.hpp>
#include <gtest/gtest.h>

namespace bksge_variant_test
{

namespace compare_test
{

#if !defined(BKSGE_NO_EXCEPTIONS)

struct MakeEmptyT
{
	MakeEmptyT() = default;
	MakeEmptyT(MakeEmptyT&&) { throw 42; }
	MakeEmptyT& operator=(MakeEmptyT&&) { throw 42; }
};
inline bool operator==(const MakeEmptyT&, const MakeEmptyT&)
{
	assert(false);
	return false;
}
inline bool operator!=(const MakeEmptyT&, const MakeEmptyT&)
{
	assert(false);
	return false;
}
inline bool operator<(const MakeEmptyT&, const MakeEmptyT&)
{
	assert(false);
	return false;
}
inline bool operator<=(const MakeEmptyT&, const MakeEmptyT&)
{
	assert(false);
	return false;
}
inline bool operator>(const MakeEmptyT&, const MakeEmptyT&)
{
	assert(false);
	return false;
}
inline bool operator>=(const MakeEmptyT&, const MakeEmptyT&)
{
	assert(false);
	return false;
}

template <class Variant>
void makeEmpty(Variant& v)
{
	Variant v2(bksge::in_place_type_t<MakeEmptyT>{});
	try
	{
		v = bksge::move(v2);
		assert(false);
	}
	catch (...)
	{
		EXPECT_TRUE(v.valueless_by_exception());
	}
}

#endif

struct MyBool
{
	bool value;
	constexpr explicit MyBool(bool v) : value(v) {}
	constexpr operator bool() const noexcept { return value; }
};

struct ComparesToMyBool
{
	int value = 0;

#if BKSGE_CXX_STANDARD < 14
	constexpr ComparesToMyBool(int v) : value(v) {}
#endif
};
inline constexpr MyBool
operator==(const ComparesToMyBool& LHS, const ComparesToMyBool& RHS) noexcept
{
	return MyBool(LHS.value == RHS.value);
}
inline constexpr MyBool
operator!=(const ComparesToMyBool& LHS, const ComparesToMyBool& RHS) noexcept
{
	return MyBool(LHS.value != RHS.value);
}
inline constexpr MyBool
operator<(const ComparesToMyBool& LHS, const ComparesToMyBool& RHS) noexcept
{
	return MyBool(LHS.value < RHS.value);
}
inline constexpr MyBool
operator<=(const ComparesToMyBool& LHS, const ComparesToMyBool& RHS) noexcept
{
	return MyBool(LHS.value <= RHS.value);
}
inline constexpr MyBool
operator>(const ComparesToMyBool& LHS, const ComparesToMyBool& RHS) noexcept
{
	return MyBool(LHS.value > RHS.value);
}
inline constexpr MyBool
operator>=(const ComparesToMyBool& LHS, const ComparesToMyBool& RHS) noexcept
{
	return MyBool(LHS.value >= RHS.value);
}

template <class T1, class T2>
void test_equality_basic()
{
	{
		using V = bksge::variant<T1, T2>;
		constexpr V v1(bksge::in_place_index_t<0>{}, T1{42});
		constexpr V v2(bksge::in_place_index_t<0>{}, T1{42});
		static_assert(v1 == v2, "");
		static_assert(v2 == v1, "");
		static_assert(!(v1 != v2), "");
		static_assert(!(v2 != v1), "");
	}
	{
		using V = bksge::variant<T1, T2>;
		constexpr V v1(bksge::in_place_index_t<0>{}, T1{42});
		constexpr V v2(bksge::in_place_index_t<0>{}, T1{43});
		static_assert(!(v1 == v2), "");
		static_assert(!(v2 == v1), "");
		static_assert(v1 != v2, "");
		static_assert(v2 != v1, "");
	}
	{
		using V = bksge::variant<T1, T2>;
		constexpr V v1(bksge::in_place_index_t<0>{}, T1{42});
		constexpr V v2(bksge::in_place_index_t<1>{}, T2{42});
		static_assert(!(v1 == v2), "");
		static_assert(!(v2 == v1), "");
		static_assert(v1 != v2, "");
		static_assert(v2 != v1, "");
	}
	{
		using V = bksge::variant<T1, T2>;
		constexpr V v1(bksge::in_place_index_t<1>{}, T2{42});
		constexpr V v2(bksge::in_place_index_t<1>{}, T2{42});
		static_assert(v1 == v2, "");
		static_assert(v2 == v1, "");
		static_assert(!(v1 != v2), "");
		static_assert(!(v2 != v1), "");
	}
}

void test_equality()
{
	test_equality_basic<int, long>();
	test_equality_basic<ComparesToMyBool, int>();
	test_equality_basic<int, ComparesToMyBool>();
	test_equality_basic<ComparesToMyBool, ComparesToMyBool>();
#if !defined(BKSGE_NO_EXCEPTIONS)
	{
		using V = bksge::variant<int, MakeEmptyT>;
		V v1;
		V v2;
		makeEmpty(v2);
		EXPECT_TRUE(!(v1 == v2));
		EXPECT_TRUE(!(v2 == v1));
		EXPECT_TRUE(v1 != v2);
		EXPECT_TRUE(v2 != v1);
	}
	{
		using V = bksge::variant<int, MakeEmptyT>;
		V v1;
		makeEmpty(v1);
		V v2;
		EXPECT_TRUE(!(v1 == v2));
		EXPECT_TRUE(!(v2 == v1));
		EXPECT_TRUE(v1 != v2);
		EXPECT_TRUE(v2 != v1);
	}
	{
		using V = bksge::variant<int, MakeEmptyT>;
		V v1;
		makeEmpty(v1);
		V v2;
		makeEmpty(v2);
		EXPECT_TRUE(v1 == v2);
		EXPECT_TRUE(v2 == v1);
		EXPECT_TRUE(!(v1 != v2));
		EXPECT_TRUE(!(v2 != v1));
	}
#endif
}

template <class Var>
constexpr bool test_less(const Var& l, const Var& r, bool expect_less,
	bool expect_greater)
{
	static_assert(bksge::is_same<decltype(l < r), bool>::value, "");
	static_assert(bksge::is_same<decltype(l <= r), bool>::value, "");
	static_assert(bksge::is_same<decltype(l > r), bool>::value, "");
	static_assert(bksge::is_same<decltype(l >= r), bool>::value, "");

	return ((l < r) == expect_less) && (!(l >= r) == expect_less) &&
		((l > r) == expect_greater) && (!(l <= r) == expect_greater);
}

template <class T1, class T2>
void test_relational_basic()
{
	{
		// same index, same value
		using V = bksge::variant<T1, T2>;
		constexpr V v1(bksge::in_place_index_t<0>{}, T1{1});
		constexpr V v2(bksge::in_place_index_t<0>{}, T1{1});
		static_assert(test_less(v1, v2, false, false), "");
	}
	{
		// same index, value < other_value
		using V = bksge::variant<T1, T2>;
		constexpr V v1(bksge::in_place_index_t<0>{}, T1{0});
		constexpr V v2(bksge::in_place_index_t<0>{}, T1{1});
		static_assert(test_less(v1, v2, true, false), "");
	}
	{
		// same index, value > other_value
		using V = bksge::variant<T1, T2>;
		constexpr V v1(bksge::in_place_index_t<0>{}, T1{1});
		constexpr V v2(bksge::in_place_index_t<0>{}, T1{0});
		static_assert(test_less(v1, v2, false, true), "");
	}
	{
		// LHS.index() < RHS.index()
		using V = bksge::variant<T1, T2>;
		constexpr V v1(bksge::in_place_index_t<0>{}, T1{0});
		constexpr V v2(bksge::in_place_index_t<1>{}, T2{0});
		static_assert(test_less(v1, v2, true, false), "");
	}
	{
		// LHS.index() > RHS.index()
		using V = bksge::variant<T1, T2>;
		constexpr V v1(bksge::in_place_index_t<1>{}, T2{0});
		constexpr V v2(bksge::in_place_index_t<0>{}, T1{0});
		static_assert(test_less(v1, v2, false, true), "");
	}
}

void test_relational()
{
	test_relational_basic<int, long>();
	test_relational_basic<ComparesToMyBool, int>();
	test_relational_basic<int, ComparesToMyBool>();
	test_relational_basic<ComparesToMyBool, ComparesToMyBool>();
#if !defined(BKSGE_NO_EXCEPTIONS)
	{
		// LHS.index() < RHS.index(), RHS is empty
		using V = bksge::variant<int, MakeEmptyT>;
		V v1;
		V v2;
		makeEmpty(v2);
		EXPECT_TRUE(test_less(v1, v2, false, true));
	}
	{
		// LHS.index() > RHS.index(), LHS is empty
		using V = bksge::variant<int, MakeEmptyT>;
		V v1;
		makeEmpty(v1);
		V v2;
		EXPECT_TRUE(test_less(v1, v2, true, false));
	}
	{
		// LHS.index() == RHS.index(), LHS and RHS are empty
		using V = bksge::variant<int, MakeEmptyT>;
		V v1;
		makeEmpty(v1);
		V v2;
		makeEmpty(v2);
		EXPECT_TRUE(test_less(v1, v2, false, false));
	}
#endif
}

GTEST_TEST(VariantTest, CompareTest)
{
	test_equality();
	test_relational();
}

}	// namespace compare_test

}	// namespace bksge_variant_test
