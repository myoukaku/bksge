/**
 *	@file	unit_test_fnd_compare_partial_order.cpp
 *
 *	@brief	partial_order のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/compare/partial_order.hpp>
#include <bksge/fnd/compare/partial_ordering.hpp>
#include <bksge/fnd/compare/is_eq.hpp>
#include <bksge/fnd/compare/concepts/three_way_comparable.hpp>
#include <bksge/fnd/limits.hpp>
#include <bksge/fnd/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

#if defined(BKSGE_HAS_STD_COMPARE) && defined(BKSGE_HAS_CXX20_THREE_WAY_COMPARISON)

namespace bksge_compare_test
{

namespace partial_order_test
{

constexpr bksge::partial_ordering
different_cv_quals(int i, const int j)
{
	return bksge::partial_order(i, j);
}

struct X
{
	int i;

	friend constexpr bksge::partial_ordering
	operator<=>(X l, X r)
	{
		if (l.i < 0 && r.i < 0)
		{
			return bksge::partial_ordering::equivalent;
		}
		return r.i <=> l.i;
	}

	friend constexpr bool operator==(X l, X r)
	{
		return bksge::is_eq(l <=> r);
	}
};

struct Y
{
	int i;

	friend constexpr bksge::partial_ordering
	partial_order(Y lhs, Y rhs)
	{
		return lhs.i <=> rhs.i;
	}
};

struct Z
{
	int i;

	friend constexpr bksge::weak_ordering
	weak_order(Z lhs, Z rhs)
	{
		return lhs.i <=> rhs.i;
	}
};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline BKSGE_CXX14_CONSTEXPR bool test01()
{
	using bksge::partial_order;
	using bksge::partial_ordering;

	VERIFY(partial_order(1, 2) == partial_ordering::less);
	VERIFY(partial_order(1, 1) == partial_ordering::equivalent);
	VERIFY(partial_order(2, 1) == partial_ordering::greater);
	static_assert(noexcept(partial_order(1, 1)), "");

	VERIFY(different_cv_quals(  42,   999) == partial_ordering::less);
	VERIFY(different_cv_quals(-999,  -999) == partial_ordering::equivalent);
	VERIFY(different_cv_quals(-999, -1000) == partial_ordering::greater);

	static_assert(bksge::three_way_comparable<X>, "");

	X x1{ 1};
	X x2{-1};
	X x3{ 2};
	X x4{-2};
	VERIFY(partial_order(x1, x1) == partial_ordering::equivalent);
	VERIFY(partial_order(x2, x4) == partial_ordering::equivalent);
	VERIFY(partial_order(x1, x3) == partial_ordering::greater);
#if !defined(_MSC_VER)
	static_assert(!noexcept(partial_order(X{1}, X{2})), "");
#endif

	Y y1{ 1};
	Y y2{-1};
	Y y3{ 2};
	Y y4{-2};
	VERIFY(partial_order(y1, y1) == partial_ordering::equivalent);
	VERIFY(partial_order(y1, y2) == partial_ordering::greater);
	VERIFY(partial_order(y1, y3) == partial_ordering::less);
	VERIFY(partial_order(y1, y4) == partial_ordering::greater);

	Z z1{ 1};
	Z z2{-1};
	Z z3{ 2};
	Z z4{-2};
	VERIFY(partial_order(z1, z1) == partial_ordering::equivalent);
	VERIFY(partial_order(z1, z2) == partial_ordering::greater);
	VERIFY(partial_order(z1, z3) == partial_ordering::less);
	VERIFY(partial_order(z1, z4) == partial_ordering::greater);

	VERIFY(partial_order( 0.0,  0.0) == partial_ordering::equivalent);
	VERIFY(partial_order(-0.0, -0.0) == partial_ordering::equivalent);
	VERIFY(partial_order(-0.0,  0.0) == partial_ordering::equivalent);
	VERIFY(partial_order( 0.0, -0.0) == partial_ordering::equivalent);
	static_assert(noexcept(partial_order(0.0, 1.0)), "");
	VERIFY(partial_order(0.0, 1.0) == std::partial_ordering::less);

	double min = bksge::numeric_limits<double>::lowest();
	double max = bksge::numeric_limits<double>::max();
	//double nan = bksge::numeric_limits<double>::quiet_NaN();
	double inf = bksge::numeric_limits<double>::infinity();
	double denorm = bksge::numeric_limits<double>::denorm_min();
	double smallest = bksge::numeric_limits<double>::min();
	double epsilon = bksge::numeric_limits<double>::epsilon();

	VERIFY(partial_order(denorm, smallest) == partial_ordering::less);
	VERIFY(partial_order(denorm, 0.0) == partial_ordering::greater);
	//VERIFY(partial_order(0.0, nan) == partial_ordering::unordered);
	//VERIFY(partial_order(nan, nan) == partial_ordering::unordered);
	//VERIFY(partial_order(nan, 0.0) == partial_ordering::unordered);
	//VERIFY(partial_order(-nan, 0.0) == partial_ordering::unordered);
	//VERIFY(partial_order(-nan, min) == partial_ordering::unordered);
	VERIFY(partial_order(-inf, min) == partial_ordering::less);
	//VERIFY(partial_order(-nan, -inf) == partial_ordering::unordered);
	//VERIFY(partial_order(-inf, -nan) == partial_ordering::unordered);
	VERIFY(partial_order(max, inf) == partial_ordering::less);
	VERIFY(partial_order(inf, max) == partial_ordering::greater);
	//VERIFY(partial_order(inf, nan) == partial_ordering::unordered);
	VERIFY(partial_order(1.0, 1.0+epsilon) == partial_ordering::less);

	return true;
}

#undef VERIFY

GTEST_TEST(CompareTest, PartialOrderTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
}

}	// namespace partial_order_test

}	// namespace bksge_compare_test

#endif
