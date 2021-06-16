/**
 *	@file	unit_test_fnd_algorithm_ranges_generate_n.cpp
 *
 *	@brief	ranges::generate_n のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/algorithm/ranges/generate_n.hpp>
#include <bksge/fnd/algorithm/ranges/equal.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace bksge_algorithm_test
{

namespace ranges_generate_n_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

struct Foo
{
	int a;

	BKSGE_CXX14_CONSTEXPR Foo() : a(0) {}

	BKSGE_CXX14_CONSTEXPR Foo(int x) : a(x) {}

	BKSGE_CXX14_CONSTEXPR int operator()()
	{
		return a++;
	}
};

inline BKSGE_CXX14_CONSTEXPR bool test01()
{
	namespace ranges = bksge::ranges;
	{
		int x[] = {5,6,7};
		auto res = ranges::generate_n(x, -1, Foo{});
		VERIFY(res == x);
		int const y[] = {5,6,7};
		VERIFY(ranges::equal(x, y));
	}
	{
		int x[] = {5,6,7,8};
		Foo f{};
		auto res = ranges::generate_n(x, 3, f);
		VERIFY(res == x+3);
		int const y[] = {0,1,2,8};
		VERIFY(ranges::equal(x, y));
	}
	{
		int x[] = {5,6,7,8};
		test_range<int, output_iterator_wrapper> rx(x);
		auto res = ranges::generate_n(rx.begin(), 4, Foo{10});
		VERIFY(res == rx.end());
		int const y[] = {10,11,12,13};
		VERIFY(ranges::equal(x, y));
	}
	return true;
}

inline bool test02()
{
	namespace ranges = bksge::ranges;
	{
		int x[6] = {};
		int a = 1;
		auto res = ranges::generate_n(x, 3, [&] { return a++; });
		VERIFY(res == x+3);
		int const y[6] = {1,2,3,0,0,0};
		VERIFY(ranges::equal(x, y));
	}
	{
		int x[] = {1,2,3,4,5};
		auto res = ranges::generate_n(x+1, 3, [&] { return -1; });
		VERIFY(res == x+4);
		int const y[5] = {1,-1,-1,-1,5};
		VERIFY(ranges::equal(x, y));
	}
	return true;
}

#undef VERIFY

GTEST_TEST(AlgorithmTest, RangesGenerateNTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	EXPECT_TRUE(test02());
}

}	// namespace ranges_generate_n_test

}	// namespace bksge_algorithm_test
