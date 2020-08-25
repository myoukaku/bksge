/**
 *	@file	unit_test_fnd_algorithm_ranges_swap_ranges.cpp
 *
 *	@brief	ranges::swap_ranges のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/algorithm/ranges/swap_ranges.hpp>
#include <bksge/fnd/algorithm/ranges/equal.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace bksge_algorithm_test
{

namespace ranges_swap_ranges_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline BKSGE_CXX14_CONSTEXPR bool test01()
{
	namespace ranges = bksge::ranges;
	{
		int x[3] = { 1, 2, 3 };
		int y[4] = { 2, 4, 6, 0 };
		int z[3] = { 1, 2, 3 };
		int w[3] = { 2, 4, 6 };
		test_range<int, input_iterator_wrapper> cx(x);
		test_range<int, input_iterator_wrapper> cy(y);
		auto res = ranges::swap_ranges(cx, cy);
		VERIFY(res.in1.m_ptr == x+3 && res.in2.m_ptr == y+3);
		VERIFY(ranges::equal(y, y+3, z, z+3));
		VERIFY(y[3] == 0);
		VERIFY(ranges::equal(x, w));
	}
	return true;
}

struct X
{
	int i;

	BKSGE_CXX14_CONSTEXPR X(int a) : i(a) { }

	BKSGE_CXX14_CONSTEXPR X(X const&) = delete;
	BKSGE_CXX14_CONSTEXPR X& operator=(X const&) = delete;

	BKSGE_CXX14_CONSTEXPR X(X&& other)
		: i(other.i)
	{
	}

	BKSGE_CXX14_CONSTEXPR X&
	operator=(X&& other)
	{
		i = other.i;
		return *this;
	}

	friend BKSGE_CXX14_CONSTEXPR bool
	operator==(X const& a, X const& b)
	{
		return a.i == b.i;
	}

	friend BKSGE_CXX14_CONSTEXPR bool
	operator!=(X const& a, X const& b)
	{
		return !(a == b);
	}
};

inline BKSGE_CXX14_CONSTEXPR bool test02()
{
	namespace ranges = bksge::ranges;
	{
		X x[7] = { 1, 2, 3, 4, 5, 6, 7 };
		X y[7] = { 2, 4, 3, 5, 8, 9, 1 };
		X z[7] = { 1, 2, 3, 4, 5, 6, 7 };
		X w[7] = { 2, 4, 3, 5, 8, 9, 1 };
		auto res = ranges::swap_ranges(x, y);
		VERIFY(res.in1 == x+7 && res.in2 == y+7);
		VERIFY(ranges::equal(y, z));
		VERIFY(ranges::equal(x, w));
	}
	return true;
}

#undef VERIFY

GTEST_TEST(AlgorithmTest, RangesSwapRangesTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
#if defined(_MSC_VER)
	// Avoid internal compiler error
	EXPECT_TRUE(test02());
#else
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
#endif
}

}	// namespace ranges_swap_ranges_test

}	// namespace bksge_algorithm_test
