/**
 *	@file	unit_test_fnd_span_ctor_ptr_ptr.cpp
 *
 *	@brief	span::span(pointer first, pointer last) のテスト
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

namespace ctor_ptr_ptr_test
{

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool
cv_test()
{
	constexpr bool b = !bksge::is_class<T>::value;
	static_assert(     bksge::is_constructible<bksge::span<T               >, T               *, T               *>::value, "");
	static_assert(    !bksge::is_constructible<bksge::span<T               >, T const         *, T const         *>::value, "");
	static_assert(    !bksge::is_constructible<bksge::span<T               >, T       volatile*, T       volatile*>::value, "");
	static_assert(    !bksge::is_constructible<bksge::span<T               >, T const volatile*, T const volatile*>::value, "");
	static_assert(     bksge::is_constructible<bksge::span<T const         >, T               *, T               *>::value, "");
	static_assert(     bksge::is_constructible<bksge::span<T const         >, T const         *, T const         *>::value, "");
	static_assert(    !bksge::is_constructible<bksge::span<T const         >, T       volatile*, T       volatile*>::value, "");
	static_assert(    !bksge::is_constructible<bksge::span<T const         >, T const volatile*, T const volatile*>::value, "");
	static_assert(     bksge::is_constructible<bksge::span<T       volatile>, T               *, T               *>::value, "");
	static_assert(    !bksge::is_constructible<bksge::span<T       volatile>, T const         *, T const         *>::value, "");
	static_assert(b == bksge::is_constructible<bksge::span<T       volatile>, T       volatile*, T       volatile*>::value, "");
	static_assert(    !bksge::is_constructible<bksge::span<T       volatile>, T const volatile*, T const volatile*>::value, "");
	static_assert(     bksge::is_constructible<bksge::span<T const volatile>, T               *, T               *>::value, "");
	static_assert(     bksge::is_constructible<bksge::span<T const volatile>, T const         *, T const         *>::value, "");
	static_assert(b == bksge::is_constructible<bksge::span<T const volatile>, T       volatile*, T       volatile*>::value, "");
	static_assert(b == bksge::is_constructible<bksge::span<T const volatile>, T const volatile*, T const volatile*>::value, "");
	static_assert(     bksge::is_constructible<bksge::span<T               , 0>, T               *, T               *>::value, "");
	static_assert(    !bksge::is_constructible<bksge::span<T               , 0>, T const         *, T const         *>::value, "");
	static_assert(    !bksge::is_constructible<bksge::span<T               , 0>, T       volatile*, T       volatile*>::value, "");
	static_assert(    !bksge::is_constructible<bksge::span<T               , 0>, T const volatile*, T const volatile*>::value, "");
	static_assert(     bksge::is_constructible<bksge::span<T const         , 0>, T               *, T               *>::value, "");
	static_assert(     bksge::is_constructible<bksge::span<T const         , 0>, T const         *, T const         *>::value, "");
	static_assert(    !bksge::is_constructible<bksge::span<T const         , 0>, T       volatile*, T       volatile*>::value, "");
	static_assert(    !bksge::is_constructible<bksge::span<T const         , 0>, T const volatile*, T const volatile*>::value, "");
	static_assert(     bksge::is_constructible<bksge::span<T       volatile, 0>, T               *, T               *>::value, "");
	static_assert(    !bksge::is_constructible<bksge::span<T       volatile, 0>, T const         *, T const         *>::value, "");
	static_assert(b == bksge::is_constructible<bksge::span<T       volatile, 0>, T       volatile*, T       volatile*>::value, "");
	static_assert(    !bksge::is_constructible<bksge::span<T       volatile, 0>, T const volatile*, T const volatile*>::value, "");
	static_assert(     bksge::is_constructible<bksge::span<T const volatile, 0>, T               *, T               *>::value, "");
	static_assert(     bksge::is_constructible<bksge::span<T const volatile, 0>, T const         *, T const         *>::value, "");
	static_assert(b == bksge::is_constructible<bksge::span<T const volatile, 0>, T       volatile*, T       volatile*>::value, "");
	static_assert(b == bksge::is_constructible<bksge::span<T const volatile, 0>, T const volatile*, T const volatile*>::value, "");

	return true;
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool
test2()
{
	static_assert( bksge::is_constructible<bksge::span<T>   , T*, T*>::value, "");
	static_assert( bksge::is_constructible<bksge::span<T, 0>, T*, T*>::value, "");
	static_assert( bksge::is_constructible<bksge::span<T, 1>, T*, T*>::value, "");
	static_assert( bksge::is_constructible<bksge::span<T, 2>, T*, T*>::value, "");
	static_assert( bksge::is_nothrow_constructible<bksge::span<T>   , T*, T*>::value, "");
	static_assert( bksge::is_nothrow_constructible<bksge::span<T, 0>, T*, T*>::value, "");
	static_assert( bksge::is_nothrow_constructible<bksge::span<T, 1>, T*, T*>::value, "");
	static_assert( bksge::is_nothrow_constructible<bksge::span<T, 2>, T*, T*>::value, "");
	static_assert( bksge::is_implicitly_constructible<bksge::span<T>   , T*, T*>::value, "");
	static_assert(!bksge::is_implicitly_constructible<bksge::span<T, 0>, T*, T*>::value, "");
	static_assert(!bksge::is_implicitly_constructible<bksge::span<T, 1>, T*, T*>::value, "");
	static_assert(!bksge::is_implicitly_constructible<bksge::span<T, 2>, T*, T*>::value, "");
	T arr[3] {};
	bksge::span<T>    s1{arr, arr + 2};
	bksge::span<T, 3> s2{arr, arr + 3};
	return
		s1.data() == &arr[0] && s1.size() == 2 &&
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

GTEST_TEST(SpanTest, CtorPtrPtrTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test<int>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test<long>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test<double>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test<A>()));
	                      EXPECT_TRUE((test<std::string>()));
}

}	// namespace ctor_ptr_ptr_test

}	// namespace bksge_span_test
