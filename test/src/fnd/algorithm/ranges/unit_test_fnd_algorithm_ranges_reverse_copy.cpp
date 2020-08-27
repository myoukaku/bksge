/**
 *	@file	unit_test_fnd_algorithm_ranges_reverse_copy.cpp
 *
 *	@brief	ranges::reverse_copy のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/algorithm/ranges/reverse_copy.hpp>
#include <bksge/fnd/algorithm/ranges/equal.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace bksge_algorithm_test
{

namespace ranges_reverse_copy_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <template <typename> class iter_wrapper>
inline BKSGE_CXX14_CONSTEXPR bool test01()
{
	namespace ranges = bksge::ranges;
	{
		int const x[] = { 1, 2, 3, 4 };
		test_range<int const, iter_wrapper> rx(x);
		int w[4] = {};
		auto res = ranges::reverse_copy(rx, w);
		VERIFY(res.in  == rx.end());
		VERIFY(res.out == w+4);
		const int y[] = { 4, 3, 2, 1 };
		VERIFY(ranges::equal(w, y));
	}
	{
		int const x[] = { 1, 2, 3, 4, 5 };
		test_range<int const, iter_wrapper> rx(x);
		int w[5] = {};
		auto res = ranges::reverse_copy(rx, w);
		VERIFY(res.in  == rx.end());
		VERIFY(res.out == w+5);
		const int y[] = { 5, 4, 3, 2, 1 };
		VERIFY(ranges::equal(w, y));
	}
	return true;
}

#undef VERIFY

GTEST_TEST(AlgorithmTest, RangesReverseCopyTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test01<bidirectional_iterator_wrapper>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test01<random_access_iterator_wrapper>());
}

}	// namespace ranges_reverse_copy_test

}	// namespace bksge_algorithm_test
