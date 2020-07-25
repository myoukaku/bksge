/**
 *	@file	unit_test_fnd_span_ctor_copy.cpp
 *
 *	@brief	span::span(const span& other) のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/span.hpp>
#include <bksge/fnd/type_traits/conditional.hpp>
#include <bksge/fnd/type_traits/is_class.hpp>
#include <bksge/fnd/type_traits/remove_volatile.hpp>
#include <string>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "noexcept_test.hpp"

namespace bksge_span_test
{

namespace ctor_copy_test
{

template <typename T>
BKSGE_CXX14_CONSTEXPR bool do_copy(T const& rhs)
{
	BKSGE_ASSERT_NOEXCEPT(T{ rhs });
	T lhs{ rhs };
	return
		lhs.data() == rhs.data() &&
		lhs.size() == rhs.size();
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool test2()
{
	using U = bksge::conditional_t<
		bksge::is_class<T>::value,
		bksge::remove_volatile_t<T>,
		T
	>;
	U a[3]{};
	return
		do_copy(bksge::span<T   >()) &&
		do_copy(bksge::span<T, 0>()) &&
		do_copy(bksge::span<T   >(a, 1)) &&
		do_copy(bksge::span<T, 1>(a, 1)) &&
		do_copy(bksge::span<T   >(a, 2)) &&
		do_copy(bksge::span<T, 2>(a, 2)) &&
		do_copy(bksge::span<T   >(a, 3)) &&
		do_copy(bksge::span<T, 3>(a, 3));
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

GTEST_TEST(SpanTest, CtorCopyTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test<int>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test<long>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test<double>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test<A>()));
	                      EXPECT_TRUE((test<std::string>()));
}

}	// namespace ctor_copy_test

}	// namespace bksge_span_test
