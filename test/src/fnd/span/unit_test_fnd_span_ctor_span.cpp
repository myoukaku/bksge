/**
 *	@file	unit_test_fnd_span_ctor_span.cpp
 *
 *	@brief	span::span(const span<OtherElementType, OtherExtent>&) のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/span.hpp>
//#include <bksge/fnd/type_traits/is_convertible.hpp>
#include <string>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "noexcept_test.hpp"

namespace bksge_span_test
{

namespace ctor_span_test
{

void check_cv()
{
	bksge::span<               int>   sp;
//  bksge::span<const          int>  csp;
	bksge::span<      volatile int>  vsp;
//  bksge::span<const volatile int> cvsp;

	bksge::span<               int, 0>   sp0;
//  bksge::span<const          int, 0>  csp0;
	bksge::span<      volatile int, 0>  vsp0;
//  bksge::span<const volatile int, 0> cvsp0;

	//  dynamic -> dynamic
	{
		bksge::span<const          int> s1{ sp};     // a span<const          int> pointing at int.
		bksge::span<      volatile int> s2{ sp};     // a span<      volatile int> pointing at int.
		bksge::span<const volatile int> s3{ sp};     // a span<const volatile int> pointing at int.
		bksge::span<const volatile int> s4{vsp};     // a span<const volatile int> pointing at volatile int.
		EXPECT_EQ(s1.size(), 0u);
		EXPECT_EQ(s2.size(), 0u);
		EXPECT_EQ(s3.size(), 0u);
		EXPECT_EQ(s4.size(), 0u);
	}

	//  static -> static
	{
		bksge::span<const          int, 0> s1{ sp0}; // a span<const          int> pointing at int.
		bksge::span<      volatile int, 0> s2{ sp0}; // a span<      volatile int> pointing at int.
		bksge::span<const volatile int, 0> s3{ sp0}; // a span<const volatile int> pointing at int.
		bksge::span<const volatile int, 0> s4{vsp0}; // a span<const volatile int> pointing at volatile int.
		EXPECT_EQ(s1.size(), 0u);
		EXPECT_EQ(s2.size(), 0u);
		EXPECT_EQ(s3.size(), 0u);
		EXPECT_EQ(s4.size(), 0u);
	}

	//  static -> dynamic
	{
		bksge::span<const          int> s1{ sp0};    // a span<const          int> pointing at int.
		bksge::span<      volatile int> s2{ sp0};    // a span<      volatile int> pointing at int.
		bksge::span<const volatile int> s3{ sp0};    // a span<const volatile int> pointing at int.
		bksge::span<const volatile int> s4{vsp0};    // a span<const volatile int> pointing at volatile int.
		EXPECT_EQ(s1.size(), 0u);
		EXPECT_EQ(s2.size(), 0u);
		EXPECT_EQ(s3.size(), 0u);
		EXPECT_EQ(s4.size(), 0u);
	}

	//  dynamic -> static
	{
		bksge::span<const          int, 0> s1{ sp};  // a span<const          int> pointing at int.
		bksge::span<      volatile int, 0> s2{ sp};  // a span<      volatile int> pointing at int.
		bksge::span<const volatile int, 0> s3{ sp};  // a span<const volatile int> pointing at int.
		bksge::span<const volatile int, 0> s4{vsp};  // a span<const volatile int> pointing at volatile int.
		EXPECT_EQ(s1.size(), 0u);
		EXPECT_EQ(s2.size(), 0u);
		EXPECT_EQ(s3.size(), 0u);
		EXPECT_EQ(s4.size(), 0u);
	}
}

template <typename T>
BKSGE_CXX14_CONSTEXPR bool test()
{
	bksge::span<T>    s0{};
	bksge::span<T, 0> s1(s0); // dynamic -> static
	bksge::span<T>    s2(s1); // static -> dynamic
	BKSGE_ASSERT_NOEXCEPT(bksge::span<T>   {s0});
	BKSGE_ASSERT_NOEXCEPT(bksge::span<T, 0>{s1});
	BKSGE_ASSERT_NOEXCEPT(bksge::span<T>   {s1});
	BKSGE_ASSERT_NOEXCEPT(bksge::span<T, 0>{s0});

	return
		s1.data() == nullptr && s1.size() == 0 &&
		s2.data() == nullptr && s2.size() == 0;
}

#if 0
template <typename Dest, typename Src>
bool testConversionSpan()
{
	static_assert(bksge::is_convertible<Src(*)[], Dest(*)[]>::value, "Bad input types to 'testConversionSpan");
	bksge::span<Src>     s0d{};
	bksge::span<Src>     s0s{};
	bksge::span<Dest, 0> s1(s0d); // dynamic -> static
	bksge::span<Dest>    s2(s0s); // static -> dynamic
	s1.data() == nullptr && s1.size() == 0 &&
	s2.data() == nullptr && s2.size() == 0;
}
#endif

struct A {};

GTEST_TEST(SpanTest, CtorSpanTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test<int>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test<long>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test<double>());
	                      EXPECT_TRUE(test<std::string>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test<A>());

	//  TODO: Add some conversion tests here that aren't "X --> const X"
	//  EXPECT_TRUE((testConversionSpan<unsigned char, char>()));

	check_cv();
}

}	// namespace ctor_span_test

}	// namespace bksge_span_test
