/**
 *	@file	unit_test_fnd_utility_pair_comparison.cpp
 *
 *	@brief	比較演算子のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/utility/pair.hpp>
#include <bksge/fnd/compare/is_eq.hpp>
#include <bksge/fnd/compare/is_lt.hpp>
#include <bksge/fnd/compare/is_gt.hpp>
#include <bksge/fnd/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace bksge_pair_test
{

namespace comparison_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline BKSGE_CXX14_CONSTEXPR bool test()
{
	bksge::pair<int, int> p1{1, 2};
	bksge::pair<int, int> p2{1, 2};
	bksge::pair<int, int> p3{0, 2};
	bksge::pair<int, int> p4{2, 1};
	bksge::pair<int, int> p5{1, 1};
	bksge::pair<int, int> p6{1, 3};

	VERIFY( (p1 == p1));
	VERIFY( (p1 == p2));
	VERIFY(!(p1 == p3));
	VERIFY(!(p1 == p4));
	VERIFY(!(p1 == p5));
	VERIFY(!(p1 == p6));

	VERIFY(!(p1 != p1));
	VERIFY(!(p1 != p2));
	VERIFY( (p1 != p3));
	VERIFY( (p1 != p4));
	VERIFY( (p1 != p5));
	VERIFY( (p1 != p6));

	VERIFY(!(p1 < p1));
	VERIFY(!(p1 < p2));
	VERIFY(!(p1 < p3));
	VERIFY( (p1 < p4));
	VERIFY(!(p1 < p5));
	VERIFY( (p1 < p6));

	VERIFY(!(p1 > p1));
	VERIFY(!(p1 > p2));
	VERIFY( (p1 > p3));
	VERIFY(!(p1 > p4));
	VERIFY( (p1 > p5));
	VERIFY(!(p1 > p6));

	VERIFY( (p1 <= p1));
	VERIFY( (p1 <= p2));
	VERIFY(!(p1 <= p3));
	VERIFY( (p1 <= p4));
	VERIFY(!(p1 <= p5));
	VERIFY( (p1 <= p6));

	VERIFY( (p1 >= p1));
	VERIFY( (p1 >= p2));
	VERIFY( (p1 >= p3));
	VERIFY(!(p1 >= p4));
	VERIFY( (p1 >= p5));
	VERIFY(!(p1 >= p6));

#if defined(BKSGE_HAS_CXX20_THREE_WAY_COMPARISON)
	VERIFY(bksge::is_eq(p1 <=> p1));
	VERIFY(bksge::is_eq(p1 <=> p2));
	VERIFY(bksge::is_gt(p1 <=> p3));
	VERIFY(bksge::is_lt(p1 <=> p4));
	VERIFY(bksge::is_gt(p1 <=> p5));
	VERIFY(bksge::is_lt(p1 <=> p6));
#endif

	return true;
}

#undef VERIFY

GTEST_TEST(PairTest, ComparisonTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test()));
}

}	// namespace comparison_test

}	// namespace bksge_pair_test
