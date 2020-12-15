/**
 *	@file	unit_test_fnd_utility_pair_swap.cpp
 *
 *	@brief	swap のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/utility/pair.hpp>
#include <bksge/fnd/type_traits/is_swappable.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace bksge_pair_test
{

namespace swap_test
{

struct C {};
void swap(C&, C&) = delete;
static_assert(!bksge::is_swappable<bksge::pair<int, C>>::value, "");
static_assert(!bksge::is_swappable<bksge::pair<C, int>>::value, "");

struct D { D(D&&) = delete; };
static_assert(!bksge::is_swappable<bksge::pair<int, D>>::value, "");
static_assert(!bksge::is_swappable<bksge::pair<D, int>>::value, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline BKSGE_CXX14_CONSTEXPR bool test()
{
	bksge::pair<int, float> p1(1, 0.5f);
	bksge::pair<int, float> p2(2, 1.5f);

	p1.swap(p2);
	VERIFY(p1.first  == 2);
	VERIFY(p1.second == 1.5f);
	VERIFY(p2.first  == 1);
	VERIFY(p2.second == 0.5f);

	swap(p1, p2);
	VERIFY(p1.first  == 1);
	VERIFY(p1.second == 0.5f);
	VERIFY(p2.first  == 2);
	VERIFY(p2.second == 1.5f);

	return true;
}

#undef VERIFY

GTEST_TEST(PairTest, SwapTest)
{
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((test()));
}

}	// namespace swap_test

}	// namespace bksge_pair_test
