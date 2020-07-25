/**
 *	@file	unit_test_fnd_span_ctor_stdarray.cpp
 *
 *	@brief	span::span(array<value_type, N>& arr) のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/span.hpp>
#include <bksge/fnd/type_traits/is_constructible.hpp>
#include <bksge/fnd/type_traits/is_nothrow_constructible.hpp>
#include <bksge/fnd/type_traits/is_implicitly_constructible.hpp>
#include <bksge/fnd/type_traits/remove_volatile.hpp>
#include <array>
#include <string>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "noexcept_test.hpp"

namespace bksge_span_test
{

namespace ctor_stdarray_test
{

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool
cv_test()
{
	static_assert( bksge::is_constructible<bksge::span<T               >, std::array<T, 2>      &>::value, "");
	static_assert(!bksge::is_constructible<bksge::span<T               >, std::array<T, 2> const&>::value, "");
	static_assert( bksge::is_constructible<bksge::span<T const         >, std::array<T, 2>      &>::value, "");
	static_assert( bksge::is_constructible<bksge::span<T const         >, std::array<T, 2> const&>::value, "");
	static_assert( bksge::is_constructible<bksge::span<T       volatile>, std::array<T, 2>      &>::value, "");
	static_assert(!bksge::is_constructible<bksge::span<T       volatile>, std::array<T, 2> const&>::value, "");
	static_assert( bksge::is_constructible<bksge::span<T const volatile>, std::array<T, 2>      &>::value, "");
	static_assert( bksge::is_constructible<bksge::span<T const volatile>, std::array<T, 2> const&>::value, "");
	static_assert( bksge::is_constructible<bksge::span<T               >, std::array<T, 3>      &>::value, "");
	static_assert(!bksge::is_constructible<bksge::span<T               >, std::array<T, 3> const&>::value, "");
	static_assert( bksge::is_constructible<bksge::span<T const         >, std::array<T, 3>      &>::value, "");
	static_assert( bksge::is_constructible<bksge::span<T const         >, std::array<T, 3> const&>::value, "");
	static_assert( bksge::is_constructible<bksge::span<T       volatile>, std::array<T, 3>      &>::value, "");
	static_assert(!bksge::is_constructible<bksge::span<T       volatile>, std::array<T, 3> const&>::value, "");
	static_assert( bksge::is_constructible<bksge::span<T const volatile>, std::array<T, 3>      &>::value, "");
	static_assert( bksge::is_constructible<bksge::span<T const volatile>, std::array<T, 3> const&>::value, "");
	static_assert( bksge::is_constructible<bksge::span<T               , 2>, std::array<T, 2>      &>::value, "");
	static_assert(!bksge::is_constructible<bksge::span<T               , 2>, std::array<T, 2> const&>::value, "");
	static_assert( bksge::is_constructible<bksge::span<T const         , 2>, std::array<T, 2>      &>::value, "");
	static_assert( bksge::is_constructible<bksge::span<T const         , 2>, std::array<T, 2> const&>::value, "");
	static_assert( bksge::is_constructible<bksge::span<T       volatile, 2>, std::array<T, 2>      &>::value, "");
	static_assert(!bksge::is_constructible<bksge::span<T       volatile, 2>, std::array<T, 2> const&>::value, "");
	static_assert( bksge::is_constructible<bksge::span<T const volatile, 2>, std::array<T, 2>      &>::value, "");
	static_assert( bksge::is_constructible<bksge::span<T const volatile, 2>, std::array<T, 2> const&>::value, "");
	static_assert(!bksge::is_constructible<bksge::span<T               , 2>, std::array<T, 3>      &>::value, "");
	static_assert(!bksge::is_constructible<bksge::span<T               , 2>, std::array<T, 3> const&>::value, "");
	static_assert(!bksge::is_constructible<bksge::span<T const         , 2>, std::array<T, 3>      &>::value, "");
	static_assert(!bksge::is_constructible<bksge::span<T const         , 2>, std::array<T, 3> const&>::value, "");
	static_assert(!bksge::is_constructible<bksge::span<T       volatile, 2>, std::array<T, 3>      &>::value, "");
	static_assert(!bksge::is_constructible<bksge::span<T       volatile, 2>, std::array<T, 3> const&>::value, "");
	static_assert(!bksge::is_constructible<bksge::span<T const volatile, 2>, std::array<T, 3>      &>::value, "");
	static_assert(!bksge::is_constructible<bksge::span<T const volatile, 2>, std::array<T, 3> const&>::value, "");

	return true;
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool
test2()
{
	using U = bksge::remove_cv_t<T>;
	static_assert( bksge::is_constructible<bksge::span<T>   , std::array<U, 2>&>::value, "");
	static_assert(!bksge::is_constructible<bksge::span<T, 0>, std::array<U, 2>&>::value, "");
	static_assert(!bksge::is_constructible<bksge::span<T, 1>, std::array<U, 2>&>::value, "");
	static_assert( bksge::is_constructible<bksge::span<T, 2>, std::array<U, 2>&>::value, "");
	static_assert( bksge::is_nothrow_constructible<bksge::span<T>   , std::array<U, 2>&>::value, "");
	static_assert(!bksge::is_nothrow_constructible<bksge::span<T, 0>, std::array<U, 2>&>::value, "");
	static_assert(!bksge::is_nothrow_constructible<bksge::span<T, 1>, std::array<U, 2>&>::value, "");
	static_assert( bksge::is_nothrow_constructible<bksge::span<T, 2>, std::array<U, 2>&>::value, "");
	static_assert( bksge::is_implicitly_constructible<bksge::span<T>   , std::array<U, 2>&>::value, "");
	static_assert(!bksge::is_implicitly_constructible<bksge::span<T, 0>, std::array<U, 2>&>::value, "");
	static_assert(!bksge::is_implicitly_constructible<bksge::span<T, 1>, std::array<U, 2>&>::value, "");
	static_assert( bksge::is_implicitly_constructible<bksge::span<T, 2>, std::array<U, 2>&>::value, "");
	std::array<U, 3>       arr{};
	std::array<U, 4> const carr{};
	bksge::span<U>          s1{arr};
	bksge::span<U const, 4> s2{carr};
	return
		s1.data() == &arr[0]  && s1.size() == 3 &&
		s2.data() == &carr[0] && s2.size() == 4;
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

GTEST_TEST(SpanTest, CtorStdArrayTest)
{
	BKSGE_CXX17_CONSTEXPR_EXPECT_TRUE((test<int>()));
	BKSGE_CXX17_CONSTEXPR_EXPECT_TRUE((test<long>()));
	BKSGE_CXX17_CONSTEXPR_EXPECT_TRUE((test<double>()));
	BKSGE_CXX17_CONSTEXPR_EXPECT_TRUE((test<A>()));
	                      EXPECT_TRUE((test<std::string>()));
}

}	// namespace ctor_stdarray_test

}	// namespace bksge_span_test
