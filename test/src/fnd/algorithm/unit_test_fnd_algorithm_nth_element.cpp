/**
 *	@file	unit_test_fnd_algorithm_nth_element.cpp
 *
 *	@brief	nth_element のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/algorithm/nth_element.hpp>
#include <bksge/fnd/functional/greater.hpp>
#include <bksge/fnd/iterator/begin.hpp>
#include <bksge/fnd/iterator/end.hpp>
#include <bksge/fnd/iterator/next.hpp>
#include <gtest/gtest.h>
#include <array>
#include <vector>

namespace bksge_algorithm_test
{

namespace nth_element_test
{

template <typename RandomAccessIterator>
void NthElementTest(
	RandomAccessIterator first,
	RandomAccessIterator nth,
	RandomAccessIterator last)
{
	for (auto i = first; i < nth; ++i)
	{
		for (auto j = nth; j < last; ++j)
		{
			EXPECT_FALSE(*j < *i);
		}
	}
}

template <typename RandomAccessIterator, typename Compare>
void NthElementTest(
	RandomAccessIterator first,
	RandomAccessIterator nth,
	RandomAccessIterator last,
	Compare comp)
{
	for (auto i = first; i < nth; ++i)
	{
		for (auto j = nth; j < last; ++j)
		{
			EXPECT_FALSE(comp(*j, *i));
		}
	}
}

GTEST_TEST(AlgorithmTest, NthElementTest)
{
	{
		const int nth = 1;
		int a[] { 3, 1, 4, 1, 5, 9, 2, 6, 5, 3 };
		bksge::nth_element(bksge::begin(a), bksge::next(bksge::begin(a), nth), bksge::end(a));
		NthElementTest(bksge::begin(a), bksge::next(bksge::begin(a), nth), bksge::end(a));
	}
	{
		const int nth = 3;
		int a[] { 3, 1, 4, 1, 5, 9, 2, 6, 5, 3 };
		bksge::nth_element(bksge::begin(a), bksge::next(bksge::begin(a), nth), bksge::end(a), bksge::greater<>());
		NthElementTest(bksge::begin(a), bksge::next(bksge::begin(a), nth), bksge::end(a), bksge::greater<>());
	}
	{
		const int nth = 5;
		std::array<int, 10> a {{ 3, 1, 4, 1, 5, 9, 2, 6, 5, 3 }};
		bksge::nth_element(bksge::begin(a), bksge::next(bksge::begin(a), nth), bksge::end(a));
		NthElementTest(bksge::begin(a), bksge::next(bksge::begin(a), nth), bksge::end(a));
	}
	{
		const int nth = 7;
		std::array<int, 10> a {{ 3, 1, 4, 1, 5, 9, 2, 6, 5, 3 }};
		bksge::nth_element(bksge::begin(a), bksge::next(bksge::begin(a), nth), bksge::end(a), bksge::greater<>());
		NthElementTest(bksge::begin(a), bksge::next(bksge::begin(a), nth), bksge::end(a), bksge::greater<>());
	}
	{
		const int nth = 6;
		std::vector<int> a { 3, 1, 4, 1, 5, 9, 2, 6, 5, 3 };
		bksge::nth_element(bksge::begin(a), bksge::next(bksge::begin(a), nth), bksge::end(a));
		NthElementTest(bksge::begin(a), bksge::next(bksge::begin(a), nth), bksge::end(a));
	}
	{
		const int nth = 8;
		std::vector<int> a { 3, 1, 4, 1, 5, 9, 2, 6, 5, 3 };
		bksge::nth_element(bksge::begin(a), bksge::next(bksge::begin(a), nth), bksge::end(a), bksge::greater<>());
		NthElementTest(bksge::begin(a), bksge::next(bksge::begin(a), nth), bksge::end(a), bksge::greater<>());
	}
}

}	// namespace nth_element_test

}	// namespace bksge_algorithm_test
