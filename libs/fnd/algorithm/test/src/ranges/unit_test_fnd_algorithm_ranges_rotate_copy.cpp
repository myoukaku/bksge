/**
 *	@file	unit_test_fnd_algorithm_ranges_rotate_copy.cpp
 *
 *	@brief	ranges::rotate_copy のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/algorithm/ranges/rotate_copy.hpp>
#include <bksge/fnd/algorithm/ranges/equal.hpp>
#include <bksge/fnd/iterator/ranges/next.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace bksge_algorithm_test
{

namespace ranges_rotate_copy_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <template <typename> class iter_wrapper>
inline BKSGE_CXX14_CONSTEXPR bool test01()
{
	namespace ranges = bksge::ranges;
	{
		int const x[] = { 1, 2, 3, 4, 5, 6, 7 };
		test_range<int const, iter_wrapper> rx(x);
		int w[7] = {};
		auto res = ranges::rotate_copy(rx.begin(), rx.begin(), rx.end(), w);
		VERIFY(res.in  == rx.end());
		VERIFY(res.out == w+7);
		int const y[] = { 1, 2, 3, 4, 5, 6, 7 };
		VERIFY(ranges::equal(w, y));
	}
	{
		int const x[] = { 1, 2, 3, 4, 5, 6, 7 };
		test_range<int const, iter_wrapper> rx(x);
		int w[7] = {};
		auto res = ranges::rotate_copy(rx, ranges::next(rx.begin(), 1), w);
		VERIFY(res.in  == rx.end());
		VERIFY(res.out == w+7);
		int const y[] = { 2, 3, 4, 5, 6, 7, 1 };
		VERIFY(ranges::equal(w, y));
	}
	{
		int const x[] = { 1, 2, 3, 4, 5, 6, 7 };
		test_range<int const, iter_wrapper> rx(x);
		int w[7] = {};
		auto res = ranges::rotate_copy(rx, ranges::next(rx.begin(), 6), w);
		VERIFY(res.in  == rx.end());
		VERIFY(res.out == w+7);
		int const y[] = { 7, 1, 2, 3, 4, 5, 6 };
		VERIFY(ranges::equal(w, y));
	}
	{
		int const x[] = { 1, 2, 3, 4, 5, 6, 7 };
		test_range<int const, iter_wrapper> rx(x);
		int w[7] = {};
		auto res = ranges::rotate_copy(rx, ranges::next(rx.begin(), 7), w);
		VERIFY(res.in  == rx.end());
		VERIFY(res.out == w+7);
		int const y[] = { 1, 2, 3, 4, 5, 6, 7 };
		VERIFY(ranges::equal(w, y));
	}
	return true;
}

#undef VERIFY

GTEST_TEST(AlgorithmTest, RangesRotateCopyTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test01<forward_iterator_wrapper>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test01<bidirectional_iterator_wrapper>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test01<random_access_iterator_wrapper>());
}

}	// namespace ranges_rotate_copy_test

}	// namespace bksge_algorithm_test
