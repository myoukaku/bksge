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
constexpr bool test(Span sp, typename Span::pointer ptr)
{
	BKSGE_ASSERT_NOEXCEPT(sp.data());
	return sp.data() == ptr;
}

struct A {};

GTEST_TEST(SpanTest, DataTest)
{
	constexpr int arr1[] ={0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

	//  dynamic size
	BKSGE_CONSTEXPR_EXPECT_TRUE(test(bksge::span<int>(), nullptr));
	BKSGE_CONSTEXPR_EXPECT_TRUE(test(bksge::span<long>(), nullptr));
	BKSGE_CONSTEXPR_EXPECT_TRUE(test(bksge::span<double>(), nullptr));
	BKSGE_CONSTEXPR_EXPECT_TRUE(test(bksge::span<A>(), nullptr));
	BKSGE_CONSTEXPR_EXPECT_TRUE(test(bksge::span<std::string>(), nullptr));

	BKSGE_CONSTEXPR_EXPECT_TRUE(test(bksge::span<const int>(arr1, 1), arr1));
	BKSGE_CONSTEXPR_EXPECT_TRUE(test(bksge::span<const int>(arr1, 2), arr1));
	BKSGE_CONSTEXPR_EXPECT_TRUE(test(bksge::span<const int>(arr1, 3), arr1));
	BKSGE_CONSTEXPR_EXPECT_TRUE(test(bksge::span<const int>(arr1, 4), arr1));

	BKSGE_CONSTEXPR_EXPECT_TRUE(test(bksge::span<const int>(arr1 + 1, 1), arr1 + 1));
	BKSGE_CONSTEXPR_EXPECT_TRUE(test(bksge::span<const int>(arr1 + 2, 2), arr1 + 2));
	BKSGE_CONSTEXPR_EXPECT_TRUE(test(bksge::span<const int>(arr1 + 3, 3), arr1 + 3));
	BKSGE_CONSTEXPR_EXPECT_TRUE(test(bksge::span<const int>(arr1 + 4, 4), arr1 + 4));

	//  static size
	BKSGE_CONSTEXPR_EXPECT_TRUE(test(bksge::span<int, 0>(), nullptr));
	BKSGE_CONSTEXPR_EXPECT_TRUE(test(bksge::span<long, 0>(), nullptr));
	BKSGE_CONSTEXPR_EXPECT_TRUE(test(bksge::span<double, 0>(), nullptr));
	BKSGE_CONSTEXPR_EXPECT_TRUE(test(bksge::span<A, 0>(), nullptr));
	BKSGE_CONSTEXPR_EXPECT_TRUE(test(bksge::span<std::string, 0>(), nullptr));

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test(bksge::span<const int, 1>(arr1, 1), arr1));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test(bksge::span<const int, 2>(arr1, 2), arr1));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test(bksge::span<const int, 3>(arr1, 3), arr1));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test(bksge::span<const int, 4>(arr1, 4), arr1));

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test(bksge::span<const int, 1>(arr1 + 1, 1), arr1 + 1));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test(bksge::span<const int, 2>(arr1 + 2, 2), arr1 + 2));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test(bksge::span<const int, 3>(arr1 + 3, 3), arr1 + 3));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test(bksge::span<const int, 4>(arr1 + 4, 4), arr1 + 4));

	std::string s;
	EXPECT_TRUE(test(bksge::span<std::string>(&s, 1), &s));
	EXPECT_TRUE(test(bksge::span<std::string, 1>(&s, 1), &s));
}

}	// namespace data_test

}	// namespace bksge_span_test
