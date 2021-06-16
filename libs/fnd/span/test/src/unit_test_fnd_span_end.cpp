/**
 *	@file	unit_test_fnd_span_end.cpp
 *
 *	@brief	iterator span::end() のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/span.hpp>
#include <bksge/fnd/string/string.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace bksge_span_test
{

namespace end_test
{

template <typename Span>
BKSGE_CXX14_CONSTEXPR bool test(Span s)
{
	typename Span::iterator e = s.end();
	if (s.empty())
	{
		return
			(e == s.begin()) &&
			(static_cast<size_t>(e - s.begin()) == s.size());
	}
	else
	{
		typename Span::const_pointer last = &*(s.begin() + s.size() - 1);
		return
			(e != s.begin()) &&
			(&*(e-1) == last) &&
			(static_cast<size_t>(e - s.begin()) == s.size());
	}
}

struct A{};
bool operator==(A, A) {return true;}

GTEST_TEST(SpanTest, EndTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test(bksge::span<int>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test(bksge::span<long>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test(bksge::span<double>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test(bksge::span<A>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test(bksge::span<bksge::string>()));

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test(bksge::span<int, 0>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test(bksge::span<long, 0>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test(bksge::span<double, 0>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test(bksge::span<A, 0>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test(bksge::span<bksge::string, 0>()));

	BKSGE_CXX14_CONSTEXPR int arr[] = {10, 11, 12, 13, 14, 15, 16, 17, 18, 19};
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test(bksge::span<int const>(arr, 1)));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test(bksge::span<int const>(arr, 2)));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test(bksge::span<int const>(arr, 3)));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test(bksge::span<int const>(arr, 4)));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test(bksge::span<int const>(arr, 5)));
}

}	// namespace end_test

}	// namespace bksge_span_test
