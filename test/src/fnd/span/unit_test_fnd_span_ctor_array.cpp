/**
 *	@file	unit_test_fnd_span_ctor_array.cpp
 *
 *	@brief	span::span(element_type (&arr)[N]) のテスト
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

namespace ctor_array_test
{

void check_cv()
{
	               int   arr[] = {1, 2, 3};
	const          int  carr[] = {4, 5, 6};
	      volatile int  varr[] = {7, 8, 9};
	const volatile int cvarr[] = {1, 3, 5};

	//  Types the same (dynamic sized)
	{
		bksge::span<               int> s1{  arr};    // a span<               int> pointing at int.
		bksge::span<const          int> s2{ carr};    // a span<const          int> pointing at const int.
		bksge::span<      volatile int> s3{ varr};    // a span<      volatile int> pointing at volatile int.
		bksge::span<const volatile int> s4{cvarr};    // a span<const volatile int> pointing at const volatile int.
		EXPECT_EQ(s1.size(), 3u);
		EXPECT_EQ(s2.size(), 3u);
		EXPECT_EQ(s3.size(), 3u);
		EXPECT_EQ(s4.size(), 3u);
	}

	//  Types the same (static sized)
	{
		bksge::span<               int, 3> s1{  arr};  // a span<               int> pointing at int.
		bksge::span<const          int, 3> s2{ carr};  // a span<const          int> pointing at const int.
		bksge::span<      volatile int, 3> s3{ varr};  // a span<      volatile int> pointing at volatile int.
		bksge::span<const volatile int, 3> s4{cvarr};  // a span<const volatile int> pointing at const volatile int.
		EXPECT_EQ(s1.size(), 3u);
		EXPECT_EQ(s2.size(), 3u);
		EXPECT_EQ(s3.size(), 3u);
		EXPECT_EQ(s4.size(), 3u);
	}

	//  types different (dynamic sized)
	{
		bksge::span<const          int> s1{ arr};     // a span<const          int> pointing at int.
		bksge::span<      volatile int> s2{ arr};     // a span<      volatile int> pointing at int.
		bksge::span<      volatile int> s3{ arr};     // a span<      volatile int> pointing at const int.
		bksge::span<const volatile int> s4{ arr};     // a span<const volatile int> pointing at int.
		bksge::span<const volatile int> s5{carr};     // a span<const volatile int> pointing at const int.
		bksge::span<const volatile int> s6{varr};     // a span<const volatile int> pointing at volatile int.
		EXPECT_EQ(s1.size(), 3u);
		EXPECT_EQ(s2.size(), 3u);
		EXPECT_EQ(s3.size(), 3u);
		EXPECT_EQ(s4.size(), 3u);
		EXPECT_EQ(s5.size(), 3u);
		EXPECT_EQ(s6.size(), 3u);
	}

	//  types different (static sized)
	{
		bksge::span<const          int, 3> s1{ arr};   // a span<const          int> pointing at int.
		bksge::span<      volatile int, 3> s2{ arr};   // a span<      volatile int> pointing at int.
		bksge::span<      volatile int, 3> s3{ arr};   // a span<      volatile int> pointing at const int.
		bksge::span<const volatile int, 3> s4{ arr};   // a span<const volatile int> pointing at int.
		bksge::span<const volatile int, 3> s5{carr};   // a span<const volatile int> pointing at const int.
		bksge::span<const volatile int, 3> s6{varr};   // a span<const volatile int> pointing at volatile int.
		EXPECT_EQ(s1.size(), 3u);
		EXPECT_EQ(s2.size(), 3u);
		EXPECT_EQ(s3.size(), 3u);
		EXPECT_EQ(s4.size(), 3u);
		EXPECT_EQ(s5.size(), 3u);
		EXPECT_EQ(s6.size(), 3u);
	}
}

template <typename T>
BKSGE_CXX14_CONSTEXPR bool test()
{
	T val[2] ={};

	BKSGE_ASSERT_NOEXCEPT(bksge::span<const T>   {val});
	BKSGE_ASSERT_NOEXCEPT(bksge::span<const T, 2>{val});
	bksge::span<const T>    s1{val};
	bksge::span<const T, 2> s2{val};
	return
		s1.data() == &val[0] && s1.size() == 2 &&
		s2.data() == &val[0] && s2.size() == 2;
}

struct A {};

GTEST_TEST(SpanTest, CtorArrayTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test<int>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test<long>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test<double>());
	                      EXPECT_TRUE(test<std::string>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test<A>());

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test<const int>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test<const long>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test<const double>());
	                      EXPECT_TRUE(test<const std::string>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test<const A>());

	check_cv();
}

}	// namespace ctor_array_test

}	// namespace bksge_span_test
