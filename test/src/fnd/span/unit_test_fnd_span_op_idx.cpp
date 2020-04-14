/**
 *	@file	unit_test_fnd_span_op_idx.cpp
 *
 *	@brief	reference span::operator[](index_type idx) のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/span.hpp>
#include <cstddef>
#include <string>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "noexcept_test.hpp"

namespace bksge_span_test
{

namespace op_idx_test
{

template <typename Span>
constexpr bool test(Span sp, std::size_t idx)
{
	BKSGE_ASSERT_NOEXCEPT(sp[idx]);
	return sp[idx] == *(sp.data() + idx);
}

GTEST_TEST(SpanTest, OpIdxTest)
{
	constexpr int arr1[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	BKSGE_CONSTEXPR_EXPECT_TRUE((test(bksge::span<const int>(arr1, 1), 0)));

	BKSGE_CONSTEXPR_EXPECT_TRUE((test(bksge::span<const int>(arr1, 2), 0)));
	BKSGE_CONSTEXPR_EXPECT_TRUE((test(bksge::span<const int>(arr1, 2), 1)));

	BKSGE_CONSTEXPR_EXPECT_TRUE((test(bksge::span<const int>(arr1, 3), 0)));
	BKSGE_CONSTEXPR_EXPECT_TRUE((test(bksge::span<const int>(arr1, 3), 1)));
	BKSGE_CONSTEXPR_EXPECT_TRUE((test(bksge::span<const int>(arr1, 3), 2)));

	BKSGE_CONSTEXPR_EXPECT_TRUE((test(bksge::span<const int>(arr1, 4), 0)));
	BKSGE_CONSTEXPR_EXPECT_TRUE((test(bksge::span<const int>(arr1, 4), 1)));
	BKSGE_CONSTEXPR_EXPECT_TRUE((test(bksge::span<const int>(arr1, 4), 2)));
	BKSGE_CONSTEXPR_EXPECT_TRUE((test(bksge::span<const int>(arr1, 4), 3)));

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test(bksge::span<const int, 1>(arr1, 1), 0)));

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test(bksge::span<const int, 2>(arr1, 2), 0)));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test(bksge::span<const int, 2>(arr1, 2), 1)));

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test(bksge::span<const int, 3>(arr1, 3), 0)));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test(bksge::span<const int, 3>(arr1, 3), 1)));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test(bksge::span<const int, 3>(arr1, 3), 2)));

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test(bksge::span<const int, 4>(arr1, 4), 0)));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test(bksge::span<const int, 4>(arr1, 4), 1)));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test(bksge::span<const int, 4>(arr1, 4), 2)));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test(bksge::span<const int, 4>(arr1, 4), 3)));

	int arr2[] = {10, 11, 12, 13, 14, 15, 16, 17, 18, 19};
	EXPECT_TRUE((test(bksge::span<int>(arr2, 1), 0)));

	EXPECT_TRUE((test(bksge::span<int>(arr2, 2), 0)));
	EXPECT_TRUE((test(bksge::span<int>(arr2, 2), 1)));

	EXPECT_TRUE((test(bksge::span<int>(arr2, 3), 0)));
	EXPECT_TRUE((test(bksge::span<int>(arr2, 3), 1)));
	EXPECT_TRUE((test(bksge::span<int>(arr2, 3), 2)));

	EXPECT_TRUE((test(bksge::span<int>(arr2, 4), 0)));
	EXPECT_TRUE((test(bksge::span<int>(arr2, 4), 1)));
	EXPECT_TRUE((test(bksge::span<int>(arr2, 4), 2)));
	EXPECT_TRUE((test(bksge::span<int>(arr2, 4), 3)));

	EXPECT_TRUE((test(bksge::span<int, 1>(arr2, 1), 0)));

	EXPECT_TRUE((test(bksge::span<int, 2>(arr2, 2), 0)));
	EXPECT_TRUE((test(bksge::span<int, 2>(arr2, 2), 1)));

	EXPECT_TRUE((test(bksge::span<int, 3>(arr2, 3), 0)));
	EXPECT_TRUE((test(bksge::span<int, 3>(arr2, 3), 1)));
	EXPECT_TRUE((test(bksge::span<int, 3>(arr2, 3), 2)));

	EXPECT_TRUE((test(bksge::span<int, 4>(arr2, 4), 0)));
	EXPECT_TRUE((test(bksge::span<int, 4>(arr2, 4), 1)));
	EXPECT_TRUE((test(bksge::span<int, 4>(arr2, 4), 2)));
	EXPECT_TRUE((test(bksge::span<int, 4>(arr2, 4), 3)));

	std::string s;
	EXPECT_TRUE((test(bksge::span<std::string>   (&s, 1), 0)));
	EXPECT_TRUE((test(bksge::span<std::string, 1>(&s, 1), 0)));
}

}	// namespace op_idx_test

}	// namespace bksge_span_test
