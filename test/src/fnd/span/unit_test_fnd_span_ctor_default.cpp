/**
 *	@file	unit_test_fnd_span_ctor_default.cpp
 *
 *	@brief	span::span() のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/span.hpp>
#include <bksge/fnd/string/string.hpp>
#include <bksge/fnd/type_traits/is_default_constructible.hpp>
#include <bksge/fnd/type_traits/is_nothrow_default_constructible.hpp>
#include <bksge/fnd/type_traits/is_implicitly_default_constructible.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace bksge_span_test
{

namespace ctor_default_test
{

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool
test2()
{
	static_assert( bksge::is_default_constructible<bksge::span<T, bksge::dynamic_extent>>::value, "");
	static_assert( bksge::is_default_constructible<bksge::span<T, 0>>::value, "");
	static_assert(!bksge::is_default_constructible<bksge::span<T, 1>>::value, "");
	static_assert(!bksge::is_default_constructible<bksge::span<T, 2>>::value, "");
	static_assert( bksge::is_nothrow_default_constructible<bksge::span<T, bksge::dynamic_extent>>::value, "");
	static_assert( bksge::is_nothrow_default_constructible<bksge::span<T, 0>>::value, "");
	static_assert(!bksge::is_nothrow_default_constructible<bksge::span<T, 1>>::value, "");
	static_assert(!bksge::is_nothrow_default_constructible<bksge::span<T, 2>>::value, "");
	static_assert( bksge::is_implicitly_default_constructible<bksge::span<T, bksge::dynamic_extent>>::value, "");
	static_assert( bksge::is_implicitly_default_constructible<bksge::span<T, 0>>::value, "");
	static_assert(!bksge::is_implicitly_default_constructible<bksge::span<T, 1>>::value, "");
	static_assert(!bksge::is_implicitly_default_constructible<bksge::span<T, 2>>::value, "");
	bksge::span<T>    s1;
	bksge::span<T, 0> s2;
	return
		s1.data() == nullptr && s1.size() == 0 &&
		s2.data() == nullptr && s2.size() == 0;
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool
test()
{
	return
		test2<T               >() &&
		test2<T const         >() &&
		test2<T       volatile>() &&
		test2<T const volatile>();
}

struct A{};

GTEST_TEST(SpanTest, CtorDefaultTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test<int>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test<long>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test<double>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test<A>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test<bksge::string>()));
}

}	// namespace ctor_default_test

}	// namespace bksge_span_test
