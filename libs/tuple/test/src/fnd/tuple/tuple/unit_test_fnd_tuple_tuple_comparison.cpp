/**
 *	@file	unit_test_fnd_tuple_tuple_comparison.cpp
 *
 *	@brief	tuple の比較演算子のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/tuple/tuple.hpp>
#include <bksge/fnd/compare/is_eq.hpp>
#include <bksge/fnd/compare/is_lt.hpp>
#include <bksge/fnd/compare/is_gt.hpp>
#include <bksge/fnd/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace bksge_tuple_test
{

namespace comparison_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline BKSGE_CXX14_CONSTEXPR bool test()
{
	bksge::tuple<int, int, int> t1(1, 2, 3);
	bksge::tuple<int, int, int> t2(1, 2, 3);
	bksge::tuple<int, int, int> t3(1, 2, 2);
	bksge::tuple<int, int, int> t4(1, 2, 4);
	bksge::tuple<int, int, int> t5(0, 2, 3);
	bksge::tuple<int, int, int> t6(2, 2, 3);

	VERIFY( (t1 == t1));
	VERIFY( (t1 == t2));
	VERIFY(!(t1 == t3));
	VERIFY(!(t1 == t4));
	VERIFY(!(t1 == t5));
	VERIFY(!(t1 == t6));

	VERIFY(!(t1 != t1));
	VERIFY(!(t1 != t2));
	VERIFY( (t1 != t3));
	VERIFY( (t1 != t4));
	VERIFY( (t1 != t5));
	VERIFY( (t1 != t6));

	VERIFY(!(t1 < t1));
	VERIFY(!(t1 < t2));
	VERIFY(!(t1 < t3));
	VERIFY( (t1 < t4));
	VERIFY(!(t1 < t5));
	VERIFY( (t1 < t6));

	VERIFY(!(t1 > t1));
	VERIFY(!(t1 > t2));
	VERIFY( (t1 > t3));
	VERIFY(!(t1 > t4));
	VERIFY( (t1 > t5));
	VERIFY(!(t1 > t6));

	VERIFY( (t1 <= t1));
	VERIFY( (t1 <= t2));
	VERIFY(!(t1 <= t3));
	VERIFY( (t1 <= t4));
	VERIFY(!(t1 <= t5));
	VERIFY( (t1 <= t6));

	VERIFY( (t1 >= t1));
	VERIFY( (t1 >= t2));
	VERIFY( (t1 >= t3));
	VERIFY(!(t1 >= t4));
	VERIFY( (t1 >= t5));
	VERIFY(!(t1 >= t6));

#if defined(BKSGE_HAS_CXX20_THREE_WAY_COMPARISON)
	VERIFY(bksge::is_eq(t1 <=> t1));
	VERIFY(bksge::is_eq(t1 <=> t2));
	VERIFY(bksge::is_gt(t1 <=> t3));
	VERIFY(bksge::is_lt(t1 <=> t4));
	VERIFY(bksge::is_gt(t1 <=> t5));
	VERIFY(bksge::is_lt(t1 <=> t6));
#endif
	return true;
}

#undef VERIFY

GTEST_TEST(TupleTest, ComparisonTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test()));
}

}	// namespace comparison_test

}	// namespace bksge_tuple_test
