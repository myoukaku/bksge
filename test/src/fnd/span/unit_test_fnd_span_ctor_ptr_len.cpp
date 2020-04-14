/**
 *	@file	unit_test_fnd_span_ctor_ptr_len.cpp
 *
 *	@brief	span::span(pointer ptr, index_type count) のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/span.hpp>
#include <string>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace bksge_span_test
{

namespace ctor_ptr_len_test
{

void check_cv()
{
	               int   arr[] ={1, 2, 3};
	const          int  carr[] ={4, 5, 6};
	      volatile int  varr[] ={7, 8, 9};
	const volatile int cvarr[] ={1, 3, 5};

	//  Types the same (dynamic sized)
	{
		bksge::span<               int> s1{  arr, 3}; // a span<               int> pointing at int.
		bksge::span<const          int> s2{ carr, 3}; // a span<const          int> pointing at const int.
		bksge::span<      volatile int> s3{ varr, 3}; // a span<      volatile int> pointing at volatile int.
		bksge::span<const volatile int> s4{cvarr, 3}; // a span<const volatile int> pointing at const volatile int.
		EXPECT_EQ(s1.size(), 3u);
		EXPECT_EQ(s2.size(), 3u);
		EXPECT_EQ(s3.size(), 3u);
		EXPECT_EQ(s4.size(), 3u);
	}

	//  Types the same (static sized)
	{
		bksge::span<               int, 3> s1{  arr, 3};   // a span<               int> pointing at int.
		bksge::span<const          int, 3> s2{ carr, 3};   // a span<const          int> pointing at const int.
		bksge::span<      volatile int, 3> s3{ varr, 3};   // a span<      volatile int> pointing at volatile int.
		bksge::span<const volatile int, 3> s4{cvarr, 3};   // a span<const volatile int> pointing at const volatile int.
		EXPECT_EQ(s1.size(), 3u);
		EXPECT_EQ(s2.size(), 3u);
		EXPECT_EQ(s3.size(), 3u);
		EXPECT_EQ(s4.size(), 3u);
	}

	//  types different (dynamic sized)
	{
		bksge::span<const          int> s1{ arr, 3};      // a span<const          int> pointing at int.
		bksge::span<      volatile int> s2{ arr, 3};      // a span<      volatile int> pointing at int.
		bksge::span<      volatile int> s3{ arr, 3};      // a span<      volatile int> pointing at const int.
		bksge::span<const volatile int> s4{ arr, 3};      // a span<const volatile int> pointing at int.
		bksge::span<const volatile int> s5{carr, 3};      // a span<const volatile int> pointing at const int.
		bksge::span<const volatile int> s6{varr, 3};      // a span<const volatile int> pointing at volatile int.
		EXPECT_EQ(s1.size(), 3u);
		EXPECT_EQ(s2.size(), 3u);
		EXPECT_EQ(s3.size(), 3u);
		EXPECT_EQ(s4.size(), 3u);
		EXPECT_EQ(s5.size(), 3u);
		EXPECT_EQ(s6.size(), 3u);
	}

	//  types different (static sized)
	{
		bksge::span<const          int, 3> s1{ arr, 3};    // a span<const          int> pointing at int.
		bksge::span<      volatile int, 3> s2{ arr, 3};    // a span<      volatile int> pointing at int.
		bksge::span<      volatile int, 3> s3{ arr, 3};    // a span<      volatile int> pointing at const int.
		bksge::span<const volatile int, 3> s4{ arr, 3};    // a span<const volatile int> pointing at int.
		bksge::span<const volatile int, 3> s5{carr, 3};    // a span<const volatile int> pointing at const int.
		bksge::span<const volatile int, 3> s6{varr, 3};    // a span<const volatile int> pointing at volatile int.
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
	T val[2] = {};
	bksge::span<const T>    s1{val, 2};
	bksge::span<const T, 2> s2{val, 2};
	return
		s1.data() == &val[0] && s1.size() == 2 &&
		s2.data() == &val[0] && s2.size() == 2;
}

struct A {};

GTEST_TEST(SpanTest, CtorPtrLenTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test<int>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test<long>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test<double>());
	                      EXPECT_TRUE(test<std::string>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test<A>());

	check_cv();
}

}	// namespace ctor_ptr_len_test

}	// namespace bksge_span_test
