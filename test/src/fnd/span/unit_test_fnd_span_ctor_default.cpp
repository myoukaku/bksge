/**
 *	@file	unit_test_fnd_span_ctor_default.cpp
 *
 *	@brief	span::span() のテスト
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

namespace ctor_default_test
{

void check_cv()
{
	//  Types the same (dynamic sized)
	{
		bksge::span<               int> s1;
		bksge::span<const          int> s2;
		bksge::span<      volatile int> s3;
		bksge::span<const volatile int> s4;
		EXPECT_EQ(s1.size(), 0u);
		EXPECT_EQ(s2.size(), 0u);
		EXPECT_EQ(s3.size(), 0u);
		EXPECT_EQ(s4.size(), 0u);
	}

	//  Types the same (static sized)
	{
		bksge::span<               int, 0> s1;
		bksge::span<const          int, 0> s2;
		bksge::span<      volatile int, 0> s3;
		bksge::span<const volatile int, 0> s4;
		EXPECT_EQ(s1.size(), 0u);
		EXPECT_EQ(s2.size(), 0u);
		EXPECT_EQ(s3.size(), 0u);
		EXPECT_EQ(s4.size(), 0u);
	}
}

template <typename T>
BKSGE_CXX14_CONSTEXPR bool test()
{
	BKSGE_ASSERT_NOEXCEPT(T{});
	bksge::span<const T>    s1;
	bksge::span<const T, 0> s2;
	return
		s1.data() == nullptr && s1.size() == 0 &&
		s2.data() == nullptr && s2.size() == 0;
}

struct A {};

GTEST_TEST(SpanTest, CtorDefaultTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test<int>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test<long>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test<double>());
	                      EXPECT_TRUE(test<std::string>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test<A>());

	check_cv();
}

}	// namespace ctor_default_test

}	// namespace bksge_span_test
