/**
 *	@file	unit_test_fnd_span_begin.cpp
 *
 *	@brief	iterator span::begin() のテスト
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

namespace begin_test
{

template <typename Span>
constexpr bool test_1(Span s)
{
	return
		(s.begin()  == s.end()) &&
		(s.cbegin() == s.cend());
}

template <typename Span>
constexpr bool test_2(Span s)
{
	return
		( *s.begin()  ==  s[0]) &&
		(&*s.begin()  == &s[0]) &&
		( *s.cbegin() ==  s[0]) &&
		(&*s.cbegin() == &s[0]);
}

template <typename Span>
constexpr bool test(Span s)
{
	return
		(s.empty() ? test_1(s) : test_2(s)) &&
		(s.begin() == s.cbegin());
}

struct A {};

bool operator==(A, A) { return true; }

GTEST_TEST(SpanTest, BeginTest)
{
	BKSGE_CONSTEXPR_EXPECT_TRUE(test(bksge::span<int>()));
	BKSGE_CONSTEXPR_EXPECT_TRUE(test(bksge::span<long>()));
	BKSGE_CONSTEXPR_EXPECT_TRUE(test(bksge::span<double>()));
	BKSGE_CONSTEXPR_EXPECT_TRUE(test(bksge::span<A>()));
	BKSGE_CONSTEXPR_EXPECT_TRUE(test(bksge::span<std::string>()));

	BKSGE_CONSTEXPR_EXPECT_TRUE(test(bksge::span<int,         0>()));
	BKSGE_CONSTEXPR_EXPECT_TRUE(test(bksge::span<long,        0>()));
	BKSGE_CONSTEXPR_EXPECT_TRUE(test(bksge::span<double,      0>()));
	BKSGE_CONSTEXPR_EXPECT_TRUE(test(bksge::span<A,           0>()));
	BKSGE_CONSTEXPR_EXPECT_TRUE(test(bksge::span<std::string, 0>()));

	constexpr int arr1[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	BKSGE_CONSTEXPR_EXPECT_TRUE(test(bksge::span<const int>(arr1, 1)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(test(bksge::span<const int>(arr1, 2)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(test(bksge::span<const int>(arr1, 3)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(test(bksge::span<const int>(arr1, 4)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(test(bksge::span<const int>(arr1, 5)));

	std::string s;
	EXPECT_TRUE(test(bksge::span<std::string>(&s, static_cast<std::size_t>(0))));
	EXPECT_TRUE(test(bksge::span<std::string>(&s, 1)));
}

}	// namespace begin_test

}	// namespace bksge_span_test
