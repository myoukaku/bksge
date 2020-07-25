/**
 *	@file	unit_test_fnd_span_ctor_span.cpp
 *
 *	@brief	span::span(const span<OtherElementType, OtherExtent>&) のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/span.hpp>
//#include <bksge/fnd/type_traits/is_convertible.hpp>
#include <bksge/fnd/type_traits/is_constructible.hpp>
#include <bksge/fnd/type_traits/is_nothrow_constructible.hpp>
#include <bksge/fnd/type_traits/is_implicitly_constructible.hpp>
#include <string>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "noexcept_test.hpp"

namespace bksge_span_test
{

namespace ctor_span_test
{

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool cv_test()
{
	static_assert( bksge::is_constructible<bksge::span<T               >, bksge::span<T               >>::value, "");
	static_assert(!bksge::is_constructible<bksge::span<T               >, bksge::span<T const         >>::value, "");
	static_assert(!bksge::is_constructible<bksge::span<T               >, bksge::span<T       volatile>>::value, "");
	static_assert(!bksge::is_constructible<bksge::span<T               >, bksge::span<T const volatile>>::value, "");
	static_assert( bksge::is_constructible<bksge::span<T const         >, bksge::span<T               >>::value, "");
	static_assert( bksge::is_constructible<bksge::span<T const         >, bksge::span<T const         >>::value, "");
	static_assert(!bksge::is_constructible<bksge::span<T const         >, bksge::span<T       volatile>>::value, "");
	static_assert(!bksge::is_constructible<bksge::span<T const         >, bksge::span<T const volatile>>::value, "");
	static_assert( bksge::is_constructible<bksge::span<T       volatile>, bksge::span<T               >>::value, "");
	static_assert(!bksge::is_constructible<bksge::span<T       volatile>, bksge::span<T const         >>::value, "");
	static_assert( bksge::is_constructible<bksge::span<T       volatile>, bksge::span<T       volatile>>::value, "");
	static_assert(!bksge::is_constructible<bksge::span<T       volatile>, bksge::span<T const volatile>>::value, "");
	static_assert( bksge::is_constructible<bksge::span<T const volatile>, bksge::span<T               >>::value, "");
	static_assert( bksge::is_constructible<bksge::span<T const volatile>, bksge::span<T const         >>::value, "");
	static_assert( bksge::is_constructible<bksge::span<T const volatile>, bksge::span<T       volatile>>::value, "");
	static_assert( bksge::is_constructible<bksge::span<T const volatile>, bksge::span<T const volatile>>::value, "");

	static_assert( bksge::is_constructible<bksge::span<T               >, bksge::span<T               , 0>>::value, "");
	static_assert(!bksge::is_constructible<bksge::span<T               >, bksge::span<T const         , 0>>::value, "");
	static_assert(!bksge::is_constructible<bksge::span<T               >, bksge::span<T       volatile, 0>>::value, "");
	static_assert(!bksge::is_constructible<bksge::span<T               >, bksge::span<T const volatile, 0>>::value, "");
	static_assert( bksge::is_constructible<bksge::span<T const         >, bksge::span<T               , 0>>::value, "");
	static_assert( bksge::is_constructible<bksge::span<T const         >, bksge::span<T const         , 0>>::value, "");
	static_assert(!bksge::is_constructible<bksge::span<T const         >, bksge::span<T       volatile, 0>>::value, "");
	static_assert(!bksge::is_constructible<bksge::span<T const         >, bksge::span<T const volatile, 0>>::value, "");
	static_assert( bksge::is_constructible<bksge::span<T       volatile>, bksge::span<T               , 0>>::value, "");
	static_assert(!bksge::is_constructible<bksge::span<T       volatile>, bksge::span<T const         , 0>>::value, "");
	static_assert( bksge::is_constructible<bksge::span<T       volatile>, bksge::span<T       volatile, 0>>::value, "");
	static_assert(!bksge::is_constructible<bksge::span<T       volatile>, bksge::span<T const volatile, 0>>::value, "");
	static_assert( bksge::is_constructible<bksge::span<T const volatile>, bksge::span<T               , 0>>::value, "");
	static_assert( bksge::is_constructible<bksge::span<T const volatile>, bksge::span<T const         , 0>>::value, "");
	static_assert( bksge::is_constructible<bksge::span<T const volatile>, bksge::span<T       volatile, 0>>::value, "");
	static_assert( bksge::is_constructible<bksge::span<T const volatile>, bksge::span<T const volatile, 0>>::value, "");

	static_assert( bksge::is_constructible<bksge::span<T               , 0>, bksge::span<T               >>::value, "");
	static_assert(!bksge::is_constructible<bksge::span<T               , 0>, bksge::span<T const         >>::value, "");
	static_assert(!bksge::is_constructible<bksge::span<T               , 0>, bksge::span<T       volatile>>::value, "");
	static_assert(!bksge::is_constructible<bksge::span<T               , 0>, bksge::span<T const volatile>>::value, "");
	static_assert( bksge::is_constructible<bksge::span<T const         , 0>, bksge::span<T               >>::value, "");
	static_assert( bksge::is_constructible<bksge::span<T const         , 0>, bksge::span<T const         >>::value, "");
	static_assert(!bksge::is_constructible<bksge::span<T const         , 0>, bksge::span<T       volatile>>::value, "");
	static_assert(!bksge::is_constructible<bksge::span<T const         , 0>, bksge::span<T const volatile>>::value, "");
	static_assert( bksge::is_constructible<bksge::span<T       volatile, 0>, bksge::span<T               >>::value, "");
	static_assert(!bksge::is_constructible<bksge::span<T       volatile, 0>, bksge::span<T const         >>::value, "");
	static_assert( bksge::is_constructible<bksge::span<T       volatile, 0>, bksge::span<T       volatile>>::value, "");
	static_assert(!bksge::is_constructible<bksge::span<T       volatile, 0>, bksge::span<T const volatile>>::value, "");
	static_assert( bksge::is_constructible<bksge::span<T const volatile, 0>, bksge::span<T               >>::value, "");
	static_assert( bksge::is_constructible<bksge::span<T const volatile, 0>, bksge::span<T const         >>::value, "");
	static_assert( bksge::is_constructible<bksge::span<T const volatile, 0>, bksge::span<T       volatile>>::value, "");
	static_assert( bksge::is_constructible<bksge::span<T const volatile, 0>, bksge::span<T const volatile>>::value, "");

	static_assert( bksge::is_constructible<bksge::span<T               , 0>, bksge::span<T               , 0>>::value, "");
	static_assert(!bksge::is_constructible<bksge::span<T               , 0>, bksge::span<T const         , 0>>::value, "");
	static_assert(!bksge::is_constructible<bksge::span<T               , 0>, bksge::span<T       volatile, 0>>::value, "");
	static_assert(!bksge::is_constructible<bksge::span<T               , 0>, bksge::span<T const volatile, 0>>::value, "");
	static_assert( bksge::is_constructible<bksge::span<T const         , 0>, bksge::span<T               , 0>>::value, "");
	static_assert( bksge::is_constructible<bksge::span<T const         , 0>, bksge::span<T const         , 0>>::value, "");
	static_assert(!bksge::is_constructible<bksge::span<T const         , 0>, bksge::span<T       volatile, 0>>::value, "");
	static_assert(!bksge::is_constructible<bksge::span<T const         , 0>, bksge::span<T const volatile, 0>>::value, "");
	static_assert( bksge::is_constructible<bksge::span<T       volatile, 0>, bksge::span<T               , 0>>::value, "");
	static_assert(!bksge::is_constructible<bksge::span<T       volatile, 0>, bksge::span<T const         , 0>>::value, "");
	static_assert( bksge::is_constructible<bksge::span<T       volatile, 0>, bksge::span<T       volatile, 0>>::value, "");
	static_assert(!bksge::is_constructible<bksge::span<T       volatile, 0>, bksge::span<T const volatile, 0>>::value, "");
	static_assert( bksge::is_constructible<bksge::span<T const volatile, 0>, bksge::span<T               , 0>>::value, "");
	static_assert( bksge::is_constructible<bksge::span<T const volatile, 0>, bksge::span<T const         , 0>>::value, "");
	static_assert( bksge::is_constructible<bksge::span<T const volatile, 0>, bksge::span<T       volatile, 0>>::value, "");
	static_assert( bksge::is_constructible<bksge::span<T const volatile, 0>, bksge::span<T const volatile, 0>>::value, "");

	static_assert(!bksge::is_constructible<bksge::span<T               , 1>, bksge::span<T               , 2>>::value, "");
	static_assert(!bksge::is_constructible<bksge::span<T               , 1>, bksge::span<T const         , 2>>::value, "");
	static_assert(!bksge::is_constructible<bksge::span<T               , 1>, bksge::span<T       volatile, 2>>::value, "");
	static_assert(!bksge::is_constructible<bksge::span<T               , 1>, bksge::span<T const volatile, 2>>::value, "");
	static_assert(!bksge::is_constructible<bksge::span<T const         , 1>, bksge::span<T               , 2>>::value, "");
	static_assert(!bksge::is_constructible<bksge::span<T const         , 1>, bksge::span<T const         , 2>>::value, "");
	static_assert(!bksge::is_constructible<bksge::span<T const         , 1>, bksge::span<T       volatile, 2>>::value, "");
	static_assert(!bksge::is_constructible<bksge::span<T const         , 1>, bksge::span<T const volatile, 2>>::value, "");
	static_assert(!bksge::is_constructible<bksge::span<T       volatile, 1>, bksge::span<T               , 2>>::value, "");
	static_assert(!bksge::is_constructible<bksge::span<T       volatile, 1>, bksge::span<T const         , 2>>::value, "");
	static_assert(!bksge::is_constructible<bksge::span<T       volatile, 1>, bksge::span<T       volatile, 2>>::value, "");
	static_assert(!bksge::is_constructible<bksge::span<T       volatile, 1>, bksge::span<T const volatile, 2>>::value, "");
	static_assert(!bksge::is_constructible<bksge::span<T const volatile, 1>, bksge::span<T               , 2>>::value, "");
	static_assert(!bksge::is_constructible<bksge::span<T const volatile, 1>, bksge::span<T const         , 2>>::value, "");
	static_assert(!bksge::is_constructible<bksge::span<T const volatile, 1>, bksge::span<T       volatile, 2>>::value, "");
	static_assert(!bksge::is_constructible<bksge::span<T const volatile, 1>, bksge::span<T const volatile, 2>>::value, "");

	return true;
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool test2()
{
	static_assert( bksge::is_constructible<bksge::span<T>   , bksge::span<T   >>::value, "");
	static_assert( bksge::is_constructible<bksge::span<T>   , bksge::span<T, 0>>::value, "");
	static_assert( bksge::is_constructible<bksge::span<T, 0>, bksge::span<T   >>::value, "");
	static_assert( bksge::is_constructible<bksge::span<T, 0>, bksge::span<T, 0>>::value, "");
	static_assert( bksge::is_nothrow_constructible<bksge::span<T>   , bksge::span<T   >>::value, "");
	static_assert( bksge::is_nothrow_constructible<bksge::span<T>   , bksge::span<T, 0>>::value, "");
	static_assert( bksge::is_nothrow_constructible<bksge::span<T, 0>, bksge::span<T   >>::value, "");
	static_assert( bksge::is_nothrow_constructible<bksge::span<T, 0>, bksge::span<T, 0>>::value, "");
	static_assert( bksge::is_implicitly_constructible<bksge::span<T>   , bksge::span<T   >>::value, "");
	static_assert( bksge::is_implicitly_constructible<bksge::span<T>   , bksge::span<T, 0>>::value, "");
	static_assert(!bksge::is_implicitly_constructible<bksge::span<T, 0>, bksge::span<T   >>::value, "");
	static_assert( bksge::is_implicitly_constructible<bksge::span<T, 0>, bksge::span<T, 0>>::value, "");

	bksge::span<T>    s0{};
	bksge::span<T, 0> s1{ s0 };
	bksge::span<T>    s2{ s1 };

	T arr[3] {};
	bksge::span<T>    s3{arr, 3};
	bksge::span<T, 3> s4{s3};
	bksge::span<T>    s5{s4};

	return
		s1.data() == nullptr && s1.size() == 0 &&
		s2.data() == nullptr && s2.size() == 0 &&
		s3.data() == &arr[0] && s3.size() == 3 &&
		s4.data() == &arr[0] && s4.size() == 3;
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool test()
{
	return
		test2<T      >() &&
		test2<T const>() &&
		cv_test<T>();
}

struct A{};

GTEST_TEST(SpanTest, CtorSpanTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test<int>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test<long>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test<double>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test<A>()));
	                      EXPECT_TRUE((test<std::string>()));
}

}	// namespace ctor_span_test

}	// namespace bksge_span_test
