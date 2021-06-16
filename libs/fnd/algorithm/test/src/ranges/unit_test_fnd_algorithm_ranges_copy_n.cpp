/**
 *	@file	unit_test_fnd_algorithm_ranges_copy_n.cpp
 *
 *	@brief	ranges::copy_n のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/algorithm/ranges/copy_n.hpp>
#include <bksge/fnd/algorithm/ranges/equal.hpp>
#include <bksge/fnd/iterator/ranges/next.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace bksge_algorithm_test
{

namespace ranges_copy_n_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline BKSGE_CXX14_CONSTEXPR bool test01()
{
	namespace ranges = bksge::ranges;
	int const x[7] = { 1, 2, 3, 4, 5, 6, 7 };
	{
		int w[7] = {};
		auto res = ranges::copy_n(x, -1, w);
		VERIFY(res.in  == x+0);
		VERIFY(res.out == w+0);
	}
	{
		int w[7] = {};
		auto res = ranges::copy_n(x, 0, w);
		VERIFY(res.in  == x+0);
		VERIFY(res.out == w+0);
	}
	{
		int w[7] = {};
		auto res = ranges::copy_n(x, 1, w);
		VERIFY(res.in  == x+1);
		VERIFY(res.out == w+1);
		int const y[7] = { 1, 0, 0, 0, 0, 0, 0 };
		VERIFY(ranges::equal(w, y));
	}
	{
		int w[7] = {};
		auto res = ranges::copy_n(x, 7, w);
		VERIFY(res.in  == x+7);
		VERIFY(res.out == w+7);
		int const y[7] = { 1, 2, 3, 4, 5, 6, 7 };
		VERIFY(ranges::equal(w, y));
	}
	return true;
}

template <
	template <typename> class in_wrapper,
	template <typename> class out_wrapper
>
inline BKSGE_CXX14_CONSTEXPR bool test02()
{
	namespace ranges = bksge::ranges;
	int x[7] = { 1, 2, 3, 4, 5, 6, 7 };
	{
		int w[7] = {};
		test_range<int, in_wrapper>  rx(x);
		test_range<int, out_wrapper> rw(w);
		auto res = ranges::copy_n(rx.begin(), -1, rw.begin());
		VERIFY(res.in  == rx.begin());
		VERIFY(res.out.m_ptr == w);
	}
	{
		int w[7] = {};
		test_range<int, in_wrapper>  rx(x);
		test_range<int, out_wrapper> rw(w);
		auto res = ranges::copy_n(rx.begin(), 0, rw.begin());
		VERIFY(res.in  == rx.begin());
		VERIFY(res.out.m_ptr == w);
	}
	{
		int w[7] = {};
		test_range<int, in_wrapper>  rx(x);
		test_range<int, out_wrapper> rw(w);
		auto res = ranges::copy_n(rx.begin(), 1, rw.begin());
		VERIFY(res.in  == ranges::next(rx.begin(), 1));
		VERIFY(res.out.m_ptr == w+1);
		int const y[7] = { 1, 0, 0, 0, 0, 0, 0 };
		VERIFY(ranges::equal(w, y));
	}
	{
		int w[7] = {};
		test_range<int, in_wrapper>  rx(x);
		test_range<int, out_wrapper> rw(w);
		auto res = ranges::copy_n(rx.begin(), 7, rw.begin());
		VERIFY(res.in  == rx.end());
		VERIFY(res.out == rw.end());
		int const y[7] = { 1, 2, 3, 4, 5, 6, 7 };
		VERIFY(ranges::equal(w, y));
	}
	return true;
}

#undef VERIFY

GTEST_TEST(AlgorithmTest, RangesCopyNTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(
		(test02<input_iterator_wrapper, output_iterator_wrapper>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(
		(test02<random_access_iterator_wrapper, output_iterator_wrapper>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(
		(test02<random_access_iterator_wrapper, random_access_iterator_wrapper>()));
}

}	// namespace ranges_copy_n_test

}	// namespace bksge_algorithm_test
