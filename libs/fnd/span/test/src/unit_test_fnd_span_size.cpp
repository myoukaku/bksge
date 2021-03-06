﻿/**
 *	@file	unit_test_fnd_span_size.cpp
 *
 *	@brief	index_type span::size() のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/span.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>
#include <bksge/fnd/string/string.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "noexcept_test.hpp"

namespace bksge_span_test
{

namespace size_test
{

template <typename Span>
BKSGE_CXX14_CONSTEXPR bool test(Span sp, bksge::size_t sz)
{
	BKSGE_ASSERT_NOEXCEPT(sp.size());
	return sp.size() == sz;
}

struct A {};

GTEST_TEST(SpanTest, SizeTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test(bksge::span<int>(),            0));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test(bksge::span<long>(),           0));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test(bksge::span<double>(),         0));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test(bksge::span<A>(),              0));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test(bksge::span<bksge::string>(),  0));

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test(bksge::span<int, 0>(),         0));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test(bksge::span<long, 0>(),        0));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test(bksge::span<double, 0>(),      0));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test(bksge::span<A, 0>(),           0));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test(bksge::span<bksge::string, 0>(), 0));

	BKSGE_CXX14_CONSTEXPR int arr[] = {10, 11, 12, 13, 14, 15, 16, 17, 18, 19};
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test(bksge::span<int const>(arr, 1), 1));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test(bksge::span<int const>(arr, 2), 2));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test(bksge::span<int const>(arr, 3), 3));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test(bksge::span<int const>(arr, 4), 4));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test(bksge::span<int const>(arr, 5), 5));

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test(bksge::span<int const, 1>(arr + 5, 1), 1));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test(bksge::span<int const, 2>(arr + 4, 2), 2));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test(bksge::span<int const, 3>(arr + 3, 3), 3));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test(bksge::span<int const, 4>(arr + 2, 4), 4));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test(bksge::span<int const, 5>(arr + 1, 5), 5));
}

}	// namespace size_test

}	// namespace bksge_span_test
