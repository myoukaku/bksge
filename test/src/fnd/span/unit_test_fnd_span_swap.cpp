/**
 *	@file	unit_test_fnd_span_swap.cpp
 *
 *	@brief	swap(span, span) のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/span.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "noexcept_test.hpp"

namespace bksge_span_test
{

namespace swap_test
{

template <typename Span>
BKSGE_CXX14_CONSTEXPR bool test(Span s1, Span s2)
{
	BKSGE_ASSERT_NOEXCEPT(s1.swap(s2));
	BKSGE_ASSERT_NOEXCEPT(swap(s1, s2));

	auto p1_1 = s1.data();
	auto p2_1 = s2.data();
	auto sz1_1 = s1.size();
	auto sz2_1 = s2.size();

	s1.swap(s2);

	auto p1_2 = s1.data();
	auto p2_2 = s2.data();
	auto sz1_2 = s1.size();
	auto sz2_2 = s2.size();

	swap(s1, s2);

	auto p1_3 = s1.data();
	auto p2_3 = s2.data();
	auto sz1_3 = s1.size();
	auto sz2_3 = s2.size();

	return
		p1_1 == p2_2 && p2_2 == p1_3 &&
		p2_1 == p1_2 && p1_2 == p2_3 &&
		sz1_1 == sz2_2 && sz2_2 == sz1_3 &&
		sz2_1 == sz1_2 && sz1_2 == sz2_3;
}

GTEST_TEST(SpanTest, SwapTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test(bksge::span<int>(), bksge::span<int>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test(bksge::span<int, 0>(), bksge::span<int, 0>()));

	BKSGE_STATIC_CONSTEXPR int arr1[] = {1, 2, 3};
	BKSGE_STATIC_CONSTEXPR int arr2[] = {4, 5, 6, 7};
	BKSGE_STATIC_CONSTEXPR int arr3[] = {8, 9, 0};
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test(bksge::span<const int>(arr1), bksge::span<const int>(arr1)));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test(bksge::span<const int>(arr1), bksge::span<const int>(arr2)));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test(bksge::span<const int>(arr1), bksge::span<const int>(arr3)));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test(bksge::span<const int>(arr2), bksge::span<const int>(arr2)));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test(bksge::span<const int>(arr2), bksge::span<const int>(arr3)));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test(bksge::span<const int>(arr3), bksge::span<const int>(arr3)));

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test(bksge::span<const int, 3>(arr1), bksge::span<const int, 3>(arr1)));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test(bksge::span<const int, 3>(arr1), bksge::span<const int, 4>(arr2)));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test(bksge::span<const int, 3>(arr1), bksge::span<const int, 3>(arr3)));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test(bksge::span<const int, 4>(arr2), bksge::span<const int, 4>(arr2)));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test(bksge::span<const int, 4>(arr2), bksge::span<const int, 3>(arr3)));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test(bksge::span<const int, 3>(arr3), bksge::span<const int, 3>(arr3)));
}

}	// namespace swap_test

}	// namespace bksge_span_test
