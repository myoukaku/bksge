/**
 *	@file	unit_test_fnd_algorithm_ranges_set_intersection.cpp
 *
 *	@brief	ranges::set_intersection のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/algorithm/ranges/set_intersection.hpp>
#include <bksge/fnd/algorithm/ranges/equal.hpp>
#include <bksge/fnd/functional/ranges/greater.hpp>
#include <bksge/fnd/iterator/ranges/next.hpp>
#include <gtest/gtest.h>
#include <vector>
#include <list>
#include <forward_list>
#include <iterator>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace bksge_algorithm_test
{

namespace ranges_set_intersection_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline BKSGE_CXX14_CONSTEXPR bool test01()
{
	namespace ranges = bksge::ranges;
	{
		int const x[] = { 1, 2, 3, 4 };
		int const y[] = { 3, 4, 5, 6 };
		int z[2] = {};
		test_range<int const, input_iterator_wrapper> rx(x);
		test_range<int const, input_iterator_wrapper> ry(y);
		test_range<int, output_iterator_wrapper> rz(z);
		auto res = ranges::set_intersection(rx, ry, rz.begin());
		VERIFY(res.in1 == rx.end());
		VERIFY(res.in2 == ry.end());
		VERIFY(res.out == rz.end());
		int const a[] = { 3, 4 };
		VERIFY(ranges::equal(z, a));
	}
	{
		int const x[] = { 6, 5, 2, 1 };
		int const y[] = { 5, 3, 1 };
		int z[2] = {};
		test_range<int const, input_iterator_wrapper> rx(x);
		test_range<int const, input_iterator_wrapper> ry(y);
		test_range<int, output_iterator_wrapper> rz(z);
		auto res = ranges::set_intersection(rx, ry, rz.begin(), ranges::greater{});
		VERIFY(res.in1 == rx.end());
		VERIFY(res.in2 == ry.end());
		VERIFY(res.out == rz.end());
		int const a[] = { 5, 1 };
		VERIFY(ranges::equal(z, a));
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
		X const x[] = { {1}, {2}, {3}, {4}, {5} };
		X const y[] = { {3}, {4}, {5}, {6} };
		X z[3] = {};
		test_range<X const, input_iterator_wrapper> rx(x);
		test_range<X const, input_iterator_wrapper> ry(y);
		test_range<X, output_iterator_wrapper> rz(z);
		auto res = ranges::set_intersection(rx, ry, rz.begin(), {}, &X::i, &X::i);
		VERIFY(res.in1 == rx.end());
		VERIFY(res.in2 == ry.end());
		VERIFY(res.out == rz.end());
		int const a[] = { 3, 4, 5 };
		VERIFY(ranges::equal(z, a, {}, &X::i));
	}
	{
		int const x[] = { 5, 6, 7 };
		std::list<int> const y = { 1, 2, 3 };
		int z[1];
		auto res = ranges::set_intersection(x, y, z);
		VERIFY(res.in1 == x+3);
		VERIFY(res.in2 == y.end());
		VERIFY(res.out == z);
	}
	{
		std::vector<int> const x;
		std::forward_list<int> const y;
		int z[1];
		auto res = ranges::set_intersection(x, y, z);
		VERIFY(res.in1 == x.end());
		VERIFY(res.in2 == y.end());
		VERIFY(res.out == z);
	}
	return true;
}

#undef VERIFY

GTEST_TEST(AlgorithmTest, RangesSetIntersectionTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	EXPECT_TRUE(test02());
}

}	// namespace ranges_set_intersection_test

}	// namespace bksge_algorithm_test
