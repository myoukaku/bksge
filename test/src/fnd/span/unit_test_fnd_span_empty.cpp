/**
 *	@file	unit_test_fnd_span_empty.cpp
 *
 *	@brief	bool span::empty() のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/span.hpp>
#include <cstddef>
#include <string>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "noexcept_test.hpp"

namespace bksge_span_test
{

namespace empty_test
{

struct A {};

GTEST_TEST(SpanTest, EmptyTest)
{
	BKSGE_ASSERT_NOEXCEPT(bksge::span<int>   ().empty());
	BKSGE_ASSERT_NOEXCEPT(bksge::span<int, 0>().empty());

	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::span<int>().empty());
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::span<long>().empty());
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::span<double>().empty());
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::span<A>().empty());
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::span<std::string>().empty());

	BKSGE_CONSTEXPR_EXPECT_TRUE((bksge::span<int, 0>().empty()));
	BKSGE_CONSTEXPR_EXPECT_TRUE((bksge::span<long, 0>().empty()));
	BKSGE_CONSTEXPR_EXPECT_TRUE((bksge::span<double, 0>().empty()));
	BKSGE_CONSTEXPR_EXPECT_TRUE((bksge::span<A, 0>().empty()));
	BKSGE_CONSTEXPR_EXPECT_TRUE((bksge::span<std::string, 0>().empty()));

	constexpr int arr1[] ={0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::span<const int>(arr1, 1).empty());
	BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::span<const int>(arr1, 2).empty());
	BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::span<const int>(arr1, 3).empty());
	BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::span<const int>(arr1, 4).empty());
	BKSGE_CONSTEXPR_EXPECT_TRUE(!bksge::span<const int>(arr1, 5).empty());

	std::string s;
	EXPECT_TRUE( ((bksge::span<std::string>(&s, static_cast<std::size_t>(0))).empty()));
	EXPECT_TRUE(!((bksge::span<std::string>(&s, 1).empty())));
}

}	// namespace empty_test

}	// namespace bksge_span_test
