/**
 *	@file	unit_test_fnd_span_rend.cpp
 *
 *	@brief	reverse_iterator span::rend() のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/span.hpp>
#include <cstddef>
#include <string>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace bksge_span_test
{

namespace rend_test
{

template <class Span>
BKSGE_CXX14_CONSTEXPR bool test(Span s)
{
	typename Span::reverse_iterator e = s.rend();
	if (s.empty())
	{
		return
			(e == s.rbegin()) &&
			(static_cast<size_t>(e - s.rbegin()) == s.size());
	}
	else
	{
		return
			(e != s.rbegin()) &&
			(static_cast<size_t>(e - s.rbegin()) == s.size());
	}
}

struct A {};
bool operator==(A, A) { return true; }

GTEST_TEST(SpanTest, REndTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test(bksge::span<int>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test(bksge::span<long>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test(bksge::span<double>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test(bksge::span<A>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test(bksge::span<std::string>()));

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test(bksge::span<int, 0>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test(bksge::span<long, 0>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test(bksge::span<double, 0>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test(bksge::span<A, 0>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test(bksge::span<std::string, 0>()));

	BKSGE_CXX14_CONSTEXPR int arr[] ={10, 11, 12, 13, 14, 15, 16, 17, 18, 19};
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test(bksge::span<int const>(arr, 1)));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test(bksge::span<int const>(arr, 2)));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test(bksge::span<int const>(arr, 3)));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test(bksge::span<int const>(arr, 4)));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test(bksge::span<int const>(arr, 5)));
}

}	// namespace rend_test

}	// namespace bksge_span_test
