/**
 *	@file	unit_test_fnd_span_rbegin.cpp
 *
 *	@brief	reverse_iterator span::rbegin() のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/span.hpp>
#include <string>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace bksge_span_test
{

namespace rbegin_test
{

template <typename Span>
BKSGE_CXX14_CONSTEXPR bool test1(Span s)
{
	typename Span::reverse_iterator b = s.rbegin();
	return b == s.rend();
}

template <typename Span>
BKSGE_CXX14_CONSTEXPR bool test2(Span s)
{
	typename Span::reverse_iterator b = s.rbegin();
	const typename Span::size_type last = s.size() - 1;
	return
		( *b ==  s[last]) &&
		(&*b == &s[last]);
}

struct A {};
bool operator==(A, A) { return true; }

GTEST_TEST(SpanTest, RBeginTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test1(bksge::span<int>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test1(bksge::span<long>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test1(bksge::span<double>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test1(bksge::span<A>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test1(bksge::span<std::string>()));

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test1(bksge::span<int, 0>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test1(bksge::span<long, 0>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test1(bksge::span<double, 0>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test1(bksge::span<A, 0>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test1(bksge::span<std::string, 0>()));

	BKSGE_CXX14_CONSTEXPR int arr[] = {10, 11, 12, 13, 14, 15, 16, 17, 18, 19};
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test2(bksge::span<int const>(arr, 1)));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test2(bksge::span<int const>(arr, 2)));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test2(bksge::span<int const>(arr, 3)));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test2(bksge::span<int const>(arr, 4)));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test2(bksge::span<int const>(arr, 5)));
}

}	// namespace rbegin_test

}	// namespace bksge_span_test
