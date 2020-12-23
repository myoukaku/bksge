/**
 *	@file	unit_test_fnd_span_ctor_range.cpp
 *
 *	@brief	span::span(Range&&) のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/span.hpp>
#include <bksge/fnd/type_traits/is_constructible.hpp>
#include <bksge/fnd/type_traits/is_nothrow_constructible.hpp>
#include <bksge/fnd/type_traits/is_implicitly_constructible.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>
#include <string>
#include <vector>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace bksge_span_test
{

namespace ctor_range_test
{

template <typename T>
struct MyRange
{
	BKSGE_CXX14_CONSTEXPR MyRange() : m_value{} {}
	BKSGE_CXX14_CONSTEXPR bksge::size_t size() const noexcept { return 1; }
	BKSGE_CXX14_CONSTEXPR T      * data()        noexcept { return &m_value; }
	BKSGE_CXX14_CONSTEXPR T const* data()  const noexcept { return &m_value; }
	BKSGE_CXX14_CONSTEXPR T      * begin()       noexcept { return &m_value; }
	BKSGE_CXX14_CONSTEXPR T const* begin() const noexcept { return &m_value; }
	BKSGE_CXX14_CONSTEXPR T      * end()         noexcept { return &m_value + 1; }
	BKSGE_CXX14_CONSTEXPR T const* end()   const noexcept { return &m_value + 1; }

	BKSGE_CXX14_CONSTEXPR T const* getV() const noexcept { return &m_value; } // for checking
	T m_value;
};

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool cv_test()
{
	static_assert(!bksge::is_constructible<bksge::span<T               >, MyRange<T>>::value, "");
	static_assert( bksge::is_constructible<bksge::span<T const         >, MyRange<T>>::value, "");
	static_assert(!bksge::is_constructible<bksge::span<T       volatile>, MyRange<T>>::value, "");
	static_assert( bksge::is_constructible<bksge::span<T const volatile>, MyRange<T>>::value, "");
	static_assert( bksge::is_constructible<bksge::span<T               >, MyRange<T>&>::value, "");
	static_assert( bksge::is_constructible<bksge::span<T const         >, MyRange<T>&>::value, "");
	static_assert( bksge::is_constructible<bksge::span<T       volatile>, MyRange<T>&>::value, "");
	static_assert( bksge::is_constructible<bksge::span<T const volatile>, MyRange<T>&>::value, "");
	static_assert(!bksge::is_constructible<bksge::span<T               >, MyRange<T>&&>::value, "");
	static_assert( bksge::is_constructible<bksge::span<T const         >, MyRange<T>&&>::value, "");
	static_assert(!bksge::is_constructible<bksge::span<T       volatile>, MyRange<T>&&>::value, "");
	static_assert( bksge::is_constructible<bksge::span<T const volatile>, MyRange<T>&&>::value, "");

	static_assert(!bksge::is_constructible<bksge::span<T               >, MyRange<T> const>::value, "");
	static_assert( bksge::is_constructible<bksge::span<T const         >, MyRange<T> const>::value, "");
	static_assert(!bksge::is_constructible<bksge::span<T       volatile>, MyRange<T> const>::value, "");
	static_assert( bksge::is_constructible<bksge::span<T const volatile>, MyRange<T> const>::value, "");
	static_assert(!bksge::is_constructible<bksge::span<T               >, MyRange<T> const&>::value, "");
	static_assert( bksge::is_constructible<bksge::span<T const         >, MyRange<T> const&>::value, "");
	static_assert(!bksge::is_constructible<bksge::span<T       volatile>, MyRange<T> const&>::value, "");
	static_assert( bksge::is_constructible<bksge::span<T const volatile>, MyRange<T> const&>::value, "");
	static_assert(!bksge::is_constructible<bksge::span<T               >, MyRange<T> const&&>::value, "");
	static_assert( bksge::is_constructible<bksge::span<T const         >, MyRange<T> const&&>::value, "");
	static_assert(!bksge::is_constructible<bksge::span<T       volatile>, MyRange<T> const&&>::value, "");
	static_assert( bksge::is_constructible<bksge::span<T const volatile>, MyRange<T> const&&>::value, "");

	return true;
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool test2()
{
	static_assert( bksge::is_constructible<bksge::span<T>   , MyRange<T>&>::value, "");
	static_assert( bksge::is_constructible<bksge::span<T, 0>, MyRange<T>&>::value, "");
	static_assert( bksge::is_constructible<bksge::span<T, 1>, MyRange<T>&>::value, "");
	static_assert( bksge::is_constructible<bksge::span<T, 2>, MyRange<T>&>::value, "");
	static_assert( bksge::is_nothrow_constructible<bksge::span<T>   , MyRange<T>&>::value, "");
	static_assert( bksge::is_nothrow_constructible<bksge::span<T, 0>, MyRange<T>&>::value, "");
	static_assert( bksge::is_nothrow_constructible<bksge::span<T, 1>, MyRange<T>&>::value, "");
	static_assert( bksge::is_nothrow_constructible<bksge::span<T, 2>, MyRange<T>&>::value, "");
	static_assert( bksge::is_implicitly_constructible<bksge::span<T>   , MyRange<T>&>::value, "");
	static_assert(!bksge::is_implicitly_constructible<bksge::span<T, 0>, MyRange<T>&>::value, "");
	static_assert(!bksge::is_implicitly_constructible<bksge::span<T, 1>, MyRange<T>&>::value, "");
	static_assert(!bksge::is_implicitly_constructible<bksge::span<T, 2>, MyRange<T>&>::value, "");

	MyRange<T>       val1{};
	MyRange<T> const val2{};
	bksge::span<T>          s1{ val1 };
	bksge::span<T, 1>       s2{ val1 };
	bksge::span<T const>    s3{ val2 };
	bksge::span<T const, 1> s4{ val2 };
	return
		s1.data() == val1.getV() && s1.size() == 1 &&
		s2.data() == val1.getV() && s2.size() == 1 &&
		s3.data() == val2.getV() && s3.size() == 1 &&
		s4.data() == val2.getV() && s4.size() == 1;
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool test()
{
	return
		test2<T>() &&
		cv_test<T>();
}

struct A {};

GTEST_TEST(SpanTest, CtorRangeTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test<int>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test<long>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test<double>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test<A>()));
	EXPECT_TRUE((test<std::string>()));
}

}	// namespace ctor_range_test

}	// namespace bksge_span_test
