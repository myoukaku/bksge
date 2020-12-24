/**
 *	@file	unit_test_fnd_span_ctor_deduct.cpp
 *
 *	@brief
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/span.hpp>
#include <bksge/fnd/algorithm/equal.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>
#include <bksge/fnd/iterator/begin.hpp>
#include <bksge/fnd/iterator/end.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <bksge/fnd/array.hpp>
#include <bksge/fnd/config.hpp>
#include <gtest/gtest.h>

#define ASSERT_SAME_TYPE(...) \
    static_assert((bksge::is_same<__VA_ARGS__>::value), \
                 "Types differ unexpectedly")

namespace bksge_span_test
{

namespace ctor_deduct_test
{

template <typename T>
struct MyRange
{
	BKSGE_CXX14_CONSTEXPR MyRange() : m_value{} {}
	BKSGE_CXX14_CONSTEXPR bksge::size_t size() const noexcept { return 1; }
	BKSGE_CXX14_CONSTEXPR T      * data()        noexcept { return &m_value; }
	BKSGE_CXX14_CONSTEXPR T const* data()  const noexcept { return &m_value; }
	BKSGE_CXX14_CONSTEXPR T      * begin()       noexcept { return &m_value; }
	BKSGE_CXX14_CONSTEXPR T const* begin() const noexcept { return &m_value; }
	BKSGE_CXX14_CONSTEXPR T      * end()         noexcept { return &m_value + 1; }
	BKSGE_CXX14_CONSTEXPR T const* end()   const noexcept { return &m_value + 1; }

	BKSGE_CXX14_CONSTEXPR T const* getV() const noexcept { return &m_value; } // for checking
	T m_value;
};

GTEST_TEST(SpanTest, CtorDeductTest)
{
#if defined(BKSGE_HAS_CXX17_DEDUCTION_GUIDES)
	{
		int arr[] = { 1,2,3 };
		bksge::span s{ arr };
		using S = decltype(s);
		ASSERT_SAME_TYPE(S, bksge::span<int, 3>);
		EXPECT_TRUE((bksge::equal(bksge::begin(arr), bksge::end(arr), s.begin(), s.end())));
	}

	{
		bksge::array<double, 4> arr = { 1.0, 2.0, 3.0, 4.0 };
		bksge::span s{ arr };
		using S = decltype(s);
		ASSERT_SAME_TYPE(S, bksge::span<double, 4>);
		EXPECT_TRUE((bksge::equal(bksge::begin(arr), bksge::end(arr), s.begin(), s.end())));
	}

	{
		bksge::array<long, 5> const arr = { 4, 5, 6, 7, 8 };
		bksge::span s{ arr };
		using S = decltype(s);
		ASSERT_SAME_TYPE(S, bksge::span<long const, 5>);
		EXPECT_TRUE((bksge::equal(bksge::begin(arr), bksge::end(arr), s.begin(), s.end())));
	}
	{
		MyRange<int> r;
		bksge::span s{ r };
		using S = decltype(s);
		ASSERT_SAME_TYPE(S, bksge::span<int>);
		EXPECT_TRUE(static_cast<bksge::size_t>(s.size()) == r.size());
		EXPECT_TRUE((bksge::equal(bksge::begin(r), bksge::end(r), s.begin(), s.end())));
	}

	{
		MyRange<char> const r;
		bksge::span s{ r };
		using S = decltype(s);
		ASSERT_SAME_TYPE(S, bksge::span<char const>);
		EXPECT_TRUE(static_cast<bksge::size_t>(s.size()) == r.size());
		EXPECT_TRUE((bksge::equal(bksge::begin(r), bksge::end(r), s.begin(), s.end())));
	}
#endif
}

}	// namespace ctor_deduct_test

}	// namespace bksge_span_test

#undef ASSERT_SAME_TYPE
