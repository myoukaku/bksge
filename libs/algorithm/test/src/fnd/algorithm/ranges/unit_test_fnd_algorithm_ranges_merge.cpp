/**
 *	@file	unit_test_fnd_algorithm_ranges_merge.cpp
 *
 *	@brief	ranges::merge のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/algorithm/ranges/merge.hpp>
#include <bksge/fnd/algorithm/ranges/sort.hpp>
#include <bksge/fnd/algorithm/ranges/equal.hpp>
#include <bksge/fnd/functional/ranges/greater.hpp>
#include <bksge/fnd/vector.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace bksge_algorithm_test
{

namespace ranges_merge_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline BKSGE_CXX14_CONSTEXPR bool test01()
{
	namespace ranges = bksge::ranges;
	{
		int x[] = { 1,2,3,4 };
		int y[] = { 3,4,5,6,7 };
		int z[9] = {};
		test_range<int, input_iterator_wrapper> rx(x);
		test_range<int, input_iterator_wrapper> ry(y);
		test_range<int, output_iterator_wrapper> rz(z);
		auto res = ranges::merge(rx, ry, rz.begin());
		VERIFY(res.in1 == rx.end());
		VERIFY(res.in2 == ry.end());
		VERIFY(res.out == rz.end());
		int a[] = { 1,2,3,3,4,4,5,6,7 };
		VERIFY(ranges::equal(z, a));
	}
	{
		int x[] = { 5,5,4,2,2,2 };
		int y[] = { 7,6,5,4,0 };
		int z[11] = {};
		test_range<int, input_iterator_wrapper> rx(x);
		test_range<int, input_iterator_wrapper> ry(y);
		test_range<int, output_iterator_wrapper> rz(z);
		auto res = ranges::merge(rx, ry, rz.begin(), ranges::greater{});
		VERIFY(res.in1 == rx.end());
		VERIFY(res.in2 == ry.end());
		VERIFY(res.out == rz.end());
		int a[] = { 7,6,5,5,5,4,4,2,2,2,0 };
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
		int x[] = { 1,2,3,4,5 };
		for (int i = 0; i <= 5; i++)
		{
			for (int j = 0; j <= 5; j++)
			{
				int z[10];
				test_range<int, input_iterator_wrapper> rx(x, x+i);
				test_range<int, input_iterator_wrapper> ry(x, x+j);
				test_range<int, output_iterator_wrapper> rz(z, z+i+j);
				auto res = ranges::merge(rx, ry, rz.begin());
				VERIFY(res.in1 == rx.end());
				VERIFY(res.in2 == ry.end());
				VERIFY(res.out == rz.end());

				bksge::vector<int> v(x, x+i);
				v.insert(v.end(), x, x+j);
				ranges::sort(v);

				VERIFY(ranges::equal(v.begin(), v.end(), z, z+i+j));
			}
		}
	}
	{
		X x[] = { {5},{4},{3},{2},{1} };
		X y[] = { {6},{4},{2},{0} };
		X z[9] = {};
		auto res = ranges::merge(x, y, z, ranges::greater{}, &X::i, &X::i);
		VERIFY(res.in1 == x+5);
		VERIFY(res.in2 == y+4);
		VERIFY(res.out == z+9);
		int a[] = { 6,5,4,4,3,2,2,1,0 };
		VERIFY(ranges::equal(z, a, {}, &X::i, {}));
	}
	{
		bksge::vector<int> x;
		bksge::vector<int> y;
		int z[1] = {};
		auto res = ranges::merge(x, y, z);
		VERIFY(res.in1 == x.begin());
		VERIFY(res.in2 == y.begin());
		VERIFY(res.out == z);
	}
	return true;
}

#undef VERIFY

GTEST_TEST(AlgorithmTest, RangesMergeTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	EXPECT_TRUE(test02());
}

}	// namespace ranges_merge_test

}	// namespace bksge_algorithm_test
