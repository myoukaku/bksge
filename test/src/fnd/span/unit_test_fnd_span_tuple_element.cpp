/**
 *	@file	unit_test_fnd_span_tuple_element.cpp
 *
 *	@brief	std::tuple_element のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/span.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <cstddef>
#include <gtest/gtest.h>

#define ASSERT_SAME_TYPE(...) \
    static_assert((bksge::is_same<__VA_ARGS__>::value), \
                 "Types differ unexpectedly")

namespace bksge_span_test
{

namespace tuple_element_test
{

template <typename T, std::size_t N, std::size_t Idx>
void test()
{
	{
		typedef bksge::span<T, N> C;
		ASSERT_SAME_TYPE(typename std::tuple_element<Idx, C>::type, T);
	}
	{
		typedef bksge::span<T const, N> C;
		ASSERT_SAME_TYPE(typename std::tuple_element<Idx, C>::type, T const);
	}
	{
		typedef bksge::span<T volatile, N> C;
		ASSERT_SAME_TYPE(typename std::tuple_element<Idx, C>::type, T volatile);
	}
	{
		typedef bksge::span<T const volatile, N> C;
		ASSERT_SAME_TYPE(typename std::tuple_element<Idx, C>::type, T const volatile);
	}
}

GTEST_TEST(SpanTest, TupleElementTest)
{
	test<double, 3, 0>();
	test<double, 3, 1>();
	test<double, 3, 2>();

	test<int, 5, 0>();
	test<int, 5, 1>();
	test<int, 5, 2>();
	test<int, 5, 3>();
	test<int, 5, 4>();
}

}	// namespace tuple_element_test

}	// namespace bksge_span_test
