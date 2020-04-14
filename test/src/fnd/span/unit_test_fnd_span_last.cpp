/**
 *	@file	unit_test_fnd_span_last.cpp
 *
 *	@brief	span::last() のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/span.hpp>
#include <bksge/fnd/algorithm/equal.hpp>
#include <cstddef>
#include <string>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "noexcept_test.hpp"

#define ASSERT_SAME_TYPE(...) \
    static_assert((bksge::is_same<__VA_ARGS__>::value), \
                 "Types differ unexpectedly")

namespace bksge_span_test
{

namespace last_test
{

template <typename Span, std::size_t Count>
BKSGE_CXX14_CONSTEXPR bool test(Span sp)
{
	BKSGE_ASSERT_NOEXCEPT(sp.template last<Count>());
	BKSGE_ASSERT_NOEXCEPT(sp.last(Count));
	auto s1 = sp.template last<Count>();
	auto s2 = sp.last(Count);
	using S1 = decltype(s1);
	using S2 = decltype(s2);
	ASSERT_SAME_TYPE(typename Span::value_type, typename S1::value_type);
	ASSERT_SAME_TYPE(typename Span::value_type, typename S2::value_type);
	static_assert(S1::extent == Count, "");
	static_assert(S2::extent == bksge::dynamic_extent, "");
	return
		s1.data() == s2.data() &&
		s1.size() == s2.size() &&
		bksge::equal(s1.begin(), s1.end(), sp.end() - Count);
}

GTEST_TEST(SpanTest, LastTest)
{
	constexpr int carr[] = {1, 2, 3, 4};
	          int  arr[] = {5, 6, 7};
	std::string   sarr[] = {"ABC", "DEF", "GHI", "JKL", "MNO"};

	{
		using Sp = bksge::span<const int>;
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test<Sp, 0>(Sp{})));

		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test<Sp, 0>(Sp{carr})));
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test<Sp, 1>(Sp{carr})));
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test<Sp, 2>(Sp{carr})));
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test<Sp, 3>(Sp{carr})));
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test<Sp, 4>(Sp{carr})));
	}

	{
		using Sp = bksge::span<const int, 4>;

		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test<Sp, 0>(Sp{carr})));
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test<Sp, 1>(Sp{carr})));
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test<Sp, 2>(Sp{carr})));
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test<Sp, 3>(Sp{carr})));
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test<Sp, 4>(Sp{carr})));
	}

	{
		using Sp = bksge::span<int>;
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test<Sp, 0>(Sp{})));

		EXPECT_TRUE((test<Sp, 0>(Sp{arr})));
		EXPECT_TRUE((test<Sp, 1>(Sp{arr})));
		EXPECT_TRUE((test<Sp, 2>(Sp{arr})));
		EXPECT_TRUE((test<Sp, 3>(Sp{arr})));
	}

	{
		using Sp = bksge::span<int, 3>;

		EXPECT_TRUE((test<Sp, 0>(Sp{arr})));
		EXPECT_TRUE((test<Sp, 1>(Sp{arr})));
		EXPECT_TRUE((test<Sp, 2>(Sp{arr})));
		EXPECT_TRUE((test<Sp, 3>(Sp{arr})));
	}

	{
		using Sp = bksge::span<std::string>;
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test<Sp, 0>(Sp{})));

		EXPECT_TRUE((test<Sp, 0>(Sp{sarr})));
		EXPECT_TRUE((test<Sp, 1>(Sp{sarr})));
		EXPECT_TRUE((test<Sp, 2>(Sp{sarr})));
		EXPECT_TRUE((test<Sp, 3>(Sp{sarr})));
		EXPECT_TRUE((test<Sp, 4>(Sp{sarr})));
		EXPECT_TRUE((test<Sp, 5>(Sp{sarr})));
	}

	{
		using Sp = bksge::span<std::string, 5>;

		EXPECT_TRUE((test<Sp, 0>(Sp{sarr})));
		EXPECT_TRUE((test<Sp, 1>(Sp{sarr})));
		EXPECT_TRUE((test<Sp, 2>(Sp{sarr})));
		EXPECT_TRUE((test<Sp, 3>(Sp{sarr})));
		EXPECT_TRUE((test<Sp, 4>(Sp{sarr})));
		EXPECT_TRUE((test<Sp, 5>(Sp{sarr})));
	}
}

}	// namespace last_test

}	// namespace bksge_span_test
