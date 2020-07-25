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

template <typename Span>
BKSGE_CXX14_CONSTEXPR bool test(Span sp)
{
	BKSGE_ASSERT_NOEXCEPT(sp.empty());
	return sp.empty();
}

struct A {};

GTEST_TEST(SpanTest, EmptyTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test(bksge::span<int>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test(bksge::span<long>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test(bksge::span<double>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test(bksge::span<A>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test(bksge::span<std::string>()));

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test(bksge::span<int,         0>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test(bksge::span<long,        0>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test(bksge::span<double,      0>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test(bksge::span<A,           0>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test(bksge::span<std::string, 0>()));

	BKSGE_CXX14_CONSTEXPR int arr[] = {10, 11, 12, 13, 14, 15, 16, 17, 18, 19};
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(!test(bksge::span<int const>(arr, 1)));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(!test(bksge::span<int const>(arr, 2)));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(!test(bksge::span<int const>(arr, 3)));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(!test(bksge::span<int const>(arr, 4)));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(!test(bksge::span<int const>(arr, 5)));

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(!test(bksge::span<int const, 1>(arr, 1)));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(!test(bksge::span<int const, 2>(arr, 2)));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(!test(bksge::span<int const, 3>(arr, 3)));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(!test(bksge::span<int const, 4>(arr, 4)));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(!test(bksge::span<int const, 5>(arr, 5)));
}

}	// namespace empty_test

}	// namespace bksge_span_test
