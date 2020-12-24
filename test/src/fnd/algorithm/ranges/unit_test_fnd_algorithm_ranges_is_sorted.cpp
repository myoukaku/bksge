/**
 *	@file	unit_test_fnd_algorithm_ranges_is_sorted.cpp
 *
 *	@brief	ranges::is_sorted のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/algorithm/ranges/is_sorted.hpp>
#include <bksge/fnd/algorithm/ranges/equal.hpp>
#include <bksge/fnd/functional/ranges/greater.hpp>
#include <bksge/fnd/forward_list.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace bksge_algorithm_test
{

namespace ranges_is_sorted_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline BKSGE_CXX14_CONSTEXPR bool test01()
{
	namespace ranges = bksge::ranges;
	{
		int const a[] = {1,2,3,4,5};
		VERIFY(true  == ranges::is_sorted(a));
		VERIFY(false == ranges::is_sorted(a, ranges::greater{}));
	}
	{
		int const a[] = {5,4,3,2,1};
		VERIFY(false == ranges::is_sorted(a));
		VERIFY(true  == ranges::is_sorted(a, ranges::greater{}));
	}
	{
		int const a[] = {1,2,0,3,4};
		VERIFY(false == ranges::is_sorted(a));
		VERIFY(false == ranges::is_sorted(a, ranges::greater{}));
	}
	{
		int const a[] = {1};
		VERIFY(true  == ranges::is_sorted(a));
		VERIFY(true  == ranges::is_sorted(a, ranges::greater{}));
	}
	{
		int const a[] = {1,1};
		VERIFY(true  == ranges::is_sorted(a));
		VERIFY(true  == ranges::is_sorted(a, ranges::greater{}));
	}
	{
		int const a[] = {0,0,0,1,1,2,3,3,3,4,5,5,5,5};
		test_range<int const, forward_iterator_wrapper> r(a);
		VERIFY(true  == ranges::is_sorted(r));
		VERIFY(false == ranges::is_sorted(r, ranges::greater{}));
	}
	{
		int const a[] = {3,1,4,1,5,9,2};
		test_range<int const, forward_iterator_wrapper> r(a);
		VERIFY(false == ranges::is_sorted(r));
		VERIFY(false == ranges::is_sorted(r, ranges::greater{}));
	}
	return true;
}

struct X
{
	int i;
};

inline bool test02()
{
	namespace ranges = bksge::ranges;
	{
		X const a[] = { {1},{1},{3},{5} };
		VERIFY(true  == ranges::is_sorted(a, {}, &X::i));
		VERIFY(false == ranges::is_sorted(a, ranges::greater{}, &X::i));
	}
	{
		bksge::forward_list<int> const a = {};
		VERIFY(true  == ranges::is_sorted(a));
		VERIFY(true  == ranges::is_sorted(a, ranges::greater{}));
	}
	return true;
}

#undef VERIFY

GTEST_TEST(AlgorithmTest, RangesIsSortedTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	EXPECT_TRUE(test02());
}

}	// namespace ranges_is_sorted_test

}	// namespace bksge_algorithm_test
