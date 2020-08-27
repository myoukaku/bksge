/**
 *	@file	unit_test_fnd_algorithm_ranges_reverse.cpp
 *
 *	@brief	ranges::reverse のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/algorithm/ranges/reverse.hpp>
#include <bksge/fnd/algorithm/ranges/equal.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace bksge_algorithm_test
{

namespace ranges_reverse_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <template <typename> class iter_wrapper>
inline BKSGE_CXX14_CONSTEXPR bool test01()
{
	namespace ranges = bksge::ranges;
	{
		int x[] = { 1, 2, 3, 4 };
		test_range<int, iter_wrapper> rx(x);
		auto res = ranges::reverse(rx);
		VERIFY(res == rx.end());
		const int y[] ={ 4, 3, 2, 1 };
		VERIFY(ranges::equal(x, y));
	}
	{
		int x[] = { 1, 2, 3, 4, 5 };
		test_range<int, iter_wrapper> rx(x);
		auto res = ranges::reverse(rx);
		VERIFY(res == rx.end());
		const int y[] ={ 5, 4, 3, 2, 1 };
		VERIFY(ranges::equal(x, y));
	}
	return true;
}

inline BKSGE_CXX14_CONSTEXPR bool test02()
{
	namespace ranges = bksge::ranges;
	{
		int x[] = { 1, 2, 3, 4 };
		auto res = ranges::reverse(x, x+2);
		VERIFY(res == x+2);
		const int y[] = { 2, 1, 3, 4 };
		VERIFY(ranges::equal(x, y));
	}
	return true;
}

#undef VERIFY

GTEST_TEST(AlgorithmTest, RangesReverseTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test01<bidirectional_iterator_wrapper>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test01<random_access_iterator_wrapper>());
#if defined(_MSC_VER)
	// Avoid MSVC internal compiler error
	EXPECT_TRUE(test02());
#else
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
#endif
}

}	// namespace ranges_reverse_test

}	// namespace bksge_algorithm_test
