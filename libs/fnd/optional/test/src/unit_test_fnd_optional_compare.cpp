/**
 *	@file	unit_test_fnd_optional_compare.cpp
 *
 *	@brief	optional のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/optional/optional.hpp>
#include <bksge/fnd/optional/nullopt.hpp>
#include <bksge/fnd/compare/is_eq.hpp>
#include <bksge/fnd/compare/is_lt.hpp>
#include <bksge/fnd/compare/is_gt.hpp>
#include <bksge/fnd/compare/concepts/three_way_comparable_with.hpp>
#include <bksge/fnd/utility/in_place.hpp>
#include <bksge/fnd/tuple/tie.hpp>
#include <bksge/fnd/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace bksge_optional_test
{

namespace compare_test
{

struct value_type
{
	int i;
	float f;
};

inline BKSGE_CXX14_CONSTEXPR bool
operator==(value_type const& lhs, value_type const& rhs)
{
	return bksge::tie(lhs.i, lhs.f) == bksge::tie(rhs.i, rhs.f);
}

inline BKSGE_CXX14_CONSTEXPR bool
operator!=(value_type const& lhs, value_type const& rhs)
{
	return !(lhs == rhs);
}

inline BKSGE_CXX14_CONSTEXPR bool
operator<(value_type const& lhs, value_type const& rhs)
{
	return bksge::tie(lhs.i, lhs.f) < bksge::tie(rhs.i, rhs.f);
}

inline BKSGE_CXX14_CONSTEXPR bool
operator>(value_type const& lhs, value_type const& rhs)
{
	return rhs < lhs;
}

inline BKSGE_CXX14_CONSTEXPR bool
operator<=(value_type const& lhs, value_type const& rhs)
{
	return !(lhs > rhs);
}

inline BKSGE_CXX14_CONSTEXPR bool
operator>=(value_type const& lhs, value_type const& rhs)
{
	return !(lhs < rhs);
}

GTEST_TEST(OptionalTest, CompareTest)
{
	using O = bksge::optional<value_type>;

	{
		BKSGE_CXX14_CONSTEXPR O o;
		BKSGE_CXX14_CONSTEXPR O p;
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE (o == p);
		BKSGE_CXX14_CONSTEXPR_EXPECT_FALSE(o != p);
		BKSGE_CXX14_CONSTEXPR_EXPECT_FALSE(o < p);
		BKSGE_CXX14_CONSTEXPR_EXPECT_FALSE(o > p);
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE (o <= p);
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE (o >= p);
	}

	{
		BKSGE_CXX14_CONSTEXPR O o{ value_type{ 42, 0.5f } };
		BKSGE_CXX14_CONSTEXPR O p;
		BKSGE_CXX14_CONSTEXPR_EXPECT_FALSE(o == p);
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE (o != p);
		BKSGE_CXX14_CONSTEXPR_EXPECT_FALSE(o < p);
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE (o > p);
		BKSGE_CXX14_CONSTEXPR_EXPECT_FALSE(o <= p);
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE (o >= p);
	}

	{
		BKSGE_CXX14_CONSTEXPR O o;
		BKSGE_CXX14_CONSTEXPR O p{ value_type{ 42, 0.5f } };
		BKSGE_CXX14_CONSTEXPR_EXPECT_FALSE(o == p);
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE (o != p);
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE (o < p);
		BKSGE_CXX14_CONSTEXPR_EXPECT_FALSE(o > p);
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE (o <= p);
		BKSGE_CXX14_CONSTEXPR_EXPECT_FALSE(o >= p);
	}

	{
		BKSGE_CXX14_CONSTEXPR O o{ value_type{ 11, 0.5f } };
		BKSGE_CXX14_CONSTEXPR O p{ value_type{ 42, 0.5f } };
		BKSGE_CXX14_CONSTEXPR_EXPECT_FALSE(o == p);
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE (o != p);
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE (o < p);
		BKSGE_CXX14_CONSTEXPR_EXPECT_FALSE(o > p);
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE (o <= p);
		BKSGE_CXX14_CONSTEXPR_EXPECT_FALSE(o >= p);
	}

	{
		BKSGE_CXX14_CONSTEXPR O o{ value_type{ 42, 0.5f } };
		BKSGE_CXX14_CONSTEXPR O p{ value_type{ 11, 0.5f } };
		BKSGE_CXX14_CONSTEXPR_EXPECT_FALSE(o == p);
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE (o != p);
		BKSGE_CXX14_CONSTEXPR_EXPECT_FALSE(o < p);
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE (o > p);
		BKSGE_CXX14_CONSTEXPR_EXPECT_FALSE(o <= p);
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE (o >= p);
	}

	{
		BKSGE_CXX14_CONSTEXPR O o{ value_type{ 42, 0.5f } };
		BKSGE_CXX14_CONSTEXPR O p{ value_type{ 42, 1.5f } };
		BKSGE_CXX14_CONSTEXPR_EXPECT_FALSE(o == p);
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE (o != p);
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE (o < p);
		BKSGE_CXX14_CONSTEXPR_EXPECT_FALSE(o > p);
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE (o <= p);
		BKSGE_CXX14_CONSTEXPR_EXPECT_FALSE(o >= p);
	}

	{
		BKSGE_CXX14_CONSTEXPR O o{ value_type{ 42, 1.5f } };
		BKSGE_CXX14_CONSTEXPR O p{ value_type{ 42, 0.5f } };
		BKSGE_CXX14_CONSTEXPR_EXPECT_FALSE(o == p);
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE (o != p);
		BKSGE_CXX14_CONSTEXPR_EXPECT_FALSE(o < p);
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE (o > p);
		BKSGE_CXX14_CONSTEXPR_EXPECT_FALSE(o <= p);
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE (o >= p);
	}

	{
		BKSGE_CXX14_CONSTEXPR O o{ value_type{ 42, 1.5f } };
		BKSGE_CXX14_CONSTEXPR O p{ value_type{ 42, 1.5f } };
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE (o == p);
		BKSGE_CXX14_CONSTEXPR_EXPECT_FALSE(o != p);
		BKSGE_CXX14_CONSTEXPR_EXPECT_FALSE(o < p);
		BKSGE_CXX14_CONSTEXPR_EXPECT_FALSE(o > p);
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE (o <= p);
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE (o >= p);
	}

	BKSGE_CONSTEXPR value_type const r{ 42, 0.5f };

	{
		BKSGE_CXX14_CONSTEXPR O o;
		BKSGE_CXX14_CONSTEXPR_EXPECT_FALSE(o == r);
		BKSGE_CXX14_CONSTEXPR_EXPECT_FALSE(r == o);
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE (o != r);
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE (r != o);
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE (o < r);
		BKSGE_CXX14_CONSTEXPR_EXPECT_FALSE(r < o);
		BKSGE_CXX14_CONSTEXPR_EXPECT_FALSE(o > r);
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE (r > o);
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE (o <= r);
		BKSGE_CXX14_CONSTEXPR_EXPECT_FALSE(r <= o);
		BKSGE_CXX14_CONSTEXPR_EXPECT_FALSE(o >= r);
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE (r >= o);
	}

	{
		BKSGE_CXX14_CONSTEXPR O o{ value_type{ 11, 0.5f } };
		BKSGE_CXX14_CONSTEXPR_EXPECT_FALSE(o == r);
		BKSGE_CXX14_CONSTEXPR_EXPECT_FALSE(r == o);
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE (o != r);
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE (r != o);
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE (o < r);
		BKSGE_CXX14_CONSTEXPR_EXPECT_FALSE(r < o);
		BKSGE_CXX14_CONSTEXPR_EXPECT_FALSE(o > r);
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE (r > o);
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE (o <= r);
		BKSGE_CXX14_CONSTEXPR_EXPECT_FALSE(r <= o);
		BKSGE_CXX14_CONSTEXPR_EXPECT_FALSE(o >= r);
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE (r >= o);
	}

	{
		BKSGE_CXX14_CONSTEXPR O o{ value_type{ 42, 0.5f } };
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE (o == r);
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE (r == o);
		BKSGE_CXX14_CONSTEXPR_EXPECT_FALSE(o != r);
		BKSGE_CXX14_CONSTEXPR_EXPECT_FALSE(r != o);
		BKSGE_CXX14_CONSTEXPR_EXPECT_FALSE(o < r);
		BKSGE_CXX14_CONSTEXPR_EXPECT_FALSE(r < o);
		BKSGE_CXX14_CONSTEXPR_EXPECT_FALSE(o > r);
		BKSGE_CXX14_CONSTEXPR_EXPECT_FALSE(r > o);
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE (o <= r);
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE (r <= o);
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE (o >= r);
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE (r >= o);
	}

	// bksge::nullopt

	{
		BKSGE_CXX14_CONSTEXPR O o;
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE (o == bksge::nullopt);
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE (bksge::nullopt == o);
		BKSGE_CXX14_CONSTEXPR_EXPECT_FALSE(o != bksge::nullopt);
		BKSGE_CXX14_CONSTEXPR_EXPECT_FALSE(bksge::nullopt != o);
		BKSGE_CXX14_CONSTEXPR_EXPECT_FALSE(o < bksge::nullopt);
		BKSGE_CXX14_CONSTEXPR_EXPECT_FALSE(bksge::nullopt < o);
		BKSGE_CXX14_CONSTEXPR_EXPECT_FALSE(o > bksge::nullopt);
		BKSGE_CXX14_CONSTEXPR_EXPECT_FALSE(bksge::nullopt > o);
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE (o <= bksge::nullopt);
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE (bksge::nullopt <= o);
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE (o >= bksge::nullopt);
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE (bksge::nullopt >= o);
	}

	{
		BKSGE_CXX14_CONSTEXPR O o{ bksge::in_place };
		BKSGE_CXX14_CONSTEXPR_EXPECT_FALSE(o == bksge::nullopt);
		BKSGE_CXX14_CONSTEXPR_EXPECT_FALSE(bksge::nullopt == o);
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE (o != bksge::nullopt);
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE (bksge::nullopt != o);
		BKSGE_CXX14_CONSTEXPR_EXPECT_FALSE(o < bksge::nullopt);
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE (bksge::nullopt < o);
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE (o > bksge::nullopt);
		BKSGE_CXX14_CONSTEXPR_EXPECT_FALSE(bksge::nullopt > o);
		BKSGE_CXX14_CONSTEXPR_EXPECT_FALSE(o <= bksge::nullopt);
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE (bksge::nullopt <= o);
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE (o >= bksge::nullopt);
		BKSGE_CXX14_CONSTEXPR_EXPECT_FALSE(bksge::nullopt >= o);
	}
}

GTEST_TEST(OptionalTest, CompareThreeWayTest)
{
#if defined(BKSGE_HAS_CXX20_THREE_WAY_COMPARISON)
	{
		using O = bksge::optional<int>;

		static_assert(bksge::is_eq(O{} <=> O{}), "");
		static_assert(bksge::is_lt(O{} <=> O{1}), "");
		static_assert(bksge::is_gt(O{1} <=> O{}), "");
		static_assert(bksge::is_eq(O{1} <=> O{1}), "");
		static_assert(bksge::is_lt(O{1} <=> O{2}), "");

		static_assert(O{} == O{}, "");
		static_assert(O{} <  O{1}, "");
		static_assert(O{1} >  O{}, "");
		static_assert(O{1} == O{1}, "");
		static_assert(O{1} != O{2}, "");
		static_assert(O{1} <  O{2}, "");

		using Os = bksge::optional<short>;
		static_assert(bksge::is_eq(O{} <=> Os{}), "");
		static_assert(bksge::is_lt(O{} <=> Os{short(1)}), "");
		static_assert(bksge::is_gt(O{1} <=> Os{}), "");
		static_assert(bksge::is_eq(O{1} <=> Os{short(1)}), "");
		static_assert(bksge::is_lt(O{1} <=> Os{short(2)}), "");

		static_assert(O{} == Os{}, "");
		static_assert(O{} <  Os{short(1)}, "");
		static_assert(O{1} >  Os{}, "");
		static_assert(O{1} == Os{short(1)}, "");
		static_assert(O{1} != Os{short(2)}, "");
		static_assert(O{1} <  Os{short(2)}, "");

		// Would requires narrowing conversion to make operands the same type:
		static_assert(!bksge::three_way_comparable_with<O, bksge::optional<unsigned>>, "");
	}
	{
		using O = bksge::optional<int>;
		using bksge::nullopt;

		static_assert(bksge::is_eq(O{} <=> nullopt), "");
		static_assert(bksge::is_gt(O{1} <=> nullopt), "");
		static_assert(bksge::is_lt(nullopt <=> O{1}), "");

		static_assert(O{}  == nullopt, "");
		static_assert(O{1} != nullopt, "");
		static_assert(nullopt != O{1}, "");
		static_assert(O{1} > nullopt, "");
		static_assert(nullopt <  O{1}, "");
		static_assert(nullopt <= O{}, "");
		static_assert(nullopt <= O{1}, "");
	}
#endif
}

}	// namespace compare_test

}	// namespace bksge_optional_test
