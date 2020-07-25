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
BKSGE_CXX14_CONSTEXPR bool test(Span sp)
{
	BKSGE_ASSERT_NOEXCEPT(sp.front());
	return bksge::addressof(sp.front()) == sp.data();
}

GTEST_TEST(SpanTest, FrontTest)
{
	BKSGE_CXX14_CONSTEXPR int arr[] = {10, 11, 12, 13, 14, 15, 16, 17, 18, 19};
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test(bksge::span<int const>(arr + 5, 1)));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test(bksge::span<int const>(arr + 4, 2)));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test(bksge::span<int const>(arr + 3, 3)));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test(bksge::span<int const>(arr + 2, 4)));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test(bksge::span<int const>(arr + 1, 5)));

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test(bksge::span<int const, 1>(arr + 5, 1)));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test(bksge::span<int const, 2>(arr + 4, 2)));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test(bksge::span<int const, 3>(arr + 3, 3)));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test(bksge::span<int const, 4>(arr + 2, 4)));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test(bksge::span<int const, 5>(arr + 1, 5)));
}

}	// namespace front_test

}	// namespace bksge_span_test
