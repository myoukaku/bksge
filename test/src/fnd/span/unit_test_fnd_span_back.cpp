/**
 *	@file	unit_test_fnd_span_back.cpp
 *
 *	@brief	reference span::back() のテスト
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

namespace back_test
{

template <typename Span>
constexpr bool test(Span sp)
{
	BKSGE_ASSERT_NOEXCEPT(sp.back());
	return bksge::addressof(sp.back()) == sp.data() + sp.size() - 1;
}

GTEST_TEST(SpanTest, BackTest)
{
	constexpr int arr[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	BKSGE_CONSTEXPR_EXPECT_TRUE(test(bksge::span<const int>(arr, 1)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(test(bksge::span<const int>(arr, 2)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(test(bksge::span<const int>(arr, 3)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(test(bksge::span<const int>(arr, 4)));

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test(bksge::span<const int, 1>(arr, 1)));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test(bksge::span<const int, 2>(arr, 2)));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test(bksge::span<const int, 3>(arr, 3)));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test(bksge::span<const int, 4>(arr, 4)));

	std::string s;
	EXPECT_TRUE(test(bksge::span<std::string>   (&s, 1)));
	EXPECT_TRUE(test(bksge::span<std::string, 1>(&s, 1)));
}

}	// namespace back_test

}	// namespace bksge_span_test
