/**
 *	@file	unit_test_fnd_span_tuple_size.cpp
 *
 *	@brief	 のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/span.hpp>
#include <cstddef>
#include <gtest/gtest.h>

namespace bksge_span_test
{

namespace tuple_size_test
{

template <typename T, std::size_t N>
void test()
{
	{
		typedef bksge::span<T, N> C;
		static_assert((std::tuple_size<C>::value == N), "");
	}
	{
		typedef bksge::span<T const, N> C;
		static_assert((std::tuple_size<C>::value == N), "");
	}
	{
		typedef bksge::span<T volatile, N> C;
		static_assert((std::tuple_size<C>::value == N), "");
	}
	{
		typedef bksge::span<T const volatile, N> C;
		static_assert((std::tuple_size<C>::value == N), "");
	}
}

GTEST_TEST(SpanTest, TupleSizeTest)
{
	test<double, 0>();
	test<double, 3>();
	test<double, 5>();
}

}	// namespace tuple_size_test

}	// namespace bksge_span_test
