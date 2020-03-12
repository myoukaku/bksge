﻿/**
 *	@file	unit_test_fnd_optional_compare.cpp
 *
 *	@brief	optional のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/optional/optional.hpp>
#include <bksge/fnd/optional/nullopt.hpp>
#include <bksge/fnd/utility/in_place.hpp>
#include <bksge/fnd/config.hpp>
#include <tuple>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

#if defined(_MSC_VER)
#define BKSGE_OPTIONAL_CONSTEXPR
#define BKSGE_OPTIONAL_CXX14_CONSTEXPR_EXPECT_TRUE		EXPECT_TRUE
#define BKSGE_OPTIONAL_CXX14_CONSTEXPR_EXPECT_FALSE		EXPECT_FALSE
#else
#define BKSGE_OPTIONAL_CONSTEXPR						BKSGE_CONSTEXPR
#define BKSGE_OPTIONAL_CXX14_CONSTEXPR_EXPECT_TRUE		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE
#define BKSGE_OPTIONAL_CXX14_CONSTEXPR_EXPECT_FALSE		BKSGE_CXX14_CONSTEXPR_EXPECT_FALSE
#endif

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
	return std::tie(lhs.i, lhs.f) == std::tie(rhs.i, rhs.f);
}

inline BKSGE_CXX14_CONSTEXPR bool
operator!=(value_type const& lhs, value_type const& rhs)
{
	return !(lhs == rhs);
}

inline BKSGE_CXX14_CONSTEXPR bool
operator<(value_type const& lhs, value_type const& rhs)
{
	return std::tie(lhs.i, lhs.f) < std::tie(rhs.i, rhs.f);
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
		BKSGE_OPTIONAL_CONSTEXPR O o;
		BKSGE_OPTIONAL_CONSTEXPR O p;
		BKSGE_OPTIONAL_CXX14_CONSTEXPR_EXPECT_TRUE (o == p);
		BKSGE_OPTIONAL_CXX14_CONSTEXPR_EXPECT_FALSE(o != p);
		BKSGE_OPTIONAL_CXX14_CONSTEXPR_EXPECT_FALSE(o < p);
		BKSGE_OPTIONAL_CXX14_CONSTEXPR_EXPECT_FALSE(o > p);
		BKSGE_OPTIONAL_CXX14_CONSTEXPR_EXPECT_TRUE (o <= p);
		BKSGE_OPTIONAL_CXX14_CONSTEXPR_EXPECT_TRUE (o >= p);
	}

	{
		BKSGE_OPTIONAL_CONSTEXPR O o{ value_type{ 42, 0.5f } };
		BKSGE_OPTIONAL_CONSTEXPR O p;
		BKSGE_OPTIONAL_CXX14_CONSTEXPR_EXPECT_FALSE(o == p);
		BKSGE_OPTIONAL_CXX14_CONSTEXPR_EXPECT_TRUE (o != p);
		BKSGE_OPTIONAL_CXX14_CONSTEXPR_EXPECT_FALSE(o < p);
		BKSGE_OPTIONAL_CXX14_CONSTEXPR_EXPECT_TRUE (o > p);
		BKSGE_OPTIONAL_CXX14_CONSTEXPR_EXPECT_FALSE(o <= p);
		BKSGE_OPTIONAL_CXX14_CONSTEXPR_EXPECT_TRUE (o >= p);
	}

	{
		BKSGE_OPTIONAL_CONSTEXPR O o;
		BKSGE_OPTIONAL_CONSTEXPR O p{ value_type{ 42, 0.5f } };
		BKSGE_OPTIONAL_CXX14_CONSTEXPR_EXPECT_FALSE(o == p);
		BKSGE_OPTIONAL_CXX14_CONSTEXPR_EXPECT_TRUE (o != p);
		BKSGE_OPTIONAL_CXX14_CONSTEXPR_EXPECT_TRUE (o < p);
		BKSGE_OPTIONAL_CXX14_CONSTEXPR_EXPECT_FALSE(o > p);
		BKSGE_OPTIONAL_CXX14_CONSTEXPR_EXPECT_TRUE (o <= p);
		BKSGE_OPTIONAL_CXX14_CONSTEXPR_EXPECT_FALSE(o >= p);
	}

	{
		BKSGE_OPTIONAL_CONSTEXPR O o{ value_type{ 11, 0.5f } };
		BKSGE_OPTIONAL_CONSTEXPR O p{ value_type{ 42, 0.5f } };
		BKSGE_OPTIONAL_CXX14_CONSTEXPR_EXPECT_FALSE(o == p);
		BKSGE_OPTIONAL_CXX14_CONSTEXPR_EXPECT_TRUE (o != p);
		BKSGE_OPTIONAL_CXX14_CONSTEXPR_EXPECT_TRUE (o < p);
		BKSGE_OPTIONAL_CXX14_CONSTEXPR_EXPECT_FALSE(o > p);
		BKSGE_OPTIONAL_CXX14_CONSTEXPR_EXPECT_TRUE (o <= p);
		BKSGE_OPTIONAL_CXX14_CONSTEXPR_EXPECT_FALSE(o >= p);
	}

	{
		BKSGE_OPTIONAL_CONSTEXPR O o{ value_type{ 42, 0.5f } };
		BKSGE_OPTIONAL_CONSTEXPR O p{ value_type{ 11, 0.5f } };
		BKSGE_OPTIONAL_CXX14_CONSTEXPR_EXPECT_FALSE(o == p);
		BKSGE_OPTIONAL_CXX14_CONSTEXPR_EXPECT_TRUE (o != p);
		BKSGE_OPTIONAL_CXX14_CONSTEXPR_EXPECT_FALSE(o < p);
		BKSGE_OPTIONAL_CXX14_CONSTEXPR_EXPECT_TRUE (o > p);
		BKSGE_OPTIONAL_CXX14_CONSTEXPR_EXPECT_FALSE(o <= p);
		BKSGE_OPTIONAL_CXX14_CONSTEXPR_EXPECT_TRUE (o >= p);
	}

	{
		BKSGE_OPTIONAL_CONSTEXPR O o{ value_type{ 42, 0.5f } };
		BKSGE_OPTIONAL_CONSTEXPR O p{ value_type{ 42, 1.5f } };
		BKSGE_OPTIONAL_CXX14_CONSTEXPR_EXPECT_FALSE(o == p);
		BKSGE_OPTIONAL_CXX14_CONSTEXPR_EXPECT_TRUE (o != p);
		BKSGE_OPTIONAL_CXX14_CONSTEXPR_EXPECT_TRUE (o < p);
		BKSGE_OPTIONAL_CXX14_CONSTEXPR_EXPECT_FALSE(o > p);
		BKSGE_OPTIONAL_CXX14_CONSTEXPR_EXPECT_TRUE (o <= p);
		BKSGE_OPTIONAL_CXX14_CONSTEXPR_EXPECT_FALSE(o >= p);
	}

	{
		BKSGE_OPTIONAL_CONSTEXPR O o{ value_type{ 42, 1.5f } };
		BKSGE_OPTIONAL_CONSTEXPR O p{ value_type{ 42, 0.5f } };
		BKSGE_OPTIONAL_CXX14_CONSTEXPR_EXPECT_FALSE(o == p);
		BKSGE_OPTIONAL_CXX14_CONSTEXPR_EXPECT_TRUE (o != p);
		BKSGE_OPTIONAL_CXX14_CONSTEXPR_EXPECT_FALSE(o < p);
		BKSGE_OPTIONAL_CXX14_CONSTEXPR_EXPECT_TRUE (o > p);
		BKSGE_OPTIONAL_CXX14_CONSTEXPR_EXPECT_FALSE(o <= p);
		BKSGE_OPTIONAL_CXX14_CONSTEXPR_EXPECT_TRUE (o >= p);
	}

	{
		BKSGE_OPTIONAL_CONSTEXPR O o{ value_type{ 42, 1.5f } };
		BKSGE_OPTIONAL_CONSTEXPR O p{ value_type{ 42, 1.5f } };
		BKSGE_OPTIONAL_CXX14_CONSTEXPR_EXPECT_TRUE (o == p);
		BKSGE_OPTIONAL_CXX14_CONSTEXPR_EXPECT_FALSE(o != p);
		BKSGE_OPTIONAL_CXX14_CONSTEXPR_EXPECT_FALSE(o < p);
		BKSGE_OPTIONAL_CXX14_CONSTEXPR_EXPECT_FALSE(o > p);
		BKSGE_OPTIONAL_CXX14_CONSTEXPR_EXPECT_TRUE (o <= p);
		BKSGE_OPTIONAL_CXX14_CONSTEXPR_EXPECT_TRUE (o >= p);
	}

	BKSGE_OPTIONAL_CONSTEXPR value_type const r{ 42, 0.5f };

	{
		BKSGE_OPTIONAL_CONSTEXPR O o;
		BKSGE_OPTIONAL_CXX14_CONSTEXPR_EXPECT_FALSE(o == r);
		BKSGE_OPTIONAL_CXX14_CONSTEXPR_EXPECT_FALSE(r == o);
		BKSGE_OPTIONAL_CXX14_CONSTEXPR_EXPECT_TRUE (o != r);
		BKSGE_OPTIONAL_CXX14_CONSTEXPR_EXPECT_TRUE (r != o);
		BKSGE_OPTIONAL_CXX14_CONSTEXPR_EXPECT_TRUE (o < r);
		BKSGE_OPTIONAL_CXX14_CONSTEXPR_EXPECT_FALSE(r < o);
		BKSGE_OPTIONAL_CXX14_CONSTEXPR_EXPECT_FALSE(o > r);
		BKSGE_OPTIONAL_CXX14_CONSTEXPR_EXPECT_TRUE (r > o);
		BKSGE_OPTIONAL_CXX14_CONSTEXPR_EXPECT_TRUE (o <= r);
		BKSGE_OPTIONAL_CXX14_CONSTEXPR_EXPECT_FALSE(r <= o);
		BKSGE_OPTIONAL_CXX14_CONSTEXPR_EXPECT_FALSE(o >= r);
		BKSGE_OPTIONAL_CXX14_CONSTEXPR_EXPECT_TRUE (r >= o);
	}

	{
		BKSGE_OPTIONAL_CONSTEXPR O o{ value_type{ 11, 0.5f } };
		BKSGE_OPTIONAL_CXX14_CONSTEXPR_EXPECT_FALSE(o == r);
		BKSGE_OPTIONAL_CXX14_CONSTEXPR_EXPECT_FALSE(r == o);
		BKSGE_OPTIONAL_CXX14_CONSTEXPR_EXPECT_TRUE (o != r);
		BKSGE_OPTIONAL_CXX14_CONSTEXPR_EXPECT_TRUE (r != o);
		BKSGE_OPTIONAL_CXX14_CONSTEXPR_EXPECT_TRUE (o < r);
		BKSGE_OPTIONAL_CXX14_CONSTEXPR_EXPECT_FALSE(r < o);
		BKSGE_OPTIONAL_CXX14_CONSTEXPR_EXPECT_FALSE(o > r);
		BKSGE_OPTIONAL_CXX14_CONSTEXPR_EXPECT_TRUE (r > o);
		BKSGE_OPTIONAL_CXX14_CONSTEXPR_EXPECT_TRUE (o <= r);
		BKSGE_OPTIONAL_CXX14_CONSTEXPR_EXPECT_FALSE(r <= o);
		BKSGE_OPTIONAL_CXX14_CONSTEXPR_EXPECT_FALSE(o >= r);
		BKSGE_OPTIONAL_CXX14_CONSTEXPR_EXPECT_TRUE (r >= o);
	}

	{
		BKSGE_OPTIONAL_CONSTEXPR O o{ value_type{ 42, 0.5f } };
		BKSGE_OPTIONAL_CXX14_CONSTEXPR_EXPECT_TRUE (o == r);
		BKSGE_OPTIONAL_CXX14_CONSTEXPR_EXPECT_TRUE (r == o);
		BKSGE_OPTIONAL_CXX14_CONSTEXPR_EXPECT_FALSE(o != r);
		BKSGE_OPTIONAL_CXX14_CONSTEXPR_EXPECT_FALSE(r != o);
		BKSGE_OPTIONAL_CXX14_CONSTEXPR_EXPECT_FALSE(o < r);
		BKSGE_OPTIONAL_CXX14_CONSTEXPR_EXPECT_FALSE(r < o);
		BKSGE_OPTIONAL_CXX14_CONSTEXPR_EXPECT_FALSE(o > r);
		BKSGE_OPTIONAL_CXX14_CONSTEXPR_EXPECT_FALSE(r > o);
		BKSGE_OPTIONAL_CXX14_CONSTEXPR_EXPECT_TRUE (o <= r);
		BKSGE_OPTIONAL_CXX14_CONSTEXPR_EXPECT_TRUE (r <= o);
		BKSGE_OPTIONAL_CXX14_CONSTEXPR_EXPECT_TRUE (o >= r);
		BKSGE_OPTIONAL_CXX14_CONSTEXPR_EXPECT_TRUE (r >= o);
	}

	// bksge::nullopt

	{
		BKSGE_OPTIONAL_CONSTEXPR O o;
		BKSGE_OPTIONAL_CXX14_CONSTEXPR_EXPECT_TRUE (o == bksge::nullopt);
		BKSGE_OPTIONAL_CXX14_CONSTEXPR_EXPECT_TRUE (bksge::nullopt == o);
		BKSGE_OPTIONAL_CXX14_CONSTEXPR_EXPECT_FALSE(o != bksge::nullopt);
		BKSGE_OPTIONAL_CXX14_CONSTEXPR_EXPECT_FALSE(bksge::nullopt != o);
		BKSGE_OPTIONAL_CXX14_CONSTEXPR_EXPECT_FALSE(o < bksge::nullopt);
		BKSGE_OPTIONAL_CXX14_CONSTEXPR_EXPECT_FALSE(bksge::nullopt < o);
		BKSGE_OPTIONAL_CXX14_CONSTEXPR_EXPECT_FALSE(o > bksge::nullopt);
		BKSGE_OPTIONAL_CXX14_CONSTEXPR_EXPECT_FALSE(bksge::nullopt > o);
		BKSGE_OPTIONAL_CXX14_CONSTEXPR_EXPECT_TRUE (o <= bksge::nullopt);
		BKSGE_OPTIONAL_CXX14_CONSTEXPR_EXPECT_TRUE (bksge::nullopt <= o);
		BKSGE_OPTIONAL_CXX14_CONSTEXPR_EXPECT_TRUE (o >= bksge::nullopt);
		BKSGE_OPTIONAL_CXX14_CONSTEXPR_EXPECT_TRUE (bksge::nullopt >= o);
	}

	{
		BKSGE_OPTIONAL_CONSTEXPR O o{ bksge::in_place };
		BKSGE_OPTIONAL_CXX14_CONSTEXPR_EXPECT_FALSE(o == bksge::nullopt);
		BKSGE_OPTIONAL_CXX14_CONSTEXPR_EXPECT_FALSE(bksge::nullopt == o);
		BKSGE_OPTIONAL_CXX14_CONSTEXPR_EXPECT_TRUE (o != bksge::nullopt);
		BKSGE_OPTIONAL_CXX14_CONSTEXPR_EXPECT_TRUE (bksge::nullopt != o);
		BKSGE_OPTIONAL_CXX14_CONSTEXPR_EXPECT_FALSE(o < bksge::nullopt);
		BKSGE_OPTIONAL_CXX14_CONSTEXPR_EXPECT_TRUE (bksge::nullopt < o);
		BKSGE_OPTIONAL_CXX14_CONSTEXPR_EXPECT_TRUE (o > bksge::nullopt);
		BKSGE_OPTIONAL_CXX14_CONSTEXPR_EXPECT_FALSE(bksge::nullopt > o);
		BKSGE_OPTIONAL_CXX14_CONSTEXPR_EXPECT_FALSE(o <= bksge::nullopt);
		BKSGE_OPTIONAL_CXX14_CONSTEXPR_EXPECT_TRUE (bksge::nullopt <= o);
		BKSGE_OPTIONAL_CXX14_CONSTEXPR_EXPECT_TRUE (o >= bksge::nullopt);
		BKSGE_OPTIONAL_CXX14_CONSTEXPR_EXPECT_FALSE(bksge::nullopt >= o);
	}
}

}	// namespace compare_test

}	// namespace bksge_optional_test

#undef BKSGE_OPTIONAL_CONSTEXPR
#undef BKSGE_OPTIONAL_CXX14_CONSTEXPR_EXPECT_TRUE
#undef BKSGE_OPTIONAL_CXX14_CONSTEXPR_EXPECT_FALSE
