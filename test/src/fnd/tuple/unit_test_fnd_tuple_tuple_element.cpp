/**
 *	@file	unit_test_fnd_tuple_tuple_element.cpp
 *
 *	@brief	tuple_element のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/tuple/tuple_element.hpp>
#include <bksge/fnd/tuple/tuple.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>
#include <gtest/gtest.h>

namespace bksge_tuple_test
{

namespace tuple_element_test
{

template <typename T, bksge::size_t N, typename U>
void test()
{
	static_assert((bksge::is_same<typename bksge::tuple_element<N, T>::type, U>::value), "");
	static_assert((bksge::is_same<typename bksge::tuple_element<N, const T>::type, const U>::value), "");
	static_assert((bksge::is_same<typename bksge::tuple_element<N, volatile T>::type, volatile U>::value), "");
	static_assert((bksge::is_same<typename bksge::tuple_element<N, const volatile T>::type, const volatile U>::value), "");

	static_assert((bksge::is_same<typename bksge::tuple_element_t<N, T>, U>::value), "");
	static_assert((bksge::is_same<typename bksge::tuple_element_t<N, const T>, const U>::value), "");
	static_assert((bksge::is_same<typename bksge::tuple_element_t<N, volatile T>, volatile U>::value), "");
	static_assert((bksge::is_same<typename bksge::tuple_element_t<N, const volatile T>, const volatile U>::value), "");
}

GTEST_TEST(TupleTest, TupleElementTest)
{
	test<bksge::tuple<int>, 0, int>();
	test<bksge::tuple<char, int>, 0, char>();
	test<bksge::tuple<char, int>, 1, int>();
	test<bksge::tuple<int*, char, int>, 0, int*>();
	test<bksge::tuple<int*, char, int>, 1, char>();
	test<bksge::tuple<int*, char, int>, 2, int>();
}

}	// namespace tuple_element_test

}	// namespace bksge_tuple_test
