/**
 *	@file	unit_test_fnd_span_size.cpp
 *
 *	@brief	index_type span::size() のテスト
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

namespace size_test
{

template <typename Span>
constexpr bool test(Span sp, std::size_t sz)
{
	BKSGE_ASSERT_NOEXCEPT(sp.size());
	return sp.size() == sz;
}

struct A {};

GTEST_TEST(SpanTest, SizeTest)
{
	BKSGE_CONSTEXPR_EXPECT_TRUE((test(bksge::span<int>(),         0)));
	BKSGE_CONSTEXPR_EXPECT_TRUE((test(bksge::span<long>(),        0)));
	BKSGE_CONSTEXPR_EXPECT_TRUE((test(bksge::span<double>(),      0)));
	BKSGE_CONSTEXPR_EXPECT_TRUE((test(bksge::span<A>(),           0)));
	BKSGE_CONSTEXPR_EXPECT_TRUE((test(bksge::span<std::string>(), 0)));

	BKSGE_CONSTEXPR_EXPECT_TRUE((test(bksge::span<int,         0>(), 0)));
	BKSGE_CONSTEXPR_EXPECT_TRUE((test(bksge::span<long,        0>(), 0)));
	BKSGE_CONSTEXPR_EXPECT_TRUE((test(bksge::span<double,      0>(), 0)));
	BKSGE_CONSTEXPR_EXPECT_TRUE((test(bksge::span<A,           0>(), 0)));
	BKSGE_CONSTEXPR_EXPECT_TRUE((test(bksge::span<std::string, 0>(), 0)));

	constexpr int arr1[] ={0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	BKSGE_CONSTEXPR_EXPECT_TRUE((test(bksge::span<const int>(arr1, 1), 1)));
	BKSGE_CONSTEXPR_EXPECT_TRUE((test(bksge::span<const int>(arr1, 2), 2)));
	BKSGE_CONSTEXPR_EXPECT_TRUE((test(bksge::span<const int>(arr1, 3), 3)));
	BKSGE_CONSTEXPR_EXPECT_TRUE((test(bksge::span<const int>(arr1, 4), 4)));
	BKSGE_CONSTEXPR_EXPECT_TRUE((test(bksge::span<const int>(arr1, 5), 5)));

	EXPECT_TRUE((test(bksge::span<int>        (), 0)));
	EXPECT_TRUE((test(bksge::span<long>       (), 0)));
	EXPECT_TRUE((test(bksge::span<double>     (), 0)));
	EXPECT_TRUE((test(bksge::span<A>          (), 0)));
	EXPECT_TRUE((test(bksge::span<std::string>(), 0)));

	EXPECT_TRUE((test(bksge::span<int,         0>(), 0)));
	EXPECT_TRUE((test(bksge::span<long,        0>(), 0)));
	EXPECT_TRUE((test(bksge::span<double,      0>(), 0)));
	EXPECT_TRUE((test(bksge::span<A,           0>(), 0)));
	EXPECT_TRUE((test(bksge::span<std::string, 0>(), 0)));

	int arr2[] ={10, 11, 12, 13, 14, 15, 16, 17, 18, 19};
	EXPECT_TRUE((test(bksge::span<int>(arr2, 1), 1)));
	EXPECT_TRUE((test(bksge::span<int>(arr2, 2), 2)));
	EXPECT_TRUE((test(bksge::span<int>(arr2, 3), 3)));
	EXPECT_TRUE((test(bksge::span<int>(arr2, 4), 4)));
	EXPECT_TRUE((test(bksge::span<int>(arr2, 5), 5)));

	EXPECT_TRUE((test(bksge::span<int, 1>(arr2 + 5, 1), 1)));
	EXPECT_TRUE((test(bksge::span<int, 2>(arr2 + 4, 2), 2)));
	EXPECT_TRUE((test(bksge::span<int, 3>(arr2 + 3, 3), 3)));
	EXPECT_TRUE((test(bksge::span<int, 4>(arr2 + 2, 4), 4)));
	EXPECT_TRUE((test(bksge::span<int, 5>(arr2 + 1, 5), 5)));

	std::string s;
	EXPECT_TRUE((test(bksge::span<std::string>(&s, static_cast<std::size_t>(0)), 0)));
	EXPECT_TRUE((test(bksge::span<std::string>(&s, 1), 1)));
}

}	// namespace size_test

}	// namespace bksge_span_test
