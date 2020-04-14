/**
 *	@file	unit_test_fnd_span_front.cpp
 *
 *	@brief	reference span::front() のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/span.hpp>
#include <bksge/fnd/memory/addressof.hpp>
#include <string>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "noexcept_test.hpp"

namespace bksge_span_test
{

namespace front_test
{

template <typename Span>
constexpr bool test(Span sp)
{
	BKSGE_ASSERT_NOEXCEPT(sp.front());
	return bksge::addressof(sp.front()) == sp.data();
}

GTEST_TEST(SpanTest, FrontTest)
{
	constexpr int arr1[] ={0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	BKSGE_CONSTEXPR_EXPECT_TRUE(test(bksge::span<const int>(arr1, 1)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(test(bksge::span<const int>(arr1, 2)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(test(bksge::span<const int>(arr1, 3)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(test(bksge::span<const int>(arr1, 4)));

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test(bksge::span<const int, 1>(arr1, 1)));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test(bksge::span<const int, 2>(arr1, 2)));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test(bksge::span<const int, 3>(arr1, 3)));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test(bksge::span<const int, 4>(arr1, 4)));

	int arr2[] ={10, 11, 12, 13, 14, 15, 16, 17, 18, 19};
	EXPECT_TRUE(test(bksge::span<int>(arr2, 1)));
	EXPECT_TRUE(test(bksge::span<int>(arr2, 2)));
	EXPECT_TRUE(test(bksge::span<int>(arr2, 3)));
	EXPECT_TRUE(test(bksge::span<int>(arr2, 4)));

	EXPECT_TRUE(test(bksge::span<int, 1>(arr2, 1)));
	EXPECT_TRUE(test(bksge::span<int, 2>(arr2, 2)));
	EXPECT_TRUE(test(bksge::span<int, 3>(arr2, 3)));
	EXPECT_TRUE(test(bksge::span<int, 4>(arr2, 4)));

	std::string s;
	EXPECT_TRUE(test(bksge::span<std::string>   (&s, 1)));
	EXPECT_TRUE(test(bksge::span<std::string, 1>(&s, 1)));
}

}	// namespace front_test

}	// namespace bksge_span_test
