/**
 *	@file	unit_test_fnd_span_ctor_ptr_len.cpp
 *
 *	@brief	span::span(pointer ptr, index_type count) のテスト
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

namespace ctor_ptr_len_test
{

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool
cv_test()
{
	constexpr bool b = !bksge::is_class<T>::value;
	static_assert(     bksge::is_constructible<bksge::span<T               >, T               *, std::size_t>::value, "");
	static_assert(    !bksge::is_constructible<bksge::span<T               >, T const         *, std::size_t>::value, "");
	static_assert(    !bksge::is_constructible<bksge::span<T               >, T       volatile*, std::size_t>::value, "");
	static_assert(    !bksge::is_constructible<bksge::span<T               >, T const volatile*, std::size_t>::value, "");
	static_assert(     bksge::is_constructible<bksge::span<T const         >, T               *, std::size_t>::value, "");
	static_assert(     bksge::is_constructible<bksge::span<T const         >, T const         *, std::size_t>::value, "");
	static_assert(    !bksge::is_constructible<bksge::span<T const         >, T       volatile*, std::size_t>::value, "");
	static_assert(    !bksge::is_constructible<bksge::span<T const         >, T const volatile*, std::size_t>::value, "");
	static_assert(     bksge::is_constructible<bksge::span<T       volatile>, T               *, std::size_t>::value, "");
	static_assert(    !bksge::is_constructible<bksge::span<T       volatile>, T const         *, std::size_t>::value, "");
	static_assert(b == bksge::is_constructible<bksge::span<T       volatile>, T       volatile*, std::size_t>::value, "");
	static_assert(    !bksge::is_constructible<bksge::span<T       volatile>, T const volatile*, std::size_t>::value, "");
	static_assert(     bksge::is_constructible<bksge::span<T const volatile>, T               *, std::size_t>::value, "");
	static_assert(     bksge::is_constructible<bksge::span<T const volatile>, T const         *, std::size_t>::value, "");
	static_assert(b == bksge::is_constructible<bksge::span<T const volatile>, T       volatile*, std::size_t>::value, "");
	static_assert(b == bksge::is_constructible<bksge::span<T const volatile>, T const volatile*, std::size_t>::value, "");
	static_assert(     bksge::is_constructible<bksge::span<T               , 0>, T               *, std::size_t>::value, "");
	static_assert(    !bksge::is_constructible<bksge::span<T               , 0>, T const         *, std::size_t>::value, "");
	static_assert(    !bksge::is_constructible<bksge::span<T               , 0>, T       volatile*, std::size_t>::value, "");
	static_assert(    !bksge::is_constructible<bksge::span<T               , 0>, T const volatile*, std::size_t>::value, "");
	static_assert(     bksge::is_constructible<bksge::span<T const         , 0>, T               *, std::size_t>::value, "");
	static_assert(     bksge::is_constructible<bksge::span<T const         , 0>, T const         *, std::size_t>::value, "");
	static_assert(    !bksge::is_constructible<bksge::span<T const         , 0>, T       volatile*, std::size_t>::value, "");
	static_assert(    !bksge::is_constructible<bksge::span<T const         , 0>, T const volatile*, std::size_t>::value, "");
	static_assert(     bksge::is_constructible<bksge::span<T       volatile, 0>, T               *, std::size_t>::value, "");
	static_assert(    !bksge::is_constructible<bksge::span<T       volatile, 0>, T const         *, std::size_t>::value, "");
	static_assert(b == bksge::is_constructible<bksge::span<T       volatile, 0>, T       volatile*, std::size_t>::value, "");
	static_assert(    !bksge::is_constructible<bksge::span<T       volatile, 0>, T const volatile*, std::size_t>::value, "");
	static_assert(     bksge::is_constructible<bksge::span<T const volatile, 0>, T               *, std::size_t>::value, "");
	static_assert(     bksge::is_constructible<bksge::span<T const volatile, 0>, T const         *, std::size_t>::value, "");
	static_assert(b == bksge::is_constructible<bksge::span<T const volatile, 0>, T       volatile*, std::size_t>::value, "");
	static_assert(b == bksge::is_constructible<bksge::span<T const volatile, 0>, T const volatile*, std::size_t>::value, "");

	return true;
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool
test2()
{
	static_assert( bksge::is_constructible<bksge::span<T>   , T*, std::size_t>::value, "");
	static_assert( bksge::is_constructible<bksge::span<T, 0>, T*, std::size_t>::value, "");
	static_assert( bksge::is_constructible<bksge::span<T, 1>, T*, std::size_t>::value, "");
	static_assert( bksge::is_constructible<bksge::span<T, 2>, T*, std::size_t>::value, "");
	static_assert( bksge::is_nothrow_constructible<bksge::span<T>   , T*, std::size_t>::value, "");
	static_assert( bksge::is_nothrow_constructible<bksge::span<T, 0>, T*, std::size_t>::value, "");
	static_assert( bksge::is_nothrow_constructible<bksge::span<T, 1>, T*, std::size_t>::value, "");
	static_assert( bksge::is_nothrow_constructible<bksge::span<T, 2>, T*, std::size_t>::value, "");
	static_assert( bksge::is_implicitly_constructible<bksge::span<T>   , T*, std::size_t>::value, "");
	static_assert(!bksge::is_implicitly_constructible<bksge::span<T, 0>, T*, std::size_t>::value, "");
	static_assert(!bksge::is_implicitly_constructible<bksge::span<T, 1>, T*, std::size_t>::value, "");
	static_assert(!bksge::is_implicitly_constructible<bksge::span<T, 2>, T*, std::size_t>::value, "");
	T arr[4] {};
	bksge::span<T>    s1{arr, 3};
	bksge::span<T, 4> s2{arr, 4};
	return
		s1.data() == &arr[0] && s1.size() == 3 &&
		s2.data() == &arr[0] && s2.size() == 4;
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

GTEST_TEST(SpanTest, CtorPtrLenTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test<int>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test<long>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test<double>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test<A>()));
	                      EXPECT_TRUE((test<std::string>()));
}

}	// namespace ctor_ptr_len_test

}	// namespace bksge_span_test
