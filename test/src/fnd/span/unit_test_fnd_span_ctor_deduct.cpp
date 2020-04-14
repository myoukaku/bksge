/**
 *	@file	unit_test_fnd_span_ctor_deduct.cpp
 *
 *	@brief
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/span.hpp>
#include <bksge/fnd/algorithm/equal.hpp>
#include <bksge/fnd/iterator/begin.hpp>
#include <bksge/fnd/iterator/end.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <bksge/fnd/config.hpp>
#include <array>
#include <cstddef>
#include <string>
#include <gtest/gtest.h>

#define ASSERT_SAME_TYPE(...) \
    static_assert((bksge::is_same<__VA_ARGS__>::value), \
                 "Types differ unexpectedly")

namespace bksge_span_test
{

namespace ctor_deduct_test
{

GTEST_TEST(SpanTest, CtorDeductTest)
{
#if defined(BKSGE_HAS_CXX17_DEDUCTION_GUIDES)
	{
		int arr[] ={1, 2, 3};
		bksge::span s{arr};
		using S = decltype(s);
		ASSERT_SAME_TYPE(S, bksge::span<int, 3>);
		EXPECT_TRUE((bksge::equal(bksge::begin(arr), bksge::end(arr), s.begin(), s.end())));
	}

	{
		std::array<double, 4> arr ={1.0, 2.0, 3.0, 4.0};
		bksge::span s{arr};
		using S = decltype(s);
		ASSERT_SAME_TYPE(S, bksge::span<double, 4>);
		EXPECT_TRUE((bksge::equal(bksge::begin(arr), bksge::end(arr), s.begin(), s.end())));
	}

	{
		const std::array<long, 5> arr ={4, 5, 6, 7, 8};
		bksge::span s{arr};
		using S = decltype(s);
		ASSERT_SAME_TYPE(S, bksge::span<const long, 5>);
		EXPECT_TRUE((bksge::equal(bksge::begin(arr), bksge::end(arr), s.begin(), s.end())));
	}

	{
		std::string str{"ABCDE"};
		bksge::span s{str};
		using S = decltype(s);
		ASSERT_SAME_TYPE(S, bksge::span<char>);
		EXPECT_TRUE(static_cast<std::size_t>(s.size()) == str.size());
		EXPECT_TRUE((bksge::equal(s.begin(), s.end(), bksge::begin(s), bksge::end(s))));
	}

	{
		const std::string str{"QWERTYUIOP"};
		bksge::span s{str};
		using S = decltype(s);
		ASSERT_SAME_TYPE(S, bksge::span<const char>);
		EXPECT_TRUE(static_cast<std::size_t>(s.size()) == str.size());
		EXPECT_TRUE((bksge::equal(s.begin(), s.end(), bksge::begin(s), bksge::end(s))));
	}
#endif
}

}	// namespace ctor_deduct_test

}	// namespace bksge_span_test
