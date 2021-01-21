/**
 *	@file	unit_test_fnd_algorithm_radix_sort.cpp
 *
 *	@brief	radix_sort のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/algorithm/radix_sort.hpp>
#include <bksge/fnd/algorithm/equal.hpp>
#include <bksge/fnd/iterator/begin.hpp>
#include <bksge/fnd/iterator/end.hpp>
#include <bksge/fnd/array.hpp>
#include <bksge/fnd/vector.hpp>
#include <gtest/gtest.h>

namespace bksge_algorithm_test
{

namespace radix_sort_test
{

GTEST_TEST(AlgorithmTest, radix_sortTest)
{
	{
		unsigned char a[] { 3,1,4, };
		bksge::radix_sort(bksge::begin(a), bksge::end(a));
		unsigned char b[] { 1,3,4, };
		EXPECT_TRUE(bksge::equal(
			bksge::begin(a), bksge::end(a),
			bksge::begin(b), bksge::end(b)));
	}
	{
		unsigned short a[] { 1,2,2,1,2,2,2,1,1,1, };
		bksge::radix_sort(bksge::begin(a), bksge::end(a));
		unsigned short b[] { 1,1,1,1,1,2,2,2,2,2, };
		EXPECT_TRUE(bksge::equal(
			bksge::begin(a), bksge::end(a),
			bksge::begin(b), bksge::end(b)));
	}
	{
		unsigned int a[] { 3,1,4,1,5,9,2,6,5,3,5, };
		bksge::radix_sort(bksge::begin(a), bksge::end(a));
		unsigned int b[] { 1,1,2,3,3,4,5,5,5,6,9, };
		EXPECT_TRUE(bksge::equal(
			bksge::begin(a), bksge::end(a),
			bksge::begin(b), bksge::end(b)));
	}
	{
		unsigned long long a[] { 19,18,17,16,15,14,13,12,11,10, };
		bksge::radix_sort(bksge::begin(a), bksge::end(a));
		unsigned long long b[] { 10,11,12,13,14,15,16,17,18,19, };
		EXPECT_TRUE(bksge::equal(
			bksge::begin(a), bksge::end(a),
			bksge::begin(b), bksge::end(b)));
	}
	{
		bksge::array<unsigned int, 6> a {{ 3,1,4,1,5,9, }};
		bksge::radix_sort(bksge::begin(a), bksge::end(a));
		bksge::array<unsigned int, 6> b {{ 1,1,3,4,5,9, }};
		EXPECT_TRUE(bksge::equal(
			bksge::begin(a), bksge::end(a),
			bksge::begin(b), bksge::end(b)));
	}
	{
		bksge::vector<unsigned int> a { 5,4,1,1,3, };
		bksge::radix_sort(bksge::begin(a), bksge::end(a));
		bksge::vector<unsigned int> b { 1,1,3,4,5, };
		EXPECT_TRUE(bksge::equal(
			bksge::begin(a), bksge::end(a),
			bksge::begin(b), bksge::end(b)));
	}
	{
		bksge::vector<unsigned int> a;
		bksge::radix_sort(bksge::begin(a), bksge::end(a));
		EXPECT_TRUE(a.empty());
	}
}

}	// namespace radix_sort_test

}	// namespace bksge_algorithm_test
