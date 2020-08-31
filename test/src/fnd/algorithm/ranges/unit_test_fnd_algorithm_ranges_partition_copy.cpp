/**
 *	@file	unit_test_fnd_algorithm_ranges_partition_copy.cpp
 *
 *	@brief	ranges::partition_copy のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/algorithm/ranges/partition_copy.hpp>
#include <bksge/fnd/algorithm/ranges/none_of.hpp>
#include <bksge/fnd/algorithm/ranges/all_of.hpp>
#include <bksge/fnd/iterator/ranges/next.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace bksge_algorithm_test
{

namespace ranges_partition_copy_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

struct IsEven
{
	constexpr bool operator()(int a) const
	{
		return a%2==0;
	}
};

struct IsOdd
{
	constexpr bool operator()(int a) const
	{
		return a%2==1;
	}
};

inline BKSGE_CXX14_CONSTEXPR bool test01()
{
	namespace ranges = bksge::ranges;
	{
		int const x[] = { 3,1,4,1,5,9,2,6,5,3 };
		int y[3] = {};
		int z[7] = {};
		test_range<int const, input_iterator_wrapper> rx(x);
		test_range<int, output_iterator_wrapper> ry(y);
		test_range<int, output_iterator_wrapper> rz(z);
		auto pred = IsEven{};
		auto res = ranges::partition_copy(rx, ry.begin(), rz.begin(), pred);
		VERIFY(res.in   == rx.end());
		VERIFY(res.out1 == ry.end());
		VERIFY(res.out2 == rz.end());
		VERIFY(ranges::all_of(y, pred));
		VERIFY(ranges::none_of(z, pred));
	}
	{
		int const x[] = { 1,3,5,7,9 };
		int y[5] = {};
		int z[5] = {};
		test_range<int const, input_iterator_wrapper> rx(x);
		test_range<int, output_iterator_wrapper> ry(y);
		test_range<int, output_iterator_wrapper> rz(z);
		auto pred = IsOdd{};
		auto res = ranges::partition_copy(rx, ry.begin(), rz.begin(), pred);
		VERIFY(res.in.m_ptr   == x+5);
		VERIFY(res.out1.m_ptr == y+5);
		VERIFY(res.out2.m_ptr == z+0);
		VERIFY(ranges::all_of(y, y+5, pred));
		VERIFY(ranges::none_of(z, z+0, pred));
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
		X x[] = { {1},{2},{3},{4},{5},{6},{7},{8},{9} };
		X y[4] = {};
		X z[5] = {};
		test_range<X, input_iterator_wrapper> rx(x);
		test_range<X, output_iterator_wrapper> ry(y);
		test_range<X, output_iterator_wrapper> rz(z);
		auto pred = [](int a) { return a%2==0; };
		auto proj = &X::i;
		auto res = ranges::partition_copy(rx, ry.begin(), rz.begin(), pred, proj);
		VERIFY(res.in   == rx.end());
		VERIFY(res.out1 == ry.end());
		VERIFY(res.out2 == rz.end());
		VERIFY(ranges::all_of(y, pred, proj));
		VERIFY(ranges::none_of(z, pred, proj));
	}
	{
		std::vector<int> x {};
		int y[1] = {};
		int z[1] = {};
		auto res = ranges::partition_copy(x, y, z, [](int a) { return a%2==0; });
		VERIFY(res.in   == x.end());
		VERIFY(res.out1 == y);
		VERIFY(res.out2 == z);
	}
	return true;
}

#undef VERIFY

GTEST_TEST(AlgorithmTest, RangesPartitionCopyTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	EXPECT_TRUE(test02());
}

}	// namespace ranges_partition_copy_test

}	// namespace bksge_algorithm_test
