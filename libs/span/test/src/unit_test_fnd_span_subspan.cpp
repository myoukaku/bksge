/**
 *	@file	unit_test_fnd_span_subspan.cpp
 *
 *	@brief	span::subspan() のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/span.hpp>
#include <bksge/fnd/algorithm/equal.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "noexcept_test.hpp"

#define ASSERT_SAME_TYPE(...) \
    static_assert((bksge::is_same<__VA_ARGS__>::value), \
                 "Types differ unexpectedly")

namespace bksge_span_test
{

namespace subspan_test
{

template <typename Span, bksge::size_t Offset, bksge::size_t Count>
BKSGE_CXX14_CONSTEXPR bool test(Span sp)
{
	BKSGE_ASSERT_NOEXCEPT(sp.template subspan<Offset, Count>());
	BKSGE_ASSERT_NOEXCEPT(sp.subspan(Offset, Count));
	auto s1 = sp.template subspan<Offset, Count>();
	auto s2 = sp.subspan(Offset, Count);
	using S1 = decltype(s1);
	using S2 = decltype(s2);
	ASSERT_SAME_TYPE(typename Span::value_type, typename S1::value_type);
	ASSERT_SAME_TYPE(typename Span::value_type, typename S2::value_type);
	static_assert(S1::extent == Count, "");
	static_assert(S2::extent == bksge::dynamic_extent, "");
	return
		s1.data() == s2.data() &&
		s1.size() == s2.size() &&
		bksge::equal(s1.begin(), s1.end(), sp.begin() + Offset);
}

template <typename Span, bksge::size_t Offset>
BKSGE_CXX14_CONSTEXPR bool test(Span sp)
{
	BKSGE_ASSERT_NOEXCEPT(sp.template subspan<Offset>());
	BKSGE_ASSERT_NOEXCEPT(sp.subspan(Offset));
	auto s1 = sp.template subspan<Offset>();
	auto s2 = sp.subspan(Offset);
	using S1 = decltype(s1);
	using S2 = decltype(s2);
	ASSERT_SAME_TYPE(typename Span::value_type, typename S1::value_type);
	ASSERT_SAME_TYPE(typename Span::value_type, typename S2::value_type);
	static_assert(S1::extent == (Span::extent == bksge::dynamic_extent ? bksge::dynamic_extent : Span::extent - Offset), "");
	static_assert(S2::extent == bksge::dynamic_extent, "");
	return
		s1.data() == s2.data() &&
		s1.size() == s2.size() &&
		bksge::equal(s1.begin(), s1.end(), sp.begin() + Offset, sp.end());
}

GTEST_TEST(SpanTest, SubspanTest)
{
	BKSGE_CXX14_CONSTEXPR int carr1[] = {1, 2, 3, 4};
	{
		using Sp = bksge::span<const int>;
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test<Sp, 0>(Sp{})));
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test<Sp, 0, 4>(Sp{carr1})));
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test<Sp, 0, 3>(Sp{carr1})));
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test<Sp, 0, 2>(Sp{carr1})));
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test<Sp, 0, 1>(Sp{carr1})));
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test<Sp, 0, 0>(Sp{carr1})));
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test<Sp, 1, 3>(Sp{carr1})));
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test<Sp, 2, 2>(Sp{carr1})));
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test<Sp, 3, 1>(Sp{carr1})));
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test<Sp, 4, 0>(Sp{carr1})));
	}

	{
		using Sp = bksge::span<const int, 4>;
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test<Sp, 0, 4>(Sp{carr1})));
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test<Sp, 0, 3>(Sp{carr1})));
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test<Sp, 0, 2>(Sp{carr1})));
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test<Sp, 0, 1>(Sp{carr1})));
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test<Sp, 0, 0>(Sp{carr1})));
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test<Sp, 1, 3>(Sp{carr1})));
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test<Sp, 2, 2>(Sp{carr1})));
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test<Sp, 3, 1>(Sp{carr1})));
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test<Sp, 4, 0>(Sp{carr1})));
	}

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

}	// namespace subspan_test

}	// namespace bksge_span_test

#undef ASSERT_SAME_TYPE
