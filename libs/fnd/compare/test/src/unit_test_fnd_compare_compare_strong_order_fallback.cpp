/**
 *	@file	unit_test_fnd_compare_compare_strong_order_fallback.cpp
 *
 *	@brief	compare_strong_order_fallback のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/compare/compare_strong_order_fallback.hpp>
#include <bksge/fnd/compare/strong_ordering.hpp>
#include <bksge/fnd/config.hpp>
#include <gtest/gtest.h>
#include <limits>
#include "constexpr_test.hpp"

namespace bksge_compare_test
{

namespace compare_strong_order_fallback_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

struct X
{
	int v = 0;

	constexpr X(int x) : v(x) {}

	friend constexpr bool operator==(const X& lhs, const X& rhs)
	{
		return lhs.v == rhs.v;
	}

	friend constexpr bool operator<(const X& lhs, const X& rhs)
	{
		return lhs.v < rhs.v;
	}
};

inline BKSGE_CXX17_CONSTEXPR bool test01()
{
	using bksge::compare_strong_order_fallback;
	using bksge::strong_ordering;

	int n1 = 1;
	int n2 = 2;
	VERIFY(compare_strong_order_fallback(n1, n1) == strong_ordering::equal);
	VERIFY(compare_strong_order_fallback(n1, n2) == strong_ordering::less);
	VERIFY(compare_strong_order_fallback(n2, n1) == strong_ordering::greater);
	VERIFY(compare_strong_order_fallback(n2, n2) == strong_ordering::equal);
	static_assert(noexcept(compare_strong_order_fallback(1, 1)), "");

	X x1 { 0 };
	X x2 { 1 };
	X x3 {-1 };
	X x4 { std::numeric_limits<int>::max() };
	X x5 { std::numeric_limits<int>::min() };

	VERIFY(compare_strong_order_fallback(x1, x1) == strong_ordering::equal);
	VERIFY(compare_strong_order_fallback(x1, x2) == strong_ordering::less);
	VERIFY(compare_strong_order_fallback(x1, x3) == strong_ordering::greater);
	VERIFY(compare_strong_order_fallback(x1, x4) == strong_ordering::less);
	VERIFY(compare_strong_order_fallback(x1, x5) == strong_ordering::greater);

	VERIFY(compare_strong_order_fallback(x2, x1) == strong_ordering::greater);
	VERIFY(compare_strong_order_fallback(x2, x2) == strong_ordering::equal);
	VERIFY(compare_strong_order_fallback(x2, x3) == strong_ordering::greater);
	VERIFY(compare_strong_order_fallback(x2, x4) == strong_ordering::less);
	VERIFY(compare_strong_order_fallback(x2, x5) == strong_ordering::greater);

	VERIFY(compare_strong_order_fallback(x3, x1) == strong_ordering::less);
	VERIFY(compare_strong_order_fallback(x3, x2) == strong_ordering::less);
	VERIFY(compare_strong_order_fallback(x3, x3) == strong_ordering::equal);
	VERIFY(compare_strong_order_fallback(x3, x4) == strong_ordering::less);
	VERIFY(compare_strong_order_fallback(x3, x5) == strong_ordering::greater);

	VERIFY(compare_strong_order_fallback(x4, x1) == strong_ordering::greater);
	VERIFY(compare_strong_order_fallback(x4, x2) == strong_ordering::greater);
	VERIFY(compare_strong_order_fallback(x4, x3) == strong_ordering::greater);
	VERIFY(compare_strong_order_fallback(x4, x4) == strong_ordering::equal);
	VERIFY(compare_strong_order_fallback(x4, x5) == strong_ordering::greater);

	VERIFY(compare_strong_order_fallback(x5, x1) == strong_ordering::less);
	VERIFY(compare_strong_order_fallback(x5, x2) == strong_ordering::less);
	VERIFY(compare_strong_order_fallback(x5, x3) == strong_ordering::less);
	VERIFY(compare_strong_order_fallback(x5, x4) == strong_ordering::less);
	VERIFY(compare_strong_order_fallback(x5, x5) == strong_ordering::equal);

	return true;
}

#undef VERIFY

GTEST_TEST(CompareTest, CompareStrongOrderFallbackTest)
{
#if defined(BKSGE_COMPARE_USE_INLINE_VARIABLES)
	BKSGE_CONSTEXPR_EXPECT_TRUE(test01());
#else
	EXPECT_TRUE(test01());
#endif
}

}	// namespace compare_strong_order_fallback_test

}	// namespace bksge_compare_test
