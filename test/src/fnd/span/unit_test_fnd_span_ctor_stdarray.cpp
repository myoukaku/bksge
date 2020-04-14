/**
 *	@file	unit_test_fnd_span_ctor_stdarray.cpp
 *
 *	@brief	span::span(array<value_type, N>& arr) のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/span.hpp>
#include <array>
#include <string>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "noexcept_test.hpp"

namespace bksge_span_test
{

namespace ctor_stdarray_test
{

void check_cv()
{
	std::array<int, 3> arr  ={1, 2, 3};
//  STL says these are not cromulent
//  std::array<const int,3> carr = {4,5,6};
//  std::array<volatile int, 3> varr = {7,8,9};
//  std::array<const volatile int, 3> cvarr = {1,3,5};

	//  Types the same (dynamic sized)
	{
		bksge::span<               int> s1{arr};    // a span<               int> pointing at int.
		EXPECT_EQ(s1.size(), 3u);
	}

	//  Types the same (static sized)
	{
		bksge::span<               int, 3> s1{arr};  // a span<               int> pointing at int.
		EXPECT_EQ(s1.size(), 3u);
	}

	//  types different (dynamic sized)
	{
		bksge::span<const          int> s1{arr};     // a span<const          int> pointing at int.
		bksge::span<      volatile int> s2{arr};     // a span<      volatile int> pointing at int.
		bksge::span<const volatile int> s3{arr};     // a span<const volatile int> pointing at int.
		EXPECT_EQ(s1.size(), 3u);
		EXPECT_EQ(s2.size(), 3u);
		EXPECT_EQ(s3.size(), 3u);
	}

	//  types different (static sized)
	{
		bksge::span<const          int, 3> s1{arr};   // a span<const          int> pointing at int.
		bksge::span<      volatile int, 3> s2{arr};   // a span<      volatile int> pointing at int.
		bksge::span<const volatile int, 3> s3{arr};   // a span<const volatile int> pointing at int.
		EXPECT_EQ(s1.size(), 3u);
		EXPECT_EQ(s2.size(), 3u);
		EXPECT_EQ(s3.size(), 3u);
	}
}

template <typename T>
BKSGE_CXX14_CONSTEXPR bool test()
{
	std::array<T, 2>        val = {T(), T()};
	std::array<T, 3> const cval = {T(), T(), T()};
	BKSGE_ASSERT_NOEXCEPT(bksge::span<const T>   {val});
	BKSGE_ASSERT_NOEXCEPT(bksge::span<const T, 2>{val});
	BKSGE_ASSERT_NOEXCEPT(bksge::span<const T>   {cval});
	BKSGE_ASSERT_NOEXCEPT(bksge::span<const T, 3>{cval});
	bksge::span<const T>    s1{val};
	bksge::span<const T, 2> s2{val};
	bksge::span<const T>    s3{cval};
	bksge::span<const T, 3> s4{cval};
	return
		s1.data() == & val[0] && s1.size() == 2 &&
		s2.data() == & val[0] && s2.size() == 2 &&
		s3.data() == &cval[0] && s3.size() == 3 &&
		s4.data() == &cval[0] && s4.size() == 3;
}

struct A {};

GTEST_TEST(SpanTest, CtorStdArrayTest)
{
	BKSGE_CXX17_CONSTEXPR_EXPECT_TRUE(test<int>());
	BKSGE_CXX17_CONSTEXPR_EXPECT_TRUE(test<long>());
	BKSGE_CXX17_CONSTEXPR_EXPECT_TRUE(test<double>());
	                      EXPECT_TRUE(test<std::string>());
	BKSGE_CXX17_CONSTEXPR_EXPECT_TRUE(test<A>());

	check_cv();
}

}	// namespace ctor_stdarray_test

}	// namespace bksge_span_test
