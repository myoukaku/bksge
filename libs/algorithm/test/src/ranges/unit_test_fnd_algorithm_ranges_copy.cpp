/**
 *	@file	unit_test_fnd_algorithm_ranges_copy.cpp
 *
 *	@brief	ranges::copy のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/algorithm/ranges/copy.hpp>
#include <bksge/fnd/algorithm/ranges/equal.hpp>
#include <bksge/fnd/forward_list.hpp>
#include <bksge/fnd/list.hpp>
#include <bksge/fnd/vector.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace bksge_algorithm_test
{

namespace ranges_copy_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline BKSGE_CXX14_CONSTEXPR bool test01()
{
	namespace ranges = bksge::ranges;
	{
		int const x[7] = { 1, 2, 3, 4, 5, 6, 7 };
		int w[7] = {};
		auto res = ranges::copy(x, x+7, w);
		VERIFY(res.in  == x+7);
		VERIFY(res.out == w+7);
		int const y[7] = { 1, 2, 3, 4, 5, 6, 7 };
		VERIFY(ranges::equal(w, y));
	}
	{
		char const x[5] = { 1, 2, 3, 4, 5 };
		int w[5] = {};
		auto res = ranges::copy(x, x+5, w);
		VERIFY(res.in  == x+5);
		VERIFY(res.out == w+5);
		int const y[5] = { 1, 2, 3, 4, 5 };
		VERIFY(ranges::equal(w, y));
	}
	return true;
}

inline BKSGE_CXX14_CONSTEXPR bool test02()
{
	namespace ranges = bksge::ranges;
	{
		int const x[] = { 1, 2, 3 };
		int w[3] = {};
		test_range<int const, input_iterator_wrapper> rx(x);
		test_range<int, output_iterator_wrapper> rw(w);
		auto res = ranges::copy(rx, rw.begin());
		VERIFY(res.in  == rx.end());
		VERIFY(res.out == rw.end());
		int const y[] = { 1, 2, 3 };
		VERIFY(ranges::equal(w, y));
	}
	{
		char const x[] = { 1, 2, 3, 4 };
		int w[4] = {};
		test_range<char const, input_iterator_wrapper> rx(x);
		test_range<int, output_iterator_wrapper> rw(w);
		auto res = ranges::copy(rx, rw.begin());
		VERIFY(res.in  == rx.end());
		VERIFY(res.out == rw.end());
		int const y[] = { 1, 2, 3, 4 };
		VERIFY(ranges::equal(w, y));
	}
	return true;
}

inline bool test03()
{
	namespace ranges = bksge::ranges;
	{
		bksge::vector<int> x = { 1, 2, 3, 4, 5, 6, 7 };
		bksge::vector<int> w(x.size());
		auto res = ranges::copy(x.rbegin(), x.rend(), w.begin());
		VERIFY(res.in  == x.rend());
		VERIFY(res.out == w.end());
		int const y[7] = { 7, 6, 5, 4, 3, 2, 1 };
		VERIFY(ranges::equal(w, y));
	}
	{
		bksge::list<int> x = { 1, 2, 3, 4, 5, 6, 7 };
		bksge::list<int> w(x.size());
		auto res = ranges::copy(x.rbegin(), x.rend(), w.rbegin());
		VERIFY(res.in  == x.rend());
		VERIFY(res.out == w.rend());
		int const y[7] = { 1, 2, 3, 4, 5, 6, 7 };
		VERIFY(ranges::equal(w, y));
	}
	return true;
}

inline bool test04()
{
	namespace ranges = bksge::ranges;
	{
		bksge::vector<int> x = { 1, 2, 3, 4, 5, 6 };
		bksge::vector<int> w(x.size());
		auto res = ranges::copy(x, w.rbegin());
		VERIFY(res.in  == x.end());
		VERIFY(res.out == w.rend());
		int const y[6] = { 6, 5, 4, 3, 2, 1 };
		VERIFY(ranges::equal(w, y));
	}
	{
		bksge::forward_list<int> x = { 1, 2, 3, 4, 5 };
		bksge::forward_list<int> w(5);
		auto res = ranges::copy(x, w.begin());
		VERIFY(res.in  == x.end());
		VERIFY(res.out == w.end());
		int const y[5] = { 1, 2, 3, 4, 5 };
		VERIFY(ranges::equal(w, y));
	}
	return true;
}

#undef VERIFY

GTEST_TEST(AlgorithmTest, RangesCopyTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
	EXPECT_TRUE(test03());
	EXPECT_TRUE(test04());
}

}	// namespace ranges_copy_test

}	// namespace bksge_algorithm_test
