/**
 *	@file	unit_test_fnd_tuple_tuple_size.cpp
 *
 *	@brief	tuple_size のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/tuple/tuple_size.hpp>
#include <bksge/fnd/tuple/tuple.hpp>
#include <bksge/fnd/type_traits/is_base_of.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <bksge/fnd/type_traits/integral_constant.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>
//#include <bksge/fnd/array.hpp>
#include <bksge/fnd/pair.hpp>
#include <gtest/gtest.h>

namespace bksge_tuple_test
{

namespace tuple_size_test
{

template <typename T, bksge::size_t N>
void test()
{
	static_assert(bksge::tuple_size<T>::value == N, "");
	static_assert(bksge::tuple_size<const T>::value == N, "");
	static_assert(bksge::tuple_size<volatile T>::value == N, "");
	static_assert(bksge::tuple_size<const volatile T>::value == N, "");
}

GTEST_TEST(TupleTest, TupleSizeTest)
{
	test<bksge::tuple<>, 0>();
	test<bksge::tuple<int>, 1>();
	test<bksge::tuple<char, int>, 2>();
	test<bksge::tuple<char, char*, int>, 3>();

	// TODO
	//test<bksge::array<int, 5>, 5>();
	//test<bksge::array<const char *, 4>, 4>();
	//test<bksge::array<char *, 3>, 3>();

	test<bksge::pair<int, int>, 2>();
	test<bksge::pair<const int, int>, 2>();
	test<bksge::pair<int, volatile int>, 2>();
	test<bksge::pair<char *, int>, 2>();
}

}	// namespace tuple_size_test

namespace tuple_size_value_sfinae_test
{

template <typename T, typename = decltype(bksge::tuple_size<T>::value)>
constexpr bool has_value(int) { return true; }
template <typename> constexpr bool has_value(long) { return false; }
template <typename T> constexpr bool has_value() { return has_value<T>(0); }

GTEST_TEST(TupleTest, TupleSizeValueSfinaeTest)
{
	// Test that the ::value member does not exist
	static_assert( has_value<bksge::tuple<int> const>(), "");
	static_assert( has_value<bksge::pair<int, long> volatile>(), "");
	static_assert(!has_value<int>(), "");
	static_assert(!has_value<const int>(), "");
	static_assert(!has_value<volatile void>(), "");
	static_assert(!has_value<const volatile bksge::tuple<int>&>(), "");
}

}	// namespace tuple_size_value_sfinae_test

}	// namespace bksge_tuple_test
