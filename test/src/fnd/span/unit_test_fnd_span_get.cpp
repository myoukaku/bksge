/**
 *	@file	unit_test_fnd_span_get.cpp
 *
 *	@brief	std::get(span) のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/span.hpp>
#include <bksge/fnd/memory/addressof.hpp>
#include <cstddef>
#include <string>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "noexcept_test.hpp"

namespace bksge_span_test
{

namespace get_test
{

template <std::size_t Idx, typename Span>
constexpr bool test(Span sp, typename Span::pointer ptr)
{
	BKSGE_ASSERT_NOEXCEPT(std::get<Idx>(sp));
	return bksge::addressof(std::get<Idx>(sp)) == ptr;
}

GTEST_TEST(SpanTest, GetTest)
{
	constexpr int arr1[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test<0>(bksge::span<const int, 4>(arr1, 4), arr1 + 0));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test<1>(bksge::span<const int, 4>(arr1, 4), arr1 + 1));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test<2>(bksge::span<const int, 4>(arr1, 4), arr1 + 2));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test<3>(bksge::span<const int, 4>(arr1, 4), arr1 + 3));

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test<0>(bksge::span<const int, 1>(arr1 + 1, 1), arr1 + 1));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test<1>(bksge::span<const int, 2>(arr1 + 2, 2), arr1 + 3));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test<2>(bksge::span<const int, 3>(arr1 + 3, 3), arr1 + 5));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test<3>(bksge::span<const int, 4>(arr1 + 4, 4), arr1 + 7));

	int arr2[] = {10, 11, 12, 13, 14, 15, 16, 17, 18, 19};
	EXPECT_TRUE(test<0>(bksge::span<int, 4>(arr2, 4), arr2 + 0));
	EXPECT_TRUE(test<1>(bksge::span<int, 4>(arr2, 4), arr2 + 1));
	EXPECT_TRUE(test<2>(bksge::span<int, 4>(arr2, 4), arr2 + 2));
	EXPECT_TRUE(test<3>(bksge::span<int, 4>(arr2, 4), arr2 + 3));

	EXPECT_TRUE(test<0>(bksge::span<int, 1>(arr2 + 1, 1), arr2 + 1));
	EXPECT_TRUE(test<1>(bksge::span<int, 2>(arr2 + 2, 2), arr2 + 3));
	EXPECT_TRUE(test<2>(bksge::span<int, 3>(arr2 + 3, 3), arr2 + 5));
	EXPECT_TRUE(test<3>(bksge::span<int, 4>(arr2 + 4, 4), arr2 + 7));

	std::string s;
	EXPECT_TRUE(test<0>(bksge::span<std::string, 1>(&s, 1), &s));
}

}	// namespace get_test

}	// namespace bksge_span_test
