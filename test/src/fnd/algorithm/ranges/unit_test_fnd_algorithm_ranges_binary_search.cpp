/**
 *	@file	unit_test_fnd_algorithm_ranges_binary_search.cpp
 *
 *	@brief	ranges::binary_search のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/algorithm/ranges/binary_search.hpp>
#include <bksge/fnd/functional/ranges/greater.hpp>
#include <gtest/gtest.h>
#include <forward_list>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace bksge_algorithm_test
{

namespace ranges_binary_search_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline BKSGE_CXX14_CONSTEXPR bool test01()
{
	namespace ranges = bksge::ranges;
	{
		int const x[] = { 1,2,2,4,4,4 };
		test_range<int const, forward_iterator_wrapper> r(x);
		VERIFY(false == ranges::binary_search(r, 0));
		VERIFY(true  == ranges::binary_search(r, 1));
		VERIFY(true  == ranges::binary_search(r, 2));
		VERIFY(false == ranges::binary_search(r, 3));
		VERIFY(true  == ranges::binary_search(r, 4));
		VERIFY(false == ranges::binary_search(r, 5));
	}
	{
		int const x[] = { 5,5,5,4,1,0 };
		test_range<int const, forward_iterator_wrapper> r(x);
		auto pred = ranges::greater{};
		VERIFY(true  == ranges::binary_search(r, 0, pred));
		VERIFY(true  == ranges::binary_search(r, 1, pred));
		VERIFY(false == ranges::binary_search(r, 2, pred));
		VERIFY(false == ranges::binary_search(r, 3, pred));
		VERIFY(true  == ranges::binary_search(r, 4, pred));
		VERIFY(true  == ranges::binary_search(r, 5, pred));
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
		X const x[] = { {0},{1},{3},{3},{5} };
		VERIFY(true  == ranges::binary_search(x, 0, {}, &X::i));
		VERIFY(true  == ranges::binary_search(x, 1, {}, &X::i));
		VERIFY(false == ranges::binary_search(x, 2, {}, &X::i));
		VERIFY(true  == ranges::binary_search(x, 3, {}, &X::i));
		VERIFY(false == ranges::binary_search(x, 4, {}, &X::i));
		VERIFY(true  == ranges::binary_search(x, 5, {}, &X::i));
		VERIFY(false == ranges::binary_search(x, 6, {}, &X::i));
	}
	{
		X const x[] = { {8},{8},{6},{4},{4} };
		auto pred = ranges::greater{};
		VERIFY(false == ranges::binary_search(x, 9, pred, &X::i));
		VERIFY(true  == ranges::binary_search(x, 8, pred, &X::i));
		VERIFY(false == ranges::binary_search(x, 7, pred, &X::i));
		VERIFY(true  == ranges::binary_search(x, 6, pred, &X::i));
		VERIFY(false == ranges::binary_search(x, 5, pred, &X::i));
		VERIFY(true  == ranges::binary_search(x, 4, pred, &X::i));
		VERIFY(false == ranges::binary_search(x, 3, pred, &X::i));
	}
	{
		std::forward_list<int> x {};
		VERIFY(false == ranges::binary_search(x, 0));
	}
	return true;
}

#undef VERIFY

GTEST_TEST(AlgorithmTest, RangesBinarySearchTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	EXPECT_TRUE(test02());
}

}	// namespace ranges_binary_search_test

}	// namespace bksge_algorithm_test
