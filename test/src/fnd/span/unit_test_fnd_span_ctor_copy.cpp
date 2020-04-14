/**
 *	@file	unit_test_fnd_span_ctor_copy.cpp
 *
 *	@brief	span::span(const span& other) のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/span.hpp>
#include <string>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "noexcept_test.hpp"

namespace bksge_span_test
{

namespace ctor_copy_test
{

template <typename T>
BKSGE_CXX14_CONSTEXPR bool do_copy(const T& rhs)
{
	BKSGE_ASSERT_NOEXCEPT(T{rhs});
	T lhs{rhs};
	return lhs.data() == rhs.data() && lhs.size() == rhs.size();
}

template <typename T>
void test_cv ()
{
	int  arr[] ={1, 2, 3};
	EXPECT_TRUE((do_copy(bksge::span<T>  ())));
	EXPECT_TRUE((do_copy(bksge::span<T, 0>())));
	EXPECT_TRUE((do_copy(bksge::span<T>   (&arr[0], 1))));
	EXPECT_TRUE((do_copy(bksge::span<T, 1>(&arr[0], 1))));
	EXPECT_TRUE((do_copy(bksge::span<T>   (&arr[0], 2))));
	EXPECT_TRUE((do_copy(bksge::span<T, 2>(&arr[0], 2))));
}

struct A {};

GTEST_TEST(SpanTest, CtorCopyTest)
{
	constexpr int carr[] ={1, 2, 3};

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(do_copy(bksge::span<      int>  ()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(do_copy(bksge::span<      int, 0>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(do_copy(bksge::span<const int>   (&carr[0], 1)));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(do_copy(bksge::span<const int, 1>(&carr[0], 1)));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(do_copy(bksge::span<const int>   (&carr[0], 2)));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(do_copy(bksge::span<const int, 2>(&carr[0], 2)));

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(do_copy(bksge::span<long>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(do_copy(bksge::span<double>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(do_copy(bksge::span<A>()));

	std::string s;
	EXPECT_TRUE(do_copy(bksge::span<std::string>   ()));
	EXPECT_TRUE(do_copy(bksge::span<std::string, 0>()));
	EXPECT_TRUE(do_copy(bksge::span<std::string>   (&s, 1)));
	EXPECT_TRUE(do_copy(bksge::span<std::string, 1>(&s, 1)));

	test_cv<               int>();
	test_cv<const          int>();
	test_cv<      volatile int>();
	test_cv<const volatile int>();
}

}	// namespace ctor_copy_test

}	// namespace bksge_span_test
