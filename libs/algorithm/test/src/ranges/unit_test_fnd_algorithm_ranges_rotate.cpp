/**
 *	@file	unit_test_fnd_algorithm_ranges_rotate.cpp
 *
 *	@brief	ranges::rotate のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/algorithm/ranges/rotate.hpp>
#include <bksge/fnd/algorithm/ranges/equal.hpp>
#include <bksge/fnd/iterator/ranges/next.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace bksge_algorithm_test
{

namespace ranges_rotate_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <template <typename> class iter_wrapper>
inline BKSGE_CXX14_CONSTEXPR bool test01()
{
	namespace ranges = bksge::ranges;
	{
		int x[] = { 1, 2, 3, 4, 5, 6, 7 };
		test_range<int, iter_wrapper> rx(x);
		auto res = ranges::rotate(rx.begin(), rx.begin(), rx.end());
		VERIFY(res.begin() == rx.end());
		VERIFY(res.end()   == rx.end());
		int const y[] = { 1, 2, 3, 4, 5, 6, 7 };
		VERIFY(ranges::equal(x, y));
	}
	{
		int x[] = { 1, 2, 3, 4, 5, 6, 7 };
		test_range<int, iter_wrapper> rx(x);
		auto res = ranges::rotate(rx.begin(), ranges::next(rx.begin(), 1), rx.end());
		VERIFY(res.begin() == ranges::next(rx.begin(), 6));
		VERIFY(res.end()   == rx.end());
		int const y[] = { 2, 3, 4, 5, 6, 7, 1 };
		VERIFY(ranges::equal(x, y));
	}
	{
		int x[] = { 1, 2, 3, 4, 5, 6, 7 };
		test_range<int, iter_wrapper> rx(x);
		auto res = ranges::rotate(rx.begin(), ranges::next(rx.begin(), 3), rx.end());
		VERIFY(res.begin() == ranges::next(rx.begin(), 4));
		VERIFY(res.end()   == rx.end());
		int const y[] = { 4, 5, 6, 7, 1, 2, 3 };
		VERIFY(ranges::equal(x, y));
	}
	{
		int x[] = { 1, 2, 3, 4, 5, 6, 7 };
		test_range<int, iter_wrapper> rx(x);
		auto res = ranges::rotate(rx.begin(), ranges::next(rx.begin(), 5), rx.end());
		VERIFY(res.begin() == ranges::next(rx.begin(), 2));
		VERIFY(res.end()   == rx.end());
		int const y[] = { 6, 7, 1, 2, 3, 4, 5 };
		VERIFY(ranges::equal(x, y));
	}
	{
		int x[] = { 1, 2, 3, 4, 5, 6, 7 };
		test_range<int, iter_wrapper> rx(x);
		auto res = ranges::rotate(rx.begin(), ranges::next(rx.begin(), 6), rx.end());
		VERIFY(res.begin() == ranges::next(rx.begin(), 1));
		VERIFY(res.end()   == rx.end());
		int const y[] = { 7, 1, 2, 3, 4, 5, 6 };
		VERIFY(ranges::equal(x, y));
	}
	{
		int x[] = { 1, 2, 3, 4, 5, 6, 7 };
		test_range<int, iter_wrapper> rx(x);
		auto res = ranges::rotate(rx.begin(), ranges::next(rx.begin(), 7), rx.end());
		VERIFY(res.begin() == rx.begin());
		VERIFY(res.end()   == rx.end());
		int const y[] = { 1, 2, 3, 4, 5, 6, 7 };
		VERIFY(ranges::equal(x, y));
	}
	{
		int x[] = { 1, 2, 3, 4, 5, 6 };
		test_range<int, iter_wrapper> rx(x);
		auto res = ranges::rotate(rx, ranges::next(rx.begin(), 2));
		VERIFY(res.begin() == ranges::next(rx.begin(), 4));
		VERIFY(res.end()   == rx.end());
		int const y[] = { 3, 4, 5, 6, 1, 2 };
		VERIFY(ranges::equal(x, y));
	}
	{
		int x[] = { 1, 2, 3, 4, 5, 6 };
		test_range<int, iter_wrapper> rx(x);
		auto res = ranges::rotate(rx, ranges::next(rx.begin(), 3));
		VERIFY(res.begin() == ranges::next(rx.begin(), 3));
		VERIFY(res.end()   == rx.end());
		int const y[] = { 4, 5, 6, 1, 2, 3 };
		VERIFY(ranges::equal(x, y));
	}
	{
		int x[] = { 1, 2, 3, 4, 5, 6 };
		test_range<int, iter_wrapper> rx(x);
		auto res = ranges::rotate(rx, ranges::next(rx.begin(), 4));
		VERIFY(res.begin() == ranges::next(rx.begin(), 2));
		VERIFY(res.end()   == rx.end());
		int const y[] = { 5, 6, 1, 2, 3, 4 };
		VERIFY(ranges::equal(x, y));
	}
	return true;
}

#undef VERIFY

GTEST_TEST(AlgorithmTest, RangesRotateTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test01<forward_iterator_wrapper>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test01<bidirectional_iterator_wrapper>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test01<random_access_iterator_wrapper>());
}

}	// namespace ranges_rotate_test

}	// namespace bksge_algorithm_test
