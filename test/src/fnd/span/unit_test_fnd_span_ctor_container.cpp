/**
 *	@file	unit_test_fnd_span_ctor_container.cpp
 *
 *	@brief	span::span(Container& cont) のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/span.hpp>
#include <cstddef>
#include <string>
#include <vector>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace bksge_span_test
{

namespace ctor_container_test
{

template <typename T>
struct MyContainer
{
	constexpr MyContainer(): v_{} {}
	constexpr std::size_t size() const { return 1; }
	BKSGE_CXX14_CONSTEXPR       T* data() { return &v_; }
	constexpr const T* data() const { return &v_; }

	constexpr T const* getV() const { return &v_; } // for checking
	T v_;
};

void check_cv()
{
	std::vector<int> v  ={1, 2, 3};

	//  Types the same
	{
		bksge::span<               int> s1{v};    // a span<               int> pointing at int.
	}

	//  types different
	{
		bksge::span<const          int> s1{v};    // a span<const          int> pointing at int.
		bksge::span<      volatile int> s2{v};    // a span<      volatile int> pointing at int.
		bksge::span<      volatile int> s3{v};    // a span<      volatile int> pointing at const int.
		bksge::span<const volatile int> s4{v};    // a span<const volatile int> pointing at int.
	}

	//  Constructing a const view from a temporary
	{
		bksge::span<const int>    s1{MyContainer<int>()};
		bksge::span<const int>    s3{std::vector<int>()};
		(void)s1;
		(void)s3;
	}
}

template <typename T>
BKSGE_CXX14_CONSTEXPR bool test()
{
	MyContainer<T> val{};
	bksge::span<T> s1{val};
	return s1.data() == val.getV() && s1.size() == 1;
}

struct A {};

GTEST_TEST(SpanTest, CtorContainerTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test<const int>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test<const long>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test<const double>());
	                      EXPECT_TRUE(test<const std::string>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test<const A>());

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test<int>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test<long>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test<double>());
	                      EXPECT_TRUE(test<std::string>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test<A>());

	check_cv();
}

}	// namespace ctor_container_test

}	// namespace bksge_span_test
