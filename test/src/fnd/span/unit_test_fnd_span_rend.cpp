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

template <typename Span>
constexpr bool test_1(Span s)
{
	return
		(s.rend()  == s.rbegin()) &&
		(s.crend() == s.crbegin());
}

template <typename Span>
constexpr bool test_2(Span s)
{
	return
		(s.rend()  != s.rbegin()) &&
		(s.crend() != s.crbegin());
}

template <typename Span>
constexpr bool test(Span s)
{
	return
		(s.empty() ? test_1(s) : test_2(s)) &&
		(static_cast<std::size_t>(s.rend() -  s.rbegin())  == s.size()) &&
		(static_cast<std::size_t>(s.crend() - s.crbegin()) == s.size()) &&
		(s.rend() == s.crend());
}

struct A {};

bool operator==(A, A) { return true; }

GTEST_TEST(SpanTest, REndTest)
{
	BKSGE_CXX17_CONSTEXPR_EXPECT_TRUE((test(bksge::span<int>())));
	BKSGE_CXX17_CONSTEXPR_EXPECT_TRUE((test(bksge::span<long>())));
	BKSGE_CXX17_CONSTEXPR_EXPECT_TRUE((test(bksge::span<double>())));
	BKSGE_CXX17_CONSTEXPR_EXPECT_TRUE((test(bksge::span<A>())));
	BKSGE_CXX17_CONSTEXPR_EXPECT_TRUE((test(bksge::span<std::string>())));

	BKSGE_CXX17_CONSTEXPR_EXPECT_TRUE((test(bksge::span<int,         0>())));
	BKSGE_CXX17_CONSTEXPR_EXPECT_TRUE((test(bksge::span<long,        0>())));
	BKSGE_CXX17_CONSTEXPR_EXPECT_TRUE((test(bksge::span<double,      0>())));
	BKSGE_CXX17_CONSTEXPR_EXPECT_TRUE((test(bksge::span<A,           0>())));
	BKSGE_CXX17_CONSTEXPR_EXPECT_TRUE((test(bksge::span<std::string, 0>())));

	constexpr int arr1[] ={0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	BKSGE_CXX17_CONSTEXPR_EXPECT_TRUE((test(bksge::span<const int>(arr1, 1))));
	BKSGE_CXX17_CONSTEXPR_EXPECT_TRUE((test(bksge::span<const int>(arr1, 2))));
	BKSGE_CXX17_CONSTEXPR_EXPECT_TRUE((test(bksge::span<const int>(arr1, 3))));
	BKSGE_CXX17_CONSTEXPR_EXPECT_TRUE((test(bksge::span<const int>(arr1, 4))));
	BKSGE_CXX17_CONSTEXPR_EXPECT_TRUE((test(bksge::span<const int>(arr1, 5))));

	EXPECT_TRUE((test(bksge::span<int>        ())));
	EXPECT_TRUE((test(bksge::span<long>       ())));
	EXPECT_TRUE((test(bksge::span<double>     ())));
	EXPECT_TRUE((test(bksge::span<A>          ())));
	EXPECT_TRUE((test(bksge::span<std::string>())));

	EXPECT_TRUE((test(bksge::span<int,         0>())));
	EXPECT_TRUE((test(bksge::span<long,        0>())));
	EXPECT_TRUE((test(bksge::span<double,      0>())));
	EXPECT_TRUE((test(bksge::span<A,           0>())));
	EXPECT_TRUE((test(bksge::span<std::string, 0>())));

	int arr2[] ={10, 11, 12, 13, 14, 15, 16, 17, 18, 19};
	EXPECT_TRUE((test(bksge::span<int>(arr2, 1))));
	EXPECT_TRUE((test(bksge::span<int>(arr2, 2))));
	EXPECT_TRUE((test(bksge::span<int>(arr2, 3))));
	EXPECT_TRUE((test(bksge::span<int>(arr2, 4))));
	EXPECT_TRUE((test(bksge::span<int>(arr2, 5))));

	std::string s;
	EXPECT_TRUE((test(bksge::span<std::string>(&s, static_cast<std::size_t>(0)))));
	EXPECT_TRUE((test(bksge::span<std::string>(&s, 1))));
}

}	// namespace rend_test

}	// namespace bksge_span_test
