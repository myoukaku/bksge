/**
 *	@file	unit_test_fnd_span_first.cpp
 *
 *	@brief	span::first() のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/span.hpp>
#include <bksge/fnd/algorithm/equal.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>
#include <string>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "noexcept_test.hpp"

#define ASSERT_SAME_TYPE(...) \
    static_assert((bksge::is_same<__VA_ARGS__>::value), \
                 "Types differ unexpectedly")

namespace bksge_span_test
{

namespace first_test
{

template <typename Span, bksge::size_t Count>
BKSGE_CXX14_CONSTEXPR bool test(Span sp)
{
	BKSGE_ASSERT_NOEXCEPT(sp.template first<Count>());
	BKSGE_ASSERT_NOEXCEPT(sp.first(Count));
	auto s1 = sp.template first<Count>();
	auto s2 = sp.first(Count);
	using S1 = decltype(s1);
	using S2 = decltype(s2);
	ASSERT_SAME_TYPE(typename Span::value_type, typename S1::value_type);
	ASSERT_SAME_TYPE(typename Span::value_type, typename S2::value_type);
	static_assert(S1::extent == Count, "");
	static_assert(S2::extent == bksge::dynamic_extent, "");
	return
		s1.data() == s2.data() &&
		s1.size() == s2.size() &&
		bksge::equal(s1.begin(), s1.end(), sp.begin());
}

GTEST_TEST(SpanTest, FirstTest)
{
	BKSGE_CXX14_CONSTEXPR int carr1[] = {1, 2, 3, 4};
	{
		using Sp = bksge::span<const int>;
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test<Sp, 0>(Sp{})));
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test<Sp, 0>(Sp{carr1})));
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test<Sp, 1>(Sp{carr1})));
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test<Sp, 2>(Sp{carr1})));
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test<Sp, 3>(Sp{carr1})));
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test<Sp, 4>(Sp{carr1})));
	}
	{
		using Sp = bksge::span<const int, 4>;
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test<Sp, 0>(Sp{carr1})));
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test<Sp, 1>(Sp{carr1})));
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test<Sp, 2>(Sp{carr1})));
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test<Sp, 3>(Sp{carr1})));
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test<Sp, 4>(Sp{carr1})));
	}
}

}	// namespace first_test

}	// namespace bksge_span_test

#undef ASSERT_SAME_TYPE
