/**
 *	@file	unit_test_fnd_span_data.cpp
 *
 *	@brief	pointer span::data() のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/span.hpp>
#include <string>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "noexcept_test.hpp"

namespace bksge_span_test
{

namespace data_test
{

template <typename Span>
BKSGE_CXX14_CONSTEXPR bool test(Span sp, typename Span::pointer ptr)
{
	BKSGE_ASSERT_NOEXCEPT(sp.data());
	return sp.data() == ptr;
}

struct A{};

GTEST_TEST(SpanTest, DataTest)
{
	BKSGE_CXX14_CONSTEXPR int arr[] = {10, 11, 12, 13, 14, 15, 16, 17, 18, 19};
	//  dynamic size
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test(bksge::span<int>(),         nullptr));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test(bksge::span<long>(),        nullptr));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test(bksge::span<double>(),      nullptr));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test(bksge::span<A>(),           nullptr));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test(bksge::span<std::string>(), nullptr));

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test(bksge::span<int const>(arr, 1), arr));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test(bksge::span<int const>(arr, 2), arr));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test(bksge::span<int const>(arr, 3), arr));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test(bksge::span<int const>(arr, 4), arr));

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test(bksge::span<int const>(arr + 1, 1), arr + 1));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test(bksge::span<int const>(arr + 2, 2), arr + 2));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test(bksge::span<int const>(arr + 3, 3), arr + 3));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test(bksge::span<int const>(arr + 4, 4), arr + 4));

	//  static size
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test(bksge::span<int, 0>(),         nullptr));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test(bksge::span<long, 0>(),        nullptr));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test(bksge::span<double, 0>(),      nullptr));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test(bksge::span<A, 0>(),           nullptr));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test(bksge::span<std::string, 0>(), nullptr));

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test(bksge::span<int const, 1>(arr, 1), arr));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test(bksge::span<int const, 2>(arr, 2), arr));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test(bksge::span<int const, 3>(arr, 3), arr));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test(bksge::span<int const, 4>(arr, 4), arr));

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test(bksge::span<int const, 1>(arr + 1, 1), arr + 1));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test(bksge::span<int const, 2>(arr + 2, 2), arr + 2));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test(bksge::span<int const, 3>(arr + 3, 3), arr + 3));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test(bksge::span<int const, 4>(arr + 4, 4), arr + 4));
}

}	// namespace data_test

}	// namespace bksge_span_test
