/**
 *	@file	unit_test_fnd_span_ctor_array.cpp
 *
 *	@brief	span::span(element_type (&arr)[N]) のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/span.hpp>
#include <bksge/fnd/type_traits/is_constructible.hpp>
#include <bksge/fnd/type_traits/is_nothrow_constructible.hpp>
#include <bksge/fnd/type_traits/is_implicitly_constructible.hpp>
#include <string>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace bksge_span_test
{

namespace ctor_array_test
{

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool
cv_test()
{
	static_assert( bksge::is_constructible<bksge::span<T               >, T               (&)[2]>::value, "");
	static_assert(!bksge::is_constructible<bksge::span<T               >, T const         (&)[2]>::value, "");
	static_assert(!bksge::is_constructible<bksge::span<T               >, T       volatile(&)[2]>::value, "");
	static_assert(!bksge::is_constructible<bksge::span<T               >, T const volatile(&)[2]>::value, "");
	static_assert( bksge::is_constructible<bksge::span<T const         >, T               (&)[2]>::value, "");
	static_assert( bksge::is_constructible<bksge::span<T const         >, T const         (&)[2]>::value, "");
	static_assert(!bksge::is_constructible<bksge::span<T const         >, T       volatile(&)[2]>::value, "");
	static_assert(!bksge::is_constructible<bksge::span<T const         >, T const volatile(&)[2]>::value, "");
	static_assert( bksge::is_constructible<bksge::span<T       volatile>, T               (&)[2]>::value, "");
	static_assert(!bksge::is_constructible<bksge::span<T       volatile>, T const         (&)[2]>::value, "");
	static_assert( bksge::is_constructible<bksge::span<T       volatile>, T       volatile(&)[2]>::value, "");
	static_assert(!bksge::is_constructible<bksge::span<T       volatile>, T const volatile(&)[2]>::value, "");
	static_assert( bksge::is_constructible<bksge::span<T const volatile>, T               (&)[2]>::value, "");
	static_assert( bksge::is_constructible<bksge::span<T const volatile>, T const         (&)[2]>::value, "");
	static_assert( bksge::is_constructible<bksge::span<T const volatile>, T       volatile(&)[2]>::value, "");
	static_assert( bksge::is_constructible<bksge::span<T const volatile>, T const volatile(&)[2]>::value, "");
	static_assert( bksge::is_constructible<bksge::span<T               >, T               (&)[3]>::value, "");
	static_assert(!bksge::is_constructible<bksge::span<T               >, T const         (&)[3]>::value, "");
	static_assert(!bksge::is_constructible<bksge::span<T               >, T       volatile(&)[3]>::value, "");
	static_assert(!bksge::is_constructible<bksge::span<T               >, T const volatile(&)[3]>::value, "");
	static_assert( bksge::is_constructible<bksge::span<T const         >, T               (&)[3]>::value, "");
	static_assert( bksge::is_constructible<bksge::span<T const         >, T const         (&)[3]>::value, "");
	static_assert(!bksge::is_constructible<bksge::span<T const         >, T       volatile(&)[3]>::value, "");
	static_assert(!bksge::is_constructible<bksge::span<T const         >, T const volatile(&)[3]>::value, "");
	static_assert( bksge::is_constructible<bksge::span<T       volatile>, T               (&)[3]>::value, "");
	static_assert(!bksge::is_constructible<bksge::span<T       volatile>, T const         (&)[3]>::value, "");
	static_assert( bksge::is_constructible<bksge::span<T       volatile>, T       volatile(&)[3]>::value, "");
	static_assert(!bksge::is_constructible<bksge::span<T       volatile>, T const volatile(&)[3]>::value, "");
	static_assert( bksge::is_constructible<bksge::span<T const volatile>, T               (&)[3]>::value, "");
	static_assert( bksge::is_constructible<bksge::span<T const volatile>, T const         (&)[3]>::value, "");
	static_assert( bksge::is_constructible<bksge::span<T const volatile>, T       volatile(&)[3]>::value, "");
	static_assert( bksge::is_constructible<bksge::span<T const volatile>, T const volatile(&)[3]>::value, "");
	static_assert( bksge::is_constructible<bksge::span<T               , 2>, T               (&)[2]>::value, "");
	static_assert(!bksge::is_constructible<bksge::span<T               , 2>, T const         (&)[2]>::value, "");
	static_assert(!bksge::is_constructible<bksge::span<T               , 2>, T       volatile(&)[2]>::value, "");
	static_assert(!bksge::is_constructible<bksge::span<T               , 2>, T const volatile(&)[2]>::value, "");
	static_assert( bksge::is_constructible<bksge::span<T const         , 2>, T               (&)[2]>::value, "");
	static_assert( bksge::is_constructible<bksge::span<T const         , 2>, T const         (&)[2]>::value, "");
	static_assert(!bksge::is_constructible<bksge::span<T const         , 2>, T       volatile(&)[2]>::value, "");
	static_assert(!bksge::is_constructible<bksge::span<T const         , 2>, T const volatile(&)[2]>::value, "");
	static_assert( bksge::is_constructible<bksge::span<T       volatile, 2>, T               (&)[2]>::value, "");
	static_assert(!bksge::is_constructible<bksge::span<T       volatile, 2>, T const         (&)[2]>::value, "");
	static_assert( bksge::is_constructible<bksge::span<T       volatile, 2>, T       volatile(&)[2]>::value, "");
	static_assert(!bksge::is_constructible<bksge::span<T       volatile, 2>, T const volatile(&)[2]>::value, "");
	static_assert( bksge::is_constructible<bksge::span<T const volatile, 2>, T               (&)[2]>::value, "");
	static_assert( bksge::is_constructible<bksge::span<T const volatile, 2>, T const         (&)[2]>::value, "");
	static_assert( bksge::is_constructible<bksge::span<T const volatile, 2>, T       volatile(&)[2]>::value, "");
	static_assert( bksge::is_constructible<bksge::span<T const volatile, 2>, T const volatile(&)[2]>::value, "");
	static_assert(!bksge::is_constructible<bksge::span<T               , 2>, T               (&)[3]>::value, "");
	static_assert(!bksge::is_constructible<bksge::span<T               , 2>, T const         (&)[3]>::value, "");
	static_assert(!bksge::is_constructible<bksge::span<T               , 2>, T       volatile(&)[3]>::value, "");
	static_assert(!bksge::is_constructible<bksge::span<T               , 2>, T const volatile(&)[3]>::value, "");
	static_assert(!bksge::is_constructible<bksge::span<T const         , 2>, T               (&)[3]>::value, "");
	static_assert(!bksge::is_constructible<bksge::span<T const         , 2>, T const         (&)[3]>::value, "");
	static_assert(!bksge::is_constructible<bksge::span<T const         , 2>, T       volatile(&)[3]>::value, "");
	static_assert(!bksge::is_constructible<bksge::span<T const         , 2>, T const volatile(&)[3]>::value, "");
	static_assert(!bksge::is_constructible<bksge::span<T       volatile, 2>, T               (&)[3]>::value, "");
	static_assert(!bksge::is_constructible<bksge::span<T       volatile, 2>, T const         (&)[3]>::value, "");
	static_assert(!bksge::is_constructible<bksge::span<T       volatile, 2>, T       volatile(&)[3]>::value, "");
	static_assert(!bksge::is_constructible<bksge::span<T       volatile, 2>, T const volatile(&)[3]>::value, "");
	static_assert(!bksge::is_constructible<bksge::span<T const volatile, 2>, T               (&)[3]>::value, "");
	static_assert(!bksge::is_constructible<bksge::span<T const volatile, 2>, T const         (&)[3]>::value, "");
	static_assert(!bksge::is_constructible<bksge::span<T const volatile, 2>, T       volatile(&)[3]>::value, "");
	static_assert(!bksge::is_constructible<bksge::span<T const volatile, 2>, T const volatile(&)[3]>::value, "");

	return true;
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool
test2()
{
	static_assert( bksge::is_constructible<bksge::span<T>   , T(&)[2]>::value, "");
	static_assert(!bksge::is_constructible<bksge::span<T, 0>, T(&)[2]>::value, "");
	static_assert(!bksge::is_constructible<bksge::span<T, 1>, T(&)[2]>::value, "");
	static_assert( bksge::is_constructible<bksge::span<T, 2>, T(&)[2]>::value, "");
	static_assert( bksge::is_nothrow_constructible<bksge::span<T>   , T(&)[2]>::value, "");
	static_assert(!bksge::is_nothrow_constructible<bksge::span<T, 0>, T(&)[2]>::value, "");
	static_assert(!bksge::is_nothrow_constructible<bksge::span<T, 1>, T(&)[2]>::value, "");
	static_assert( bksge::is_nothrow_constructible<bksge::span<T, 2>, T(&)[2]>::value, "");
	static_assert( bksge::is_implicitly_constructible<bksge::span<T>   , T(&)[2]>::value, "");
	static_assert(!bksge::is_implicitly_constructible<bksge::span<T, 0>, T(&)[2]>::value, "");
	static_assert(!bksge::is_implicitly_constructible<bksge::span<T, 1>, T(&)[2]>::value, "");
	static_assert( bksge::is_implicitly_constructible<bksge::span<T, 2>, T(&)[2]>::value, "");
	T arr[3] {};
	bksge::span<T>    s1{arr};
	bksge::span<T, 3> s2{arr};
	return
		s1.data() == &arr[0] && s1.size() == 3 &&
		s2.data() == &arr[0] && s2.size() == 3;
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool
test()
{
	return
		test2<T      >() &&
		test2<T const>() &&
		cv_test<T>();
}

struct A{};

GTEST_TEST(SpanTest, CtorArrayTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test<int>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test<long>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test<double>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test<A>()));
	                      EXPECT_TRUE((test<std::string>()));
}

}	// namespace ctor_array_test

}	// namespace bksge_span_test
